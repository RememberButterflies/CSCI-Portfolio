/**
 * @file ftp_client_ui.cpp
 * @author Patrick McGrath, CSCI 460, VIU
 * @version 1.0.0
 * @date February 3, 2025
 *
 * @brief 
 *
 * 
 * File contains functions for;
 *      - 
 * 
 * 
 * 
 *      Project #1 File Transfer Protocol (FTP) Client Software Application
 *          Copyright (C) 2025  Patrick McGrath
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

// Headers
#include "ftp_client_ui.h"
#include <string.h>
#include <iostream>


/**
* @brief Retrieves user input (command) after displaying prompt, "CSCI460FTP>>"
*
* @param userCommand, String to store user input.
*/
void getUserCommand(std::string& userCommand){

    // Display prompt and clear current contents of userCommand
    printf("%s", FTP_CLIENT_PROMT);
    userCommand.clear();

    // Get user command from usre
    std::getline (std::cin, userCommand);

    // End
    return;
}



/**
* @brief Displays server response
*
* @param response, The response to display
*/
void showFtpResponse(std::string response){

    // Print response to user
    std::cout << response;

    // End
    return;
}
