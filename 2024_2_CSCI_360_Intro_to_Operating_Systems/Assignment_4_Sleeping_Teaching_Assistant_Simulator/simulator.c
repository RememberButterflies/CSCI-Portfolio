/**
 * @file simulator.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - Initializing the simulator variables
 *      - Cleaning up the simulator variables
 *      - Creating TA threads
 *      - Creating student threads
 *      - The main function
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
#include <time.h>
#include <stdlib.h>
#include "simulator.h"
#include "ta.h"
#include "student.h"
#include "logger.h"



/**
* @brief Initializes the simulator variables.
*        Initializes mutex locks for queue and log.
*        Initializes semaphores for students and TAs.
*        Initializes student and TA ids.
*        Initializes random number generator.
*
* @param none
*/
void init(){

    //Initialize mutex locks by calling pthread_mutex_init() library function on each lock.
    pthread_mutex_init(&mutex_lock_queue, NULL);
    pthread_mutex_init(&mutex_lock_log, NULL);

    //Initialize both student_sem and ta_sem semaphores by calling sem_init() system call on each semaphore.
    sem_init(&student_sem, 0, 0);
    sem_init(&ta_sem, 0, 0);

    // Initialize student and TA ids
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        student_id[i] = i+1;
    }
    for (int j = 0; j < NUMBER_OF_TAS; j++) {
        ta_id[j] = j+1;
    }

    // Initialize random number generator seed
    srandom(time(NULL));


    return;
}



/**
* @brief Cleans up the simulator variables.
*        Destroys mutex locks for queue and log.
*        Destroys semaphores for students and TAs.
*
* @param none
*/
void cleanup(){
    //Destroy mutex locks by calling pthread_mutex_destroy() library function on each lock.
    pthread_mutex_destroy(&mutex_lock_queue);
    pthread_mutex_destroy(&mutex_lock_log);

    //Destroy both student_sem and ta_sem semaphores by calling sem_destroy() library function on each semaphore.
    sem_destroy(&student_sem);
    sem_destroy(&ta_sem);

    return;
}




/**
* @brief Creates all TA threads, running 'run_ta' function with the ta_id as the parameter.
*
* @param none
*/
void create_tas(){

    // create ta threads
    for (int i = 0; i < NUMBER_OF_TAS; i++) {
        pthread_create(&tas[i], NULL, run_ta, (void*)&ta_id[i]);
    }
    return;
}

/**
* @brief Creates all TA threads, running 'run_studnet' function with the student_id as the parameter.
*
* @param none
*/
void create_students(){

    // create sudent threads
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        pthread_create(&students[i], NULL, run_student, (void*)&student_id[i]);
    }
    return;
}


/**
* @brief Main function of program.
*        Initializes the simulator variables.
*        Creates TA and student threads.
*        Joins on student threads.
*        Cancels TA threads after all student threads.
*        Shows log.
*        Saves log.
*        Cleans up simulator variables.
*
* @param none
*/
int main(){

    // initialize simulator
    init();

    // create threads for TAs and students
    create_tas();
    create_students();

    // join on student threads
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    // cancel ta threads
    for (int i = 0; i < NUMBER_OF_TAS; i++) {
        pthread_cancel(tas[i]);
    }

    log_show();     // show log
    log_save();     // save log
    cleanup();      // cleanup

    return 0;
}