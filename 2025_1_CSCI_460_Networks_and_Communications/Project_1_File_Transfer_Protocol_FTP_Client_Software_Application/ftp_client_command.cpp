/**
 * @file ftp_client_command.cpp
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
 *          Copyright (C) 2025 Patrick McGrath
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
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdbool.h>
#include <vector>
#include <bits/stdc++.h>
#include <regex>
#include "ftp_client_command.h"
#include "ftp_client_ui.h"
#include "ftp_client_connection.h"
#include "ftp_client_session.h"
#include "ftp_server_response.h"




/**
* @brief Interprets and handles user commands
*
* @param command,   The user's command to be interpretted.
* @param clientFtpSession, The data structure for the client's FTP sockets and other variables.
* @param serverResponse, Data structure for logging server responses
*/
void interpretAndHandleUserCommand(string command, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // Tokenize command, delineated by space, stored in /tokens/
    vector <string> tokens;
    string copyCommand = command;
    string temp;
    stringstream check1(copyCommand);
    while (getline(check1, temp, ' ')){
        tokens.push_back(temp);
    }
    int tokenCount = (int)tokens.size();

    // Check if no command given
    if (tokenCount == 0){
        return;
    }

    // Compare first token to each acceptable user command.
    // On a match, handle appropriately
    if ((tokens[0] == "Help") || (tokens[0] == "help")){
        // Help command
        handleCommandHelp();
    } 
    else if ((tokens[0] == "User") || (tokens[0] == "user")){
        // User command
        // Check if at least 2 tokens
        if (tokenCount >= 2){
            handleCommandUser(tokens[1], clientFtpSession, serverResponse);
        }
    }
    else if ((tokens[0] == "Pass") || (tokens[0] == "pass")){
        // Pass command
        // Check if at least 2 tokens
        if (tokenCount >= 2){
            handleCommandPassword(tokens[1], clientFtpSession, serverResponse);
        }
    }
    else if ((tokens[0] == "Dir") || (tokens[0] == "dir")){
        // Dir command
        handleCommandDirectory(clientFtpSession, serverResponse);
    }
    else if ((tokens[0] == "Cwd") || (tokens[0] == "cwd")){
        // Cwd command
        // Check if at least 2 tokens
        if (tokenCount >= 2){
            handleCommandChangeDirectory(tokens[1], clientFtpSession, serverResponse);
        }
    }
    else if ((tokens[0] == "Cdup") || (tokens[0] == "cdup")){
        // Cdup command
        handleCommandChangeDirectoryUp(clientFtpSession, serverResponse);
    }
    else if ((tokens[0] == "Get") || (tokens[0] == "get")){
        // Get command
        // Check if at least 2 tokens
        if (tokenCount >= 2){
            handleCommandGetFile(tokens[1], clientFtpSession, serverResponse);
        }
    }
    else if ((tokens[0] == "Quit") || (tokens[0] == "quit")){
        // Quit command
        handleCommandQuit(clientFtpSession, serverResponse);
    }
    else if ((tokens[0] == "Pwd") || (tokens[0] == "pwd")){
        // Pwd command
        handleCommandPrintDirectory(clientFtpSession, serverResponse);
    }
    else {
        // Incorrect command
        // Do nothing
    }
    // End
    return;
}




/**
* @brief Handles user command 'help'. Will display a formatted list of commands the user may use.
*
* @param none
*/
void handleCommandHelp(){

    // First line
    std::cout << "Usage: csci460Ftp>> [ ";
    std::cout << FTP_CLIENT_USER_COMMAND_HELP << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_USER << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_PASSWORD << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_DIRECTORY << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_GET << " | ";
    std::cout << FTP_CLIENT_USER_COMMAND_QUIT << " ]";
    std::cout << std::endl;

    // Subsequent lines
    std::cout << "         " << FTP_CLIENT_USER_COMMAND_HELP;
    std::cout << "                    Gives the list of FTP commands available and how to use them.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_USER;
    std::cout << "    <username>      Sumbits the <username> to FTP server for authentication.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_PASSWORD;
    std::cout << "    <password>      Sumbits the <password> to FTP server for authentication.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY;
    std::cout << "                     Requests FTP server to print current directory.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_DIRECTORY;
    std::cout << "                     Requests FTP server to list the entries of the current directory.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY;
    std::cout << "     <dirname>       Requests FTP server to change current working directory.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP;
    std::cout << "                    Requests FTP server to change current directory to parent directory.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_GET;
    std::cout << "     <filename>      Requests FTP server to send the file with <filename>.";
    std::cout << std::endl;

    std::cout << "         " << FTP_CLIENT_USER_COMMAND_QUIT;
    std::cout << "                    Requests to end FTP session and quit.";
    std::cout << std::endl;

    // End
    return;

}




