# CSCI 439 - Advanced Topics in Programming

*Spring, '25*

## *Overview*

This course examines selected emerging and advanced topics in programming. Topics may include: a detailed analysis of language design, semantics, verification, resource utilization, language support for concurrency, meta-programming, and compilers. [1]

## Contents:

### Term\_Project\_Sittie-Typpie\_Reader\_Writer\_Program

*"This program implements a \*\*turn-based text file-based chat log system\*\* that simulates the backend infrastructure of a multi-user messaging platform. It reads, parses, and manages chat logs stored in a custom \`.sittie\` file format. The program uses a recursive descent parser to tokenize and validate log files according to a formal grammar specification, extracting information about users, messages, events, invitations, and responses. Users can then log in with a valid user ID and interact with the existing chat log by adding new entries such as messages, events, responses, or user invitations—all of which are written back to the file in the proper format.*

*The core functionality revolves around managing \*\*sequences\*\* (representing user sessions) and \*\*entries\*\* (representing individual interactions like messages or events). The program enforces strict validation rules, such as ensuring entry IDs are sequential, users have been properly invited before logging in, and all referenced entries exist. It includes a command-line interface with operations to view the log, post messages, create events, respond to entries with text or reaction emojis (thumbs up/down, smiley), and invite other users. "* [2]

## Sources

1.  VIU. (2026, April 29). *Computer science*. Computer Science Courses | Vancouver Island University | Canada. https://www.viu.ca/programs/courses/computer-science
2. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 paragraph explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.