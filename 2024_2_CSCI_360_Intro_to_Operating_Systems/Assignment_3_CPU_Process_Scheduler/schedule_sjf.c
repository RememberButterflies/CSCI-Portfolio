/**
 * @file scheduler_sjf.c
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
#include "cpu.h"
#include <stddef.h>
#include <limits.h>

cpu_task_t* pick_next_task(list_node_t* list){
    if (list == NULL){      // check if list is null first
        return NULL;
    }

    int cpu = INT_MAX;              // find lowest value cpu in list
    list_node_t* t = list;          // node for traversing
    while (t != NULL){              // find lowest value in list, ignoring where it came from
        if (t->task->burst < cpu){
            cpu = t->task->burst;
        }
        t = t->next;
    }

    if (cpu != INT_MAX){                // find the first node with the cpu's value
        t = list;                       // reset t to beginning
        while (t->task->burst != cpu){  // while t is not at a node with cpu's value
            t = t->next;                // move t to its next
        }
        return t->task;                 // return t's task.
    }

    return NULL;
}
// Pick up the next task from the given task list based on any of the specific scheduling algorithm.
//	    Shortest Job First (SJF): Return the task that needs the least cpu burst and came first among the 
//                                tasks that need the same cpu burst.

void schedule(list_node_t** list){
    cpu_task_t* t = pick_next_task(*list);  // get first task
    while (t != NULL){                      // as long as there is a current task
        run(t, t->burst);                   // run it
        delete(list, t);                    // delete it
        t = pick_next_task(*list);          // get the next one, if there is one
    }
    return; 
}
//For SJF, schedule all the tasks from the task list by doing the followings:
//      - Pick up the task that needs the least cpu burst and came first among the tasks that need the same cpu burst
//        by calling pick_next_task() function.
//      - Run the task by calling run() function for its needed cpu burst.
//      - Delete the task from the list by calling delete() function.