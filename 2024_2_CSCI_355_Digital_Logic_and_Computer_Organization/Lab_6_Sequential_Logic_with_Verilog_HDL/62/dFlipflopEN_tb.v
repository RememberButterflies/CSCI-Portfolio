/**
 * @file dFlipflopEN_tb.v
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
`include "dFlipflopEN.v"

module dFlipflopEN_tb ();

reg D = 0;
reg En = 0;
reg CLK = 0;
wire Q;

dFlipflopEN UUT(D, En, CLK, Q);

always begin
    CLK = ~CLK;
    #10;
end

initial begin
    $dumpfile("dFlipflopEN_tb.vcd");
    $dumpvars(0,dFlipflopEN_tb);
    En = 0;    #35;
    D = 0;     #35;
    D = 1;     #35;
    D = 0;     #35;

    En = 1;   #35;
    D = 0;    #35;
    D = 1;    #35;
    D = 0;    #35;
    $finish;   //since CLK is running in the always block, it's important to inform simulator to stop 
end
    
endmodule