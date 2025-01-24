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
//  adfpaperprotectioncombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
ADFPaperProtectionCombobox::ADFPaperProtectionCombobox(QWidget *parent) :
    QComboBox(parent)
{
    this->initialize(ADFPaperProtection_Off);
}
void ADFPaperProtectionCombobox::initialize(ADFPaperProtection default_item){
    changed = true;
    enabled = true;
    current_item = default_item;
}
void ADFPaperProtectionCombobox::update_ui(INT_SETTING_VALUE paper_protection_para){
    if(paper_protection_para.capability.supportLevel == kSDISupportLevelAvailable){
        this->set_enabled(true);
        this->show();
        changed = true;
    }else if(paper_protection_para.capability.supportLevel == kSDISupportLevelUnavailable){
        this->set_enabled(false);
        this->show();
        current_item = ADFPaperProtection_Off;
        changed = true;
    }else if(paper_protection_para.capability.supportLevel == kSDISupportLevelNone){
        this->hide();
        current_item = ADFPaperProtection_Off;
    }
    if(changed == true){
        this->clear();
        this->add_item(paper_protection_para.capability.list, paper_protection_para.capability.countOfAllList);
        this->select_item();
        changed = false;
    }
}
void ADFPaperProtectionCombobox::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
void ADFPaperProtectionCombobox::add_item(int32_t item_list[], int32_t list_size)
{
    int i = 0;
    int item_num = 0;
    while(i < list_size){
        if(item_list[i] == ADFPaperProtection_Off){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_003, ADFPaperProtection_Off);
            item_num++;
        }else if(item_list[i] == ADFPaperProtection_Low){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_004, ADFPaperProtection_Low);
            item_num++;
        }else if(item_list[i] == ADFPaperProtection_Normal){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_008, ADFPaperProtection_Normal);
            item_num++;
        }else if(item_list[i] == ADFPaperProtection_High){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_SCANNER_005, ADFPaperProtection_High);
            item_num++;
        }
        i++;
    }
}
void ADFPaperProtectionCombobox::select_item()
{
    this->setCurrentIndex(this->findData(current_item));
}
void ADFPaperProtectionCombobox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == ADFPaperProtection_Off){
        current_item = ADFPaperProtection_Off;
    }else if(select_item == ADFPaperProtection_Low){
        current_item = ADFPaperProtection_Low;
    }else if(select_item == ADFPaperProtection_Normal){
        current_item = ADFPaperProtection_Normal;
    }else if(select_item == ADFPaperProtection_High){
        current_item = ADFPaperProtection_High;
    }
    changed = true;
}
ADFPaperProtection ADFPaperProtectionCombobox::get_current_item(void)
{
    return current_item;
}
