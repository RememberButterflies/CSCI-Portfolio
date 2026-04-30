/**
 * @file m.cpp
 * @author Patrick McGrath, CSCI 429, VIU
 * @version 1.0
 * @date September, 2025
 * 
 *  Assignment #1: Optimal Cost of Binary Search Tree
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



// global variables          
int* arr = (int*)nullptr;               // values array starts with no allocation
int* fre = (int*)nullptr;               // frequncy array
int* ARR = (int*)nullptr;
int** fre_ranges = (int**)nullptr;     // a 2d matrix for memoizing ranges in the frequency array, before recursive calls to recalculate them
int Xarr[9] = {1,   3,  8,  15, 19, 22, 28, 35, 44};
int Xfre[9] = {60,  40, 3,  5,  17, 35, 19, 22, 6};
int XARR[9] = {0};
int Xfre_ranges[9][9] = {0};
int Xarrsize = 9;
int arrsize = 0;                // max size of array
int prev = INT_MIN;             // previous value in array for making sure input is sorted
std::string input = "?";        // UI variable - string for user input
int inputval = INT_MIN;
bool inited = false;            // UI variable - bool for indicating that initialization has already occured this session, to avoid double free
enum command_code {             // UI variable - enum for switching user input
    quit,
    initiate,
    opt_cost,
    help,
    example,
    print_range,
    invalid
};
command_code com = invalid;     // UI variable - the code corresponding to user input
int arr_get = INT_MIN;


// function declarations
void init(int n);
int OptCost(int i, int k);
void help_print();                                  // UI function - print help menu
command_code get_command_code(std::string input);   // UI function - get command code from user input
int MY_string_to_int(std::string s);                // UI function - get integer value from user input
void freemem();
void calc_ranges();
void printRange();


// allocates memory for n ADT_thing elements for arr, and assigns starttime, notes that init has been set
void init(int n){
    arr = (int*)malloc(n * sizeof(int));
    fre = (int*)malloc(n * sizeof(int));
    ARR = (int*)malloc(n * sizeof(int));
    fre_ranges = (int**)malloc(n * sizeof(int*));
    for (int i=0; i<n; i++){
        fre_ranges[i] = (int*)malloc(n * sizeof(int));
    }
    inited = true;

}

// free allocated memory
void freemem(){
    free(arr);
    free(fre);
    free(ARR);
    for (int i=0; i<arrsize; i++){
        free(fre_ranges[i]);
    }
    free(fre_ranges);
}


void calc_ranges(){         //O(n^2)

    // arrsize is size of both dimensions
    // fre_ranges is the matrix
    // do single node first
    fre_ranges[0][0] = fre[0];  // single node
    //then do, m==0, before rest of loop
    for (int n=1; n<arrsize; n++){                         
        fre_ranges[0][n] = fre[n] + fre_ranges[0][n-1]; // sum range from m to n (n is >m)
    }

    for (int m=1; m<arrsize; m++){
        for (int n=0; n<arrsize; n++){
            int temp = fre_ranges[m-1][n]-fre[m-1];
            if (temp < 0){
                fre_ranges[m][n] = 0;
            } else {
                fre_ranges[m][n] = fre_ranges[m-1][n]-fre[m-1];
            }
        }
    }
    return;
}

void printRange(){
    for (int m=0; m<arrsize; m++){
        for (int n=0; n<arrsize; n++){
            std::cout << "fre_ranges[" << m << "][" << n << "]= " << fre_ranges[m][n] << std::endl;
        }
    }
}






int OptCost(int i, int k){
    // sum portion
    int sum = 0;
    if (i>k){
        return 0;
    } else {
        sum = fre_ranges[i][k]; // retrieve from matrix
    }


     //less portion
    int minimum = INT_MAX;
    for (int r=i; r<=k; r++){
        int left = OptCost(i, r-1);
        int right = OptCost (r+1, k);
        int temp = 0;
        if ((left != -1) && (right != -1)){
            temp = left + right;
        }
        if ((temp < minimum) && (temp >= 0)){
            minimum = temp;
        }
    }
 
    // return
    return sum + minimum;


}

// UI function - print help menu
void help_print(){
    std::cout << "Choose from the following options:" << std::endl;
    std::cout << "      (i):    init();         initialize the array's memory for " << arrsize << " elements." << std::endl;
    std::cout << "      (o):    Optcost(i,j);   get the opt cost from i to j, if its valid." << std::endl;
    std::cout << "      (x):    example         run with example data" << std::endl;
    std::cout << "      (p):    print the frequency ranges matrix" << std::endl;
    std::cout << "      (q):    quit            quit this program and free memory." << std::endl;
    std::cout << "      (h):    help            help, prints this message" << std::endl;
    std::cout << std::endl;
}

// UI function - get command code from user input
// switches based on the first char of input.
// 5 options:
    // i = init
    // o = opt_cost
    // q = quit
    // h = help
    // (x):    example
command_code get_command_code(std::string input){
    if (input.length() <= 0){
        return invalid;
    }
    switch (input[0]){
        case 'i':
        case 'I':
            return initiate;
            break;
        case 'o':
        case 'O':
            return opt_cost;
            break;
        case 'q':
        case 'Q':
            return quit;
            break;
        case 'h':
        case 'H':
            return help;
            break;
        case 'x':
        case 'X':
            return example;
            break;
        case 'p':
        case 'P':
            return print_range;
        break;
        default:
            return invalid;
            break;
    }

    return invalid;
}


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

    if (s[0] == '-'){
        return -result;
    }

    if (s[0] == '+'){
        return result;
    }

    if ((s[0]<'0') || (s[0]>'9')){
        return INT_MIN;
    }

    result += (s[0]-'0')*tens;
    return result;


}



// Main function, start of session
int main(){

    
    help_print();       // start with help menu print


    // while loop for ui
    // while the command is not quit, keep asking for and processing commands 
    while (com != quit){

        // ask for commnd, get it, conver it to command code, reset input string
        std::cout << "Enter a command --(h) for help or (q) to quit" << std::endl;
        std::cin >> input;
        com = invalid;
        com = get_command_code(input);
        input = "?";


        // handle command
        switch (com){

            // Quit
            case quit:

                // free memory from last init
                if (inited){
                    freemem();
                }
                std::cout << "Goodbye" << std::endl;
                break;

            // init
            case initiate:

                // only free memory if it has been allocated previously this session
                // need to free memory, because new n value might be different (bigger)
                if (inited){
                    freemem();
                }

                // reset arrsize, and ask for new one until valid int >0 is given
                arrsize = 0;
                while (arrsize <= 0){
                    std::cout << "What is the size of the array?" << std::endl;
                    std::cin >> input;
                    arrsize = MY_string_to_int(input);
                }

                // init (memory allocation and start time get)
                init(arrsize);
                std::cout << "Memory has been initialized " << std::endl;
                prev = INT_MIN;
                for (int curr=0; curr<arrsize; curr++){
                    inputval = INT_MIN;
                    while ((inputval == INT_MIN) || (inputval <= prev)){
                        std::cout << "What is the " << curr << "th value? (must be above " << prev << ")" << std::endl;
                        std::cin >> input;
                        inputval = MY_string_to_int(input);
                    }
                    arr[curr] = inputval;
                    prev = arr[curr];
                    inputval = INT_MIN;
                    while (inputval < 0){
                        std::cout << "What is the " << curr << "th frequency?" << std::endl;
                        std::cin >> input;
                        inputval = MY_string_to_int(input);
                    }
                    fre[curr] = inputval;
                }
                calc_ranges();      // calculate frequency ranges matrix
                break;


            // get
            case opt_cost:

                // only attempt to retrieve data if memory has been allocated
                if (inited){

                    

                    // get value from array
                    //arr_get = OptCost(0, arrsize-1);
                    arr_get = OptCost(0, arrsize-1);

                    // check if data was valid (start time matches init's start time)
                    if (arr_get != INT_MIN){
                        // valid data
                        std::cout << "OptCost at index is " << arr_get << std::endl;
                    } else {
                        // invalid data
                        std::cout << "OptCost is NO_VAL. (" << arr_get << ")" << std::endl;
                    }
                } else {

                    // tell user to use init first
                    std::cout << "Initialize memory first" << std::endl;
                }
                arr_get = INT_MIN;
                break;

            case example:
                if (inited){
                    freemem();
                }

                init(Xarrsize);
                
                for (int copy=0; copy<Xarrsize; copy++){
                    arr[copy] = Xarr[copy];
                    fre[copy] = Xfre[copy];
                    ARR[copy] = XARR[copy];
                }
                arrsize = Xarrsize;
                calc_ranges();      // calculate frequency ranges matrix
                std::cout << "example values loaded" << std::endl;
                break;

            // help
            case help:
                help_print();
                break;

            case print_range:
                if (inited){
                    printRange();
                }else {
                    // tell user to use init first
                    std::cout << "Initialize memory first" << std::endl;
                }
                break;

            // other input received
            case invalid:
                break;
            default:
                break;
        }
    }
    return 0;
}