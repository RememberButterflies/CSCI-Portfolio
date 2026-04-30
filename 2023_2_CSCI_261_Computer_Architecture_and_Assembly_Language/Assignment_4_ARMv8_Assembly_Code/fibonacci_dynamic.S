/**
* @file	 fibonacci_dynamic.S
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
			.global fibdyn		//Start implementing the function with the function name as a label in your assembly code 
fibdyn:		str lr, [sp, #-16]	//Save the return address onto stack	
			cmp x0, #0			//Compare the index with zero
			beq loopend			//If it is zero, return it as the return value of the function and branch to the end of the function
			cmp x0, #1			//Compare the index value with one
			beq loopend			//If it is one, return it as the return value of the function and branch to the end of the function


			// else section of cmp-beq
			mov x4, x0			//Move the index value from x0 to x4
			mov x3, #1			//Use x3 as your loop couner and initialize it to 1
			mov x2, #0			//Use x2 to keep track of your fib[n-2] and initialize it to 0
			mov x1, #1			//Use x1 to keep track of your fib[n-1] and initialize it to 1
			mov x0, #0			//Use x0 to hold your fib[n] and initialize it to 0



loop:		cmp x3, x4			//Define the beginning of a loop with an appropriate loop label
								//Compare loop counter with the current index value
			beq loopend			//End the loop if they are equal by branching to the end of the function
			add x0, x1, x2		//Compute fib[n] = fib[n-1] + fib[n-2]
			mov x2, x1			//Move fib[n-1] to fib[n-2] 
			mov x1, x0			//Move fib[n] to fib[n-1]	
			add x3, x3, #1		//Increment the loop counter
			bl loop				//Branch to the beginning of the loop


loopend:	ldr lr, [sp, #-16]	//Define the end of the function with an appropriate label
								//Retrieve the return address from the stack
			ret lr				//Return from the function
