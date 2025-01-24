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
//  unitscombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
UnitsComboBox::UnitsComboBox(QWidget *parent) :
    QComboBox(parent)
{
    this->initialize(unit_inchi);
}
void UnitsComboBox::initialize(Units default_item){
    units_list = {unit_mm, unit_inchi};
    changed = true;
    enabled = true;
    current_item = default_item;
}
void UnitsComboBox::update_ui(void){
    if(changed == true){
        this->clear();
        this->set_enabled(enabled);
        this->add_item();
        this->select_item(current_item);
        changed = false;
    }
}
void UnitsComboBox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void UnitsComboBox::add_item(void){
    int list_size = units_list.size();
    int i = 0;
    auto units_item = units_list.begin();
    while(i < list_size){
        if((Units)*units_item == unit_inchi){
            this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_GENERAL_004, unit_inchi);
        }else if((Units)*units_item == unit_mm){
            this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_GENERAL_003, unit_mm);
        }
        ++units_item;
        i++;
    }
}
void UnitsComboBox::select_item(Units select){
    int list_size = units_list.size();
    int i = 0;
    auto units_item = units_list.begin();
    while(i < list_size){
        if((Units)*units_item == select){
            this->setCurrentIndex(i);
        }
        ++units_item;
        i++;
    }
}
void UnitsComboBox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == unit_inchi){
        current_item = unit_inchi;
    }else if(select_item == unit_mm){
        current_item = unit_mm;
    }
    changed = true;
}
Units UnitsComboBox::get_current_item(void)
{
    return current_item;
}
