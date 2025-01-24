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
//  scanningside.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
Scanning_Side::Scanning_Side(QWidget *parent) :
    QComboBox(parent),
    changed(false)
{
}
void Scanning_Side::initialize(ScanningSide type){
    changed = true;
}
void Scanning_Side::update_ui(INT_SETTING_VALUE* scanning_side_para)
{
    if(scanning_side_para->capability.supportLevel == kSDISupportLevelAvailable){
        this->set_enabled(true);
        changed = true;
        this->show();
    }else if(scanning_side_para->capability.supportLevel == kSDISupportLevelUnavailable){
        this->set_enabled(false);
        scanning_side_para->select = Single_Sided;
        changed = true;
        this->show();
    }else if(scanning_side_para->capability.supportLevel == kSDISupportLevelNone){
        this->hide();
    }
    if(changed == true){
        this->clear();
        this->add_item(scanning_side_para->capability.list, scanning_side_para->capability.countOfAllList);
        this->select_item(*scanning_side_para);
        changed = false;
    }
}
void Scanning_Side::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void Scanning_Side::add_item(int32_t item_list[], int32_t list_size){
    int i = 0;
    while(i < list_size){
        if(item_list[i] == Single_Sided){
            this->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_009, Single_Sided);
        }else if(item_list[i] == Double_Sided){
            this->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_010, Double_Sided );
        }
        i++;
    }
}
void Scanning_Side::select_item(INT_SETTING_VALUE scanning_side_para){
    int list_size = scanning_side_para.capability.countOfAllList;
    int i = 0;
    while(i < list_size){
        if(scanning_side_para.capability.list[i] == scanning_side_para.select){
            this->setCurrentIndex(i);
        }
        i++;
    }
}
void Scanning_Side::item_event(int value, INT_SETTING_VALUE* scanning_side_para)
{
    QVariant select_item = this->itemData(value);
    if(select_item == Single_Sided){
        scanning_side_para->select = Single_Sided;
    }else if(select_item == Double_Sided){
        scanning_side_para->select = Double_Sided;
    }
    changed = true;
}
