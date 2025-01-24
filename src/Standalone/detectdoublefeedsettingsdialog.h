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
//  detectdoublefeedsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DETECTDOUBLEFEEDSETTINGSDIALOG_H
#define DETECTDOUBLEFEEDSETTINGSDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class DetectDoubleFeedSettingsDialog;
}
class DetectDoubleFeedSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DetectDoubleFeedSettingsDialog(QWidget *parent = 0);
    ~DetectDoubleFeedSettingsDialog();
    void Initialize(DOUBLE_FEED_DETECTION_VALUE detectdoublefeed_para);
    void SetValue(void);
    void Finalize(void);
    void GetValue(double *min, double *max, SDIInt *pt);
public slots:
    void onValueChanged(int value);
private:
    Ui::DetectDoubleFeedSettingsDialog *det_double_feed_ui;
    DoubleFeedDetection paper_thickness;
    double detection_area_min;
    double detection_area_max;
    INT_SETTING_VALUE DoubleFeedDetectionLevel_item;
    void updateUI(void);
    void select_units(void);
};
#endif
