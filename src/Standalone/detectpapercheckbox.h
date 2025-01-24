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
//  detectpapercheckbox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DETECTPAPERCHECKBOX_H
#define DETECTPAPERCHECKBOX_H 
#include <QCheckBox>
#include "capitem.h"
class DetectPaperCheckBox : public QCheckBox
{
public:
    DetectPaperCheckBox(QWidget *parent = 0);
    bool current_item;
    void initialize(bool default_item);
    void update_ui(void);
    void item_event(bool value);
private:
    bool changed;
    bool enabled;
    void set_enabled(bool enabled);
    void select_item(bool select);
};
#endif
