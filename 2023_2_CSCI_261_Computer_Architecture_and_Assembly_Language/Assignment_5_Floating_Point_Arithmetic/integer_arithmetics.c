/**
 * @file integer_arithmetics.c
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
#include <stddef.h>
#include "utility.h"
#include "convert.h"
#include "integer_arithmetics.h"





/**
* @brief Takes a string. Copies its contents into a new same-sized string.
*   Then, returns the copy.
*
* @param number, the string.
*/
char* copy_twos_complement(const char* number){

    // check for null and length
    if (number == FALSE){
        return FALSE;
    }
    size_t len = strlen(number);
    if (len == 0){
        return FALSE;
    }

    // new string
    char* temp = malloc((len+1)*(sizeof(char)));

    // copy contents
    for (int i =0; i < len; i++){
        temp[i] = number[i];
    }
    // add terminator
    temp[len] = '\0';

    // return
    return temp;
}


/**
* @brief Takes 2 strings, each representing a signed 2's complement integer of same length.
*   The two strings are added together using one_bit_add. The sum is returned.
*   Overflow is checked and if detected, FALSE is returned.
*
* @param number1, the first string.
* @param number2, the second string.
*/
char* add_twos_complement(const char* number1, const char* number2){
   
    // check for null and length
    if (number1 == FALSE || number2 == FALSE){
        return FALSE;
    }
    size_t len1 = strlen(number1);
    size_t len2 = strlen(number2);
    if (len1 == 0 || len2 == 0){
        return FALSE;
    }

    // temp string and char
    char* temp = malloc((BINARY_WORD_SIZE+1)*(sizeof(char)));
    temp[BINARY_WORD_SIZE] = '\0';
    char car = '0'; 

    //fill in temp
    for (int i = BINARY_WORD_SIZE - 1; i >= 0; i--) {
        temp[i] = one_bit_add(number1[i], number2[i], car, &car);
    }


    // check for overflow
    // if both operands share sign, result will share sign or be overflow
    // if both operands dont share sign, result shold be between the 2 and have one of the signs
    if (number1[0] == number2[0]){
        if (temp[0] != number1[0]){
            free(temp);
            return FALSE;
        }
    }

    return temp;

}




/**
* @brief Takes 2 strings, each representing a signed 2's complement integer of same length.
*   The second string is subtracted from the first. This is done by doing a 2's complement
*   on the second string and then adding them.
*
* @param number1, the first string.
* @param number2, the second string.
*/
char* subtract_twos_complement(const char* number1, const char* number2){

    // copy 2nd number into temp and get 2's complement
    char* temp = copy_twos_complement(number2);
    twos_complement(temp);

    // add 2's complement and first number
    char* result = add_twos_complement(number1, temp);

    // free mem and return
    free(temp);
    return result;
}


/**
* @brief Takes 2 strings, each representing a signed 2's complement integer of same length.
*   The 2 strings are multiplied together. Their product is returned as a string of twice length
*
* @param number1, the first string.
* @param number2, the second string.
*/
char* multiply_twos_complement(const char* number1, const char* number2){

    // check for 0 initially
    if ((strcmp(number1, "00000000000000000000000000000000") == 0) || (strcmp(number2, "00000000000000000000000000000000") == 0)){
        char* aq = malloc(((2*BINARY_WORD_SIZE)+1)*(sizeof(char)));
        for (int i = 0; i < (2*BINARY_WORD_SIZE); i++){
            aq[i] = '0';
        }
        aq[2*BINARY_WORD_SIZE] = '\0';
        return aq;
    }

    // allocate memory for temp aregister
    // initilize all to 0, add terminator
    char* aregister = malloc((BINARY_WORD_SIZE+1)*(sizeof(char)));
    for (int i = 0; i < BINARY_WORD_SIZE; i++){
        aregister[i] = '0';
    }
    aregister[BINARY_WORD_SIZE] = '\0';

    // q_1
    char* q_1 = malloc((2)*(sizeof(char)));
    q_1[0] = '0';
    q_1[1] = '\0';

    // copy number1, number2
    char* mregister = copy_twos_complement(number1);
    char* qregister = copy_twos_complement(number2);

    // booths algorithm
    int count = BINARY_WORD_SIZE;
    while (count > 0){

        // left branch Q0, Q-1 = 10
        if ((qregister[BINARY_WORD_SIZE-1] == '1') && (q_1[0] == '0')){
            char* tempa = subtract_twos_complement(aregister, mregister);
            if (tempa != FALSE){
                aregister = copy_twos_complement(tempa);
                free(tempa);
            }

            // right branch, Q0, Q-1 = 01
        } else if ((qregister[BINARY_WORD_SIZE-1] == '0') && (q_1[0] == '1')){
            char* tempa = add_twos_complement(aregister, mregister);
            if (tempa != FALSE){
                aregister = copy_twos_complement(tempa);
                free(tempa);
            }
        }

        // arithmatic shift
        group_arithmetic_shift_right(aregister, qregister, q_1, BINARY_WORD_SIZE);
        count--;
    }

    // count = 0
    // result is in A,Q
    char* aq = malloc(((2*BINARY_WORD_SIZE)+1)*(sizeof(char)));
    // copy aregister and qregister
    for (int i = 0; i < BINARY_WORD_SIZE; i++){
        aq[i] = aregister[i];
        aq[i+BINARY_WORD_SIZE] = qregister[i];
    }
    // add terminator
    aq[(2*BINARY_WORD_SIZE)] = '\0';
    
    //free mem
    free(mregister);
    free(aregister);
    free(qregister);
    free(q_1);

    // return
    return aq;

}
  


