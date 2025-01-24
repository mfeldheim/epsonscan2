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
//  DoubleFeedDetection.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "DoubleFeedDetection.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void DoubleFeedDetection::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void DoubleFeedDetection::Reset()
{
 current_ = true;
}
void DoubleFeedDetection::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void DoubleFeedDetection::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
   capability.supportLevel = kSDISupportLevelNone;
 ESIndexSet available;
 SDICapability levelCapability;
 GetCapabilityWithKey(std::string(kSDIDoubleFeedDetectionLevelKey), levelCapability);
 if (levelCapability.supportLevel != kSDISupportLevelNone)
 {
  AddList(capability, true);
  AddList(capability, false);
  AddAllList(capability, true);
  AddAllList(capability, false);
  capability.supportLevel = kSDISupportLevelAvailable;
 }else{
  ResetList(capability);
 }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
 {
  if (levelCapability.supportLevel == kSDISupportLevelAvailable || levelCapability.supportLevel == kSDISupportLevelUnavailable)
  {
   capability.supportLevel = kSDISupportLevelUnavailable;
  }
  if (levelCapability.supportLevel == kSDISupportLevelNone)
  {
   capability.supportLevel = kSDISupportLevelNone;
  }
  ResetList(capability);
 }
}
ESDictionary DoubleFeedDetection::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
