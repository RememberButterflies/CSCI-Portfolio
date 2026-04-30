/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.07.05
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #3 Longest Substring Without Repeating Characters
 *          (https://leetcode.com/problems/longest-substring-without-repeating-characters/)
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
    int lengthOfLongestSubstring(std::string s) {
        // variables
        /*
            len = length of s
            longest = current longest (result)
            i = start of substring
            c = end of substring
            currLen = length of current subtring (i to c)
            found = helper for checking if match is found
        */
        int len = s.length();
        // check for trivial length
        if (len <= 1){
            return len;
        }
        // if not trivial, than at least 1 char is longest
        int longest = 1;
        int currLen = 1;
        int i = 0;
        // go through initial repeating chars to find true start
        while ((i < (len-1)) && (s[0] == s[i+1])){
            i++;
        }
        // set c to next char after i is found
        int c = i+1;
        bool found = false;

        // while the start of the substring is less than the (end of the input string)-(the current longest) and c is still within bounds of s
        while ((i < (len - longest)) && (c <= len)){
            // check if s[c] == (s[i] to s[c-1])
            for (int j=i; ((j<=(c-1)) && (!found)); j++){
                if (s[c] == s[j]){
                    // found, then move i to after j and use the remaing portion of the substring
                    found = true;
                    i = j+1;
                }
            }
            // set the currLen and check if its the new longest
            currLen = (c-i)+1;
            if (currLen > longest){
                longest = currLen;
            }

            // move c and reset found
            c++;
            found = false;
        }

        // return longest
        return longest;


    }
};