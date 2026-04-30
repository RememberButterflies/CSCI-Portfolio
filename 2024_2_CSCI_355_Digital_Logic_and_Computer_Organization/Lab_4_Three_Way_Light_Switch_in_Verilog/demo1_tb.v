/**
 * @file demo1_tb.v
 * @author Patrick McGrath, CSCI 355, VIU
 * @version 1.0
 * @date November, 2024
 * 
 *  Lab #4 Three Way Light Switch in Verilog.
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
`include "threeWayLight.v"
module demo1_tb (
);
    reg x1;
    reg x2;
    reg x3;
    wire light;

    threeWayLight ut(x1, x2, x3, light);

    initial begin
        $dumpfile("demo1_tb.vcd");
        $dumpvars(0, demo1_tb);

        x1 = 0;
        x2 = 0;
        x3 = 0;
		#20;
		
        x1 = 0;
        x2 = 0;
        x3 = 1;
		#20;
		
        x1 = 0;
        x2 = 1;
        x3 = 0;
		#20;
		
        x1 = 0;
        x2 = 1;
        x3 = 1;
		#20;

        x1 = 1;
        x2 = 0;
        x3 = 0;
		#20;

        x1 = 1;
        x2 = 0;
        x3 = 1;
		#20;

        x1 = 1;
        x2 = 1;
        x3 = 0;
		#20;

        x1 = 1;
        x2 = 1;
        x3 = 1;
		#20;
		
		$display("Test complete");

    end
  
endmodule