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
//  devicefinder.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "devicefinder.h"
#include "devicelist.h"
#include "mainwindow.h"
#include "../Include/Config.h"
#include "loadnetworksetting.h"
#include <fstream>
#include <iostream>
#include "PathUtils.h"
DeviceFinder::DeviceFinder()
{
    wait_dialog = NULL;
}
void DeviceFinder::finder(QWidget *parent)
{
    Supervisor* sv = new Supervisor();
    if(sv == NULL){
        return;
    }
    sv->SetUp();
    SDIDeviceFinder* finder = nullptr;
    sv->SDIDeviceFinder_CreatePtr_(&finder);
    sv->SDIDeviceFinder_StartDiscoveryPtr_(finder, nullptr, nullptr);
    if(!wait_dialog){
        if(parent == 0){
            wait_dialog = new WaitingDialog((TranslationString::GetString().translation_str.LINUX_DEVICESELECT_003.toLocal8Bit()).constData(), DEVICE_SEARCH_TIME);
        }else {
            wait_dialog = new WaitingDialog((TranslationString::GetString().translation_str.LINUX_DEVICESELECT_003.toLocal8Bit()).constData(), DEVICE_SEARCH_TIME, parent);
        }
        delete wait_dialog;
    }
    sv->SDIDeviceFinder_StopDiscoveryPtr_(finder);
    SDIDeviceInfo* devices = nullptr;
    SDIInt count = 0;
    sv->SDIDeviceFinder_GetDevicesPtr_(finder, &devices, &count);
    DeviceList::device_list.clear();
    for (int i = 0; i < count; i++) {
        DeviceList::device_list.push_back(devices[i]);
    }
    sv->SDIDeviceFinder_DisposePtr_(finder);
    finder = nullptr;
    sv->Terminate();
    delete sv;
    sv = nullptr;
}
bool DeviceFinder::ManuNetfinder()
{
    DeviceList::select_manu_ip_address = -1;
    GetNetworkDevcicesFromIni(DeviceList::manu_network_device_list);
    return true;
}
