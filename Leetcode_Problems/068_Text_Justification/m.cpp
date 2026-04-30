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
 *      Leetcode #68 Text Justification
 *          (https://leetcode.com/problems/text-justification/)
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

    // finds the index of the end of the current line, given the words / maxwidth / index of start
    int find_end_of_line(vector<string>& words, int maxWidth, int first_word){
        //int start = first_word;                     // index of start
        // check if out of bounds
        if (first_word >= words.size()){
            return first_word;
        }
        int end = first_word;                       // index of end. note if only 1 word, start == end
        int line_size = words[first_word].size();   // size of the current line, starting with first word size, excluding spaces
        if (line_size >= maxWidth){                 // check if 1 word is enough
            return end;
        }
        int numwords = 1;                           // number of words in current line
        int end_of_words = words.size()-1;            // bounds for line
        bool done = false;                          // escape value


        // while not done, keep going
        while (!done){

            // check if at end of words
            if (end>=end_of_words){
                done = true;
            }else if((line_size + numwords + words[end+1].size())<=maxWidth){      // check if next word is small enough to fit
            // maxwidth >= (line_size + numwords - 1)
            // this is for; the length of the current words + at least 1 space between them, but not at the ends. 
            // so for next word, add 1 more space and the length of the next word
            // maxwidth >= (line_size + numwords + words[end+1].size())

                // can add next word
                end++;                              // move end
                line_size += words[end].size();    // add length
                numwords++;                         // increase num of words
            }else{
                // cant add next word. we are at end
                done = true;
            }
        }

        // end is at end
        return end;
    }

    // pad end with spaces
    // takes line by reference, and will pad until length is width
    void padend(string& line, int width){
        int size = line.size();
        int i = 0;
        while(size<width){
            line += " ";
            size++;
        }
        return;
    }
    
    // add spaces to end
    // takes line by reference, and will add numspaces spaces to end. 
    void addspaces(string& line, int numspaces){
        for(int i=0; i<numspaces; i++){
            line += " ";
        }
        return;
    }

    // main function
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        /*
        idea:
            at start of new line add the next word to the output line
            1st check to see if single word is >=maxWidth, (will not exceed, so == is all thats neeed) 
                this output line is complete, move onto next.
            else, log 
                    number of words
                    line length (linelength = sum(length of words) + (number of words) - 1) // at least 1 space inbetween
            while (line length < maxwidth){
                temp get next word. 
                if adding temp word to line doesnt make line length go above maxwidth, add it
                else, break loop
            }
            justify:
                log total spaces needed, maxwidth

        */

        vector<string> result;          // return vector
        int num_words = words.size();   // number of words to do total
        int num_words_in_line = 0;      // number of words in current line being produced
        int line_len = 0;               // length of current line so far
        int line_len_word = 0;          // length of just the words in the current line
        string curr_line = "";          // the current line being produced
        int words_start = 0;            // index in words for start of current line
        int words_end = find_end_of_line(words, maxWidth, words_start);              // index in words for end of current line
        bool done = false;              // escape for whole thing


        //while words not empty
        while(!done){
                // start and end should be got from last run or init
                /*
                    figure spacing;
                    cases:
                        1)  single word -   left justified  (no space on left, all spaces on right)
                        2)  final line  -   left justified  (no space on left, single space inbetween words, all spaces on right)
                        3)  normal case -   left and right  (no space on left or right, split the maxwidth-line_len_word over the spaces between the words in the line)
                */
            if (words_start==words_end){
                // case 1
                // single word,
                // add word
                curr_line += words[words_end];
                line_len_word += words[words_end].size();
                // pad end
                if (line_len_word<maxWidth){
                    padend(curr_line, maxWidth);
                }
                // add line to vector
                result.push_back(curr_line);
            } else if (words_end==(num_words-1)){
                // case 2
                //    add all the words, 1 space inbetween, then pad end
                while (words_start<words_end){
                    curr_line += words[words_start];
                    curr_line += ' ';
                    words_start++;
                }
               // last word, no final space
                curr_line += words[words_start];
               // add final spaces
                padend(curr_line, maxWidth);
               // add line to vector
                result.push_back(curr_line);
            } else {
                // case 3
                // get size of just the words no spaces
                for (int i=words_start; i<=words_end; i++){
                    line_len_word += words[i].size();
                }
                // get number of spaces, minimum 1 space between each word
                int numspaces = words_end-words_start;
                // the size of each space using floor division
                int space_size = (maxWidth - line_len_word) / numspaces;
                // the remaining spaces needed
                int space_remainder = maxWidth - (space_size*numspaces) - line_len_word;
                /*
                    every space gets space_size ' 's.
                    the 1st space_remainder spaces get 1 more
                */
                while (words_start<words_end){
                    curr_line += words[words_start];    // add word to line
                    words_start++;
                    if (space_remainder > 0){   // 1st space_remainder spaces
                        addspaces(curr_line, space_size+1);
                        space_remainder--;
                    }else{                      // the remaining spaces
                        addspaces(curr_line, space_size);
                    }
                }
                curr_line += words[words_start];    // add last word
                result.push_back(curr_line);        // push line to vector
            }
            // if here, current line is done
            // need to see if we are done entirely
            words_start = words_end + 1;    // next word is right after previous end
            if (words_start >= num_words){
                // at end
                done = true;
            } else{
                // not done, reset variables and get new end
                words_end = find_end_of_line(words, maxWidth, words_start);
                curr_line = "";
                num_words_in_line = 0;
                line_len = 0;
                line_len_word = 0;
            }
        }
        // done entirely, return
        return result;
    }
};
