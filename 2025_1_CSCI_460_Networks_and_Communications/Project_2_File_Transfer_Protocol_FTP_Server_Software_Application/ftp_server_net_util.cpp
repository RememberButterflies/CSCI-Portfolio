/**
 * @file    ftp_server_net_util.cpp
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
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include "ftp_server_net_util.h"



// Functions

/**
* @brief Closes the socket nrepresented by 'sockDescriptor' by calling close() system call.
*
* @param sockDescriptor, int the socket descriptor to be closed.
*/
void closeSocket(int& sockDescriptor){
    // Check parameter
    if (sockDescriptor == -1){
        return;
    }
    // Close network connection and set the socket descriptor to -1
    close(sockDescriptor);
    sockDescriptor = -1;
    return;
}








/**
* @brief Gets the local port number from the socket descriptor by calling getsockname() system call.
*
* @param sockDescriptor, int the socket descriptor to get the port number from.
*
* @return int the port number of the socket descriptor.
*/
int getPortFromSocketDescriptor(const int sockDescriptor){
    // Check parameter
    if (sockDescriptor == -1){
        return -1;
    }

    // Return variables for getting socket address
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    // Get the socket address
    int result = getsockname(sockDescriptor, (struct sockaddr*)&addr, &addrlen);
    if (result == -1){
        return -1;  // Failure
    } 

    // Return the port number
    result = ntohs(addr.sin_port);
    return result;
}








/**
* @brief Gets the IP address from the socket address by calling system call inet_ntoa,
*        which is got from the socket descriptor by calling getsockname() system call.
*
* @param sockDescriptor, int the socket descriptor to get the IP address from.
*
* @return char* the IP address of the socket descriptor.
*/
char* getIPAddressFromSocketDescriptor(const int sockDescriptor){

    // Check parameter
    if (sockDescriptor == -1){
        return nullptr;
    }

    // Return variables for getting socket address
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    // Get the socket address
    int result = getsockname(sockDescriptor, (struct sockaddr*)&addr, &addrlen);
    if (result == -1){
        return nullptr;  // Failure
    } 


    // Get IP address from local socket
    char* IPstr = inet_ntoa(addr.sin_addr);
    char* IPcopy = (char*)malloc(strlen(IPstr) + 1);
    strcpy(IPcopy, IPstr);
    return IPcopy;
}















/**
 * @brief Gets the remote port number from the socket address by calling system call ntohs, 
 *        which is got from socket descriptor by calling getpeername() system call.
 *
 * @param sockDescriptor, int the socket descriptor to get the remote port number from.
 *
 * @return int the remote port number of the socket descriptor.
 */ 
int getRemotePortFromSocketDescriptor(const int sockDescriptor){
    // Check parameters
    if (sockDescriptor == -1){
        return -1;
    }

    // Return variables for getpeername
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    // Get the socket address
    int result = getpeername(sockDescriptor, (struct sockaddr*)&addr, &addrlen);
    if (result == -1){
        return -1;  // Failure
    } else {
        result = -1;    // reset result
    }
    // Return the port number
    result = ntohs(addr.sin_port);
    return result;
}








/**
 * @brief Gets the remote IP Address from the socket address by calling system call inet_ntoa,
 *        which is got from the socket descriptor by calling getpeername() system call.
 *
 * @param sockDescriptor, int the socket descriptor to get the remote IP address from.
 *
 * @return char* the remote IP address of the socket descriptor.
 */ 
char* getRemoteIPAddressFromSocketDescriptor(const int sockDescriptor){
    // Check parameters
    if (sockDescriptor == -1){
        return nullptr;
    }

    // Return variables for getpeername
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    // Get the socket address
    int result = getpeername(sockDescriptor, (struct sockaddr*)&addr, &addrlen);
    if (result == -1){
        return nullptr;  // Failure
    }

    // Get IP address from local socket
    char* IPstr = inet_ntoa(addr.sin_addr);
    return IPstr;
}







/**
 * @brief Checks if the socket is ready to read by calling select() system call on sockDescriptor with supplied timeout values.AF_FILE
 * 
 * @param sockDescriptor, int the socket descriptor to check if it is ready to read.
 * @param timeoutSec, int the timeout value in seconds.
 * @param timeoutUSec, int the timeout value in microseconds.
 * @param isError, bool& reference to set if there is an error.
 * @param isTimedout, bool& reference to set if there is a timeout.
 * 
 * @return bool true if the socket is ready to read, false otherwise.
 */
bool isSocketReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool& isTimedout){

    // Check parameters
    if (sockDescriptor == -1){
        return false;
    }


    // Variables for select() call
    fd_set rfds;                    // file descriptor set
    FD_ZERO(&rfds);                 // zero the descriptor set
    FD_SET(sockDescriptor, &rfds);  // set descriptor set to sockDescriptor
    struct timeval tv;              // struct for timeout
    tv.tv_sec = timeoutSec;         // set timeout
    tv.tv_usec = timeoutUSec;       // set timeout
    int nfds = sockDescriptor + 1;  // nfds = 1 + max value of descriptor



    // See if something is waiting on the socket
    int result = select(nfds, &rfds, NULL, NULL, &tv);
    if (result == -1){          // error result
        isError = true;         // set error
        return false;
    } else if (result == 0){    // timeout result
        isTimedout = true;      // set timeout
        return false;
    } else {                    // no error or timeout
    // All good
        return true;
    }

    // Unknown results
    return false;

}