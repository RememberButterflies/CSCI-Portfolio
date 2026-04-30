/**
 * @file MooreBeh.v
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

module MooreBeh (

    input wire Clk,
    input wire Resetn,
    input wire w,
    output reg z
);
    reg [2:0] y, Y;    //present and next state
    parameter A=3'b000, B=3'b001, C=3'b010, D=3'b011, E=3'b100, F=3'b101;

    // Define “Next state" and “output”, and combinational logic required for next state 
    always @(w,y) begin
        case (y)
            A: if (w) Y=B;
                else Y=A;
            B: if (w) Y=C;
                else Y=D;
            C: if (w) Y=C;
                else Y=E;
            D: if (w) Y=F;
                else Y=D;
            E: if (w) Y=F;
                else Y=A;
            F: if (w) Y=C;
                else Y=D;
            default: Y=3'bxxx;   //Important to include “default” case; don’t care states
        endcase
        if (y==E | y==F) z = 1;   //Output (combinational) logic for z simply checking for state C
        else z = 0;
    end

    // Define the “state update” sequential logic
    //Asynchronous reset is performed when Resetn input goes to 0
    always @(negedge Resetn, posedge Clk) begin
        #10;   //to create 1 time-period delay in the output
        if (Resetn==0)  y <= A;
        else y <= Y;     
    end

endmodule
