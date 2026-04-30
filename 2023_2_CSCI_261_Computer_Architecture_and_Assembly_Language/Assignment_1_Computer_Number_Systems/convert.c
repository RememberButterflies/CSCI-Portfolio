/**
 * @file utility.c
 * @author Patrick McGrath, VIU
 * @version 1.0
 * @date September 26, 2023
 *  Assignment #1 Computer Number Systems Application
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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "../include/convert.h"
#include "../include/utility.h"


/**
* @brief Takes an integer number as string and a length as an int.
* converts the value of the number from decimal to binary. Then
* if it is shorter than the size, the front is padded with 0's until
* equal size. Then returned
*
* @param str number, string to be converted.
* @param int word_size, size of output string 
*/
char* integer_to_binary(const char* number, int word_size){

	// check if number is NULL
	if (number == 0){
		return FALSE;
	}
	// check if number is no length
	int len = 0;
	if (number[0] != '\0'){
		len = strlen(number);
	}

	// create temp string
	char* temp = malloc((word_size+1)*(sizeof(char)));
	// check if temp is NULL
	if (temp == 0){
		return FALSE;
	}
	// for loop for setting every character to '0'
	for(int i = 0; i < word_size; i++){
		temp[i] = '0';
	}
	// adding terminator
	temp[word_size] = number[len];




	//convert number to binary
	//numi is number converted to a long int
	//strtol is used, but its base remains 10 for excercise purposes.
	//i is the position in temp being changed
	//done is an escape value
	//r is int for dumping remainder. r is checked for value
	//because temp doesnt want 0/1, it wants '0'/'1'.
	//temp is already all 0's, so only 1 will be updated.
	//while loop while take numi mod 2 and
	//place it in temp[i]. numi's then halved.
	//done is activated if after this numi is 0.
	char* endptr;
	long int numi = strtol(number, &endptr, 10);
	int i = word_size - 1;
	int r = -1;
	int done = 0;
	while(done == 0){
		r = numi % 2;
		if(r == 1){
			temp[i] = '1';
		} 
		numi = numi / 2;
		if(numi == 0){
			done++;
		}
		i--;
	}
	

	// temp was updated backwards, with terminator added first
	// return temp
	return temp;
}


/**
* @brief Takes an integer number as string and a length as an int.
* converts the value of the number from decimal to binary. Then
* if it is shorter than the size, the front is padded with 0's until
* equal size. Then returned
*
* @param str number, string to be converted.
* @param int word_size, size of output string 
*/
char* decimal_to_binary(const char* number, int word_size){
	// check if number is NULL
	if (number == 0){
		return FALSE;
	}
	// check if number has no length
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// check if word_size is negative
	if (word_size < 0){
		return FALSE;
	}

	// check if number isnt valid decimal
	if ((is_decimal(number)) == 0){
		printf("decimal_to_binary failed; %s is not decimal\n", number);
		return NULL;
	}

	// tests passed
	// conversion section
	char* temp = integer_to_binary(number, word_size);
	if (temp == 0){
		return FALSE;
	}
	return temp;

}

/**
* @brief Takes a binary integer number as string and a length as an int.
* converts the value of the number from binary to decimal. Then converts
* that to a string of length word_size and returns it
*
* @param str number, string to be converted.
* @param int word_size, size of output string 
*/
char* binary_to_integer(const char* number,  int word_size){

	// check if number is NULL
	if (number == 0){
		return FALSE;
	}
	// check if number is no length
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// temp string, size = word_size+1
	char* temp = malloc((word_size+1)*(sizeof(char)));
	// check if temp is NULL
	if (temp == 0){
		return FALSE;
	}


	//conversion section
	//binary to decimal
	//long int t is running total
	//e is current exponent of 2
	//i is the position in number currently being converted
	long int t = 0;
	int e = 0;
	for(int i = len-1; i >= 0; i--){
		// t equals itself plus 
		// number[i] * 2^e
		// l is temp int for current value being added
		long int l = 0;
		// number[i] is checked if its 1 or not
		// 0 is ignored, 0 * 2^anything = 0
		if (number[i] == '1'){
			// l is 1*2^current exponent
			l = (pow(2,e));
		}
		// t is updated to add current l
		t = t + l;
		// exponent is updated
		e++;
	}
	// t should be decimal conversion as long int
	// first check if t equals 0
	if (t == 0){
		temp[0] = '0';
		temp[1] = number[len];
		return temp;
	}
	// convert t to string
	// loop for finding exponent of base of largest digit in t
	// s is exponent of bases of largest digit, also length needed
	// continually divide a copy of t until it equals 0
	// for each time, increase s.
	long int t1 = t;
	int s = 0;
	for(int z = 0; t1 != 0; t1 = t1 / 10){
	       z++;
	       s = z;
	}
	// populate temp from right
	// r is current remainder
	// i is position in temp being updated
	// switch case used to check value of r and update temp
	int r = 0;
	int i = s-1;
	while (i >= 0){
		r = t % 10;
		switch(r){
			case 0:
				temp[i] = '0';
				break;
			case 1:
				temp[i] = '1';
				break;
			case 2:
				temp[i] = '2';
				break;
			case 3:
				temp[i] = '3';
				break;
			case 4:
				temp[i] = '4';
				break;
			case 5:
				temp[i] = '5';
				break;
			case 6:
				temp[i] = '6';
				break;
			case 7:
				temp[i] = '7';
				break;
			case 8:
				temp[i] = '8';
				break;
			case 9:
				temp[i] = '9';
				break;
			default:
				break;
		}
		t = t/10;
		i--;
	}
	// terminator added, and temp returned
	temp[s] = number[len];
	return temp;

}

