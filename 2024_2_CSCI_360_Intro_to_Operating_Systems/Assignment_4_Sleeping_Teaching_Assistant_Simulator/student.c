/**
 * @file student.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - Simulating student programming
 *      - Running student thread
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
#include <stdlib.h>
#include <unistd.h>
#include "student.h"
#include "logger.h"
#include "config.h"
#include "queue.h"


/**
* @brief Simulates a student programming and logs the event in the log array, 
        using MUTEX lock to prevent race condition on the log with other events.
*
* @param student_id const int, the id of the student programming
* @param programing_time const int, the time the student will spend programming
*/
void programming(const int student_id, const int programing_time){

    // Memory for log message
    char buffer[LOG_MESSAGE_MAX_LENGTH];

    // Create message to log
    create_log_message2(buffer, LOG_MESSAGE_FORMAT_PROGRAMMING, student_id, programing_time);

    // Lock the log mutex
    pthread_mutex_lock(&mutex_lock_log);

    // Log the message
    log_message(LOG_LABEL_PROGRAMMING, buffer);

    // Unlock the log mutex
    pthread_mutex_unlock(&mutex_lock_log);

    // Simulate programming by sleeping the thread for specified programming time
    sleep(programing_time);
    return;
}


/**
* @brief Simulates a student cycling through programming, waiting for help and getting help up.
*        The student will ultimately receive help the number of times specified by NUMBER_OF_STUDENT_CYCLES.
        Mutex is used to access the queue & log array and semaphores are used to signal the TA & students.
*
* @param param void*, the id of the student
*/
void *run_student(void *param){


    // Initialize student state and loop count
    student_state_t state = UNKNOWN;
    int loops = 0;

    // While the maximum number of loops hasnt been reached
    while (loops < NUMBER_OF_STUDENT_CYCLES){

        // If the student is not waiting, start programming
        if (state != WAITING){

            // Generate a random programming time
            int rannum = (random() % MAX_PROGRAM_TIME) + 1;

            // Start programming
            programming(*(int*)param, rannum);

            // Set state to programming
            state = PROGRAMMING;

            // Lock the queue mutex
            pthread_mutex_lock(&mutex_lock_queue);

            // Check the queue size
            // If there is room in the queue,
            if (queue_size() < NUMBER_OF_SEATS){

                // Enqueue the student
                enqueue(*(int*)param);

                //Unlock the queue mutex
                pthread_mutex_unlock(&mutex_lock_queue);

                // Message buffer for log message
                char buffer[LOG_MESSAGE_MAX_LENGTH];

                // Create message to log, waiting
                create_log_message2(buffer, LOG_MESSAGE_FORMAT_WAITING, *(int*)param, queue_size());

                // Lock the log mutex
                pthread_mutex_lock(&mutex_lock_log);

                // Log the message
                log_message(LOG_LABEL_WAITING, buffer);

                // Unlock the log mutex
                pthread_mutex_unlock(&mutex_lock_log);

                // Notify the TA that the student is waiting
                sem_post(&student_sem);
                sem_wait(&ta_sem);

                // Set state to getting help
                state = GETTING_HELP;

                // Message buffer for log message, getting help
                char buffer1[LOG_MESSAGE_MAX_LENGTH];

                // Create message to log, getting help
                create_log_message1(buffer1, LOG_MESSAGE_FORMAT_GETTING_HELP, *(int*)param);

                // Lock the log mutex
                pthread_mutex_lock(&mutex_lock_log);

                // Log the message
                log_message(LOG_LABEL_GETTING_HELP, buffer1);

                // Unlock the log mutex
                pthread_mutex_unlock(&mutex_lock_log);
                loops++;
            } else {
                // Queue is full.
                // Unlock the queue mutex
                pthread_mutex_unlock(&mutex_lock_queue);

                // Message buffer for log message, no waiting room
                char buffer2[LOG_MESSAGE_MAX_LENGTH];

                // Create message to log, no waiting room
                create_log_message2(buffer2, LOG_MESSAGE_FORMAT_NO_WAITING_ROOM, *(int*)param, queue_size());

                // Lock the log mutex
                pthread_mutex_lock(&mutex_lock_log);

                // Log the message
                log_message(LOG_LABEL_WAITING, buffer2);

                // Unlock the log mutex
                pthread_mutex_unlock(&mutex_lock_log);
            }
        }

    }

    return NULL;
}