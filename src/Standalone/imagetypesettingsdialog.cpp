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
//  imagetypesettingsdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "imagetypesettingsdialog.h"
#include "ui_imagetypesettingsdialog.h"
#include "translationstring.h"
ImageTypeSettingsDialog::ImageTypeSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageTypeSettingsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}
ImageTypeSettingsDialog::~ImageTypeSettingsDialog()
{
    delete ui;
}
bool ImageTypeSettingsDialog::Initialize(Supervisor* sv)
{
    current_item = (AutoColorPixelType)sv->device_data.AutoColorPixelType.select;
    current_value = sv->device_data.AutoColorPixelLevel.select;
    ui->Detection_Color_Auto_comboBox->clear();
    this->add_item(sv->device_data.AutoColorPixelType.capability.list, sv->device_data.AutoColorPixelType.capability.countOfList);
    this->select_item(sv->device_data.AutoColorPixelType);
    this->select_level(sv->device_data.AutoColorPixelLevel);
    if(sv->device_data.AutoColorPixelLevel.capability.supportLevel == kSDISupportLevelNone){
        ui->ImageType_Adjustment_horizontalSlider->hide();
    }else {
        ui->ImageType_Adjustment_horizontalSlider->show();
    }
    if(ui->ImageType_Adjustment_horizontalSlider->isHidden()){
        ui->ImageType_Adjustment_colon_label->hide();
        ui->ImageType_Adjustment_label->hide();
        ui->More_BW_label->hide();
        ui->More_Gray_label->hide();
    }else {
        ui->ImageType_Adjustment_colon_label->show();
        ui->ImageType_Adjustment_label->show();
        ui->More_BW_label->show();
        ui->More_Gray_label->show();
    }
    changed = false;
    return true;
}
void ImageTypeSettingsDialog::add_item(int32_t item_list[], int32_t list_size){
    int i = 0;
    while(i < list_size){
        if(item_list[i] == AutoColorPixelTypeMono){
            ui->Detection_Color_Auto_comboBox->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_075, AutoColorPixelTypeMono);
        }else if(item_list[i] == AutoColorPixelTypeGray){
            ui->Detection_Color_Auto_comboBox->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_076, AutoColorPixelTypeGray);
        }else if(item_list[i] == AutoColorPixelTypeAuto){
            ui->Detection_Color_Auto_comboBox->insertItem(i, TranslationString::GetString().translation_str.MAINSETTING_081, AutoColorPixelTypeAuto);
        }
        i++;
    }
}
void ImageTypeSettingsDialog::select_item(INT_SETTING_VALUE image_type_auto_para){
    int list_size = image_type_auto_para.capability.countOfList;
    int i = 0;
    while(i < list_size){
        if(image_type_auto_para.capability.list[i] == image_type_auto_para.select){
            ui->Detection_Color_Auto_comboBox->setCurrentIndex(i);
        }
        i++;
    }
}
void ImageTypeSettingsDialog::select_level(INT_SETTING_VALUE image_type_auto_lv_para)
{
    ui->ImageType_Adjustment_horizontalSlider->setValue(image_type_auto_lv_para.select);
}
void ImageTypeSettingsDialog::onValueChanged(int value)
{
    QObject* obj = sender();
    if(obj == ui->Detection_Color_Auto_comboBox){
        this->item_event(value);
    }else if(obj == ui->ImageType_Adjustment_horizontalSlider){
        this->item_event_slider(value);
    }
}
void ImageTypeSettingsDialog::item_event(int value)
{
    QVariant select_item = ui->Detection_Color_Auto_comboBox->itemData(value);
    bool enabled = false;
    if(select_item == AutoColorPixelTypeMono){
        enabled = false;
        current_item = AutoColorPixelTypeMono;
    }else if(select_item == AutoColorPixelTypeGray){
        enabled = false;
        current_item = AutoColorPixelTypeGray;
    }else if(select_item == AutoColorPixelTypeAuto){
        enabled = true;
        current_item = AutoColorPixelTypeAuto;
    }
    ui->ImageType_Adjustment_horizontalSlider->setEnabled(enabled);
    ui->More_BW_label->setEnabled(enabled);
    ui->More_Gray_label->setEnabled(enabled);
    ui->ImageType_Adjustment_label->setEnabled(enabled);
    ui->ImageType_Adjustment_colon_label->setEnabled(enabled);
    changed = true;
}
void ImageTypeSettingsDialog::item_event_slider(int value)
{
    current_value = value;
    changed = true;
}
AutoColorPixelType ImageTypeSettingsDialog::get_currentItem()
{
    return current_item;
}
int ImageTypeSettingsDialog::get_currentValue()
{
    return current_value;
}
