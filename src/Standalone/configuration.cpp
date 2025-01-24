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
//  configuration.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "configuration.h"
static Configuration config;
Configuration::Configuration()
{
    this->config_para.units = unit_inchi;
    this->config_para.last_used_settings = true;
    this->config_para.used_default_settings = false;
    this->config_para.compression = true;
    this->config_para.open_img_folder = true;
    this->config_para.quality_preview = false;
    this->config_para.preview_resolution = 50;
    this->config_para.preview_immediately_resolution = 50;
    this->config_para.ac_power = t_Off;
    this->config_para.usb_power = t_Off;
    this->config_para.roller_kit_counter = 0;
    this->config_para.roller_counter = 0;
    this->config_para.retard_roller_counter = 0;
    this->config_para.sleep_timer = 240;
    this->config_para.WindowPositionX = INIT_POSITION_X;
    this->config_para.WindowPositionY = INIT_POSITION_Y;
    this->config_para.WindowWidth = INIT_MAINWINDOW_WIDTH;
    this->config_para.WindowHeight = INIT_MAINWINDOW_HEIGHT;
    this->config_para.sensor_glass_dirtsensitivity = SensorGlassDirtSensitivityOff;
    this->config_para.adf_paper_protection = ADFPaperProtection_Off;
    this->config_para.behavior_when_doublefeed = BehaviorWhenDoubleFeed_Immediately;
    this->config_para.direct_power_on = DirectPowerOn_Off;
    this->config_para.non_connect_poweroff = NonConnectPowerOff_Off;
}
Configuration& Configuration::GetConfiguration()
{
    return config;
}
void Configuration::SetConfiguration(CONFIGURATION _config)
{
    this->config_para = _config;
}
