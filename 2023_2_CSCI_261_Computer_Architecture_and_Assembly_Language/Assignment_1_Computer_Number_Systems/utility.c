/**
 * @file utility.c
 * @author Patrick McGrath, VIU
 * @version 1.0
 * @date September 26, 2023
 * 
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
#include "../include/utility.h"




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
        
        //if greater than, returns null
        return NULL;

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
        
        //if equal, returns null
        return NULL;

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

    // check if length is greater than max length
    if (len > DECIMAL_MAX_DIGITS){
	    return FALSE;
    }

    // check if characters are decimal digits
    // will not return true for negative
    // therefore, if it passes, value number is at least 0
    if ((are_decimal_digits(number)) == 0){
	    return FALSE;
    }

    // check if value of number is greater than maximum
    long n = strtoul(number, NULL, 10);
    if (n > DECIMAL_MAX_VALUE){
	    return FALSE;
    }

    // all tests passed
    // true is returned
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

    // check if length is 0
    if (len == 0){
	    return FALSE;
    }

    // check if greater than max length
    if (len > BINARY_WORD_SIZE){
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
 * @brief Takes a number as a string. Checks if all the characters are decimal
 * digits, within acceptable range for length. Returns true is checks pass,
 * otherwise false.
 * @param number string to be checked
 * */
int is_real_integer_part(const char* number){
	
	// check if number is NULL
	if (number == 0){
		return FALSE;
	}

	// check if number is not NULL but has no length
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// check if length is less than max
	if (len > REAL_PART_MAX_DIGITS){
		return FALSE;
	}

	// check if characters are decimal digits
	if ((are_decimal_digits(number)) == 0){
		return FALSE;
	}

	// check if value is less than or equal to max 65535
	long n = strtoul(number, NULL, 10);
	if (n > REAL_INTEGER_PART_MAX_VALUE){
		return FALSE;
	}

	// all tests passed
	// returns true
	return TRUE;
}

/**
 * @brief Takes a number as a string, checks if all the characters
 * are decimal digits and with range for size and length. If all 
 * tests pass, true is returned. Otherwise false
 * @param number string to be checked
 */
int is_real_fraction_part(const char* number){

	// check if number is NULL
	if (number == 0){
		return FALSE;
	}

	// check if length is 0
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// check if length is greater than max
	if (len > REAL_PART_MAX_DIGITS){
		return FALSE;
	}

	// check if digits are decimal
	if ((are_decimal_digits(number)) == 0){
		return FALSE;
	}

	// check if value is less than or equal to max
	long n = strtoul(number, NULL, 10);
	if (n > REAL_FRACTION_PART_MAX_VALUE){
		return FALSE;
	}

	// all tests passed
	// returns true
	return TRUE;
}

/**
 * @brief Takes a number as a string. Checks if it is a real number
 * within the acceptable range for size and length. As part of the
 * tests for realness, the string is tested for presence of '.'s,
 * their position, and the acceptability of the integer and fractional
 * portions, if present. If all tests pass, true is returned. Otherwise,
 * false
 *
 * @param number string to be checked
 */
