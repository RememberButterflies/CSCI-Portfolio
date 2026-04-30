/**
 * @file    ftp_server_string_util.cpp
 * @author  Patrick McGrath, CSCI 460, VIU
 * @version 1.0.0
 * @date    April 7, 2025
 *
 * @brief   File contains functions for;
 *      - 
 * 
 * 
 * 
 *      Project #2 File Transfer Protocol (FTP) Server Software Application
 *          Copyright (C) 2025  Patrick McGrath
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

// Includes
#include <string.h>
#include "ftp_server_string_util.h"


// Functions
void replaceAll(char* str, char find, char replace){
    // Check for parameters
    if (str == nullptr){
        return;
    }

    // Replace characters
    size_t length = strlen(str);
    for (int i=0; i<length; i++){
        if (str[i] == find){
            str[i] = replace;
        }
    }
    // End
    return;
}







/**
 * @brief Check if a string starts with a given prefix.
 * 
 * @param str The string to check.
 * @param prefix The prefix to check for.
 * 
 * @return true if the string starts with the prefix, false otherwise.
 */
bool startsWith(const char* str, const char* prefix){
    // Check for parameters
    if ((str == nullptr) || (prefix == nullptr)){
        return false;
    }

    // Check if str is shorter than prefix
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (str_length < prefix_length){
        return false;
    }

    // If both not null and prefix is "", then true by default
    if (strcmp(prefix, "") == 0){
        return true;
    }

    // Check the first prefix length of str, returning false on mismatch
    for (size_t i=0; i<prefix_length; i++){
        if (str[i] != prefix[i]){
            return false;
        }
    }

    // All is good
    return true;
}







/**
 * @brief Check if a string contains a given substring.
 * 
 * @param str The string to check.
 * @param substr The substring to check for.
 * 
 * @return true if the string contains the substring, false otherwise.
 */
bool contains(const char* str, const char* substr){
    // Check for parameters
    if ((str == nullptr) || (substr == nullptr)){
        return false;
    }

    // Check if str is shorter than substr
    size_t str_length = strlen(str);
    size_t substr_length = strlen(substr);
    if (str_length < substr_length){
        return false;
    }

    // If both not null and substr is "", then true by default
    if (strcmp(substr, "") == 0){
        return true;
    }

    // Check from beginning of str to see if each chr is the start for substr
    for (size_t i=0; i<(str_length-substr_length+1); i++){
        // if match on first char of substr, check for rest of it
        if (strncmp(&str[i], substr, substr_length) == 0) {
            return true;
        }
    }    
    // Return result
    return false;
}












void toUpper(char* str){
    // Check parameter
    if (str == nullptr){
        return;
    }


    // Change each alpha lower to alpha upper using ASCII values
    size_t len = strlen(str);
    for (size_t i=0; i<len; i++){
        if ((str[i] >= 97) && (str[i] <= 122)){
            str[i] = (str[i]) - 32;
        }
    }

    // Done
    return;
}
//Change all characters of 'str' to upper case.













void toLower(char* str){
    // Check parameter
    if (str == nullptr){
        return;
    }


    // Change each alpha upper to alpha lower using ASCII values
    size_t len = strlen(str);
    for (size_t i=0; i<len; i++){
        if ((str[i] >= 65) && (str[i] <= 90)){
            str[i] = (str[i]) + 32;
        }
    }

    // Done
    return;
}
//Change all characters of 'str' to lower case.











void stripLeadingAndTrailingSpaces(char* str){
    // Check parameter
    if (str == nullptr){
        return;
    }


    // Get length and check for ""
    size_t len = strlen(str);
    if (len == 0){
        return;
    }
    size_t start = 0;
    size_t end = len-1;

    // Iterate through first spaces to find start of text
    while ((start < len) && (str[start] == ' ')){
        start++;
    }
    
    // Iterate through last spaces to find end of text
    while ((end >= start) && ((str[end]) == ' ')){
        end--;
    }

    // Check if all spaces
    if (start >= end){
        return;
    }

    // Iterate through str from 0 replacing each character with it's + start value
    for (size_t i=0; (i+start)<=end; i++){
        str[i] = str[i+start];
    }

    // Add null terminator
    str[end - start + 1] = '\0';

    // End
    return;
}
//Remove all the spaces, if there is any, from the beginning and the ending of 'str'.













void stripNewlineAtEnd(char* str){
    // Check parameter
    if (str == nullptr){
        return;
    }


    // Get length and check for no length
    size_t len = strlen(str);
    if (len == 0){
        return;
    }

    if (str[len-1] == '\n'){
        str[len-1] = '\0';  // Replace the newline with null terminator
    }
    return;
}
//Remove new line character ('\n'), if there is any, from the end of 'str'.