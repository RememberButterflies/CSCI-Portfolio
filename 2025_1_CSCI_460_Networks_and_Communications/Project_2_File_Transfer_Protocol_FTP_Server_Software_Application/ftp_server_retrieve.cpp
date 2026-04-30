/**
 * @file    ftp_server_retrieve.cpp
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
#include <sys/stat.h>
#include <unistd.h>
#include "ftp_server_retrieve.h"
#include "ftp_server_connection.h"
#include "ftp_server_response.h"

/**
 * @brief Get the size of a file.
 * 
 * @param filename The name of the file to get the size of.
 */
int getFileSize(const char* filename){

    //Check whether the file with 'filename' is accessible or not by calling access() system call.
    int accessResult = access(filename, F_OK);
    if(accessResult == -1){
        return -1;
    }

    // variable for stat
    struct stat sb;
    
    //If file is accessible, get file stat by calling stat() system call 
    int statResult = stat(filename, &sb);
    if(statResult == -1){
        return -1;      // error
    }

    // return file size from the stat.
    int size = (int)sb.st_size;
    return size;
}






/**
 * @brief Send a file to the client.
 * 
 * @param filename The name of the file to send.
 * @param dataSockDescriptor The socket descriptor to send the file on.
 */
int sendFile(const char* filename, int& dataSockDescriptor){

    //Check whether the file with the 'filename' is accessible or not by calling access() system call.
    int accessResult = access(filename, F_OK);
    if(accessResult == -1){
        return -1;
    }

    // get size of file & check if file is accessible using stat system call in getFileSize
    int size = getFileSize(filename);
    if (size == -1){
        return -1;
    }



    //Open the file in FILE_OPEN_MODE by calling fopen() library function.
    FILE* fptr;
    fptr = fopen(filename, FILE_OPEN_MODE);
    if(fptr == NULL){
        return -1;
    }

    //Initialize a send-to-byte-count to the size of the file.
    int sendToByteCount = size;

    // Loop until sendToByteCount is zero
    while (sendToByteCount > 0){

        // If send-to-byte-count is greater than or equal to DATA_SOCKET_SEND_BUFFER_SIZE
        if (sendToByteCount >= DATA_SOCKET_SEND_BUFFER_SIZE){
            char* buffer = (char*)malloc(DATA_SOCKET_SEND_BUFFER_SIZE*(sizeof(char)));
            if (buffer == nullptr){
                return -1;  // Failure
            }

            // Read DATA_SOCKET_SEND_BUFFER_SIZE bytes from the file in a buffer by caling fread() library function.
            fread(buffer, DATA_SOCKET_SEND_BUFFER_SIZE, 1, fptr);

            // Send the buffer content to the client using data connection represented by 'dataSockDescriptor' by calling sendToClient() function.
            sendToClient(dataSockDescriptor, buffer, DATA_SOCKET_SEND_BUFFER_SIZE);
            
            // free memory
            free(buffer);

            // Update send-to-byte-count.
            sendToByteCount = sendToByteCount - DATA_SOCKET_SEND_BUFFER_SIZE;
        } else {

            // If send-to-byte-count is less than DATA_SOCKET_SEND_BUFFER_SIZE
            char* buffer = (char*)malloc(sendToByteCount*(sizeof(char)));
            if (buffer == nullptr){
                return -1;  // Failure
            }

            // Read send-to-byte-count bytes from the file in a buffer by calling fread() library function.
            fread(buffer, sendToByteCount, 1, fptr);

            // Send the buffer content to the client using data connection represented by 'dataSockDescriptor' by calling sendToClient() function.
            sendToClient(dataSockDescriptor, buffer, sendToByteCount);

            // Free memory
            free(buffer);

            // Update send-to-byte-count.
            sendToByteCount = 0;
        }
    }

    // close file
    fclose(fptr);

    // Return the size of the file.
    return size;
}