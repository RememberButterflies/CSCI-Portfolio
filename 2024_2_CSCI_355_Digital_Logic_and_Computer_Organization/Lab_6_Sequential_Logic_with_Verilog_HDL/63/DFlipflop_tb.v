/**
 * @file DFlipflop_tb.v
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
`include "DFlipflop.v"

module DFlipflop_tb ();
    reg clk = 0;
    reg d = 0;
    reg reset_n = 0;
    wire q;

DFlipflop UUT(clk, d, reset_n, q);

always begin
    clk = ~clk;
    #10;
end

initial begin
    $dumpfile("DFlipflop_tb.vcd");
    $dumpvars(0,DFlipflop_tb);
    reset_n = 0;    #35;
    d = 0;     #35;
    d = 1;     #35;
    d = 0;     #35;

    reset_n = 1;   #35;
    d = 0;    #35;
    d = 1;    #35;
    d = 0;    #35;
    $finish;   //since CLK is running in the always block, it's important to inform simulator to stop 
end
    
endmodule