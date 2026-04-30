/**
 * @file scheduler_priority.c
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
#include <cpu.h>

cpu_task_t* pick_next_task(list_node_t* list){
    if (list == NULL){      // check if list is null first
        return NULL;
    }
    return list->task;      // return the first task in the list
}
//	    Priority (PR): Return the task that has the highest priority and came first among the tasks
//                     in that priority level.


void schedule(list_node_t** list){


    list_node_t* l[MAX_PRIORITY] = {NULL};   // Priority lists
    list_node_t* curr = *list;      // current node
    while (curr != NULL){           // while there are still nodes
        list_node_t* temp = curr->next;     //  note currents next
        add(curr->task->name, curr->task->priority, curr->task->burst, &l[curr->task->priority - 1]);    // add the values of current to its appropriate priority list
        delete(list, curr->task);   // remove current node from main list
        curr = temp;                // update current to its next
    }

    // do fcfs for each priority list going from highest to lowest
    for (int i = MAX_PRIORITY; i > 0; i--){
        cpu_task_t* t = pick_next_task(l[i-1]);  // get first task
        while (t != NULL){                      // as long as there is a current task
            run(t, t->burst);                   // run it
            delete(&l[i-1], t);                    // delete it
            t = pick_next_task(l[i-1]);          // get the next one, if there is one
        }
    }

    return;
}
//For PR, shecdule all the tasks from the task list doing the followings:
//      - Rearrange the tasks into multiple lists (for example, an array of lists), one list for each priority level
//      - For each priority level starting from the highest to lowest do the followings:
//          - Pick up the task that came first in this priority level by calling pick_next_task() function.
//          - Run the task by calling run() function for its needed cpu burst.
//          - Delete the task from the list by calling delete() function.
//