/**
* @brief Checks if the user is logged in.
*
* @param clientFtpSession, The data structure of the user who's status is being checked. 
*/
bool isLoggedIn(ClientFtpSession clientFtpSession){
    // Check if user is not logged in
    if (clientFtpSession.isLoggedIn == false){
        // Display error and return false
        std::cout << "Error:    User is not logged in" << std::endl;
        return false;
    }
    // User is logged in, return true
    return true;
}




/**
* @brief Sends ftp request to server and receives then returns the server's response. Used by other functions.
*
* @param ftpRequest, The ftp request being sent
* @param clientFtpSession, The data structure of the user sending the request, contains the control socket. 
*/
char* handleFtpRequest(string ftpRequest, ClientFtpSession& clientFtpSession){

    // Check validity of Control Socket
    if (clientFtpSession.controlSocket >= 0){

        // Send ftpRequest to server
        int sendReturn = sendToServer(clientFtpSession.controlSocket, ftpRequest.c_str(), ftpRequest.length());

        // Check if send is successful
        if (sendReturn != -1){

            // Allocate memory to receive response from server
            char* buffer;
            size_t buffersize = FTP_RESPONSE_MAX_LENGTH;
            buffer = (char*)malloc(buffersize * sizeof(char));
            if (buffer == NULL){
                std::cout << "Error: Allocation error." << std::endl;
                return nullptr;
            }

            // Receive server response
            int recReturn = receiveFromServer(clientFtpSession.controlSocket, buffer, FTP_RESPONSE_MAX_LENGTH - 1);

            // Check if return of response is successful
            if (recReturn != -1){

                // Null-terminate the return message and return it.
                buffer[recReturn] = '\0';
                return buffer;

            } else {
                // Receive message failed
                std::cout << "Error: Receive message from server to client failed." << std::endl;
            }
        } else {
            // Send message failed
            std::cout << "Error: Send message from client to server failed." << std::endl;
        }
    } else {
        // Invalid control socket
        std::cout << "Error: Invalid control socket." << std::endl;
    }

    // Socket not valid
    return nullptr;
}




