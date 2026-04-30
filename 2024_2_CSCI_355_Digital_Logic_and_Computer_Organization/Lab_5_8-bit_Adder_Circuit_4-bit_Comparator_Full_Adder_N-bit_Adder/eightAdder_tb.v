/**
 * @file eightAdder_tb.v
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
`include "eightAdder.v"
module eightAdder_tb (
);
    reg ci;
    reg x0;
    reg x1;
    reg x2;
    reg x3;
    reg x4;
    reg x5;
    reg x6;
    reg x7;
    reg y0;
    reg y1;
    reg y2;
    reg y3;
    reg y4;
    reg y5;
    reg y6;
    reg y7;
    wire s0;
    wire s1;
    wire s2;
    wire s3;
    wire s4;
    wire s5;
    wire s6;
    wire s7;

    eightAdder ut(ci, x7, x6, x5, x4, x3, x2, x1, x0, y7, y6, y5, y4, y3, y2, y1, y0, s7, s6, s5, s4, s3, s2, s1, s0, co);

    initial begin
        $dumpfile("eightAdder_tb.vcd");
        $dumpvars(0, eightAdder_tb);

        x0 = 0;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        x4 = 0;
        x5 = 0;
        x6 = 0;
        x7 = 0;
        y0 = 0;
        y1 = 0;
        y2 = 0;
        y3 = 0;
        y4 = 0;
        y5 = 0;
        y6 = 0;
        y7 = 0;
        ci = 0;
		#20;

        x0 = 1;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        x4 = 0;
        x5 = 0;
        x6 = 0;
        x7 = 0;
        y0 = 0;
        y1 = 0;
        y2 = 0;
        y3 = 0;
        y4 = 0;
        y5 = 0;
        y6 = 0;
        y7 = 0;
        ci = 1;
		#20;

        x0 = 1;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        x4 = 0;
        x5 = 1;
        x6 = 0;
        x7 = 0;
        y0 = 1;
        y1 = 0;
        y2 = 0;
        y3 = 1;
        y4 = 0;
        y5 = 0;
        y6 = 1;
        y7 = 0;
        ci = 1;
		#20;

        x0 = 0;
        x1 = 1;
        x2 = 1;
        x3 = 0;
        x4 = 1;
        x5 = 1;
        x6 = 1;
        x7 = 1;
        y0 = 1;
        y1 = 0;
        y2 = 1;
        y3 = 1;
        y4 = 0;
        y5 = 1;
        y6 = 1;
        y7 = 0;
        ci = 0;
        #20;

        x0 = 0;
        x1 = 1;
        x2 = 1;
        x3 = 0;
        x4 = 1;
        x5 = 1;
        x6 = 1;
        x7 = 1;
        y0 = 1;
        y1 = 0;
        y2 = 1;
        y3 = 1;
        y4 = 0;
        y5 = 1;
        y6 = 1;
        y7 = 0;
        ci = 0;
		#20;

        x0 = 0;
        x1 = 0;
        x2 = 1;
        x3 = 0;
        x4 = 1;
        x5 = 1;
        x6 = 1;
        x7 = 0;
        y0 = 1;
        y1 = 1;
        y2 = 1;
        y3 = 1;
        y4 = 0;
        y5 = 1;
        y6 = 0;
        y7 = 0;
        ci = 1;
		#20;



		
		$display("Test complete");

    end
  
endmodule