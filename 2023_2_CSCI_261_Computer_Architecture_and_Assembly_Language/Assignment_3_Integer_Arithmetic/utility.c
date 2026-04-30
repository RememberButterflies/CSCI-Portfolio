/**
 * @file utility.c
 * @author Patrick McGrath, CSCI 261, VIU
 * @version 1.0
 * @date November 7, 2023
 * 
 *  Assignment #3 Integer Arithmetic Application
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
#include "utility.h"





/**
* @brief Takes a string and reverses it
*
* @param str The string to be reversed
*/
void reverse(char* str){
    // check if string is null pointer
    if (str == 0){
	    return;
    }
    //length of passed string excl. terminator
    size_t len = strlen(str);

    // check if string is only 1 character
    if (len == 1 || len == 0){
	    return;
    } else {
	    //allocate memory for temp string length of passed string + 1 for term.
	    char* temp = malloc((len+1)*(sizeof(char)));

	    //memory check
	    if (temp == NULL){
        	return;
	    }

	    // for loop for assigning characters in reverse from
	    // passed string to temp string
	    // j keeps track of temp position
	    // i keeps track of str position
	    // terminator is added first
	    temp[len] = str[len];
	    int j = 0;
	    for(int i=len-1; i>=0; i--){
	        temp[j] = str[i];
	        j++;
	    }

	    // temp is copied to str
	    strcpy(str, temp);

	    // memory freed and returned
	    free(temp);
    }
    return;
}






/**
* @brief Takes a number as a string and a word size. Checks if the 
* string is larger, lesser or equal to word size. If larger, NULL returned.
* If lesser, new string size of word_size is created, front-padded with 0's,
* and back-filled with the passed number string. If equal, a new string is
* created, with all the values passed.
*
* @param number string to be compared for size and values
*
* @param word_size int for comparing size to length of string number
*/
char* extend_integer_binary(const char* number, int word_size){
    // check if number is NULL
    if (number == 0){
	    return NULL;
    }
    //length of passed string excl. terminator
    size_t len = strlen(number);

    // comparison of string length to word size
    // using if, else if, else
    // greater than, less than, equal
    if (len > word_size){
        
        //if greater than
        // copy 'word_size" most significant digits (left)
        char* temp = malloc((word_size+1)*(sizeof(char)));


        for(int i=len-word_size; i<len; i++){
            temp[i-(len-word_size)] = number[i];
        }
        temp[word_size] = '\0';
        return temp;

    } else if (len < word_size){
        
        // if less than
        // allocate memory for extended word+1 for terminator
        char* temp = malloc((word_size+1)*(sizeof(char)));
     
        //memory check
        if (temp == NULL){
        return NULL;
        }

        // find difference
        int diff = word_size-len;

        // while loop for padding front of extended with 0's
        int i = 0;
        while(i < diff){
            temp[i] = '0';
            i++;
        }

        // copy the rest of the digits from number to temp
        // i will be at correct position, diff
        // j will go through number
        // i will increment to the terminators postion aswell, number[word_size]
        int j = 0;
        while(i<=word_size){
            temp[i] = number[j];
            i++;
            j++;
        }

        // return value without freeing memory
        return temp;
    } else {

        // if len = word_size
        // allocate memory for extended word, +1 for terminator
        char* temp = malloc((word_size+1)*(sizeof(char)));
        
        //memory check
        if (temp == NULL){
        return NULL;
        }

        // copy all digits and term.
        int i = 0;
        while(i <= word_size){
            temp[i] = number[i];
            i++;
        }       

        // returns temp
        return temp; 
    }
    return 0;
}







