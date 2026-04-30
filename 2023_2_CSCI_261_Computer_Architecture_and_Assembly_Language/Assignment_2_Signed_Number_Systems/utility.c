/**
 * @file utility.c
 * @author Patrick McGrath, CSCI 261, VIU
 * @version 1.0
 * @date October 17, 2023
 * 
 *  Assignment #2 Signed Systems Application
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
* @brief Takes a number as a string and a word size. Checks if the 
* string is larger, lesser or equal to word size. If larger, NULL returned.
* If lesser, new string size of word_size is created, back-padded with 0's,
* and front-filled with the passed number string. If equal, a new string is
* created, with all the values passed.
*
* @param number string to be compared for size and values
*
* @param word_size int for comparing size to length of string number
*/
char* extend_fraction_binary(const char* number, int word_size){
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
        
        char* temp = malloc((word_size+1)*(sizeof(char)));
        for(int i=0; i<word_size; i++){
            temp[i] = number[i];
        }
        temp[word_size] = '\0';
        return temp;

    } else if (len < word_size){
        
        // if less than
        // allocate memory for extended word, +1 for terminator
        char* temp = malloc((word_size+1)*(sizeof(char)));
     
        //memory check
        if (temp == NULL){
        return NULL;
        }

	// back-padding with 0's
	for (int i = word_size-1; i >= len; i--){
		temp[i] = '0';
	}

	// copy digits from number to left side of temp
	for (int i = 0; i < len; i++){
		temp[i] = number[i];
	}

	// copy terminator
	// and return
	temp[word_size] = number[len];
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

    // check if not binary word size
    if (len != BINARY_WORD_SIZE){
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
 * @brief Takes a number as a string. Checks if the number is a valid biased
 * 127 decimal number. If it is, True (1) is returned, otherwise False (0) 
 * 
 * @param number string to be checked
 */
int is_biased_127_decimal(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // number length
    size_t len = strlen(number);

    // check if 0
    if (len == 0){
        return FALSE;
    }

    // check if greater than BIASED_127_DECIMAL_MAX_DIGITS
    if (number[0] == '-'){
        if (len > BIASED_127_BINARY_MAX_DIGITS+1){
            return FALSE;
        }
    } else {
        if (len > BIASED_127_BINARY_MAX_DIGITS){
            return FALSE;
        }
    }

    // check if not decimal
    if (is_decimal(number) == 0){
        return FALSE;
    }

    // check if outside range
    // turn number to int n
    // start from first non-'-', times the previous n by 10, add the current value in number, move to next
    int n = 0;
    int bin = 0;

    if (number[0] == '-') {
        for (int i = 1; i < len; i++) {
            bin = (number[i] - 48);
            n = (n*10) + bin;
            }
        n = -n;
    } else {
        for (int i = 0; i < len; i++) {
            bin = (number[i] - 48);
            n = (n*10) + bin;
        }
    }

    // check if n is outside of range
    if (n > BIASED_127_DECIMAL_MAX_VALUE || n < BIASED_127_DECIMAL_MIN_VALUE){
        return FALSE;
    }

    // all passed, return true
    return TRUE;
}

   

/**
 * @brief Takes a number as a string. Checks if the number is a valid biased
 * 127 binary number. If it is, True (1) is returned, otherwise False (0) 
 * 
 * @param number string to be checked
 */
int is_biased_127_binary(const char* number){

    // check for null
    if (number == NULL){
        return FALSE;
    }

    //check for length
    size_t len = strlen(number);
    if (len != BIASED_127_BINARY_MAX_DIGITS){
        return FALSE;
    }

    // check for binaryism
    if (are_binary_digits(number) == 0){
        return FALSE;
    }

    // all passed
    return TRUE;
}



/**
 * @brief Takes a number as a string. Checks if the number is a valid significand. 
 * If it is, True (1) is returned, otherwise False (0) 
 * 
 * @param number string to be checked
 */
int is_significand(const char* number){
    // check for null
    if (number == 0){
        return FALSE;
    }

    // length check
    size_t len = strlen(number);
    if (len != FLOATING_POINT_SIGNIFICAND_DIGITS){
        return FALSE;
    }

    // binary check
    if (are_binary_digits(number) == 0){
        return FALSE;
    }
    
    // all passed
    return TRUE;
}




/**
 * @brief Takes a number as a string. Checks if the number is a real number. 
 * If it is, True (1) is returned, otherwise False (0) 
 * 
 * @param number string to be checked
 */
int is_real(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }


    // length check
    // cant be 0 or real max +2 for (-/+) and .
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }
    if (len > REAL_MAX_DIGITS+2){
        return FALSE;
    }

    // checking for the 3 acceptable non decimal characters, their quantity and locations
    int plus = 0;
    int pluspos = -1;
    int mnus = 0;
    int mnuspos = -1;
    int dots = 0;
    int dotspos = -1;

    

    for (int i=0; i<len; i++){

        // check if number[i] is 0-9,-,+,.
        // first check if its outside of range of 0-9
        if(number[i] < 48 || number[i] > 57){
            // then check the characters
            if (number[i] != '-' && number[i] != '+' && number[i] != '.'){
                return FALSE;
            }
        }

        // update -+. values
        if(number[i] == '+'){
            plus++;
            pluspos = i;
        } else if(number[i] == '-'){
            mnus++;
            mnuspos = i;
        } else if (number[i] == '.'){
            dots++;
            dotspos = i;
        }


        // check if 2 or more -,+
        if (plus > 1 || mnus > 1){
            return FALSE;
        }

        // check if both minus and plus
        if (plus > 0 && mnus > 0){
            return FALSE;
        }

        // check if there is 1 +, if it is not first
        if (plus == 1 && pluspos != 0){
            return FALSE;
        }

        // check if there is 1 -, if it is not first
        if (mnus == 1 && mnuspos != 0){
            return FALSE;
        }

        // check if there are more than 1 dot
        if (dots > 1){
            return FALSE;
        }

        // check if dot is last
        if (dotspos == len-1){
            return FALSE;
        }

    }

    // if here, number is 0 or 1 - or +, at beginning, 0 or 1 . and the rest 0-9
    // now know if there is -,+, .. so we can accurrately check length
    if (len > REAL_MAX_DIGITS + plus + mnus + dots){
        return FALSE;
    }

    // all tests passed
    return TRUE;

}



