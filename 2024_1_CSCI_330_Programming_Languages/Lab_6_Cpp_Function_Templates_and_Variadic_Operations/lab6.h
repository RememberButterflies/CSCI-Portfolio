/**
 * @file lab6.h
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

#pragma once
#include <iostream>
#include <string>
#include <cmath>

// provided functions
std::string concat(std::string s1, std::string s2);
std::string smallStr(std::string s1, std::string s2);
int smallInt(int x, int y);



// sample functions, 
//      type type[number of parameters][versions, starting at a](type x);
// uniary functions

bool bool1a(bool b);
int int1a(int n);
float float1a(float n);
double double1a(double n);
long long1a(long n);
std::string string1a(std::string s);
std::string string1b(std::string s);
char char1a(char c);

float c2f(float c);

// binary functions

bool bool2a(bool a, bool b);
bool bool2b(bool a, bool b);
int int2a(int n, int m);
float float2a(float n, float m);
double double2a(double n, double m);
long long2a(long n, long m);
std::string string2a(std::string s, std::string r);
char char2a(char c, char d);




// Template declarations
// apply
// single parameter
template<class T>
T apply(T (*f)(T), T arg1) {
    return (*f)(arg1);
}
// double parameters
template <class T>
T apply(T (*f)(T,T), T arg1, T arg2) {
   return (*f)(arg1,arg2);
}


// sumDiffs
// single parameter
template <typename T>
T sumDiffs(T x) {
    return x;
}

// double parameter
template <typename T>
T sumDiffs(T x, T y) {
    return x-y;
}

// variadic parameters
template<typename T, typename... Args>
T sumDiffs(T x, T y, Args... args) {
    return sumDiffs(x, y) + sumDiffs(args...);
}


//chosenMin
// double parameters
template <class T>
T chosenMin(T (*f)(T,T), T arg1, T arg2) {
   return (*f)(arg1,arg2);
}

// variadic parameters
template<class T, class... Args>
T chosenMin(T (*f)(T, T), T arg1, T arg2, Args... args){
    return chosenMin(f, chosenMin(f, arg1, arg2), args...);
}
