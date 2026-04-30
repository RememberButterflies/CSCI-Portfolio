/**
 * @file genAdder.v
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
 
`include "fullAdder.v"
module genAdder (ci, X, Y, S, co);
    parameter n = 32;
    input ci;
    input [n-1:0] X;
    input [n-1:0] Y;
    output co;
    output [n-1:0] S;
    wire [n:0] C;

    genvar i;
    assign C[0] = ci;
    assign co = C[n];
    generate
        for (i = 0; i <= n-1; i = i+1)
        begin:addbit
            fullAdder ut(X[i], Y[i], C[i], S[i], C[i+1]);
        end
    endgenerate
endmodule