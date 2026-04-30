/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.08.24
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #65 Valid Number
 *          (https://leetcode.com/problems/valid-number/)
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

class Solution {
public:
    bool isNumber(string s) {
        int len = s.length();
        if (len == 0){
            return false;
        }
        if (len == 1){
            if ((s[0]<'0')||(s[0]>'9')){
                return false;
            }
        }

        if (case_int(s, len, 0)){
            return true;
        }

        if (case_dec(s, len, 0)){
            return true;
        }      

        return false;
    }

private:

// check for ints
    bool case_int(string s, int len, int start){
        
        int i = start;  // index through s
        char curr = s[i];   // char of index
        bool int_found = false;


        // check for + and -
        if ((curr == '-') || (curr == '+')){
            i++;    // move
            if (i == len){  // check if only +/-
                return false;
            }
            if (i < len){
                curr = s[i];
            }
        }

        // move i through all int values
        while ((i<len) && (curr >= '0') && (curr <= '9')){
            if (!int_found){
                if ((curr >= '0') && (curr <= '9')){
                    int_found = true;
                }
            }
            i++;
            if (i < len){
                curr = s[i];
            }
        }

        // check if at end 
        if ((i == len) && (i != 0)){
            return true;
        }

        // not end, move curr
        // check for exponent. only do so if start was 0
        if ((start == 0) && ((curr == 'e') || (curr == 'E')) && (i != 0) && (int_found)){
            // move i, and check if remainder is int
            i++;
            if (i < len){
                if (case_int(s, len, i) == true){
                    return true;
                } else {
                    return false;
                }
            }
        }

        // if here, it failed
        return false;
    }

    bool case_dec(string s, int len, int start){



        int i = start;
        char curr = s[i];
        bool dot_found = false;
        bool int_found = false;
        int dot_pos = -1;
    
        // check for + and -
        if ((curr == '-') || (curr == '+')){
            i++;    // move
            if (i == len){  // check if only +/-
                return false;
            }
            if (i < len){
                curr = s[i];
            }
        }



        // move i through all int values and dots. false if more than 1 dot. note pos of single dot
        while ((i<len) && ((curr >= '0') && (curr <= '9')) || (curr == '.')){

            if (curr == '.'){
                if (!dot_found){
                    dot_found = true;
                    dot_pos = i;
                } else {
                    return false;
                }
            }
            if (!int_found){
                if ((curr >= '0') && (curr <= '9')){
                    int_found = true;
                }
            }
            i++;
            if (i < len){
                curr = s[i];
            } else {
                curr = 'X';
            }
        }




        // check if at end 
        if ((i == len) && (i != 0) && (int_found)){
            return true;
        }

        // not end, move curr
        // check for exponent. only do so if start was 0
        if ((start == 0) && ((curr == 'e') || (curr == 'E')) && (i != 0) && (int_found)){
            // move i, and check if remainder is int
            i++;
            if (i < len){
                if (case_int(s, len, i) == true){
                    return true;
                } else {
                    return false;
                }
            }
        }


        return false;
    }
};