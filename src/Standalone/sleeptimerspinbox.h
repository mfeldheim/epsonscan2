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
//  sleeptimerspinbox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SLEEPTIMERSPINBOX_H
#define SLEEPTIMERSPINBOX_H 
#include <QFocusEvent>
#include <QSpinBox>
#include "supervisor.h"
class SleepTimerSpinBox : public QSpinBox
{
public:
    SleepTimerSpinBox(QWidget *parent = 0);
    void initialize(INT_SETTING_VALUE sleep_time_para);
    void update_ui(void);
    void item_event(int value);
    int get_current_item(void);
private:
    bool changed;
    bool enabled;
    int current_value;
    void set_enabled(bool enabled);
    void select_item(int select);
};
#endif
