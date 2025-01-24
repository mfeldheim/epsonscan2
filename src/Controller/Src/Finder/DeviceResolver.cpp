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
//  DeviceResolver.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "DeviceResolver.hpp"
#include "ModelInfo.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
namespace epsonscan
{
SDIError GetDeviceID2(const uint8_t* address,
                           uint8_t* val,
                           uint8_t vallen,
                           ESCommandType comType
                           )
{
    ESString es_deviceInfo;
    auto engine = std::make_shared<Engine>(comType);
 ESDictionary deviceDict;
 deviceDict[ES_CNCT_KEY_TYPE] = (ESNumber)kESConnectionNetworkIS;
 deviceDict[ES_CNCT_KEY_ADDRESS] = ESString((const char*)address);
 ESDictionary esDeviceDict;
 esDeviceDict[ES_CNCT_KEY_ROOT] = deviceDict;
 ES_CMN_FUNCS::JSON::DictionaryToJSON(esDeviceDict, es_deviceInfo);
 ES_Dump_Json(deviceDict, "deviceDict");
 if(engine.get()->InitWithDeviceInfoDict(es_deviceInfo.c_str()) == false)
 {
  SDI_TRACE_LOG("InitDevice fails");
        return kSDIErrorUnknownError;
 }
    SDIError err = engine->Open();
    if (err != kSDIErrorNone)
    {
        return err;
    }
    ESString productName;
    if(engine->GetValueForKey(kESProductName, productName))
    {
         strncpy((char*)val, (const char*)productName.c_str(), vallen);
    }
    engine->Close();
    return kSDIErrorNone;
}
    static void EraseSubStr(std::string & mainStr, const std::string & toErase)
    {
        size_t pos = mainStr.find(toErase);
        if (pos != std::string::npos)
        {
            mainStr.erase(pos, toErase.length());
        }
    }
    bool DeviceResolver::Resolve(SDIDeviceInfo& devInfo)
    {
        SDI_TRACE_LOG("Resolve %s", devInfo.ipAddress);
        memset(devInfo.displayName, 0, MAX_DISPLAYNAME);
        memset(devInfo.modelID, 0 , MAX_MODEL_ID);
        if (GetDeviceID2((uint8_t*)devInfo.ipAddress, (uint8_t*)devInfo.displayName, MAX_DISPLAYNAME, kESCommandTypeESCI2) == kSDIErrorInvalidResponse)
        {
            GetDeviceID2((uint8_t*)devInfo.ipAddress, (uint8_t*)devInfo.displayName, MAX_DISPLAYNAME, kESCommandTypeESCI);
        }
        SDI_TRACE_LOG("Resolve %s displayName %s", devInfo.ipAddress, devInfo.displayName);
        std::string modelID = "";
        std::string deviceID = std::string(devInfo.displayName);
        EraseSubStr(deviceID, "EPSON ");
        memset(devInfo.displayName, 0, sizeof(devInfo.displayName));
        strncpy(devInfo.displayName, deviceID.c_str(), sizeof(devInfo.displayName) - 1);
     if(ModelInfo::GetModelIDFromProductName(deviceID, modelID)){
   strncpy(const_cast<char*>(devInfo.modelID), modelID.c_str(), MAX_MODEL_ID);
            SDI_TRACE_LOG("Resolve %s displayName %s modelID %s ", devInfo.ipAddress, devInfo.displayName, devInfo.modelID);
            return true;
        }else{
            return false;
        }
        return false;
    }
}
