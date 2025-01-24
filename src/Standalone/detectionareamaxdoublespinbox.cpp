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
//  detectionareamaxdoublespinbox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
DetectionAreaMaxDoubleSpinBox::DetectionAreaMaxDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
    base_value = 1550;
    this->CreateBaseToValue();
}
void DetectionAreaMaxDoubleSpinBox::initialize(DOUBLE_FEED_DETECTION_VALUE detectdoublefeed_para)
{
    base_value = detectdoublefeed_para.DoubleFeedDetectionAreaLength.select;
    this->CreateBaseToValue();
    this->SetSpinBoxParam(detectdoublefeed_para);
    if(this->isUnit_inchi()){
        this->setValue(CreateDisplayValue(current_value_inchi));
    }else {
        this->setValue(CreateDisplayValue(current_value_mm));
    }
}
void DetectionAreaMaxDoubleSpinBox::Finalize(void)
{
    this->CreateValueToBase();
    this->CreateBaseToValue();
}
#include "common_utility.h"
void DetectionAreaMaxDoubleSpinBox::SetSpinBoxParam(DOUBLE_FEED_DETECTION_VALUE detectdoublefeed_para)
{
    if(this->isUnit_inchi()){
        this->setDecimals(1);
        this->setSingleStep(0.1);
        this->setMaximum(common_utility.PixelToInchi(detectdoublefeed_para.DoubleFeedDetectionAreaLength.capability.maxValue, 100));
        this->setMinimum(common_utility.PixelToInchi(detectdoublefeed_para.DoubleFeedDetectionAreaLength.capability.minValue, 100));
    }else {
        this->setDecimals(0);
        this->setSingleStep(1);
        this->setMaximum(common_utility.PixelToMm(detectdoublefeed_para.DoubleFeedDetectionAreaLength.capability.maxValue, 100));
        this->setMinimum(common_utility.PixelToMm(detectdoublefeed_para.DoubleFeedDetectionAreaLength.capability.minValue, 100));
    }
}
void DetectionAreaMaxDoubleSpinBox::CreateBaseToValue(void)
{
    current_value_inchi = base_value / 100;
    current_value_mm = base_value * 25.4 / 100;
}
void DetectionAreaMaxDoubleSpinBox::CreateValueToBase(void)
{
    if(this->isUnit_inchi()){
        if(CreateDisplayValue(current_value_inchi) != CreateDisplayValue(this->value())){
            current_value_inchi = this->value();
            base_value = (current_value_inchi * 100) + 0.005;
        }
    }else {
        if(CreateDisplayValue(current_value_mm) != CreateDisplayValue(this->value())){
            current_value_mm = this->value();
            base_value = (current_value_mm * 100 / 25.4) + 0.005;
        }
    }
}
double DetectionAreaMaxDoubleSpinBox::CreateDisplayValue(double value)
{
    int magnification;
    int temp;
    if(this->isUnit_inchi()){
        magnification = 100;
        temp = value * magnification;
    }else {
        magnification = 10;
        temp = value * magnification;
    }
    return (double)temp / (double)magnification;
}
void DetectionAreaMaxDoubleSpinBox::set_enabled(bool enabled)
{
    this->setEnabled(enabled);
}
bool DetectionAreaMaxDoubleSpinBox::isUnit_inchi(void)
{
    Configuration& config = Configuration::GetConfiguration();
    Units units = config.config_para.units;
    if(units == unit_inchi){
        return true;
    }else if(units == unit_mm){
        return false;
    }else {
        return false;
    }
}
void DetectionAreaMaxDoubleSpinBox::setMinValue(double value){
    if(value < 0){
        value = 0;
    }
    double dif = 0;
    if(this->isUnit_inchi()){
        dif = 1.0;
    }else {
        dif = 26;
    }
    this->setMinimum(value + dif);
}
