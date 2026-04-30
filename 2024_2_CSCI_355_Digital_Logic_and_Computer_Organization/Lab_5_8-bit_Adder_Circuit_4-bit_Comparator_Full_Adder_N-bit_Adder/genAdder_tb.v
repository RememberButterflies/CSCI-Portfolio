/**
 * @file genAdder_tb.v
 * @author Patrick McGrath, CSCI 355, VIU
 * @version 1.0
 * @date November, 2024
 * 
 *  Lab #5 8-bit Adder Circuit, 4-bit Comparator, Full Adder, N-bit Adder
 *  Copyright (C) 2024  Patrick McGrath
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
 
`timescale 1ns/1ns
`include "genAdder.v"
module genAdder_tb (
);
    parameter n = 32;
    reg [n-1:0] X;
    reg [n-1:0] Y;
    reg ci;
    wire [n-1:0] S;
    wire co;

    genAdder ut(ci, X, Y, S, co);

    initial begin
        $dumpfile("genAdder_tb.vcd");
        $dumpvars(0, genAdder_tb);

        ci = 0;
        X = 32'hA5432FE7;
        Y = 32'h1;
		#20;

        ci = 1;
        X = 'hA5432FE7;
        Y = 'h1;
		#20;

        ci = 0;
        X = 'hF661AAA0;
        Y = 'h3A052F1A;
		#20;

        ci = 1;
        X = 'hF661AAA0;
        Y = 'h3A052F1A;
		#20;

        ci = 0;
        X = 'h7272AAFF;
        Y = 'hAAAAAAAA;
		#20;

        ci = 1;
        X = 'h7272AAFF;
        Y = 'hAAAAAAAA;
		#20;
		
		$display("Test complete");

    end
  
endmodule