/**
* @brief Handles user command "quit". Will check if user is logged in.
*        If they are, sends "QUIT" to server, receives response and logs it. If logged
*        message is a quit response, the session is stopped. If the user is not logged in
*        the session is stopped.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandQuit(ClientFtpSession &clientFtpSession, ServerResponse &serverResponse){
    
    // Check if user is logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        // Send message "QUIT" to server and receive response
        char *buffer;
        std::string ftpMessage = "QUIT";
        buffer = handleFtpRequest(ftpMessage, clientFtpSession);

        // Check if response was successful
        if (buffer != nullptr){
            // Log message
            serverResponse.responses[serverResponse.count] = (std::string)buffer;
            serverResponse.count++;

            // Check if response was correct
            if (((std::string)buffer) == QUIT_RESPONSE){
                // Server response was correct
                // Stop session
                stopClientFTPSession(clientFtpSession);
                return;
            } else {
                // Server response was not correct
                return;
            }
        }
    } else {
        // User is not logged in
        // Stop session
        stopClientFTPSession(clientFtpSession);
        return;
    }
    // End
    return;
}



/**
* @brief Handles user command "user <usernname>". Sends command to server, and logs response.
*        If the response was username ok response, sets user status to authenticated.
*        If the response was invalid username, sets user status to unathenticated and stops session.
*        If any other response, the session is stopped.
*
* @param username, The username used in the command.
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandUser(string username, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // Send message "USER <username>" to server and receive response
    char* buffer;
    std::string ftpMessage = "USER " + username;
    buffer = handleFtpRequest(ftpMessage, clientFtpSession);

    // Check if response was successful
    if (buffer != nullptr){
        // Log message
        serverResponse.responses[serverResponse.count] = (std::string)buffer;
        serverResponse.count++;
    }

    // Check if response was USERNAME_OK_RESPONSE
    if (((std::string)buffer) == USERNAME_OK_RESPONSE){
        // Set user's authentication status to true and return
        clientFtpSession.isUserAuthenticated = true;
        return;
    }

    // Check if response was INVALID_USERNAME_RESPONSE
    if (((std::string)buffer) == INVALID_USERNAME_RESPONSE){
        // Set user's authentication status to false, stop session and return
        clientFtpSession.isUserAuthenticated = false;
        stopClientFTPSession(clientFtpSession);
        return;
    }

    // Response is something else, close sessions and return
    stopClientFTPSession(clientFtpSession);
    return;
}



/**
* @brief Handles user command "pass <password>". Checks if user is authenticated. If they are, 
*        sends command to server, and logs response.
*        If the response was login response, sets user status to logged in.
*        If the response was not logged in response, sets user status to not logged in and stops session.
*        If user is not authenticated, the session is stopped.
*
* @param password, The password used in the command.
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandPassword(string password, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // Check if user is authenticated
    bool authReturn = clientFtpSession.isUserAuthenticated;
    if (authReturn == true){

        // User is authenticated
        // Send message "PASS <password>" to server and receive response
        char* buffer;
        std::string ftpMessage = "PASS " + password;
        buffer = handleFtpRequest(ftpMessage, clientFtpSession);

        // Check if response was succesful
        if (buffer != nullptr){
            // Log response
            serverResponse.responses[serverResponse.count] = (std::string)buffer;
            serverResponse.count++;
        
            // Check if response was LOGIN_RESPONSE
            if (((std::string)buffer) == LOGIN_RESPONSE){
                // Set user's logged in status to true and return
                clientFtpSession.isLoggedIn = true;
                return;
            }

            // Check if response was NOT_LOGGED_IN_RESPONSE
            if (((std::string)buffer) == NOT_LOGGED_IN_RESPONSE){
                // Set user's logged in status to false, close session and return
                clientFtpSession.isLoggedIn = false;
                stopClientFTPSession(clientFtpSession);
                return;
            }
        }
    }

    // User is not authenticated, stop session and return
    stopClientFTPSession(clientFtpSession);
    return;
}







/**
* @brief Handles user command "pwd". Checks if user is logged in. If they are, sends command to server, and logs response.
*        If the user is not logged in, the session is stopped.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandPrintDirectory(ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){
    // check if user logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        // Send message "PWD" to server and receive response
        char* buffer;
        std::string ftpMessage = "PWD";
        buffer = handleFtpRequest(ftpMessage, clientFtpSession);

        // Check if response was successful
        if (buffer != nullptr){
            // Log message
            serverResponse.responses[serverResponse.count] = (std::string)buffer;
            serverResponse.count++;
        }
    } else {
        // User is not logged in
        // Stop client's ftp session
        stopClientFTPSession(clientFtpSession);
    }
    // End
    return;
}




/**
* @brief Handles user command "cwd <path>". Checks if user is logged in. If they are, 
*        sends command to server, and logs response. If they are not logged in, the session is stopped.
*
* @param path, The path used in the command.
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandChangeDirectory(string path, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // check if user logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        // Send message "CWD" to server and receive response
        char* buffer;
        std::string ftpMessage = "CWD " + path;
        buffer = handleFtpRequest(ftpMessage, clientFtpSession);

        // Check if response was successful
        if (buffer != nullptr){

            // Log message
            serverResponse.responses[serverResponse.count] = (std::string)buffer;
            serverResponse.count++;
        }
    } else {

        // User is not logged in
        // Stop client's ftp session
        stopClientFTPSession(clientFtpSession);
    }

    // End
    return;
}



/**
* @brief Handles user command "cdup". Checks if user is logged in. If they are, 
*        sends command to server, and logs response. If they are not logged in, the session is stopped.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandChangeDirectoryUp(ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){
    // check if user logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        // Send message "CDUP" to server and receive response
        char* buffer;
        std::string ftpMessage = "CDUP";
        buffer = handleFtpRequest(ftpMessage, clientFtpSession);

        // Check if response was successful
        if (buffer != nullptr){
            // Log message
            serverResponse.responses[serverResponse.count] = (std::string)buffer;
            serverResponse.count++;
        }
    } else {
        // User is not logged in
        // Stop client's ftp session
        stopClientFTPSession(clientFtpSession);
    }
    // End
    return;
}



/**
* @brief Handles user command "dir". Checks if user is logged in. If they are, 
*        opens a passive connection with the server on the user's data socket.
*        If the connection is successful, the directory list is received and logged.
*        If the user is not logged in, the session is stopped.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandDirectory(ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // check if user logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        handlePassive(clientFtpSession, serverResponse);

        if (clientFtpSession.dataSocket != -1){
            handleNLIST(clientFtpSession, serverResponse);
        }
    } else {
        // User is not logged in
        // Stop client's ftp session
        stopClientFTPSession(clientFtpSession);
    }
    // End
    return;
}

 

/**
* @brief Handles user command "get <filename>". Checks if user is logged in. If they are, gets the size of <filename>
*        from the server. If size retrieval was succesful, passive connection on user's data socket is opened.
*        If passive connection successful, file is retrieved from server.
*        If they are not logged in, the session is stopped.
*
* @param filename, The filename used in the command.
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleCommandGetFile(string filename, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){

    // check if user logged in
    bool loggedReturn = isLoggedIn(clientFtpSession);
    if (loggedReturn == true){

        // User is logged in
        int size = -1;
        handleSize(filename, clientFtpSession, serverResponse, size);
        
        if (size > 0){
            handlePassive(clientFtpSession, serverResponse);
            if(clientFtpSession.dataSocket != -1){
                handleRETR(filename, size, clientFtpSession, serverResponse);
            }
        }
    } else {
        // User is not logged in
        // Stop client's ftp session
        stopClientFTPSession(clientFtpSession);
    }

    // End
    return;
}

 

/**
* @brief Handles FTP request "PASV". Sends request to server, and logs response. 
*        If the response was passive error, session is stopped. 
*        If the response was passive success, connection over user's data socket is made,
*        using IP and port in response. If data connection successful, receive response from server over control socket.
*        If they are not logged in, or for any other error, the session is stopped.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handlePassive(ClientFtpSession& clientFtpSession, ServerResponse& serverResponse ){
    // Send message "PASV" to server and receive response
    char* buffer;
    std::string ftpMessage = "PASV";
    buffer = handleFtpRequest(ftpMessage, clientFtpSession);

    // Check if response was succesful
    if (buffer != nullptr){
        // Log response
        serverResponse.responses[serverResponse.count] = (std::string)buffer;
        serverResponse.count++;

        // Check if response was PASSIVE_ERROR_RESPONSE
        if (((std::string)buffer) == PASSIVE_ERROR_RESPONSE){

            // Stop client's ftp session
            stopClientFTPSession(clientFtpSession);            
            return;
        }

        // Check if response was PASSIVE_SUCCESS_RESPONSE using regex
        std::regex pattern(R"(227 Entering Passive Mode \((\d+,\d+,\d+,\d+),(\d+),(\d+)\)\.\n)");
        if (std::regex_match(buffer, pattern)){

            // Get host IP and port from response
            char* HostResponse = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*sizeof(char));
            int HostIPint;
            getHostIPAndPortFromPassiveSuccessResponse(buffer, HostResponse, HostIPint);


            // Connect to server's data port
            connectToServer(clientFtpSession.dataSocket, HostResponse, HostIPint);


            // Check Socket to see if connection was succesfful
            if (clientFtpSession.dataSocket != -1){

                // Get response from server
                char* passResponse = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*sizeof(char));
                if (passResponse == NULL){
                    stopClientFTPSession(clientFtpSession);
                    return;
                }
                int passReturn = receiveFromServer(clientFtpSession.controlSocket, passResponse, FTP_RESPONSE_MAX_LENGTH-1);

                // Log message
                if (passReturn != -1){
                    serverResponse.responses[serverResponse.count] = (std::string)passResponse;
                    serverResponse.count++;
                } else {
                    // Message return error
                    stopClientFTPSession(clientFtpSession);
                }
            } else {
                // Data connection error
                stopClientFTPSession(clientFtpSession);
            }
            // Free temporary memory
            free(HostResponse);
        } else {
            // Passive success not received
            stopClientFTPSession(clientFtpSession);
        }
    } else {
        // Response error
        stopClientFTPSession(clientFtpSession);
    }
    // End
    return;
}



/**
* @brief Handles FTP request "NLST". Sends request to server, and logs response. 
*        If the response was NLST connection close, response is received over user's data socket and logged. 
*        Data connection is closed.
*
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleNLIST(ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){
    // Send message "NLST" to server and receive response
    char* buffer;
    std::string ftpMessage = "NLST";
    buffer = handleFtpRequest(ftpMessage, clientFtpSession);

    // Check if response was succesful
    if (buffer != nullptr){
        // Log response
        serverResponse.responses[serverResponse.count] = (std::string)buffer;
        serverResponse.count++;

        // Check if response was NLST_CONNECTION_CLOSE_RESPONSE
        if (((std::string)buffer) == NLST_CONNECTION_CLOSE_RESPONSE){
            //Receive from server
            char* passResponse = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*sizeof(char));
            if (passResponse == NULL){
                stopClientFTPSession(clientFtpSession);
                return;
            }
            int result = receiveFromServer(clientFtpSession.dataSocket, passResponse, FTP_RESPONSE_MAX_LENGTH-1);
            if (result != -1){
                // Log message
                serverResponse.responses[serverResponse.count] = (std::string)passResponse;
                serverResponse.count++;
            }
                //disconnectFromServer(clientFtpSession.dataSocket);
        }
    }
    disconnectFromServer(clientFtpSession.dataSocket);
    return;
}



/**
* @brief Handles FTP request "SIZE + <filename>". Sends request to server, and logs response. 
*        If the response was file size response, the file size is extracted from the response and returned.
*
* @param filename, The filename used in the request
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
* @param size, The by reference file size
*/
void handleSize(string filename, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse, int& size){
    // Send message "SIZE" to server and receive response
    char* buffer;
    std::string ftpMessage = "SIZE " + filename;
    buffer = handleFtpRequest(ftpMessage, clientFtpSession);

    // Check if response was succesful
    if (buffer != nullptr){
        // Log response
        serverResponse.responses[serverResponse.count] = (std::string)buffer;
        serverResponse.count++;

        // Check if response was FILE_SIZE_RESPONSE "213 File size (%d).\n"
        std::regex pattern(R"(213 File size \((\d+)\)\.\n)");
        if (std::regex_match(buffer, pattern)){
            // Get filesize
            // filesize is from buffer[15] to ')'
            string filesizestr;
            int index = 15;
            char curr = buffer[index];
            while (curr != ')'){
                filesizestr += curr;
                index++;
                curr = buffer[index];
            }
            size = stoi(filesizestr);
        }
    }
    return;
}