/**
 * @brief Takes a number as a string. Checks if the number is a valid floating point number. 
 * If it is, True (1) is returned, otherwise False (0) 
 * 
 * @param number string to be checked
 */
int is_floating_point(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // length check
    size_t len = strlen(number);
    if (len != FLOATING_POINT_MAX_DIGITS){
        return FALSE;
    }

    // binary check
    if (are_binary_digits(number) == 0){
        return FALSE;
    }

    // all tests passed
    return TRUE;
}




/**
 * @brief Takes a number as a string. Returns integer portion as a string.
 * 
 * @param number string to be checked
 */
char* get_integer_part(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // find decimal and position
    int dotpos = -1;
    for (int i = 0; i < len; i++){
        if (number[i] == '.'){
            dotpos = i;
        }
    }

    // check if dot last
    if (dotpos == len-1){
        return FALSE;
    }

    // either no dot, or present with non0 integer
    // first no dot
    if (dotpos == -1){
        // temp string equal to full length, and copy contents
        char* temp = malloc((len+1)*(sizeof(char)));
        for (int i = 0; i < len; i++){
            temp[i] = number[i];
        }
        // null terminator and return
        temp[len] = '\0';
        return temp;
    } else {
        // make temp string equal to integer length, then same as above
        char* temp = malloc((dotpos+1)*(sizeof(char)));
        for (int i = 0; i < dotpos; i++){
            temp[i] = number[i];
        }
        temp[dotpos] = '\0';
        return temp;
    }

    // success should return above
    return FALSE;
}

    



/**
 * @brief Takes a number as a string. Returns fraction portion as a string.
 * 
 * @param number string to be checked
 */
char* get_fraction_part(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // find decimal and position
    int dotpos = -1;
    for (int i = 0; i < len; i++){
        if (number[i] == '.'){
            dotpos = i;
        }
    }

    // check if dot last
    if (dotpos == len-1){
        return FALSE;
    }

    // either no dot, or present with non0 integer
    // first no dot
    if (dotpos == -1){
        // temp string with just null
        char* temp = malloc((1)*(sizeof(char)));
        // null terminator and return
        temp[0] = '\0';
        return temp;
    } else {
        // make temp string equal to fraction length
        size_t templen = len-dotpos-1;
        char* temp = malloc((templen+1)*(sizeof(char)));
        if (temp == NULL){
            return FALSE;
        }

        // copy fractional contents add terminator and return
        for (int i = dotpos+1, j=0; i < len; i++, j++){
            temp[j] = number[i];
        }
        temp[len-dotpos] = '\0';
        return temp;
    }

    // success should return above
    return FALSE;
}