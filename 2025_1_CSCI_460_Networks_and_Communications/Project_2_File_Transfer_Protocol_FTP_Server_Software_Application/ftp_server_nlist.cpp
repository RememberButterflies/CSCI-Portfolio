/**
 * @file    ftp_server_nlist.cpp
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
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include "ftp_server_nlist.h"



/**
 * @brief List the directory entries in the current working directory and send them to the client.
 * 
 * @param dataSockDescriptor The socket descriptor to send the directory entries to.
 */
int listDirEntries(int dataSockDescriptor){

    //Get the absolute path name of current working directory by calling get_current_dir_name() system call.
    char* getcwdResult = get_current_dir_name();

    // Variable for scandir
    struct dirent **namelist;

    //Get the list of directory entries by calling scandir() system call with current directory path.
    int scandirResult = scandir(getcwdResult, &namelist, NULL, alphasort);
    if (scandirResult > 0){

        //Loop through the list 
        for (int i=0; i<scandirResult; i++){

            // variable for stat
            struct stat sb;
            //Get the stat of the entry by calling stat() system call.
            int statResult = stat(namelist[i]->d_name, &sb);
            if (statResult == 0){
                // Determine the 'entryType', name, and size from entry stat.
                char entryType;
                if (S_ISREG(sb.st_mode)){
                    entryType = '-';
                } else if (S_ISDIR(sb.st_mode)){
                    entryType = 'd';
                } else if (S_ISCHR(sb.st_mode)){
                    entryType = 'c';
                } else if (S_ISBLK(sb.st_mode)){
                    entryType = 'b';
                } else if (S_ISFIFO(sb.st_mode)){
                    entryType = 'p';
                } else if (S_ISLNK(sb.st_mode)){
                    entryType = 'l';
                } else if (S_ISSOCK(sb.st_mode)){
                    entryType = 's';
                }

                // -Write the 'entryType', name, and size on 'dataSocketDescritor' by calling dprintf() system call with DIRECTORY_LIST_ENTRY_FORMAT.
            dprintf(dataSockDescriptor, DIRECTORY_LIST_ENTRY_FORMAT, entryType, namelist[i]->d_name, sb.st_size);
            }
        }
    }

    //Return the number of entries in entry list.
    return scandirResult;
}