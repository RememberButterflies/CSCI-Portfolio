/**
 * @file sudoku_logger.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date October 8, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      Creating a message to log, with the message being [the date and time of the check, its result, and which check it was (including the final check for the whole puzzle)],
 *      Logging the created message to a log array in memory,
 *      Displaying the log array to user, and 
 *      Saving the log array to a file.
 * 
 * The file also contain clearation of the array for the log messages from main
 * 
 * 
 * 
 *      Assignment #2 Multithreaded Sudoku Solution Validator
 *          Copyright (C) 2024  Patrick McGrath
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */



    // Header files

#include "sudoku_logger.h"
#include "sudoku_param.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
 



//Use following global variable declared in main.c file.
extern char logs[LOG_SIZE][LOG_MESSAGE_MAX_LENGTH];








/**
* @brief Cretes a message for storing in an array, displaying to user and saving to file
*
* @param message char* memory location for storing the created message
* @param location const char* the type of check being performed (Column, Row, Subgrid)
* @param row const int, the value of the row for the check
* @param col const int, the value of the column for the check
* @param thread_no const int, the thread number of the check
*/
void create_message(char* message, const char* location, const int row, const int col, const int thread_no){


    // create buffer of size LOG_MESSAGE_MAX_LENGTH
    // use sprintf to create message, using format provided in LOG_MESSAGE_FORMAT_LOCATION ("%s (%d,%d) has been checked by thread %d.")
    // the parameters for LOG_MESSAGE_FORMAT_LOCATION are the functions parameters (location, row, col, thread_no)
    // the message is copied from the buffer into the message parameter
    char buffer[LOG_MESSAGE_MAX_LENGTH];
    sprintf(buffer, LOG_MESSAGE_FORMAT_LOCATION, location, row, col, thread_no);
    strcpy(message, buffer);

    return;
}







/**
* @brief Stores a log entry in the log array after appending date and time and valid/invalid label to front of message.
*
* @param labe const char*, the label for the log entry (VALID or INVALID)
* @param message const char*, the message for the log entry, created by create_message()
* @param thread_no const int, the thread number of the check
*/
void log_message(const char* label, const char* message, const int thread_no){


    // get current time in elapsed seconds since jan 1 1970
    time_t currtime;
    currtime = time(NULL);

    // convert current time to human readable string
    char* currtimemsg = ctime(&currtime);

    // remove newline character from the end of the string
    currtimemsg[strlen(currtimemsg) - 1] = '\0';


    ///Format a log entry using LOG_ENTRY_FORMAT, current time, 'label', and 'message'
    char buffer[LOG_MESSAGE_MAX_LENGTH];
    sprintf(buffer, LOG_ENTRY_FORMAT, currtimemsg, label, message);

    //and copy the log entry into the element of the log sequence indexed by 'thread_no'. 
    strcpy(logs[thread_no], buffer);

    // return
    return;
}





/**
* @brief Displays all the entries in the log array to user via command-line
*
* @param NONE
*/
void log_show(){

    // iterate through the log array
    // printf with the %s being each element
    for (int i=0; i < LOG_SIZE; i++){
        printf("%s\n", logs[i]);
    }

    // return
    return;
}




/**
* @brief Saves all the entries in the log array to a file specified by LOG_FILE_PATH
*
* @param NONE
*/
void log_save(){

    // open file
    FILE *f = fopen(LOG_FILE_PATH, "a");
    if (f != NULL){
        // iterate through logs and print to file
        for (int i = 0; i < LOG_SIZE; i++){
            fprintf(f, "%s\n", logs[i]);
        }
        // close file
        fclose(f);
    }

    return;
}