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
//  initdeviceselectcombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
#include "devicelist.h"
InitDeviceSelectCombobox::InitDeviceSelectCombobox(QWidget *parent) :
    QComboBox(parent),
    changed(false),
    networkdeviceselect_dialog(NULL)
{
}
bool InitDeviceSelectCombobox::initialize()
{
    if(!networkdeviceselect_dialog){
        networkdeviceselect_dialog = new NetworkDeviceSelectDialog;
        if(networkdeviceselect_dialog == NULL){
            return false;
        }
    }
    changed = true;
    DeviceList::select_device = 0;
    return true;
}
void InitDeviceSelectCombobox::update_device_list(){
    if(changed == true){
        this->clear();
        this->add_device();
        this->select_item();
        changed = false;
    }
}
void InitDeviceSelectCombobox::add_device(){
    int list_size = DeviceList::device_list.size();
    int i = 0;
    const char* connection;
    auto device = DeviceList::device_list.begin();
    while(i < list_size){
        auto qString = TranslationString::GetString().translation_str.SCANNERSETTING_005.toLocal8Bit();
        if(device->ipAddress[0] == '\0'){
            connection = qString.constData();
        }else {
            connection = device->ipAddress;
        }
        this->CreateDisplayName(device->displayName, connection, i, i);
        ++device;
        i++;
    }
    this->add_manu_ip();
    this->add_option();
}
void InitDeviceSelectCombobox::add_option()
{
    this->insertSeparator(this->count());
    this->insertItem(this->count(), TranslationString::GetString().translation_str.SCANNERSETTING_006, OPTIONS);
}
void InitDeviceSelectCombobox::add_manu_ip()
{
    if(DeviceList::manu_network_device_list.size() > 0){
        int list_size = DeviceList::manu_network_device_list.size() + DeviceList::device_list.size();
        auto device = DeviceList::manu_network_device_list.begin();
        this->insertSeparator(this->count());
        int i = this->count();
        int dev_index = DeviceList::device_list.size();
        while(i <= list_size){
            this->CreateDisplayName("Network Scanner", device->ipAddress, i, dev_index);
            ++device;
            i++;
            dev_index++;
        }
    }
}
void InitDeviceSelectCombobox::CreateDisplayName(char displayName[MAX_DISPLAYNAME], const char* connection, int num, int index)
{
    char *displayDeviceName = NULL;
    char temp_displayName[MAX_DISPLAYNAME];
    bool find = false;
    memcpy_s(temp_displayName, MAX_DISPLAYNAME, displayName, strlen(displayName)+1);
    std::string connection_display = connection;
    if(strncmp(connection, "USB", 3) == 0){
    for (int i = 0; i < sizeof(temp_displayName) / sizeof(temp_displayName[0]); i++) {
        if (temp_displayName[i] == ':') {
            find = true;
        }
    }
        if(find && strtok(temp_displayName, ":")){
            std::string serialNumber = strtok(NULL, ":");
            connection_display = connection_display + ":" + serialNumber;
        }
    }
#ifdef AKBMODE
    int connection_str_size = strlen(temp_displayName) + strlen(" (") + strlen(connection_display.c_str()) + strlen(")") + 1;
#else
    int connection_str_size = strlen("EPSON ") + strlen(temp_displayName) + strlen(" (") + strlen(connection_display.c_str()) + strlen(")") + 1;
#endif
    if(!displayDeviceName){
        displayDeviceName = (char *)malloc(connection_str_size);
        if(displayDeviceName){
           memset(displayDeviceName, 0, connection_str_size);
#ifdef AKBMODE
           sprintf(displayDeviceName, "%s (%s)", temp_displayName, connection_display.c_str());
#else
           sprintf(displayDeviceName, "EPSON %s (%s)", temp_displayName, connection_display.c_str());
#endif
           this->insertItem(num, displayDeviceName, index);
           free(displayDeviceName);
           displayDeviceName = NULL;
        }
    }
}
void InitDeviceSelectCombobox::item_event(int value)
{
    int list_size = this->count();
    QVariant select_device = this->itemData(value);
    int i = 0;
    while(i < list_size){
        if(select_device == i){
            DeviceList::select_device = i;
            break;
        }
        i++;
    }
    if(select_device == OPTIONS){
        this->item_event_options();
    }
    changed = true;
}
void InitDeviceSelectCombobox::item_event_options(void){
    if(DeviceList::manu_network_device_list.size() != 0 && networkdeviceselect_dialog->Get_IP_ListTable_Size() == 0){
        networkdeviceselect_dialog->InsertDevice();
    }
    if(networkdeviceselect_dialog->isHidden()){
        networkdeviceselect_dialog->exec();
    }else {
        networkdeviceselect_dialog->activateWindow();
    }
    if(!networkdeviceselect_dialog->UpdateNetworkSettingFile()){
    }
    if(DeviceList::select_manu_ip_address >= 0){
        if(DeviceList::device_list.size() == 0){
            DeviceList::select_device = (DeviceList::manu_network_device_list.size() - 1) - DeviceList::select_manu_ip_address;
        }else {
            DeviceList::select_device = ((DeviceList::device_list.size() + DeviceList::manu_network_device_list.size()) - 1) - DeviceList::select_manu_ip_address;
        }
    }else {
        DeviceList::select_device = 0;
    }
}
void InitDeviceSelectCombobox::select_item()
{
    if(this->findData(OPTIONS) == 1){
        this->setCurrentIndex(this->findData(OPTIONS));
    }else {
        this->setCurrentIndex(this->findData(DeviceList::select_device));
    }
}
