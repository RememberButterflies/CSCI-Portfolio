#/**
# * @file Makefile
# * @author Patrick McGrath, CSCI 439, VIU
# * @version 1.0
# * @date April, 2025
# * 
# *  Sittie-Typpie Reader / Writer Program
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

warns = -Wall -Wextra -pedantic
cc =g++

all: projx projxTest

projx: objects/proj.o objects/tokenparsewrite.o
	${cc} ${warns} $< objects/tokenparsewrite.o -o $@

projxTest: objects/projTest.o objects/tokenparsewriteTest.o
	${cc} ${warns} $< objects/tokenparsewriteTest.o -o $@

objects/proj.o: src/proj.cpp include/tokenparsewrite.h
	${cc} ${warns} -c $< -o $@

objects/projTest.o: src/projTest.cpp include/tokenparsewriteTest.h
	${cc} ${warns} -c $< -o $@

objects/tokenparsewrite.o: src/tokenparsewrite.cpp include/tokenparsewrite.h
	${cc} ${warns} -c $< -o $@

objects/tokenparsewriteTest.o: src/tokenparsewriteTest.cpp include/tokenparsewriteTest.h
	${cc} ${warns} -c $< -o $@

clean:
	rm -f objects/*.o projx projxTest

