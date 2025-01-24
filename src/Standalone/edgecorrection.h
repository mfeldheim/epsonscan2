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
//  edgecorrection.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef EDGECORRECTION_H
#define EDGECORRECTION_H 
#include <QComboBox>
#include "supervisor.h"
#include "edgecorrectionsettingsdialog.h"
class EdgeCorrection : public QComboBox
{
public:
    bool changed;
    bool current_item;
    EdgeCorrection(QWidget *parent = 0);
    void initialize(SCANPARA edge_correction_para);
    void update_ui(INT_SETTING_VALUE edge_correction_para, QLabel* label1, QLabel* label2);
    void item_event(int value, INT_SETTING_VALUE* edge_correction_para);
    void item_event_options(void);
private:
    EdgeCorrectionSettingsDialog* edgeCorrectionSettingsDialog;
    void add_item();
    void select_item(void);
};
#endif
