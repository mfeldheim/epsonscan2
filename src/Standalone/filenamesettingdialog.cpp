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
//  filenamesettingdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
#include "ui_filenamesettingdialog.h"
FileNameSettingDialog::FileNameSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileNameSettingDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}
FileNameSettingDialog::~FileNameSettingDialog()
{
    delete ui;
}
void FileNameSettingDialog::Initialize(SCANPARA filename_para)
{
    m_FileName_OverWrite = filename_para.FileName_OverWrite;
    m_FileName_Counter = filename_para.FileName_Counter;
    ui->Samename_Overwrite_checkBox->setChecked(m_FileName_OverWrite);
    ui->File_Counter_checkBox->setChecked(m_FileName_Counter);
}
void FileNameSettingDialog::onValueChangedBool(bool value)
{
    QObject* obj = sender();
    if(obj == ui->Samename_Overwrite_checkBox){
        m_FileName_OverWrite = value;
    }else if(obj == ui->File_Counter_checkBox){
        m_FileName_Counter = value;
    }
}
bool FileNameSettingDialog::getFileName_OverWrite()
{
    return m_FileName_OverWrite;
}
bool FileNameSettingDialog::getFileName_Counter()
{
    return m_FileName_Counter;
}
