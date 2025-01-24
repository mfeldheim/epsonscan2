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
//  acpowercombobox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
ACPowerComboBox::ACPowerComboBox(QWidget *parent) :
    QComboBox(parent)
{
    this->initialize(t_Off);
}
void ACPowerComboBox::initialize(Time default_item){
    changed = true;
    enabled = true;
    current_item = default_item;
}
void ACPowerComboBox::update_ui(INT_SETTING_VALUE power_of_time_para){
    if(changed == true){
        this->clear();
        this->set_enabled(enabled);
        this->add_item(power_of_time_para.capability.list, power_of_time_para.capability.countOfAllList);
        this->select_item(current_item);
        changed = false;
    }
}
void ACPowerComboBox::set_enabled(bool enabled){
    if(enabled == true){
        this->setEnabled(true);
    }else {
        this->setEnabled(false);
    }
}
void ACPowerComboBox::add_item(int32_t item_list[], int32_t list_size)
{
    int i = 0;
    int item_num = 0;
    while(i < list_size){
        if(item_list[i] == t_Off){
            this->insertItem(item_num, TranslationString::GetString().translation_str.ES2U_MAIN_025, t_Off);
            item_num++;
        }else if(item_list[i] == t_3){
            this->insertItem(item_num, "3", t_3);
            item_num++;
        }else if(item_list[i] == t_5){
            this->insertItem(item_num, "5", t_5);
            item_num++;
        }else if(item_list[i] == t_10){
            this->insertItem(item_num, "10", t_10);
            item_num++;
        }else if(item_list[i] == t_15){
            this->insertItem(item_num, "15", t_15);
            item_num++;
        }else if(item_list[i] == t_30){
            this->insertItem(item_num, "30", t_30);
            item_num++;
        }else if(item_list[i] == t_60){
            this->insertItem(item_num, "60", t_60);
            item_num++;
        }else if(item_list[i] == t_120){
            this->insertItem(item_num, "120", t_120);
            item_num++;
        }else if(item_list[i] == t_240){
            this->insertItem(item_num, "240", t_240);
            item_num++;
        }else if(item_list[i] == t_480){
            this->insertItem(item_num, "480", t_480);
            item_num++;
        }else if(item_list[i] == t_720){
            this->insertItem(item_num, "720", t_720);
            item_num++;
        }
        i++;
    }
}
void ACPowerComboBox::select_item(Time select)
{
    this->setCurrentIndex(this->findData(current_item));
}
void ACPowerComboBox::item_event(int value)
{
    QVariant select_item = this->itemData(value);
    if(select_item == t_Off){
        current_item = t_Off;
    }else if(select_item == t_3){
        current_item = t_3;
    }else if(select_item == t_5){
        current_item = t_5;
    }else if(select_item == t_10){
        current_item = t_10;
    }else if(select_item == t_15){
        current_item = t_15;
    }else if(select_item == t_30){
        current_item = t_30;
    }else if(select_item == t_60){
        current_item = t_60;
    }else if(select_item == t_120){
        current_item = t_120;
    }else if(select_item == t_240){
        current_item = t_240;
    }else if(select_item == t_480){
        current_item = t_480;
    }else if(select_item == t_720){
        current_item = t_720;
    }
    changed = true;
}
Time ACPowerComboBox::get_current_item(void)
{
    return current_item;
}