/**
* @brief Takes a binary integer number as string and a length as an int.
* converts the value of the number from binary to decimal. Then converts
* that to a string of length word_size and returns it
*
* @param str number, string to be converted.
* @param int word_size, size of output string 
*/
char* binary_to_decimal(const char* number,  int word_size){
	// check if number is NULL
	if (number == 0){
		return FALSE;
	}
	// check if number is no length
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// check if number is valid binary or not
	if ((is_binary(number)) == 0){
		printf("binary_to_decimal failed: %s is not binary\n", number);
		return NULL;
	}

	//number is valid binary
	char* temp = binary_to_integer(number, word_size);
	if (temp == 0){
		return FALSE;
	}
	return temp;
}

/**
* @brief Takes an integer portion of a fixed point number as string
* Converts the value of the number from decimal to binary. That string
* extended with 16x0's on the right side. then returned
*
* @param str number, string to be converted.
*/
char* integer_part_to_binary(const char* number){

	//check if number is null
	if (number == 0){
		return FALSE;
	}


	// temp string calling integer to binary with 
	// FIXED POINT PART MAX DIGITS size parameter.
	// function will extend string without 
	// extend integer binary
	char* temp = integer_to_binary(number, FIXED_POINT_PART_MAX_DIGITS);
	if (temp == 0){
		return FALSE;
	}
	// temp is returned
	return temp;

}

/**
* @brief Takes an fraction portion of a fixed point number as string
* Converts the value of the number from decimal to binary. That string
* extended with 16x0's on the left side. then returned
*
* @param str number, string to be converted.
*/
char* fraction_part_to_binary(const char* number){


	// number is not checked for length
	// get fraction part may pass an array 
	// where len = 0, but theres a terminator
	// this needs to be converted too
	int len = 0;
	if (number[0] != '\0'){
		len = strlen(number);
	}


	// allocate memory for FIXED POINT PART
	// MAX DIGITS. binary digits + 1 for terminator
	// set all to '0' and add terminator
	char* temp = malloc((FIXED_POINT_PART_MAX_DIGITS+1)*(sizeof(char)));
	if (temp == 0){
		return FALSE;
	}
	for (int i = 0; i < FIXED_POINT_PART_MAX_DIGITS; i++){
		temp[i] = '0';
	}
	temp[FIXED_POINT_PART_MAX_DIGITS] = '\0';
	if (len == 0){
		return temp;
	}
	


	// decimal fraction to binary conversion
	// convert number string to integer of same digits
	// using len to keep track of the "depth" of the fraction
	long int numi = 0;
	for (int i = 0; i < len; i++){
		// increase numi to next order of magnitude
		numi = numi * 10;
		// switch case to convert char to int
		switch(number[i]){
			case '0':
				numi = numi + 0;
				break;
			case '1':
				numi = numi + 1;
				break;
			case '2':
				numi = numi + 2;
				break;
			case '3':
				numi = numi + 3;
				break;
			case '4':
				numi = numi + 4;
				break;
			case '5':
				numi = numi + 5;
				break;
			case '6':
				numi = numi + 6;
				break;
			case '7':
				numi = numi + 7;
				break;
			case '8':
				numi = numi + 8;
				break;
			case '9':
				numi = numi + 9;
				break;
			default:
				break;
		}
	}
	// numi now is long int decimal value of number
	// numi's highest digit is of order 10^(len-1)
	// p will keep track of position being updated in temp
	// while p is less than max length, and numi is not 0
	// numi will be doubled, if the product is greater than 
	// the next order of magnitude, temp[p] = '1' and that
	// higher order is removed from numi. 
	int p = 0;
	while(p < FIXED_POINT_PART_MAX_DIGITS && numi != 0){
		numi = numi * 2;
		if (numi >= pow(10, len)){
			temp[p] = '1';
			numi = numi - pow(10, len);
		}
		p++;
	}
	// temp is returned
	return temp;

}


