/**
 * @file sudoku_checker.c
 * @author Patrick McGrath, CSCI 360, VIU
 * @version 1.0.0
 * @date October 8, 2024
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      reading a sudoku solution from file, 
 *      displaying the solution from memory,
 *      creating an array for the checks on the solution and
 *      checking the results of the puzzle checks are all valid or not.
 * 
 * File also contains declaration of the arrays for the solution and the results of the puzzle checks from main
 * 
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
#include "sudoku_param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>



//Use following global variables that have been declared in main.c file.
extern int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]; 		// Im memory solutiona of a sudoku puzzle
extern int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread



/**
* @brief Reads sudoku solution from file and places integer values into puzzle array.
*
* @param filename char* relative location of file to be read
*/
void read_from_file(char* filename){

    // open file
    FILE *file = fopen(filename, "r");
    // check if actually opened
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // read line by line
    // then for each line, parse the values
    // and store values in puzzle[][]
    int row = 0;                                    // row index
    int col = 0;                                    // column index                     
    char *line = NULL;                              // line buffer                        
    size_t len = 0;                                 // length of line buffer
    ssize_t read;                                   // return value of getline()
    read = getline(&line, &len, file);              // read first line

    // if the first line read correctly and while there are lines to read, and the puzzle has not gone past its max number of rows
    while((read != -1) && (row < PUZZLE_SIZE)){

        // parse line, tokenizing by comma
        char* token = strtok(line, ",");

        // while there are tokens, and the puzzle has not gone past its max number of columns,
        // fill current row in puzzle with current line from file, character by character, after converting to integers
        while ((token != NULL) && (col < PUZZLE_SIZE)){

            puzzle[row][col]= atoi(token);
            col++;
            token = strtok(NULL, ",");
        }

        // get next line, increment row and reset column
        read = getline(&line, &len, file);
        row++;
        col = 0;
    }



    // free memory, close file and return
    free(line);
    fclose(file);
    return;
}


/**
* @brief Displays values of in-memory puzzle array to user
*
* @param NONE
*/
void show_puzzle(){

    //print initial header
    printf("Sudoku Puzzle:\n");

    // row and column counters
    int row = 0;
    int col = 0;

    // while there are rows to print
    while (row < PUZZLE_SIZE){

        //for each row, print each column
        while (col < PUZZLE_SIZE){
            printf("%d ", puzzle[row][col]);
            col++;
        }
        //print new line, increment rows and reset columns
        printf("\n");
        row++;
        col = 0;
    }

    //return
    return;
}


/**
* @brief Sets each element of the status array to the given value.
*
* @param value const int, the value to set all elements of the status array to
*/
void init_status_map(const int value){

    // set each element in status_map[NUMBER_OF_THREADS] to value
    for (int i=0; i<NUMBER_OF_THREADS; i++){
        status_map[i] = value;
    }

    //return
    return;
}



/**
* @brief Checks whether every element in the status array is set to 1 or not.
*        If all elements are set to 1, return 1, else return 0.
*
* @param NONE
*/
int check_status_map(){

    // return value, assume ll elements are set to 1
    int r = 1;

    // check each element in status_map[NUMBER_OF_THREADS] to see if it is not 1.
    // if it isnt 1, set r to 0, else, keep checking.
    for (int i=0; i<NUMBER_OF_THREADS; i++){
        if (status_map[i] != 1){
            r = 0;
        }
    }

    //return
    return r;
}