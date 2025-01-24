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
//  scanningdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SCANNINGDIALOG_H
#define SCANNINGDIALOG_H 
#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "supervisor.h"
namespace Ui {
class ScanningDialog;
}
class ScanningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScanningDialog(Supervisor* sv, QWidget *parent = 0);
    ~ScanningDialog();
    int getPagecount();
    void ScanInitialize(QString progress_message);
protected:
    void closeEvent(QCloseEvent* event);
private:
    Ui::ScanningDialog *ui;
    Supervisor *sv;
    int page_count;
    QTimer* m_timer;
    bool do_cancel;
private slots:
    void Update();
    void Cancel();
};
#endif
