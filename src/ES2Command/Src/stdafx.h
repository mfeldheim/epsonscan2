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

       
#include <sys/socket.h>
#include <assert.h>
#include "Platform.h"
#include "CommonUtility/ESCommonTypedef.h"
#include "Include/ES2Command/ESCommandProperties.h"
#include "CommonUtility/utils/ESAnyCastUtils.h"
#include "Utils/ESDebugLog.h"
inline bool IS_ERR_SUCCESS( ESErrorCode err )
{
 return ( err == kESErrorNoError );
}
inline bool IS_ERR_CODE( ESErrorCode err )
{
 return ( err != kESErrorNoError );
}
inline bool IsEnableDumpCommand()
{
 return ( AfxGetLog()->IsEnableDumpCommand() ? true : false );
}
#ifndef WIN32
#ifndef __in
#define __in 
#endif
#ifndef __out
#define __out 
#endif
#ifndef __inout
#define __inout 
#endif
#ifndef __in_opt
#define __in_opt 
#endif
#ifndef __out_opt
#define __out_opt 
#endif
#endif
