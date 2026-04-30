/**
 * @file logger.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - Creating log messages, with 1 to 3 values
 *      - Logging messages with current time into the log array
 *      - Displaying all log messages
 *      - Saving all log messages to a file
 * 
 * 
 * 
 *      Assignment #4 Sleeping Teaching Assistant Simulator
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

// Headers
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "config.h"
#include "logger.h"


char logs[LOG_MAX_SIZE][LOG_MESSAGE_MAX_LENGTH];    //Array to hold log messages in memory
int log_size = 0;                                   //The actual number of log messages in the array




/**
* @brief Creates log message using message format passed and 1 value to be inserted into the message.
*        The resultant log message is copied into the passed memory address.
*
* @param message char*, the memory address to copy the log message
* @param message_format const char*, the format of the log message
* @param value1 const int, the value to be inserted into the log message
*/
void create_log_message1(char* message, const char* message_format, const int value1){

    // Message buffer for log message
    char buffer[LOG_MESSAGE_MAX_LENGTH];

    // Create message to log
    sprintf(buffer, message_format, value1);

    // Copy message to passed memory address
    strcpy(message, buffer);
    return;
}


/**
* @brief Creates log message using message format passed and 2 values to be inserted into the message.
*        The resultant log message is copied into the passed memory address.
*
* @param message char*, the memory address to copy the log message
* @param message_format const char*, the format of the log message
* @param value1 const int, the 1st value to be inserted into the log message
* @param value2 const int, the 2nd value to be inserted into the log message
*/
void create_log_message2(char* message, const char* message_format, const int value1, const int value2){
    
    // Message buffer for log message
    char buffer[LOG_MESSAGE_MAX_LENGTH];

    // Create message to log
    sprintf(buffer, message_format, value1, value2);

    // Copy message to passed memory address
    strcpy(message, buffer);
    return;
}



/**
* @brief Creates log message using message format passed and 3 values to be inserted into the message.
*        The resultant log message is copied into the passed memory address.
*
* @param message char*, the memory address to copy the log message
* @param message_format const char*, the format of the log message
* @param value1 const int, the 1st value to be inserted into the log message
* @param value2 const int, the 2nd value to be inserted into the log message
* @param value3 const int, the 3rd value to be inserted into the log message
*/
void create_log_message3(char* message, const char* message_format, const int value1, const int value2, const int value3){

    // Message buffer for log message
    char buffer[LOG_MESSAGE_MAX_LENGTH];

    // Create message to log
    sprintf(buffer, message_format, value1, value2, value3);

    // Copy message to passed memory address
    strcpy(message, buffer);
    return;
}


/**
* @brief Logs a message with the current time and a label into the log array.
*
* @param message char*, the memory address of the message to be logged
* @param label const char*, the label of the log message
*/
void log_message(const char* label, const char* message){

    // get time
    time_t currtime;
    currtime = time(NULL);

    // convert time to human readable
    char* currtimemsg = ctime(&currtime);

    // remove newline character from the end of the string
    currtimemsg[strlen(currtimemsg) - 1] = '\0';

    // format log entry and copy to the log sequence
    char buffer[LOG_MESSAGE_MAX_LENGTH];
    sprintf(buffer, LOG_ENTRY_FORMAT, currtimemsg, label, message);

    // log the message
    if (log_size < LOG_MAX_SIZE){
        strcpy(logs[log_size], buffer);
        log_size++;
    }

    return;
}





/**
* @brief Prints to screen all entries in the log array.
*
* @param none
*/
void log_show(){

    // Iterate through the log array
    for (int i = 0; i < log_size; i++){

        // print current log message
        printf("%s\n", logs[i]);
    }
    return;
}





/**
* @brief Saves all log messages to a file specificed by LOG_FILE_PATH.
*
* @param none
*/
void log_save(){
    // open file
    FILE *file = fopen(LOG_FILE_PATH, "w");
    if (file == NULL){
        perror("Error opening file");
        return;
    }

    // add all logs to file
    for (int i = 0; i < log_size; i++){
        fprintf(file, "%s\n", logs[i]);
    }

    // close file
    fclose(file);

    // end
    return;
}