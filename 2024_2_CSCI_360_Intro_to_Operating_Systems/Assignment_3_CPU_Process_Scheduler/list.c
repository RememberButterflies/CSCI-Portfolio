/**
 * @file list.c
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

#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void insert(list_node_t** list, cpu_task_t* task){

    // make new list node
    list_node_t* t = (list_node_t*)malloc(sizeof(list_node_t));

    // if node was made successfully, continue
    if (t != NULL){

        // assign nodes task as the given one
        t->task = task;
        t->next = NULL;

        // add node to end of list

        // check if list is not null,
        list_node_t* curr = *list;
        if (*list != NULL){
            // list is currently not empty
            // find last node
            while (curr->next != NULL){
                curr = curr->next;
            }
            // make last node's next the new node
            curr->next = t;
        } else {
            // list is currently empty, make first item new node
            *list = t;
        }
    }

    return;
}
//Parameter 'list' is a pointer of a 'list_node_t' pointer, i.e., a pointer of a pointer.
//This pointer points to the fist node of the list, it could be NULL if there is no node already inserted in the list.
//Allocate memory for a new list node using malloc() function and assign its task to the given task.
//Add the new list node at the end of the list.


void delete(list_node_t** list, const cpu_task_t* task){

    //Parameter 'list' is a pointer of a 'list_node_t' pointer, i.e., a pointer of a pointer.
    //This pointer points to the fist node of the list, it could be NULL if there is no node already inserted in the list.
    //Do nothing if the list is empty or the task pointer is NULL.
    if (*list != NULL){

        //Search the task in the list by task name.
        list_node_t* curr = *list;      // current node, will find the one to delete
        list_node_t* prev = *list;      // previous node, will chase current to be the node previous to it
        bool found = false;             // marker for found or not

        // check if first node is the one to delete
        if (strcmp(curr->task->name, task->name) == 0){
            found = true;   // mark found
            prev = NULL;    // mark previous as null
        } else {
            // if not the first element, move current to its next, leave previous at the start and begin searching.
            curr = curr->next;
            // while the current node isnt null and the found marker hasnt been set, check current
            while ((curr != NULL) && (found == false)){
                // if current's name is same, mark found
                if (strcmp(curr->task->name, task->name) == 0){
                    found = true;
                } else {
                    // if curr's name is different, move curr and prev to their nexts
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }

        //If the task is found remove the corresponding list node from the list by manipulating appropriate pointers.
        if (found == true){

            // curr is either first, last, or in the middle
            // 1. if current is first, prev will be null.
            // 2. if it is last, current's next will be null
            // 3. if it is in the middle, previous will not be null and curr's next will not be null

            // 1. current is first member of list
            if (prev == NULL){
                *list = curr->next;

            // 2 + 3. curr is in the middle
            } else {
                prev->next = curr->next;
            }

            // free tasks memory
            free(curr->task->name);
            free(curr->task);
            free(curr);
        }


    }
    return;
}



void add(char* name, const int priority, const int burst, list_node_t** list){

    //Allocate memory by calling malloc() or calloc() library function for a new task.
    cpu_task_t* t = (cpu_task_t*)malloc(sizeof(cpu_task_t));

    if (t != NULL){
        //Allocate memory for name, assign name, priority, and burst to the new task.
        t->name = (char*)malloc(strlen(name) + 1);
        if (t->name == NULL){
            free(t);
            return;
        }
        strcpy(t->name, name);
        t->burst = burst;
        t->priority = priority;

        //Insert the task into the list by calling your insert() function.
        insert(list, t);
    }
    return;
}



void load(const char* filename, list_node_t** list){

    if (list == NULL){
        return;
    }

        // open file
    FILE *file = fopen(filename, "r");
    // check if actually opened
    if (file == NULL) {
        return;
    }

    // buffer for line
    char buffer[TASK_SIZE];

    // get each line
    while (fgets(buffer, TASK_SIZE, file) != NULL){
        char* name = NULL;
        int priority = 0;
        int burst = 0;
        int i = 0;                  // counter for which token
        char* token = strtok(buffer, ", ");     // get first token
        while (token != NULL){
            if (i == 0){
                // dealing with name
                name = (char*)malloc(strlen(token) + 1);
                if (name == NULL){
                    fclose(file);
                    return;
                }
                strcpy(name, token);
                i = 1;
            } else if (i == 1){
                // dealing with priority
                priority = atoi(token);
                i = 2;
            } else {
                // dealing with burst
                burst = atoi(token);
                // add to list
                add(name, priority, burst, list);
                free(name);
                name = NULL;
                i = 0;
            }

            // get next token
            token = strtok(NULL, ", ");
        }
    }
    fclose(file);
    return;
}



void traverse(list_node_t* list){
    // check if list is NULL
    if (list == NULL){
        return;
    }

    list_node_t* t = list;      // current node
    while (t != NULL){          // while current node is not null
        char buffer[TASK_SIZE];     // buffer for print message
        char* nm = (char*)malloc(strlen(t->task->name) + 1);    // string for copy of task name
        if (nm == NULL){    // check if string creation successful
            return;
        }
        strcpy(nm, t->task->name);  // copy task name
        size_t len = strlen(nm);    // length of string 
        if (len > 0 && nm[len - 1] == '\n') {   // check if string is not empty and if the final character is  a newling
            nm[len - 1] = '\0';     // remove newline
        }
        sprintf(buffer, TASK_INFO_FORMAT, nm, t->task->priority, t->task->burst);      // format print message
        printf("%s", buffer);    // print message
        t = t->next;        // move to next node
        free(nm);       // free memory for copy of task name
    }
    return;
}