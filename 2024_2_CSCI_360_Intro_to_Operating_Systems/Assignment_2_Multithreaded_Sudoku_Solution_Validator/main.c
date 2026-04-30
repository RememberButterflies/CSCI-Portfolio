/**
 * @file main.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date October 8, 2024
 *
 * @brief Multithreaded Sudoku Solution Validator
 * 
 * Program checks whether a given sudoku solution is valid or invalid. 
 * User will provide the relative path of the file containing the sudoku puzzle.
 * The user will provide this as the only parameter of the program when executed in command line.
 * If no filename is provided, the user is informed of this. 
 * The program checks the validity of the puzzle solution by checking the requirements in seperate threads.
 * The requirements are to have 9 columns and 9 rows and in each column, row and 3x3 subgrid the numbers 1-9 without repition.
 * This will result in 27 threads and 27 checks.
 * The file will have each each row as a line in the file. Then each number will be comma-seperated.
 * After threads have completed, the program will display the results of all 27 checks and whether the whole puzzle is valid.
 * The program will also save the results to a log file.
 * Finally the prgram exits.
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

	// Header files
#include "sudoku_checker.h"
#include "sudoku_logger.h"
#include "sudoku_thread.h"
#include "sudoku_param.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//Use following global variables in your code
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]; 			// In memory solution of a sudoku puzzle
int status_map[NUMBER_OF_THREADS];       		// Status maps updated by corresponding thread
char logs[LOG_SIZE][LOG_MESSAGE_MAX_LENGTH];	// In memory logs updated by all threads
char filename[SUDOKU_FILE_LINE_LENGTH_MAX]; 	// memory to hold user entered filename



int main(int argc, char** argv) {



	// initialize filename to empty string
	filename[0] = '\0';

	//Check whether a command line argument has been passed or not.
	if (argc < 2){
		// no filename provided, inform user
		printf("Filename of sudoku needed to check validity. \n");
	} else {

		// run the rest of the program

		//set filename to provided one
		strcpy(filename, argv[1]);

		// read sudoku from file 
		read_from_file(filename);

		// display sudoku to user
		show_puzzle();

		//Initialize all elements of threat status map to 1
		init_status_map(1);

		//Declare an array of pthread_t threads and an array of thread_parameter_t thread_parameters of dimension NUMBER_OF_THREADS.
		//pthread_t threads[NUMBER_OF_THREADS];
	//	thread_parameter_t thread_parameters[NUMBER_OF_THREADS];


		// thread tracker int*
		// tracks number of threads, from 0 to 26
		// 0-8 = columns, 9-17 = rows, 18-26 = subgrids, 27 = final print statement
		int* thread_tracker = (int*)malloc(sizeof(int));
		*thread_tracker = 0;

		// thread parameter array
		// pointer array, with memory alloated for 1 thread_parameter_t for each of the 27 threads
		thread_parameter_t** thread_parameters = (thread_parameter_t**)malloc(NUMBER_OF_THREADS * sizeof(thread_parameter_t*));

		// pthread_t array
		// array with memory allocated for 27 pthread_t's
		pthread_t* threads = (pthread_t*)malloc(NUMBER_OF_THREADS * sizeof(pthread_t));

		// create threads for columns, rows, and subgrids
		create_column_threads(thread_tracker, PUZZLE_SIZE, thread_parameters, threads);
		create_row_threads(thread_tracker, PUZZLE_SIZE, thread_parameters, threads);
		create_subgrid_threads(thread_tracker, PUZZLE_SIZE, thread_parameters, threads);


		//Wait for all column, row, and subgrid threads to complete their execution 
		for(int i=0; i<NUMBER_OF_THREADS; i++ ) {
			pthread_join(threads[i], NULL);
		}


		//Check the results from all threads through status map		
		int status = check_status_map();

		
		//Log whether the solution is valid or not	
		if (status == 1 ){
			// puzzle valid
			log_message(LOG_LABEL_VALID, LOG_MESSAGE_FORMAT_SUDOKU, (*thread_tracker));
		} else {
			// puzzle not valid
			log_message(LOG_LABEL_INVALID, LOG_MESSAGE_FORMAT_SUDOKU, (*thread_tracker));
		}
		
		

		//Release dynamically allocated memory from the thread parameters
		clear_thread_parameters(thread_parameters, NUMBER_OF_THREADS);

		//Display and save log messages
		log_show();
		log_save();


		// free remaining  memory
		free(thread_tracker);
		free(threads);
	}

	// End program	
	return 0;
}