# Term\_Project\_Sittie-Typpie\_Reader\_Writer\_Program

CSCI 439 - Advanced Topics in Programming*, Spring, '25*

## Overview

Sittie-Typpie is a turn-based textfile-based chat log script. Its purpose is to simulate the inner structure of a potential user-friendly chat system. That system would be the interface for users to do various things like leave messages. This program facilitates what information that system would have access to based on previous interactions and also how to handle and record current interactions to the same log.

The name is because, like Walkie-Talkies, Sittie-Typpie uses a shared medium between all users who must take turns to use it. However Walkie-Talkies are used by talking and can be used during walking. Whereas Sittie-Typpie must be used by typing and while sitting.

## Overview, AI-summary

*"This program implements a \*\*turn-based text file-based chat log system\*\* that simulates the backend infrastructure of a multi-user messaging platform. It reads, parses, and manages chat logs stored in a custom \`.sittie\` file format. The program uses a recursive descent parser to tokenize and validate log files according to a formal grammar specification, extracting information about users, messages, events, invitations, and responses. Users can then log in with a valid user ID and interact with the existing chat log by adding new entries such as messages, events, responses, or user invitations—all of which are written back to the file in the proper format.*

*The core functionality revolves around managing \*\*sequences\*\* (representing user sessions) and \*\*entries\*\* (representing individual interactions like messages or events). The program enforces strict validation rules, such as ensuring entry IDs are sequential, users have been properly invited before logging in, and all referenced entries exist. It includes a command-line interface with operations to view the log, post messages, create events, respond to entries with text or reaction emojis (thumbs up/down, smiley), and invite other users. "* [1]

## Usage

### To compile, in the source code directory, enter:

			make

### To uninstall and remove compiled objects, enter:

			make clean

### Compilation will produce two versions of the program; the regular one and a test version with an excess of extra debugging information:

			projx		and		projxTest

### To run the program, make sure you are the only person currently using the chat log you intend to open. Then, enter:

			./projx		or		./projxTest

### To use the program, follow the following steps:

1. The program asks for the filename to open or create. (without extension)
    1. If the file does not exist, it is created, otherwise it is opened.
    2. If it is opened, it is tokenized and parsed. If not successful, the program exits.
2. The program asks for a userID number, front-padded with 0’s (without leading 'U')
    1. If the user is not in the log, the program exits.
    2. If the user is in log, relevant log information is printed.
    3. The program also printed the beginning of this sequence to log.
3. While the user has not selected to quit the program, the program will ask for a command and execute it

### The commands are:

| h | Prints these commands (no interaction) |
| l | Prints the in-memory chat log information (no interaction) |
| m | To record a message entry. |
| e | To record an event entry |
| r | To record a response entry |
| i | To record a user invitation |
| q | To quit the program. (no interaction) |

### Command Interactions:

| m | The program will ask for text to enter as message. |
| e | The program will ask for the name of the event.\n\nThe program will ask for the location of the event, optional.\n\nThe program will ask for the time of the event, optional. |
| r | The program will ask for the entryID of the entry being responded to.\n\nThe program will ask for either text or to select an optional response. |
| i | The program will ask for a userID to invite. |

## Specifications

### Literals:

| USERID | U([0-9][0-9][0-9]) |
| ENTRYID | E([0-9][0-9][0-9]) |
| TEXTLIT | ["][^"]\*["] |

### Tokens:

### 

| OPEN | {{ |
| CLOSE | }} |
| INVITE | INV |
| LOGIN | LGN |
| MESSAGE | MSG |
| EVENT | EVT |
| RESPONSE | RSP |
| THUMBSUP | TMUP |
| THUMBSDOWN | TMDN |
| SMILEYFACE | SMILEY |
| BLANK | BLNK |

### Grammar Rules:

| start | sequences |
| sequences | sequence sequences |
| sequence | OPEN LOGIN USERID entries CLOSE |
|  | OPEN LOGIN USERID CLOSE |
| entries | entry entries |
| entry | messageentry |
|  | evententry |
|  | responseentry |
|  | inviteentry |
| messageentry | OPEN ENTRYID MESSAGE TEXTLIT CLOSE |
| evententry | OPEN ENTRYID EVENT TEXTLIT TEXTLIT TEXTLIT CLOSE |
|  | OPEN ENTRYID EVENT TEXTLIT BLANK TEXTLIT CLOSE |
|  | OPEN ENTRYID EVENT TEXTLIT TEXTLIT BLANK CLOSE |
|  | OPEN ENTRYID EVENT TEXTLIT BLANK BLANK CLOSE |
| responseentry | OPEN ENTRYID RESPONSE ENTRYID TEXTLIT CLOSE |
|  | OPEN ENTRYID RESPONSE ENTRYID reactiontoken CLOSE |
| inviteentry | OPEN ENTRYID INVITE USERID CLOSE |
| reactiontoken | THUMBSUP |
|  | THUMBSDOWN |
|  | SMILEYFACE |

### Notes:

The logs are kept in the folder "logs" and all have the extension ".sittie". When this program asks for a filename, do not give this folder or extension, just the name.

When the program asks the user for a userID pr entryID, the user should give the response as 3 integers without a leading character. (if the value is less than 100, it will begin with zeros)

Text literals are stored as single words in the log, regardless if they are in-fact mutiple words. The placeholder for spaces in storage is "\_SPACE\_".

This series of characters is forbidden in series but not in combination (feel free to use underscore in other contexts.)

## Sources

1. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 paragraph explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.

## License

    Sittie-Typpie Reader / Writer Program

    Copyright (C) 2025 Patrick McGrath

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