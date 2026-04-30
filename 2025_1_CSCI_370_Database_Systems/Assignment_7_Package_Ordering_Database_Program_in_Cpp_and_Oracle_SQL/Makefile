# * @file Makefile
# * @author Patrick McGrath, CSCI 370, VIU
# * @version 1.0
# * @date March, 2025
# * 
# *  Assignment #7 Package Ordering Database Program in C++ / Oracle SQL
# *  Copyright (C) 2025  Patrick McGrath
# *
# *  This program is free software: you can redistribute it and/or modify
# *  it under the terms of the GNU General Public License as published by
# *  the Free Software Foundation, either version 3 of the License, or
# *  (at your option) any later version.
# *
# *  This program is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
# */

G = g++-4.9 # only installed on otter
CFLAGS = -I/usr/local/lib/Oracle/instantclient_11_2/sdk/include
LFLAGS = -L/usr/local/lib/Oracle/instantclient_11_2 -locci -lociei
all: assignment7


assignment7.o: assignment7.cpp
	$(G) -c $(CFLAGS) assignment7.cpp

assignment7: assignment7.o
	$(G) $(LFLAGS) -o foodSharing assignment7.o

clean:
	rm -f *.o foodSharing
