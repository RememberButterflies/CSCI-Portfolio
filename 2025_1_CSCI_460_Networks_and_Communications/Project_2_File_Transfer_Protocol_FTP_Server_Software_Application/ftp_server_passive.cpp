/**
 * @file    ftp_server_passive.cpp
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
#include <cstdio>
#include <cstring>
#include "ftp_server_passive.h"
#include "ftp_server_connection_listener.h"
#include "ftp_server_connection.h"
#include "ftp_server_net_util.h"
#include "ftp_server_response.h"



// Helper Function Declaration
void replaceAll(char* str, char find, char replace);    //Replace all the occurrences of 'find' character in 'str' with 'replace' character.

// Functions
void replaceAll(char* str, char find, char replace){
    // Check for parameters
    if (str == nullptr){
        return;
    }

    // Replace characters
    int length = (int)strlen(str);
    for (int i=0; i<length; i++){
        if (str[i] == find){
            str[i] = replace;
        }
    }
    // End
    return;
}


/**
 * @brief Creates a passive success response message for the client.
 * 
 * @param response, char* the response message to be created.
 * @param passiveListenerSockDescriptor, const int the socket descriptor for the passive listener.
 */
void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor){

    //Determine the passive listener port number from 'passiveListenerSockDescriptor' by calling 'getPortFromSocketDescriptor()' function.
    int PortResult = getPortFromSocketDescriptor(passiveListenerSockDescriptor);

    //Determine the local IP address by calling 'getIPAddressFromSocketDescriptor()' function.
    char* IPResult = getIPAddressFromSocketDescriptor(passiveListenerSockDescriptor);

    // Creat formatted message
    char* message = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*(sizeof(char)));
    if (message == nullptr){
        return;
    }

    // Includes both the IP address and the port number into passive success response according to RFC959.
    int portA = PortResult / 256;
    int portB = PortResult % 256;

    // In passive response message, dots(.) in dotted decimal IP address are replaced by commas(,)
    replaceAll(IPResult, '.', ',');

    // format the message with IP address and port number
    sprintf(message, PASSIVE_SUCCESS_RESPONSE, IPResult, portA, portB);

    // update the message parameter with the formatted message
    strcpy(response, message);

    // free the temporary message
    free(message);

    // End
    return;
}











/**
 * @brief Starts a passive listener socket that can listen connection requests from the client.
 * 
 * @param clientFtpSession, ClientFtpSession& the client FTP session to start the passive listener for.
 * @param succeded, bool& reference to set if the socket was successfully created and bound.
 */
void startPassiveListener(ClientFtpSession& clientFtpSession, bool& succeded){


    // Memory for the PASSIVE_DEFAULT_PORT
    char* temp = (char*)malloc((strlen(PASSIVE_DEFAULT_PORT)+1)*(sizeof(char)));

    // Copy the PASSIVE_DEFAULT_PORT to the temp variable
    strcpy(temp, PASSIVE_DEFAULT_PORT);

    //Start a passive listener socket that can listen connection requests from the client
    //by calling 'startListenerSocket()' function with PASSIVE_DEFAULT_PORT and clientFtpSession.dataListenerSocket.
    startListenerSocket(temp, clientFtpSession.dataListenerSocket, succeded);
    
    // free the temp variable
    free(temp);

    // End
    return;
}











/**
 * @brief Stops the passive listener socket by closing it.
 * 
 * @param clientFtpSession, ClientFtpSession& the client FTP session to stop the passive listener for.
 */
void stopPassiveListener(ClientFtpSession& clientFtpSession){

    //Stop passive listener socket by calling closeSocket() with clientFtpSession.dataListenerSocket.
    closeSocket(clientFtpSession.dataListenerSocket);
    return;
}









/**
 * @brief Handles the FTP PASV requests.
 * 
 * @param clientFtpSession, ClientFtpSession& the client FTP session to handle the request for.
 * 
 */
void enteringIntoPassive(ClientFtpSession& clientFtpSession){

    //Start a passive connection listener by calling 'startPassiveListener()' function.
    bool passSucceded = false;
    startPassiveListener(clientFtpSession, passSucceded);

    //If successful, create a passive success response calling 'createPassiveSuccessResponse()'
    //function and send the passive success response to the client on the control connection 
    //represented by 'controlSocket' of 'clientFtpSession'.
    char* message = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*(sizeof(char)));
    createPassiveSuccessResponse(message, clientFtpSession.dataListenerSocket);

    //Use 'sendToClient()' function to send the passive success response to the client.
    sendToClient(clientFtpSession.controlSocket, message, strlen(message));

    //Wait for DATA_CONNECTION_TIME_OUT_SEC and DATA_CONNECTION_TIME_OUT_USEC time to get a data connection request 
    //from the client on data listener socket by calling isListenerSocketReady() function.
    bool isError = false;
    bool isTimedout = false;
    bool isListenerResult = isListenerSocketReady(clientFtpSession.dataListenerSocket, DATA_CONNECTION_TIME_OUT_SEC, DATA_CONNECTION_TIME_OUT_USEC, isError, isTimedout);
    if (isListenerResult == true){

        //If there is a request, accept it and opens a data connection with the client by calling 
        //'acceptClientConnetion() function with clientFtpSession.dataListenerSocket and clientFtpSession.dataSocket.
        char* IPstr;
        int Portint = -1;
        acceptClientConnection(clientFtpSession.dataListenerSocket, clientFtpSession.dataSocket, IPstr, Portint);
        if (Portint != -1){

            //If the data connection is opened successfully, send DATA_CONNECTION_SUCCESS_RESPONSE to the by calling sendToClient() function.
            sendToClient(clientFtpSession.controlSocket, DATA_CONNECTION_SUCCESS_RESPONSE, strlen(DATA_CONNECTION_SUCCESS_RESPONSE));
        } else {

            //Send DATA_OPEN_CONNECTION_ERROR_RESPONSE to the client, otherwise.
            sendToClient(clientFtpSession.controlSocket, DATA_OPEN_CONNECTION_ERROR_RESPONSE, strlen(DATA_LOCAL_ERROR_RESPONSE));
        }
    }

    //If timed out happens while waiting send PASSIVE_ERROR_TIMEOUT_RESPONSE to the client.
    if (isTimedout == true){
        sendToClient(clientFtpSession.controlSocket, PASSIVE_ERROR_TIMEOUT_RESPONSE, strlen(PASSIVE_ERROR_TIMEOUT_RESPONSE));
    }

    //If error occurs while waiting send PASSIVE_ERROR_RESPONSE to the client.
    if (isError == true){
        sendToClient(clientFtpSession.controlSocket, PASSIVE_ERROR_RESPONSE, strlen(PASSIVE_ERROR_RESPONSE));
    }

    // Free the message
    free(message);

    //Close the connection listener by calling 'stopPassiveListener() function'.
    stopPassiveListener(clientFtpSession);

    // End
    return;
}