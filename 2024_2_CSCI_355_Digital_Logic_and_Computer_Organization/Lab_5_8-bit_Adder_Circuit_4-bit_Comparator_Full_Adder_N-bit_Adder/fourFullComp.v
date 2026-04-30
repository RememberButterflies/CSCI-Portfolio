/**
 * @file fourFullComp.v
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

`include "fourComp.v"

module fourFullComp(
    input wire [ 3:0 ] a,
    input wire [ 3:0 ] b,
    output wire equal,
    output wire greaterThan,
    output wire lessThan
    );

    fourComp stage3 (a[3], b[3], 1'b1, 1'b0, 1'b0, eq3, gt3, ln3);
    fourComp stage2 (a[2], b[2], eq3, gt3, ln3, eq2, gt2, ln2);
    fourComp stage1 (a[1], b[1], eq2, gt2, ln2, eq1, gt1, ln1);
    fourComp stage0 (a[0], b[0], eq1, gt1, ln1, equal, greaterThan, lessThan);

endmodule