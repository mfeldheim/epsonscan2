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
//  documentsourcesettingsdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "documentsourcesettingsdialog.h"
#include "ui_documentsourcesettingsdialog.h"
DocumentSourceSettingsDialog::DocumentSourceSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentSourceSettingsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}
DocumentSourceSettingsDialog::~DocumentSourceSettingsDialog()
{
    delete ui;
}
void DocumentSourceSettingsDialog::Initialize(INT_SETTING_VALUE afm_para)
{
    ui->Afm_Timeout_comboBox->initialize(afm_para);
}
void DocumentSourceSettingsDialog::onValueChanged(int value)
{
    QObject* obj = sender();
    if(obj == ui->Afm_Timeout_comboBox){
        ui->Afm_Timeout_comboBox->item_event(value);
    }
    ui->Afm_Timeout_comboBox->update_ui();
}
int DocumentSourceSettingsDialog::GetCurrentValue()
{
    return ui->Afm_Timeout_comboBox->current_item;
}
