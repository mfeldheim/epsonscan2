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
//  automaticfeedingmodecombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef AUTOMATICFEEDINGMODECOMBOBOX_H
#define AUTOMATICFEEDINGMODECOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class AutomaticFeedingModeCombobox : public QComboBox
{
public:
    AutomaticFeedingModeCombobox(QWidget *parent = 0);
    bool changed;
    bool current_item;
    void initialize(INT_SETTING_VALUE afm_para, INT_SETTING_VALUE cafm_para);
    void update_ui(INT_SETTING_VALUE afm_para, bool use_continuousAutoFeedingMode);
    void item_event(int value, INT_SETTING_VALUE* afm_para, bool* use_continuousAutoFeedingMode);
    void set_enabled(bool enabled);
private:
    void add_item();
    void select_item(INT_SETTING_VALUE afm_para, bool use_continuousAutoFeedingMode);
    bool supported_cafm;
};
#endif
