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
//  documentsizesettingdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "documentsizesettingdialog.h"
#include "ui_documentsizesettingdialog.h"
DocumentSizeSettingDialog::DocumentSizeSettingDialog(INT_SETTING_VALUE* inscribed_para, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentSizeSettingDialog)
{
    m_inscribed_para = inscribed_para;
    if(inscribed_para->select == 0)
    {
        m_inscribed_para->select = false;
    } else {
        m_inscribed_para->select = true;
    }
    ui->setupUi(this);
}
DocumentSizeSettingDialog::~DocumentSizeSettingDialog()
{
    delete ui;
}
void DocumentSizeSettingDialog::onValueChangedBool(bool value)
{
    QObject* obj = sender();
    if(obj == ui->Black_edge_inscribed_checkBox){
        if(ui->Black_edge_inscribed_checkBox->isChecked())
        {
            m_inscribed_para->select = 1;
        } else {
            m_inscribed_para->select = 0;
        }
    }
}
void DocumentSizeSettingDialog::Initialize(INT_SETTING_VALUE* document_size_setting)
{
    if(document_size_setting->select == 0)
    {
        ui->Black_edge_inscribed_checkBox->setChecked(false);
    }else {
        ui->Black_edge_inscribed_checkBox->setChecked(true);
    }
    ui->Black_edge_inscribed_checkBox->show();
    if(document_size_setting->capability.supportLevel == kSDISupportLevelAvailable)
    {
        ui->Black_edge_inscribed_checkBox->show();
    }else{
        ui->Black_edge_inscribed_checkBox->hide();
    }
}
