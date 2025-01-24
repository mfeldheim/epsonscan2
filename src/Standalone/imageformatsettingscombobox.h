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
//  imageformatsettingscombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGEFORMATSETTINGSCOMBOBOX_H
#define IMAGEFORMATSETTINGSCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
#include "imageformatcomb.h"
class ImageFormatSettingsCombobox : public QComboBox
{
public:
    ImageFormatSettingsCombobox(QWidget *parent = 0);
    ImageFormat current_item;
    void initialize(ImageFormat default_item);
    void item_event(int value);
    void get_current_item(ImageFormat* select);
    void update_ui(ImageFormat img_format_list[]);
private:
    bool changed;
    void set_enabled(bool enabled);
    void add_item(ImageFormat img_format_list[]);
    void select_item();
};
#endif
