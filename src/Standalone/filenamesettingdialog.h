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
//  filenamesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef FILENAMESETTINGDIALOG_H
#define FILENAMESETTINGDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class FileNameSettingDialog;
}
class FileNameSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FileNameSettingDialog(QWidget *parent = 0);
    ~FileNameSettingDialog();
    void Initialize(SCANPARA filename_para);
    bool getFileName_OverWrite();
    bool getFileName_Counter();
private:
    Ui::FileNameSettingDialog *ui;
    bool m_FileName_OverWrite;
    bool m_FileName_Counter;
public slots:
    void onValueChangedBool(bool value);
};
#endif
