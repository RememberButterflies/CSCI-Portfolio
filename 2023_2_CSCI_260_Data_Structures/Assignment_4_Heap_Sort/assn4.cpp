/**
 * @file asn4.cpp
 * @author Patrick McGrath, VIU
 * @version 1.0
 * @date November 10, 2023
 * 
 *  Assignment #4 - Heap Sort Program
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

#include <iostream>
#include <string>




// declarations
bool checkheap(int arr[], int num);
int peak_heap(int arr[]);
void heapify(int arr[], int num, int i);
void heapsort(int arr[], int num);
void createheap(int arr[], int num);
void printheap(int arr[], int num);


// functions
// checks if passed array and its size are a valid max heap
bool checkheap(int arr[], int num){

    // check for single item array, 1 item is heap
    if (num == 1){
        return 1;
    }

    // check root first
    // num will be at least 2
    if (arr[1] > arr[0]){
        return 0;
    }
    // check right child if there is one
    if (num >= 3){
        if (arr[2] > arr[0]){
            return 0;
        }
    }

    // check remaining 1 to n/2 cells
    // the remaining cells will be leaf nodes
    for (int i=1; i <= num/2; i++){
        // left child
        // gets its index
        // check if that is out of bounds
        // then do comparison
        // same for right
        int l = (2*i) + 1;
        if (l <= num-1){
            if (arr[l] > arr[i]){
                return 0;
            }
        }
        //right child
        int r = (2*i) + 2;
        if (r <= num-1){
            if (arr[r] > arr[i]){
                return 0;
            }
        }
    }

    //tests passed
    return 1;
}


// returns the max value in max heap
int peak_heap(int arr[]){
    // first element is max in max heap
    return arr[0];
}

// recursively called function for heapifying
// takes array of numbers, the size of array, and the index that is being heapified
// call on root to heapify.
void heapify(int arr[], int num, int i){

    // starting from beginning, see if element
    // is largest compared to children.
    // if not, swap with its largest child and heapify on the location of this element

    // get children's indexes
    // check if they are within bounds
    // get their actual values
    // compare with i and each other if necessary
    int li = (2*i)+1;
    int l = -1;
    int ri = (2*i)+2;
    int r = -1;

    if (li <= num-1){
        l = arr[li];
    } else {
        l = -1;
    }

    if (ri <= num-1){
        r = arr[ri];
    } else {
        r = -1;
    }

    // compare to i
    if ((l > arr[i]) || (r > arr[i])){
        // one is larger, find wich, if equal, swap with r
        if (l > r){
            // l is larger
            // swap it with i
            // heapify that new location
            int temp = l;
            arr[li] = arr[i];
            arr[i] = temp;
            heapify(arr, num, li);
        } else {
            int temp = r;
            arr[ri] = arr[i];
            arr[i] = temp;
            heapify(arr, num, ri);
        }
    }
    return;
}


// heapsort function for sorting a heap. must call createheap first
// pass heap as arr[] and size as int num
// array will be in order after running heapsort
void heapsort(int arr[], int num){
        int n = num;
        while (n>1){
            int temp = arr[0];
            arr[0] = arr[n-1];
            arr[n-1] = temp;
            n--;
            heapify(arr, n, 0);
        }

    
}


// createheap function from array.
// pass array as arr[], and size and int num.
// array will be max-heap after
void createheap(int arr[], int num){
    // calls heapify from halfway (since it checks its children)
    // back to root
    int n = (num/2) - 1;
    for (int i=n; i>=0; i--){
        heapify(arr, num, i);
    }
}


// printheap function
// pass array as arr[] and size and num. 
// will print elements in order, regardless if they are sorted. 
void printheap(int arr[], int num){
    if (num > 0){
        for (int i=0; i<num; i++){
            std::cout << arr[i] << "    ";
        }
        std::cout << std::endl;
    }
}




// main function	
int main(){

    // string and int for user input
    std::string input = "";
    int inputint = -1;

    // prompt and input
    std::cout << "How many elements are in the array?" << std::endl;
    std::cin >> input;

    // convert input to int
    inputint = std::stoi(input);

    // make array
    int arr[inputint];

    // populate array
    for (int i=0; i<inputint; i++){
        std::cout << "What is element number " << i+1 << "?" << std::endl;
        std::cin >> input;
        int tempint = std::stoi(input);
        arr[i] = tempint;
    }

    // print pre heapify
    std::cout << std::endl;
    std::cout << "Array before heapify: " << std::endl;
    printheap(arr, inputint);


    // checks if array is a heap
    int isheap = checkheap(arr, inputint);
    std::cout << std::endl;
    if (isheap == 1){
        std::cout << "Array is a heap" << std::endl;
    } else {
        std::cout << "Array is not a heap" << std::endl;
    }

    // create heap
    createheap(arr, inputint);

    // print post heapify
    std::cout << std::endl;
    std::cout << "Array after heapify: " << std::endl;
    printheap(arr, inputint);


    // print peak on heap
    std::cout << std::endl;
    std::cout << "Peak on heap gives: " << peak_heap(arr) << std::endl;

    // sort and print
    heapsort(arr, inputint);
    std::cout << std::endl;
    std::cout << "Array after heapsort:" << std::endl;
    printheap(arr, inputint);


    // goodbye
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
	return 0;
}