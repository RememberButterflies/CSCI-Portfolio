/**
 * @file srlatchnor_tb.v
 * @author Patrick McGrath, CSCI 355, VIU
 * @version 1.0
 * @date November, 2024
 * 
 *  Lab #6 Sequential Logic with Verilog HDL
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
`include "srlatchnor.v"
module srlatchnor_tb (
);
    reg s;
    reg r;
    wire q;
    wire q_n;

    SRLatchNor ut(s, r, q, q_n);

    initial begin
        $dumpfile("srlatchnor_tb.vcd");
        $dumpvars(0, srlatchnor_tb);

        s = 0;
        r = 0;
		#20;

        s = 0;
        r = 1;
		#20;

        s = 1;
        r = 1;
		#20;

        s = 1;
        r = 0;
		#20;

        s = 0;
        r = 0;
		#20;

        s = 0;
        r = 1;
		#20;

        s = 0;
        r = 0;
		#20;

        s = 1;
        r = 1;
		#20;

        s = 0;
        r = 0;
		#20;

        s = 1;
        r = 0;
		#20;

        s = 0;
        r = 0;
		#20;
		
		$display("Test complete");

    end
  
endmodule