/**
 * @file fourComp_tb.v
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
`include "fourComp.v"
module fourComp_tb (
);
    reg a;
    reg b;
    reg eq_in;
    reg gt_in;
    reg lt_in;
    wire eq;
    wire gt;
    wire ln;

    fourComp ut(a, b, eq_in, gt_in, lt_in, eq, gt, ln);

    initial begin
        $dumpfile("fourComp_tb.vcd");
        $dumpvars(0, fourComp_tb);

        a = 0;
        b = 0;
        eq_in = 0;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 0;
        b = 0;
        eq_in = 1;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 0;
        b = 0;
        eq_in = 0;
        gt_in = 1;
        lt_in = 0;
		#20;
		
        a = 0;
        b = 0;
        eq_in = 0;
        gt_in = 0;
        lt_in = 1;
		#20;

        a = 0;
        b = 1;
        eq_in = 0;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 0;
        b = 1;
        eq_in = 1;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 0;
        b = 1;
        eq_in = 0;
        gt_in = 1;
        lt_in = 0;
		#20;
		
        a = 0;
        b = 1;
        eq_in = 0;
        gt_in = 0;
        lt_in = 1;
		#20;

        a = 1;
        b = 1;
        eq_in = 0;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 1;
        b = 1;
        eq_in = 1;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 1;
        b = 1;
        eq_in = 0;
        gt_in = 1;
        lt_in = 0;
		#20;
		
        a = 1;
        b = 1;
        eq_in = 0;
        gt_in = 0;
        lt_in = 1;
		#20;

        a = 1;
        b = 0;
        eq_in = 0;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 1;
        b = 0;
        eq_in = 1;
        gt_in = 0;
        lt_in = 0;
		#20;

        a = 1;
        b = 0;
        eq_in = 0;
        gt_in = 1;
        lt_in = 0;
		#20;
		
        a = 1;
        b = 0;
        eq_in = 0;
        gt_in = 0;
        lt_in = 1;
		#20;
		
		$display("Test complete");

    end
  
endmodule