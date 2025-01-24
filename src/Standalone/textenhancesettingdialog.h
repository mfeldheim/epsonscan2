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
//  textenhancesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef TEXTENHANCESETTINGDIALOG_H
#define TEXTENHANCESETTINGDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class TextEnhanceSettingDialog;
}
class TextEnhanceSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextEnhanceSettingDialog(SCANPARA device_data, QWidget *parent = 0);
    ~TextEnhanceSettingDialog();
    void SetValue(void);
    void GetValue(SCANPARA* device_data);
public slots:
    void onValueChanged(int value);
private:
    Ui::TextEnhanceSettingDialog *text_enhance_ui;
    int m_textEnhanceSensitivity;
    int m_thresholdAdjustment;
    int m_textEnhanceNoiseReductionLevel;
    bool m_textEnhancePaperCreaseReduction;
    void updateUI(void);
};
#endif
