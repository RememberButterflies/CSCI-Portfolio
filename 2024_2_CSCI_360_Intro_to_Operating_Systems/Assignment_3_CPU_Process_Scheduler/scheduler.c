/**
 * @file scheduler.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date October 20, 2024
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
 *      Assignment #3: CPU Process Scheduler
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "schedule.h"


//Use following global variable in your code.
list_node_t *list = NULL;  	//Global pointer variable to refer the head of the task list


int main(int argc, char *argv[]) {
    
    //Check whether a command line argument has been passed or not.
	if (argc < 2){
		// no filename provided, inform user
		printf("Filename not given. \n");
	} else {
        
        char filename[TASK_SIZE]; 	// memory to hold user entered filename
        // initialize filename to empty string
        filename[0] = '\0';
		//set filename to provided one
		strcpy(filename, argv[1]);
    //Check whether the task file name has been given as the command line argument or not.
    //If not given, report it to the user and exit the program.
    //If given, open the file in read only mode and load the tasks to the task list from the file
    //by calling load() function.
    load(filename, &list);

    //Show the loaded tasks by calling traverse() function.
    traverse(list);
    //Schedule the tasks of the list by calling schedule() function.	
    schedule(&list);

    }
    return 0;
}