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
//  loadnetworksetting.h -- template and derived ESC/I ESC/I-2 protocol commands

#include "PathUtils.h"
#include <string>
#include <fstream>
static bool GetNetworkDevcicesFromIni(std::list<SDIDeviceInfo>& devices)
{
    if(strlen(getenv("HOME")) > 1023){
        return false;
    }
    std::string strDst = getenv("HOME");
#ifdef AKBMODE
    std::string dir_name = ".";
    dir_name = dir_name + DRIVER_NAME;
    dir_name = dir_name + "/Network/";
    dir_name = dir_name + DRIVER_NAME;
    dir_name = dir_name + ".conf";
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, dir_name.c_str());
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, ".epsonscan2/Network/epsonscan2.conf");
#endif
    std::ifstream netSettingFile(strDst.c_str());
    SDIDeviceInfo devInfo;
    memset(&devInfo, 0, sizeof(SDIDeviceInfo));
    char ip_row[256];
    std::string ip;
    if (netSettingFile.fail())
    {
        return false;
    }
    while (netSettingFile.getline(ip_row, 256 - 1))
    {
        if(strcmp(ip_row, "[Network]") == 0){
            break;
        }
    }
    devices.clear();
    while (netSettingFile.getline(ip_row, 256 - 1))
    {
        ip = ip_row;
        ip.erase(std::remove(ip.begin(), ip.end(), ' '), ip.end());
        if(ip[0] == '#' || ip[0] == ';'){
            continue;
        }
        if ( !ip.size() ) continue;
        if (ip.size() > MAX_IP_ADDR) return false;
        auto device = devices.begin();
        int i = 0;
        while(i < devices.size()){
            if(device->ipAddress == ip){
                break;
            }
            ++device;
            i++;
        }
        if(device == devices.end()){
            memset(devInfo.ipAddress, 0, MAX_IP_ADDR);
            memset(devInfo.displayName, 0, MAX_DISPLAYNAME);
            devInfo.productID = 0;
            memcpy(devInfo.ipAddress, ip.c_str(), std::min(sizeof(devInfo.ipAddress), ip.size()));
            devices.push_back(devInfo);
        }
    }
    return true;
}
