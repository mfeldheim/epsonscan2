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
//  resolution.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef RESOLUTION_H
#define RESOLUTION_H 
#include <QComboBox>
#include "supervisor.h"
class Resolution : public QComboBox
{
public:
    Resolution(QWidget *parent = 0);
    bool changed;
    ResolutionList current_item;
    int current_value;
    void focusOutEvent(QFocusEvent* event);
    void initialize(INT_SETTING_VALUE resolution_para);
    void update_ui(INT_SETTING_VALUE resolution_para, bool isLFPModel);
    void validate_input();
    void item_event(int value, INT_SETTING_VALUE* resolution_para);
private:
    QIntValidator* validator;
    void set_enabled(bool enabled);
    void create_list(INT_SETTING_VALUE resolution_para, bool isLFPModel);
    void select_item();
    int IdToValue(ResolutionList item);
    ResolutionList ValueToId(int res);
};
#endif
