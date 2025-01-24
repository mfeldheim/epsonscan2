//  Copyright (C) 2018-2022  SEIKO EPSON CORPORATION
//
//  License: LGPL-2.1+
//  Author : SEIKO EPSON CORPORATION
//
//  This file is part of the 'Epson Scan 2' package.
//	 This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.

//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  savedestfolder.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "savedestfolder.h"
#include "PathUtils.h"
SaveDestFolder::SaveDestFolder()
{
}
std::string SaveDestFolder::ReplaceString
(
      std::string String1
    , std::string String2
    , std::string String3
)
{
    std::string::size_type Pos( String1.find( String2 ) );
    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
    return String1;
}
bool SaveDestFolder::open_folder(Supervisor* sv)
{
    char *failer = NULL;
    char *cmd = NULL;
    int cmd_size = 0;
    const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFile(sv->device_data.SelectPath);
    if (result) {
        if(system("which nautilus > /dev/null") == 0){
            cmd_size = strlen("nautilus ");
            failer = (char *)malloc(cmd_size+1);
            if(failer){
               memset(failer, 0, cmd_size+1);
               memcpy(failer, "nautilus", cmd_size);
            }
        }else if(system("which dolphin > /dev/null") == 0){
            cmd_size = strlen("dolphin ");
            failer = (char *)malloc(cmd_size+1);
            if(failer){
               memset(failer, 0, cmd_size+1);
               memcpy(failer, "dolphin", cmd_size);
            }
        }else if(system("which caja > /dev/null") == 0){
            cmd_size = strlen("caja ");
            failer = (char *)malloc(cmd_size+1);
            if(failer){
               memset(failer, 0, cmd_size+1);
               memcpy(failer, "caja", cmd_size);
            }
        }else if(system("which dde-file-manager > /dev/null") == 0){
            cmd_size = strlen("dde-file-manager ");
            failer = (char *)malloc(cmd_size+1);
            if(failer){
               memset(failer, 0, cmd_size+1);
               memcpy(failer, "dde-file-manager", cmd_size);
            }
        }else if(system("which peony > /dev/null") == 0){
            cmd_size = strlen("peony ");
            failer = (char *)malloc(cmd_size+1);
            if(failer){
               memset(failer, 0, cmd_size+1);
               memcpy(failer, "peony", cmd_size);
            }
        }else {
            return true;
        }
        cmd_size +=1;
        cmd_size += strlen(sv->device_data.SelectPath.c_str());
        cmd_size += 2;
        cmd_size += 2;
        cmd = (char *)malloc(cmd_size + 1);
        if(cmd){
           memset(cmd, 0, cmd_size);
        }else {
            if(failer){
                free(failer);
                failer = NULL;
            }
            return false;
        }
        std::string SelectPath = sv->device_data.SelectPath;
        SelectPath = ReplaceString(SelectPath.c_str(), "\"", "\\\"");
        if(failer && cmd){
            sprintf(cmd , "%s \"%s\" &" , failer, SelectPath.c_str()) ;
            system(cmd);
            free(failer);
            failer = NULL;
            free(cmd);
            cmd = NULL;
        }else {
            if(cmd){
                free(cmd);
                cmd = NULL;
            }
            return false;
        }
        return true;
    }else {
        return false;
    }
}
