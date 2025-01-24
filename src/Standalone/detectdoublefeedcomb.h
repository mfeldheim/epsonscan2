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
//  detectdoublefeedcomb.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DETECTDOUBLEFEEDCOMB_H
#define DETECTDOUBLEFEEDCOMB_H 
#include <QComboBox>
#include "supervisor.h"
#include "detectdoublefeedsettingsdialog.h"
#include "selectabledetectdoublefeedsettingsdialog.h"
class DetectDoubleFeedComb : public QComboBox
{
public:
    DetectDoubleFeedComb(QWidget *parent = 0);
    bool changed;
    double max_value;
    double min_value;
    INT_SETTING_VALUE pt_value;
    void initialize(INT_SETTING_VALUE detectdoublefeed_para);
    void focusOutEvent(QFocusEvent* event);
    void update_ui(DOUBLE_FEED_DETECTION_VALUE detectdoublefeed_para);
    void item_event(int value, DOUBLE_FEED_DETECTION_VALUE* detectdoublefeed_para);
    void item_event_options(DOUBLE_FEED_DETECTION_VALUE* detectdoublefeed_para);
private:
    DetectDoubleFeedSettingsDialog* detectdoublefeedsettings_dialog;
    SelectableDetectDoubleFeedSettingsDialog* selectdetectdoublefeedsettings_dialog;
    void set_enabled(bool enabled);
    void add_item(SDICapability capability);
    void select_item(INT_SETTING_VALUE detectdoublefeed_para);
};
#endif
