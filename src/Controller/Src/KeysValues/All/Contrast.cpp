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
//  Contrast.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Contrast.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void Contrast::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void Contrast::Reset()
{
 current_ = 0;
 ESNumber currentContast;
 Scanner* scannerSupportContrast = dataProvider_->GetScanner().get();
 if(scannerSupportContrast && scannerSupportContrast->GetValueForKey(kESContrast, currentContast)) {
  isSupportContarastCommand_ = true;
 }else{
  isSupportContarastCommand_ = false;
 }
}
void Contrast::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void Contrast::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
 capability.supportLevel = kSDISupportLevelAvailable;
 if (GetValueInt(kSDIColorTypeKey) == kSDIColorTypeMono1)
 {
  capability.minValue = 0;
  capability.maxValue = 0;
  capability.supportLevel= kSDISupportLevelUnavailable;
 }else
 {
  capability.minValue = 0;
  capability.maxValue = 100;
  capability.supportLevel= kSDISupportLevelAvailable;
 }
 capability.allMinValue = 0;
 capability.allMaxValue = 100;
}
ESDictionary Contrast::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 if(isSupportContarastCommand_) {
  dict[kESContrast] = (ESNumber)current_;
 }
 return dict;
}
bool Contrast::IsSupportContrastCommand()
{
 return isSupportContarastCommand_;
}
}
