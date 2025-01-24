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
//  imageformatsettingscombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
ImageFormatSettingsCombobox::ImageFormatSettingsCombobox(QWidget *parent) :
    QComboBox(parent),
    changed(false),
    current_item(ImageFormatJPEG)
{
}
void ImageFormatSettingsCombobox::initialize(ImageFormat default_item){
    changed = true;
    current_item = default_item;
}
void ImageFormatSettingsCombobox::update_ui(ImageFormat img_format_list[]){
    if(changed == true){
        this->clear();
        this->set_enabled(true);
        this->add_item(img_format_list);
        this->select_item();
        changed = false;
    }
}
void ImageFormatSettingsCombobox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void ImageFormatSettingsCombobox::add_item(ImageFormat img_format_list[])
{
    int i = 0;
    while(1){
        if(img_format_list[i] == ImageFormatPNM){
            this->insertItem(i, TranslationString::GetString().translation_str.LINUX_FILESAVESETTING_009, ImageFormatPNM);
            i++;
        }else if(img_format_list[i] == ImageFormatJPEG){
            this->insertItem(i, TranslationString::GetString().translation_str.FILESAVESETTING_003, ImageFormatJPEG);
            i++;
        }else if(img_format_list[i] == ImageFormatPNG){
            this->insertItem(i, TranslationString::GetString().translation_str.FILESAVESETTING_004, ImageFormatPNG);
            i++;
        }else if(img_format_list[i] == ImageFormatTIFF){
            this->insertItem(i, TranslationString::GetString().translation_str.FILESAVESETTING_005, ImageFormatTIFF);
            i++;
        }else if(img_format_list[i] == ImageFormatMultiTIFF){
            this->insertItem(i, TranslationString::GetString().translation_str.FILESAVESETTING_006, ImageFormatMultiTIFF);
            i++;
        }else if(img_format_list[i] == ImageFormatColorJpegMonoRaw){
            this->insertItem(i, TranslationString::GetString().translation_str.FILESAVESETTING_007, ImageFormatColorJpegMonoRaw);
            i++;
        }else if(img_format_list[i] == ImageFormatOFD){
            this->insertItem(i, "OFD", ImageFormatOFD);
            i++;
        }else if(img_format_list[i] == OPTIONS){
            break;
        }
    }
}
void ImageFormatSettingsCombobox::select_item()
{
    this->setCurrentIndex(this->findData(current_item));
}
void ImageFormatSettingsCombobox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == ImageFormatJPEG){
        current_item = ImageFormatJPEG;
    }else if(select_item == ImageFormatTIFF){
        current_item = ImageFormatTIFF;
    }else if(select_item == ImageFormatMultiTIFF){
        current_item = ImageFormatMultiTIFF;
    }else if(select_item == ImageFormatColorJpegMonoRaw){
        current_item = ImageFormatColorJpegMonoRaw;
    }else if(select_item == ImageFormatPNG){
        current_item = ImageFormatPNG;
    }else if(select_item == ImageFormatPNM){
        current_item = ImageFormatPNM;
    }else if(select_item == ImageFormatOFD){
        current_item = ImageFormatOFD;
    }
    changed = true;
}
void ImageFormatSettingsCombobox::get_current_item(ImageFormat* select)
{
    *select = current_item;
}
