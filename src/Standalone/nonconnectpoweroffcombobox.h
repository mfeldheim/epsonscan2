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
//  nonconnectpoweroffcombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef NONCONNECTPOWEROFFCOMBOBOX_H
#define NONCONNECTPOWEROFFCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class NonConnectPowerOffCombobox : public QComboBox
{
public:
    NonConnectPowerOffCombobox(QWidget *parent = 0);
    void initialize(NonConnectPowerOff default_item);
    void update_ui(INT_SETTING_VALUE non_connect_power_off_para);
    void item_event(int value);
    void set_enabled(bool enabled);
    NonConnectPowerOff get_current_item(void);
private:
    bool changed;
    bool enabled;
    NonConnectPowerOff current_item;
    void add_item(int32_t item_list[], int32_t list_size);
    void select_item(void);
};
#endif
