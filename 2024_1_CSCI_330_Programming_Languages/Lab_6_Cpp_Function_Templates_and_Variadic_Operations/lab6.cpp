/**
 * @file lab6.cpp
 * @author Patrick McGrath, CSCI 330, VIU
 * @version 1.0.0
 * @date April, 2024
 *
 * 
 * 
 *      Lab 6  C++ Function Templates and Variadic Operations
 *          Copyright (C) 2024 Patrick McGrath
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

#include "lab6.h"




// Function Declarations

// provided functions
std::string concat(std::string s1, std::string s2){
    return s1 + s2;
}
std::string smallStr(std::string s1, std::string s2){
    if (s1 < s2){
        return s1;
    }
    return s2;
}
int smallInt(int x, int y){
    if (x < y){
        return x;
    }
    return y;
}



// Basic functions, 1 per each type:
// bool, int, double, long, float, string and char
//      type type[number of parameters][versions, starting at a](type x);



//           Uniary Functions
// return not b
bool bool1a(bool b){
    return !b;
}

// number function a, 
// return n^2
int int1a(int n){
    return n*n;
}
float float1a(float n){
    return n*n;
}
double double1a(double n){
    return n*n;
}
long long1a(long n){
    return n*n;
}

// return reverse s
std::string string1a(std::string s){
    size_t len = s.length();
    std::string temp;
    for (int i = len-1; i >= 0; i--){
        temp = temp + s[i];
    }
    return temp;
}

// return each character shifted by 1
std::string string1b(std::string s){
    size_t len = s.length();
    std::string temp;
    int l = len;
    for (int i = 0; i <= l-1; i++){
        temp = temp + char1a(s[i]);
    }
    return temp;
}

// return next "printable" character
char char1a(char c){
    if (c >= 32 && c <= 125){
        return c+1;
    } else if (c == 126){
        return 32;
    }
    return c;
}

// return farenheit from celcius
float c2f(float c){
    return ((c+40)*1.8)-40;
}




// binary functions
// return inclusive or
bool bool2a(bool a, bool b){
    if (a == 1 || b == 1){
        return 1;
    }
    return 0;
}

// return exclusive or
bool bool2b(bool a, bool b){
    if (a == 1 && b == 1){
        return 1;
    }
    return 0;
}

// number function a,
// return n^(m-n)  // why not
int int2a(int n, int m){
    return pow(n, (m-n));
}
float float2a(float n, float m){
    return pow(n, (m-n));
}
double double2a(double n, double m){
    return pow(n, (m-n));
}
long long2a(long n, long m){
    return pow(n, (m-n));
}

// return reverse s1 + nonreverse s2
std::string string2a(std::string s, std::string r){
    return (string1a(s) + r);
}

// return character between c and d
char char2a(char c, char d){
    return ((c+d)/2);
}


// global variables for testing
bool b1 = 0;
bool b2 = 1;
bool b3 = 0;
int i1 = 2;
int i2 = 5;
int i3 = -43;
int i4 = -100;
float f1 = 35.54;
float f2 = 22.03;
float f3 = -103.342;
float f4 = 0;
double d1 = 37;
double d2 = -7;
double d3 = 633;
long l1 = 262;
long l2 = 929;
long l3 = -3;
std::string s1 = "nuqneH";
std::string s2 = "?";
std::string s3 = "word";
std::string s4 = "Nanaimo";
char c1 = 'a';
char c2 = 32;
char c3 = 126;
char c4 = '6';

std::string stsp = "****    ";
std::string spst = "    ****";






int main(){

// testing functions without templates
std::cout << stsp << "Testing functions without templates" << spst << std::endl;
std::cout << "Uniary functions:" << std::endl;
std::cout << std::endl;



// my functions
std::cout << "return (not b):    ";
std::cout << "bool1a(" << b1 << ") = " << bool1a(b1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "int1a(" << i1 << ") = " << int1a(i1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "float1a(" << f1 << ") = " << float1a(f1) << std::endl;
std::cout << "return farenheit from celcius:    ";
std::cout << "c2f(" << f4 << ") = " << c2f(f4) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "double1a(" << d1 << ") = " << double1a(d1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "long1a(" << l1 << ") = " << long1a(l1) << std::endl;
std::cout << "return (reverse s1):    ";
std::cout << "string1a(" << s1 << ") = " << string1a(s1) << std::endl;
std::cout << "return (s1 with char's shifted by 1):    ";
std::cout << "string1b(" << s1 << ") = " << string1b(s1) << std::endl;
std::cout << "return (next printable c1):    ";
std::cout << "char1a(" << c1 << ") = " << char1a(c1) << std::endl;
std::cout << "return (next printable c1):    ";
std::cout << "char1a(" << c3 << ") = " << char1a(c3) << std::endl;
std::cout << std::endl;



// binary functions


std::cout << "Binary functions:" << std::endl;
std::cout << std::endl;
std::cout << "provided functions:" << std::endl;
std::cout << "concat(" << s1 << ", " << s2 << ") = " << concat(s1, s2) << std::endl;
std::cout << "smallStr(" << s1 << ", " << s2 << ") = " << smallStr(s1, s2) << std::endl;
std::cout << "smallInt(" << i1 << ", " << i2 << ") = " << smallInt(i1, i2) << std::endl;
std::cout << "return (inclusive or):    ";
std::cout << "bool2a(" << b1 << ", " << b2 << ") = " << bool2a(b1, b2) << std::endl;
std::cout << "return (exclusive or):    ";
std::cout << "bool2b(" << b2 << ", " << b3 << ") = " << bool2b(b2, b3) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "int2a(" << i1 << ", " << i2 << ") = " << int2a(i1, i2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "float2a(" << f1 << ", " << f2 << ") = " << float2a(f1, f2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "double2a(" << d1 << ", " << d2 << ") = " << double2a(d1, d2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "long2a(" << l1 << ", " << l2 << ") = " << long2a(l1, l2) << std::endl;
std::cout << "return (reverse(s1) + s2):    ";
std::cout << "string2a(" << s1 << ", " << s3 << ") = " << string2a(s1, s3) << std::endl;
std::cout << "return middle char of c1, c2:    ";
std::cout << "char2a(" << c1 << ", " << c2 << ") = " << char2a(c1, c2) << std::endl;
std::cout << "return middle char of c1, c2:    ";
std::cout << "char2a(" << c2 << ", " << c3 << ") = " << char2a(c2, c3) << std::endl;
std::cout << std::endl;




// template calls

// Uniary functions
// testing functions without templates
std::cout << stsp << "Testing functions with templates" << spst <<std::endl;
std::cout << "Uniary functions:" << std::endl;
std::cout << std::endl;





std::cout << "return (not b):    ";
std::cout << "bool1a(" << b1 << ") = " << apply(bool1a, b1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "int1a(" << i1 << ") = " << apply(int1a, i1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "float1a(" << f1 << ") = " << apply(float1a, f1) << std::endl;
std::cout << "return farenheit from celcius:    ";
std::cout << "c2f(" << f2 << ") = " << apply(c2f, f2) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "double1a(" << d1 << ") = " << apply(double1a, d1) << std::endl;
std::cout << "return (n^2):    ";
std::cout << "long1a(" << l1 << ") = " << apply(long1a, l1) << std::endl;
std::cout << "return (reverse s1):    ";
std::cout << "string1a(" << s1 << ") = " << apply(string1a, s1) << std::endl;
std::cout << "return (s1 with char's shifted by 1):    ";
std::cout << "string1b(" << s1 << ") = " << apply(string1b, s1) << std::endl;
std::cout << "return (next printable c1):    ";
std::cout << "char1a(" << c1 << ") = " << apply(char1a, c1) << std::endl;
std::cout << "return (next printable c1):    ";
std::cout << "char1a(" << c3 << ") = " << apply(char1a, c3) << std::endl;
std::cout << std::endl;


// binarys
std::cout << "Binary functions:" << std::endl;
std::cout << std::endl;
std::cout << "provided functions:" << std::endl;
std::cout << "concat(" << s1 << ", " << s2 << ") = " << apply(concat, s1, s2) << std::endl;
std::cout << "smallStr(" << s1 << ", " << s2 << ") = " << apply(smallStr, s1, s2) << std::endl;
std::cout << "smallInt(" << i1 << ", " << i2 << ") = " << apply(smallInt, i1, i2) << std::endl;
std::cout << "return (inclusive or):    ";
std::cout << "bool2a(" << b1 << ", " << b2 << ") = " << apply(bool2a, b1, b2) << std::endl;
std::cout << "return (exclusive or):    ";
std::cout << "bool2b(" << b2 << ", " << b3 << ") = " << apply(bool2b, b2, b3) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "int2a(" << i1 << ", " << i2 << ") = " << apply(int2a, i1, i2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "float2a(" << f1 << ", " << f2 << ") = " << apply(float2a, f1, f2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "double2a(" << d1 << ", " << d2 << ") = " << apply(double2a, d1, d2) << std::endl;
std::cout << "return (n1)^(n2-n1):    ";
std::cout << "long2a(" << l1 << ", " << l2 << ") = " << apply(long2a, l1, l2) << std::endl;
std::cout << "return (reverse(s1) + s2):    ";
std::cout << "string2a(" << s1 << ", " << s3 << ") = " << apply(string2a, s1, s3) << std::endl;
std::cout << "return middle char of c1, c2:    ";
std::cout << "char2a(" << c1 << ", " << c2 << ") = " << apply(char2a, c1, c2) << std::endl;
std::cout << "return middle char of c1, c2:    ";
std::cout << "char2a(" << c2 << ", " << c3 << ") = " << apply(char2a, c2, c3) << std::endl;
std::cout << std::endl;



// Uniary functions
// testing functions without templates
std::cout << stsp << "Testing variadic functions:" << spst <<std::endl;
std::cout << std::endl;


std::cout << "Uniary functions:" << std::endl;
std::cout << "sumDiffs(" << i1 << ") = " << sumDiffs(i1) << std::endl;

std::cout << std::endl;
// binary
std::cout << "Binary functions:" << std::endl;
std::cout << "sumDiffs(" << i1 << ", " << i2 << ") = " << sumDiffs(i1, i2) << std::endl;
std::cout << "chosenMin(smallInt, " <<  i1 << ", " << i2 << ") = " << chosenMin(smallInt, i1, i2) << std::endl;
std::cout << "chosenMin(smallStr, " <<  s1 << ", " << s4  << ") = " << chosenMin(smallStr, s1, s4) << std::endl;
std::cout << std::endl;
std::cout << "Trinary functions:" << std::endl;
std::cout << "sumDiffs(" << i1 << ", " << i2 << ", " << i3 << ") = " << sumDiffs(i1, i2, i3) << std::endl;
std::cout << "chosenMin(smallInt, " <<  i1 << ", " << i2 << ", " << i3 << ") = " << chosenMin(smallInt, i1, i2, i3) << std::endl;
std::cout << "chosenMin(smallStr, " <<  s1 << ", " << s4 << ", " << s3 << ") = " << chosenMin(smallStr, s1, s4, s3) << std::endl;
std::cout << std::endl;
std::cout << "Quartinary functions:" << std::endl;
std::cout << "sumDiffs(" << i1 << ", " << i2 << ", " << i3 << ", " << i4 << ") = " << sumDiffs(i1, i2, i3, i4) << std::endl;
std::cout << "chosenMin(smallInt, " <<  i1 << ", " << i2 << ", " << i3 << ", " << i4 << ") = " << chosenMin(smallInt, i1, i2, i3, i4) << std::endl;
std::cout << "chosenMin(smallStr, " <<  s1 << ", " << s2 << ", " << s3 << ", " << s4 << ") = " << chosenMin(smallStr, s1, s2, s3, s4) << std::endl;
std::cout << std::endl;

    return 0;
}

