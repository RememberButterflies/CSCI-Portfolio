/**
 * @file tokenparsewritetest.cpp
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
#include <limits>

// convert token enum value back to string
std::string getTType(unsigned int ttype){
   
   if (ttype == USERID){
      return "USERID";
   } else if (ttype == ENTRYID){
      return "ENTRYID";
   } else if (ttype == TEXTLIT){
      return "TEXTLIT";
   } else if (ttype == OPEN){
      return "OPEN";
   } else if (ttype == CLOSE){
      return "CLOSE";
   } else if (ttype == INVITE){
      return "INVITE";
   } else if (ttype == LOGIN){
      return "LOGIN";
   } else if (ttype == MESSAGE){
      return "MESSAGE";
   } else if (ttype == EVENT){
      return "EVENT";
   } else if (ttype == RESPONSE){
      return "RESPONSE";
   } else if (ttype == THUMBSUP){
      return "THUMBSUP";
   } else if (ttype == THUMBSDOWN){
      return "THUMBSDOWN";
   } else if (ttype == BLANK){
      return "BLANK";
   } else if (ttype == SMILEYFACE){
      return "SMILEYFACE";
   } else if (ttype == ERROR){
      return "ERROR";
   } else {
      return "Some issue.";
   }
   return "Some issue.";
}


// functions


// tokenize file into tokens array. does not parse
// returns number of tokens in array, -1 on error, on max tokens returns max tokens
int tokenize(token tokens[], int MaxTokens, std::string filename){


   // variables
   std::string line = "ERROR";      // current line of file
   std::string word = "ERROR";      // current word in line
   int linecount = 0;               // number of lines in file
   int charPos = 0;                 // position in line
   int pos = 0;                     // position in token array 



   // open file
   std::ifstream file(filename);
   if (!file.is_open()){
      std::cout << "Error re-opening file: " << filename << std::endl;
      return -1;
   }


   // go through file line-by-line,
   //    get line through getline, and make a stream out of it
   // with each line, go through word-by-word
   //    add them to the token array with appropriate info
   while (getline(file, line)){
      charPos = 0;                  // reset charPos for each line
      std::istringstream iss(line); // create a string stream from the line
      

       // while there are words in the line
       while (iss >> word){

         // check if exceeded max tokens
         if (pos >= MaxTokens){
            return pos; 
         }


         // process the word into token array
         processWord(word, tokens, pos, linecount, charPos);
         pos++;                              // increment position in token array
         charPos += word.length() + 1;       // increase charPos by the size of the word + 1 for space
         word = "ERROR";                     // reset word for next iteration 
      }

      linecount++;   // increment line number
   }

   // close file
   file.close();

   // return number of tokens
   return pos;
}




// process current word into token array with appropriate info (tokenType, content, linepos, charpos)
void processWord(std::string word, token tokens[], int pos, int linecount, int charPos){

   int len = word.length();  // length of current token's content


   // check for empty word
   if (len == 0){
      tokens[pos].tokenType = ERROR;
      tokens[pos].content = "";
      tokens[pos].linepos = linecount;
      tokens[pos].charpos = charPos;
      return;
   }

   // check for textlit
   if (word[0] == 34){      // first char is quote

      // must remove all "_SPACE_"'s
      // make copy to remove _SPACE_'s (length = 7)
      std::string wordCopy = word;
      int skip = 7;


      // go through wordCopy length, replace all "_SPACE_" with " "
      // after replacing, length is updated within loop
      for (int i=1; i<len; i++){
         // chekc if at end
         if (i == len-1){
            // check if last char is quote
            if (wordCopy[i] != 34){
               // bad formatting on textlit
               tokens[pos].tokenType = ERROR;
               tokens[pos].content = word;         // give it back the original word
               tokens[pos].linepos = linecount;
               tokens[pos].charpos = charPos;
               return;
            } else {
               // good textlit
               tokens[pos].tokenType = TEXTLIT;
               tokens[pos].content = wordCopy;     // give it the updated word
               tokens[pos].linepos = linecount;
               tokens[pos].charpos = charPos;
               return;
            }
         } else {


            // not at end of word
            // check if a _SPACE_, using nested if's
            if (wordCopy[i] == 95){ // first "_" found maybe
               // check up to next 6 characters
               if (i+skip < len){
                  int k = i;        // the spot the " " will go
                  int j = i+1;      // to iterate through the rest of the "SPACE_"
                  if (wordCopy[j] == 'S'){
                     j++;
                     if (wordCopy[j] == 'P'){
                        j++;
                        if (wordCopy[j] == 'A'){
                           j++;
                           if (wordCopy[j] == 'C'){
                              j++;
                              if (wordCopy[j] == 'E'){
                                 j++;
                                 if (wordCopy[j] == 95){
                                    // _SPACE_ found from i to j
                                    // replace _SPACE_ with " "
                                    wordCopy.replace(i, skip, " ");
                                    // move i back to check for next _SPACE_
                                    i = k;
                                    len = wordCopy.length();   // update wordlength
                                 }
                              }
                           }
                        }
                     }
                  }
               }   
            }
            // else not a space, move past it
         }
      }

   } else if (word[0] == 'U'){ // check for userID
         // correct first letter
         // check rest. must be 3 remaining integers
         if (len != 4){
            // bad length
            tokens[pos].tokenType = ERROR;
            tokens[pos].content = word;
            tokens[pos].linepos = linecount;
            tokens[pos].charpos = charPos;
            return;
         }

         // check if all are digits
         for (int i=1; i<len; i++){
            if ((word[i] < 48) || (word[i] > 57)){
               // not a digit
               tokens[pos].tokenType = ERROR;
               tokens[pos].content = word;
               tokens[pos].linepos = linecount;
               tokens[pos].charpos = charPos;
               return;
            }
         }

         // good userID
         tokens[pos].tokenType = USERID;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      
      } else if (word[0] == 'E'){   // check for entryID
         // correct first letter
         // check rest. must be 3 remaining integers
         if (len != 4){
            // bad length
            tokens[pos].tokenType = ERROR;
            tokens[pos].content = word;
            tokens[pos].linepos = linecount;
            tokens[pos].charpos = charPos;
            return;
         }

         // check if all are digits
         for (int i=1; i<len; i++){
            if ((word[i] < 48) || (word[i] > 57)){
               // not a digit
               tokens[pos].tokenType = ERROR;
               tokens[pos].content = word;
               tokens[pos].linepos = linecount;
               tokens[pos].charpos = charPos;
               return;
            }
         }
         // good entryID
         tokens[pos].tokenType = ENTRYID;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;


         // then check for each token
      } else if (word == "{{") {
         tokens[pos].tokenType = OPEN;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "}}") {
         tokens[pos].tokenType = CLOSE;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "INV") {
         tokens[pos].tokenType = INVITE;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "LGN") {
         tokens[pos].tokenType = LOGIN;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "MSG") {
         tokens[pos].tokenType = MESSAGE;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "VNT") {
         tokens[pos].tokenType = EVENT;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "RSP") {
         tokens[pos].tokenType = RESPONSE;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "TMUP") {
         tokens[pos].tokenType = THUMBSUP; 
         tokens[pos].content = word; 
         tokens[pos].linepos = linecount; 
         tokens[pos].charpos = charPos; 
         return;
      } else if (word == "TMDN") {
         tokens[pos].tokenType = THUMBSDOWN; 
         tokens[pos].content = word; 
         tokens[pos].linepos = linecount; 
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "BLNK") {
         tokens[pos].tokenType = BLANK; 
         tokens[pos].content = word; 
         tokens[pos].linepos = linecount; 
         tokens[pos].charpos = charPos;
         return;
      } else if (word == "SMFL") {
         tokens[pos].tokenType = SMILEYFACE; 
         tokens[pos].content = word; 
         tokens[pos].linepos = linecount; 
         tokens[pos].charpos = charPos;
         return;
      } else {
         // not a valid token
         tokens[pos].tokenType = ERROR;
         tokens[pos].content = word;
         tokens[pos].linepos = linecount;
         tokens[pos].charpos = charPos;
         return;
      }
      
   return;  // some error
}


// parse token array into entry and user arrays
// calls helper function to parse each sequence, which will call helper to parse each entry
// return number of entries in the array, -1 on error
int parse(token tokens[], int numTokens, entry entries[], int MaxEntries, user users[], int &numUsers, int MaxUsers){
   // check parameters
   if ((tokens == NULL) || (numTokens <= 0) || (users == NULL) || (numUsers < 0)){
      return -1;
   }


   // variables
   int pos = 0;               // position in token array
   int entryCount = 0;        // number of entries in the array
   int sequenceReturn = 0;    // return value from parseSequence helper function

   // while there are tokens and still within range and no sequence parsing error has been encountered, parse the tokens
   while ((pos<numTokens) && (entryCount < MaxEntries) && (numUsers < MaxUsers) && (sequenceReturn != -1)){

      sequenceReturn = -1; // reset sequence return

      // try to process one sequence
      // return the position in token array AFTER sequence, else -1
      sequenceReturn = parseSequence(tokens, pos, entries, entryCount, MaxEntries, users, numUsers, MaxUsers);
      if (sequenceReturn == -1){
         // error in sequence, return -1
         std::cout << "Error in sequence, token array position: " << pos << std::endl;
         return -1;
      } else {
         // good sequence, move pos to next token
         pos = sequenceReturn;
      }

      // check if next token is CLOSE
      if (sequenceReturn != -1){
         if (tokens[pos].tokenType == CLOSE){
            // good, move to next token
            pos++;
            sequenceReturn = -1; // reset sequence return
         } 
      }
   }

   // check if all tokens were processed
   if (pos != numTokens){
      std::cout << "Error, not all tokens were processed, token array position: " << pos << std::endl;
      return -1;
   }

   // should be good
   return entryCount;
}


// return true if userid is correct format and is in array and is invited and is logout == login
// return false if not to any of those
bool isValidUserID(std::string userID, user users[], int numUsers){
   // check parameters
   if ((userID.length() != 4) || (users == NULL) || (numUsers <= 0)){
      return false;
   }
   if (userID[0] != 'U'){
      return false;
   }

   // look for it in array
   for (int i=0; i<numUsers; i++){
      if (users[i].userID == userID){     // found
         // check if invited and logged out
         if ((users[i].inviteCount > 0) && (users[i].loginCount == users[i].logoutCount)){
            return true;
         } else {
            // not invited or not logged out
            return false;
         }
      }
   }
   // not found in array
   return false;
}


// display in user-format, what is in the log
// keeps note of who the user is and displays their entries as "you"
void printInfo(entry entries[], int numEntries, user users[], int numUsers, std::string userID){
   // check parameters
   if ((entries == NULL) || (numEntries <= 0) || (users == NULL) || (numUsers <= 0)){
      return;
   }

   std::cout << "Log file information:" << std::endl;

   // print who made file, by grabbing users[0]
   std::cout << "Users: " << std::endl;
   std::cout << "User #1: " << users[0].userID;
   if (users[0].userID == userID){
      std::cout << " (you)";
   }
   std::cout << " (file creator)" << std::endl;


   // print users list
   for (int i=1; i<numUsers; i++){
      std::cout << "User #" << i+1 << ": " << users[i].userID;
      if (users[i].userID == userID){
         std::cout << " (you)";
      }
      std::cout << std::endl;
   }
   
   // print entry by entry, prefix with an index number for referencing in commands
   std::cout << "Entries: " << std::endl;
   for (int i=0; i<numEntries; i++){
      std::cout << "Entry " << entries[i].entryID << ". ";
      // who from
      // check if entry is from userID
      if (entries[i].userID == userID){
         std::cout << "From " << entries[i].userID << " (you), ";
      } else {
         std::cout << "From " << entries[i].userID << ", ";
      }
      std::cout << std::endl;

      // indent for type
      std::cout << "        ";
      // print entry content, based on entrytype
      if (entries[i].entryType == "MESSAGE"){
         std::cout << "message: " << std::endl;
         std::cout << "            ";                 // further indent for content
         std::cout << entries[i].content1 << "." << std::endl;    // message can have only 1 content

      } else if (entries[i].entryType == "EVENT"){
         std::cout << "event: " << std::endl;
         std::cout << "            ";
         std::cout << "name: " << entries[i].content1 << std::endl;     // event must have name
         if (entries[i].content2 != "ERROR"){                           // event can have location
            std::cout << "            ";
            std::cout << "location: " << entries[i].content2 << std::endl;
         }
         if (entries[i].content3 != "ERROR"){                           // event can have time
            std::cout << "            ";
            std::cout << "time: " << entries[i].content3;
         }
         std::cout << "." << std::endl;

      } else if (entries[i].entryType == "RESPONSE"){
         std::cout << "response: " << std::endl;
         std::cout << "            ";
         std::cout << "to: " << entries[i].content1 << std::endl;       // the entryID being responded to
         std::cout << "            ";
         std::cout << "content: " << entries[i].content2 << "." << std::endl; // content of response

      } else if (entries[i].entryType == "INVITE"){
         std::cout << "invite: " << std::endl;
         std::cout << "            ";
         std::cout << "to: ";
         if (entries[i].content1 == userID){          // who is being invited
            std::cout << "(you).";
         } else {
            std::cout << entries[i].content1 << ".";
         }
         std::cout << std::endl;
      }

   }
   return;
}


// prints a list of all the commands
void help(){
   std::cout << "Commands:" << std::endl;
   std::cout << "    h for help" << std::endl;
   std::cout << "    l for log info" << std::endl;
   std::cout << "    m for message" << std::endl;
   std::cout << "    e for event" << std::endl;
   std::cout << "    r for response" << std::endl;
   std::cout << "    i for invite" << std::endl;
   std::cout << "    q for quit" << std::endl;
   return;
}


// handles the command passed to it
// will ask for further input if needed
// then writes content to file as entry
// returns "QUIT" if quit is input, otherwise handles input and returns "CONTINUE"
std::string handleCommand(std::string input, entry entries[], int &numEntries, user users[], int &numUsers, std::string userID, std::string filename){

   // use helper function to figure out a command code of input
   switch (getCommandCode(input)){
      case HELPcom:
         // print help
         help();
         return "CONTINUE";
         break;
      case QUITcom:
         // quit
         std::cout << "Quitting Program." << std::endl;
         return "QUIT";
         break;
      case LOGINFOcom:
         // log info
         printInfo(entries, numEntries, users, numUsers, userID);
         return "CONTINUE";
         break;
      case MESSAGEcom:
      {
         // log new message
         // ask for message
         std::string messageinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR for some reason
         while (messageinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter message: ";
            std::getline(std::cin, messageinput);        // use getline not cin to get whole line
            if (messageinput.length() == 0){
               messageinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";    // nothing entered
            } else {
               // message is not 0 length, convert strings
               messageinput = deSpaceMessage(messageinput);          // log textlits dont have spaces, swap them for "_SPACE_"
            }
         }
         // message input should be despaced

         // make string for entryID that is equal to the highest entryID in the array + 1
         std::string entryIDinput = "E" + threedigitStringfromIntentryIDinput(gethighestEntryID(entries, numEntries)+1);

         // open file in append mode
         std::ofstream file(filename, std::ios::app);
         if (!file.is_open()){
            std::cout << "Error opening file for writing: " << filename << std::endl;
            return "QUIT";
         }

         // write entry to file, appending quotes to textlit message
         file << "{{ "<< entryIDinput << " MSG \"" << messageinput << "\"" << std::endl;
         file << "}}" << std::endl; // close the entry

         // close file
         file.close();

         // add entry to entries array
         entries[numEntries].entryID = entryIDinput;
         entries[numEntries].userID = userID;
         entries[numEntries].entryType = "MESSAGE";
         entries[numEntries].content1 = messageinput;
         entries[numEntries].content2 = "ERROR";
         entries[numEntries].content3 = "ERROR";
         numEntries++;

         // return continue
         return "CONTINUE";
      }
         break;
         
      case EVENTcom:
      {
         // log new event
         // ask for event name
         std::string eventinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR
         while (eventinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter event name: ";
            std::getline(std::cin, eventinput);
            if (eventinput.length() == 0){
               eventinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // message is not 0 length, convert strings
               eventinput = deSpaceMessage(eventinput);
               eventinput = "\"" + eventinput + "\""; // add quotes 
            }
         }
         // event input should be despaced

         // ask for event location or blank
         std::string locationinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR
         while (locationinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter event location or '0' for blank: ";
            std::getline(std::cin, locationinput);
            if (locationinput.length() == 0){
               locationinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // message is not 0 length
               if (locationinput == "0"){
                  locationinput = "BLNK";
               } else {
                  // convert strings
                  locationinput = deSpaceMessage(locationinput);
                  locationinput = "\"" + locationinput + "\""; // add quotes
               }
            }
         }
         // location input should be despaced
         // ask for time or blank
         std::string timeinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR
         while (timeinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter event time or '0' for blank: ";
            std::getline(std::cin, timeinput);
            if (timeinput.length() == 0){
               timeinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // message is not 0 length
               if (timeinput == "0"){
                  timeinput = "BLNK";
               } else {
                  // convert strings
                  timeinput = deSpaceMessage(timeinput); 
                  timeinput = "\"" + timeinput + "\""; // add quotes
               }
            }
         }
         // time input should be despaced

         // make string for entryID
         std::string entryIDinput = "E" + threedigitStringfromIntentryIDinput(gethighestEntryID(entries, numEntries)+1);
         // open file in append mode
         std::ofstream file(filename, std::ios::app);
         if (!file.is_open()){
            std::cout << "Error opening file for writing: " << filename << std::endl;
            return "QUIT";
         }

         // write entry to file
         file << "{{ "<< entryIDinput << " VNT " << eventinput << " " << locationinput << " " << timeinput << std::endl;
         file << "}}" << std::endl; // close the entry

         // close file
         file.close();

         // add entry to entries array
         entries[numEntries].entryID = entryIDinput;
         entries[numEntries].userID = userID;
         entries[numEntries].entryType = "EVENT";
         entries[numEntries].content1 = eventinput;
         entries[numEntries].content2 = locationinput;
         entries[numEntries].content3 = timeinput;
         numEntries++;

         // return continue
         return "CONTINUE";
      }
         break;

      case INVITEcom:
      {
         // log new invite
         // ask for userID
         std::string inviteinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR
         while (inviteinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter userID to invite (3 digit): ";
            cin >> inviteinput;
            if (inviteinput.length() != 3){
               inviteinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // message is 3 length
               // convert it to a string with U infront
               int invitenumber = getEntryIDint("E" + inviteinput);
               if (invitenumber == -1){
                  inviteinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
               } else {
                  // convert int to string with "U" infront, and padd with leadeing 0's
                  inviteinput = "U" + threedigitStringfromIntentryIDinput(invitenumber);
               }
            }
         }
         // invite input should be got

         // make string for entryID that is equal to the highest entryID in the array + 1
         std::string entryIDinput = "E" + threedigitStringfromIntentryIDinput(gethighestEntryID(entries, numEntries)+1);

         // open file in append mode
         std::ofstream file(filename, std::ios::app);
         if (!file.is_open()){
            std::cout << "Error opening file for writing: " << filename << std::endl;
            return "QUIT";
         }

         // write entry to file
         file << "{{ " << entryIDinput << " INV " << inviteinput << std::endl;
         file << "}}" << std::endl; // close the entry

         // close file
         file.close();

         // add entry to entries array
         entries[numEntries].entryID = entryIDinput;
         entries[numEntries].userID = userID;
         entries[numEntries].entryType = "INVITE";
         entries[numEntries].content1 = inviteinput;
         entries[numEntries].content2 = "ERROR";
         entries[numEntries].content3 = "ERROR";
         numEntries++;

         // check if user is in user array, if so increment invite count
         // if not in user array, add user to user array
         bool userFound = false;
         for (int i=0; ((i<numUsers) && (!userFound)); i++){
            if (users[i].userID == inviteinput){
               // found user, increment invite count
               users[i].inviteCount++;
               userFound = true;
            }
         }
         if (!userFound){
            // not found, add user to array
            users[numUsers].userID = inviteinput;
            users[numUsers].inviteCount = 1;
            users[numUsers].loginCount = 0;
            users[numUsers].logoutCount = 0;
            numUsers++;
         }


         // return continue
         return "CONTINUE";
      }
         break;

      case RESPONSEcom:
      {
         // log new response
         // ask for entryID
         std::string responseinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
         while (responseinput == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Enter entryID to respond to (3 digit) (000-" << threedigitStringfromIntentryIDinput(numEntries-1) << ") " << ": "; // REMOVE IF DOESNT WORK
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove
            std::getline(std::cin, responseinput);
            if (responseinput.length() != 3){
               responseinput = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // message is 3 length
               // convert it to a string with E infront
               responseinput = "E" + responseinput;
            }
         }

         // ask for response content
         // content may be message, thumbs up, thumbs down, or smiley face

         std::string responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // default message, incase the user wants to enter ERROR
         while (responsecontent == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
            std::cout << "Choose response content: " << std::endl;
            std::cout << "    m for message" << std::endl;
            std::cout << "    u for thumbs up" << std::endl;
            std::cout << "    d for thumbs down" << std::endl;
            std::cout << "    s for smiley face: ";
            responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // reset to default
            cin >> responsecontent;
            if (responsecontent.length() <= 0){
               responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
            } else {
               // check if valid response
               // and capture the response content
               switch (responsecontent[0]){
                  case 'm':
                  case 'M':
                  responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // reset to default
                  while (responsecontent == "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"){
                     std::cout << "Enter message: ";
                     std::getline(std::cin, responsecontent);
                     if (responsecontent.length() <= 0){
                        responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";
                     } else {
                        // message is not 0 length, convert string, removing spaces and adding quotes
                        responsecontent = deSpaceMessage(responsecontent);
                        responsecontent = "\"" + responsecontent + "\"";
                     }
                  }

                     break;
                  case 'u':
                  case 'U':
                     responsecontent = "TMUP";     // thumbs up
                     break;
                  case 'd':
                  case 'D':
                     responsecontent = "TMDN";     // thumbs down
                     break;
                  case 's':
                  case 'S':
                     responsecontent = "SMFL";     // smiley face
                     break;
                  default:
                     responsecontent = "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz"; // error
                     break;
               }
            }

         }
         // response input should be got

         // string for entryID that is equal to the highest entryID in the array + 1
         std::string entryIDinput = "E" + threedigitStringfromIntentryIDinput(gethighestEntryID(entries, numEntries)+1);

         // open file in append mode
         std::ofstream file(filename, std::ios::app);
         if (!file.is_open()){
            std::cout << "Error opening file for writing: " << filename << std::endl;
            return "QUIT";
         }

         // write entry to file
         file << "{{ " << entryIDinput << " RSP " << responseinput << " " << responsecontent << std::endl;
         file << "}}" << std::endl; // close the entry

         // close file
         file.close();

         // add entry to entries array
         entries[numEntries].entryID = entryIDinput;
         entries[numEntries].userID = userID;
         entries[numEntries].entryType = "RESPONSE";
         entries[numEntries].content1 = responseinput;
         entries[numEntries].content2 = responsecontent;
         entries[numEntries].content3 = "ERROR";
         numEntries++;

         // return continue
         return "CONTINUE";
      }
         break;
   }

   // if we get here, something went wrong
   return "ERROR";
}


// returns a string of 3 digits from an int, front padded with 0's
// if (0 > int > 999), return "ERROR"
std::string threedigitStringfromIntentryIDinput(int value){
   // check
   if (value < 0){
      return "ERROR";
   }
   if (value > 999){
      return "ERROR";
   }
   

   // go from right to left, get each digit
   // convert to char and add to string
   int ones = 0;     // curent digit
   std::string result = "000";
   for (int i=2; i>=0; i--){
      ones = value % 10;         // get the current digit
      value = value / 10;        // remove the digit
      result[i] = ones + 48;     // convert int to char and put in string
   }

   // return result
   return result;
}



// removes spaces from intput string and replaces them with "_SPACE_"
std::string deSpaceMessage(std::string messageinput){
   // check parameters
   int len = messageinput.length();
   if (len == 0){
      return "aSJy2siegfzCSGVtza6a2wm6ZSAVplqz";   // incase the message is infact "ERROR"
   }

   // go through all of messageinput and replace _SPACE_ with " "
   std::string result = "";
   for (int i=0; i<len; i++){
      if (messageinput[i] == 32){   // Check for space
         result += "_SPACE_";       // replace with _SPACE_
      } else {
         result += messageinput[i]; // else just add the character
      }
   }

   // return result
   return result;
}



// get the command code from the input string
// return the command code, or -1 if invalid
// command codes are in enumeration commandCode
int getCommandCode(std::string input){
   //check param
   if (input.length() == 0){
      return -1;
   }
   // switch on first char
   switch (input[0]){
      case 'h':
      case 'H':
         return HELPcom;      // help
         break;
      case 'L':
      case 'l':
         return LOGINFOcom;   // log info
         break;
      case 'M':
      case 'm':
         return MESSAGEcom;   // message
         break;
      case 'E':
      case 'e':
         return EVENTcom;     // event
         break;
      case 'R':
      case 'r':
         return RESPONSEcom;  // response
         break;
      case 'I':
      case 'i':
         return INVITEcom;    // invite
         break;
      case 'Q':
      case 'q':
         return QUITcom;      // quit
         break;
      default:
         return INVALIDcom;  // error
         break;
   }
   return -1;         // error
}



// parse a sequence rule of tokens into entries and users
// return the position in the token array after the sequence
int parseSequence(token tokens[], int pos, entry entries[], int &entryCount, int MaxEntries, user users[], int &numUsers, int MaxUsers){

   // check for OPEN and LOGIN and USERID
   // check if OPEN token
   if (tokens[pos].tokenType != OPEN){
      std::cout << "Error, expected OPEN token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }
   pos++; // move to next token
   // check if LOGIN token
   if (tokens[pos].tokenType != LOGIN){
      std::cout << "Error, expected LOGIN token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }
   pos++; // move to next token
   // check if USERID token
   if (tokens[pos].tokenType != USERID){
      std::cout << "Error, expected USERID token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }
   pos++;

   // user variables for sequence
   std::string currentUserID = tokens[pos-1].content;;   // current userID, not the logged in userID, just the one who made this sequence
   int currentUserPos = 0;                               // position in user array
   bool userFound = false;                               // flag for whether user found in array


   // check if userID follows valid rules
   // first see if userID is in user array
   for (int i=0; ((i<numUsers) && (!userFound)); i++){
      if (users[i].userID == currentUserID){
         userFound = true;
         currentUserPos = i;
      }
   }

   // if user is found
   // check if the inviteCount is > 0
   // check if the loginCount == logoutCount
   if (userFound){
      if ((users[currentUserPos].inviteCount <= 0) || (users[currentUserPos].loginCount != (users[currentUserPos].logoutCount))){
            std::cout << "Error, userID: " << currentUserID << " is not valid, inviteCount: " << users[currentUserPos].inviteCount << ", loginCount: " << users[currentUserPos].loginCount << ", logoutCount: " << users[currentUserPos].logoutCount << std::endl;
            return -1;
      }

      // user should be good if here
      // increment users login count
      users[currentUserPos].loginCount++;

   } else {
      // user not found
      // only valid just starting to parse and this is first userID to be inserted
      if (numUsers == 0){
         // add user to array
         users[numUsers].userID = currentUserID;
         users[numUsers].inviteCount = 1;
         users[numUsers].loginCount = 1;
         users[numUsers].logoutCount = 0;
         numUsers++;
      } else {
         // user not found and not first user
         std::cout << "Error, userID: " << currentUserID << " is not valid, inviteCount: " << users[currentUserPos].inviteCount << ", loginCount: " << users[currentUserPos].loginCount << ", logoutCount: " << users[currentUserPos].logoutCount << std::endl;
         return -1;
      }
   }


   // check for entries
   int temp = 0;                    // return value from parseEntry
   while (temp != -1){              // while not at end of entry list or not an error

      // check if next token is OPEN for a new entry or CLOSE signifying end of sequence
      if (tokens[pos].tokenType != OPEN){       // check for not open, to do open in else portion
            
         if (tokens[pos].tokenType == CLOSE){   // check for ending close, closes sequenece
            // sequence with no entries
            // logout user
            if (!userFound){
               // user was not previously found, and should be the last user in array, log them out. but invites can change this, so re-search
               // check if userID is in array
               for (int i=0; ((i<numUsers) && (!userFound)); i++){
                  if (users[i].userID == currentUserID){
                     userFound = true;
                     currentUserPos = i;
                  }
               }
               if (!userFound){
                  currentUserPos = numUsers-1; // set to last user in array
               }
               users[currentUserPos].logoutCount++; // increment logout count
               //users[numUsers-1].logoutCount++;
               pos++;
               return pos;             // return position in token array
            } else {
               // else user was found and is at currentUserPos
               users[currentUserPos].logoutCount++;
               pos++;                  // move to next token
               return pos;             // return position in token array
               }
            }

         std::cout << "Error, expected CLOSE token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         temp = -1;              // set to -1 to break out of loop
      } else {
         // parse entry starting after OPEN token
         pos++;
         temp = parseEntry(tokens, pos, entries, entryCount, MaxEntries, users, numUsers, currentUserID, MaxUsers);
      }
      if (temp != -1){     // if entry was parsed, this will update to next position, else -1. if -1, just keep pos where it was to try it on next test
         pos = temp;
      }
   }



   


   // if here, some error
   return -1;
}





// parse single entry starting after the initial OPEN token
// return the position in the token array after the entry, or -1 on error
int parseEntry(token tokens[], int pos, entry entries[], int &entryCount, int MaxEntries, user users[], int &numUsers, std::string currentUserID, int MaxUsers){

   // check for entryID
   if (tokens[pos].tokenType != ENTRYID){
      std::cout << "Error, expected ENTRYID token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }
   pos++;

   // variables
   std::string currentEntryID = tokens[pos-1].content;         // current entryID
   bool entryFound = false;                                    // flag for whether entry found in array

   // first see if entryID is in entry array
   for (int i=0; ((i<entryCount) && (!entryFound)); i++){
      if (entries[i].entryID == currentEntryID){
         entryFound = true;
      }
   }

   // if entryID is found, return error
   if (entryFound){
      std::cout << "Error, entryID: " << currentEntryID << " is not valid, already exists" << std::endl;
      return -1;
   }

   // if there are entries in the array, check if current entryID is valid
   if (entryCount > 0){
      // if entryID not found, and there are entryIDs in list, get integer value of highest entryID and current one
      int highestEntryID = gethighestEntryID(entries, entryCount);
      int currentEntryIDint = getEntryIDint(currentEntryID);
      // if current != highest + 1 or if either is an error, return error
      if ((currentEntryIDint != (highestEntryID + 1)) || (currentEntryIDint < 0) || (highestEntryID < 0)){
         std::cout << "Error, entryID: " << currentEntryID << " is not valid, highest entryID: " << highestEntryID << std::endl;
         return -1;
      }
   } 
   
   // entry variables
   std::string currentEntryType = "ERROR";      // current entry type
   std::string currentEntryContent1 = "ERROR";  // current entry content1
   std::string currentEntryContent2 = "ERROR";  // current entry content2
   std::string currentEntryContent3 = "ERROR";  // current entry content3

   // if elses for checking what type of token is next.
   // check if next token is MESSAGE, EVENT, RESPONSE, or INVITE
   if (tokens[pos].tokenType == MESSAGE){
      // PARSE MESSAGE
      currentEntryType = "MESSAGE";
      pos++;
      // get message text
      // first check if next token is TEXTLIT
      if (tokens[pos].tokenType != TEXTLIT){
         std::cout << "Error, expected TEXTLIT token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }
      // then grab content
      currentEntryContent1 = tokens[pos].content;
      // increment position
      pos++;


   } else if (tokens[pos].tokenType == EVENT){
      // PARSE EVENT
      currentEntryType = "EVENT";
      pos++;
      // get event text
      // first check if next token is TEXTLIT
      if (tokens[pos].tokenType != TEXTLIT){
         std::cout << "Error, expected TEXTLIT token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }
      // then grab content
      currentEntryContent1 = tokens[pos].content;
      // increment position
      pos++;

      // event's next 2 tokens can either be BLNK or TEXTLIT
      if ((tokens[pos].tokenType != BLANK) && (tokens[pos].tokenType != TEXTLIT)){
         std::cout << "Error, expected BLANK or TEXTLIT token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }
      // then grab content
      if (tokens[pos].tokenType == BLANK){
         currentEntryContent2 = "BLANK";
      } else {
         currentEntryContent2 = tokens[pos].content;
      }
      pos++;

      // do again for next one
      if ((tokens[pos].tokenType != BLANK) && (tokens[pos].tokenType != TEXTLIT)){
         std::cout << "Error, expected BLANK or TEXTLIT token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }
      // then grab content
      if (tokens[pos].tokenType == BLANK){
         currentEntryContent3 = "BLANK";
      } else {
         currentEntryContent3 = tokens[pos].content;
      }
      pos++;


   } else if (tokens[pos].tokenType == RESPONSE){
      // PARSE RESPONSE
      currentEntryType = "RESPONSE";
      pos++;
      // get response entryID
      // first check if next token is ENTRYID
      if (tokens[pos].tokenType != ENTRYID){
         std::cout << "Error, expected ENTRYID token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }

      // then grab content
      currentEntryContent1 = tokens[pos].content;
      // check that entryID is in entry array
      bool entryIDfound = false;
      for (int i=0; ((i<entryCount) && (!entryIDfound)); i++){
         if (entries[i].entryID == currentEntryContent1){
            entryIDfound = true;
         }
      }
      // if entryID is not found, return error
      if (!entryIDfound){
         std::cout << "Error, entryID: " << currentEntryContent1 << " is not valid, not in entry array" << std::endl;
         return -1;
      }

      // increment position
      pos++;

      // next token must be TEXTLIT || reactiontoken
      if ((tokens[pos].tokenType != TEXTLIT) && (tokens[pos].tokenType != THUMBSUP) && (tokens[pos].tokenType != THUMBSDOWN) && (tokens[pos].tokenType != SMILEYFACE)){
         std::cout << "Error, expected TEXTLIT or reactiontoken token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }
      // then grab content
      currentEntryContent2 = tokens[pos].content;
      // increment position
      pos++;

   } else if (tokens[pos].tokenType == INVITE){
      // PARSE INVITE
      currentEntryType = "INVITE";
      pos++;
      // get response userID
      // first check if next token is USERID
      if (tokens[pos].tokenType != USERID){
         std::cout << "Error, expected USERID token, found: " << getTType(tokens[pos].tokenType) << std::endl;
         return -1;
      }

      // then grab content
      currentEntryContent1 = tokens[pos].content;
      // check that userID is in user array
      bool userIDfound = false;
      int inviteeindex = -1;
      for (int i=0; ((i<numUsers) && (!userIDfound)); i++){
         if (users[i].userID == currentEntryContent1){
            userIDfound = true;
            inviteeindex = i;
         }
      }
      // if userID is not found, add it to user array
      if (!userIDfound){
         // check if user array is full
         if (numUsers >= MaxUsers){
            std::cout << "Error, user array is full, cannot add userID: " << currentEntryContent1 << std::endl;
            return -1;
         }
         // add user to array
         users[numUsers].userID = currentEntryContent1;
         users[numUsers].inviteCount = 1;
         users[numUsers].loginCount = 0;
         users[numUsers].logoutCount = 0;
         numUsers++;
      } else {
         // userID is found, increment invite count
         users[inviteeindex].inviteCount++;
      }
      // increment position
      pos++;

   } else {
      std::cout << "Error, expected MESSAGE, EVENT, RESPONSE or INVITE token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }

   // check for CLOSE
   if (tokens[pos].tokenType != CLOSE){
      std::cout << "Error, expected CLOSE token, found: " << getTType(tokens[pos].tokenType) << std::endl;
      return -1;
   }
   pos++; // move to next token
   // check if entry is full
   if (entryCount >= MaxEntries){
      std::cout << "Error, entry array is full, cannot add entryID: " << currentEntryID << std::endl;
      return -1;
   }


  

   // if everything is good, make entry in entry array
   if (entryCount < MaxEntries){
      // add entry to entry array
      entries[entryCount].userID = currentUserID;
      entries[entryCount].entryID = currentEntryID;
      entries[entryCount].entryType = currentEntryType;
      entries[entryCount].content1 = currentEntryContent1;
      entries[entryCount].content2 = currentEntryContent2;
      entries[entryCount].content3 = currentEntryContent3;
      entryCount++;
   }

   // return position in token array
   return pos;
}


// converts a string of "E###" into an int of ###, -1 on error
// designed for "E###" but can be any string of char + 3 digits
int getEntryIDint(std::string entryID){
      // convert E### string into ### int
      int result = 0;            // return value
      int tens = 1;              // tens place value
      int ones = 0;              // ones place value

      // iterate through the string backwards i=3 to i=1
      for (int i=3; i>=1; i--){
         ones = entryID[i] - 48;          // convert current char to int
         if (ones < 0 || ones > 9){       // check if char is a digit
            return -1; // not a digit
         }
         ones = ones * tens;              // adjust ones to be in correct place
         result += ones;                  // add to result
         tens = tens * 10;                // increment tens place value
      }
   
      // return result
      return result;
}


// get the highest entryID in the entries array as an int without the initial E, -1 on error
int gethighestEntryID(entry entries[], int entryCount){

   // check parameters
   // check if entryCount is valid
   if (entryCount <= 0){
      return -1;
   }

   // check if entries is valid
   if (entries == NULL){
      return -1;
   }

   // check if last entry is valid
   if (entries[entryCount-1].entryID == "ERROR"){
      return -1;
   }

   // convert and return
   return getEntryIDint(entries[entryCount-1].entryID);
}








// stuff for testing

void printAll(token tokens[], int numTokens, entry entries[], int numEntries, user users[], int numUsers, std::string linenumber){
   std::cout << "Test Code, source code line: " << linenumber << std::endl;
   printTokens(tokens, numTokens);
   printEntries(entries, numEntries);
   printUsers(users, numUsers);
   return;
}

void printTokens(token tokens[], int numTokens){
   std::cout << "Ttokens array, size = " << numTokens << std::endl;
   for (int i=0; i<numTokens; i++){
      std::cout << "Token " << i << ": " << getTType(tokens[i].tokenType) << ", content: " << tokens[i].content << ", linepos: " << tokens[i].linepos << ", charpos: " << tokens[i].charpos << std::endl;
   }
   return;
}

void printEntries(entry entries[], int numEntries){
   std::cout << "Entries array, size = " << numEntries << std::endl;
   for (int i=0; i<numEntries; i++){
      std::cout << "Entry " << i << ": " << entries[i].entryID << ", userID: " << entries[i].userID << ", entryType: " << entries[i].entryType << ", content1: " << entries[i].content1 << ", content2: " << entries[i].content2 << ", content3: " << entries[i].content3 << std::endl;
   }
   return;
}
void printUsers(user users[], int numUsers){
   std::cout << "Users array, size = " << numUsers << std::endl;
   for (int i=0; i<numUsers; i++){
      std::cout << "User " << i << ": " << users[i].userID << ", inviteCount: " << users[i].inviteCount << ", loginCount: " << users[i].loginCount << ", logoutCount: " << users[i].logoutCount << std::endl;
   }
   return;
}