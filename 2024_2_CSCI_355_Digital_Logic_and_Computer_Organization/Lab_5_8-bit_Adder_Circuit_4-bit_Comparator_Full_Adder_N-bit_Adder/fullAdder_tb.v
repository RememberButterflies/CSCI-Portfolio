/**
 * @file fullAdder_tb.v
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
`include "fullAdder.v"
module fullAdder_tb (
);
    reg xi;
    reg yi;
    reg ci;
    wire so;
    wire co;

    fullAdder ut(xi, yi, ci, so, co);

    initial begin
        $dumpfile("fullAdder_tb.vcd");
        $dumpvars(0, fullAdder_tb);

        xi = 0;
        yi = 0;
        ci = 0;
		#20;
		
        xi = 0;
        yi = 0;
        ci = 1;
		#20;
		
        xi = 0;
        yi = 1;
        ci = 0;
		#20;
		
        xi = 0;
        yi = 1;
        ci = 1;
		#20;

        xi = 1;
        yi = 0;
        ci = 0;
		#20;

        xi = 1;
        yi = 0;
        ci = 1;
		#20;

        xi = 1;
        yi = 1;
        ci = 0;
		#20;

        xi = 1;
        yi = 1;
        ci = 1;
		#20;
		
		$display("Test complete");

    end
  
endmodule