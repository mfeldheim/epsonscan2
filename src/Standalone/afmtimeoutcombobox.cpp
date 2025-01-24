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
//  afmtimeoutcombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "afmtimeoutcombobox.h"
#include "mainwindow.h"
AfmTimeoutCombobox::AfmTimeoutCombobox(QWidget *parent) :
    QComboBox(parent),
    current_item(Timeout_none)
{
}
void AfmTimeoutCombobox::initialize(INT_SETTING_VALUE afm_para)
{
    current_item = (AutomaticModeTimeout)afm_para.select;
    this->update_ui();
}
void AfmTimeoutCombobox::update_ui()
{
    this->clear();
    this->add_item();
    this->select_item();
}
void AfmTimeoutCombobox::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
void AfmTimeoutCombobox::add_item(){
    int i = 0;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_019, Timeout_none);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_023, Timeout_10);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_024, Timeout_30);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_020, Timeout_60);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_021, Timeout_180);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.CONFIG_DOC_022, Timeout_300);
    i++;
}
void AfmTimeoutCombobox::select_item()
{
    this->setCurrentIndex(this->findData(current_item));
}
void AfmTimeoutCombobox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == Timeout_none){
        current_item = Timeout_none;
    }else if(select_item == Timeout_10){
        current_item = Timeout_10;
    }else if(select_item == Timeout_30){
        current_item = Timeout_30;
    }else if(select_item == Timeout_60){
        current_item = Timeout_60;
    }else if(select_item == Timeout_180){
        current_item = Timeout_180;
    }else if(select_item == Timeout_300){
        current_item = Timeout_300;
    }
}
