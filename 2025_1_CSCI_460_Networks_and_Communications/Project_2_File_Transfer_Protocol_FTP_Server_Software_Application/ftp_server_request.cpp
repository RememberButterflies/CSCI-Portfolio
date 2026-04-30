/**
 * @file    ftp_server_request.cpp
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
#include <cstring>
#include <vector>
#include <unistd.h>
#include "ftp_server_request.h"
#include "ftp_server_net_util.h"
#include "ftp_server_session.h"
#include "ftp_server_connection.h"
#include "ftp_server_passive.h"
#include "ftp_server_nlist.h"
#include "ftp_server_retrieve.h"
#include "ftp_server_response.h"
#include "ftp_server_string_util.h"


#include <iostream>

// Helper function declarations
bool startsWith(const char* str, const char* prefix);       // Check if str starts with prefix
bool contains(const char* str, const char* substr);         // Check if str contains substr



/**
 * @brief Check if a string starts with a given prefix.
 * 
 * @param str The string to check.
 * @param prefix The prefix to check for.
 * 
 * @return true if the string starts with the prefix, false otherwise.
 */
bool startsWith(const char* str, const char* prefix){
    // Check for parameters
    if ((str == nullptr) || (prefix == nullptr)){
        return false;
    }

    // Check if str is shorter than prefix
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (str_length < prefix_length){
        return false;
    }

    // If both not null and prefix is "", then true by default
    if (strcmp(prefix, "") == 0){
        return true;
    }

    // Check the first prefix length of str, returning false on mismatch
    for (size_t i=0; i<prefix_length; i++){
        if (str[i] != prefix[i]){
            return false;
        }
    }

    // All is good
    return true;
}







/**
 * @brief Check if a string contains a given substring.
 * 
 * @param str The string to check.
 * @param substr The substring to check for.
 * 
 * @return true if the string contains the substring, false otherwise.
 */
bool contains(const char* str, const char* substr){
    // Check for parameters
    if ((str == nullptr) || (substr == nullptr)){
        return false;
    }

    // Check if str is shorter than substr
    size_t str_length = strlen(str);
    size_t substr_length = strlen(substr);
    if (str_length < substr_length){
        return false;
    }

    // If both not null and substr is "", then true by default
    if (strcmp(substr, "") == 0){
        return true;
    }

    // Check from beginning of str to see if each chr is the start for substr
    for (size_t i=0; i<(str_length-substr_length+1); i++){
        // if match on first char of substr, check for rest of it
        if (strncmp(&str[i], substr, substr_length) == 0) {
            return true;
        }
    }    
    // Return result
    return false;
}





/**
 * @brief Parse an FTP request string into its name and argument.
 * 
 * @param ftpRequest The FTP request string to parse.
 * @param requestName Pointer to store the request name.
 * @param requestArgument Pointer to store the request argument.
 */
void parseFtpRequest(const char* ftpRequest, char* requestName, char* requestArgument){
    // Check parameters
    if (ftpRequest == nullptr){
        return;
    }

    // Create local copy
    char* ftpRequestCopy = (char*)malloc(FTP_REQUEST_BUFFER_SIZE*(sizeof(char)));
    if (ftpRequestCopy == nullptr){
        return; // Failure
    }
    std::strcpy(ftpRequestCopy, ftpRequest);

    //Break the 'ftpRequest' string into its parts, request name and request argument, by calling
    //strtok() library function.
    std::vector<char*> TOKENS;                              // Array for tokens
    char* token = std::strtok((char*)ftpRequestCopy, " ");  // First token
    while (token != nullptr){                               // get the rest of tokens
        TOKENS.push_back(token);
        token = std::strtok(nullptr, FTP_REQUEST_DELIMITER);
    }
    int tokenCount = (int)TOKENS.size();                    // number of tokens
    if (tokenCount <= 0){
        return;                 // nothing passed
    }
    //Copy the request name part to the memory pointed by 'requestName' and the request argument part 
    //to the memory pointed by 'requestArgument'. Call strcpy() to copy both name and argument.
    //Caller of this function will retrieve the request parts through these pointers.
    std::strcpy(requestName, TOKENS[0]);                    // copy request
    if (tokenCount > 1){
        std::strcpy(requestArgument, TOKENS[1]);            // copy argument, if there is one
    }

    // Free memory
    free(ftpRequestCopy);

    // End
    return;
}








