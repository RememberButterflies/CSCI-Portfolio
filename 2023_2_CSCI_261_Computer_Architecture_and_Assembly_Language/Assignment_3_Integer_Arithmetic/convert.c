/**
 * @file convert.c
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
#include "convert.h"





/**
* Helper Function(s)
*/

/**
* @brief Takes an unsigned binary integer as a string. Converts it
* to a decimal integer. Returns it as a long
*
* @param number, string to be converted
*/
long unsigned_binary_to_integer(const char* number);
long unsigned_binary_to_integer(const char* number){
    
    // check for null
    if (number == NULL){
        return FALSE;
    }

    // length and test for length
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // temp long for returning
    // 2nd temp long (bin) for adding to temp
    // starting from right-hand of number, i=0, j=len-1
    //taking the value, multipling it by 2^i, and adding that to temp
    // moving j--, i++, ending when j finishes number[0]
    long temp = 0;
    long bin = 0;
    for(int i=0, j=len-1; j>=0; i++, j--){
        bin = (number[j] - 48);
        bin = bin * pow(2, i);
        temp = temp + bin;
    }
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
char* integer_to_binary(long num, int binary_size){
    long int_num = num;
    int word_size = binary_size;

    // allocate memory
    char* temp = malloc((word_size+1)*(sizeof(char)));
    if(temp == NULL){
        return FALSE;
    }

    // pre-set all characters to 0
    for (int i=0; i<word_size; i++){
        temp[i] = '0';
    }

 

    // makes the string in reverse
    long int numi = int_num;
    int i = 0;
    int r = -1;
    int done = 0;
    while (done == 0 && i < word_size){
        r = numi % 2;
        if (r == 1){
            temp[i] = '1';
        }
        numi = numi / 2;
        i++;
        if(numi == 0){
            done++;
        }
    }

    // i will be at end of digits
    // add term, revers and return
    temp[i] = '\0';
    reverse(temp);

    return temp;
}







/**
* @brief Takes a signed binary integer as a string. Converts the magnitude of it
* it to a decimal integer. Converts the integer to a binary. Returns a string
* of that binary
*
* @param signed_number, string to be converted
* @param word_size, size of string being returned
*/
char* get_magnitude_binary(const char* signed_number, int word_size){
    
    // check for null
    if (signed_number == 0){
        return FALSE;
    }

    //length and check for length
    size_t len = strlen(signed_number);
    if (len == 0){
        return FALSE;
    }

    // use 2 longs to convert unsigned number into a long
    // first check for sign symbol
    // use for loop to convert the values to numbers, inctreasing temp size and adding the converted to it
    long temp = 0;
    long bin = 0;

    if (signed_number[0] != '-' && signed_number[0] != '+'){
        for (int i=0; i<len; i++){
            temp = temp*10;
            bin = signed_number[i]-48;
            temp = temp+bin;
        }
    } else {
        for (int i=1; i<len; i++){
            temp = temp*10;
            bin = signed_number[i]-48;
            temp = temp+bin;
        }
    }

    // call integer to binary to return a binary string of the absolute value of signed_number
    return integer_to_binary(temp, word_size);
}







/**
* @brief Takes a signed binary integer as a string. Converts it
* it to a decimal integer. Returns the integer
*
* @param number, string to be converted
*/
int signed_binary_to_integer(const char* number){

    // test for null
    if (number == 0){
        return FALSE;
    }

    // upfront max and min checks
    if (strcmp(number, "10000000000000000000000000000000") == 0){
        return -2147483648;
    }
    if (strcmp(number, "01111111111111111111111111111111") == 0){
        return 2147483647;
    }

    // length and length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // temp ints for converting number to an int
    // first checks for positive and does that one
    int temp = 0;
    int bin = 0;
    if (number[0] == '0'){

        for (int i=0; i<len; i++){
            bin = (number[i]-48);
            temp = temp * 2;
            temp = temp + bin;
        }

        return temp;
    } else {
        // negative
        int flip = -1;
        for (int i=1; i<len; i++){
            flip = number[i]-48;
            if (flip == 1){
                bin = 0;
            } else {
                bin = 1;
            }
            temp = temp * 2;
            temp = temp + bin;
        }

        // already flipped, so swap sign minus 1 and return
        temp = -temp;
        temp = temp-1;
        return temp;
    }
    return 0;
}






/**
* @brief Function for adding bits and recording the carry. 
* Sums op1, op2, and cin. Then does a switch on the total.
* If total = 0, *cout = 0, return 0.
* If total = 1, *cout = 0, return 1.
* If total = 2, *cout = 1, return 0.
* If total = 3, *cout = 1, return 1.
*
* @param op1, char of bit being added
* @param op2, char of bit being added
* @param cin, char of bit being added
* @param *cout, pointer to be updated by function.
*/
char one_bit_add(const char op1, const char op2, const char cin, char* cout){

    // convert chars to ints
    // add them together
    // make a char to return
    int iop1 = op1-48;
    int iop2 = op2-48;
    int icin = cin-48;
    int total = iop1+iop2+icin;
    char result;

    // switch based on value of sum of input
    // assign result, output and then return result
    switch (total){
        case 0:
            result = '0';
            *cout = '0';
            return result;
            break;
        case 1:
            result = '1';
            *cout = '0';
            return result;
            break;
        case 2:
            result = '0';
            *cout = '1';
            return result;
            break;
        case 3:
            result = '1';
            *cout = '1';
            return result;
            break;
        default:
            break;
    }
    return '.';
}






/**
* @brief Takes a binary number as a string. Flips the bits on the that string. Returns
*
* @param number, string to be flipped
*/
void ones_complement(char* number){
    // null check
    if (number == 0){
        return;
    }

    //length and length check
    size_t len = strlen(number);
    if (len == 0){
        return;
    }

    for(int i=0; i<len; i++){
        if (number[i] == '0'){
            number[i] = '1';
        } else {
            number[i] = '0';
        }
    }
    return;
}







/**
* @brief Takes a binary number as a string. Flips the bits.
* Then adds 1 by calling one_bit_add, moving the carry from right to left
* Returns.
*
* @param number, string to be converted
*/
void twos_complement(char* number){
    // null check
    if (number == 0){
        return;
    }

    //check for extreme case
    if (strcmp(number, "00000000000000000000000000000000") == 0){
        return;
    }

    //length and length check
    size_t len = strlen(number);
    if (len == 0){
        return;
    }

    // ones compliment
    ones_complement(number);



    // use one_bit_add recursively to add 1 at lowest and carry it up as needed
    char carry = '1';
    for (int i=len-1; i>=0; i--){
        char cin = carry;
        carry = '0';
        number[i] = one_bit_add(number[i], '0', cin, &carry);
    }
    return;
}







/**
* @brief Takes a decimal number as a string. Checks if its valid.
* Then converts it to a signed binary number. Returns string to binary number. 
*
* @param number, string to be converted
*/
char* to_twos_complement(const char* number){
    // check for null
    if (number == 0){
        return FALSE;
    }

    // length and length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // check for positive symbol
    // if so, make new string copying contents except '+'
    // do everything else the same, except no check for negative
    if (number[0] == '+'){
        char* magpos = malloc((len)*(sizeof(char)));
        if (magpos == 0){
            free(magpos);
            return FALSE;
        }
        for (int i=1; i<len; i++){
            magpos[i-1] = number[i];
        }
        magpos[len-1] = '\0';


        // check for decimal
        if (is_decimal(magpos) == 0){
            return FALSE;
        }

        // get magnitude
        char* magposmag = get_magnitude_binary(magpos, BINARY_WORD_SIZE);
        if (magposmag == 0){
            free(magposmag);
            return FALSE;
        }

        // extend
        magposmag = extend_integer_binary(magposmag, BINARY_WORD_SIZE);
        if (magposmag == 0){
            free(magposmag);
            return FALSE;
        }
        return magposmag;

    } else {

        // check for decimal
        if (is_decimal(number) == 0){
            return FALSE;
        }

        // get magnitude
        char* mag = get_magnitude_binary(number, BINARY_WORD_SIZE);
        if (mag == 0){
            free(mag);
            return FALSE;
        }

        // extend
        mag = extend_integer_binary(mag, BINARY_WORD_SIZE);
        if (mag == 0){
            free(mag);
            return FALSE;
        }

        // if negative, twos compliment
        if (number[0] == '-'){
            twos_complement(mag);
        }
        return mag;
    }
    //return
    return FALSE;

}








/**
* @brief Takes a signed binary as a string. Checks if its valid.
* Then converts it to an integer. Returns string to integer number with sign. 
*
* @param number, string to be converted
*/
char* from_twos_complement(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // length and check for length
    size_t len = strlen(number);
    if(len == 0){
        return FALSE;
    }

    // check for binary
    if (is_binary(number) == 0){
        return FALSE;
    }


    // if negative, flipping it
    // using temp string with copied contents
    char* temp = malloc((len+1)*(sizeof(char)));
    if (temp == 0){
        free(temp);
        return FALSE;
    }
    for (int i=0; i<len; i++){
        temp[i] = number[i];
    }
    temp[len] = '\0';
    int sign = 1;
    // check if negative
    if (number[0] == '1'){
        sign = -1;
        ones_complement(temp);

            // use one_bit_add recursively to add 1 at lowest and carry it up as needed
        char carry = '1';
        for (int i=len-1; i>=0; i--){
            char cin = carry;
            carry = '0';
            temp[i] = one_bit_add(temp[i], '0', cin, &carry);
        }
    }

    // temp should either be a copy of number if its positive,
    // or a twos complimented copy of number if negative, sign will note the sign

    // convert binary to decimal
    long n = unsigned_binary_to_integer(temp);
    free(temp);
    // temp string for converting decimal number to string
    char* temp2 = malloc((DECIMAL_MAX_DIGITS+1)*(sizeof(char)));
    if (temp2 == 0){
        free(temp2);
        return FALSE;
    }
    // do once incase n is 0, taking sign into account
    int i = 0;
    temp2[i] = (n%10)+48;
    n = n/10;
    i++;
    // then for loop for the rest
    while (i<DECIMAL_MAX_DIGITS && n != 0){
        temp2[i] = (n%10)+48;
        n = n/10;
        i++;
    }

    // add sign if needed
    if (sign == -1){
        temp2[i] = '-';
        i++;
    }

    // add terminator, copy contents to temp3, free temp2, reverse temp3
    temp2[i] = '\0';
    char* temp3 = malloc((strlen(temp2) + 1)*(sizeof(char)));
    strcpy(temp3, temp2);
    free(temp2);
    reverse(temp3);
    // return
    return temp3;

}