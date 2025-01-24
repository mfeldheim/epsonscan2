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
//  autocroppinginscribedcheckbox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "autocroppinginscribedcheckbox.h"
AutoCroppingInscribedCheckBox::AutoCroppingInscribedCheckBox(QWidget *parent) :
    QCheckBox(parent),
    changed(false)
{
}
void AutoCroppingInscribedCheckBox::initialize(bool default_val){
    changed = true;
    current_item = default_val;
    this->setEnabled(true);
}
void AutoCroppingInscribedCheckBox::focusOutEvent(QFocusEvent* event){
    event->accept();
}
void AutoCroppingInscribedCheckBox::update_ui(INT_SETTING_VALUE inscribed_para)
{
    if(changed == true){
        this->select_item(inscribed_para.select);
        changed = false;
    }
}
void AutoCroppingInscribedCheckBox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void AutoCroppingInscribedCheckBox::select_item(bool select){
    this->setChecked(select);
}
void AutoCroppingInscribedCheckBox::item_event(bool value, INT_SETTING_VALUE* inscribed_para)
{
    inscribed_para->select = value;
    changed = true;
}