/**
 * @brief Interpret an FTP request and handle it accordingly.
 * 
 * @param ftpRequest The FTP request string to interpret.
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void interpretFtpRequest(const char* ftpRequest, ClientFtpSession& clientFtpSession){
    // Check parameters
    if (ftpRequest == nullptr){
        return;
    }

    // Memory for parsing request and arguments
    char* requestName = (char*)malloc((FTP_REQUEST_CODE_CHARACTER_COUNT+1)*(sizeof(char)));
    if (requestName == nullptr){
        return; // Failure
    }
    char* requestArgument = (char*)malloc((FTP_REQUEST_ARG_MAX_CHARACTER_COUNT+1)*(sizeof(char)));
    if (requestArgument == nullptr){
        return; // Failure
    }

    //Separate the command and its argument by calling 'parseFtpRequest()' function.
    parseFtpRequest(ftpRequest, requestName, requestArgument);

    //Determine, which valid FTP request has been sent, only the requests defined in 
    //this header file are valid for this FTP server.
    //Call appropriate 'handleFtpRequestXXXX()' function to handle a valid FTP request.
    //Call 'handleFtpRequestUnSupported()' if an invalid FTP request has been received.
    if ((strcmp(requestName, FTP_REQUEST_USER) == 0) && (requestArgument[0] != '\0')){
        handleFtpRequestUSER(requestArgument, clientFtpSession);
    } else if ((strcmp(requestName, FTP_REQUEST_PASSWORD) == 0) && (requestArgument[0] != '\0')){
        handleFtpRequestPASS(requestArgument, clientFtpSession);
    } else if (strcmp(requestName, FTP_REQUEST_PWD) == 0){
        handleFtpRequestPWD(clientFtpSession);
    } else if ((strcmp(requestName, FTP_REQUEST_CWD) == 0) && (requestArgument[0] != '\0')){
        handleFtpRequestCWD(requestArgument, clientFtpSession);
    } else if (strcmp(requestName, FTP_REQUEST_CDUP) == 0){
        handleFtpRequestCDUP(clientFtpSession);
    } else if (strcmp(requestName, FTP_REQUEST_PASV) == 0){
        handleFtpRequestPASV(clientFtpSession);
    } else if (strcmp(requestName, FTP_REQUEST_NLST) == 0){
        handleFtpRequestNLST(clientFtpSession);
    } else if ((strcmp(requestName, FTP_REQUEST_SIZE) == 0) && (requestArgument[0] != '\0')){
        handleFtpRequestSIZE(requestArgument, clientFtpSession);
    } else if ((strcmp(requestName, FTP_REQUEST_RETR) == 0) && (requestArgument[0] != '\0')){
        handleFtpRequestRETR(requestArgument, clientFtpSession);
    } else if (strcmp(requestName, FTP_REQUEST_QUIT) == 0){
        handleFtpRequestQUIT(clientFtpSession);
    } else {
        // Unknown
        handleFtpRequestUnSupported(clientFtpSession);
    }

    // Free allocated memory
    free(requestName);
    free(requestArgument);

    // End
    return;
}









/**
 * @brief Handle unsupported FTP requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestUnSupported(ClientFtpSession& clientFtpSession){

    //Send UNSUPPORTED_COMMAND_RESPONSE to the client by calling sendToClient() function
    //on clientFtpSession.controlSocket.
    sendToClient(clientFtpSession.controlSocket, UNSUPPORTED_COMMAND_RESPONSE, strlen(UNSUPPORTED_COMMAND_RESPONSE));

    // End
    return;
}










/**
 * @brief Handle FTP QUIT requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestQUIT(ClientFtpSession& clientFtpSession){

    //Send QUIT_RESPONSE to the client by calling sendToClient() function
    //on clientFtpSession.controlSocket.
    sendToClient(clientFtpSession.controlSocket, QUIT_RESPONSE, strlen(QUIT_RESPONSE));

    //Stop client ftp session by calling stopClientFTPSession() function.
    stopClientFTPSession(clientFtpSession);
    
    return;
}









/**
 * @brief Handle the case when the client is not logged in.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleNotLoggedIn(ClientFtpSession& clientFtpSession){

    //Send NOT_LOGGED_IN_RESPONSE to the client by calling sendToClient() function
    //on clientFtpSession.controlSocket.
    sendToClient(clientFtpSession.controlSocket, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));

    //Stop client ftp session by calling stopClientFTPSession() function.
    stopClientFTPSession(clientFtpSession);
    
    return;
}









/**
 * @brief Handle FTP USER requests.
 * 
 * @param username The username to check, hardcoded for this server.
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestUSER(const char* username, ClientFtpSession& clientFtpSession){

    // Compare 'username' with the DEFAULT_USERNAME.
    if (strcmp(username, DEFAULT_USERNAME) == 0){
        // set 'true' to 'clientFtpSession.isUserAuthenticated'
        clientFtpSession.isUserAuthenticated = true;
        //send USERNAME_OK_RESPONSE to the client by calling sendToClient() with clientFtpSession.controlSocket.
        sendToClient(clientFtpSession.controlSocket, USERNAME_OK_RESPONSE, strlen(USERNAME_OK_RESPONSE));
    } else {
        // set 'false' to 'clientFtpSession.isUserAuthenticated'
        clientFtpSession.isUserAuthenticated = false;
        // send INVALID_USERNAME_RESPONSE to the client
        sendToClient(clientFtpSession.controlSocket, INVALID_USERNAME_RESPONSE, strlen(INVALID_USERNAME_RESPONSE));
        // stop client's ftp session by calling stopClientFTPSession() function.
        stopClientFTPSession(clientFtpSession);
    }
    // End
    return;
}











/**
 * @brief Handle FTP PASS requests.
 * 
 * @param password The password to check, hardcoded for this server.
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestPASS(const char* password, ClientFtpSession& clientFtpSession){

    // Check if the user is authenticated and the password matches the default password.
    if ((clientFtpSession.isUserAuthenticated == true) && (strcmp(password, DEFAULT_PASSWORD) == 0)){
        // set clientFtpSession.isLoggedIn to true and send LOGIN_RESPONSE through
        //clientFtpSession.controlSocket by calling sendToClient() function.
        clientFtpSession.isLoggedIn = true;
        sendToClient(clientFtpSession.controlSocket, LOGIN_RESPONSE, strlen(LOGIN_RESPONSE));
    } else {
        // set clientFtpSession.isLoggedIn to false and call handleNotLoggedIn() to handle this unusual situation.
        clientFtpSession.isLoggedIn = false;
        handleNotLoggedIn(clientFtpSession);
    }

    // End
    return;
}













/**
 * @brief Handle FTP PWD requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestPWD(ClientFtpSession& clientFtpSession){

    // if clientFtpSession.isLoggedIn is false
    if (clientFtpSession.isLoggedIn == false){
        // call handleNotLoggedIn() to handle this unusual situation.
        handleNotLoggedIn(clientFtpSession);
    } else {
        // determines the current working directory by calling getcwd()
        char* getcwdResult = get_current_dir_name();
        // send it to the client by calling 'sendToClient()' function and free the memory
        sendToClient(clientFtpSession.controlSocket, getcwdResult, strlen(getcwdResult));
        free(getcwdResult);
    }

    // End
    return;
}

















/**
 * @brief Check if a path is valid.
 *          A path is valid if any of the following is true:
 *          It starts with ".", "*", "/", "./" or "../"
 *          It contains "*", "/.", "/.." or "./"
 * 
 * @param path The path to check.
 * 
 * @return 1 if the path is valid, 0 otherwise.
 */
