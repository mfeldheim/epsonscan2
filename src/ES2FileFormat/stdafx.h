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
//  stdafx.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "targetver.h"
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif
#ifndef WIN32
#include "Platform.h"
#endif
#include "ESCommonTypedef.h"
#include "ESproperty.h"
#include "ESBuffer.h"
#include "ESJsonUtils.h"
#include "ESImageInfo.h"
#include "FileFormatKitErrors.h"
#include "DbgLog.h"
#ifdef _DEBUG
 #define _CRTDBG_MAP_ALLOC
 #include <stdlib.h>
 #include <crtdbg.h>
 #define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
 #define safeNew DBG_NEW
#else
#define safeNew new (std::nothrow)
#endif
