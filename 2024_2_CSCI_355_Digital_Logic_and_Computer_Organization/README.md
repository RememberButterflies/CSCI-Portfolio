# CSCI 355 - Digital Logic and Computer Organization

*Fall, '24*

## *Overview*

The fundamentals of logic design, computer organization, and the structure of major hardware components of computers. Topics include the application of Boolean algebra to switching circuits; the use of MSI, LSI and field programmable devices in digital design; combinatorial and sequential circuits, flip flops, counters, memory organization, CAD tools. [1]

## Contents:

### Lab\_4\_Three\_Way\_Light\_Switch\_in\_Verilog

*"This program implements a \*\*three-way light switch\*\* in Verilog, a digital logic circuit where a light can be controlled by three independent switches (x1, x2, x3). The light turns on only when an odd number of switches are in the "on" position (1), which is a common real-world electrical configuration found in homes where lights can be toggled from multiple locations."* [2]

### Lab\_5\_8-bit\_Adder\_Circuit\_4-bit\_Comparator\_Full\_Adder\_N-bit\_Adder

*"This is a parametric N-bit adder module written in Verilog that uses a generate loop to instantiate multiple full adder components, allowing it to perform binary addition on inputs of configurable width (default 32 bits). The module chains the carry signals from each full adder stage together to implement ripple-carry addition, producing a sum output and a final carry-out signal."* [2]

### Lab\_6\_Sequential\_Logic\_with\_Verilog\_HDL

*"This is a testbench for an asynchronous 4-bit up counter written in Verilog. The testbench verifies the counter's behavior by initializing it with a reset signal, keeping the enable signal low for 100ns (during which the counter should remain unchanged), then enabling counting for 320ns while clock pulses toggle every 10ns. The generated \`.vcd\` waveform file captures all signal transitions, allowing you to visualize whether the counter increments correctly from 0 to 15 and potentially rolls over during the enabled period."* [3]

### Lab\_7\_Synchronous\_Sequential\_Circuits

*"This Verilog module implements a \*\*Mealy finite state machine (FSM)\*\* with 6 states (A through F) that processes a serial input \`w\` and produces an output \`z\`. The combinational logic determines both the next state and output based on the current state and input, where the output depends on both the current state and input value (characteristic of Mealy machines). The sequential logic updates the state on each clock pulse and includes asynchronous reset functionality. This appears to be a lab exercise for CSCI 355 demonstrating synchronous sequential circuit design using behavioral Verilog."* [3]

## Sources

1.  VIU. (2026, April 29). *Computer science*. Computer Science Courses | Vancouver Island University | Canada. https://www.viu.ca/programs/courses/computer-science
2. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.
3. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2-4 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.