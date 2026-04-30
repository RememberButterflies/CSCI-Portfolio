/**
 * @file MealyBeh.v
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

module MealyBeh (

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
            A: if (w) begin 
                Y=B;
                z=0;
            end
                else begin
                    Y=A;
                    z=0;
                end 
            B: if (w) begin
                Y=C;
                z=0;
            end
                else begin
                 Y=D;
                 z=0; 
                end
            C: if (w) begin
                Y=C;
                z=0;
            end
                else begin
                 Y=E;
                 z=1; 
                end
            D: if (w) begin
                Y=F;
                z=1;
            end
                else begin
                 Y=D;
                 z=0; 
                end
            E: if (w) begin
                Y=F;
                z=1;
            end
                else begin
                 Y=A;
                 z=0; 
                end
            F: if (w) begin
                Y=C;
                z=0;
            end
                else begin
                 Y=D;
                 z=0; 
                end
        endcase
    end

    // Define the “state update” sequential logic
    //Asynchronous reset is performed when Resetn input goes to 0
    always @(negedge Resetn, posedge Clk) begin
        #10;
        if (Resetn==0)  y <= A;
        else y <= Y;     
    end

endmodule