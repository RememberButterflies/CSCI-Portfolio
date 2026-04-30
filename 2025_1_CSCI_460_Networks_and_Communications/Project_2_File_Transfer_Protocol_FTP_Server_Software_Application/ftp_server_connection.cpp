/**
 * @file    ftp_server_connection.cpp
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


// Header
#include <sys/socket.h>
#include "ftp_server_connection.h"





/**
 * @brief Sends a message to the client on the specified socket.
 * 
 * @param clientSocket, int the socket descriptor to send the message on.
 * @param message, const char* the message to send.
 * @param messageLength, int the length of the message to send. 
 * 
 * @return int the number of bytes sent, or -1 on failure.
 */
int sendToClient(const int clientSocket, const char* message, const int messageLength){
    // Check parameters
    if ((clientSocket == -1) || (message == nullptr)){
        return -1;
    }

    //Send the 'message' of length 'messageLength' bytes to the client by calling send() 
    //system call with 'clientSocket'.
    ssize_t result = send(clientSocket, message, (size_t)messageLength, 0);
    if (result == -1){
        return -1;  // Failure
    }

    // Success
    // Return the actual number of bytes sent by send() system call.
    return (int)result;
}






/**
 * @brief Receives a message from the client on the specified socket.
 * 
 * @param clientSocket, int the socket descriptor to receive the message on.
 * @param message, char* the buffer to store the received message.
 * @param messageLength, int the length of the buffer to store the message.
 * 
 * @return int the number of bytes received, or -1 on failure.
 */
int receiveFromClient(const int clientSocket, char* message, int messageLength){
    // Check parameter
    if ((clientSocket == -1) || (messageLength <= 0)){
        return -1;
    }

    //Receive a maximum 'messageLength' of bytes into a buffer 'message' by caling
    //recv() system call with 'clientSocket'.
    ssize_t result = recv(clientSocket, message, (ssize_t)messageLength, 0);
    if (result == -1){
        return -1;  // Failure
    }
    if (message[result] != '\0'){
        message[result] = '\0';
    }

    // Success
    //Return the actual number of bytes received by recv() system call.
    return (int)result;
}