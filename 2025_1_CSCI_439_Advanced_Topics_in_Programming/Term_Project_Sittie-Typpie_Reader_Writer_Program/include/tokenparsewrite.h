/**
 * @file tokenparsewrite.h
 * @author Patrick McGrath, CSCI 439, VIU
 * @version 1.0
 * @date April, 2025
 * 
 *  Sittie-Typpie Reader / Writer Program
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

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
using namespace std;


// enumeration of all the token types
enum TokenType {
   Invalid = -1,
   USERID,
   ENTRYID,
   TEXTLIT,
   OPEN,
   CLOSE,
   INVITE,
   LOGIN,
   MESSAGE,
   EVENT,
   RESPONSE,
   THUMBSUP,
   THUMBSDOWN,
   BLANK,
   SMILEYFACE,
   ERROR
};

// enumeration of command codes
enum CommandCode {
   INVALIDcom = -1,
   HELPcom,
   QUITcom,
   LOGINFOcom,
   MESSAGEcom,
   EVENTcom,
   INVITEcom,
   RESPONSEcom,
   TMUPcom,
   TMDNcom,
   SMILEYcom
};


// upper limit on the number of tokens the program can process
const int MaxTokens = 1024;
const int MaxEntries = 200;
const int MaxUsers = 100;


// Tokenize information
// has:
//    tokenType of the token (from the TokenType enum)
//    content of the token (the text content of the token)
//    pos of the token (the position in the token array)
//    linepos of the token (the line number in the file)
//    charpos of the token (the position in the line of the token)
struct token {
   unsigned int tokenType;
   std::string content;
   int pos;
   int linepos;
   int charpos;
};


// parsing information for the entry
// has:
//    userID of the user who created the entry
//    entryID of the entry
//    entryType of the entry (e.g. INVITE, LOGIN, MESSAGE, EVENT, RESPONSE)
//    content1, content2, and content3 are the text literals or reaction tokens associated with the entry
struct entry {
   std::string userID;
   std::string entryID = "ERROR";
   std::string entryType;
   std::string content1;
   std::string content2;
   std::string content3;
};


// parsing information for the user
// has userID of the user
// used in array for parsing invites and logins/logouts of users. 
// originally logic required keeping track of all values,
// but after finalizing everything, i realized that only userID in array and correct token order in script is needed
struct user {
   std::string userID = "ERROR";
   int inviteCount = 0;
   int loginCount = 0;
   int logoutCount = 0;
};


// Function Prototypes

// tokenize file into tokens array. does not parse
// returns number of tokens in array, -1 on error, on max tokens returns max tokens
int tokenize(token tokens[], int MaxTokens, std::string filename);

// process current word into token array with appropriate info (tokenType, content, linepos, charpos)
void processWord(std::string word, token tokens[], int pos, int linecount, int charPos);

// parse token array into entry and user arrays
// calls helper function to parse each sequence, which will call helper to parse each entry
// return number of entries in the array, -1 on error
int parse(token tokens[], int numTokens, entry entries[], int MaxEntries, user users[], int &numUsers, int MaxUsers);

// parse a sequence rule of tokens into entries and users
// return the position in the token array after the sequence
int parseSequence(token tokens[], int pos, entry entries[], int &entryCount, int MaxEntries, user users[], int &numUsers, int MaxUsers);

// convert token type enum value to string
std::string getTType(unsigned int ttype);

// parse single entry starting after the initial OPEN token
// return the position in the token array after the entry, or -1 on error
int parseEntry(token tokens[], int pos, entry entries[], int &entryCount, int MaxEntries, user users[], int &numUsers, std::string currentUserID, int MaxUsers);

// get the highest entryID in the entries array as an int without the initial E, -1 on error
int gethighestEntryID(entry entries[], int entryCount);

// converts a string of "E###" into an int of ###, -1 on error
// designed for "E###" but can be any string of char + 3 digits
int getEntryIDint(std::string entryID);

// return true if userid is correct format and is in array and is invited and is logout == login
// return false if not to any of those
bool isValidUserID(std::string userID, user users[], int numUsers);

// display in user-format, what is in the log
// keeps note of who the user is and displays their entries as "you"
void printInfo(entry entries[], int numEntries, user users[], int numUsers, std::string userID);

// prints a list of all the commands
void help();

// handles the command passed to it
// will ask for further input if needed
// then writes content to file as entry
// returns "QUIT" if quit is input, otherwise handles input and returns "CONTINUE"
std::string handleCommand(std::string input, entry entries[], int &numEntries, user users[], int &numUsers, std::string userID, std::string filename);

// get the command code from the input string
// return the command code, or -1 if invalid
// command codes are in enumeration commandCode
int getCommandCode(std::string input);

// removes spaces from intput string and replaces them with "_SPACE_"
std::string deSpaceMessage(std::string messageinput);

// returns a string of 3 digits from an int, front padded with 0's
// if (0 > int > 999), return "ERROR"
std::string threedigitStringfromIntentryIDinput(int value);