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
//  Environment.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Environment.h"
#include <memory>
namespace epsonscan2 {
namespace es2command {
bool Environment::IsCommandRetry()
{
    return true;
}
bool Environment::IsAllowStatusAuthError()
{
    bool bRet = false;
#ifdef WIN32
    const DWORD ALLOW_AUTH_CODE = 1;
    DWORD dwAllowAuthError(0);
    ESErrorCode err = RegQueryDWORDValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\EPSON\\Epson Scan 2", L"AllowAuthError", &dwAllowAuthError);
    if ( IS_ERR_SUCCESS(err) && dwAllowAuthError == ALLOW_AUTH_CODE){
        bRet = true;
    }
#endif
    return bRet;
}
}
}
