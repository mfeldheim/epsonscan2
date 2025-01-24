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
//  skipblankpagessettingsdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "skipblankpagessettingsdialog.h"
#include "ui_skipblankpagessettingsdialog.h"
#include "mainwindow.h"
SkipBlankPagesSettingsDialog::SkipBlankPagesSettingsDialog(int default_lv, QWidget *parent) :
    QDialog(parent),
    det_skip_ui(new Ui::SkipBlankPagesSettingsDialog)
{
    detection_level = 0;
    det_skip_ui->setupUi(this);
    this->setFixedSize(this->size());
    det_skip_ui->Det_Lv_horizontalSlider->setValue(default_lv);
    det_skip_ui->Description_textBrowser->setText(TranslationString::GetString().translation_str.ADVANCEDSETTING_061);
    this->updateUI();
}
SkipBlankPagesSettingsDialog::~SkipBlankPagesSettingsDialog()
{
    delete det_skip_ui;
}
void SkipBlankPagesSettingsDialog::SetValue(){
    detection_level = det_skip_ui->Det_Lv_horizontalSlider->current_value;
}
void SkipBlankPagesSettingsDialog::GetValue(int *level){
    *level = detection_level;
}
void SkipBlankPagesSettingsDialog::onValueChanged(int value)
{
    QObject* obj = sender();
    if(obj == det_skip_ui->Det_Lv_horizontalSlider){
        det_skip_ui->Det_Lv_horizontalSlider->item_event(value);
    }
    this->updateUI();
}
void SkipBlankPagesSettingsDialog::updateUI(){
    det_skip_ui->Det_Lv_horizontalSlider->update_ui();
}
