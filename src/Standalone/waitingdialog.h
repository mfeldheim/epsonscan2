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
//  waitingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H 
#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
namespace Ui {
class WaitingDialog;
}
class WaitingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WaitingDialog(const char* message, int wait_time, QWidget *parent = 0);
    ~WaitingDialog();
    int wait_time;
protected:
    void closeEvent(QCloseEvent* event);
private:
    Ui::WaitingDialog *ui;
    QTimer* m_timer;
    int time_count;
private slots:
    void Update();
};
#endif
