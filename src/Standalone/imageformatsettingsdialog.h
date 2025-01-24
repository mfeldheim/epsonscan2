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
//  imageformatsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGEFORMATSETTINGSDIALOG_H
#define IMAGEFORMATSETTINGSDIALOG_H 
#include <QDialog>
#include "supervisor.h"
#define IMAGE_FORMAT_LIST_SIZE 10
namespace Ui {
class ImageFormatSettingsDialog;
}
class ImageFormatSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImageFormatSettingsDialog(QWidget *parent = 0);
    ~ImageFormatSettingsDialog();
    ImageFormat img_format_list[IMAGE_FORMAT_LIST_SIZE];
    ImageFormat select_format;
    void initialize(IMAGE_FORMAT_SETTINGS_VALUE* imageformat_settings);
public slots:
    void onValueChanged(int value);
    void updateUI();
private:
    Ui::ImageFormatSettingsDialog *ui;
    IMAGE_FORMAT_SETTINGS_VALUE* imageformat_settings_para;
    void ChangeWidget(ImageFormat format);
    void set_parameter();
    Supervisor* sv;
};
#endif
