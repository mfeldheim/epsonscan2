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
//  edgecorrection.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
#include "edgecorrection.h"
EdgeCorrection::EdgeCorrection(QWidget *parent) :
    QComboBox(parent)
{
    changed = false;
    current_item = false;
}
void EdgeCorrection::initialize(SCANPARA edge_correction_para){
    changed = true;
    current_item = edge_correction_para.DeficiencyCorrection.select;
}
void EdgeCorrection::update_ui(INT_SETTING_VALUE edge_correction_para, QLabel* label1, QLabel* label2){
    label1->setText(TranslationString::GetString().translation_str.ADVANCEDSETTING_114);
    if (edge_correction_para.capability.supportLevel != kSDISupportLevelNone)
    {
        this->setVisible(true);
        label1->setVisible(true);
        label2->setVisible(true);
    }else
    {
        this->setVisible(false);
        label1->setVisible(false);
        label2->setVisible(false);
        return;
    }
    if(changed == true){
        this->clear();
        if(edge_correction_para.capability.supportLevel == kSDISupportLevelAvailable){
            this->setEnabled(true);
            label1->setVisible(true);
            label2->setVisible(true);
            this->add_item();
            this->select_item();
        }else {
            this->setEnabled(false);
            label1->setVisible(false);
            label2->setVisible(false);
        }
        changed = false;
    }
}
void EdgeCorrection::add_item(){
    int i = 0;
    this->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_031, Off);
    i++;
    this->insertItem(i, TranslationString::GetString().translation_str.ADVANCEDSETTING_059, On);
    i++;
}
void EdgeCorrection::select_item(void){
    if(current_item){
        this->setCurrentIndex(On);
    }else {
        this->setCurrentIndex(Off);
    }
}
void EdgeCorrection::item_event(int value, INT_SETTING_VALUE* edge_correction_para)
{
    QVariant select_item = this->itemData(value);
    if(select_item == Off){
        edge_correction_para->select = current_item = false;
    }else if(select_item == On){
        edge_correction_para->select = current_item = true;
    }
    changed = true;
}
void EdgeCorrection::item_event_options(void){
}
