/**
* @file	 fibonacci_recursive.S
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
			.global fibrec
fibrec: 	str lr, [sp #-16]
			mov w8, w0			// store max index (input)
			cmp w8, #1			// compare max index with 1
			ble oneorzero		// if less than or equal to 1, branch to oneorzero

		// Greater than 1 Section
			add w12, w11, w10	// Calculate current fibonacci value, place in w12
			mov w10, w11		// Update fib(n-2) to fib(n-1)
			mov w11, w12		// Update fib(n-1) to fib(n)
			add w9, #1			// Increment current index
			cmp w9, w8			// Compare current index with max
			ble reccall			// If less than or equal to, branch to recursive call section
			mov w0, w12			// If greater than, move fib(n) into w0
			b done				// branch to done

		// Recursive Section
reccall:
			bl fibsec			// Recursive call of this function


		// 1 or 0 Section
oneorzero:
			mov w0, w8			// fib(0) = 0 & fib(1) = 1, place max index in w0
			b done				// Branch to done



		// Done Section
done:
    		ldr lr, [sp, #-16]	// Restore return address from stack
			ret