int isValidPath(const char* path){

    // If the validity integer is 0 at the end, the path is valid
    // Redunant checks are removed
    int isInvalid = (int)startsWith(path, ".");
    if (isInvalid == 0){    
        isInvalid += (int)startsWith(path, "/");
    }
    if (isInvalid == 0){    
        isInvalid += (int)contains(path, "*");
    }
    if (isInvalid == 0){    
        isInvalid += (int)contains(path, "/.");
    }
    if (isInvalid == 0){    
        isInvalid += (int)contains(path, "./");
    }

    // Path is valid
    if (isInvalid == 0){
        return 1;
    }

    // Path is invalid
    return 0;
}















/**
 * @brief Handle FTP CWD requests.
 * 
 * @param directory The directory to change to.
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestCWD(const char* directory, ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() 
    //to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
        return;
    } else {

        //Determine whether 'directory' is valid or not by calling isValidPath() function.
        int validResult = isValidPath(directory);
        if (validResult == 0){
            //If the 'directory' is not a valid directory, send INVALID_PATH_RESPONSE to the client
            //by calling sendToClient() function and return from this function.
            sendToClient(clientFtpSession.controlSocket, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
            return;
        } else {
            //Change current working directory to 'directory' by calling chdir() system call.
            int chdirResult = chdir(directory);
            if (chdirResult == 0){
                //If change is successful, send CHANGE_DIRECTORY_RESPONSE to the client by calling 
                //sendToClient() function.
                sendToClient(clientFtpSession.controlSocket, CHANGE_DIRECTORY_RESPONSE, strlen(CHANGE_DIRECTORY_RESPONSE));
            } else {
                //Otherwise, send CWD_FAIL_RESPONSE to the client by calling sendToClient() function.
                sendToClient(clientFtpSession.controlSocket, CWD_FAIL_RESPONSE, strlen(CWD_FAIL_RESPONSE));
            }
        }
    }

    // End
    return;
}
















/**
 * @brief Handle FTP CDUP requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestCDUP(ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() 
    //to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
        return;
    }



    // get parent directory from working directory
    char* getcwdResult = get_current_dir_name();
    int pos = strlen(getcwdResult) - 1;         // position of last char
    while (pos > 0){                            // go through from end to start
        if (getcwdResult[pos] == '/'){          //  if the current character is '/' ie end of directory
            getcwdResult[pos] = '\0';           // set terminator to get rid of current directory
            break;
        }
        pos--;
    }

    // flag for checking if the parent directory is beyond rootDir
    // use startsWith to see if parent directory starts with rootDir
    bool isnotToofar = startsWith(getcwdResult, clientFtpSession.rootDir);

    //If the parent directory is beyond 'clientFtpSession.rootDir, send
    //CDUP_FAIL_RESPONSE to the client by calling sendToClient() function
    //and return from this function;
    if (isnotToofar == false){
        free(getcwdResult);
        sendToClient(clientFtpSession.controlSocket, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
        return;
    }

    //If the parent directory is not beyond 'clientFtpSession.rootDir, change current
    //working directory to the parent directory by calling chdir() system call.
    int result = chdir("..");

    //If change is successful, send CHANGE_TO_PARENT_DIRECTORY_RESPONSE to the client by calling 
    //sendToClient() function.
    if (result == 0){
        free(getcwdResult);
        sendToClient(clientFtpSession.controlSocket, CHANGE_TO_PARENT_DIRECTORY_RESPONSE, strlen(CHANGE_TO_PARENT_DIRECTORY_RESPONSE));
    } else {
        //Otherwise, send CDUP_FAIL_RESPONSE to the client by calling sendToClient() function.
        free(getcwdResult);
        sendToClient(clientFtpSession.controlSocket, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
    }

    return;
}







/**
 * @brief Handle FTP PASV requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestPASV(ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
    } else {
        //If the client is logged in, enter into passive mode by calling 'enteringIntoPassive()' function'
        enteringIntoPassive(clientFtpSession);
    }
    return;
}













/**
 * @brief Handle FTP NLST requests.
 * 
 * @param clientFtpSession The client FTP session to handle the request for.
 * 
 */
