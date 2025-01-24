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
//  deviceconnectiondialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DEVICECONNECTIONDIALOG_H
#define DEVICECONNECTIONDIALOG_H 
#include <QDialog>
#include <QTimer>
#include "supervisor.h"
struct CONNECTINFO{
    QDialog* dialog;
    Supervisor* sv;
    SDIDeviceInfo select_Device;
    bool use_lastsettings;
    bool connection_result;
    bool terminate_connection;
};
namespace Ui {
class DeviceConnectionDialog;
}
class DeviceConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeviceConnectionDialog(Supervisor* sv, SDIDeviceInfo select_Device, bool use_lastsettings, QWidget *parent = 0);
    ~DeviceConnectionDialog();
    static void* ConnectToDevice(void* vpContext);
    void Initialize(void);
    bool GetConnectionResult(void);
private:
    Ui::DeviceConnectionDialog *ui;
    void ResetOnlyStandaloneVal(Supervisor* sv);
    void closeEvent(QCloseEvent* event);
    CONNECTINFO m_connect_info;
    QTimer* m_timer;
private slots:
    void CheckConnection();
};
#endif
