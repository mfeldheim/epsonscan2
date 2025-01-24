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
//  directpoweroncombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
DirectPowerOnCombobox::DirectPowerOnCombobox(QWidget *parent) :
    QComboBox(parent)
{
    this->initialize(DirectPowerOn_Off);
}
void DirectPowerOnCombobox::initialize(DirectPowerOn default_item){
    changed = true;
    enabled = true;
    current_item = default_item;
}
void DirectPowerOnCombobox::update_ui(INT_SETTING_VALUE direct_power_on_para){
    if(direct_power_on_para.capability.supportLevel == kSDISupportLevelAvailable){
        this->set_enabled(true);
        this->show();
        changed = true;
    }else if(direct_power_on_para.capability.supportLevel == kSDISupportLevelUnavailable){
        this->set_enabled(false);
        this->show();
        current_item = DirectPowerOn_Off;
        changed = true;
    }else if(direct_power_on_para.capability.supportLevel == kSDISupportLevelNone){
        this->hide();
        current_item = DirectPowerOn_Off;
    }
    if(changed == true){
        this->clear();
        this->add_item(direct_power_on_para.capability.list, direct_power_on_para.capability.countOfAllList);
        this->select_item();
        changed = false;
    }
}
void DirectPowerOnCombobox::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
void DirectPowerOnCombobox::add_item(int32_t item_list[], int32_t list_size)
{
    int i = 0;
    int item_num = 0;
    while(i < list_size){
        if(item_list[i] == DirectPowerOn_Off){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_013, DirectPowerOn_Off);
            item_num++;
        }else if(item_list[i] == DirectPowerOn_On){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_014, DirectPowerOn_On);
            item_num++;
        }
        i++;
    }
}
void DirectPowerOnCombobox::select_item()
{
    this->setCurrentIndex(this->findData(current_item));
}
void DirectPowerOnCombobox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == DirectPowerOn_Off){
        current_item = DirectPowerOn_Off;
    }else if(select_item == DirectPowerOn_On){
        current_item = DirectPowerOn_On;
    }
    changed = true;
}
DirectPowerOn DirectPowerOnCombobox::get_current_item(void)
{
    return current_item;
}
