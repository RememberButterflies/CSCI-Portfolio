/**
 * @file m.cpp
 * @author Patrick McGrath, CSCI 429, VIU
 * @version 1.0
 * @date October, 2025
 * 
 *  Assignment #2: Maximum Bitonic Sequence in an Array
 *  Copyright (C) 2025 Patrick McGrath
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

#include <iostream>         // for ui
#include <string>           // for ui
#include <limits.h>         // for INT_MIN
#include <cstdlib>          // for malloc / free


// defaults
int example[11] = {8,1,4,5,3,9,2,7,6,9,2};
int n_x = 11;

// globals
int n = INT_MIN;        // size of input sequence
int* seq = nullptr;     // the sequence
int* L = nullptr;       // rising values
int* R = nullptr;       // falling values

//function declarations
int MY_string_to_int(std::string s);    // convert string to integer
void freemem();                         // free arrays
void getSequence();                     // get user input for size and values of sequence
void getSequence_ex();                  // same but uses default values
int MBS();                              // top function, returns MBS or error code
int sizeofLeft(int p);                  // recursive call to finding cardinality of rising side
int sizeofRight(int p);                 // recursvie call to finding cardinality of falling side

// function defintions
// UI function - get integer value from user input
int MY_string_to_int(std::string s){
    int len = s.length();
    if (len <= 0){
        return INT_MIN;
    }

    bool neg = false;
    int result = 0;
    int tens = 1;
    int curr = 0;
    for (int i=len-1; i>0; i--){        // leave s[0] for last to check for '-' or '+'
        curr = s[i];
        if ((curr<'0') || (curr>'9')){
            return INT_MIN;
        }
        result += (curr-'0') * tens;
        tens *= 10;
    }

    // -int
    if (s[0] == '-'){
        return -result;
    }

    // +int
    if (s[0] == '+'){
        return result;
    }

    // ^[0-9]int
    if ((s[0]<'0') || (s[0]>'9')){
        return INT_MIN;
    }

    // [0-9][0-9]*
    result += (s[0]-'0')*tens;
    return result;


}

void freemem(){
    free(seq);
    free(L);
    free(R);
    return;
}

void getSequence(){

    // input string, input int
    std::string inp;
    int val = INT_MIN;

    // free prev memory
    freemem();

    // get size until valid
    while (n < 1){
        inp = "DEFAULT";
        std::cout << "size of sequence? ";
        std::cin >> inp;
        n = MY_string_to_int(inp);
    }
    
    //allocate memory, assign all undefined
    seq = (int*)malloc(n*sizeof(int));
    L = (int*)malloc(n*sizeof(int));    
    R = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++){
        L[i] = INT_MIN;
        R[i] = INT_MIN;
    }

    // get inputs
    for (int i=0; i<n; i++){
        val = INT_MIN;
        // get ith val, until valid input
        while (val == INT_MIN){
            inp = "DEFAULT";
            std::cout << i+1 << "th val? ";
            std::cin >> inp;
            val = MY_string_to_int(inp);
        }

        // add it to seq
        seq[i] = val;
        
    }

    //end
    return;
}

void getSequence_ex(){

    // free prev seq
    freemem();

    // assign n
    n = n_x;
    
    //allocate memory
    seq = (int*)malloc(n*sizeof(int));
    L = (int*)malloc(n*sizeof(int));    
    R = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++){
        L[i] = INT_MIN;
        R[i] = INT_MIN;
    }

    // get inputs
    int val = INT_MIN;
    for (int i=0; i<n; i++){
        val = example[i];
        // add it to seq
        seq[i] = val;
        
    }

    //end
    return;
}

int MBS(){

    
    // there must be elements
    if (n <= 0){
        return -1;
    }

    // result
    int result = INT_MIN;
    

    // loop through all elements, treating each one as the peak of its bitonic sequence.
    // The cardinality of MBS with p as its peak will double count p itself from each of the Left and Right calls, so temp has -1 at end
    // result is the largest of all the p's temps
    // Recursive calls are done by sizeofLeft and sizeofRight
    for (int p=0; p<n; p++){
        int temp = sizeofLeft(p) + sizeofRight(p) - 1;
        if (temp > result){
            result = temp;
        }
    }

    // return
    return result;
}

int sizeofLeft(int p){


    // check if memo'd already
    if (L[p] != INT_MIN){
        return L[p];
    }

    // base case
    // for rising (this function), p==0 is the base case. 
    // if seq[0] is the peak, then its rise can only include itself, and it must include itself. so L[0] = 1
    if (p == 0){
        L[p] = 1;
        return L[p];
    }

    // current max
    int curr = INT_MIN;

    // loop from p's left neighbor down to 0
    // if the value for seq[prev] is less or equal (rising) to seq[p], recursively get prev's sizeofLeft, add 1 for p itself
    // check if this is a greater max, and update current max if it is
    for (int prev = p-1; prev >= 0; prev--){
        if (seq[prev] < seq[p]){
            int temp = sizeofLeft(prev) + 1;
            if (temp > curr){
                curr = temp;
            }
        }
    }

    // check if any rise was discovered. if not, curr is 1 for p itself
    if (curr == INT_MIN){
        curr = 1;
    }
    // memo result and return
    L[p] = curr;
    return L[p];

}

int sizeofRight(int p){
    // check if memo'd already
    if (R[p] != INT_MIN){
        return R[p];
    }

    // base case
    // for falling (this function), p==(n-1) is the base case. 
    // if seq[n-1] is the peak, then its fall can only include itself, and it must include itself. so L[0] = 1
    if (p == (n-1)){
        R[p] = 1;
        return R[p];
    }

    // current max
    int curr = INT_MIN;

    // loop from p's right neighbor up to n-1
    // if the value for seq[next] is greater than or equal (falling) to seq[p], recursively get next's sizeofRight, add 1 for p itself
    // check if this is a greater max, and update current max if it is
    for (int next = p+1; next <= (n-1); next++){
        if (seq[next] < seq[p]){
            int temp = sizeofRight(next) + 1;
            if (temp > curr){
                curr = temp;
            }
        }
    }

    
    // check if any fall was discovered. if not, curr is 1 for p itself
    if (curr == INT_MIN){
        curr = 1;
    }
    // memo result and return
    R[p] = curr;
    return R[p];
}

// Main function
int main(){

    // user can choose to use example or their own input
    int choice_int = INT_MIN;
    std::string choice;
    while (choice_int == INT_MIN){
        std::cout << "use example (0) or your own input (1)? ";
        std::cin >> choice;
        choice_int = MY_string_to_int(choice);
    }

    // get size and values of sequence
    if (choice_int == 0){
        getSequence_ex();
    } else {
        getSequence();
    }

    //print seq
    std::cout << "seq[" << n << "] = { ";
    for (int j=0; j<n-1; j++){
        std::cout << seq[j] << ", ";
    }
    std::cout << seq[n-1] << " }" << std::endl;
    

    // run algorithm
    int result = MBS();



    //print L/R
    std::cout << "L[" << n << "] = { ";
    for (int j=0; j<n-1; j++){
        std::cout << L[j] << ", ";
    }
    std::cout << L[n-1] << " }" << std::endl;
    std::cout << "R[" << n << "] = { ";
    for (int j=0; j<n-1; j++){
        std::cout << R[j] << ", ";
    }
    std::cout << R[n-1] << " }" << std::endl;



    std::cout << "MBS of seq = " << result << std::endl;

    // freememory, goodbye
    freemem();
    std::cout << "Goodbye" << std::endl;
    return 0;
}