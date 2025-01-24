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
//  ESL_SAMPLE.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Platform.h"
#define OPTION_SCAN "--scan"
#define OPTION_SCAN_S "-s"
#define OPTION_MODE "--mode"
#define OPTION_SOURCE "--source"
#define OPTION_SCAN_AREA "--scan-area"
#define OPTION_RESOLUTION "--resolution"
#define OPTION_ROTATE "--rotate"
#define OPTION_BRIGHTNESS "--brightness"
#define OPTION_CONTRAST "--contrast"
#define OPTION_THRESHOLD "--threshold"
#define OPTION_DROPOUT "--dropout"
#define OPTION_BLANKPAGE_SKIP "--blankpage-skip"
#define OPTION_DOUBLE_FEED_DETECTION "--double-feed-detection"
#define OPTION_IMAGE_FORMAT "--image-format"
#define OPTION_GET_STATUS "--get-status"
#define OPTION_GET_STATUS_S "-gs"
#define OPTION_GET_SLEEPTIMER "--get-sleeptimer"
#define OPTION_SET_SLEEPTIMER "--set-sleeptimer"
#define OPTION_GET_AUTOPWOFF "--get-autopwoff"
#define OPTION_SET_AUTOPWOFF "--set-autopwoff"
#define MIN_ARGUMENTS 2
typedef enum _checkOption {
 CO_DEVICEID = 0,
 CO_VALUE = 1,
} checkOption;
typedef enum _connectionMethod {
 CM_USB = 0,
 CM_NETWORK = 1,
} connectionMethod;
void DISPLAY_DEVICE_STATUS(DWORD Code);
