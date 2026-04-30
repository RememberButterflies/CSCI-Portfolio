/**
 * @file scheduler_priority_rr.c
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

#include <stdbool.h>
#include <stdio.h>
#include "schedule.h"
#include <stddef.h>
#include "cpu.h"

cpu_task_t* pick_next_task(list_node_t* list){
    if (list == NULL){      // check if list is null first
        return NULL;
    }
    return list->task;      // return the first task in the list
}            
//	    Priority with Round Robin (PR-RR): Return the task that has the highest priority and should get the turn among
//                                         the tasks in that priority level. 
//


void schedule(list_node_t** list){

    list_node_t* l[MAX_PRIORITY] = {NULL};   // Priority lists
    list_node_t* curr = *list;      // current node
    while (curr != NULL){           // while there are still nodes
        list_node_t* temp = curr->next;     //  note currents next
        add(curr->task->name, curr->task->priority, curr->task->burst, &l[curr->task->priority - 1]);    // add the values of current to its appropriate priority list
        delete(list, curr->task);   // remove current node from main list
        curr = temp;                // update current to its next
    }



    for (int j = MAX_PRIORITY; j > 0; j--){
            int i = 1;                              // number for round
            list_node_t* n = l[j-1];                 // node for traversing list, starting at beginning
            while (n != NULL){                      // while there is at least 1 item in list     
                printf("Round %d\n", i);            // print message for current round
                cpu_task_t* t = pick_next_task(n);  // get the task of the first node
                bool single = false;
                if (n->next == NULL){
                    single = true;
                }

                while (t != NULL){                  // for current round, while there are still tasks

                    int b;               // get the burst value for current task
                    if (single == true){   // t is only task at priority level
                        b = t->burst;       // do full burst
                    } else {
                        if (t->burst > QUANTUM){               // limit it to quantum
                            b = QUANTUM;
                        } else {
                            b = t->burst;                   // don't limit
                        }
                    }
                    run(t, b);                     // run current task using  potentially limited burst
                    t->burst = t->burst - b;       // decrement tasks burst by burst value used
                    if (t->burst <= 0){            // if tasks burst is now zero or less
                        list_node_t* temp = n->next;    // keep track of n's next
                        delete(&l[j-1], t);                // remove n from list as it is t's node
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
            n = l[j-1];                             // reset n for next run
            i++;                                    // increment round number
        }
    }



    return;
}
//For PR-RR, shecdule all the tasks from the task list doing the followings:
//      - Rearrange the tasks into multiple lists (for example, an array of lists), one list for each priority level
//      - For each priority level starting from the highest to lowest do the followings:
//          - Pick up the task in turn from this priority level by calling pick_next_task() function.
//              - If there is no other task in the same priority level run the task by calling run() function for its needed cpu burst.
//              - Else run the task by calling run() function for at most a quanta of the cpu burst and decrement task's cpu burst accordingly.
//              - Delete the task from the list by calling delete() function only if the task has finished running its needed cpu burst.