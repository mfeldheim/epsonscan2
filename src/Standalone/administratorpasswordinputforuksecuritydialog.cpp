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
//  administratorpasswordinputforuksecuritydialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "administratorpasswordinputforuksecuritydialog.h"
#include "ui_administratorpasswordinputforuksecuritydialog.h"
#include <QTimer>
AdministratorPasswordInputForUKSecurityDialog::AdministratorPasswordInputForUKSecurityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdministratorPasswordInputForUKSecurityDialog)
{
    m_password = "";
    ui->setupUi(this);
    this->setFixedSize(this->size());
    QTimer::singleShot(0, ui->Password_Input_lineEdit, SLOT(setFocus()));
    setWindowFlags(Qt::WindowTitleHint | Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint) ;
}
AdministratorPasswordInputForUKSecurityDialog::~AdministratorPasswordInputForUKSecurityDialog()
{
    delete ui;
}
void AdministratorPasswordInputForUKSecurityDialog::PushButtonAction(void)
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
void AdministratorPasswordInputForUKSecurityDialog::closeEvent(QCloseEvent* event)
{
        event->ignore();
}
void AdministratorPasswordInputForUKSecurityDialog::LineEditFinished()
{
    if(ui->Password_Input_lineEdit->text() != ""){
        ui->OK_pushButton->setEnabled(true);
    }else {
        ui->OK_pushButton->setEnabled(false);
    }
}
QString AdministratorPasswordInputForUKSecurityDialog::GetPassword()
{
    return m_password;
}
