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
//  PagesTobeScanned.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "PagesTobeScanned.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void PagesTobeScanned::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void PagesTobeScanned::Reset()
{
 current_ = 0;
}
void PagesTobeScanned::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void PagesTobeScanned::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
 capability.minValue = 0;
 capability.maxValue = 9999;
 capability.allMinValue = 0;
 capability.allMaxValue = 9999;
}
ESDictionary PagesTobeScanned::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 dict[kESPagesToBeScanned] = (ESNumber)current_;
 return dict;
}
}
