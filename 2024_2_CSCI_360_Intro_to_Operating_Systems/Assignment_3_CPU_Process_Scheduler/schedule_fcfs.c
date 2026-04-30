/**
 * @file scheduler_fcfs.c
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

#include "schedule.h"
#include <stddef.h>
#include "cpu.h"

cpu_task_t* pick_next_task(list_node_t* list){
    if (list == NULL){      // check if list is null first
        return NULL;
    }
    return list->task;      // return the first task in the list
}
// Pick up the next task from the given task list based on any of the specific scheduling algorithm.
//
//	    First Come First Serve (FCFS): Return the task that came first.
//
//


void schedule(list_node_t** list){

    cpu_task_t* t = pick_next_task(*list);  // get first task
    while (t != NULL){                      // as long as there is a current task
        run(t, t->burst);                   // run it
        delete(list, t);                    // delete it
        t = pick_next_task(*list);          // get the next one, if there is one
    }
    return; 
}
//For FCFS, schedule all the tasks from the task list by doing the followings:
//      - Pick up the task that came first by calling pick_next_task() function.
//      - Run the task by calling run() function for its needed cpu burst.
//      - Delete the task from the list by calling delete() function.