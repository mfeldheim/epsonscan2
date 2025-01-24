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
//  skipblankpagescomb.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SKIPBLANKPAGESCOMB_H
#define SKIPBLANKPAGESCOMB_H 
#include <QComboBox>
#include "supervisor.h"
#include "skipblankpagessettingsdialog.h"
class SkipblankpagesComb : public QComboBox
{
public:
    SkipblankpagesComb(QWidget *parent = 0);
    bool current_item;
    int current_level;
    bool changed;
    void initialize(SCANPARA skipblankpageslv_para);
    void focusOutEvent(QFocusEvent* event);
    void update_ui(INT_SETTING_VALUE* skipblankpages_para);
    void item_event(int value, SCANPARA* skipblankpageslv_para);
    void item_event_options(void);
    void select_item(void);
private:
    SkipBlankPagesSettingsDialog* skipblankpagessettings_dialog;
    void set_enabled(bool enabled);
    void add_item();
};
#endif
