/**
 * @file summaryreport.cpp
 * @author Patrick McGrath, CSCI 370, VIU
 * @version 1.0
 * @date March, 2025
 * 
 *  Assignment #8 Package Ordering Database Summary Report Program in C++ / Oracle SQL
 *  Copyright (C) 2025  Patrick McGrath
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <occi.h>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace oracle::occi;





// Declarations

// read password without display it
string readPassword();  

// check whether memberID is in system, and return member info
string checkMemberID(Statement** stmts, string memberID, string &contactName, string &deliveryAddress, string &status);

// query member info and append to outFile
int summarizeMem(string outFile, Statement** stmts, string accnum, int year);

// print start of file info to outFile, erase prior content
int beginR(string outFile, int year, string accnum, string contactName, string deliveryAddress, string status);

// check whether producer is in system and get their info
string checkProducerID(Statement** stmts, string accnum, string &farmAddress);

// query producer info and append to outFile
int summarizePro(string outFile, Statement** stmts, string accnum, int year, string farmAddress);

// convert integer year value to string YYYY-MM-DD
string formatDateYYYYMMDDfromYear(int year);

// convert string to integer or "ERROR" if invalid
int validateStrtoInt(string str);

// checks input string to make sure all numerical. if so, pads from with 0's up to length = 6
string padAccount(string input);
 
// print end of file
int endR(string outFile);





// read database password from user input
// without showing the password on the screen
string readPassword(){
    // Declare a termios structure to hold terminal settings
    struct termios settings;
    // Get the current terminal settings and store them in 'settings'
    tcgetattr(STDIN_FILENO, &settings);
    // Modify the terminal settings to disable echoing of input characters
    settings.c_lflag = (settings.c_lflag & ~(ECHO));
    // Apply the modified settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
    // Declare a string to hold the password
    string password = "";
    // Read the password from standard input
    getline(cin, password);
    // Restore the original terminal settings to re-enable echoing
    settings.c_lflag = (settings.c_lflag | ECHO);
    // Apply the restored settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
    // Return the password
    return password;
}


// checks that each char in str is a number
// then if they all are, converts the string to an int and returns the int
int validateStrtoInt(string str){
    // check there is anything entered
    int len = str.size();
    if (len <= 0){
        return -1;
    }

    // going from right most char to left most char
    // check the char is a number
    // multiply value by current 10's place, add it to running total
    // return running total or -1 on error
    int total = 0;
    int tens = 1;
    for (int i=len-1; i>=0; i--){
        if ((str[i] < 48) || (str[i] > 57)){
            return -1;
        }
        total += (str[i]-48) * tens;
        tens *= 10;
    }

    // if this far, total is good
    return total;
}


// memberid is CHAR(6), user input account number must have padded 0's if shorter
// also check each input character to make sure its a number
string padAccount(string input){
    int len = input.size();                             // length of input
    if ((len > 0) && (len <= 6)){                       // if length 0 or too long, error
        string result = "000000";                        // set starting input to 6x 0's
        for (int j=0; j<len; j++){                      // iterate through length of input
            if ((input[j] < 48) || (input[j] > 57)){    // check if current char is not a number
                return "ERROR";                         // if so, error
            } else {                
                result[6-len+j] = input[j];             // else, copy to appropriate spot in result
            }
        }
        return result;                                  // all good, return it
    }
    return "ERROR";                                     // length error 
}



// check if memberID is in the system
// return "ERROR" if not in system
// return memberID if in system, and update member info
// use statement #0
string checkMemberID(Statement** stmts, string memberID, string &contactName, string &deliveryAddress, string &status){
    // use statement #0
    stmts[0]->setString(1, memberID);
    ResultSet *rs = stmts[0]->executeQuery();
    int numberofResults = 0;
    // return variables
    string accnumGet = "ERROR";
    string contactNameGet = "ERROR";
    string deliveryAddressGet = "ERROR";
    string statusGet = "ERROR";


    // get all results
    while (rs->next()) {
        accnumGet = rs->getString(1);
        contactNameGet = rs->getString(2);
        deliveryAddressGet = rs->getString(3);
        statusGet = rs->getString(4);
        numberofResults++;
    }

    // close results
    stmts[0]->closeResultSet(rs);

    // if 0 or more than 1 results, return error values
    if (numberofResults != 1){
        contactName = "ERROR";
        deliveryAddress = "ERROR";
        status = "ERROR";
        return "ERROR";
    }

    // everything good
    contactName = contactNameGet;
    deliveryAddress = deliveryAddressGet;
    status = statusGet;
    return accnumGet;    // there is one result, return it
}


// print beginning of file header with member info
int beginR(string outFile, int year, string accnum, string contactName, string deliveryAddress, string status){
    std::ofstream file(outFile.c_str());  // Create and open a file

    if (file.is_open()) {
        file << "Summary Report of Year ";
        file << year;
        file << "\n";
        file << "\n";

        file << "Account Number:   ";
        file << accnum;
        file << "\n";

        file << "Contact Name:     ";
        file << contactName;
        file << "\n";

        file << "Delivery Address: ";
        file << deliveryAddress;
        file << "\n";

        file << "Current Status:   ";
        file << status;
        file << "\n";
        file << "\n";

        file.close();
        return 0;
    }

    return -1;
}




// convert integer year into string of format YYYY-MM-DD
string formatDateYYYYMMDDfromYear(int year){
    string result = "0000";
    char c = '0';
    int y = year;
    for (int i=0; i<4; i++){
        c = (y % 10) + 48;
        result[3-i] = c;      // i = 0, y = 2024, return[3] = 4 + 48 = '4'
        y = y / 10;
    }

    result += "-01-01"; // Jan 1
    return result;
}




// query member info and append to outFile
// use stmt #2
int summarizeMem(string outFile, Statement** stmts, string accnum, int year){
    string querydateLower = formatDateYYYYMMDDfromYear(year);    // get string YYYY-MM-DD of Jan 1 from passed year
    string querydateUpper = formatDateYYYYMMDDfromYear(year+1);    // get string YYYY-MM-DD of Jan 1 from passed year
    // return variables
    int numberofResults = 0;
    string packageType = "ERROR";
    int type_count = -1;
    // set bound values
    stmts[2]->setString(1, accnum);
    stmts[2]->setString(2, querydateLower);
    stmts[2]->setString(3, querydateUpper);


    // open file
    std::ofstream file(outFile.c_str(), std::ios::app);  // Append mode

    if (file.is_open()) {   // if file is open

        // print header
        file << "Order History of year ";
        file << year;
        file << "\n";

        file << "Package Size	|   Ordered Number";
        file << "\n";



        // result set
        ResultSet *rs = stmts[2]->executeQuery();



        // get result(s)
        while (rs->next()) {
            
            // get 1 result
            packageType = rs->getString(1);
            type_count = rs->getInt(2);
            if (type_count > 0){ // check the amount is positive
                // print result
                file << packageType;
                file << "        ";
                file << type_count;
                file << "\n";
            }
            numberofResults++;
        }
        

        // close results and file
        stmts[2]->closeResultSet(rs);

        if (numberofResults == 0){
            // no results
            file << "none";
            file << "        ";
            file << "0";
            file << "\n";
        }
        file << "\n";
        

    } else {
        // file opening error
        file.close();
        return -1;
    }



    // all good, return 0
    file.close();
    return 0;
}








// check whether producer is in system and get their info
// use stmt #1
string checkProducerID(Statement** stmts, string accnum, string &farmAddress){
    // use statement #1
    stmts[1]->setString(1, accnum);
    ResultSet *rs = stmts[1]->executeQuery();
    int numberofResults = 0;
    // return variables
    string accnumGet = "ERROR";
    string farmAddressGet = "ERROR";


    // get all results
    while (rs->next()) {
        accnumGet = rs->getString(1);
        farmAddressGet = rs->getString(2);
        numberofResults++;
        
    }

    // close results
    stmts[1]->closeResultSet(rs);

    // if 0 or more than 1 results, return error values
    if (numberofResults != 1){
        farmAddress = "ERROR";
        return "ERROR";
    }

    // everything good, return it
    farmAddress = farmAddressGet;
    return accnumGet;    // there is one result, return it
}






// query producer info and append to outFile
// use stmt #3
int summarizePro(string outFile, Statement** stmts, string accnum, int year, string farmAddress){

    string querydateLower = formatDateYYYYMMDDfromYear(year);    // get string YYYY-MM-DD of Jan 1 from passed year
    string querydateUpper = formatDateYYYYMMDDfromYear(year+1);    // get string YYYY-MM-DD of Jan 1 from passed year
    // return variables
    int numberofResults = 0;
    string productcode = "ERROR";
    string name = "ERROR";
    string unit = "ERROR";
    int total_amount = -1;
    // set bound values
    stmts[3]->setString(1, accnum);
    stmts[3]->setString(2, querydateLower);
    stmts[3]->setString(3, querydateUpper);



    // open file
    std::ofstream file(outFile.c_str(), std::ios::app);  // Append mode


    if (file.is_open()) {   // if file is open

        // print header
        file << "Contribution History of Year ";
        file << year;
        file << "\n";
        file << "Product Code | Food Item | Name | Unit | Total Amount";
        file << "\n";



        // result set
        ResultSet *rs = stmts[3]->executeQuery();


        // get result(s)
        while (rs->next()) {
            
            // get 1 result
            productcode = rs->getString(1);
            name = rs->getString(2);
            unit = rs->getString(3);
            total_amount = rs->getInt(4);
            if (total_amount > 0){  // check the total amount is positive
                // print result
                file << productcode;
                file << "        ";
                file << name;
                file << "        ";
                file << unit;
                file << "        ";
                file << total_amount;
                file << "\n";
            }
            numberofResults++;



        }
        file << "\n";

        // close results and file
        stmts[3]->closeResultSet(rs);

        if (numberofResults == 0){
                // print result
                file << "none";
                file << "        ";
                file << "none";
                file << "        ";
                file << 0;
                file << "        ";
                file << 0;
                file << "\n";
        }
        

    } else {
        // file opening error
        file.close();
        return -1;
    }




    // all good, return 0
    file.close();
    return 0;
}









// print end of file
int endR(string outFile){

    // open in append
    std::ofstream file(outFile.c_str(), std::ios::app);

    if (file.is_open()) {
        file << "====== END OF REPORT ======";
        file << "\n";

        file.close();
        return 0;
    }

    return -1;
}

















// main function
int main()
{
    string userName;
    string password;
    // address of the Oracle server
    const string connectString = "YOUR_DATABASE_ADDRESS_HERE";

    cout << "Your user name: ";
    getline(cin, userName);           

    cout << "Your password: ";
    password = readPassword();        
    cout << endl;


    string outFile = "Report.txt";

    

    // environment, connection, prepared statement strings and their statements
    try {
        // Create an environment object for managing database connections
        Environment *env = Environment::createEnvironment();

        // Create a connection object using the provided username, password, and connection string
        Connection *conn = env->createConnection(userName, password, connectString);
        
        
        // set up all strings, then statements
        int numofStmts = 4;                // the number of prepared statements used by this program. this number used for creating and terminating statements
        string strs[4] = {"ERROR"};        // array for prepared statement strings
        Statement* stmts[4] = {NULL};      // array of statements, 1 for each string

        // check if number is member, get their info
        strs[0] = "SELECT accnum, contactName, deliveryAddress, status FROM MemberAccounts WHERE accnum = :1";
        // check if number is producer, get their info
        strs[1] = "SELECT p.accnum, p.farmAddress FROM Producers p LEFT JOIN MemberAccounts m ON p.accnum = m.accnum AND p.accnum = :1";
        // get member order info
        strs[2] = "SELECT o.packageType, COUNT(o.orderNum) AS type_count ";
        strs[2] += "FROM MemberAccounts m JOIN Orders o ON m.accnum = o.placedBy WHERE m.accnum = :1 ";
        strs[2] += "AND o.placeTime >= TO_DATE(:2, 'YYYY-MM-DD') AND o.placeTime < TO_DATE(:3, 'YYYY-MM-DD') ";
        strs[2] += "GROUP BY o.packageType";
        // get producer supply / food info
        strs[3] = "SELECT ps.productCode, f.name, f.unit, ps.total_amount FROM ( ";
        strs[3] += "SELECT s.productCode, SUM(s.quantity) AS total_amount ";
        strs[3] += "FROM SupplyRecords s JOIN Producers p ON s.accnum = p.accnum WHERE p.accnum = :1";
        strs[3] += "AND s.supplyDate >= TO_DATE(:2, 'YYYY-MM-DD') AND s.supplyDate < TO_DATE(:3, 'YYYY-MM-DD') ";
        strs[3] += "GROUP BY s.productCode ) ps LEFT JOIN FoodItems f ON ps.productCode = f.productCode";



        // Create statements for each string
        // for each string, create a statement out of it, add the pointer of the statement to the array of statements and increment
        for (int q=0; q<numofStmts; q++){
            stmts[q] = conn->createStatement(strs[q]);
        }



        bool keepgoing = true;   // used to make sure previous steps were successful
        bool isproducer = false;    // updated after producer is checked


        // variables to use with checking member and producer info
        int year = -1;
        string accnum = "ERROR";
        string contactName = "ERROR";
        string deliveryAddress = "ERROR";
        string status = "ERROR";
        string farmAddress = "ERROR";
        string input = "ERROR";


        // get year
        cout << "What year for annual report (2020 - 2024)? ";
        cin >> input;
        year = validateStrtoInt(input);
        input = "ERROR";
        if (year == -1){
            keepgoing = false;
            cout << "Invalid year value" << endl;
        } else if ((year < 2020) || (year > 2024)){
            keepgoing = false;
            cout << "Year outside of range (2020-2024)" << endl;
        }
        // year has correct year value




        // ask for member number
        if (keepgoing){
            cout << "What is the member number? ";
            cin >> input;
            accnum = padAccount(input);
            input = "ERROR";
            if (accnum == "ERROR"){
                keepgoing = false;
                cout << "Invalid member number format" << endl;
            }
        }
        // member number is good, havent checked db yet



        // check if member is in system
        if (keepgoing){
            if (checkMemberID(stmts, accnum, contactName, deliveryAddress, status) != accnum){
                keepgoing = false;
                cout << "Member number not in system" << endl;
            }
        }
            // accnum is atleast a member, their info got, start file

        // print header to file, and create file, erasing former content
        if (keepgoing){
            if (beginR(outFile, year, accnum, contactName, deliveryAddress, status) != 0){
                keepgoing= false;
                cout << "Error writing to file" << endl;
            }
        }
        // header printed


        // do member summary
        if (keepgoing){
            if (summarizeMem(outFile, stmts, accnum, year) != 0){
                keepgoing = false;
                cout << "Error writing to file" << endl;
            }
        }


        // do producer check
        if (keepgoing){
            if (checkProducerID(stmts, accnum, farmAddress) != accnum){
                isproducer = false;
            } else {
                isproducer = true;
            }
        }

        // do producer summary
        if ((keepgoing) && (isproducer)){
            if (summarizePro(outFile, stmts, accnum, year, farmAddress) != 0){
                keepgoing = false;
                cout << "Error writng to file" << endl;
            }
        }

        // print end of file
        if (keepgoing){
            if (endR(outFile) != 0){
                keepgoing = false;
                cout << "Error writing to file." << endl;
            }
        }


        // terminate all statements
        for (int i=0; i<numofStmts; i++){
            conn->terminateStatement(stmts[i]);
        }
        
        // Terminates the Connection object 'conn' to close the connection to the database.
        env->terminateConnection(conn);
        // Terminates the Environment object 'env' to release the resources associated with the database environment.
        Environment::terminateEnvironment(env);
    } catch (SQLException & e) {    
        // print any exception caught from the try block
        cout << e.what();
        // return error
        return -1;
    }
    
    // end program
    return 0;
}