void handleFtpRequestNLST(ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
    } else {

        //If clientFtpSession.dataSocket is equal to -1, send DATA_LOCAL_ERROR_RESPONSE to the client
        //by calling sendToClient() function with clientFtpSession.controlSocket and return from this function.
        if (clientFtpSession.dataSocket == -1){
            sendToClient(clientFtpSession.controlSocket, DATA_LOCAL_ERROR_RESPONSE, strlen(DATA_LOCAL_ERROR_RESPONSE));
        } else {

            //If clientFtpSession.dataSocket is not equal to -1, call listDirEntries() with 
            //clientFtpSession.dataSocket in order to send the list of directory entries to the client.
            int listResult = listDirEntries(clientFtpSession.dataSocket);

            //If successful, send NLST_CONNECTION_CLOSE_RESPONSE to the client, 
            if (listResult != -1){
                sendToClient(clientFtpSession.controlSocket, NLST_CONNECTION_CLOSE_RESPONSE, strlen(NLST_CONNECTION_CLOSE_RESPONSE));
            } else {
                // except send DATA_LOCAL_ERROR_RESPONSE
                sendToClient(clientFtpSession.controlSocket, DATA_LOCAL_ERROR_RESPONSE, strlen(DATA_LOCAL_ERROR_RESPONSE));
            }

            //Close clientFtpSession.dataSocket by calling closeSocket() function.
            closeSocket(clientFtpSession.dataSocket);
        }
    }
    return;
}