int is_real(const char* number){

	// check if number is NULL
	if (number == 0){
		return FALSE;
	}

	// check if length is 0
	int len = strlen(number);
	if (len == 0){
		return FALSE;
	}

	// check if less than max
	if (len > REAL_MAX_DIGITS){
		return FALSE;
	}

	// check for number of '.'s
	// 0 or 1 allowed
	// dots is number of '.'
	// dotspos is the position of '.' if there is only 1
	// set to -1 to start
	// for loop goes through each position in string,
	// if its a '.', dots is incremented and dotpos is updated.
	// loop breaks if there are 2 dots or the end is reach
	// false is returned if more than 1 '.' is found
	int dots = 0;
	int dotpos = -1;
	for(int i = 0; (i < len) && (dots < 2); i++){
		if(number[i] == '.'){
			dots++;
			dotpos = i;
		}
	}
	if (dots > 1){
		return FALSE;
	}

	// check if characters that arent '.' are decimal
	// if there is a dot, a new temp string that is 1 shorter is created.
	// all characters except dot is copied, including term
	// temp string is checked to see if it is decimal
	// if there is no dot, string is checked if it is decimal without temp
	if (dots == 1){
		char* temp = malloc((len)*(sizeof(char)));
		// copy before dot
		int i = 0;
		while(i < dotpos){
			temp[i] = number[i];
			i++;
		}
		// skip dot
		i++;
		// add remaining
		while (i <= len){
			temp[i-1] = number[i];
			i++;
		}

		// check if temp is decimal digits
		if((are_decimal_digits(temp)) == 0){
			return FALSE;
		}

		// free memory
		free(temp);
	} else {
		// there are no dots
		// check if passed array is decimal
		if((are_decimal_digits(number)) == 0){
			return FALSE;
		}
	}

	// if there is a dot, left of dot must be checked integer part,
	// right of dot must be checked for fraction part.
	// if there is no dot, all must be checked for integer part
	
	if(dots == 1){
		// if dot is in 0th position, there is only fractional portion
		// if dot is in (len-1)th position, there is only integer part.
		// if it is between, two temp strings will be created to test
		// each portion
		if(dotpos == 0){
			// temp string, 1 size less than number
			char* frac1 = malloc((len)*(sizeof(char)));
			// copy everything character over 1 space ecept first
			for(int j = 1; j <= len; j++){
				frac1[j-1] = number[j];
			}
			// check for fraction part
			if((is_real_fraction_part(frac1)) == 0){
				free(frac1);
				return FALSE;
			}
			
		}
		if(dotpos == len-1){
			// temp string, 1 size less
			char* int1 = malloc((len)*(sizeof(char)));
			// copy everything except final character
			for(int j = 0; j < len-1; j++){
				int1[j] = number[j];
			}
			// copy terminator
			int1[len-1] = number[len];
			// check for integer part
			if((is_real_integer_part(int1)) == 0){
				free(int1);
				return FALSE;
			}

		}
		if(dotpos != 0 && dotpos != len-1){
			// length of string before and after dot
			int bflen = dotpos;
			int aflen = len - dotpos + 1;
			// temp strings for integer and fraction portions
			char* bf = malloc((bflen+1)*(sizeof(char)));
			char* af = malloc((aflen+1)*(sizeof(char)));
			// copy contents to front string
			for(int j = 0; j < bflen; j++){
				bf[j] = number[j];
			}
			// and terminator
			bf[bflen] = number[len];
			// copy contents to back string
			// with terminator
			int k = dotpos+1;
			for(int j = 0; j <= aflen; j++){
				af[j] = number[k];
				k++;
			}

			// checks
			// integer check
			if((is_real_integer_part(bf)) == 0){
				free(af);
				free(bf);
				return FALSE;
			}
			if((is_real_fraction_part(af)) == 0){
				free(af);
				free(bf);
				return FALSE;
			}
		}
	}
	// all tests passed
	// returns true
	return TRUE;
}



/**
 * @brief Takes a number as a string. Checks if the 
 * length of number is equal to FIXED_POINT_PART_MAX_DIGITS
 * and checks if all digits are binary. Returns true if all
 * tests passed, false otherwise
 *
 * @param number string to be checked
 */
int is_fixed_point_part(const char* number){

	//check if number is NULL
	if(number == 0){
		return FALSE;
	}

	// check if number is no length
	int len = strlen(number);
	if(len == 0){
		return FALSE;
	}

	// check if equal to 
	// FIXED_POINT_PART_MAX_DIGITS
	if(len != FIXED_POINT_PART_MAX_DIGITS){
		return FALSE;
	}

	// check if digits are binary
	if((are_binary_digits(number)) == 0){
		return FALSE;
	}

	// all tests passed
	// returns true
	return TRUE;

}


