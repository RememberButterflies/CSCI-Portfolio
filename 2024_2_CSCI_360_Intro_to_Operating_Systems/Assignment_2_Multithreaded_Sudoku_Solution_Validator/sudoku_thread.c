/**
 * @file sudoku_thread.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date October 8, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      Allocating memory for individual elements of the thread parameters array.
 *      Clearing the memory from the thread parameters array,
 *      Creating individual threads for checking if rows are valid,
 *      Creating individual threads for checking if columns are valid,
 *      Creating individual threads for checking if subgrids are valid,
 *      Performing the row check in a thread,
 *      Performing the column check in a thread and
 *      Performing the subgrid check in a thread.
 * 
 * File also contains declaration of the arrays for the solution and the results of the puzzle checks from main
 *
 * 
 *      Assignment #2 Multithreaded Sudoku Solution Validator
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


//Include required library header files

//Include required custom header files


#include "sudoku_thread.h"
#include "sudoku_param.h"
#include "sudoku_logger.h"
#include <stdio.h>
#include <stdlib.h>


//Use following global variables declared in main.c file
extern int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]; 		// In memory solutiona of a sudoku puzzle
extern int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread










/**
* @brief Allocates memory for individual elements of the thread parameters array.
*
* @param thread_no const int, the number of the thread
* @param row const int, the row of the start of the check
* @param col const int, the column of the start of the check
*/
thread_parameter_t* create_thread_parameter(const int thread_no, const int row, const int col){

    //Allocate memory
    thread_parameter_t* t = (thread_parameter_t*)malloc(sizeof(thread_parameter_t));
    if (t == NULL){
        return NULL;
    } else {
        //Assign values
        t->thread_no = thread_no;
        t->puzzle_row = row;
        t->puzzle_col = col;
        // return pointer
        return t;
    }

    // return
    return NULL;
}







/**
* @brief Deallocates memory from the thread parameters array.
*
* @param thread_params, thread_parameter_t**, the array of thread parameters
* @param number_of_thread_parameters, const int, the size of the array
*/
void clear_thread_parameters(thread_parameter_t** thread_params, const int number_of_thread_parameters){

    //Release memory
    for (int i = 0; i < number_of_thread_parameters; i++){
        free(thread_params[i]);
    }
    return;
}















/**
* @brief Create individual threads for checking if columns are valid.
*        Each thread calls col_thread() function to check if that column is valid, using the values from its element in the thread parameters array.
*        col_thread will then close the thread after it has checked the column.
*        Each thread is placed in the threads array.
*        The thread tracker is incremented. 
*
* @param thread_tracker int*, pointer to the value of the thread tracker, keeps track of which thread is being created
* @param number_of_columns const int, the number of columns in the puzzle (9)
* @param thread_params thread_parameter_t**, the array of thread parameters
* @param threads pthread_t*, the array of threads
*/
void create_column_threads(int* thread_tracker, const int number_of_columns, thread_parameter_t** thread_params, pthread_t* threads){

    //Use 'thread_tracker' to track how many thread is being created in the application.
    //Use the current value of 'thread_tracker' as the thread number of the current thread that is going to be created.
    //Increment 'thread_tracker' value after a thread has been created successfully.
    //Create 'number_of_columns' column threads; one thread for each column.    
    for (int c = 0; c < number_of_columns; c++){

        //Create a thread parameter 'thread_parameter_t' by dynamically allocating memory and assigning appropriate values
        //to its 'thread_no', 'puzzle_row', and 'puzzle_col' fileds. Call create_thread_parameter() function for this.
        thread_parameter_t* t = create_thread_parameter(*thread_tracker, 0, c);

        //Assign new thread parameter to the appropriate element of 'thread_params'. This 'thread_params' keeps track of
        //all thread parameters created dynamically for all the threads in the application, so that dynamically allocated
        //memory can be released later before the application terminates to avoid memory leak.
        thread_params[*thread_tracker] = t;

        //Create a column thread by calling pthread_create() library function and using appropriate element reference of 
        //thread from 'threads', which keeps track of all the threads created in the application. Use 'col_thread()' function 
        //as the thread function and the thread parameter created in step 2 as its parameter.
        if(pthread_create(&threads[*thread_tracker], NULL, col_thread, (void*) thread_params[*thread_tracker]) != 0) {
            fprintf(stderr, "System Error! failed to create a thread.\n");
            exit(EXIT_FAILURE);
            }
            
        //Increment thread_tracker
        (*thread_tracker)++;
        
        }

    // return
    return;
}





