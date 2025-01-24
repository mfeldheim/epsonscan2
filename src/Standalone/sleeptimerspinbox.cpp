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
//  sleeptimerspinbox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
SleepTimerSpinBox::SleepTimerSpinBox(QWidget *parent) :
    QSpinBox(parent),
    changed(false),
    enabled(false),
    current_value(0)
{
}
void SleepTimerSpinBox::initialize(INT_SETTING_VALUE sleep_time_para)
{
    this->setMaximum(sleep_time_para.capability.allMaxValue);
    this->setMinimum(sleep_time_para.capability.allMinValue);
    this->setValue(sleep_time_para.select);
    changed = true;
    enabled = true;
    current_value = sleep_time_para.select;
}
void SleepTimerSpinBox::update_ui(){
    if(changed == true){
        this->set_enabled(enabled);
        changed = false;
    }
}
void SleepTimerSpinBox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void SleepTimerSpinBox::item_event(int value)
{
    current_value = value;
    changed = true;
}
int SleepTimerSpinBox::get_current_item(void)
{
    return current_value;
}
