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
//  lastusedsettings.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef LASTUSEDSETTINGS_H
#define LASTUSEDSETTINGS_H 
#include "ESJsonUtils.h"
#include "supervisor.h"
#include "configuration.h"
class LastUsedSettings
{
private:
    std::string PreferredInfoFilePath;
    std::string SettingsFilePath;
public:
    LastUsedSettings();
    bool CheckLastUsedDevice();
    bool ReadPreferredInfo();
    bool SelectUSBDevice(std::string display_name);
    bool SelectNetworkDevice(std::string ip);
    void CreatePreferredInfo(SDIDeviceInfo dev_info);
    void DeletePreferredInfo(void);
    bool CheckCommonSettingsFile();
    CONFIGURATION ReadCommonSettingsFile();
    void CreateCommonSettingsFile(Configuration& config);
    void DeleteCommonSettingsFile();
    CONFIGURATION ReadMainWindowInfo();
    bool CreateSettingsFile(std::string model_id, const SCANPARA device_data);
    void CreateSettingsDict(std::string user_settngs_file, const SCANPARA device_data);
    bool ReadSettingsFile(std::string model_id, SCANPARA* device_data);
    bool ReadCmdSettingsFile(std::string settings_file_path, SCANPARA* device_data);
    void SetDeviceData(std::string settings_file_path, SCANPARA* device_data);
};
#endif
