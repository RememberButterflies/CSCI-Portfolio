# Assignment\_2\_Multithreaded\_Sudoku\_Solution\_Validator

CSCI 360 - Intro to Operating Systems, Fall*, '24*

## *Overview*

*"This program is a \*\*multithreaded Sudoku solution validator\*\* that reads a completed Sudoku puzzle from a file and validates it by creating 27 separate threads (9 for columns, 9 for rows, and 9 for 3×3 subgrids) to check if each contains the digits 1-9 without repetition. After all threads complete their checks, the program displays and logs whether the entire puzzle solution is valid or invalid."* [1]

## Technology

This program takes a sudoku solution as a text file. The program will read the solution to memory from the file. The program will use multithreading to run checks on the sudoku to test its validity. A valid sudoku is a 9x9 grid with 9 columns, 9 rows and 9 non-overlapping 3x3 subgrids. Each one of these rows, columns and subgrids must have the digits 1-9 with no repetition or omission. 

The individual checks check whether the rows, columns and subgrids have these properties. Each check will record the time of the check, the result and info on which check it is to memory before closing its thread. The program will then save the results of all threads to a log file. 

## Sources

1. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.

## License

    Assignment #2 Multithreaded Sudoku Solution Validator

    Copyright (C) 2024  Patrick McGrath

This program is free software: you can redistribute it and/or modify

it under the terms of the GNU General Public License as published by

the Free Software Foundation, either version 3 of the License, or

(at your option) any later version.

This program is distributed in the hope that it will be useful,

but WITHOUT ANY WARRANTY; without even the implied warranty of

MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

GNU General Public License for more details.

You should have received a copy of the GNU General Public License

along with this program.  If not, see <https://www.gnu.org/licenses/>.