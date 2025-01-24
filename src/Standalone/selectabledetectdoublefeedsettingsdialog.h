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
//  selectabledetectdoublefeedsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SELECTABLEDETECTDOUBLEFEEDSETTINGSDIALOG_H
#define SELECTABLEDETECTDOUBLEFEEDSETTINGSDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class SelectableDetectDoubleFeedSettingsDialog;
}
class SelectableDetectDoubleFeedSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectableDetectDoubleFeedSettingsDialog(QWidget *parent = 0);
    ~SelectableDetectDoubleFeedSettingsDialog();
    void Initialize(INT_SETTING_VALUE DoubleFeedDetectionLevel);
    void SetValue(void);
    void Finalize(void);
    void GetValue(double *min, double *max, SDIInt *pt);
public slots:
    void onValueChanged(int value);
    void onValueChangedBool(bool check);
private:
    Ui::SelectableDetectDoubleFeedSettingsDialog *det_double_feed_ui;
    bool m_ultrasonic_sensor;
    DoubleFeedDetection paper_thickness;
    double detection_area_min;
    double detection_area_max;
    bool m_scanned_image;
    bool m_paper_protection;
    INT_SETTING_VALUE DoubleFeedDetectionLevel_item;
    void updateUI(void);
    void select_units(void);
    void WarningMessageBox(void);
};
#endif
