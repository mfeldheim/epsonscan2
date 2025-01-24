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
//  imagetypesettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGETYPESETTINGSDIALOG_H
#define IMAGETYPESETTINGSDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class ImageTypeSettingsDialog;
}
class ImageTypeSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    bool changed;
    explicit ImageTypeSettingsDialog(QWidget *parent = 0);
    ~ImageTypeSettingsDialog();
    bool Initialize(Supervisor* sv);
    void select_item(INT_SETTING_VALUE image_type_auto_para);
    void select_level(INT_SETTING_VALUE image_type_auto_lv_para);
    void item_event(int value);
    void item_event_slider(int value);
    AutoColorPixelType get_currentItem();
    int get_currentValue();
private slots:
    void onValueChanged(int value);
private:
    Ui::ImageTypeSettingsDialog *ui;
    AutoColorPixelType current_item;
    int current_value;
    void add_item(int32_t item_list[], int32_t list_size);
};
#endif
