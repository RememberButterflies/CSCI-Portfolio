/**
 * @file convert.c
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






#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "convert.h"
#include "utility.h"


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
* @brief Takes the fraction portion of a decimal number as a string.
* Converts it to a binary number. Returns a string for the binary.
*
* @param number, string to be converted
* @param word_size, the size of the string returned
*/
char* fraction_to_binary(const char* number, int word_size){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // check for empty
    if (number[0] == '\0'){
        char* temp = malloc((1)*(sizeof(char)));
        if (temp == NULL){
            return FALSE;
        }
        temp[0] = '\0';
        return temp;
    }

    // allocate memory
    char* temp = malloc((word_size+1)*(sizeof(char)));
    if(temp == 0){
        return FALSE;
    }

    // length 
    size_t len = strlen(number);

    // populate with 0's
    for (int i = 0; i < word_size; i++){
        temp[i] = '0';
    }


    // convert number to long int numi
    long int numi = 0;
    for (int i = 0; i < len; i++){
        numi = numi*10;
        numi = numi + (number[i]-48);
        }

    // check for 0
    if (numi == 0){
        temp[1] = '\0';
        return temp;
    }

    // fill in temp using decimal to binary fraction method from assignment1
    int p = 0;
    while (p < BINARY_WORD_SIZE && numi != 0){
        numi = numi * 2;
        if (numi >= pow(10, len)){
            temp[p] = '1';
            numi = numi - pow(10, len);
        }
        p++;
    }



    // add terminator and return
    temp[p] = '\0';
    return temp;

}





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


/**
* @brief Takes an integer as an int. Adds the biased number, 127. 
* Converts to binary. Returns a string of the binary. 
*
* @param number, int to be converted
*/
char* int_to_biased_127(int number){
    // add bias value
    long int t = number;
    t = t + BIASED_VALUE;

    // get binary value
    char* temp = integer_to_binary(t, BINARY_WORD_SIZE);
    if (temp == NULL){
        free(temp);
        return FALSE;
    }

    // exten to biased max
    temp = extend_integer_binary(temp, BIASED_127_BINARY_MAX_DIGITS);
    if (temp == 0){
        free(temp);
        return FALSE;
    }

    return temp;

}






/**
* @brief Takes an integer as a string. Checks if its a valid 127-biased decimal number.
* converts it to an int. Calls int_to_biased_127 to get the biased binary as a string.
* Returns that string
*
* @param number, string to be converted
*/
char* to_biased_127(const char* number){

    // check if null
    if (number == 0){
        return FALSE;
    }

    //length and length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // check if valid biased
    if (is_biased_127_decimal(number) == 0){
        return FALSE;
    }

    // turn number into a long
    int t = 0;
    int bin = 0;
    int e = 0;
    int sign = 1;
    // check for sign
    // then convert rightmost character to number, times it by 10^e, add it to to
    // move i left, e++
    if (number[0] != '-' && number[0] != '+'){
        for (int i=len-1; i>=0; i--){
            bin = ((number[i])-48);
            bin = bin * pow(10, e);
            t = t+bin;
            e++;
        }
    } else {
        // there is a sign, check if negative
        if (number[0] == '-'){
            sign = -1;
        }
        for (int i=len-1; i>0; i--){
            bin = ((number[i])-48);
            bin = bin * pow(10, e);
            t = t+bin;
            e++;
        } 
    }
    // add sign back in
    t = t * sign;
    // convert to biased and return
    char* temp = int_to_biased_127(t);
    if (temp == 0){
        free(temp);
        return FALSE;
    }
    return temp;

}



/**
* @brief Takes a 127-biased number as a string. Calls 
* unsigned_binary_to_integer to get get its value as int.
* Subtracts the biased vaue, 127 and returns the int.
*
* @param number, string to be converted
*/
int int_from_biased_127(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    //length and length check
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // binary to int
    int n = unsigned_binary_to_integer(number);
    n = n - BIASED_VALUE;
    return n;


}



