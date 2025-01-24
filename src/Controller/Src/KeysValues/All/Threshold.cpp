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
//  Threshold.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Threshold.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void Threshold::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void Threshold::Reset()
{
 current_ = 110;
}
void Threshold::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void Threshold::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 capability.supportLevel= kSDISupportLevelAvailable;
 if (GetValueInt(kSDIColorTypeKey) != kSDIColorTypeMono1)
 {
  capability.minValue = 0;
  capability.maxValue = 0;
  capability.supportLevel= kSDISupportLevelUnavailable;
 }
 capability.allMinValue = 0;
 capability.allMaxValue = 255;
}
ESDictionary Threshold::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