/**
* @brief Create individual threads for checking if rows are valid.
*        Each thread calls row_thread() function to check if that row is valid, using the values from its element in the thread parameters array.
*        row_thread() will then close the thread after it has checked the row.
*        Each thread is placed in the threads array.
*        The thread tracker is incremented. 
*
* @param thread_tracker int*, pointer to the value of the thread tracker, keeps track of which thread is being created
* @param number_of_rows const int, the number of rows in the puzzle (9)
* @param thread_params thread_parameter_t**, the array of thread parameters
* @param threads pthread_t*, the array of threads
*/
void create_row_threads(int* thread_tracker, const int number_of_rows, thread_parameter_t** thread_params, pthread_t* threads){

    //Use 'thread_tracker' to track how many thread is being created in the application.
    //Use the current value of 'thread_tracker' as the thread number of the current thread that is going to be created.
    //Increment 'thread_tracker' value after a thread has been created successfully.
    //Create 'number_of_rows' row threads; one thread for each row
    for (int r = 0; r < number_of_rows; r++){

        //Create a thread parameter 'thread_parameter_t' by dynamically allocating memory and assigning appropriate values
        //to its 'thread_no', 'puzzle_row', and 'puzzle_col' fileds. Call create_thread_parameter() function for this.
        thread_parameter_t* t = create_thread_parameter(*thread_tracker, r, 0);


        //Assign new thread parameter to the appropriate element of 'thread_params'. This 'thread_params' keeps track of
        //all thread parameters created dynamically for all the threads in the application, so that dynamically allocated
        //memory can be released later before the application terminates to avoid memory leak.
        thread_params[*thread_tracker] = t;


        //Create a row thread by calling pthread_create() library function and using appropriate element reference of 
        //thread from 'threads', which keeps track of all the threads created in the application. Use 'row_thread()' function 
        //as the thread function and the thread parameter created in step 2 as its parameter.
        if(pthread_create(&threads[*thread_tracker], NULL, row_thread, (void*) thread_params[*thread_tracker]) != 0) {
            fprintf(stderr, "System Error! failed to create a thread.\n");
            exit(EXIT_FAILURE);
            }
            
        //Increment thread_tracker
        (*thread_tracker)++;
        
        }

    // return
    return;
}





/**
* @brief Create individual threads for checking if subgrid are valid.
*        Each thread calls subgrid_thread() function to check if that subgrid is valid, using the values from its element in the thread parameters array.
*        subgrid_thread() will then close the thread after it has checked the subgrid.
*        Each thread is placed in the threads array.
*        The thread tracker is incremented. 
*
* @param thread_tracker int*, pointer to the value of the thread tracker, keeps track of which thread is being created
* @param number_of_subgrids const int, the number of subgrids in the puzzle (9)
* @param thread_params thread_parameter_t**, the array of thread parameters
* @param threads pthread_t*, the array of threads
*/
void create_subgrid_threads(int* thread_tracker, const int number_of_subgrids, thread_parameter_t** thread_params, pthread_t* threads){

    //Use 'thread_tracker' to track how many thread is being created in the application.
    //Use the current value of 'thread_tracker' as the thread number of the current thread that is going to be created.
    //Increment 'thread_tracker' value after a thread has been created successfully.
    //Create 'number_of_subgrids' subgrid threads; one thread for each subgrid
    for (int r = 0; r < 3; r++){

        for (int c = 0; c < 3; c++){

            //Create a thread parameter 'thread_parameter_t' by dynamically allocating memory and assigning appropriate values
            //to its 'thread_no', 'puzzle_row', and 'puzzle_col' fileds. Call create_thread_parameter() function for this.
            thread_parameter_t* t = create_thread_parameter(*thread_tracker, r*3, c*3);

            //Assign new thread parameter to the appropriate element of 'thread_params'. This 'thread_params' keeps track of
            //all thread parameters created dynamically for all the threads in the application, so that dynamically allocated
            //memory can be released later before the application terminates to avoid memory leak.
            thread_params[*thread_tracker] = t;
            
            //Create a subgrid thread by calling pthread_create() library function and using appropriate element reference of 
            //thread from 'threads', which keeps track of all the threads created in the application. Use 'row_thread()' function 
            //as the thread function and the thread parameter created in step 2 as its parameter.
            if(pthread_create(&threads[*thread_tracker], NULL, subgrid_thread, (void*) thread_params[*thread_tracker]) != 0) {
                fprintf(stderr, "System Error! failed to create a thread.\n");
                exit(EXIT_FAILURE);
            }
            
            //Increment thread_tracker
            (*thread_tracker)++;
            
        }
    }

    // return
    return;
}



