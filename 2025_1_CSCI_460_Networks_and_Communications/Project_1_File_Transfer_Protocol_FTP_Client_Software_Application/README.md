# Project\_1\_File\_Transfer\_Protocol\_FTP\_Client\_Software\_Application

CSCI 460 - Networks and Communications*, Spring, '25*

## *Overview*

*"This FTP client application allows users to connect to and interact with a File Transfer Protocol (FTP) server through a command-line interface. It supports standard FTP operations such as user authentication, directory navigation, file listing, and file retrieval using both control and data socket connections."*  [1]

## Usage

Command prompt "CSCI460FTP>>" will appear after building and running client. The user can enter any of the following user commands:

| help | Displays a list of commands to user. |
| user <username>  | Sends request for user <username> to login. |
| pass <password> | Sends password <password> for <username> to login. |
| pwd | Prints current working directory. |
| dir | Prints contents of current working directory. |
| cwd <dirname> | Changes working directory to <dirname>. |
| cdup | Changes working directory to parent of current directory. |
| get <filename> | Retrieves file <filename> from server. |
| quit | Quits session. |

Note: This version of the client and server uses a single hardcoded username and password as well as IP address and port. Additionally, only one test file for retrieval is provided.

| username | csci460 |
| password | 460pass |
| IP | 127.0.0.1 |
| Port | 21 |
| filename | duck.jpeg |

## Sources

1. Claude Haiku 4.5. (2026, April 29). *Response to prompt: [This is some code I wrote as an assignment. Give me a 2 sentence explanation of what this program does and/or its purpose.]* [AI-generated text]. Anthropic.

## License

    Project #1 File Transfer Protocol (FTP) Client Software Application

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