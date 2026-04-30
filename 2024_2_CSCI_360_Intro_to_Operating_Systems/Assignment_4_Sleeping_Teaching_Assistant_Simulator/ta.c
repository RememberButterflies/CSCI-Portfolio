/**
 * @file ta.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - Simulating TA helping
 *      - Running TA thread
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
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "ta.h"
#include "logger.h"
#include "config.h"
#include "queue.h"



/**
* @brief Simulates a TA heling a student and logs the event in the log array, 
        using MUTEX lock to prevent race condition on the log with other events.
*
* @param ta_id const int, the id of the TA helping the student
* @param st_id const int, the id of the student being helped
* @param help_time const int, the time the TA will spend helping the student
*/
void help_student(const int ta_id, const int st_id, const int help_time){

    // Memory for log message
    char buffer[LOG_MESSAGE_MAX_LENGTH];

    // Create message to log
    create_log_message3(buffer, LOG_MESSAGE_FORMAT_HELPING, ta_id, st_id, help_time);

    // Lock the log mutex
    pthread_mutex_lock(&mutex_lock_log);

    // Log the message
    log_message(LOG_LABEL_HELPING, buffer);

    // Unlock the log mutex
    pthread_mutex_unlock(&mutex_lock_log);

    // Simulate helping by sleeping the thread for the specified help time
    sleep(help_time);
    return;
}






/**
* @brief Simulates a TA cycling between sleeping and helping students if there are any in the queue to help. 
        Mutex is used to access the queue & log array and semaphores are used to signal the TA & students.
*
* @param param void*, the id of the TA
*/
void *run_ta(void *param){


    // Infinite loop that will be broken by the main thread
    while(1){

        // Lock the queue mutex
        pthread_mutex_lock(&mutex_lock_queue);

        // Check the size of the queue
        if (queue_size() == 0){

            // Unlock the queue mutex
            pthread_mutex_unlock(&mutex_lock_queue);

            // Memory for log message
            char buffer[LOG_MESSAGE_MAX_LENGTH];

            // Create message to log
            create_log_message1(buffer, LOG_MESSAGE_FORMAT_SLEEPING, *(int*)param);

            // Lock the log mutex
            pthread_mutex_lock(&mutex_lock_log);

            // Log the message
            log_message(LOG_LABEL_SLEEPING, buffer);

            // Unlock the log mutex
            pthread_mutex_unlock(&mutex_lock_log);

            // Wait for a student to signal the TA
            sem_wait(&student_sem);
        } else {

            // Dequeue the student
            int id = dequeue();

            // Unlock the queue mutex
            pthread_mutex_unlock(&mutex_lock_queue);

            // Random amount of time to help the student
            int rannum = (random() % MAX_HELP_TIME) + 1;

            // Help the student
            help_student(*(int*)param, id, rannum);

            // Signal the student that the TA is ready to help
            sem_post(&ta_sem);

            // Wait for the student to signal the TA
            sem_wait(&student_sem);
        }
    }
    return NULL;
}