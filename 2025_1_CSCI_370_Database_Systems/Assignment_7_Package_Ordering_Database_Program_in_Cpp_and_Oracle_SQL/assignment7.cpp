/**
 * @file assignment7.cpp
 * @author Patrick McGrath, CSCI 370, VIU
 * @version 1.0
 * @date March, 2025
 * 
 *  Assignment #7 Package Ordering Database Program in C++ / Oracle SQL
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
#include <string>
using namespace std;
using namespace oracle::occi;


// commandCodes
// convert user input into command code
// used in user interface while loop. program exits when command is terminate
enum TokenType {
    Invalid = -1,
    Help,
    PlaceOrder,
    Unsubscribe,
    Terminate
 };
 

// read database password from user input
// without showing the password on the screen
string readPassword()
{
    struct termios settings;
    tcgetattr( STDIN_FILENO, &settings );
    settings.c_lflag =  (settings.c_lflag & ~(ECHO));
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );

    string password = "";
    getline(cin, password);

    settings.c_lflag = (settings.c_lflag |   ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );
    return password;
}


// help prompt
void helpprompt(){
    cout << "Commands for database program:" << endl;
    cout << "    p    or    place_order: Place order for account number and package size" << endl;
    cout << "    u    or    unsubscribe: Unsubscribe an account number" << endl;
    cout << "    t    or    terminate: terminate this program" << endl;
    cout << "    h    or    help: to display this help menu" << endl;
    return;
}



// Convert user input command into command code
int checkCommand(string command){
    if (command.size() <= 0){   // no length
        return Invalid;
    } else if ((command[0] == 'p') || (command[0] == 'P')){
        return PlaceOrder;
    } else if ((command[0] == 'u') || (command[0] == 'U')){
        return Unsubscribe;
    } else if ((command[0] == 't') || (command[0] == 'T')){
        return Terminate;
    } else if ((command[0] == 'h') || (command[0] == 'H')){
        return Help;
    } else {
        return Invalid;
    }
    return Invalid;
}


// accnum is CHAR(6), user input account number must have padded 0's if shorter
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



// ordernum is CHAR(5), ordernum must be padded with 0's if shorter
string padOrder(int input){
    string result = "0";    // start with a 0
    int r = input % 10;     // get first remainder
    result[0] = r + 48;     // replace 0
    input = input / 10;     // move decimal place
    while (input > 0){      // while input not depleated
        r = input % 10;     // get remainder
        result += r + 48;   // add it to end
        input = input / 10; // deplete
    }
    int len = result.size();    // length of return
    string turnaround = result; // reverse and return
    for (int i=0; i<len; i++){
        turnaround[i] = result[len-i-1];
    }
    return turnaround;
}




// check input character for correctness, and uppercase it
// if invalid, returns '0'
char checkPackageType(char input){
    switch (input){
        case 's':
        case 'S':
            return 'S';
            break;
        case 'm':
        case 'M':
            return 'M';
            break;
        case 'l':
        case 'L':
            return 'L';
            break;
        default:
            return '0';
            break;
    }
    return '0';
}




// convert char to string
string ChartoString(char input){
    string result = "0";
    result[0] = input;
    return result;
}




int main(){
    string userName;
    string password;
    // address of the Oracle server
    const string connectString = "YOUR_DATABASE_ADDRESS_HERE";
    string appDate = "2024-04-30";  // YYYY-MM-DD
    int currOrderNum = 60001;

    cout << "Your user name: ";
    getline(cin, userName);

    cout << "Your password: ";
    password = readPassword();
    cout << endl;




    // Write prepared statements for each of the 3 commands. 
    // 1. PlaceOrder
    // Place order needs 2 queries to see if member is valid and order not already set.
    // this can be done in one insert, but if unsuccessful, unknown why
    // make sure accnum is Active
    string PlaceOrderValidMemberStr = "SELECT status FROM MemberAccounts WHERE accnum = :1";
    //string PlaceOrderValidMemberStr = "SELECT status FROM MemberAccounts WHERE status = 'Active' AND accnum = :1";
    // make sure accnum doesnt have an order for date
    string PlaceOrderNoOrderYetStr = "SELECT accnum FROM ";
    PlaceOrderNoOrderYetStr += "MemberAccounts LEFT JOIN Orders ON MemberAccounts.accnum = Orders.placedBy ";
    PlaceOrderNoOrderYetStr += "WHERE accnum = :1 AND placedBy NOT IN ";
    PlaceOrderNoOrderYetStr += "(SELECT placedBy FROM Orders WHERE expectDate = TO_DATE(:2, 'YYYY-MM-DD'))";
    string PlaceOrderStr = "INSERT INTO Orders ";
    PlaceOrderStr += "(ordernum, placedBy, placeTime, packageType, expectDate, deliverTime, receivedBarcode, receivedPNum) ";
    PlaceOrderStr += "VALUES (:1, :2, TRUNC(SYSDATE), :3, TO_DATE(:4, 'YYYY-MM-DD'), NULL, NULL, NULL)";




    // 2. Unsubscribe
    string UnsubscribeStr = "UPDATE MemberAccounts SET status = 'Inactive' WHERE accnum = :1";
    // reuse accountNumber string.


    
    // Parameters for PlaceOrder
    string accountNumber = "0";     // account number of order
    char packageType = '0';         // packagetype of order
    int rowsAffected = -1;          // the amount of rows affected by each execution
    int PlaceOrderCount = 0;        // the total number of executions of placeorder. if greater than 0, connection not attempted and disconnection is attempted. and vis versa
    int MemberValidCount = 0;       // total number of executions of checking if member is valid. done by both placeorder and unsubscribe
    string status = "0";            // status for query results
    int UnsubscribeCount = 0;       // total number of executions of unsubscribe. if greater than 0, connection not attempted and disconnection is attempted. and vis versa
    string command = "0";           // user input command
    int commandCode = Invalid;      // code of command
    string CurrOrderStr = "";       // string for converting current number to string for inserting
    string packageTypeStr = "";     // string for converting user input of package type for inserting
    string accountGrab = "";        // number of accounts returned in pre-queries. should be 0 or 1
    
    
    // The 'try' block contains code that might throw an exception.
    // In this case, it includes the code for connecting to the database, creating a statement, executing a query, and processing the results.
    try {
        // Create an environment object for managing database connections
        Environment *env = Environment::createEnvironment();

        // Create a connection object using the provided username, password, and connection string
        Connection *conn = env->createConnection(userName, password, connectString);

        // Pointers for each statement
        // each connects once when first called and disconnected at end only if called at all.
        Statement *PlaceOrderValidMemberStmt;
        Statement *PlaceOrderNoOrderYetStmt;
        Statement *PlaceOrderStmt;
        Statement *UnsubscribeStmt;


        // Prompt list of commands
        helpprompt();


        // Main while loop for repeated commands until terminate selected
        // loop will check previous command
        while (commandCode != Terminate){

            // Ask for command until correct command
            // While incorrect command:
            //      prompt for command, get command, get commandcode of command
            //      if command is help menu, print it, and set command to incorrect
            commandCode = Invalid;
            while (commandCode == Invalid){
                cout << "Please enter a command (or help): ";
                getline(cin, command);
                commandCode = checkCommand(command);
                if (commandCode == Help){
                    helpprompt();
                    commandCode = Invalid;
                }
            }
            // commandCode should = (PlaceOrder || Unsubscribe || Terminate) only


            switch(commandCode){
                case PlaceOrder:
                        // 1. Place order
                        // only connect if not aleady connected
                        if (PlaceOrderCount <= 0){
                            PlaceOrderNoOrderYetStmt = conn->createStatement(PlaceOrderNoOrderYetStr);
                            PlaceOrderStmt = conn->createStatement(PlaceOrderStr);
                        }
                        if (MemberValidCount <= 0){
                            PlaceOrderValidMemberStmt = conn->createStatement(PlaceOrderValidMemberStr);
                        }
                        // increament counts
                        PlaceOrderCount++;
                        MemberValidCount++;

                        // get parameters
                        // asks user for account number, then tries to pad that input to 6 character length
                        // if any characters not numbers, or if too many or no numbers entered, error
                        accountNumber = "ERROR";
                        cout << "Account number: ";
                        getline(cin, accountNumber);
                        accountNumber = padAccount(accountNumber);

                        // check for bad account number
                        if (accountNumber == "ERROR"){
                            cout << "Error: Invalid account number" << endl;
                        } else {
                            // Similar method of getting package size
                            // Except, using temp string for input, incase user uses full word instead of single char
                            packageType = '0';
                            cout << "Package type (S, M, L): ";
                            string tempPackageInput = "0";
                            getline(cin, tempPackageInput);
                            if (tempPackageInput.size() > 0){
                                packageType = checkPackageType(tempPackageInput[0]);
                            } else {
                                packageType = '0';
                            }

                            // Check for bad package type
                            if (packageType == '0'){
                                cout << "Error: Invalid package type" << endl;
                            } else {

                                // check for inactive member, get status if there is one
                                PlaceOrderValidMemberStmt->setString(1, accountNumber);
                                // execute the prepared query statement
                                ResultSet *MemberResult = PlaceOrderValidMemberStmt->executeQuery();                                
                                // grab result
                                status = "0";
                                while (MemberResult->next()) {
                                    status = MemberResult->getString(1);
                                }
                                // close result
                                PlaceOrderValidMemberStmt->closeResultSet(MemberResult);

                                // check result of getting status
                                if (status == "0"){
                                    cout << "Error: account number not in system" << endl;
                                } else if (status == "Inactive"){
                                    cout << "Error: account number Inactive" << endl;
                                } else {
                                    // check for order already set
                                    // set values in statemnt
                                    PlaceOrderNoOrderYetStmt->setString(1, accountNumber);
                                    PlaceOrderNoOrderYetStmt->setString(2, appDate);
                                    // execute
                                    ResultSet *OrderResult = PlaceOrderNoOrderYetStmt->executeQuery();
                                    // get account number
                                    accountGrab = "";
                                    while (OrderResult->next()) {
                                        accountGrab = OrderResult->getString(1);
                                    }
                                    // close result
                                    PlaceOrderNoOrderYetStmt->closeResultSet(OrderResult);

                                    // check returned account number
                                    if (accountGrab == ""){
                                        cout << "Error: account already has an order set for that date" << endl;
                                    } else {

                                        // account number, package type are good. account is active, no order placed for date
                                        // try to insert

                                        // add parameters to statement
                                        CurrOrderStr = padOrder(currOrderNum);
                                        PlaceOrderStmt->setString(1, CurrOrderStr);
                                        PlaceOrderStmt->setString(2, accountNumber);
                                        packageTypeStr = ChartoString(packageType);
                                        PlaceOrderStmt->setString(3, packageTypeStr);
                                        PlaceOrderStmt->setString(4, appDate);
                                        rowsAffected = PlaceOrderStmt->executeUpdate();
                                        // if any rows affected, commit changes. (should be exactly 1)
                                        if (rowsAffected > 0){
                                            conn->commit();
                                            currOrderNum++;     // after commit, increment orderNumber
                                        } else {
                                            cout << "Error: unknown error" << endl;
                                        }
                                    }
                                }
                            }
                        }
                        // reset user input and parameter variables
                        status = "0";
                        accountNumber = "0";
                        packageType = '0';
                        rowsAffected = -1;
                        CurrOrderStr = "";
                        packageTypeStr = "";
                        accountGrab = "";
                        break;
                case Unsubscribe:
                    // unsubscribe
                    // connect if not already
                    if (MemberValidCount <= 0){
                        PlaceOrderValidMemberStmt = conn->createStatement(PlaceOrderValidMemberStr);
                    }
                    if (UnsubscribeCount <= 0){
                        UnsubscribeStmt = conn->createStatement(UnsubscribeStr);
                    }
                    // increament MemberValidCount
                    MemberValidCount++;
                    UnsubscribeCount++;

                    // get parameters
                    // asks user for account number, then tries to pad that input to 6 character length
                    // if any characters not number, error returned
                    accountNumber = "ERROR";
                    cout << "Account number: ";
                    getline(cin, accountNumber);
                    accountNumber = padAccount(accountNumber);
                    // check for bad account number
                    if (accountNumber == "ERROR"){
                        cout << "Error: Invalid account number" << endl;
                    } else {
                        // check for member status and if they are present
                        PlaceOrderValidMemberStmt->setString(1, accountNumber);
                        // execute the prepared query statement
                        ResultSet *MemberResult = PlaceOrderValidMemberStmt->executeQuery();
                        // grab result
                        status = "0";
                        while (MemberResult->next()) {
                            status = MemberResult->getString(1);
                        }
                        // close result
                        PlaceOrderValidMemberStmt->closeResultSet(MemberResult);
                        if (status == "0"){
                            cout << "Error: account number not in system" << endl;
                        } else if (status == "Inactive"){
                            cout << "Error: account number already Inactive" << endl;
                        } else {
                            /*execute the unsubscribe sql*/
                            UnsubscribeStmt->setString(1, accountNumber);
                            rowsAffected = UnsubscribeStmt->executeUpdate();
                            // if any rows affected, commit changes. (should be exactly 1)
                            if (rowsAffected > 0){
                                conn->commit();
                            } else {
                                cout << "Error: unknown error" << endl;
                            }
                        }
                    }
                    // reset user input and parameter variables
                    accountNumber = "0";
                    status = "0";
                    rowsAffected = -1;
                    break;
                case Terminate:
                    // terminate
                    // check which statments are open, close the open ones
                    if (PlaceOrderCount > 0){
                        conn->terminateStatement(PlaceOrderNoOrderYetStmt);
                        conn->terminateStatement(PlaceOrderStmt);
                    }
                    if (MemberValidCount > 0){
                        conn->terminateStatement(PlaceOrderValidMemberStmt);
                    }
                    if (UnsubscribeCount > 0){
                        conn->terminateStatement(UnsubscribeStmt);
                    }
                    break;
                default:
                    break;
                }
            }

            // close connection and environment
            env->terminateConnection(conn);
            Environment::terminateEnvironment(env);

    } catch (SQLException & e) {    
        // Catch errors. occi uses the object type SQLException and any error will create a pointer of this type called e
        // e.what() contains a human-readable version of the error enountered.


        // rints the error message associated with the caught SQLException to the console.
        cout << "Error: exception caught: " << e.what() << endl;;
        cout << "Program terminated unexpectedly" << endl;
        return 0;
    }




    // End
    cout << "Program terminated" << endl;
    return 0;
}