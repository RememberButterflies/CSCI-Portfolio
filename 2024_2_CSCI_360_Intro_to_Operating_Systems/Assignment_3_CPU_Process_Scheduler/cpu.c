/**
 * @file cpu.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"



/**
* @brief Simulates running a specified task for a specified amount of time in cpu bursts, by printing a statement with that info.
*
* @param task, cpu_task_t*, pointer to the specified task with info to print
* @param slice, const int, the amount of cpu bursts to simulate
*/
void run(const cpu_task_t *task, const int slice){
    if (task == NULL){  // check if task is NULL
        return;
    }
    if (task->name == NULL){    // check if task name is NULL
        return;
    }

    char buffer[TASK_SIZE];     // buffer for print message 
    char* nm = (char*)malloc(strlen(task->name) + 1);    // string for copy of task name
    if (nm == NULL){    // check if string creation successful
        return;
    }
    strcpy(nm, task->name);  // copy task name
    size_t len = strlen(nm);    // length of string 
    if (len > 0 && nm[len - 1] == '\n') {   // check if string is not empty and if the final character is  a newling
        nm[len - 1] = '\0';     // remove newline
    }
        sprintf(buffer, TASK_RUN_INFO_FORMAT, nm, task->priority, task->burst, slice);      // format print message
        printf("%s", buffer);    // print message
        free(nm);       // free memory for copy of task name
    return;
}