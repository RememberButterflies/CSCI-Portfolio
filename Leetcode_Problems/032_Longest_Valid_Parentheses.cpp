/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2026.04.26
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #32 Longest Valid Parentheses
 *          (https://leetcode.com/problems/longest-valid-parentheses/)
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

    //helper for going forward and finding invalid ')'
    bool* find_invalid_closes(string s, int start, int end){

        // size of result array
        int arrend = end-start+1;
        // return array. only concerned with start to end. so only need (end-start) + 1 cells. 
        bool *result = (bool*)malloc((sizeof(bool))*arrend);

        // preset all to valid
        for(int i=0; i<arrend; i++){
            result[i] = true;
        }

        // current scope
        int scope = 0;

        // main loop.
        // on every '(', new scope
        // on every ')' reduce scope
        // if reducing scope would make curr_scope < 0, then it is an invalid ')'
        // mark it invalid in result
        for(int i=start, j=0; i<=end; i++, j++){
            if(s[i]=='('){  // (
                // increase the scope
                scope++;
            }else{          // )
                scope--;
                if(scope<0){
                    // invalid ')'
                    result[j] = false;
                    scope = 0;
                }
            }
        }
        return result;
    }

    // helper for going backwards and finding invalid '('
    bool* find_invalid_opens(string s, int start, int end){

        // size of result array
        int arrend = end-start+1;
        // return array. only concerned with start to end. so only need (end-start) + 1 cells. 
        bool *result = (bool*)malloc((sizeof(bool))*arrend);

        // preset all to valid
        for(int i=0; i<arrend; i++){
            result[i] = true;
        }

        // current scope
        int scope = 0;

        // main loop.
        // on every ')', new scope
        // on every '(' reduce scope
        // if reducing scope would make curr_scope < 0, then it is an invalid '('
        // mark it invalid in result
        for(int i=end, j=arrend-1; i>=0; i--, j--){
            if(s[i]==')'){  // )
                // increase the scope
                scope++;
            }else{          // (
                scope--;
                if(scope<0){
                    // invalid '('
                    result[j] = false;
                    scope = 0;
                }
            }
        }
        return result;
    }


    // main function
    int longestValidParentheses(string s) {
        int size = s.length();      // the length of the string
        if (size<=1){               // size check, it takes at least two char's to return greater than 0
            return 0;
        }


        int start = 0;      // the index for the first valid '('
        int end = size-1;   // the index for the the last valid ')'
        while((start<size)&&(s[start]==')')){       // find real start
            start++;
        }
        while((end>=0)&&(s[end]=='(')){             // find real end
            end--;
        }

        bool *forward = find_invalid_closes(s,start,end);
        bool *backward = find_invalid_opens(s,start,end);

        // find longest chain of non-inavlids in both lists
        int max = 0;
        int temp = 0;
        for(int i=0; i<=end-start; i++){
            if((forward[i])&&(backward[i])){    // both good
                temp++;
                if(temp>max){   // check if temp is new biggest
                    max = temp;
                }
            }else{          // at least 1 bad, reset temp
                temp = 0;
            }
        }

        // free mem and return
        free(forward);
        free(backward);
        return max;
    }
};

