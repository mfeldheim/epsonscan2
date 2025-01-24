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
//  administratorpasswordinputdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef ADMINISTRATORPASSWORDINPUTDIALOG_H
#define ADMINISTRATORPASSWORDINPUTDIALOG_H 
#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class AdministratorPasswordInputDialog;
}
class AdministratorPasswordInputDialog : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent* event);
public:
    explicit AdministratorPasswordInputDialog(QWidget *parent = 0);
    ~AdministratorPasswordInputDialog();
    QString GetPassword();
public slots:
    void PushButtonAction(void);
    void LineEditFinished();
private:
    Ui::AdministratorPasswordInputDialog *ui;
    QString m_password;
};
#endif
