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
//  deskewcheckbox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
DeskewCheckbox::DeskewCheckbox(QWidget *parent) :
    QCheckBox(parent),
    changed(false)
{
}
void DeskewCheckbox::initialize(){
    changed = true;
}
void DeskewCheckbox::focusOutEvent(QFocusEvent* event){
    event->accept();
}
void DeskewCheckbox::update_ui(INT_SETTING_VALUE deskew_para)
{
    if(deskew_para.capability.supportLevel == kSDISupportLevelAvailable){
        this->set_enabled(true);
        this->show();
    }else if(deskew_para.capability.supportLevel == kSDISupportLevelUnavailable){
        this->set_enabled(false);
        this->show();
        deskew_para.select = false;
        changed = true;
    }else if(deskew_para.capability.supportLevel == kSDISupportLevelNone){
        this->hide();
    }
    if(changed == true){
        this->select_item(deskew_para.select);
        changed = false;
    }
}
void DeskewCheckbox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void DeskewCheckbox::select_item(bool select){
    this->setChecked(select);
}
void DeskewCheckbox::item_event(bool value, INT_SETTING_VALUE* deskew_para)
{
    deskew_para->select = value;
    changed = true;
}
