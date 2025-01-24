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
//  networkdeviceselectdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef NETWORKDEVICESELECTDIALOG_H
#define NETWORKDEVICESELECTDIALOG_H 
#include "supervisor.h"
#include <QDialog>
#include <fstream>
namespace Ui {
class NetworkDeviceSelectDialog;
}
class NetworkDeviceSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NetworkDeviceSelectDialog(QWidget *parent = 0);
    ~NetworkDeviceSelectDialog();
    int Get_IP_ListTable_Size();
    void InsertDevice();
    bool UpdateNetworkSettingFile();
public slots:
    void LineEditFinished();
    void PushButtonAction();
    void AvailableDeleteButton();
private:
    Ui::NetworkDeviceSelectDialog *ui;
    void RemoveNetworkScanner(QString target_ip);
    bool DeleteMessageBox(QString target_ip);
    bool CreateNewNetworkSettingFile(int device_list_size);
    void closeEvent(QCloseEvent* event);
};
#endif
