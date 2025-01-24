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
//  detectdoublefeedsettingsdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "detectdoublefeedsettingsdialog.h"
#include "ui_detectdoublefeedsettingsdialog.h"
#include "configuration.h"
DetectDoubleFeedSettingsDialog::DetectDoubleFeedSettingsDialog(QWidget *parent) :
    QDialog(parent),
    det_double_feed_ui(new Ui::DetectDoubleFeedSettingsDialog)
{
    det_double_feed_ui->setupUi(this);
    this->setFixedSize(this->size());
    detection_area_min = 0;
    detection_area_max = 0;
    paper_thickness = DoubleFeedDetectionLow;
    memset(&DoubleFeedDetectionLevel_item, 0, sizeof(INT_SETTING_VALUE));
}
DetectDoubleFeedSettingsDialog::~DetectDoubleFeedSettingsDialog()
{
    delete det_double_feed_ui;
}
void DetectDoubleFeedSettingsDialog::Initialize(DOUBLE_FEED_DETECTION_VALUE detectdoublefeed_para)
{
    this->select_units();
    det_double_feed_ui->Min_doubleSpinBox->initialize(detectdoublefeed_para.DoubleFeedDetectionAreaMin.select);
    det_double_feed_ui->Max_doubleSpinBox->initialize(detectdoublefeed_para);
    det_double_feed_ui->Paper_Thickness_comboBox->initialize(DoubleFeedDetectionLow);
    DoubleFeedDetectionLevel_item = detectdoublefeed_para.DoubleFeedDetectionLevel;
    if(detectdoublefeed_para.DoubleFeedDetectionLevel.capability.countOfAllList <= 1){
        det_double_feed_ui->Paper_Thickness_comboBox->setVisible(false);
        det_double_feed_ui->Paper_Thickness_label->setVisible(false);
        det_double_feed_ui->Paper_Thickness_colon_label->setVisible(false);
    }else {
        det_double_feed_ui->Paper_Thickness_comboBox->setVisible(true);
        det_double_feed_ui->Paper_Thickness_label->setVisible(true);
        det_double_feed_ui->Paper_Thickness_colon_label->setVisible(true);
        det_double_feed_ui->Paper_Thickness_comboBox->set_enabled(true);
    }
    this->updateUI();
}
void DetectDoubleFeedSettingsDialog::Finalize()
{
    det_double_feed_ui->Min_doubleSpinBox->Finalize();
    det_double_feed_ui->Max_doubleSpinBox->Finalize();
}
void DetectDoubleFeedSettingsDialog::SetValue()
{
    detection_area_min = det_double_feed_ui->Min_doubleSpinBox->base_value;
    detection_area_max = det_double_feed_ui->Max_doubleSpinBox->base_value;
    paper_thickness = det_double_feed_ui->Paper_Thickness_comboBox->current_item;
}
void DetectDoubleFeedSettingsDialog::GetValue(double *min, double *max, SDIInt *pt){
    *min = detection_area_min;
    *max = detection_area_max;
    *pt = paper_thickness;
}
void DetectDoubleFeedSettingsDialog::onValueChanged(int value)
{
    QObject* obj = sender();
    if(obj == det_double_feed_ui->Paper_Thickness_comboBox){
        det_double_feed_ui->Paper_Thickness_comboBox->item_event(value);
    }
    this->updateUI();
}
void DetectDoubleFeedSettingsDialog::updateUI()
{
    det_double_feed_ui->Paper_Thickness_comboBox->update_ui(DoubleFeedDetectionLevel_item);
}
void DetectDoubleFeedSettingsDialog::select_units(void)
{
    Configuration& config = Configuration::GetConfiguration();
    Units units = config.config_para.units;
    if(units == unit_inchi){
        det_double_feed_ui->Det_Area_stackedWidget->setCurrentIndex(1);
    }else if(units == unit_mm){
        det_double_feed_ui->Det_Area_stackedWidget->setCurrentIndex(0);
    }
}
