/**
 * @file ftp_client_connection.cpp
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
#include <string.h>
#include <limits.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "ftp_client_connection.h"


/**
* @brief Handles connection to server via IPv4 using server's IP and port number.
*        Connection information is stored in socket descriptor.
*
* @param socketDescriptor, The socket descriptor used in connection.
* @param serverIP, The IP address of server.
* @param serverPort, The port number. 
*/
void connectToServer(int& socketDescriptor, const char* serverIP, int serverPort){

    // Check if socket is already in use
    // If it is, connection attempt stops
    if (socketDescriptor != -1){
        return;
    }

    // Assuming IPv4
    // (need to change if using IPv6 or both)
    int tempsock = socket(AF_INET, SOCK_STREAM, 0);

    // Assign socketDescriptor and check if valid
    // If not valid, connection attempt stops
    socketDescriptor = tempsock;
    if (socketDescriptor == -1){
        return;
    }

    // Struct for serverAddress
    struct sockaddr_in serverAddress;

    // Configure server address for IPv4
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;                 // IPv4
    serverAddress.sin_port = htons(serverPort);         // Convert port to Network byte order

    // Convert IP string to binary form and store in serverAddress
    // If conversion unsuccessful, socketDecriptor is closed and connection attempt stops
    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) != 1){
        disconnectFromServer(socketDescriptor);
        return;
    }

    // Connect to server
    // If connection unsuccessful, socketDecriptor is closed and connection attempt stops
    struct sockaddr *sockServAddress = (struct sockaddr *)&serverAddress;
    if (connect(socketDescriptor, sockServAddress, sizeof(serverAddress)) == -1){
        disconnectFromServer(socketDescriptor);
        return;
    }

    // End
    return;
}


/**
* @brief Handles disconnection from server. Closes network connection and sets descriptor to invalid
*
* @param socketDescriptor, The socket descriptor used in connection.
*/
void disconnectFromServer(int& socketDescriptor){

    // Close network connection and set the socket descriptor to -1
    close(socketDescriptor);
    socketDescriptor = -1;
    return;
}



/**
* @brief Handles sending a message to server that socket descriptor is connected to.
*        The number of bytes sent is returned.
*
* @param socketDescriptor, The socket descriptor used in connection.
* @param message, The message being sent.
* @param messageLength, The length of the message.
*/
int sendToServer(int socketDescriptor, const char* message, int messageLength){
    // Send message to server
    // Return number of bytes sent
    int sendReturn = send(socketDescriptor, message, messageLength, 0);
    return sendReturn;
}


/**
* @brief Receive message from server that socket descriptor is connected to.
*
* @param socketDescriptor, The socket descriptor used in connection.
* @param message, Character array for receiving message
* @param messageLength, The maximum possible length of message.
*/
int receiveFromServer(int socketDescriptor, char* message, int messageLength){

    // Receive message from server
    // Return number of bytes received
    ssize_t recvReturn = recv(socketDescriptor, message, messageLength, 0);
    if (recvReturn > INT_MAX){
        return -1;
    }
    return (int)recvReturn;
}