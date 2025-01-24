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
//  focuspositionsettingdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "focuspositionsettingdialog.h"
#include "ui_focuspositionsettingdialog.h"
FocusPositionSettingDialog::FocusPositionSettingDialog(SCANPARA* device_data, QWidget *parent) :
    QDialog(parent),
    focus_position_ui(new Ui::FocusPositionSettingDialog)
{
    focus_position_ui->setupUi(this);
    this->setFixedSize(this->size());
    m_focusPositionLevel = device_data->focusPosition.select;
    focus_position_ui->FocusPosition_slider->initialize(m_focusPositionLevel);
    this->updateUI();
}
FocusPositionSettingDialog::~FocusPositionSettingDialog()
{
    delete focus_position_ui;
}
void FocusPositionSettingDialog::updateUI()
{
    focus_position_ui->FocusPosition_slider->update_ui();
}
void FocusPositionSettingDialog::onValueChanged(int value)
{
    this->updateUI();
}
void FocusPositionSettingDialog::SetValue()
{
    m_focusPositionLevel = focus_position_ui->FocusPosition_slider->value();
}
void FocusPositionSettingDialog::GetValue(SCANPARA* device_data)
{
    device_data->focusPosition.select = m_focusPositionLevel;
}
void FocusPositionSettingDialog::PushButtonAction(void)
{
    QObject* obj = sender();
    if(obj == focus_position_ui->OK_pushButton){
        m_focusPositionLevel = focus_position_ui->FocusPosition_slider->value();
        this->reject();
    }else if(obj == focus_position_ui->Cancel_pushButton){
        this->reject();
    }
}
