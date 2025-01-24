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
//  administratorpasswordinputdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "administratorpasswordinputdialog.h"
#include "ui_administratorpasswordinputdialog.h"
#include <QTimer>
AdministratorPasswordInputDialog::AdministratorPasswordInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdministratorPasswordInputDialog)
{
    m_password = "";
    ui->setupUi(this);
    this->setFixedSize(this->size());
    QTimer::singleShot(0, ui->Password_Input_lineEdit, SLOT(setFocus()));
    setWindowFlags(Qt::WindowTitleHint | Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint) ;
}
AdministratorPasswordInputDialog::~AdministratorPasswordInputDialog()
{
    delete ui;
}
void AdministratorPasswordInputDialog::PushButtonAction(void)
{
    QObject* obj = sender();
    if(obj == ui->OK_pushButton){
        m_password = ui->Password_Input_lineEdit->text();
        this->reject();
    }else if(obj == ui->Cancel_pushButton){
        m_password = "";
        this->reject();
    }
}
void AdministratorPasswordInputDialog::closeEvent(QCloseEvent* event)
{
        event->ignore();
}
void AdministratorPasswordInputDialog::LineEditFinished()
{
    if(ui->Password_Input_lineEdit->text() != ""){
        ui->OK_pushButton->setEnabled(true);
    }else {
        ui->OK_pushButton->setEnabled(false);
    }
}
QString AdministratorPasswordInputDialog::GetPassword()
{
    return m_password;
}
