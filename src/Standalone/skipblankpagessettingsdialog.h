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
//  skipblankpagessettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SKIPBLANKPAGESSETTINGSDIALOG_H
#define SKIPBLANKPAGESSETTINGSDIALOG_H 
#include <QDialog>
namespace Ui {
class SkipBlankPagesSettingsDialog;
}
class SkipBlankPagesSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SkipBlankPagesSettingsDialog(int default_lv, QWidget *parent = 0);
    ~SkipBlankPagesSettingsDialog();
    void SetValue(void);
    void GetValue(int *level);
public slots:
    void onValueChanged(int value);
private:
    Ui::SkipBlankPagesSettingsDialog *det_skip_ui;
    int detection_level;
    void updateUI(void);
};
#endif