/**
* @brief Takes a number as a string. Checks if all characters are digits (0-9)
* or not. Returns TRUE if all are digits. Otherwise, FALSE
* @param number string to be checked
*/
int are_decimal_digits(const char* number){
    // check if number is NULL
    if (number == 0){
	    return FALSE;
    }

    // length of string
    size_t len = strlen(number);

    // check if number is of no length
    if (len == 0){
	    return FALSE;
    }

    //loop for checking characters against ASCII values
    for(int i=0; i<len; i++){
        // if the ith character is outside of ASCII numerical values
        // false is returned
        if(number[i] < 48 || number[i] > 57){
            return FALSE;
        }
    }
    // if for loop is complete, all characters are digits
    return TRUE;
}







/**
* @brief Takes a number as a string. Checks if all characters are digits (0-1)
* or not. Returns TRUE if all are digits. Otherwise, FALSE
* @param number string to be checked
*/
int are_binary_digits(const char* number){
    // check if number is NULL
    if (number == 0){
	    return FALSE;
    }

    // length of string
    size_t len = strlen(number);

    // check if number of no length
    if (len == 0){
	    return FALSE;
    }

    

    //loop for checking characters against ASCII values
    for(int i=0; i<len; i++){
        // if the ith character is not the ASCII values for 0 or 1,
        // FALSE is returned
        if(number[i] != '0' && number[i] != 49){
		return FALSE;
    	}
    }
    // if for loop is complete, all characters are digits 0 or 1
    return TRUE;
}







/**
* @brief Takes a number as a string. Checks if all the characters are decimal digits,
* within acceptable range for length and size. Returns true if all checks pass. 
* Otherwise, false.
* @param number string to be checked
*/
int is_decimal(const char* number){
    // check if number is NULL
    if (number == 0){
	    return FALSE;
    }


    // length of string
    size_t len = strlen(number);

    // check if length is 0
    if (len == 0){
	    return FALSE;
    }

    // check for min and max up front
    if (strcmp(number, "-2147483648") == 0 || strcmp(number, "2147483647") == 0) {
        return TRUE;
    }

    // check for '-'
    if (strcmp(number, "-") == 0){
        return FALSE;
    }


// check if length is too long
// first if its too long with minus
// then if its the max with minus, check if there is a minus
    if (len > DECIMAL_MAX_DIGITS+1){
        return FALSE;
    } else if (len == DECIMAL_MAX_DIGITS+1){
        if (number[0] != '-'){
            return FALSE;
        }
    }

    // check if digits are decimal, first not '-'/'+'
    if (number[0] != '-' && number[0] != '+'){
        if (are_decimal_digits(number) == 0){
            return FALSE;
        }
    } else {
        // first is minus or plus, check rest
        for (int i = 1; i < len; i++){
            if(number[i] < 48 || number[i] > 57){
                return FALSE;
            }
        }
    }


    // check for range
    // first positive
    if (number[0] != '-'){
        long long int n = 0;   // number being made
        double t = 0;   // temp being added to n
        int e = 0;     // temps bases exponent

        // going from right (len-1)
        // len-1 is 1st position (10^0)
        for (int i = len-1; i>=0; i--){
            // check if e is too great
            if (e > 9){
                return FALSE;
                // if max size
            } else if (e == 9){
                // value can be no greater than 2
                if ((number[i]-48) > 2){
                    return FALSE;
                } else if ((number[i]-48) == 2){
                    // if 2, check current n value to see if it will go over
                    if (n>(DECIMAL_MAX_VALUE-(2*(pow(10,9))))){
                        return FALSE;
                    }
                }
            }
            t = pow(10, e);
            t = (number[i]-48)*t;
            n = n + t;
            e++;
        }

        // check if greater than range
        if (n > DECIMAL_MAX_VALUE){
            return FALSE;
        }   
        
       
    } else {
        // next negative, number[0] == '-'


        long long int n = 0;   // number being made
        double t = 0;   // temp being added to n
        int e = 0;     // temps bases exponent

        // going from right (len-1)
        // len-1 is 1st position (10^0)
        for (int i = len-1; i>=1; i--){
            // check if e is too great
            if (e > 9){
                return FALSE;
                // if max size
            } else if (e == 9){
                // value can be no greater than 2
                if (number[i] > 2){
                    return FALSE;
                } else if (number[i] == 2){
                    // if 2, check current n value to see if it will go over
                    if (n>(abs(DECIMAL_MIN_VALUE)-(2*(pow(10,9))))){
                        return FALSE;
                    }
                }
            }
            t = pow(10, e);
            t = number[i]*t;
            n = n + t;
            e++;
        }
        // check if smaller than range
        n = -n;
        if (n < DECIMAL_MIN_VALUE){
            return FALSE;
        }  
    }
    return TRUE;
}