// DOES NOT PASS TEST
// FAILS ON 
//	"0.0"
/**
* @brief Takes a real number as string
* Converts the value of the number from decimal to binary fixed point.
* then is returned.
*
* @param str number, string to be converted.
*/
char* real_to_fixed_point(const char* number){
	// check if number null
	if (number == 0){
		return FALSE;
	}
	// check if number is no length
//	int len = strlen(number);
//	if (len == 0){
//		return FALSE;
//	}

	// check if is real
	if ((is_real(number)) == 0){
		char err[] = "real number";
		printf(ERROR_MESSAGE_FORMAT, number, err);
		return NULL;
	}


	// getting integer part
	char* temp1 = get_integer_part(number);
	if (temp1 == 0){
		return FALSE;
	}
	char* temp2 = integer_part_to_binary(temp1);
	if (temp2 == 0){
		return FALSE;
	}

	// getting fraction part
	char* temp3 = get_fraction_part(number);
	if (temp3 == 0){
		return FALSE;
	}
	char* temp4 = fraction_part_to_binary(temp3);
	if (temp4 == 0){
		return FALSE;
	}

	temp2 = realloc(temp2, ((strlen(temp2)) + (strlen(temp4)) + 1)*(sizeof(char)));
	strcat(temp2, temp4);
 	free(temp1);
	free(temp3);	
	return temp2;

/*
	// concat integer and fraction parts
	char* temp5 = malloc((BINARY_WORD_SIZE+1)*(sizeof(char)));
	strcat(temp5, temp2);
	strcat(temp5, temp4);
	// freeing memory and return
	free(temp1);
	free(temp3);
	free(temp4);
	free(temp2);
//	printf("\ntemp5 is: %s\n", temp5);
*/
	//return temp5;
}

/**
* @brief Takes a binary number as string. check if its valid
* if it is, calls binary_to_integer to convert it and returns it.
*
* @param str number, string to be converted.
*/
char* binary_to_integer_part(const char* number){

	// check if number is null
	if (number == 0){
		return FALSE;
	}

	if ((is_fixed_point_part(number) == 0)){
		char err[] = "Error Message";
		printf(ERROR_MESSAGE_FORMAT, number, err);
		return NULL;
	}
	char* temp = binary_to_integer(number, FIXED_POINT_PART_MAX_DIGITS);
	if (temp == 0){
		return FALSE;
	}
	return temp;

}

// DOES NOT PASS TEST
/**
* @brief Takes a binary fraction portion of fixed point number as string. 
* check if its a valid fixed point portion. if it is, converts to decimal fraction
* and is returned.
*
* @param str number, string to be converted.
*/
char* binary_to_fraction_part(const char* number){
	// check if number is null
	if (number == 0){
		return FALSE;
	}

	if ((is_fixed_point_part(number)) == 0){
		char err[] = "Error Message";
		printf(ERROR_MESSAGE_FORMAT, number, err);
		return NULL;
	}

	// conversion
	float t = 0;
	float j = 0;
	int len = strlen(number);
	int i = 0;
	int e = 1;
	while (i < len){
		if (number[i] == '1'){
			for(int k = 0; k < e; k++){
				j = 1 / 2;
			}
			t = t + j;
		}
		e++;
		i++;
	}

	char* temp1 = malloc((8)*(sizeof(char)));
	temp1[0] = '0';
	temp1[1] = '.';
	temp1[2] = '\0';

	char* temp2 = malloc((6)*(sizeof(char)));
	sprintf(temp2, "%f", t);
	strcat(temp1, temp2);
	free(temp2);
	return temp1;

}

// DOES NOT PASS TEST
/**
* @brief Takes a binary fixed point number as string. 
* check if its a valid fixed point. if it is, converts to real decimal number
* and is returned
*
* @param str number, string to be converted.
*/
char* fixed_point_to_real(const char* number){

	// check if is fixed point
	if ((is_fixed_point(number)) == 0){
		char err[] = "Error Message";
		printf(ERROR_MESSAGE_FORMAT, number, err);
		return NULL;
	}

	char* temp1 = get_integer_part(number);
	char* temp2 = binary_to_integer_part(temp1);
	char* temp3 = get_fraction_part(number);
	char* temp4 = binary_to_fraction_part(temp3);
	char* temp5 = malloc((FIXED_POINT_MAX_DIGITS+1)*(sizeof(char)));
	strcat(temp5, temp2);
	strcat(temp5, temp4);
	free(temp1);
	free(temp2);
	free(temp3);
	free(temp4);
	return temp5;
}