/**
* @brief Execute a check in thread created by create_row_threads() on an individual row specified in param. 
*        Create and log message based on the result of the check.
*        After execution, the thread will close.
*
* @param param void*, the functions parameter. A pointer to a thread_parameter_t struct
*/
void* row_thread(void* param){

    // cast the void* param to its expected type, thread_parameter_t*
    thread_parameter_t* t = (thread_parameter_t*) param;

    // array for counting how many of each digit is present
    // and temp ints for param's values
    // and return result integer. 1 = valid, 0 = invalid. assume all valid until checking part
    int digits[9] = {0};
    int row = t->puzzle_row;
    int thread_no = t->thread_no;
    int result = 1;

    // populate digits
    for (int c = 0; c < PUZZLE_SIZE; c++){
        int t = puzzle[row][c];     // get puzzle element value
        digits[t-1]++;              // increment t's value in digits array
    }

    // check digits for validity
    for (int i = 0; i < PUZZLE_SIZE; i++){
        if (digits[i] != 1){
            result = 0;
        }
    }

    // Set the appropriate status value in status map.
    status_map[thread_no] = result;




    // Create an appropriate log message by caling create_message() function and insert the message into the log by
    // calling log_message().
    char message[LOG_MESSAGE_MAX_LENGTH];                   // message buffer
    create_message(message, "Row", row, 0, thread_no);      // create message
    if (result == 0){
        // invalid
        log_message(LOG_LABEL_INVALID, message, thread_no);
    } else {
        // valid
        log_message(LOG_LABEL_VALID, message, thread_no);
    }




    // Call pthread_exit() library function to exit from thread execution.
    pthread_exit(NULL);

    return NULL;
}



/**
* @brief Execute a check in thread created by create_col_threads() on an individual col specified in param. 
*        Create and log message based on the result of the check.
*        After execution, the thread will close.
*
* @param param void*, the functions parameter. A pointer to a thread_parameter_t struct
*/
void* col_thread(void* param){

    // cast the void* param to its expected type, thread_parameter_t*
    thread_parameter_t* t = (thread_parameter_t*) param;
    // array for counting how many of each digit is present
    // and temp ints for param's values
    // and return result integer. 1 = valid, 0 = invalid. assume all valid until checking part
    int digits[9] = {0};
    int col = t->puzzle_col;
    int thread_no = t->thread_no;
    int result = 1;

    // populate digits
    for (int r = 0; r < PUZZLE_SIZE; r++){
        int t = puzzle[r][col];     // get puzzle element value
        digits[t-1]++;              // increment t's value in digits array
    }

    // check digits for validity
    for (int i = 0; i < PUZZLE_SIZE; i++){
        if (digits[i] != 1){
            result = 0;
        }
    }
    // Set the appropriate status value in status map.
    status_map[thread_no] = result;




    // Create an appropriate log message by caling create_message() function and insert the message into the log by
    // calling log_message().
    char message[LOG_MESSAGE_MAX_LENGTH];                   // message buffer
    create_message(message, "Column", 0, col, thread_no);      // create message
    if (result == 0){
        // invalid
        log_message(LOG_LABEL_INVALID, message, thread_no);
    } else {
        // valid
        log_message(LOG_LABEL_VALID, message, thread_no);
    }




    // Call pthread_exit() library function to exit from thread execution.
    pthread_exit(NULL);
    return NULL;
}



/**
* @brief Execute a check in thread created by create_subgrid_threads() on an individual subgrid specified in param. 
*        Create and log message based on the result of the check.
*        After execution, the thread will close.
*
* @param param void*, the functions parameter. A pointer to a thread_parameter_t struct
*/
void* subgrid_thread(void* param){

    // cast the void* param to its expected type, thread_parameter_t*
    thread_parameter_t* t = (thread_parameter_t*) param;
    // array for counting how many of each digit is present
    // and temp ints for param's values
    // and return result integer. 1 = valid, 0 = invalid. assume all valid until checking part
    int digits[9] = {0};
    int row = t->puzzle_row;
    int col = t->puzzle_col;
    int thread_no = t->thread_no;
    int result = 1;

    //populate digits, row by row
    for (int r = row; r < row+3; r++){
        for (int c = col; c < col+3; c++){
            int t = puzzle[r][c];     // get puzzle element value
            digits[t-1]++;              // increment t's value in digits array
        }
    }
    
    // check digits for validity
    for (int i = 0; i < PUZZLE_SIZE; i++){
        if (digits[i] != 1){
            result = 0;
        }
    }
    // Set the appropriate status value in status map.
    status_map[thread_no] = result;


    // Create an appropriate log message by caling create_message() function and insert the message into the log by
    // calling log_message().
    char message[LOG_MESSAGE_MAX_LENGTH];                   // message buffer
    create_message(message, "Subgrid", row, col, thread_no);      // create message
    if (result == 0){
        // invalid
        log_message(LOG_LABEL_INVALID, message, thread_no);
    } else {
        // valid
        log_message(LOG_LABEL_VALID, message, thread_no);
    }




    // Call pthread_exit() library function to exit from thread execution.
    pthread_exit(NULL);

    return NULL;
}