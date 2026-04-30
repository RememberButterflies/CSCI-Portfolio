/**
 * @file eightAdder.v
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

module eightAdder(ci, x7, x6, x5, x4, x3, x2, x1, x0, y7, y6, y5, y4, y3, y2, y1, y0, s7, s6, s5, s4, s3, s2, s1, s0, co);
    input ci, x7, x6, x5, x4, x3, x2, x1, x0, y7, y6, y5, y4, y3, y2, y1, y0;
    output s7, s6, s5, s4, s3, s2, s1, s0, co;

    fullAdder stage0 (x0, y0, ci, s0, c1);
    fullAdder stage1 (x1, y1, c1, s1, c2);
    fullAdder stage2 (x2, y2, c2, s2, c3);
    fullAdder stage3 (x3, y3, c3, s3, c4);
    fullAdder stage4 (x4, y4, c4, s4, c5);
    fullAdder stage5 (x5, y5, c5, s5, c6);
    fullAdder stage6 (x6, y6, c6, s6, c7);
    fullAdder stage7 (x7, y7, c7, s7, co);

endmodule