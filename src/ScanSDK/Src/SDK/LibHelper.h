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
//  LibHelper.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCANLIB.h"
void SetErrorCode(DWORD* pErrCode, DWORD ErrCode);
template <class T> T BITS_TO_BYTES(T bits)
{
 return (((bits) + 7) / 8);
}
template <class T> T BITS_TO_BYTES_DWORD_ALIGNED(T bits)
{
 return (ROUND_UP(bits, 32) / 8);
}
template <class T> T BYTES_TO_DWORD_ALIGNED(T bytes)
{
 return ROUND_UP(bytes, 4);
}
template <class T> T ROUND_UP(T value, int unit)
{
 return ((value + unit - 1) / unit * unit);
}
template <class T> T ROUND_DOWN(T value, int unit)
{
 return (value / unit * unit);
}
