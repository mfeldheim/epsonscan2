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
//  removebackcombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
RemoveBackComboBox::RemoveBackComboBox(QWidget *parent) :
    QComboBox(parent),
    changed(false),
    current_item(BackgroundRemovalNone)
{
}
void RemoveBackComboBox::initialize(INT_SETTING_VALUE remove_background_para)
{
    changed = true;
    current_item = (BackgroundRemoval)remove_background_para.select;
}
void RemoveBackComboBox::update_ui(INT_SETTING_VALUE remove_background_para)
{
    this->set_visible(remove_background_para.capability.supportLevel);
    if(changed == true){
        this->clear();
        if(remove_background_para.capability.supportLevel == kSDISupportLevelAvailable){
            this->add_item(remove_background_para.capability.list, remove_background_para.capability.countOfList);
            this->select_item();
        }else {
            this->add_item(remove_background_para.capability.allList, remove_background_para.capability.countOfAllList);
            this->set_enabled(false);
        }
        changed = false;
    }
}
void RemoveBackComboBox::set_visible(SDISupportLevel level)
{
    if(level == kSDISupportLevelAvailable){
        this->show();
    }else if(level == kSDISupportLevelUnavailable){
        this->show();
    }else if(level == kSDISupportLevelNone){
        this->hide();
    }
}
void RemoveBackComboBox::set_enabled(bool enabled)
{
    if(enabled == true){
        this->setEnabled(true);
        if(current_item == BackgroundRemovalNone){
            current_item = BackgroundRemovalNormal;
            changed = true;
        }
    }else {
        this->setEnabled(false);
        current_item = BackgroundRemovalNone;
        this->setCurrentIndex(this->findData(BackgroundRemovalNormal));
    }
}
void RemoveBackComboBox::add_item(int32_t item_list[], int32_t list_size)
{
    int i = 0;
    int item_num = 0;
    while(i < list_size){
        if(item_list[i] == BackgroundRemovalNormal){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ADVANCEDSETTING_063, BackgroundRemovalNormal);
            item_num++;
        }else if(item_list[i] == BackgroundRemovalHigh){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ADVANCEDSETTING_064, BackgroundRemovalHigh);
            item_num++;
        }
        i++;
    }
}
void RemoveBackComboBox::select_item()
{
    int item = this->findData(current_item);
    if(item != -1){
        this->setCurrentIndex(item);
    }else {
        this->setCurrentIndex(0);
    }
}
void RemoveBackComboBox::item_event(int value, INT_SETTING_VALUE* remove_background_para)
{
    QVariant select_item = this->itemData(value);
    if(select_item == BackgroundRemovalNormal){
        remove_background_para->select = current_item = BackgroundRemovalNormal;
    }else if(select_item == BackgroundRemovalHigh){
        remove_background_para->select = current_item = BackgroundRemovalHigh;
    }
    changed = true;
}
