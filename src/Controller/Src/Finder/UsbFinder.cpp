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
//  UsbFinder.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "UsbFinder.hpp"
#include "Error.hpp"
#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include "Utility.hpp"
extern "C" {
#include <libusb-1.0/libusb.h>
}
#include <list>
#include <iostream>
namespace epsonscan {
static bool matchProductIDWithFlatbedOption(uint32_t productID)
{
  int j = 0;
  while(k2in1FlatbedOptionVID[j] != 0x0)
  {
   if(productID == k2in1FlatbedOptionVID[j])
   {
                return true;
    break;
   }
   j++;
  }
    return false;
}
void UsbFinder::Start(std::vector<SDIDeviceInfo>& devices, bool searchSecondDevice)
{
 try {
      libusb_context* ctx = nullptr;
      bool has2in1SupportDevice = false;
  if(libusb_init(&ctx) == 0)
     {
        libusb_device **haystack;
        ssize_t cnt = libusb_get_device_list(ctx, &haystack);
        for (ssize_t i = 0; i < cnt; i++){
                struct libusb_device_descriptor dd;
            if (libusb_get_device_descriptor (haystack[i], &dd) == 0)
            {
                SDI_TRACE_LOG("USB device found VID = %d PID = %d", dd.idVendor, dd.idProduct);
                if (dd.idVendor == kEpsonUSBVID)
                {
                    std::string modelID;
                    if ( (searchSecondDevice && matchProductIDWithFlatbedOption(dd.idProduct) ) ||
                         ModelInfo::GetModelIDFromProductID(dd.idProduct, modelID))
                    {
                        SDIDeviceInfo devInfo = {0};
                        devInfo.productID = dd.idProduct;
                        bool isValidDeviceInfo = false;
                        strncpy(const_cast<char*>(devInfo.modelID), modelID.c_str(), MAX_MODEL_ID - 1);
                        if (searchSecondDevice == false)
                        {
                            ModelInfo modelInfo(devInfo);
                            ESNumber isSupported = 0;
                            modelInfo.GetValue(kPrvHRD_FlatbedOption, isSupported);
                            if (isSupported)
                            {
                                has2in1SupportDevice = true;
                            }
                        }
                        {
                            libusb_device_handle *devHandle = NULL;
                            uint8_t strDescWithAddress[300];
                            uint8_t busNumber = libusb_get_bus_number(haystack[i]);
                            uint8_t deviceNumber = libusb_get_device_address(haystack[i]);
                            if(libusb_open (haystack[i], &devHandle) == 0)
                            {
                                uint8_t strDesc[256];
                                uint8_t serialNumber[256];
                    memset(&serialNumber, 0, 256);
                                strncpy((char*)strDesc, "Scanner", 255);
                                libusb_get_string_descriptor_ascii(devHandle, dd.iProduct, strDesc, 256);
                                if(libusb_get_string_descriptor_ascii(devHandle, dd.iSerialNumber, serialNumber, 256) < 0)
                                {
                                    if (libusb_get_string_descriptor_ascii(devHandle, dd.iSerialNumber, serialNumber, 256) < 0)
                                    {
                                        if(libusb_get_string_descriptor_ascii(devHandle, dd.iSerialNumber, serialNumber, 256) < 0)
                                        {
                                            libusb_get_string_descriptor_ascii(devHandle, dd.iSerialNumber, serialNumber, 256);
                                        }
                                    }
                                }
                                if (dd.idProduct == 0x13A )
                                {
                                    sprintf(const_cast<char*>(devInfo.displayName), "%s", "Perfection V600/GT-X820");
                                    isValidDeviceInfo = true;
                                }else if (dd.idProduct == 0x13D)
                                {
                                    sprintf(const_cast<char*>(devInfo.displayName), "%s", "Perfection V39/GT-S650");
                                    isValidDeviceInfo = true;
                                }else if (dd.idProduct == 0x13C)
                                {
                                    sprintf(const_cast<char*>(devInfo.displayName), "%s", "Perfection V19");
                                    isValidDeviceInfo = true;
                                }else if (dd.idProduct == 0x146)
                                {
                                     sprintf(const_cast<char*>(devInfo.displayName), "%s", "DS-50000/DS-60000/DS-70000");
                                    isValidDeviceInfo = true;
                                }
                                else if (dd.idProduct == 0x145)
                                {
                                    sprintf(const_cast<char*>(devInfo.displayName), "%s", "DS-5500/DS-6500/DS-7500");
                                    isValidDeviceInfo = true;
                                }
                                else
                                {
                                sprintf((char*)strDescWithAddress, "%s:%s", strDesc, serialNumber);
                                 strncpy(const_cast<char*>(devInfo.displayName),(const char*)strDescWithAddress, MAX_DISPLAYNAME - 1);
                                 if (strlen(devInfo.displayName) != 0 || searchSecondDevice)
                                 {
                                     isValidDeviceInfo = true;
                                 }
                                }
                                libusb_close (devHandle);
                                devHandle = nullptr;
                            }
                        }
                        if (isValidDeviceInfo)
                        {
                            devices.push_back(devInfo);
                        }
                    }
                }
            }
        }
        libusb_free_device_list(haystack, 1);
     }else{
         SDI_TRACE_LOG("LibUSB Init fail");
     }
    if (has2in1SupportDevice && searchSecondDevice == false)
    {
        std::vector<SDIDeviceInfo> newDevices = devices;
        devices.clear();
        for (SDIDeviceInfo devInfo2 : newDevices)
        {
            if(!matchProductIDWithFlatbedOption(devInfo2.productID))
            {
                devices.push_back(devInfo2);
            }
        }
    }
 libusb_exit(ctx);
 }catch(boost::exception& e) {
  std::cout << diagnostic_information(e) << std::endl;
 }
}
}
