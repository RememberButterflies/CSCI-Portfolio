/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.07.09
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #12 Integer to Roman
 *          (https://leetcode.com/problems/integer-to-roman/)
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
    string intToRoman(int num) {

        /*
            variables
            in = copy of input
            result = output roman numeral
            tens = tens place of the input digit
            cNum = current digit from input
            next = string of current digit in its position
            skip = wether that digit requires a string value, like the '0' in "10"
        */
        int in = num;
        string result = "";
        int tens = 1;
        int cNum = 0;
        string next = "x";
        bool skip = false;


        // while the input is not exhausted, move right to left on input number
        // get right most digit from input
        // move input rightwards
        // switch on digits position.
        // nested switches, switched on value of digit
        // build substring
        // then, if not skip, add to front of result
        while (in != 0){
            cNum = in % 10;
            in = in / 10;
            switch (tens){
                case 1:
                    switch (cNum){
                        case 0:
                            skip = true;
                            next ="X";
                            break;
                        case 1:
                            next = "I";
                            break;
                        case 2:
                            next = "II";
                            break;
                        case 3:
                            next = "III";
                            break;
                        case 4:
                            next = "IV";
                            break;
                        case 5:
                            next = "V";
                            break;
                        case 6:
                            next = "VI";
                            break;
                        case 7:
                            next = "VII";
                            break;
                        case 8:
                            next = "VIII";
                            break;
                        case 9:
                            next = "IX";
                            break;
                        default:
                            break;
                    }
                    break;
                case 10:
                    switch (cNum){
                        case 0:
                            skip = true;
                            next ="X";
                            break;
                        case 1:
                            next = "X";
                            break;
                        case 2:
                            next = "XX";
                            break;
                        case 3:
                            next = "XXX";
                            break;
                        case 4:
                            next = "XL";
                            break;
                        case 5:
                            next = "L";
                            break;
                        case 6:
                            next = "LX";
                            break;
                        case 7:
                            next = "LXX";
                            break;
                        case 8:
                            next = "LXXX";
                            break;
                        case 9:
                            next = "XC";
                            break;
                        default:
                            break;
                    }
                    break;
                case 100:
                    switch (cNum){
                        case 0:
                            skip = true;
                            next ="X";
                            break;
                        case 1:
                            next = "C";
                            break;
                        case 2:
                            next = "CC";
                            break;
                        case 3:
                            next = "CCC";
                            break;
                        case 4:
                            next = "CD";
                            break;
                        case 5:
                            next = "D";
                            break;
                        case 6:
                            next = "DC";
                            break;
                        case 7:
                            next = "DCC";
                            break;
                        case 8:
                            next = "DCCC";
                            break;
                        case 9:
                            next = "CM";
                            break;
                        default:
                            break;
                    }
                    break;
                case 1000:
                    switch (cNum){
                        case 0:
                            skip = true;
                            next ="X";
                            break;
                        case 1:
                            next = "M";
                            break;
                        case 2:
                            next = "MM";
                            break;
                        case 3:
                            next = "MMM";
                            break;
                        case 4:
                            skip = true;
                            next ="X";
                            break;
                        case 5:
                            skip = true;
                            next ="X";
                            break;
                        case 6:
                            skip = true;
                            next ="X";
                            break;
                        case 7:
                            skip = true;
                            next ="X";
                            break;
                        case 8:
                            skip = true;
                            next ="X";
                            break;
                        case 9:
                            skip = true;
                            next ="X";
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            if (!skip){
                result = next + result;

            }
            skip = false;
            tens = tens*10;
        }
        return result;
    }
};