/**
* @brief Takes a 127-biased number as a string. Checks if valid.
* Converts it to an int. Converts int to string including sign. 
* Returns string.
*
* @param number, string to be converted
*/
char* from_biased_127(const char* number){
    // check for null
    if (number == 0){
        return FALSE;
    }

    // length and length check 
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // check if valid biased binary
    if (is_biased_127_binary(number) == 0){
        return FALSE;
    }

    // is valid
    // get integer equivelent of number
    int n = int_from_biased_127(number);

    // allocate memory 
    // biased maxed digits + 1 for sign + 1 for terminator
    char* temp = malloc((BIASED_127_BINARY_MAX_DIGITS+2)*(sizeof(char)));


    // convert n to string
    int bin = n;
    // first check for n = 0
    if (bin == 0){
        temp[0] = '0';
        temp[1] = '\0';
        return temp;
    } else if (bin < 0){
        // check for negative
        // reverse sign of n's temp int
        // take the remainder of bin / 10 and then take the 48th ascii character above the result and place it in temp
        // increment temp, until bin is 0
        // same thing for positive, but no sign added 
        int i = 0;
        bin = -bin;
        while(bin!=0){
            temp[i] = (bin % 10) + 48;
            bin = bin / 10;
            i++;
        }
        // add sign at end, then terminator, then reverse and return
        temp[i] = '-';
        temp[i+1] = '\0';
        reverse(temp);
        return temp;
    } else {
        // n is positive
        int i = 0;
        while(bin!=0){
            temp[i] = (bin % 10) + 48;
            bin = bin / 10;
            i++;
        }
        // add terminator, then reverse and return
        temp[i] = '\0';
        reverse(temp);
        return temp;
    }
    return FALSE;
}




/**
* @brief Takes unsigned binary integer portion and fraction portion of number as two strings, 
* and exponent value as an int pointer. Compares contents of integer and fraction to
* determine how to represent value. Returns string normalized value and updates exponent
* to the exponent value of the normalized value (2^exponent)
*
* @param integer, string to be converted
* @param fraction, string to be converted
* @param exponent, int* to be updated
*/
void normalize(char* integer, char* fraction, int* exponent){
    
    // check for nulls
    if (integer == 0 || fraction == 0){
        return;
    }

    // lengths
    size_t intlen = strlen(integer);
    size_t frclen = strlen(fraction);

    // location of first 1 in integer, 
    // go from start of integer until first one is found, set ione to its location and break
    // if no 1's, ione = -1
    int ione = -1;
    for (int i=0; (i < intlen) && (ione == -1); i++){
        if (integer[i] == '1'){
            ione = i;
        }
    }

    // if the first 1 is the last character, exponent is 0 and neither integer or fraction need updating
    if (ione == intlen-1){
        *exponent = 0;
        return;
    }

    // if there are no ones, check fraction for 1's
    int fone = -1;
    if (ione == -1){
        for (int i=0; (i < frclen) && (fone == -1); i++){
            if (fraction[i] == '1'){
                fone = i;
            }
        }

        // int has no 1's
        // if frac has no 1's (fone == -1), nothing needs to be updated
        if (fone == -1){
            *exponent = 0;
            return;
        }

        // else, int has no 1's and fract has at least 1.
        // must move fraction left until first 1 is last place of int
        // temp string for int and frac
        char* tempint = malloc((intlen+1)*(sizeof(char)));
        char* tempfrc = malloc((frclen+1)*(sizeof(char)));

        // set tempint to all 0's except final is 1 plus terminator
        for (int i=0; i < intlen-1; i++){
            tempint[i] = '0';
        }
        tempint[intlen-1] = '1';
        tempint[intlen] = '\0';

        // set tempfrc to 0's too
        for (int i=0; i<frclen; i++){
            tempfrc[i] = '0';
        }
        tempfrc[frclen] = '\0';

        // start moving fraction to the left, cutting the first 1 and noting exponent
        // exponent = -fone -1. if first 1 is in first spot, then fone =0, but exponent is -1
        // i is tempfrc position, j is fraction position start from the character after first 1
        for (int i=0, j=fone+1; j<frclen; i++, j++){
            tempfrc[i] = fraction[j];
        }
        // the remaining zeros should be already added and terminator as well
        // copy them over
        strcpy(integer, tempint);
        strcpy(fraction, tempfrc);
        fone = -fone;
        *exponent = fone - 1;
        free(tempint);
        free(tempfrc);
        return;
    } else {
        // integer has at least one 1 at integer[ione], and not at integer[intlen-1]
        // find if fraction has 1's
        for (int i=0; (i < frclen) && (fone == -1); i++){
            if (fraction[i] == '1'){
                fone = i;
            }
        }
        // fone is position of first 1 in fraction, or -1 if there is not any
        // make temp strings
        char* tempint = malloc((intlen+1)*(sizeof(char)));
        char* tempfrc = malloc((frclen+1)*(sizeof(char)));

        // set tempint to all 0's except final is 1 plus terminator
        for (int i=0; i < intlen-1; i++){
            tempint[i] = '0';
        }
        tempint[intlen-1] = '1';
        tempint[intlen] = '\0';

        // set tempfrc to 0's too
        for (int i=0; i<frclen; i++){
            tempfrc[i] = '0';
        }
        tempfrc[frclen] = '\0';

        // tempint is "000...0001" inlen
        // tempfrc is "000...000" frclen
        // copy all digits from right of ione to front of  tempfrc
        // i is tempfrc position, j is integer position
        int i = 0;
        int j = ione+1;
        while (i < frclen && j < intlen){
            tempfrc[i] = integer[j];
            i++;
            j++;
        }
        // then copy any remaining parts from fraction that can fit at end of tempfrac
        j = 0;
        while (i < frclen){
            tempfrc[i] = fraction[j];
            i++;
            j++;
        }

        // exponent is intlen - (ione+1)
        ione = ione+1;
        strcpy(integer, tempint);
        strcpy(fraction, tempfrc);
        *exponent = intlen - ione;
        free(tempint);
        free(tempfrc);
        return;
    }
    return;
}



