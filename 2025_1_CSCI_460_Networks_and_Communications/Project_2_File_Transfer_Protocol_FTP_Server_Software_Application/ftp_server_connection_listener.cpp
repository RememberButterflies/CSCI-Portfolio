/**
 * @file    ftp_server_connection_listener.cpp
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


// Headers
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include "ftp_server_connection_listener.h"
#include "ftp_server_net_util.h"



/**
* @brief Starts the listener socket by calling gethostname(), getaddrinfo(), socket(), setsockopt(), bind(), and listen() system calls.
*
* @param port, char* the port number to bind the socket to.
* @param listenerSocket, int& reference to the socket descriptor to be used for listening.
* @param succeded, bool& reference to set if the socket was successfully created and bound.
*
*/
void startListenerSocket(char* port, int& listenerSocket, bool& succeded){
    // Check parameters
    if (port == nullptr){
        return;
    }

    
    //Get the 'hostname' of this machine by calling gethostname() system call.
    char* buffer = (char*)malloc(MAX_IP_ADDRESS_LENGTH);
    if (buffer == nullptr){
        return; // allocation error
    }
    int hostVal = gethostname(buffer, MAX_IP_ADDRESS_LENGTH);
    if (hostVal == -1){
        succeded = false;
        return;
    }


    //Get the 'addrinfo' by calling getaddrinfo() system call with 'hostname', 'port' and an 'addrinfo', hints of AF_INET, SOCK_STREAM, and AI_PASSIVE. 
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    struct addrinfo *addrResult;
    int addrVal = getaddrinfo(NULL, port, &hints, &addrResult);
    if (addrVal != 0){
        succeded = false;
        return;
    }


    //Open a socket by calling socket() system call with 'listenerSocket' and the address family, the socket type, and the protocol of the above 'addrinfo'
    listenerSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (listenerSocket == -1){
        succeded = false;
        return;
    }


    //Set the socket option of 'listenerSocket' socket to re-use the port (SOL_SOCKET, SO_REUSEADDR) by calling setsockopt() system call. 
    int enable = 1;
    int setsockVal = setsockopt(listenerSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    if (setsockVal == -1){
        succeded = false;
        return;
    }

    //Bind  the IP address from 'addrinfo' to 'listenerSocket' by calling bind() system call.
    int bindVal = bind(listenerSocket, addrResult->ai_addr, addrResult->ai_addrlen);
    if (bindVal == -1){
        succeded = false;
        return;
    }

    //Make the 'listenerSocket' ready to listen connection request by calling listen() system call.
    int listenVal = listen(listenerSocket, MAX_CLIENT_CONNECTIONS);
    if (listenVal == -1){
        succeded = false;
        return;
    }

    // Success
    succeded = true;
    return;
}








/**
 * @brief Checks if the listener socket is ready to accept a connection request.
 * 
 * @param listenerSocket, int the socket descriptor to check.
 * @param timeoutSec, int the timeout in seconds.
 * @param timeoutUSec, int the timeout in microseconds.
 * @param isError, bool& reference to set if an error occurred.
 * @param isTimedout, bool& reference to set if the operation timed out.
 */
bool isListenerSocketReady(const int listenerSocket, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout){
    // Check parameters
    if (listenerSocket == -1){
        isError = true;
        return false;
    }

    // isSocketReadyToRead
    bool result = isSocketReadyToRead(listenerSocket, timeoutSec, timeoutUSec, isError, isTimedout);
    return result;
}





/**
 * @brief Accepts a connection request on the listener socket and retrieves the client's IP address and port number.
 * 
 * @param listenerSocket, int the socket descriptor to accept connections on.
 * @param clientSocket, int& reference to set the accepted client socket descriptor.
 * @param clientIP, char*& reference to set the client's IP address.
 * @param clientPort, int& reference to set the client's port number.
 */
void acceptClientConnection(const int listenerSocket, int& clientSocket, char*& clientIP, int& clientPort){
    
    // variables
    clientIP = nullptr;
    clientPort = -1;

    //Accept a connection request on 'listenerSocket' by calling accept() system call.
    // and assign the socket returned by accept() system call to 'clientSocket'.
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int acceptResult = accept(listenerSocket, (struct sockaddr *)&addr, &addrlen);
    if (acceptResult == -1){
        return; // Failure
    } else {
        clientSocket = acceptResult;
    }

    //Retrieve IP address from client socket address 'sockaddr_in' by calling inet_ntoa() library function and
    //assign the IP address to 'clientIP'.
    char* IPResult = inet_ntoa(addr.sin_addr);
    if (IPResult == nullptr){
        return; // Failure
    } else {
        clientIP = IPResult;
    }

    //Retrieve the port number from client socket address 'sockaddr_in' by calling ntohs() library function and
    //assign the port number to 'clientPort'.
    int ntohsResult = ntohs(addr.sin_port);
    if (ntohsResult == -1){
        return; // Failure
    } else {
        clientPort  = ntohsResult;
    }

    // End
    return;
}



/**
 * @brief Closes the listener socket.
 * 
 * @param listenerSocket, int& reference to the socket descriptor to close.
 */
void closeListenerSocket(int& listenerSocket){
    closeSocket(listenerSocket);
    return;
}