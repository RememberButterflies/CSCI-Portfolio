/**
 * @file    ftp_server_session.cpp
 * @author  Patrick McGrath, CSCI 460, VIU
 * @version 1.0.0
 * @date    April 7, 2025
 *
 * @brief   File contains functions for;
 *      - 
 * 
 * 
 * 
 *      Project #2 File Transfer Protocol (FTP) Server Software Application
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


// Includes
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "ftp_server_session.h"
#include "ftp_server_net_util.h"
#include "ftp_server_connection.h"
#include "ftp_server_request.h"
#include "ftp_server_response.h"


// Functions


/**
* @brief Starts a client FTP session on the server. Receives FTP requests from the client and sends appropriate responses.
*
* @param clientFtpSession, ClientFtpSession& the client FTP session to start.
*
*/
void startClientFTPSession(ClientFtpSession& clientFtpSession){
    
    //Send CONNECTED_RESPONSE to the client using 'clientFtpSession.controlSocket' by calling
    //'sendToClient()' function.
    sendToClient(clientFtpSession.controlSocket, CONNECTED_RESPONSE, strlen(CONNECTED_RESPONSE));

    //Determine the current working directory by get_current_dir_name() system call and assign it to
    //'clientFtpSession.rootDir' field.
    clientFtpSession.rootDir = get_current_dir_name();
    
    
    bool isError = false;
    bool isTimedout = false;
    // as long as the client is connected, i.e., clientFtpSession.controlSocket is not equal to -1.
    while (clientFtpSession.controlSocket != -1){
        isError = false;
        isTimedout = false;

        //		Wait for client's FTP request for FTP_CLIENT_SESSION_TIMEOUT_SEC + 0.000001xFTP_CLIENT_SESSION_TIMEOUT_USEC time
        //		by calling 'isSocketReadyToRead()' function.
        bool sockReadyResult = isSocketReadyToRead(clientFtpSession.controlSocket, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedout);
        if (sockReadyResult == true){       // no timeout
            // Check for error
            if ((isError == false) && (isTimedout == false)){
                // receive the request by calling receiveFromClient() function
                char* buffer = (char*)malloc(FTP_RESPONSE_MAX_LENGTH);
                int receiveResult = receiveFromClient(clientFtpSession.controlSocket, buffer, FTP_RESPONSE_MAX_LENGTH);

                // interpret the request, take appropriate action, and sends appropriate response to the client by calling
                // 'interpretFtpRequest()' function.
                if (receiveResult != -1){
                    interpretFtpRequest(buffer, clientFtpSession);
                }
                // Free memory
                free(buffer);
            } else {
                // Timeout or Error
                // send CONNECTION_RESET_BY_PEER to the client by
                // calling sendToClient() function, stop client FTP session by calling 'stopClientFTPSession()' function and
                // return from this function.
                sendToClient(clientFtpSession.controlSocket, CONNECTION_RESET_BY_PEER, strlen(CONNECTION_RESET_BY_PEER));
                stopClientFTPSession(clientFtpSession);
                return;
            }
        }
    }

    // Disconnected
    return;
}



/**
 * @brief Stops a client FTP session on the server. Closes the control socket, data socket, and data listener socket.
 *
 * @param clientFtpSession, ClientFtpSession& the client FTP session to stop.
 *

 */
void stopClientFTPSession(ClientFtpSession& clientFtpSession){

    //Get client's IP address (e.g., 192.168.18.157) by calling getRemoteIPAddressFromSocketDescriptor() function with 
    //clientFtpSession.controlSocket.
    char* IPResult = getRemoteIPAddressFromSocketDescriptor(clientFtpSession.controlSocket);

    //Get client's port number (e.g., 47376) by calling getRemotePortFromSocketDescriptor() function with 
    //clientFtpSession.controlSocket.
    int PortResult = getRemotePortFromSocketDescriptor(clientFtpSession.controlSocket);

    // Display message
    //      "FTP Server: Closing FTP Connection Client IP: //IPResult//, Port: //PortResult//"
    std::cout << "FTP Server: Closing FTP Connection Client IP: " << IPResult << ", Port: " << PortResult << std::endl;

    //Close controlSocket, dataSocket, and dataListenerSocket of clientFtpSession by calling closeSocket() function
    //individually.
    closeSocket(clientFtpSession.controlSocket);
    closeSocket(clientFtpSession.dataSocket);
    closeSocket(clientFtpSession.dataListenerSocket);

    //Set false to both clientFtpSession.isUserAuthenticated and clientFtpSession.isLoggedIn.
    //Set nullptr to clientFtpSession.rootDir.
    clientFtpSession.isUserAuthenticated = false;
    clientFtpSession.isLoggedIn = false;
    if (clientFtpSession.rootDir != nullptr) {
        free(clientFtpSession.rootDir);
        clientFtpSession.rootDir = nullptr;
    }

    // End
    return;
}