/**
* @warning Does not work. Causes seg faults. Still under construction.
* 
* @brief Takes a real number as a string. Converts it to a signed floating point number. 
* Returns a string to that number.
*
* @param number, string to be converted
*/
char* to_floating_point(const char* number){


    // check for null
    if (number == 0){
        return FALSE;
    }

    // check if valid
    if (is_real(number) == 0){
        return FALSE;
    }

    // get integer  and fraction parts of real number
    char* intpart = get_integer_part(number);
    char* frcpart = get_fraction_part(number);
    if (intpart == 0 || frcpart == 0){
        return FALSE;
    }

    // get binary representation of the integer and fraction parts
    char* intbin = get_magnitude_binary(intpart, BINARY_WORD_SIZE);
    char* frcbin = fraction_to_binary(frcpart, BINARY_WORD_SIZE);
    if (intbin == 0 || frcbin == 0){
        return FALSE;
    }

    // extend binaries to binary word size
    intbin = extend_integer_binary(intbin, BINARY_WORD_SIZE);
    frcbin = extend_fraction_binary(frcbin, BINARY_WORD_SIZE);
    if (intbin == 0 || frcbin == 0){
        return FALSE;
    }

    // call to normalize
    int *expopoint = 0;
    normalize(intbin, frcbin, expopoint);

    int exponent = *expopoint;

    // get biased 127 representation
    char* expostr = int_to_biased_127(exponent);
    if (expostr == NULL){
        return FALSE;
    }

    // allocate enough memory for both parts
    char* result = malloc((strlen(intbin) + strlen(frcbin) + 1)*(sizeof(char)));
    if (result == 0){
        return FALSE;
    }

    // set sign bit of floating point number
    int i = 0;
    result[i] = intbin[0];
    i++;

    // copy contents of exponent after sign bit
    for (int j=0; j < strlen(expostr); j++, i++){
        result[i] = expostr[j];
    }

    // copy fractional portion
    for (int j=0; j < strlen(frcbin); j++, i++){
        result[i] = frcbin[j];
    }

    // add terminator
    result[strlen(intbin) + strlen(frcbin)] = '\0';
    free(expostr);
    free(intbin);
    free(frcbin);
    free(intpart);
    free(frcpart);
    return result;
}


/**
* @brief Takes a significand value as a string. Converts it to a long double
* Returns the long double. 
*
* @param sig, string to be converted
*/
double get_significand_value(const char* sig){

    // check for null
    if (sig == 0){
        return FALSE;
    }

    // length
    size_t len = strlen(sig);
    if (len == 0){
        return FALSE;
    }

    // check if valid
    if(is_significand(sig) == 0){
        return FALSE;
    }

    // convert significand to double
    double temp = 0;
    double bin = 0;
    for (int i = 0; i < len; i++){
        bin = (sig[i] - 48);       // take current digit
        bin = bin / (pow(2, i+1));  // divid it by 2^i+1
        temp = temp + bin;          // add it and move to next
    }

    // add 1
    temp = temp + 1;
    return temp;
}

/**
* @brief Takes a IEEE 754 number as a string. Extracts its exponent to a string
* Returns the string
*
* @param number, string to be converted
*/
char* extract_exponent(const char* number){
    char* temp = malloc((9)*(sizeof(char)));
    for (int i=0; i<8; i++){
        temp[i] = number[i+1];
    }
    temp[8] = '\0';
    return temp;
}


