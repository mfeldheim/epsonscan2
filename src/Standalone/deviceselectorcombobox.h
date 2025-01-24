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
//  deviceselectorcombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DEVICESELECTORCOMBOBOX_H
#define DEVICESELECTORCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
#include "networkdeviceselectdialog.h"
#include "waitingdialog.h"
class DeviceSelectorCombobox : public QComboBox
{
public:
    DeviceSelectorCombobox(QWidget *parent = 0);
    void initialize();
    void finder(void);
    void update_device_list();
    void add_device();
    void CreateDisplayName(char displayName[MAX_DISPLAYNAME], const char* connection, int num, int index);
    void item_event(int value);
    void item_event_options();
    SDIDeviceInfo get_cur_device();
private:
    NetworkDeviceSelectDialog* networkdeviceselect_dialog;
    WaitingDialog* wait_dialog;
    bool changed;
    void add_option();
    void add_manu_ip();
    void select_item();
};
#endif
