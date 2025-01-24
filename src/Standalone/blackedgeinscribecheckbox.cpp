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
//  blackedgeinscribecheckbox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "blackedgeinscribecheckbox.h"
BlackEdgeInscribeCheckBox::BlackEdgeInscribeCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
    changed = false;
    current_item = false;
}
void BlackEdgeInscribeCheckBox::initialize(bool default_val){
    changed = true;
    current_item = default_val;
    this->setEnabled(true);
}
void BlackEdgeInscribeCheckBox::focusOutEvent(QFocusEvent* event){
}
void BlackEdgeInscribeCheckBox::update_ui(){
    if(changed == true){
        this->select_item((bool)current_item);
        changed = false;
    }
}
void BlackEdgeInscribeCheckBox::select_item(bool select){
    this->setChecked(select);
}
void BlackEdgeInscribeCheckBox::item_event(bool value)
{
    current_item = value;
    changed = true;
}
bool BlackEdgeInscribeCheckBox::get_current_item()
{
    return current_item;
}