/**
* @brief Handles FTP request "RETR + <filename>". Sends request to server, and logs response. 
*        If the response was RETR connection close, a new file is opened in write-only using the filename.
*        The file is received in chunks of size, DATA_SOCKET_RECEIVE_BUFFER_SIZE until the file is received. 
*        The file and data connection are closed.
*
* @param filename, The filename used in the request.
* @param size, The size of the file being rerieved. 
* @param clientFtpSession, The data structure of the user sending the request
* @param serverResponse, Log for server responses
*/
void handleRETR(string filename, const int size, ClientFtpSession& clientFtpSession, ServerResponse& serverResponse){
    // Send message "RETR" to server and receive response
    char* buffer;
    std::string ftpMessage = "RETR " + filename;
    buffer = handleFtpRequest(ftpMessage, clientFtpSession);


    // Check if response was succesful
    if (buffer != nullptr){
        // Log response
        serverResponse.responses[serverResponse.count] = (std::string)buffer;
        serverResponse.count++;

        // Check if response was RETR_CONNECTION_CLOSE_RESPONSE  "226 Closing data connection.\n"
        if (strcmp(buffer, RETR_CONNECTION_CLOSE_RESPONSE) == 0){
        //if (buffer == RETR_CONNECTION_CLOSE_RESPONSE){
            //Open new file in write only
            FILE* file = fopen(filename.c_str(), FILE_OPEN_MODE);

            if (!file) {
                return;
            }
            // Receive from server
            char* buffer1 = (char*)malloc(DATA_SOCKET_RECEIVE_BUFFER_SIZE * sizeof(char));
            int bytecount = receiveFromServer(clientFtpSession.dataSocket, buffer1, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
            int remaining = size;

            fwrite(buffer1, sizeof(char), bytecount, file); // Write to file
            remaining = remaining - bytecount;
            while (remaining > 0){
                bytecount = receiveFromServer(clientFtpSession.dataSocket, buffer1, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
                fwrite(buffer1, sizeof(char), bytecount, file); // Write to file
                remaining = remaining - bytecount;
            }
            fclose(file); // Close the file
            disconnectFromServer(clientFtpSession.dataSocket);
        }
    }
    return;
}



/**
* @brief Extracts IP and port number from server response.
*
* @param response, The response that contains the information.
* @param hostIP, The character array that the extracted IP will be placed in.
* @param hostPort, The integer that will hold the extracted port number. 
*/
void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIP, int& hostPort){
    // Tokenize response, delineated by space, stored in /tokens/
    vector <string> tokens;
    string copyresponse = (std::string)response;
    string temp;
    stringstream check1(copyresponse);
    while (getline(check1, temp, ' ')){
        tokens.push_back(temp);
    }
    int tokenCount = (int)tokens.size();

    // Check if correct number of command given, should be 5
    if (tokenCount != 5){
        return;
    }

    // Temp variables for extracting relevant data
    string IPReturn;        // temp string for IP
    string PortReturnA;     // temp string A for port
    string PortReturnB;     // temp string B for port

    // Populate IPReturn and PortReturn(A+B) from 4th token
    int index = 1;                  // Index for traversing token disregard '('
    char curr = tokens[4][index];   // Current character

    // Populate IPReturn
    // IP has 4 sections, the first 3 end with '.'
    for (int ipcount = 0; ipcount < 3; ipcount++){ 
        // While between deliniators
        while ((curr != ',') && (curr != '.')){
            IPReturn += curr;           // Add current character to IPReturn
            index++;                    // Increment index
            curr = tokens[4][index];    // Update current character
        } 
        // Upon delinator, add '.' to IPReturn
        IPReturn +=  '.';
        index++;
        curr = tokens[4][index];
    }

    // 4th sction
    // While between deliniators
    while ((curr != ',') && (curr != '.')){
        IPReturn += curr;
        index++;
        curr = tokens[4][index];
    } 

    // PortReturnA
    index++;
    curr = tokens[4][index];
    // While between deliniators
    while ((curr != ',') && (curr != '.')){
        PortReturnA += curr;
        index++;
        curr = tokens[4][index];
    } 

    // PortReturnB
    index++;
    curr = tokens[4][index];
    // While between deliniators
    while ((curr != ',') && (curr != '.') && (curr != ')')){
        PortReturnB += curr;
        index++;
        curr = tokens[4][index];
    }
    
    // Convert IPReturn to char and convert PortReturn A+B with algoithm
    //IPRETURN
    strncpy(hostIP, IPReturn.c_str(), IPReturn.size()); // Copy IPReturn to hostIP
    hostIP[IPReturn.size()] = '\0';                     // Null terminate hostIP

    //PORTRETURN
    int PortA = stoi(PortReturnA);  // Convert to integers
    int PortB = stoi(PortReturnB);
    int PortC = (256*PortA)+PortB;  // Port Number = (PortA * 256) + PortB
    hostPort = PortC;

    return;
}