/**
 * @file Mealy1_tb.v
 * @author Patrick McGrath, CSCI 355, VIU
 * @version 1.0
 * @date November, 2024
 * 
 *  Lab #7 Synchronous Sequential Circuits
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
`include "Mealy1.v"

module Mealy1_tb ();
    reg Clk = 0;
    reg Resetn = 0;
    reg w;
    wire z;

    Mealy1 UUT(Clk, Resetn, w, z);

    always begin
        Clk = ~Clk;
        #5;
    end

    initial begin
        $dumpfile("Mealy1_tb.vcd");
        $dumpvars(0,Mealy1_tb);

        Resetn = 0; #10;
        w = 1; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;
        w = 0; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;
        w = 1; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;
        Resetn = 1; #10;
        w = 1; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;
        w = 0; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;
        w = 1; #10;
        w = 0; #10;
        w = 1; #10;
        w = 1; #10;          

        $finish;  
    end
    
endmodule