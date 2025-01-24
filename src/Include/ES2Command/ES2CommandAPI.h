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
//  ES2CommandAPI.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#define _UNICODE_ESSCANNER 
#if defined(ES2COMMAND_EXPORTS)
#define ESSCANNER_API __declspec(dllexport)
#elif defined(ES2COMMAND_EXPORTS)
#define ESSCANNER_API __declspec(dllimport)
#else
#define ESSCANNER_API 
#endif
#include "ESCommandProperties.h"
#include "ESPropertyKeys.h"
#include "IESScanner.h"
#include "IESScannedImage.h"
extern "C" {
 ESSCANNER_API ESErrorCode ESCreateScanner( ESCommandType eCommandType, IESScanner** ppScanner );
};
typedef ESErrorCode (*PFN_CREATE_SCANNER )( ESCommandType eCommandType, IESScanner** ppScanner );
