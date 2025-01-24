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
//  DeficiencyCorrection.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "DeficiencyCorrection.hpp"
#include "Scanner.hpp"
#include "Lut.hpp"
#include "ESIMP2.hpp"
#include "Brightness.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void DeficiencyCorrection::SetValue(const SDIInt& intVal)
{
 SDICapability cap;
 GetCapability(cap);
 if (cap.supportLevel != kSDISupportLevelNone)
 {
  current_ = intVal;
 }
}
void DeficiencyCorrection::Reset()
{
 current_ = 0;
}
void DeficiencyCorrection::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void DeficiencyCorrection::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 capability.supportLevel = kSDISupportLevelNone;
 Brightness* brigtness = (Brightness*)dataProvider_->GetKeyInstance(kSDIBrightnessKey).get();
 if (brigtness && brigtness->IsSupportBrightnessCommand())
 {
  capability.supportLevel = kSDISupportLevelNone;
  return;
 }
 ESNumber imageCorrectionSupport = (ESNumber)kPrvHRD_ImageDefectCorrection_NotSupport;
 dataProvider_->GetModelInfo()->GetValue(kPrvHRD_ImageDefectCorrection, imageCorrectionSupport);
 if(imageCorrectionSupport && ESIMP2::IsESIMP2Available())
 {
  AddList(capability, true);
  AddList(capability, false);
  AddAllList(capability, true);
  AddAllList(capability, false);
  capability.supportLevel = kSDISupportLevelAvailable;
 }else{
  capability.supportLevel = kSDISupportLevelNone;
 }
}
ESDictionary DeficiencyCorrection::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
bool DeficiencyCorrection::IsProcessDeficiencyCorrection()
{
 bool shouldProcessRmovePunchHole = false;
 SDICapability deficiencyCap = {0};
 GetCapabilityWithKey(kSDIDeficiencyCorrectionKey, deficiencyCap);
 if (deficiencyCap.supportLevel != kSDISupportLevelNone && GetValueInt(kSDIRemovePunchholeKey))
 {
  shouldProcessRmovePunchHole = true;
 }
 return GetValueInt(kSDIDeficiencyCorrectionKey) || shouldProcessRmovePunchHole;
}
}
