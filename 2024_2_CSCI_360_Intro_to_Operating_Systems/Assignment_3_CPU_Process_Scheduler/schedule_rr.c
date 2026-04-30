/**
 * @file scheduler_rr.c
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
#include <stdio.h>



cpu_task_t* pick_next_task(list_node_t* list){
    if (list == NULL){      // check if list is null first
        return NULL;
    }
    return list->task;      // return the task of the node being passed
}
// Pick up the next task from the given task list based on any of the specific scheduling algorithm.
//	    Round Robin (RR): Return the task that should get the turn in the current round




void schedule(list_node_t** list){
    int i = 1;                              // number for round
    list_node_t* n = *list;                 // node for traversing list, starting at beginning
    while (n != NULL){                      // while there is at least 1 item in list     
        printf("Round %d\n", i);            // print message for current round
        cpu_task_t* t = pick_next_task(n);  // get the task of the first node
        while (t != NULL){                  // for current round, while there are still tasks
            int b = t->burst;               // get the burst value for current task
            if (b > QUANTUM){               // limit it to quantum
                b = QUANTUM;
            }
            run(t, b);                     // run current task using limited burst
            t->burst = t->burst - b;       // decrement tasks burst by burst value used
            if (t->burst <= 0){            // if tasks burst is now zero or less
                list_node_t* temp = n->next;    // keep track of n's next
                delete(list, t);                // remove n from list as it is t's node
                n = temp;                       // set n to its next
            } else {
                n = n->next;                    // if task's burst is greater than 0, just move n to its next
            }
            if (n != NULL){
                t = pick_next_task(n);          // if n is not null, get task from the next node
            } else {
                t = NULL;                       // else no more tasks in list for this round
            }
        }
        n = *list;                              // reset n for next run
        i++;                                    // increment round number
    }
    return; 
}
//For RR, schedule all the tasks from the task list by doing the followings:
//      - Pick up the next task by calling pick_next_task() function.
//      - Run the task by calling run() function for at most a quanta of the cpu burst and decrement task's cpu burst accordingly.
//	    - Delete the task from the list by calling delete() function only if the task has finished running its needed cpu burst.