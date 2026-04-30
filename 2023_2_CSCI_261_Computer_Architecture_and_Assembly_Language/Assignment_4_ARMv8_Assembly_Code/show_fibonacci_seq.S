/**
* @file	 show_fibonacci_seq.S
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

*
*/
			ldr x0, =fibarray		//Initialize ARM register x0 with the address of the integer array that was defined to fibonacci sequence values
			ldr x2, =userin			//Initialize ARM register x2 with the address of integer variable that was defined to hold user input
			ldr w1, [x2]			//Initialize ARM register w1 with the value of integer variable
//			bl showfib				//Call show_fibonacci_seq() function to show the sequence of fibonacci values for
									//all indices strating from 0 and ending at user entered index


			.text
			.global showfib
showfib:    str lr, [sp, #-16]	// Save the return address onto stack
            mov x3, x0          //Array address has been passed through x0, copy it to x3
            mov x4, x1          //Max index has been passed through x1, copy it to x4
            mov x1, #0          //Use x1 as the loop counter and initialize it to zero

loop:       cmp x1, x4          //Compare loop counter value with the max index value
            beq end             //End the loop if they are equal by branching to the end of the function
            ldr x0, =shstr      //Assign the address of the formatted string to x0 to pass it to printf function
            ldr w2, [x0, x1, LSL #2]    //Assign w2 the fibonacci sequence value pointed by index x1 from the array
            str x1, [sp, #-8]       //Save current index value in x1 onto stack before calling printf function
            str x3, [sp, #-8]       //Save the address of fibonacci sequence array (in x3) onto stack before calling printf function
            str x4, [sp, #-8]       //Save fibonacci sequence array max index (in x4) onto stack before calling printf function
            bl prntf                //Call printf() function
            ldr x4, [sp, #-8]       //Retrive fibonacci sequence array index limit from the stack into x4
            ldr x3, [sp, #-8]       //Retrive the address fibonacci sequence array from the stack into x3
            ldr x1, [sp, #-8]       //Retrive current loop counter value from the stack into x1
            add x1, #1              //Increment the loop counter
            bl loop                 //Branch to the beginning of the loop


end:        ldr lr, [sp, #-16]  	// Restore return address from stack
			ret

