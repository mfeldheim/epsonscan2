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
//  qualitypreviewcheckbox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef QUALITYPREVIEWCHECKBOX_H
#define QUALITYPREVIEWCHECKBOX_H 
#include <QCheckBox>
#include "capitem.h"
class QualityPreviewCheckbox : public QCheckBox
{
public:
public:
    QualityPreviewCheckbox(QWidget *parent = 0);
    bool current_item;
    void initialize(bool default_item);
    void update_ui(void);
    bool item_event(bool value);
private:
    bool changed;
    bool enabled;
    void set_enabled(bool enabled);
    void select_item(bool select);
};
#endif
