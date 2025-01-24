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

       
#include "ESCommonTypedef.h"
#include "ESCommandProperties.h"
#include "DbgLog.h"
#include "utils/ESAnyCastUtils.h"
#include "utils/PathUtils.h"
#include "utils/ESJsonUtils.h"
#include "utils/ESFile.h"
#include "boost/format.hpp"
#define ES_TRACE_LOG(msg,...) ES_Trace_Log2( __FUNCTION__, msg, ##__VA_ARGS__ );
#define ES_LOG_TRACE_FUNC() ES_TRACE_LOG( ES_STRING("ENTER : %s"), __FUNCTION__ )
#define ES_LOG_LEAVE_FUNC() ES_TRACE_LOG( ES_STRING("LEAVE : %s"), __FUNCTION__ )
inline bool IsEnableDumpCommand(){
 return false;
}
#define ES_INFO_LOG(msg,...) printf
