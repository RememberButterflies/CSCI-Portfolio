/**
 * @file fourFullComp_tb.v
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
`include "fourFullComp.v"

module fourFullComp_tb;

    reg [3:0] a;
    reg [3:0] b;
    wire equal;
    wire greaterThan;
    wire lessThan;

    fourFullComp uut (a, b, equal, greaterThan, lessThan);

    initial begin
        $dumpfile("fourFullComp_tb.vcd");
        $dumpvars(0, fourFullComp_tb);

        a = 4'b0000;
        b = 4'b0000;
        #20;

        a = 4'b1010;
        b = 4'b0101;
        #20;

        a = 4'b0011;
        b = 4'b1100;
        #20;

        a = 4'b1111;
        b = 4'b1111;
        #20;

        $display("Test complete");
    end

endmodule