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
//  Brightness.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Brightness.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void Brightness::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void Brightness::Reset()
{
 current_ = 0;
 ESNumber currentBrightness;
 Scanner* scannerSupportBrightness = dataProvider_->GetScanner().get();
 if(scannerSupportBrightness && scannerSupportBrightness->GetValueForKey(kESBrightness, currentBrightness)) {
  isSupportBrigthenessCommand_ = true;
 }else{
  isSupportBrigthenessCommand_ = false;
 }
}
void Brightness::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void Brightness::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
 capability.supportLevel= kSDISupportLevelAvailable;
 ESIndexSet availableBrightnessTypes;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if (GetValueInt(kSDIColorTypeKey) == kSDIColorTypeMono1)
 {
  capability.minValue = 0;
  capability.maxValue = 0;
  capability.supportLevel = kSDISupportLevelUnavailable;
 }else
 {
  capability.minValue = 0;
  capability.maxValue = 100;
  capability.supportLevel= kSDISupportLevelAvailable;
 }
 capability.allMinValue = 0;
 capability.allMaxValue = 100;
}
ESDictionary Brightness::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 if(isSupportBrigthenessCommand_) {
  dict[kESBrightness] = (ESNumber)current_;
 }
 return dict;
}
bool Brightness::IsSupportBrightnessCommand()
{
 return isSupportBrigthenessCommand_;
}
}
