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
//  sensorglassdirtsensitivitycombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
SensorGlassDirtSensitivityCombobox::SensorGlassDirtSensitivityCombobox(QWidget *parent) :
    QComboBox(parent)
{
    this->initialize(SensorGlassDirtSensitivityOff);
}
void SensorGlassDirtSensitivityCombobox::initialize(SensorGlassDirtSensitivity default_item){
    changed = true;
    enabled = true;
    current_item = default_item;
}
void SensorGlassDirtSensitivityCombobox::update_ui(INT_SETTING_VALUE sensor_glass_para){
    if(sensor_glass_para.capability.supportLevel == kSDISupportLevelAvailable){
        this->set_enabled(true);
        this->show();
        changed = true;
    }else if(sensor_glass_para.capability.supportLevel == kSDISupportLevelUnavailable){
        this->set_enabled(false);
        this->show();
        current_item = SensorGlassDirtSensitivityOff;
        changed = true;
    }else if(sensor_glass_para.capability.supportLevel == kSDISupportLevelNone){
        this->hide();
        current_item = SensorGlassDirtSensitivityOff;
    }
    if(changed == true){
        this->clear();
        this->add_item(sensor_glass_para.capability.list, sensor_glass_para.capability.countOfAllList);
        this->select_item();
        changed = false;
    }
}
void SensorGlassDirtSensitivityCombobox::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
void SensorGlassDirtSensitivityCombobox::add_item(int32_t item_list[], int32_t list_size)
{
    int i = 0;
    int item_num = 0;
    while(i < list_size){
        if(item_list[i] == SensorGlassDirtSensitivityOff){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_003, SensorGlassDirtSensitivityOff);
            item_num++;
        }else if(item_list[i] == SensorGlassDirtSensitivityLow){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_004, SensorGlassDirtSensitivityLow);
            item_num++;
        }else if(item_list[i] == SensorGlassDirtSensitivityNormal){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_005, SensorGlassDirtSensitivityNormal);
            item_num++;
        }
        i++;
    }
}
void SensorGlassDirtSensitivityCombobox::select_item()
{
    this->setCurrentIndex(this->findData(current_item));
}
void SensorGlassDirtSensitivityCombobox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == SensorGlassDirtSensitivityOff){
        current_item = SensorGlassDirtSensitivityOff;
    }else if(select_item == SensorGlassDirtSensitivityLow){
        current_item = SensorGlassDirtSensitivityLow;
    }else if(select_item == SensorGlassDirtSensitivityNormal){
        current_item = SensorGlassDirtSensitivityNormal;
    }
    changed = true;
}
SensorGlassDirtSensitivity SensorGlassDirtSensitivityCombobox::get_current_item(void)
{
    return current_item;
}
