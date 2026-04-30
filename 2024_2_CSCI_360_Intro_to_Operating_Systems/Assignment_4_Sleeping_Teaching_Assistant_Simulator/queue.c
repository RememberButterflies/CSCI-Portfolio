/**
 * @file queue.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - Enqueueing student id into the end of the waiting queue
 *      - Dequeueing student id from the head of the waiting queue
 *      - Returning the current size of the waiting queue
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
#include <stddef.h>
#include <stdlib.h>
#include "queue.h"


queue_node_t* head = NULL;		//Queue head
queue_node_t* tail = NULL;		//Queue tail
int q_size = 0;				//Queue size



/**
* @brief Enqueues student id into the end of the waiting queue
*
* @param id const int, the id of the student to be enqueued
*/
void enqueue(const int id){
    queue_node_t* n = (queue_node_t*)malloc(sizeof(queue_node_t));  // new node
    if (n != NULL){             // if not null
        n->id = id;             // set id
        n->next = NULL;         // set next to null
        if (head == NULL){      // if list is empty
            head = n;
            tail = n;
        } else {                // if list is not empty
            tail->next = n;
            tail = n;
        }
        q_size++;               // increment size
    }
    return;
}


/**
* @brief Dequeues student id from the head of the waiting queue
*        Returns the value of the dequeued student id.
*
* @param none
*/
int dequeue(){
    if (q_size <= 0){               // queue empty / less than empty
        return -1;
    } else if ( q_size == 1){       // queue has 1 item
        int id = head->id;          // get id
        queue_node_t* temp = head;  // tempt to head
        head = NULL;                // nullify head and tail
        tail = NULL;
        free(temp);                 // free head/tail
        q_size--;                   // decrement size
        return id;                  // return id
    } else {                        // queue has more than 1 item
        int id = head->id;          // get id
        queue_node_t* temp = head;  // temp to current head
        head = head->next;          // move head to its next
        free(temp);                 // free old head
        q_size--;                   // decrement size
        return id;                  // return id
    }
    return -1;                      // error
}


/**
* @brief Returns size of the queue
*
* @param none
*/
int queue_size(){
    return q_size;
}
