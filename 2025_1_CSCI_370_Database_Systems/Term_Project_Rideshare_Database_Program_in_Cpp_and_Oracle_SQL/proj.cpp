/**
 * @file proj.cpp
 * @author Patrick McGrath, CSCI 370, VIU
 * @version 1.0
 * @date April, 2025
 * 
 *  Term Project: Rideshare Database Program in C++ / Oracle SQL
 *  Copyright (C) 2025 Patrick McGrath
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
using namespace std;
using namespace oracle::occi;

// Command Codes for switching user inter input
enum CommandCode {        // command codes
    Invalid = -1,
    Help,
    AddTrip,
    AddGasPrice,
    FastestTripsandVehicles,
    OverlappingTrips,
    UpdateBalance,
    NegativeBalances,
    Quit
 };




// Declarations

// Convert user input into commande code
int checkCommand(string command);

// Print available user commands
void helpprompt();

// get user input password without displaying characters
string readPassword();

// checks if each char is a number, and that there is 1-6 char's. then pads the front with 0's and returns, else "ERROR"
string padAccount(string input);

// adds trip, manifest, and updates balances. returns 0 on success and -1 on any fail
// has multiple steps, and therefore handles its own commits
int insertTrip(Connection* conn, Statement** stmts); 

// if memberid is in db, it is returned as well as updating fname and lname, else "ERROR"
string checkMemberID(Statement** stmts, string memberID, string &fname, string &lname); 

// check that each char in str is a number. if so, convert the str to an int
int validateStrtoInt(string str);

// inserts vehicleID and startime into trips table to start trip. returns 1 on success and -1 on failure
int tripStartInsert(Statement** stmts, string vehicleID, string startTime);   

// Inserts a single passenger's manifest entry. returns 0 on success, -1 on error
int tripStartInsertManifest(Statement** stmts, string vehicleID, string startTime, string memberID);

// Updates a trip entry at end of trip 
int tripEndTrips(Statement** stmts, string vehicleID, string startTime, int distance, int duration);

// Update member balance to be balance += diff. used at end of trip and to update balances. returns 0 on success, -1 on error
int tripEndBalances(Statement** stmts, string memberID, int diff);

// adds a new gas price after the latest one. returns 0 on success, -1 on error
// does its own commits
int insertGasPrice(Connection* conn, Statement** stmts);

// gets the most recently entered date for gas price. returns date on success, "ERROR" on error
string getGasDate(Statement** stmts);

// helper for interting the gas price. returns 0 on success, -1 on error
int insertGasPricehelp(Statement** stmts, string lastdate, int price);

// get all the pretrip variables for insertTrip
void getpreTrip(Statement** stmts, string memberID, string &vehicleID, string &fname, string &lname, string &make, string &model, int &year, int &conRate); 

// print a pre-trip summary to user
void preTripDone(string startTimeStr, string fname, string lname, string make, string model, int year, string passengerfnames[], string passengerlnames[], int numofPassengers);

// print a post-trip summary to user
void postTripDone(int cost, int conRate, int distance, int duration, int gasPrice, int numofPassengers);

// get the gas price for the day of the start time of a trip. returns 0 on success, -1 on error
int getgasPrice(Statement** stmts, int &gasPrice, string startTimeStr);

// just calls dofastestTrips + dofastestVehicles. returns 0 on success, -1 on error
int doFastestTripsandVehicles(Statement** stmts);

// lists relevant information for the top 3 fastest trips in system. returns 0 on success, -1 on error
int dofastestTrips(Statement** stmts);

// lists relevant information for the top 3 fastest vehicles in system. returns 0 on success, -1 on error
int dofastestVehicles(Statement** stmts);

// Finds all pairs of trips where the vehicleID is the same, and their durations overlap (b.starttime < a.starttime < b.endtime), returns 0 on success, -1 on error
int doOverlappingTrips(Statement** stmts);

// checks that driverID is in system and has a vehicle. returns 0 on success, -1 on error
int checkdriverID(Statement** stmts, string driverID);

// handles topping-up and withdrawing from user accounts
// returns 0 on success, -1 on error
// handles its own commits
int doUpdateBalance(Connection* conn, Statement** stmts);

// gets user's balance info. returns 0 on success, -1 on error
int startUpdateBalance(Statement** stmts, string memberID, string &fname, string &lname, int &balance);




// Functions


// gets list fo all members with a negative balance
int doNegativeBalances(Statement** stmts);
 // Convert user input command into command code
 int checkCommand(string command){
    if (command.size() <= 0){   // no length
        return Invalid;
    } else if ((command[0] == 'q') || (command[0] == 'Q')){
        return Quit;
    } else if ((command[0] == 'h') || (command[0] == 'H')){
        return Help;
    } else if ((command[0] == 'a') || (command[0] == 'A')){
        return AddTrip;
    } else if ((command[0] == 'g') || (command[0] == 'G')){
        return AddGasPrice;
    } else if ((command[0] == 'f') || (command[0] == 'F')){
        return FastestTripsandVehicles;
    } else if ((command[0] == 'o') || (command[0] == 'O')){
        return OverlappingTrips;
    } else if ((command[0] == 'u' || (command[0] == 'U'))){
        return UpdateBalance;
    } else if ((command[0] == 'n') || (command[0] == 'N')){
        return NegativeBalances;
    } else {
        return Invalid;
    }
    return Invalid;
}

// help prompt
void helpprompt(){
    cout << endl;
    cout << "----" << endl;
    cout << "Commands for database program:" << endl;
    cout << "    a    to add trip" << endl;
    cout << "    g    to add a gas price" << endl;
    cout << "    f    to get list of fastest trips and vehicles" << endl;
    cout << "    o    to get a list of overlapping (invalid) trips" << endl;
    cout << "    u    to update a members balance" << endl;
    cout << "    n    to get a list of all members with negative balances" << endl;
    cout << "    h    to display this help menu" << endl;
    cout << "    q    to quit this program" << endl;
    return;
}


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



// memberid and vehicleid is CHAR(6), user input account number must have padded 0's if shorter
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
// return memberID if in system, as well as update fname and lname
string checkMemberID(Statement** stmts, string memberID, string &fname, string &lname){
    // use statement #2
    stmts[2]->setString(1, memberID);
    ResultSet *rs = stmts[2]->executeQuery();
    int numberofResults = 0;
    // return variables
    string resultID = "ERROR";
    string fnameget = "ERROR";
    string lnameget = "ERROR";

    // get all results
    while (rs->next()) {
        numberofResults++;
        resultID = rs->getString(1);
        fnameget = rs->getString(2);
        lnameget = rs->getString(3);
    }

    // close results
    stmts[2]->closeResultSet(rs);

    // if 0 or more than 1 results, return error values
    if (numberofResults != 1){
        fname = "ERROR";
        lname = "ERROR";
        return "ERROR";
    }

    // everything good, return it
    fname = fnameget;
    lname = lnameget;
    return resultID;    // there is one result, return it
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




// get all pretrip variables for insert trip
void getpreTrip(Statement** stmts, string memberID, string &vehicleID, string &fname, string &lname, string &make, string &model, int &year, int &conRate){
    // pass a memberID that has already been verified and checked in 
    stmts[14]->setString(1, memberID);
    ResultSet *rs = stmts[14]->executeQuery();
    int numberofResults = 0;

    // return variables
    string vehicleIDreturn = "ERROR";
    string fnamereturn = "ERROR";
    string lnamereturn = "ERROR";
    string makereturn = "ERROR";
    string modelreturn = "ERROR";
    int yearreturn = -1;
    int conRatereturn = -1;

    // get results
    while (rs->next()) {
        numberofResults++;
        fnamereturn = rs->getString(1);
        lnamereturn = rs->getString(2);
        makereturn = rs->getString(3);
        modelreturn = rs->getString(4);
        yearreturn = rs->getInt(5);
        conRatereturn = rs->getInt(6);
        vehicleIDreturn = rs->getString(7);
    }

    // close result set
    stmts[14]->closeResultSet(rs);

    // if 0 or more than 1 result, return errors
    if (numberofResults != 1){
        fname = "ERROR";
        lname = "ERROR";
        make = "ERROR";
        model = "ERROR";
        year = -1;
        conRate = -1;
        vehicleID = "ERROR";
        return;
    }



    // everything good, return
    fname = fnamereturn;
    lname = lnamereturn;
    make = makereturn;
    model = modelreturn;
    year = yearreturn;
    conRate = conRatereturn;
    vehicleID = vehicleIDreturn;
    return;
}



// does start of trip insert for trips table.
// inserts vehicleID and startTime
// returns 1 on success and -1 on failure
int tripStartInsert(Statement** stmts, string vehicleID, string startTime){
    stmts[4]->setString(1, vehicleID);
    stmts[4]->setString(2, startTime);
    int rowsAffected = -1;
    rowsAffected = stmts[4]->executeUpdate();
    if (rowsAffected != 1){
        return -1;
    }


    // 1 row affected
    return 1;
}


// does start of trip insert for manifests table for single passenger
// inserts vehicleID, passengerID and startTime
// returns 1 on success and -1 on failure
int tripStartInsertManifest(Statement** stmts, string vehicleID, string startTime, string memberID){
    stmts[5]->setString(1, vehicleID);
    stmts[5]->setString(2, startTime);
    stmts[5]->setString(3, memberID);
    int rowsAffected = -1;
    rowsAffected = stmts[5]->executeUpdate();
    if (rowsAffected != 1){
        return -1;
    }

    // 1 row affected
    return 1;
}






//does end of trip update for trips table
// updates the trip entry for vehicleID+startTime with distance and endTime = startTime + duration
// returns 1 on success and -1 on failure
int tripEndTrips(Statement** stmts, string vehicleID, string startTime, int distance, int duration){
    stmts[6]->setInt(1, distance);
    stmts[6]->setInt(2, duration);
    stmts[6]->setString(3, vehicleID);
    stmts[6]->setString(4, startTime);
    int rowsAffected = -1;
    rowsAffected = stmts[6]->executeUpdate();
    if (rowsAffected != 1){
        return -1;
    }

    // 1 row affected
    return 1;
}






// updates memberID's balance
// balance += diff
// if subtracting, pass a negative diff, else positive
// returns 1 on success and -1 on failure
int tripEndBalances(Statement** stmts, string memberID, int diff){
    stmts[12]->setInt(1, diff);
    stmts[12]->setString(2, memberID);
    int rowsAffected = -1;
    rowsAffected = stmts[12]->executeUpdate();
    if (rowsAffected != 1){
        return -1;
    }

    // 1 row affected
    return 1;
}





// Print a pre-trip summary to user
void preTripDone(string startTimeStr, string fname, string lname, string make, string model, int year, string passengerfnames[], string passengerlnames[], int numofPassengers){
    cout << "----" << endl;
    cout << "Trip started at " << startTimeStr << endl;
    cout << "    Driver: " << fname << " " << lname << endl;
    cout << "    Vehicle: " << year << " " << make << " " << model << "." << endl;
    cout << "    Passengers: " << endl;
    for (int i=0; i<numofPassengers; i++){
        cout << "        #" << i+1 << ": " << passengerfnames[i] << " " << passengerlnames[i] << endl;
    }

    return;
}



// gets price of gas for the day that startTimeStr has. 
// returns 1 on success and -1 on failure
int getgasPrice(Statement** stmts, int &gasPrice, string startTimeStr){
    string justday = startTimeStr;
    justday[10] = '\0'; // null terminate to get ride of time portion
    stmts[10]->setString(1, justday);
    ResultSet *rs = stmts[10]->executeQuery();
    int numberofResults = 0;
    int gasPriceget = -1;
    while (rs->next()) {
        numberofResults++;
        gasPriceget = rs->getInt(1);
    }
    stmts[10]->closeResultSet(rs);
    if (numberofResults != 1){
        return -1;
    }

    // 1 result
    gasPrice = gasPriceget;
    return 1;
}




// checks that a passed driverID is a member with vehicle in system
// returns 0 on success and -1 on failure
int checkdriverID(Statement** stmts, string driverID){
    stmts[9]->setString(1, driverID);
    ResultSet *rs = stmts[9]->executeQuery();
    int numberofResults = 0;
    string driverIDreturn = "ERROR";
    while (rs->next()){
        numberofResults++;
        driverIDreturn = rs->getString(1);
    }
    stmts[9]->closeResultSet(rs);
    if (numberofResults != 1){
        return -1;
    }

    // only one result
    return 0;
}




// adds trip, manifest, and updates balances. returns 0 on success and -1 on any fail
// simulates driver entering their ID, number of passengers, their ID's, length and duration of trip.
// Trip is started using system time
// asks user for info at each step.
// has multiple steps, and therefore handles its own commits
int insertTrip(Connection* conn, Statement** stmts){
    // variables
    string input = "ERROR";             // string for getting user input
    string driverID = "ERROR";          // memberID of driver
    string vehicleID = "ERROR";         // vehicleID of vehicle
    string fname = "ERROR";
    string lname = "ERROR";
    string make = "ERROR";
    string model = "ERROR";
    int year = -1;
    int conRate = -1;                   // gas consumption rate in L/100km
    int numofPassengers = -1;           // number of passengers
    string passengerIDs[6] = {"ERROR"}; // array of passenger memberIDs. max of 6
    string passengerfnames [6] = {"ERROR"};
    string passengerlnames[6] = {"ERROR"};
    time_t startTimestamp = time(NULL); // startTime timestamp
    struct tm startDateTime;            // struct for startTime
    char startTime[20];                 // char array for startTime in prepared statement
    string startTimeStr;                // string for converting char array to actually put in prepared statement
    string startDay = "ERROR";          // string for day for getting gas price
    int distance = -1;                  // distance of trip in 100m's
    int duration = -1;                  // duration of trip in minutes
    int gasPrice = -1;                  // price of gas in cents/L
    int cost = -1;                      // cost of the trip in cents
    int passcost = -1;


    // Prompt that start of trip has been initiated
    cout << "----" << endl;
    cout << "    New trip started. Pre-trip info needed." << endl;
    cout << "    What is your (driver) ID? ";
    cin >> input;
    driverID = padAccount(input);        // validate and pad input characters
    if (driverID == "ERROR"){
        cout << "Invalid member ID format." << endl;
        return -1;  // error
    }
    input = "ERROR";
    // entered id is in correct format, but need to check system

    // check memberID is of a driver
    if (checkdriverID(stmts, driverID) == -1){
        cout << "Error, not a driver's ID" << endl;
        return -1;
    }

    // get all driver / vehicle variables
    getpreTrip(stmts, driverID, vehicleID, fname, lname, make, model, year, conRate); // get all the pretrip variables
    if (driverID == "ERROR"){
        cout << "Error getting pretrip info from database." << endl;
        return -1;
    }



    // ask for number of passengers
    cout << "    How many passengers (1-6)? ";
    cin >> input;
    numofPassengers = validateStrtoInt(input);
    if (numofPassengers < 0){
        cout << "Not a number." << endl;
        return -1;
    }
    if (numofPassengers == 0){
        cout << "Must be at least one passeneger (1-6)." << endl;
        return -1;
    }
    if (numofPassengers > 6){
        cout << "Too many passengers (1-6)." << endl;
        return -1;
    }
    input = "ERROR";
    // number of passengers got

    // passenger by passenger,
    // ask for passengerID, check its format, check its in db
    for (int j=0; j<numofPassengers; j++){
        // get passenger id
        cout << "    What is the member ID of the " << j+1;
        switch (j){
            case 0: cout << "st";
                    break;
            case 1: cout << "nd";
                    break;
            case 2: cout << "rd";
                    break;
            case 3: cout << "th";
                    break;
            case 4: cout << "th";
                    break;
            case 5: cout << "th";
                    break;
            default:
                    break;
        }
        cout << " passenger? ";
        cin >> input;

        // validate it
        passengerIDs[j] = padAccount(input);
        if (passengerIDs[j] == "ERROR"){
            cout << "Invalid member ID format." << endl;
            return -1;  // error
        }
        // entered id is in correct format, but need to check system

        // check passenger is in system
        if (checkMemberID(stmts, passengerIDs[j], passengerfnames[j], passengerlnames[j]) != passengerIDs[j]){
            cout << "Invalid member ID, not in system." << endl;
            return -1;  // error
        }

        input = "ERROR";
    }
    // all passenger member IDs got a validated


    // get time and do pre-trip inserts
    startDateTime = *localtime(&startTimestamp);  // get current system time
    strftime(startTime, 20, "%Y-%m-%d %H:%M:%S", &startDateTime); // convert time to oracle format
    startTimeStr = std::string(startTime);      // comvert char arr[20] to string
    // current date and time got



    // get today's gas price
    if (getgasPrice(stmts, gasPrice, startTimeStr) == -1){
        cout << "Error getting today's gas price." << endl;
        return -1;
    }

    
    // pre-trip insertions
    // trips, just 1
    if (tripStartInsert(stmts, vehicleID, startTimeStr) != 1){
        cout << "Error inserting start of trip." << endl;
        return -1;
    } else {
        // 1 trip inserted, commit it
        conn->commit();
    }
    // manifests, 1 per passenger
    for (int k=0; k<numofPassengers; k++){
        if (tripStartInsertManifest(stmts, vehicleID, startTimeStr, passengerIDs[k]) != 1){
            cout << "Error inserting manifest." << endl;
            return -1;
        }
        // 1 manifest inserted
        conn->commit();
    }

    //pre trip finished

    
    preTripDone(startTimeStr, fname, lname, make, model, year, passengerfnames, passengerlnames, numofPassengers);
    // upate earlier memberID get query to get memberID and first, last names
    // update earlier vehicleID get query to get vehicleID and make, model
    // print all relavent info here as a pretrip message
    // update later balance update to not need to get balance, just update it
    input = "ERROR";
    while (input == "ERROR"){
        cout << "Enter anything to end trip. ";
        cin >> input;
    }
    input = "ERROR";
    bool goodInput = false;
    while (!goodInput){
        cout << "    Trip ended. How long was trip in minutes (may be more than 60)? ";
        cin >> input;
        duration = validateStrtoInt(input);
        
        if (duration < 0){
            cout << "Not a number." << endl;
        } else if (duration == 0){
            cout << "Must be more than zero." << endl;
        } else {
            goodInput = true;
        }
        input = "ERROR";
    }
    
    // duration got and postitive
    goodInput = false;
    input = "ERROR";
    while (!goodInput){
        cout << "    What was the distance in 100m's (must be less than 1M km)? ";
        cin >> input;
        distance = validateStrtoInt(input);
        if (distance < 0){
            cout << "Not a number." << endl;
        } else if (distance == 0){
            cout << "Must be more than zero." << endl;
        } else {
            goodInput = true;
        }
        input = "ERROR";
    }
    // distance got and postitive
    

    // do post-trip updates
    // trip
    if (tripEndTrips(stmts, vehicleID, startTimeStr, distance, duration) == -1){
        cout << "Error updating trips." << endl;
        return -1;
    } else {
        conn->commit();
    }

    // balances
    cost = (distance * conRate * gasPrice)/1000;
    // update driver
      if (tripEndBalances(stmts, driverID, cost) == -1){
        cout << "Error updating driver's balance" << endl;
        return -1;
    } else {
        conn->commit();
    }
    // update all passenger balances
    passcost = -(cost/numofPassengers);
    for (int y=0; y<numofPassengers; y++){
        if (tripEndBalances(stmts, passengerIDs[y], passcost) == -1){
            cout << "Error updating passenger's balance" << endl;
            return -1;
        } else {
            conn->commit();
        }

    }

    // print a post trip summary
    postTripDone(cost, conRate, distance, duration, gasPrice, numofPassengers);




    // all done
    return 0;
}




// gets the most recently entered gas price date.
// returns date on success or "ERROR" on error
string getGasDate(Statement** stmts){
    ResultSet *rs = stmts[0]->executeQuery();
    int numberofResults = 0;
    string dateGet = "ERROR";
    while (rs->next()) {
        numberofResults++;
        dateGet = rs->getString(1);
    }
    stmts[0]->closeResultSet(rs);
    if (numberofResults != 1){
        return "ERROR";
    }

    // 1 result
    return dateGet;
}


// helper for interting the gas price. returns 0 on success, -1 on error
// takes the most recently added date as a parameter. updates the day after that
int insertGasPricehelp(Statement** stmts, string lastdate, int price){
    stmts[1]->setString(1, lastdate);
    stmts[1]->setInt(2, price);
    int rowsAffected = -1;
    rowsAffected = stmts[1]->executeUpdate();
    if (rowsAffected != 1){
        return -1;
    }

    // 1 row affected
    return 1;

}




// function for handling adding gas prices
// assumes no gaps in history of gas prices
// rest of system assumes the gas prices for the day the program is being used is already entered
// therefore, gasprice for each day must be set no later than the day before 
int insertGasPrice(Connection* conn, Statement** stmts){
    // variables
    string lastDate = "ERROR";
    string priceStr = "ERROR";
    int price = -1;
    // get the date of the most recently updated gasprice
    cout << "----" << endl;
    lastDate = getGasDate(stmts);
    if (lastDate == "ERROR"){
        cout << "Error getting date of gas price" << endl;
        return -1;
    }
    // max date got

    // tell user
    cout << "Enter a new gas price" << endl;
    cout << "    Most recent gas price entered was for date: " << lastDate << endl;
    cout << "    What is the gas price for the following day (in cents/L)? ";
    cin >> priceStr;
    price = validateStrtoInt(priceStr);
    if (price == -1){
        cout << "Not a number" << endl;
        return -1;
    } else if (price == 0){
        cout << "    Gas is free today." << endl;
    }
    // price good too

    // do insert
    if (insertGasPricehelp(stmts, lastDate, price) == -1){
        cout << "Error trying to add gas price." << endl;
        return -1;
    } else {
        // 1 price inserted
        conn->commit();
    }

    // everything good
    return 0;
}








// Print a post-trip summary to user
void postTripDone(int cost, int conRate, int distance, int duration, int gasPrice, int numofPassengers){
    cout << "----" << endl;
    cout << "Trip concluded." << endl;
    float km = distance;
    km = km/10;
    float hours = duration;
    hours = hours/60;
    float litres = conRate * distance;
    litres = litres/1000;
    float dollars = cost;
    dollars = dollars/100;
    float gasfl = gasPrice;
    gasfl = gasfl / 100;
    if (hours >= 1){
        cout << "    Duration: " << hours << " hours" << endl;
    } else {
        cout << "    Duration: " << duration << " minutes" << endl;
    }
    cout << fixed << setprecision(2);  // Set precision to 2 decimal places
    cout << "    Distance: " << km << " km" << endl;
    cout << "    Avg speed: " << km/hours << " km/h" << endl;
    cout << "    Fuel consumed: " << litres << "L" << endl;
    cout << "    Cost of fuel: " << gasfl << "$/L" << endl;
    cout << "    Cost: $" << dollars << " (total), $" << dollars/numofPassengers << " (per pass.)" << endl;
    cout << "    Cost per distance: " << dollars/km << " $/km" << endl;
    cout << "    Cost per time: " << dollars/hours << " $/hr" << endl;
    cout << "    Done." << endl;
    cout.unsetf(ios::fixed | ios::scientific);  // Reset formatting
    cout << setprecision(6);  // Restore default precision
    return;
}




// lists relevant information for the top 3 fastest trips in system. returns 0 on success, -1 on error
int dofastestTrips(Statement** stmts){
    ResultSet *rs = stmts[3]->executeQuery();
    int numberofResults = 0;

    // variables
    float speed[3] = {-1};          // km/h
    int distance[3] = {-1};         // 100m's
    float dist[3] = {-1};           // km's
    float diff[3] = {-1};           // hr's
    string fname[3] = {"ERROR"};
    string lname[3] = {"ERROR"};
    string make[3] = {"ERROR"};
    string model[3] = {"ERROR"};
    string startTime[3] = {"ERROR"};
    string endTime[3] = {"ERROR"};
    int year[3] = {-1};
    while ((rs->next()) && (numberofResults < 3)){
        speed[numberofResults] = rs->getFloat(1);
        distance[numberofResults] = rs->getInt(2);
        dist[numberofResults] = distance[numberofResults]/10;
        diff[numberofResults] = rs->getFloat(3);
        fname[numberofResults] = rs->getString(4);
        lname[numberofResults] = rs->getString(5);
        make[numberofResults] = rs->getString(6);
        model[numberofResults] = rs->getString(7);
        year[numberofResults] = rs->getInt(8);
        startTime[numberofResults] = rs->getString(9);
        endTime[numberofResults] = rs->getString(10);
        numberofResults++;
    }
    stmts[3]->closeResultSet(rs);
    if (numberofResults == 0){
        cout << "No results" << endl;
        return -1;
    }

    if (numberofResults == -1){
        cout << "Error getting fastest trips results" << endl;
        return -1;
    }
    cout << fixed << setprecision(2);  // Set precision to 2 decimal places
    cout << "----" << endl;
    cout << "Fastest Trips:" << endl;
    for (int i=0; i<numberofResults; i++){
        cout << "    #" << i+1 << ": ";
        cout << fname[i] << " " << lname[i] << "'s " << year[i] << " " << make[i] << " " << model[i] << endl;
        cout << "        From " << startTime[i] << " to " << endTime[i] << endl;
        cout << "        Distance / Time = " << dist[i] << "km / " << diff[i] << "hrs = " << speed[i] << "km/h" << endl;
    }
    cout.unsetf(ios::fixed | ios::scientific);  // Reset formatting
    cout << setprecision(6);  // Restore default precision

    return 0;
}



// lists relevant information for the top 3 fastest vehicles in system. returns 0 on success, -1 on error
int dofastestVehicles(Statement** stmts){
    ResultSet *rs = stmts[7]->executeQuery();
    int numberofResults = 0;

    // variables
    float speed[3] = {-1};          // km/h
    float diff[3] = {-1};           // hr's
    int distance[3] = {-1};         // 100m's
    float dist[3] = {-1};           // km's
    string fname[3] = {"ERROR"};
    string lname[3] =  {"ERROR"};
    string make[3] = {"ERROR"};
    string model[3] = {"ERROR"};
    int year[3] = {-1};

    while ((rs->next()) && (numberofResults < 3)){
        speed[numberofResults] = rs->getFloat(1);
        diff[numberofResults] = rs->getFloat(2);
        distance[numberofResults] = rs->getInt(3);
        dist[numberofResults] = distance[numberofResults]/10;
        fname[numberofResults] = rs->getString(4);
        lname[numberofResults] = rs->getString(5);
        make[numberofResults] = rs->getString(6);
        model[numberofResults] = rs->getString(7);
        year[numberofResults] = rs->getInt(8);
        numberofResults++;
    }
    stmts[7]->closeResultSet(rs);
    if (numberofResults == 0){
        cout << "No results" << endl;
        return -1;
    }

    if (numberofResults == -1){
        cout << "Error getting fastest vehicle results" << endl;
        return -1;
    }

    cout << fixed << setprecision(2);  // Set precision to 2 decimal places
    cout << "----" << endl;
    cout << "Fastest vehicles:" << endl;
    for (int i=0; i<numberofResults; i++){
        cout << "    #" << i+1 << ": ";
        cout << fname[i] << " " << lname[i] << "'s " << year[i] << " " << make[i] << " " << model[i] << endl;
        cout << "        Distance / Time = " << dist[i] << "km / " << diff[i] << "hrs = " << speed[i] << "km/h" << endl;       
    }
    cout.unsetf(ios::fixed | ios::scientific);  // Reset formatting
    cout << setprecision(6);  // Restore default precision

    return 0;
}




// Just calls dofastestTrips and dofastestVehicles
// returns 0 on success, else if either fails, -1 is returned
int doFastestTripsandVehicles(Statement** stmts){
    if (dofastestTrips(stmts) == -1){
        cout << "Error getting fastest trips info" << endl;
        return -1;
    }

    if (dofastestVehicles(stmts) == -1){
        cout << "Error getting fastest vehicles info" << endl;
        return -1;
    }

    return 0;
}






// Finds all pairs of trips where the vehicleID is the same, and their durations overlap (b.starttime < a.starttime < b.endtime), returns 0 on success, -1 on error
// prints information about the driver, vehicle and both trips
int doOverlappingTrips(Statement** stmts){
    ResultSet *rs = stmts[8]->executeQuery();
    int numberofResults = 0;

    // variables
    // maximum 20 pairs
    string vehicleID[20] = {"ERROR"};
    string startTimeA[20] = {"ERROR"};
    string endTimeA[20] = {"ERROR"};
    string startTimeB[20] = {"ERROR"};
    string endTimeB[20] = {"ERROR"};
    string fname[20] = {"ERROR"};
    string lname[20] = {"ERROR"};
    string email[20] = {"ERROR"};
    int year[20] = {-1};
    string make[20] = {"ERROR"};
    string model[20] = {"ERROR"};


    while ((rs->next()) && (numberofResults < 20)){
        vehicleID[numberofResults] = rs->getString(1);
        startTimeA[numberofResults] = rs->getString(2);
        endTimeA[numberofResults] = rs->getString(3);
        startTimeB[numberofResults] = rs->getString(4);
        endTimeB[numberofResults] = rs->getString(5);
        fname[numberofResults] = rs->getString(6);
        lname[numberofResults] = rs->getString(7);
        email[numberofResults] = rs->getString(8);
        year[numberofResults] = rs->getInt(9);
        make[numberofResults] = rs->getString(10);
        model[numberofResults] = rs->getString(11);
        numberofResults++;
    }
    stmts[8]->closeResultSet(rs);
    if (numberofResults == 0){
        cout << "No results" << endl;
        return -1;
    }

    if (numberofResults == -1){
        cout << "Error getting overlapping trips results" << endl;
        return -1;
    }

    if (numberofResults >= 20){
        cout << "Maximum number of pairs (20) reached. May be more pairs." << endl;
    }

    cout << "----" << endl;
    cout << "Overlapping trip pairs: " << endl;
    for (int i=0; i<numberofResults; i++){
        cout << "    #" << i+1 << ": ";
        cout << fname[i] << " " << lname[i] << "'s " << year[i] << " " << make[i] << " " << model[i] << endl;
        cout << "        Trip A: " << startTimeA[i] << " - " << endTimeA[i] << endl;
        cout << "        Trip B: " << startTimeB[i] << " - " << endTimeB[i] << endl;
        cout << "        email driver at " << email[i] << endl;
    }


    return -1;
}




// gets member's name and balance. used before and after updating balance
// returns -1 on error, and 0 on success
int startUpdateBalance(Statement** stmts, string memberID, string &fname, string &lname, int &balance){

    // variables
    string fnamereturn = "ERROR";
    string lnamereturn = "ERROR";
    int balancereturn = -1;
    int numberofResults = 0;
    stmts[13]->setString(1, memberID);
    ResultSet *rs = stmts[13]->executeQuery();
    while (rs->next()){
        fnamereturn = rs->getString(1);
        lnamereturn = rs->getString(2);
        balancereturn = rs->getInt(3);
        numberofResults++;
    }
    stmts[13]->closeResultSet(rs);
    if (numberofResults != 1){
        fname = "ERROR";
        lname = "ERROR";
        balance = -1;
        return -1;
    }

    fname = fnamereturn;
    lname = lnamereturn;
    balance = balancereturn;
    return 0;
}








// handles topping-up and withdrawing from user accounts
// returns 0 on success, -1 on error
// handles its own commits
int doUpdateBalance(Connection* conn, Statement** stmts){

    // variables
    string memberID = "ERROR";
    string fname = "ERROR";
    string lname = "ERROR";
    int balance = -1;               // cents
    float balancefl = -1;           // $'s
    string input = "ERROR";
    string inputamount = "ERROR";
    int amount = -1;                // the amount to increase balance by

    // get memberID
    cout << "----" << endl;
    cout << "Updating member balance" << endl;
    cout << "What is the memberID? ";
    cin >> memberID;
    memberID = padAccount(memberID);
    if (memberID == "ERROR"){
        cout << "Error, not a member ID" << endl;
        return -1;
    }
    // memberid correct format
    if (checkMemberID(stmts, memberID, fname, lname) != memberID){
        cout << "Error, memberID not in system" << endl;
        return -1;
    }
    // get balance and info
    if (startUpdateBalance(stmts, memberID, fname, lname, balance) == -1){
        cout << "Error, memberID not in system" << endl;
        return -1;
    }

    // convert cents to dollars
    balancefl = balance;
    balancefl = balancefl / 100;


    // ask user whether to top-up or withdraw
    cout << "----" << endl;
    cout << fixed << setprecision(2);  // Set precision to 2 decimal places
    cout << fname << " " << lname << "'s balance = $" << balancefl << endl;
    cout.unsetf(ios::fixed | ios::scientific);  // Reset formatting
    cout << setprecision(6);  // Restore default precision
    while (input == "ERROR"){
        cout << "Choose an option:" << endl;
        cout << "    t    to topup balance" << endl;
        cout << "    w    to withdraw from balance? ";
        cin >> input;
        if (input.size() < 1){
            input = "ERROR";
        } else {
            if ((input[0] != 't') && (input[0] != 'T') && (input[0] != 'w') && (input[0] != 'W')){
                input = "ERROR";
            }
        }
    }

    // selection chosen
    // input[0] = t/T or w/W
    if ((input[0] == 't') || (input[0] == 'T')){
        // top-up
        cout << "How much to top-up by in cents? ";
    } else {
        // withdraw
        cout << "How much to withdraw in cents? ";
    }

    cin >> inputamount;
    amount = validateStrtoInt(inputamount);
    if (amount == -1){
        cout << "Error, not a number" << endl;
        return -1;
    }

    // update balance
    if ((input[0] == 't') || (input[0] == 'T')){
        // deposit
        if (tripEndBalances(stmts, memberID, amount) == -1){
            cout << "Error updating balance" << endl;
            return -1;
        } else {
            conn->commit();
        }
    } else {
        // withdraw
        if (amount > balance){
            cout << "Error, cannot withdraw more than balance" << endl;
            return -1;
        } else {
            if (tripEndBalances(stmts, memberID, -amount) == -1){
                cout << "Error updating balance" << endl;
                return -1;
            } else {
                conn->commit();
            }
        }
    }


    // re print balance info to show change
    if (startUpdateBalance(stmts, memberID, fname, lname, balance) == -1){
        cout << "Error, memberID not in system" << endl;
    }
    // convert cents to dollars
    balancefl = balance;
    balancefl = balancefl / 100;
    cout << "----" << endl;
    cout << "Balance update complete" << endl;
    cout << fixed << setprecision(2);  // Set precision to 2 decimal places
    cout << fname << " " << lname << "'s balance = $" << balancefl << endl;
    cout.unsetf(ios::fixed | ios::scientific);  // Reset formatting
    cout << setprecision(6);  // Restore default precision
    cout << "Done" << endl;

    // done
    return 0;
}




int doNegativeBalances(Statement** stmts){



    //strs[11] = "SELECT memberID, fname, lname, balance, email FROM Members WHERE balance < 0";  

    string memberID = "ERROR";
    string fname = "ERROR";
    string lname = "ERROR";
    int balance = -1;
    float balancefl = -1;
    int numberofResults = 0;
    ResultSet *rs = stmts[11]->executeQuery();
    while (rs->next()){
        memberID = rs->getString(1);
        fname = rs->getString(2);
        lname = rs->getString(3);
        balance = rs->getInt(4);
        balancefl = balance;
        balancefl = balancefl / 100;
        numberofResults++;
        cout << fname << " " << lname << "'s balance = $" << balancefl << endl;
    }
    stmts[11]->closeResultSet(rs);
    cout << numberofResults << " members have negative balances" << endl;

    
    return 0;
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

    

    // environment, connection, prepared statement strings and their statements
    try {
        // Create an environment object for managing database connections
        Environment *env = Environment::createEnvironment();

        // Create a connection object using the provided username, password, and connection string
        Connection *conn = env->createConnection(userName, password, connectString);
        
        
        // set up all strings, then statements
        int numofStmts = 15;                // the number of prepared statements used by this program. this number used for creating and terminating statements
        string strs[15] = {"ERROR"};        // array for prepared statement strings
        Statement* stmts[15] = {NULL};      // array of statements, 1 for each string

        // get day of most recent gas price entry
        strs[0] = "SELECT TO_CHAR(MAX(day), 'YYYY-MM-DD') FROM GasPrices";
        // insert a gas price for a 1 day past the passed date
        strs[1] = "INSERT INTO GasPrices (day, price) VALUES (TO_DATE(:1, 'YYYY-MM-DD HH24:MI:SS') + 1, :2)";
        // validate / retrieve user-passed member ID by checking if it is in database, used for both driver and passengers
        strs[2] = "SELECT memberID, fname, lname FROM Members WHERE memberID = :1";
        // get information for finding fastest trips
        strs[3] = "SELECT ((s.distance / s.diff) / 10) AS speed, s.distance, s.diff, m.fname, m.lname, s.make, s.model, s.year, ";
        strs[3] += "TO_CHAR(s.startTime, 'YYYY-MM-DD HH24:MI:SS'), TO_CHAR(s.endTime, 'YYYY-MM-DD HH24:MI:SS') ";
        strs[3] += "FROM (SELECT t.vehicleID, t.distance, v.ownerID, v.make, v.model, v.year, ((t.endTime - t.startTime) * 24) AS diff, t.startTime, t.endTime ";
        strs[3] += "FROM Trips t JOIN Vehicles v ON t.vehicleID = v.vehicleID) s ";
        strs[3] += "JOIN Members m ON s.ownerID = m.memberID ORDER BY speed DESC";
        // start of trip, insert into Trips, vehicleID and startTime
        strs[4] = "INSERT INTO Trips (vehicleID, startTime) VALUES (:1, ";
        strs[4] += "TO_DATE(:2, 'YYYY-MM-DD HH24:MI:SS'))";
        // start of trip, insert into manifests for each passenger, vehicleID, startTime, passengerID
        strs[5] = "INSERT INTO Manifests (vehicleID, startTime, passengerID) ";
        strs[5] += "VALUES (:1, TO_DATE(:2, 'YYYY-MM-DD HH24:MI:SS'), :3)";
        // end of trip, update trips for endtime (= startTime + x minutes) and distance
        strs[6] = "UPDATE Trips SET distance = :1, endTime = startTime + (:2 / (24 * 60)) WHERE ";
        strs[6] += "vehicleID = :3 AND startTime = TO_DATE(:4, 'YYYY-MM-DD HH24:MI:SS')";
        // get informtion for finding fastest vehicles
        strs[7] = "SELECT ((ts.dist / ts.diff) / 10) AS speed, ts.diff AS total_time, ts.dist AS total_distance, m.fname, m.lname, v.make, v.model, v.year ";
        strs[7] += "FROM (SELECT t.vehicleID, SUM(t.distance) AS dist, (SUM((t.endTime - t.startTime) * 24)) AS diff ";
        strs[7] += "FROM Trips t GROUP BY t.vehicleID) ts JOIN Vehicles v ON ts.vehicleID = v.vehicleID ";
        strs[7] += "JOIN Members m ON v.ownerID = m.memberID ORDER BY speed DESC";
        // get information on overlapping trips by the same vehicle
        strs[8] = "SELECT vm.vehicleID, TO_CHAR(t1.startTime, 'YYYY-MM-DD HH24:MI:SS') AS trip1_start, TO_CHAR(t1.endTime, 'YYYY-MM-DD HH24:MI:SS') AS trip1_end, ";
        strs[8] += "TO_CHAR(t2.startTime, 'YYYY-MM-DD HH24:MI:SS') AS trip2_start, TO_CHAR(t2.endTime, 'YYYY-MM-DD HH24:MI:SS') AS trip2_end, ";
        strs[8] += "vm.fname, vm.lname, vm.email, vm.year, vm.make, vm.model ";
        strs[8] += "FROM (SELECT v.vehicleID, m.memberID, m.fname, m.lname, m.email, v.year, v.make, v.model ";
        strs[8] += "FROM Vehicles v LEFT JOIN Members m ON v.ownerID = m.memberID) vm ";
        strs[8] += "JOIN Trips t1 ON vm.vehicleID = t1.vehicleID JOIN Trips t2 ON t1.vehicleID = t2.vehicleID ";
        strs[8] += "WHERE t1.startTime <> t2.startTime AND (t1.startTime > t2.startTime AND t1.startTime < t2.endTime)";
        // check that memberID is a valid driver
        strs[9] = "SELECT v.ownerID FROM Vehicles v LEFT JOIN Members m ON v.ownerID = m.memberID WHERE m.memberID = :1";
        // get price of gas for passed date
        strs[10] = "SELECT price FROM GasPrices WHERE day = TO_DATE(:1, 'YYYY-MM-DD')";
        // get balance of all members with negative balances
        strs[11] = "SELECT memberID, fname, lname, balance, email FROM Members WHERE balance < 0";  
        // update member's balance to be balance += difference
        strs[12] = "UPDATE Members SET balance = balance + :1 WHERE memberID = :2";
        // get member's information and balance for memberID
        strs[13] = "SELECT fname, lname, balance FROM Members WHERE memberID = :1";
        // get pretrip information
        strs[14] = "SELECT M.fname, M.lname, V.make, V.model, V.year, V.consumeRate, V.vehicleID ";
        strs[14] += "FROM Members M RIGHT JOIN Vehicles V ON M.memberID = V.ownerID WHERE M.memberID = :1";


        // Create statements for each string
        // for each string, create a statement out of it, add the pointer of the statement to the array of statements and increment
        for (int q=0; q<numofStmts; q++){
            stmts[q] = conn->createStatement(strs[q]);
        }



        // print help
        // set command to invalid
        // while command not terminate
            // prompt for command
            // get command
            // convert command to code to see if invalid
            // if is help, print help, set it to invalid

        // Prompt list of commands
        helpprompt();

        int commandCode = Invalid;
        string command = "ERROR";
        // Main while loop for repeated commands until terminate selected
        // loop will check previous command
        while (commandCode != Quit){

            // Ask for command until correct command
            // While incorrect command:
            //      prompt for command, get command, get commandcode of command
            //      if command is help menu, print it, and set command to incorrect
            commandCode = Invalid;
            while (commandCode == Invalid){
                cout << "----" << endl;
                cout << "Please enter a command (or help): ";
                cin >> command;
                commandCode = checkCommand(command);
                if (commandCode == Help){
                    helpprompt();
                    commandCode = Invalid;
                }
                command = "ERROR";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear cin buffer
            }
            // commandCode should be valid

            // handle command
        int result = -1;
            switch(commandCode){
                case(AddTrip):
                    result = insertTrip(conn, stmts);
                    result = -1;
                    break;
                case(AddGasPrice):
                    result = insertGasPrice(conn, stmts);
                    result = -1;
                    break;
                case(FastestTripsandVehicles):
                    result = doFastestTripsandVehicles(stmts);
                    result = -1;
                    break;
                case (OverlappingTrips):
                    result = doOverlappingTrips(stmts);
                    result = -1;
                    break;
                case (UpdateBalance):
                    result = doUpdateBalance(conn, stmts);
                    result = -1;
                    break;
                case (NegativeBalances):
                    result = doNegativeBalances(stmts);
                    result = -1;
                    break;
                case(Quit):
                default:
                    break;
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