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
//  administratorpasswordinputforuksecuritydialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef AdministratorPasswordInputForUKSecurityDialog_H
#define AdministratorPasswordInputForUKSecurityDialog_H 
#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class AdministratorPasswordInputForUKSecurityDialog;
}
class AdministratorPasswordInputForUKSecurityDialog : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent* event);
public:
    explicit AdministratorPasswordInputForUKSecurityDialog(QWidget *parent = 0);
    ~AdministratorPasswordInputForUKSecurityDialog();
    QString GetPassword();
public slots:
    void PushButtonAction(void);
    void LineEditFinished();
private:
    Ui::AdministratorPasswordInputForUKSecurityDialog *ui;
    QString m_password;
};
#endif