/**
* @warning Known to not work. The bug is in the remainder return.
*
* @brief Takes 2 strings, each representing a signed 2's complement integer of same length.
*   The first string is divided by the second. The quotient is returned and the remainder is updated.
*
* @param number1, the first string.
* @param number2, the second string.
* @param reminder, the remainder.
*/
char* divide_twos_complement(const char* number1, const char* number2, char* reminder){

    // allocate memory for temp aregister
    // initilize all to 0, add terminator
    char* aregister = malloc((BINARY_WORD_SIZE+1)*(sizeof(char)));
    for (int i = 0; i < BINARY_WORD_SIZE; i++){
        aregister[i] = '0';
    }
    aregister[BINARY_WORD_SIZE] = '\0';

    // copy number1 to qregister
    // copy number2 to mregister
    // if either register is neagtive, call twos complement on it
    char* qregister = copy_twos_complement(number1);
    char* mregister = copy_twos_complement(number2);
    if (qregister[0] == '1'){
        twos_complement(qregister);
    }
    if (mregister[0] == '1'){
        twos_complement(mregister);
    }



    // unsigned division algorithm
    int count = BINARY_WORD_SIZE;
    while (count > 0){

        // left shift,
        // then subtract (a = a-m) only if theres no overflow
        group_logical_shift_left(aregister, qregister, BINARY_WORD_SIZE);
        char* tempa = subtract_twos_complement(aregister, mregister);
        if (tempa != FALSE){
            aregister = copy_twos_complement(tempa);
        }
        free(tempa);


        // switch if A is negative or not
        // first positive, then negative
        // if positive, set last digit of qregister to 1
        // if negative, set qregisters final digit to 0 and a=a+m, if theres no overflow
        if (aregister[0] == '0'){
            qregister[BINARY_WORD_SIZE-1] = '1';
        } else {
            qregister[BINARY_WORD_SIZE-1] = '0';
            char* tempa = add_twos_complement(aregister, mregister);
            if (tempa != FALSE){
                aregister = copy_twos_complement(tempa);
            }
            free(tempa);
        }
        // decrement
        count--;
    }

    // quotient in q, remainder in a
    // determine sign of q and a
    // for q, if the input signs were the same, the output will be positive. if they mis-match, it will be negative
    if (number1[0] != number2[0]){
        twos_complement(qregister);
    }

    // for remainders sign,
    // if there is a remainder, it will share the numerator's sign
    if (strcmp(aregister, "00000000000000000000000000000000") != 0){
        if (number1[0] == '1'){
            twos_complement(aregister);
        }
    }

    // update the remainder    
    for (int i = 0; i < BINARY_WORD_SIZE; i++){
        reminder[i] = aregister[i];
    }
    reminder[BINARY_WORD_SIZE] = '\0';

    // free memory and return
    free(aregister);
    free(mregister);
    return qregister;
}
 

char* divide_twos_complement_significand(const char* number1, const char* number2){
    return FALSE;
}