/**
* @brief Takes a number as a string. Checks if all the characters are binary digits,
* within acceptable range for length. Returns true if all checks pass. 
* Otherwise, false.
* @param number string to be checked
*/
int is_binary(const char* number){
    // check if number is NULL
    if (number == 0){
	    return FALSE;
    }

    // length of string
    size_t len = strlen(number);

    // check if less than binary word size
    if (len < BINARY_WORD_SIZE){
	    return FALSE;
    }

    // check if greater than double binary worde size
    if (len > 2*BINARY_WORD_SIZE){
	    return FALSE;
    }

    // check if characters are binary digits
    // if it passes, it will binary and nonnegative
    if ((are_binary_digits(number)) == 0){
	    return FALSE;
    }

    // all tests passed,
    // return true
    return TRUE;
}








/**
* @brief Takes 2 strings, 1 bit as a string and an int that is the size of the first two strings. 
*   does an arithmetic shift to the right, moving the right most character of qregister into q_1.
*   And extending the first digit of aregister. Only 1 shift is done
*
* @param aregister, first string. 
* @param qregister, second string.
* @param q_1, final string, single bit.
* @param word_size, int size of first 2 strings
*/
void group_arithmetic_shift_right(char* aregister, char* qregister, char* q_1, int word_size){

    // temp strings
    char* tempa = malloc((word_size+1)*(sizeof(char)));
    char* tempq = malloc((word_size+1)*(sizeof(char)));
    // add sign and extend first character of temps
    tempa[0] = aregister[0];
    tempa[1] = aregister[0];
    tempq[0] = aregister[word_size-1];
    tempq[1] = qregister[0];

    // assign q_1
    q_1[0] = qregister[word_size-1];

    // copy remaining chars to temps
    for (int i = 2; i < word_size; i++){
        tempa[i] = aregister[i-1];
        tempq[i] = qregister[i-1];
    }
    tempa[word_size] = '\0';
    tempq[word_size] = '\0';

    // copy contents back to original
    for (int i = 0; i < word_size; i++){
        aregister[i] = tempa[i];
        qregister[i] = tempq[i];
    }

    // free mem
    free(tempa);
    free(tempq);
    return;
}









/**
* @brief Takes 2 strings, and an int that is the size of the first two strings. 
*   does a logical left shift, inserting 0 to the right most character of qregister.
*   And dropping the left most of aregister.
*
* @param aregister, first string. 
* @param qregister, second string.
* @param word_size, int size of first 2 strings
*/
void group_logical_shift_left(char* aregister, char* qregister, int word_size){
    
    // temp strings
    char* tempa = malloc((word_size+1)*(sizeof(char)));
    char* tempq = malloc((word_size+1)*(sizeof(char)));

    // copy contents to all but final chars
    for (int i = 0; i < word_size-1; i++){
        tempa[i]= aregister[i+1];
        tempq[i]= qregister[i+1];
    }
    // final chars and terminators
    tempa[word_size-1] = qregister[0];
    tempq[word_size-1] = '0';
    tempa[word_size] = '\0';
    tempq[word_size] = '\0';

    // copy contents back to originals
    for (int i = 0; i < word_size; i++){
        aregister[i] = tempa[i];
        qregister[i] = tempq[i];
    }


    // free mem and return
    free(tempa);
    free(tempq);
    return;
}