/**
 * @file projTest.cpp
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
#include "../include/tokenparsewriteTest.h"


int main(){

   // variables
   // user and file stuff
   std::string logfolder = "logs/";    // folder to store logs
   std::string extension = ".sittie";  // extension of log files
   std::string filename = "ERROR";     // name of file to open
   std::string userID = "ERROR";       // userid of user using this program
   bool fileFound = true;              // flag to indicate if file was found. default true, if false,  new one was created
   std::string input = "ERROR";        // user input

   // tokenizing stuff
   token tokens[MaxTokens];            // array of tokens
   int numTokens = 0;                  // number of tokens in the array

   // parsing stuff
   entry entries[MaxEntries];           // array of entries
   int numEntries = 0;                 // number of entries in the array
   user users[MaxUsers];               // array of users
   int numUsers = 0;                   // number of users in the array


   // ask user for file name
   std::cout << "Enter the name of the file to open (without extension): ";
   std::cin >> filename;
   filename = logfolder + filename + extension;   // add the log folder to the file name
   // try to open file, if fail note it
   std::ifstream checkfileexists(filename);
   if (!checkfileexists.is_open()){
      fileFound = false;
      std::cout << "File not found, creating new file: " << filename << std::endl;
   } else {
      std::cout << "File opened successfully: " << filename << std::endl;
      checkfileexists.close();
   }



   // if there is a file, open, tokenize and parse it
   if (fileFound == true){
      // open file, tokenize it and return number of tokens
      // will close file when done
      numTokens = tokenize(tokens, MaxTokens, filename); 
      if (numTokens < 0){
         std::cout << "Error tokenizing file: " << filename << std::endl;
         return -1;
      }

      // parse the tokens
      // any grammar rules or context rules error will be caught here and returned -1
      numEntries = parse(tokens, numTokens, entries, MaxEntries, users, numUsers, MaxUsers);
      if (numEntries < 0){
         std::cout << "Error parsing file: " << filename << std::endl;
         return -1;
      }
   }

   // TEST CODE
   printAll(tokens, numTokens, entries, numEntries, users, numUsers, "62");


   // if file is good, then ask user for their id
   int inputlength = 0;
   while (inputlength != 3){
      std::cout << "Enter your user number (3 digit): ";
      std::cin >> userID;
      inputlength = userID.length();
   }
   userID = "U" + userID;   // add U to the front of the userID
   if (fileFound == true){
      // log already exists and was just tokenized and parsed
      // check if userID in file
      if (!isValidUserID(userID, users, numUsers)){
         std::cout << "Invalid user ID: " << userID << std::endl;
         return -1;
      }
   } 

   // either user is valid in already existing file, or new file needs to be created
   // then write the header
   std::ofstream headerfile(filename, std::ios::app);
   if (!headerfile.is_open()){
      std::cout << "Error reopening file for writing: " << filename << std::endl;
      return -1;
   }
   // add new line if old file
   if (fileFound == true){
      headerfile << std::endl;
   }
   headerfile << "{{ LGN " << userID << std::endl;    // opens the sequence rule for first user
   headerfile.close();     // open again for each command/entry and finally to add the CLOSE for the sequence


   // if previous log was opened, display relevant information
   if (fileFound == true){
      printInfo(entries, numEntries, users, numUsers, userID);
   }

   // ask user for command, get it, and execute it
   help();   // print help
   while (input != "QUIT"){
      inputlength = 0;
      while (inputlength < 1){
         std:: cout << "Enter command ('h' for help list): ";
         std::cin >> input;
         inputlength = input.length();
      }
      // will handle command and return either QUIT or CONTINUE
      input = handleCommand(input, entries, numEntries, users, numUsers, userID, filename);
   }


   // write footer closing file with }}
   // open file in append mode
   std::ofstream tailfile(filename, std::ios::app);
   if (!tailfile.is_open()){
      std::cout << "Error reopening file for writing: " << filename << std::endl;
      return -1;
   }
   tailfile << "}}"; // close the entry

   // close file
   tailfile.close();

   // TEST CODE
   printAll(tokens, numTokens, entries, numEntries, users, numUsers, "125");

   // done
   return 0;
}

