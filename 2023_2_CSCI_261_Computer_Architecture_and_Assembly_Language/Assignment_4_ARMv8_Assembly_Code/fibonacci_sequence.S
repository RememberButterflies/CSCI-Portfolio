/**
* @file	 fibonacci_sequence.S
* @Patrick McGrath, CSCI 261, VIU
* @version 1.0.0
* @date December 4, 2023
* 
*  Assignment #4 ARMv8 Assembly Code
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


			.text
			.global fibsec
fibsec:    	str lr, [sp, #-16]	// Save the return address onto stack
			mov w8, w1			// Move the max index value from w1 to w8    
			cmp w8, #0			// Compare the max index value with 0
    		beq zero			// If max index is 0, branch to zero
			cmp w8, #1			// Compare the max index with 1
			beq one				// If max index is 1, branch to one
			
			// Greater than 1 section
			mov w9, #0			// Initialize variable for fib(n-2) as 0
			mov w10, #1			// Initialize variable for fib(n-1) as 1
			str w9, [x0, #0]	// Store fib(0) at array index 0
			str w10, [x0, #4]	// Store fib(1) at array index 1 (4 bytes offset)
			mov w11, #2			// Initialize current index at 2

			// Loop Section
seq:
			add w12, w9, w10			// Calculate current Fibonacci number= fib(n-1) + fib(n-2), store in w12
    		str w12, [x0, w11, LSL #2]	// Store the result at appropriate index
										// fibarray is in x0, w11 is index / offset
										// and LSL #2 is the size of the offset, 4 bytes
    		mov w9, w10					// Update fib(n-2) to fib(n-1)
   			mov w10, w12				// Update fib(n-1) to the current fibonacci value
    		add w11, w11, #1			// Increment current index by 1
    		cmp w11, w8					// Compare index to max index to see if loop is done
    		ble seq						// if current index (1 greater than when it started), is less than or equal
										// to max index, repeat loop
			b done						// if w11 greater than w8, break loop

		// Zero Section
zero:
			str w8, [x0, #0]			// Store 0 at index 0 on the array
			b done						// Branch to done

		// One Section
one:
			mov w9, #0					// Initialize w9 to be 0
			str w9, [x0, #0]			// Store w9 (0) at index 0 on the array
			str w8, [x0, #4]			// Store w8 (1) at index 1 on the array
			b done						// Branch to done

		// Done Section
done:
    		ldr lr, [sp, #-16]			// Restore return address from stack
    		ret