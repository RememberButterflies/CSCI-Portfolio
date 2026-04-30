#/**
# * @file Makefile
# * @author Patrick McGrath, CSCI 370, VIU
# * @version 1.0
# * @date April, 2025
# * 
# *  Term Project: Rideshare Database Program in C++ / Oracle SQL
# *  Copyright (C) 2025 Patrick McGrath
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
all: projx

proj.o: proj.cpp
	$(G) -c $(CFLAGS) proj.cpp

projx: proj.o
	$(G) $(LFLAGS) -o projx proj.o

clean:
	rm -f *.o projx