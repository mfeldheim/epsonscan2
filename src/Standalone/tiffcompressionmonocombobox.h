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
//  tiffcompressionmonocombobox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef TIFFCOMPRESSIONMONOCOMBOBOX_H
#define TIFFCOMPRESSIONMONOCOMBOBOX_H 
#include <QComboBox>
#include "supervisor.h"
class TiffCompressionMonoCombobox : public QComboBox
{
public:
    TiffCompressionMonoCombobox(QWidget *parent = 0);
    TiffCompression current_item;
    void initialize(TiffCompression default_value);
    void update_ui(INT_SETTING_VALUE tiff_compression_para);
    void item_event(int value, INT_SETTING_VALUE* tiff_compression_para);
private:
    bool changed;
    void set_enabled(bool enabled);
    void add_item(int32_t item_list[], int32_t list_size);
    void select_item();
};
#endif