/**
 * @brief Handle FTP SIZE requests.
 * 
 * @param file The file to check the size of.
 * @param clientFtpSession The client FTP session to handle the request for.
 */
void handleFtpRequestSIZE(const char* file, ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
    } else {

        //Determine whether 'file' is valid or not by calling isValidPath() function.
        if (file != nullptr){
            int validResult = isValidPath(file);

            //If the 'file' is not valid, send INVALID_PATH_RESPONSE to the client
            //by calling sendToClient() function on clientFtpSession.controlSocket and 
            //return from this function.
            if (validResult != 1){
                sendToClient(clientFtpSession.controlSocket, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
                return;
            } else {

                // Check if working directory is valid. I dont know why I put this here
                char* getcwdResult = get_current_dir_name();
                if (getcwdResult == nullptr){
                    return;
                }

                //If 'file' is valid, call getFileSize() in order to determine the size of the file.
                int filesize = getFileSize(file);

                //If file size is greater than zero, send FILE_SIZE_RESPONSE with size value to the
                //client by calling sendToClient() function. 
                if (filesize > 0){
                    char* message = (char*)malloc(FTP_RESPONSE_MAX_LENGTH*(sizeof(char)));
                    if (message == nullptr){
                        return;
                    }

                    // format the message with filesize
                    sprintf(message, FILE_SIZE_RESPONSE, filesize);

                    // Send the message to the client
                    sendToClient(clientFtpSession.controlSocket, message, strlen(message));
                    // free memeory
                    free(message);
                    return;
                } else {

                    //If file size is less than or equal to zero, send RETR_UNAVAILABLE_ERROR_RESPONSE to the client.
                    sendToClient(clientFtpSession.controlSocket, RETR_UNAVAILABLE_ERROR_RESPONSE, strlen(RETR_UNAVAILABLE_ERROR_RESPONSE));
                    return;
                }
            }
        }
    }

    // End
    return;
}















/**
 * @brief Handle FTP RETR requests.
 * 
 * @param file The file to retrieve.
 * @param clientFtpSession The client FTP session to handle the request for.
 * 
 */
void handleFtpRequestRETR(const char* file, ClientFtpSession& clientFtpSession){

    //If 'clientFtpSession.isLoggedIn' is false, call handleNotLoggedIn() to handle this unusual situation.
    if (clientFtpSession.isLoggedIn == false){
        handleNotLoggedIn(clientFtpSession);
    } else {

        //If clientFtpSession.dataSocket is equal to -1, send DATA_LOCAL_ERROR_RESPONSE to the client
        //by calling sendToClient() function with clientFtpSession.controlSocket and return from this function.
        if (clientFtpSession.dataSocket == -1){
            sendToClient(clientFtpSession.controlSocket, DATA_LOCAL_ERROR_RESPONSE, strlen(DATA_LOCAL_ERROR_RESPONSE));
            return;
        } else {
            if (file != nullptr){

                //Determine whether 'file' is valid or not by calling isValidPath() function.
                int validResult = isValidPath(file);
                if (validResult != 1){

                    //If the 'file' is not valid, send INVALID_PATH_RESPONSE to the client by calling sendToClient() 
                    //function on clientFtpSession.controlSocket.
                    sendToClient(clientFtpSession.controlSocket, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));
                } else {

                    //If the file is valid, call sendFile() function on clientFtpSession.dataSocket.
                    int sendResult = sendFile(file, clientFtpSession.dataSocket);
                    if (sendResult != -1){

                        //If successful, send RETR_CONNECTION_CLOSE_RESPONSE to the client,
                        sendToClient(clientFtpSession.controlSocket, RETR_CONNECTION_CLOSE_RESPONSE, strlen(RETR_CONNECTION_CLOSE_RESPONSE));
                    } else {
                        // otherwise send RETR_UNAVAILABLE_ERROR_RESPONSE to the client.
                        sendToClient(clientFtpSession.controlSocket, RETR_UNAVAILABLE_ERROR_RESPONSE, strlen(RETR_UNAVAILABLE_ERROR_RESPONSE));
                    }
                }
            }
            // close data socket
            closeSocket(clientFtpSession.dataSocket);
        }
    }

    // End
    return;
}