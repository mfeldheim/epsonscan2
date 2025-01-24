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
//  addpagedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef ADDPAGEDIALOG_H
#define ADDPAGEDIALOG_H 
#include <QDialog>
#include <QCloseEvent>
#include "supervisor.h"
namespace Ui {
class AddPageDialog;
}
class AddPageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddPageDialog(ScanningStatus* scanning_status, QWidget *parent = 0);
    ~AddPageDialog();
private slots:
    void onButtonPressed();
protected:
    void closeEvent(QCloseEvent* event);
private:
    Ui::AddPageDialog *ui;
    bool CancelDialog(void);
    ScanningStatus* scanning_status;
};
#endif
