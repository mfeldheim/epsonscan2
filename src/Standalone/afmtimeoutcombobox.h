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
//  afmtimeoutcombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef AFMTIMEOUTCOMBOBOX_H
#define AFMTIMEOUTCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class AfmTimeoutCombobox : public QComboBox
{
public:
    AfmTimeoutCombobox(QWidget *parent = 0);
    AutomaticModeTimeout current_item;
    void initialize(INT_SETTING_VALUE afm_para);
    void update_ui();
    void item_event(int value);
private:
    void set_enabled(bool enabled);
    void add_item();
    void select_item();
};
#endif
