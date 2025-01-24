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
//  adfpaperprotectioncombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef ADFPAPERPROTECTIONCOMBOBOX_H
#define ADFPAPERPROTECTIONCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class ADFPaperProtectionCombobox : public QComboBox
{
public:
    ADFPaperProtectionCombobox(QWidget *parent = 0);
    void initialize(ADFPaperProtection default_item);
    void update_ui(INT_SETTING_VALUE paper_protection_para);
    void item_event(int value);
    void set_enabled(bool enabled);
    ADFPaperProtection get_current_item(void);
private:
    bool changed;
    bool enabled;
    ADFPaperProtection current_item;
    void add_item(int32_t item_list[], int32_t list_size);
    void select_item();
};
#endif
