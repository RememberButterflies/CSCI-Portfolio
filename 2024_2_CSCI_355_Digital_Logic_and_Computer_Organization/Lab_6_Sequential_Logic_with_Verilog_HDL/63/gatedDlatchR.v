/**
 * @file gatedDlatchR.v
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

module gatedDlatchR (
    input wire clk,
    input wire d,
    input wire reset_n,
    output wire q
);

    not (a, d);
    not (b, clk);
    nand (e, d, reset_n, b);
    nand (h, b, a);
    not (c, b);
    nand (g, e, f);
    nand (f, g, reset_n);
    nand (i, g, reset_n, c);
    nand (j, f, c);
    nand (qn, j, q, reset_n);
    nand (q, i, qn);

endmodule