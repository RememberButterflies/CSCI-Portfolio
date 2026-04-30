# Solutions to Leetcode Problems

*as of April, '26*

## *Overview*

This is a selection of my solutions to Leetcode problems.

## Contents:

### 002\_Add\_Two\_Numbers

*"This solution adds two numbers represented as linked lists in reverse order (e.g., 342 + 465 is represented as 2→4→3 and 5→6→4). The algorithm iterates through both lists simultaneously, adding corresponding digits with a carry value, creating a new linked list with the sum digits and properly handling any final carry."* [1]

### 003\_Longest\_Substring\_Without\_Repeating\_Characters

*"*This solution finds the longest contiguous substring in a string that has no repeating characters. It uses a sliding window approach with two pointers (\`i\` and \`c\`) where it expands the window by moving \`c\` forward, and whenever a duplicate character is found, it shrinks the window by moving \`i\` past the previous occurrence of that character, tracking the maximum length encountered.*"* [1]

### 004\_Median\_of\_Two\_Sorted\_Arrays

*"This solution finds the median of two sorted arrays by merging them up to the midpoint without creating a fully merged array. For odd-length combined arrays, it returns the middle element; for even-length arrays, it returns the average of the two middle elements."* [1]

### 006\_Zigzag\_Conversion

*"This solution solves the \*\*Zigzag Conversion\*\* problem, which requires rearranging a string into a zigzag pattern across a given number of rows, then reading it back row-by-row. The algorithm calculates the period of the zigzag pattern (\`v = 2\*(numRows-1)\`) and uses it to determine which characters belong to each row, placing them sequentially into the result string."* [1]

### 012\_Integer\_to\_Roman

*"This solution converts an integer to its Roman numeral representation. The algorithm extracts each digit from right to left, uses nested switches to map each digit at its respective position (ones, tens, hundreds, thousands) to the corresponding Roman numeral substring, then concatenates them to build the final result."* [1]

### 032\_Longest\_Valid\_Parentheses

*"The problem is to find the length of the longest valid (properly matched) parentheses substring in a given string. The code uses a two-pass approach—first scanning forward to mark invalid closing parentheses that have no matching opening bracket, then scanning backward to mark invalid opening parentheses that have no matching closing bracket. Finally, it finds the longest consecutive sequence where both passes marked parentheses as valid."* [1]

### 065\_Valid\_Number

*"This solution validates whether a string represents a valid number according to specific rules (integers, decimals, and scientific notation). It uses two helper functions: \`case\_int()\` handles integers with optional signs and exponents, while \`case\_dec()\` handles decimal numbers by tracking dot placement and ensuring at least one digit is present before checking for exponents."* [1]

### 068\_Text\_Justification

*"This solution solves the \*\*Text Justification\*\* problem, which formats a list of words into lines of exactly \`maxWidth\` characters with proper spacing and alignment. The algorithm works by: (1) finding which words fit on each line using \`find\_end\_of\_line()\`, then (2) justifying them based on three cases—single words (left-justified), the last line (left-justified with single spaces), or normal lines (spaces distributed evenly with extra spaces added to the left gaps first)."* [1]

### 198\_House\_Robber

*"The House Robber problem asks you to find the maximum sum of money you can steal from houses where you cannot rob two adjacent houses. This solution uses dynamic programming with memoization, maintaining two DP arrays to track the maximum money obtainable from each position onward—one allowing robbery at the current house and one forbidding it—then recursively computing results while caching them to avoid recomputation."* [1]

### 701\_Insert\_into\_a\_Binary\_Search\_Tree

*"This solution inserts a value into a Binary Search Tree by creating a new node and traversing the tree to find the correct leaf position based on BST ordering rules (smaller values go left, larger go right). It handles the empty tree case separately, then uses a loop to navigate down the tree until finding an empty child pointer where the new node can be attached."* [1]

## Sources

1. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is a solution I wrote for a Leetcode problem. Give me an explanation, no longer than 2 sentences. Focus on what the problem is and how the problem is solved.]* [AI-generated text]. Anthropic.

## License

    Solutions to Leetcode Problems

    Copyright (C) 2026  Patrick McGrath

This program is free software: you can redistribute it and/or modify

it under the terms of the GNU General Public License as published by

the Free Software Foundation, either version 3 of the License, or

(at your option) any later version.

This program is distributed in the hope that it will be useful,

but WITHOUT ANY WARRANTY; without even the implied warranty of

MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

GNU General Public License for more details.

You should have received a copy of the GNU General Public License

along with this program.  If not, see <https://www.gnu.org/licenses/>.