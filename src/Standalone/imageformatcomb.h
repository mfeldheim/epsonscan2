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
//  imageformatcomb.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGEFORMATCOMB_H
#define IMAGEFORMATCOMB_H 
#include <QComboBox>
#include "supervisor.h"
#include "imageformatsettingsdialog.h"
class ImageFormatComb : public QComboBox
{
public:
    ImageFormatComb(QWidget *parent = 0);
    ImageFormat current_item;
    void initialize(IMAGE_FORMAT_SETTINGS_VALUE imageformat_settings_para);
    void focusOutEvent(QFocusEvent* event);
    void update_ui(IMAGE_FORMAT_SETTINGS_VALUE imageformat_settings_para, bool isLFPModel);
    void item_event(int value, IMAGE_FORMAT_SETTINGS_VALUE* imageformat_settings_para);
private:
    ImageFormatSettingsDialog* imageformat_dialog;
    bool changed;
    void set_enabled(bool enabled);
    void add_item(int32_t item_list[], int32_t list_size, SDISupportLevel mTiff_support_lv, bool isLFPModel, SDISupportLevel OFD_support);
    void add_option(int list_size);
    void select_item();
    void item_event_options(IMAGE_FORMAT_SETTINGS_VALUE* imageformat_settings_para);
};
#endif