/**
* @brief Takes a IEEE 754 number as a string. Extracts its significand to a string
* Returns the string
*
* @param number, string to be converted
*/
char* extract_significand(const char* number){
    char* temp = malloc((24)*(sizeof(char)));
    for (int i=0; i<23; i++){
        temp[i] = number[i+9];
    }
    temp[23] = '\0';
    return temp;
}



/**
* @warning Does not work. Times out. Still under construction.
* 
* @brief Takes a floating point number as a string. Converts
* it to a real number. Returns a string of the real number
*
* @param number, string to be converted
*/
char* from_floating_point(const char* number){

    // check for null
    if (number == 0){
        return FALSE;
    }

    // check if valid
    if (is_floating_point(number) == 0){
        return FALSE;
    }

    // char* for getting 8 exponent digits
    char* expostr = malloc(9*(sizeof(char)));
    if (expostr == 0){
        return FALSE;
    }
    for (int i=0; i<8; i++){
        expostr[i] = number[i+1];
    }
    expostr[8] = '\0';

    // extract exponent part
    
    int expo = int_from_biased_127(expostr);



    // char* for significand digits
    char* sigstr = malloc(24*(sizeof(char)));
    if (sigstr == 0){
        return FALSE;
    }
    for (int i=0; i<23; i++){
        sigstr[i] = number[i+9];
    }
    sigstr[23] = '\0';

    // extract significand part
    long double sig = get_significand_value(sigstr);

    //Value = Sign * 2^Exponent * Significand
    sig = sig * pow(2, expo);

    // check sign
    if (number[0] == '1'){
        sig = -sig;
    }

    free(expostr);
    free(sigstr);
    

    // sig is long double of value
    // convert to string
    long double temp = sig;
    char* result = malloc((DECIMAL_MAX_DIGITS+2)*(sizeof(char)));
    
    // check for zero
    if (sig == 0){
        result[0] = '0';
        result[1] = '.';
        result[2] = '0';
        result[3] = '0';
        result[4] = '0';
        result[5] = '0';
        result[6] = '0';
        result[7] = '0';
        result[8] = '\0';
        return result;
    }

    // check if 0 < abs(sig) < 1
    // if so, 0.######
    // make an int, times sig by 10, if there is a result that exceeds 0, it will be less than 10 and can be collected as a character
    if (abs(sig) < 1){
        result[0] = '0';
        result[1] = '.';

        // the integer and fractional portions of sig
        long double sigint = (long double)((int)sig);
        long double sigfrc = sig - sigint;


        for(int i=2; i<8; i++){
            sigint = (long double)((int)(sigfrc*10));   // update sigint to be the integer value of sigfrc 1/10 position
            result[i] = sigint + 48;                // assign it to the string
            sigfrc = sigfrc*10;                     // increase sigfrc by 10 for next run
            sigint = (long double)((int)sigfrc);       // update sigint for remove to already recorded value
            sigfrc = sigfrc - sigint;                  // remove the recorded value from the integer portion
        }
        result[8] = '\0';
        return result;
    } else {
        // abs(sig) > 1
        // the integer and fractional portions of sig
        long double sigint = (long double)((int)sig);
        long double sigfrc = sig - sigint;

        // find number of digits above '.'
        int scale = 0;
        long double tempsc = sigint;
        while (tempsc >= 0){
            tempsc = tempsc / 10;
            scale++;
        }
        int bin = 0;
        // scale will equal number of digts above dot
        // go through integer portion,  taking the rightmost digit, and placing it in its position
        // moving left
        for (int i=scale-1; i >= 0; i--){
            bin = (int)sigint % 10;
            result[i] = bin + 48;
            bin = bin / 10;
        }

        // add dot
        result[scale] = '.';
        scale++;

        // fraction portion
        for(int i=scale; i<8; i++){
            sigint = (long double)((int)(sigfrc*10));   // update sigint to be the integer value of sigfrc 1/10 position
            result[i] = sigint + 48;                // assign it to the string
            sigfrc = sigfrc*10;                     // increase sigfrc by 10 for next run
            sigint = (long double)((int)sigfrc);       // update sigint for remove to already recorded value
            sigfrc = sigfrc - sigint;                  // remove the recorded value from the integer portion
        }
        result[8] = '\0';
        return result;
    }
    return FALSE;
}