/**
 * @brief Takes a number as a string. Checks if the 
 * length of number is equal to FIXED_POINT_MAX_DIGITS
 * and checks if all digits are binary. Returns true if all
 * tests passed, false otherwise
 *
 * @param number string to be checked
 */
int is_fixed_point(const char* number){
	// check if number is NULL
	if(number == 0){
		return FALSE;
	}
	// check if number is no length
	int len = strlen(number);
	if(len == 0){
		return FALSE;
	}

	// check if number is not equal to
	// FIXED_POINT_MAX_DIGITS
	if(len != FIXED_POINT_MAX_DIGITS){
		return FALSE;
	}

	// check if all digits are not binary
	if((are_binary_digits(number)) == 0){
		return FALSE;
	}

	// all tests passed
	// returns true
	return TRUE;

}

/**
 * @brief Takes a real number as a string. checks if its real,
 * then if it is, returns a new string that is the integer part
 *
 * @param number string to be checked
 */
char* get_integer_part(const char* number){

	// check if number is NULL
	if(number == NULL){
		return FALSE;
	}
	// check if number is no length
	int len = strlen(number);
	if(len == 0){
		return FALSE;
	}

	// check if number is not real
	if((is_real(number)) == 0){
		return FALSE;
	}

	// if number passes to here, dot may be present
	// find dots position
	int dotpos = -1;
	for(int i = 0; (i < len) && (dotpos < 0); i++){
		if(number[i] == '.'){
			dotpos = i;
		}
	}

	// no dots present
	if (dotpos == -1){
		// temp string to copy all contents of number including terminator
		char* temp = malloc((len+1)*(sizeof(char)));
		// check if memory allocated
		if (temp == 0){
			return FALSE;
		}
		for(int i = 0; i <= len; i++){
			temp[i] = number[i];
		}
		// return temp
		return temp;
	}


	// check if dot is first
	if(dotpos == 0){
		//integer part = ''
		char* temp = malloc((1)*(sizeof(char)));
		if (temp == 0){
			return FALSE;
		}
		temp[0] = number[len];
		return temp;
	}

	// check if dot last
	if(dotpos == len-1){
		return FALSE;
	}

	// dot present, not initial
	// temp string with length up to '.'
	char* temp = malloc((dotpos+1)*(sizeof(char)));
	// check if memory allocated
	if(temp == 0){
		return FALSE;
	}
	// copy contents
	for(int i = 0; i < dotpos; i++){
		temp[i] = number[i];
	}
	// terminator
	temp[dotpos] = number[len];

	// return temp
	return temp;
	

}

/**
 * @brief Takes a real number as a string. checks if its real,
 * then if it is, returns a new string that is the fraction part
 *
 * @param number string to be checked
 */
char* get_fraction_part(const char* number){

	// check if number is null
	if(number == 0){
		return FALSE;
	}
	// check if number is no length
	int len = strlen(number);
	if(len == 0){
		return FALSE;
	}

	// check if number is real
	if((is_real(number)) == 0){
		return FALSE;
	}

	// if passes to here, dots may be present
	int dotpos = -1;
	for(int i = 0; (i < len) && (dotpos < 0); i++){
		if(number[i] == '.'){
			dotpos = i;
		}
	}

	//if no dot
	if(dotpos == -1){
		char* temp = malloc((1)*(sizeof(char)));
		if (temp == 0){
			return FALSE;
		}
		temp[0] = number[len];
		return temp;
	}

	//if dot first
	if(dotpos == 0){
		char* temp = malloc((len)*(sizeof(char)));
		if(temp == 0){
			return FALSE;
		}
		for (int i = 0; i < len; i++){
			temp[i] = number[i+1];
		}
		return temp;
	}


	// dot present, not first or last
	// create temp string of appropriate length
	// and copy contents right of '.' in number
	// to temp string
	int templen = len-dotpos;
	char* temp = malloc((templen)*(sizeof(char)));
	for(int i = 0; i <= templen-1; i++){
		temp[i] = number[dotpos+1+i];
	}

	// return temp
	return temp;
}