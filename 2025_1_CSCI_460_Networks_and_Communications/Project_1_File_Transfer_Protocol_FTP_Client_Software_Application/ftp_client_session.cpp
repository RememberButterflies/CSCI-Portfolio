/**
 * @file ftp_client_session.cpp
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
#include "ftp_client_session.h"
#include "ftp_client_connection.h"
#include "ftp_client_command.h"
#include "ftp_client_ui.h"
#include "ftp_server_response.h"


/**
* @brief Handles starting a client connection over control socket to specified FTP server.
*        If connection is successful, server response is received and displayed.
*
* @param serverIP, FTP server's IP address.
* @param serverPort, FTP server's Port number
* @param clientFtpSession, The data structure for the client's FTP sockets and other variables.
*/
void startClientFTPSession(const char* serverIP, int serverPort, ClientFtpSession& clientFtpSession){
    
    // Open connection to server at specified port, updating controlSocket
    connectToServer(clientFtpSession.controlSocket, serverIP, serverPort);

    // Check controlSocket to see if conneciton was succesful
    if (clientFtpSession.controlSocket != -1){

        // Receive response from server
        char* buffer;
        size_t buffersize = BUFFER_SIZE;
        buffer = (char*)malloc(buffersize*sizeof(char));
        if (buffer == NULL){
            return;
        }
        int recReturn = receiveFromServer(clientFtpSession.controlSocket, buffer, buffersize);

        // Check if receiving message was succesful
        if (recReturn != -1){
        // Show response
            showFtpResponse(std::string(buffer));
        }
        // Free memory
        free(buffer);
    }

    // End
    return;
}


/**
* @brief Handles stopping a client connection over both sockets from server(s) specified in client's connections,
*        if there are any. Client's status is set to not logged in and not authenticated.
*
* @param clientFtpSession, The data structure for the client's FTP sockets and statuses
*/
void stopClientFTPSession(ClientFtpSession& clientFtpSession){

    // Close both control and data connection sockets from ftp client
    // Set both logged in and authentication flares to false
    disconnectFromServer(clientFtpSession.controlSocket);
    disconnectFromServer(clientFtpSession.dataSocket);
    clientFtpSession.isLoggedIn = false;
    clientFtpSession.isUserAuthenticated = false;
    return;
}