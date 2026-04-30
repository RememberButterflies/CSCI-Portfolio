/**
 * @file dFlipflopEN.v
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

//Gated D flipflop with Enable
module dFlipflopEN (
    input D,
    input En,
    input CLK,
    output reg Q
);

always @(posedge CLK) begin      //edge for positive (rising) edge of clk; negedge for negative(falling) edge of clock
    if (En) begin
        Q <= D;                  //Since no “else” is given, a latch will be synthesized to hold the value of “Q”
    end
end
    
endmodule