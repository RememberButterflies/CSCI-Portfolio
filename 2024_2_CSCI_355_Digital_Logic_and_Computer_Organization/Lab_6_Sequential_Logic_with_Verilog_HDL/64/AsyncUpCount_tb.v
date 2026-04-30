/**
 * @file AsyncUpCount_tb.v
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
`include "AsyncUpCount.v"

module AsyncUpCount_tb ();

parameter N = 4;

reg clk = 0;
reg reset = 0;
reg en = 0;
wire [N-1:0] q;

AsyncUpCount #(N) UUT(clk, reset, en, q);

always begin
    clk = ~clk;
    #10;
end

initial begin
    $dumpfile("AsyncUpCount_tb.vcd");
    $dumpvars(0,AsyncUpCount_tb);
    reset = 1; #20;
    reset = 0; #20;
    en = 0;    #100;
    en = 1;    #320;
    $finish;   //since CLK is running in the always block, it's important to inform simulator to stop 
end
    
endmodule