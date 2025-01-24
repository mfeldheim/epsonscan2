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
//  dropoutcombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DROPOUTCOMBOBOX_H
#define DROPOUTCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class DropoutCombobox : public QComboBox
{
public:
    bool changed;
    DropoutCombobox(QWidget *parent = 0);
    DropoutColor current_item;
    void initialize(INT_SETTING_VALUE dropout_para);
    void update_ui(INT_SETTING_VALUE dropout_para);
    void item_event(int value, INT_SETTING_VALUE* dropout_para);
    void set_enabled(bool enabled);
private:
    void add_item(int32_t item_list[], int32_t list_size);
    void select_item();
};
#endif
