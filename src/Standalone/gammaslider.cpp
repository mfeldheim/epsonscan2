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
//  gammaslider.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
GammaSlider::GammaSlider(QWidget *parent) :
    QSlider(parent)
{
    changed = false;
    current_item = 0;
}
void GammaSlider::initialize(double default_item){
    changed = true;
    current_item = default_item;
}
void GammaSlider::update_ui(){
    if(changed == true){
        this->set_enabled(true);
        this->setValue(current_item);
        changed = false;
    }
}
void GammaSlider::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
void GammaSlider::item_event(double value, INT_SETTING_VALUE* gamma_para)
{
    gamma_para->select = current_item = value;
    changed = true;
}
void GammaSlider::setGammaSlider(double value){
    this->setValue(value * 10);
}
