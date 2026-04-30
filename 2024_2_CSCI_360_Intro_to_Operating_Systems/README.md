# CSCI 360 - Intro to Operating Systems

*Fall, '24*

## *Overview*

An introduction to the major concepts of operating systems and study of the interrelationships between the operating system and the architecture of computer systems. Topics include operating system structures, concurrent programming techniques, cpu scheduling, deadlocks, memory management, file systems and protection. [1]

The assignments in this course were given to the students as structured but incomplete software. All assignments had their makefile, main, headers and test cases included. The students work of the assignments were to write the functions (including how they might call each other.) Because this repository is meant to showcase my coding skills and experience, and is not intended to provide usable software, this repository contains only the source code that I wrote and any associated README's.

## Contents:

### Assignment\_2\_Multithreaded\_Sudoku\_Solution\_Validator

*"This program is a \*\*multithreaded Sudoku solution validator\*\* that reads a completed Sudoku puzzle from a file and validates it by creating 27 separate threads (9 for columns, 9 for rows, and 9 for 3×3 subgrids) to check if each contains the digits 1-9 without repetition. After all threads complete their checks, the program displays and logs whether the entire puzzle solution is valid or invalid."* [2]

### Assignment\_3\_CPU\_Process\_Scheduler

*"This is a \*\*CPU Process Scheduler\*\* that implements multiple scheduling algorithms to manage task execution. The program reads a list of tasks (with name, priority, and CPU burst time) from a file, then simulates scheduling them using different algorithms: First Come First Serve (FCFS), Shortest Job First (SJF), Round Robin (RR), Priority-based (PR), and Priority with Round Robin (PR-RR). Depending on which scheduling implementation is compiled, the scheduler picks and executes tasks in the appropriate order, removing them from the list once their CPU burst is complete. This demonstrates how different scheduling strategies affect task execution order and efficiency in operating systems."* [3]

### Assignment\_4\_Sleeping\_Teaching\_Assistant\_Simulator

*"This is a \*\*Sleeping Teaching Assistant Simulator\*\* that models a concurrent system using threads, mutexes, and semaphores. The program simulates multiple students cycling through programming assignments and requesting help from teaching assistants, with a limited waiting queue. TAs sleep when no students need help and wake up when a student joins the queue, while the system uses synchronization primitives to prevent race conditions on shared resources like the queue and log."* [3]

## Sources

1.  VIU. (2026, April 29). *Computer science*. Computer Science Courses | Vancouver Island University | Canada. https://www.viu.ca/programs/courses/computer-science
2. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.
3. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2-4 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.