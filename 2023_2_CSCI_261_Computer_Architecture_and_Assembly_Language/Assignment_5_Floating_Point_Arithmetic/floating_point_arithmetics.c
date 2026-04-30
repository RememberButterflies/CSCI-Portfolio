/**
 * @file floating_point_arithmetics.c
 * @author Patrick McGrath, CSCI 261, VIU
 * @version 1.0
 * @date December, 2023
 * 
 *  Assignment #5 Floating Point Arithmetic
 *  Copyright (C) 2023  Patrick McGrath
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "utility.h"
#include "convert.h"
#include "math.h"
#include "floating_point_arithmetics.h"
#include "integer_arithmetics.h"


/**
* @brief Takes a string and returns true if all chars are '0'
*
* @param number, the first string.
*/
int is_zero_fp(const char* number){
	size_t len = strlen(number);
	for (int i=0; i<len; i++){
		if (number[i] != '0'){
			return FALSE;
		}
	}
    return TRUE;
}




/**
* @brief Takes number and checks if its greater than BIAS_127_DECIMAL_MAX_VALUE
* prints error if so and returns true
*
* @param exponent_value, number being checked
*/
int is_exponent_overflow(int exponent_value){
	if (exponent_value > BIASED_127_DECIMAL_MAX_VALUE){
		// print statement
		return TRUE;
	}
    return FALSE;
}



/**
* @brief Takes number and checks if its less than BIAS_127_DECIMAL_MAX_VALUE
* prints error if so and returns true
*
* @param exponent_value, number being checked
*/
int is_exponent_underflow(int exponent_value){
	if (exponent_value < BIASED_127_DECIMAL_MIN_VALUE){
		// print statement
		return TRUE;
	}
    return FALSE;
}


/**
 * @brief Takes a string, makes a new string of same length, copies contents and returns new string
 * 
 * @param fp_number, the string being copied
*/
char* copy_floating_point(const char* fp_number){
	char* temp = malloc((strlen(fp_number)+1)*(sizeof(char)));
	for (int i=0; (i<(strlen(fp_number))); i++){
		temp[i] = fp_number[i];
	}
	temp[strlen(fp_number)] = '\0';
	return temp;
}


/**
 * @brief Makes a string, length BINARY_WORD_SIZE, assigns all characters to '0', returns it.
 * 
*/
char* create_zero_fp(){
	char* temp = malloc((BINARY_WORD_SIZE)*(sizeof(char)));
	for (int i=0; i<BINARY_WORD_SIZE; i++){
		temp[i] = '0';
	}
	temp[BINARY_WORD_SIZE] = '\0';
    return temp;
}


/**
 * @brief Makes a string, length BINARY_WORD_SIZE, 
 * 		assigns the characters to be "01111111100000000000000000000000"
 * 		returns it
 * 
*/
char* create_infinity_fp(){
	char* temp = malloc((BINARY_WORD_SIZE)*(sizeof(char)));
	int i = 0;
	temp[i] = '0';
	i++;
	while (i<9){
		temp[i] = '1';
		i++;
	}
	while (i<BINARY_WORD_SIZE){
		temp[i] = '0';
		i++;
	}
	temp[BINARY_WORD_SIZE] = '\0';
    return temp;
}



/**
 * @brief Takes a string, makes a new string, length BINARY_WORD_SIZE, 
 * 		assigns the first characters to be "000000001"
 * 		the remmaining characters are copied from fp_significan
 * 		returns new string
 * 
 * @param fp_significand, string being copied
*/
char* implicit_to_explicit_significand(const char* fp_significand){
	char* temp = malloc((BINARY_WORD_SIZE)*(sizeof(char)));
	int i = 0;
	while (i<8){
		temp[i] = '0';
		i++;
	}
	temp[i] = '1';
	i++;
	for (int j=0; j<FLOATING_POINT_SIGNIFICAND_DIGITS; j++, i++){
		temp[i] = fp_significand[j];
	}
	temp[BINARY_WORD_SIZE] = '\0';
	return temp;
}

/**
 * @brief Takes 2 strings representing 32 bit length signed IEEE 754 numbers
 * 	converts them to absolute value integers
 * 	calculates the difference between them (first - second)
 * 	returns the difference as integer
 * 
 * @param fp_number1, the first number being compared
 * @param fp_number2, the second number being compared
*/
int get_exponent_difference(const char* fp_number1, const char* fp_number2){
    char* temp1 = malloc((FLOATING_POINT_EXPONENT_DIGITS+1)*(sizeof(char)));
	char* temp2 = malloc((FLOATING_POINT_EXPONENT_DIGITS+1)*(sizeof(char)));
	for (int j=0; j<=(FLOATING_POINT_EXPONENT_DIGITS); j++){
		temp1[j] = fp_number1[j];
		temp2[j] = fp_number2[j];
	}
	temp1[FLOATING_POINT_EXPONENT_DIGITS+1] = '\0';
	temp2[FLOATING_POINT_EXPONENT_DIGITS+1] = '\0';
	int t1 = 0;
	int t2 = 0;
	for (int e=0, i=8; i>=1; i--, e++){
		if (temp1[i] == '1'){
			t1 = t1 + (pow(2, e));
		}
		if (temp2[i] == '1'){
			t2 = t2 + (pow(2, e));
		}
	}
	int t3 = t1-t2;
	free(temp1);
	free(temp2);
	return t3;
}

/**
 * @brief Takes a string and an integer. Shifters the characters in the string right
 *  a number of times equal to the integer
 * 
 * @param significand, the string being shifted
 * @param shift_length, the amount being shifted
*/
void align_significand_to_right(char* significand, int shift_length){
	for (int i=(BINARY_WORD_SIZE-1); i>(shift_length); i--){
		significand[i] = significand[i-shift_length];
	}

	for (int i=0; i<shift_length; i++){
		significand[1] = '0';
	}
    return;
}


/*
	End of completed functions
*/
