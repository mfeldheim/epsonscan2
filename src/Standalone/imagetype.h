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
//  imagetype.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGETYPE_H
#define IMAGETYPE_H 
#include <QComboBox>
#include "supervisor.h"
#include "imagetypesettingsdialog.h"
class Image_Type : public QComboBox
{
public:
    bool changed;
    Image_Type(QWidget *parent = 0);
    void initialize(INT_SETTING_VALUE* document_type_para);
    void update_ui(INT_SETTING_VALUE image_type_para);
    void item_event(int value, INT_SETTING_VALUE* image_type_para, Supervisor* sv);
    void disable_color_auto(INT_SETTING_VALUE image_type_para);
private:
    void set_enabled(bool enabled);
    void add_item(int32_t item_list[], int32_t list_size);
    void select_item(INT_SETTING_VALUE image_type_para);
    void item_event_options(Supervisor* sv);
    ImageTypeSettingsDialog* m_ImageTypeSetting_Dialog;
    INT_SETTING_VALUE* m_document_type_para;
};
#endif
