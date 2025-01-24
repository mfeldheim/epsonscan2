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
//  SkipBlankPage.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "SkipBlankPage.hpp"
#include "Scanner.hpp"
#include "DTR.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void SkipBlankPage::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void SkipBlankPage::Reset()
{
 current_ = 10;
 ESNumber currentBlankPageLevel;
 Scanner* scannerSupportBlankPageLevel = dataProvider_->GetScanner().get();
 if(scannerSupportBlankPageLevel && scannerSupportBlankPageLevel->GetValueForKey(kESDetectBlankPageLevel, currentBlankPageLevel)) {
  isSupportHardwareBlankPageLevel_ = true;
 }else{
  isSupportHardwareBlankPageLevel_ = false;
 }
}
void SkipBlankPage::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void SkipBlankPage::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
 capability.minValue = 0;
 capability.maxValue = 30;
 capability.allMinValue = 0;
 capability.allMaxValue = 30;
 bool hasAdf = false;
 ESIndexSet functionalUnits = dataProvider_->GetScanner().get()->GetSupportedFunctionalUnit();
 if (functionalUnits.find(kESFunctionalUnitDocumentFeeder) != functionalUnits.end())
 {
  hasAdf = true;
 }
 if ((DTR::IsDTRAvailable() || isSupportHardwareBlankPageLevel_ == true) && hasAdf)
 {
  capability.supportLevel = kSDISupportLevelAvailable;
  if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
  {
   capability.supportLevel = kSDISupportLevelUnavailable;
   ResetRange(capability);
  }
 }else{
  capability.supportLevel = kSDISupportLevelNone;
 }
}
ESDictionary SkipBlankPage::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 if(isSupportHardwareBlankPageLevel_ == true && GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder
  && GetValueInt(kSDIBlankPageSkipKey))
 {
  dict[kESDetectBlankPageLevel] = (ESNumber)current_;
 }
 return dict;
}
bool SkipBlankPage::IsSupportBlankPageLevel()
{
 return isSupportHardwareBlankPageLevel_;
}
}
