/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.07.08
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #6 Zigzag Conversion
 *          (https://leetcode.com/problems/zigzag-conversion/)
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
    string convert(string s, int numRows) {
        // size 1 is trivial
        if (numRows == 1){
            return s;
        }

        // numRows > 1, need size of string
        int len = s.size();

        // if numRows >= len, result is a vertical line = horizontal line
        if (numRows >= len){
            return s;
        }

        // variables for zigzagging
        /*
            result = result string
            i = result's index 
            j = index of result
            v = the length of the "V" shape made by the zigzag
            q = the offset within the v for that given row
            right = if you are on the RHS of the V for the offset
            r =  the current row number
        */
        string result(len, '?');
        int i = 0;
        int j = 0;
        int v = 2*(numRows-1);
        int q = 0;
        bool right = false;
        int r = 0;



        // top line
        while (j<len){
            result[i] = s[j];
            j = j+v;
            i++;
        }
        r++;

        //middle line(s)
        while (r < (numRows-1)){
            q = v-(r*2);    // start on left side of V
            j = r;
            right = false;
            while (j<len){
                result[i] = s[j];
                i++;
                j = j+q;

                // need to swap sides
                if (!right){
                    q = v-q;
                    right = true;
                } else {
                    q = v-(r*2);
                    right = false;
                }
                
            }
            r++;
        }

        // last line
        j = r;
        while (j<len){
            result[i] = s[j];
            j = j+v;
            i++;
        }

        return result;
    }
};