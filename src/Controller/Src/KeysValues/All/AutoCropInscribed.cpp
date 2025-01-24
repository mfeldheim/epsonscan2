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
//  AutoCropInscribed.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "AutoCropInscribed.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void AutoCropInscribed::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void AutoCropInscribed::Reset()
{
 SDICapability cap;
 GetCapability(cap);
 if (cap.supportLevel != kSDISupportLevelNone)
 {
  current_ = true;
 }else{
  current_ = false;
 }
 adf_ = nullptr;
}
void AutoCropInscribed::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void AutoCropInscribed::GetADFCapability(SDICapability &capability)
{
 if (adf_)
 {
  capability = *adf_;
  return;
 }
 std::unique_ptr<SDICapability> adfCap(new SDICapability());
 SetDefaultListCapability(*adfCap);
 adfCap->supportLevel = kSDISupportLevelNone;
 ESIndexSet available;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESAutoCroppingInscribed, available, kESFunctionalUnitDocumentFeeder)) {
  if (available.find(true) != available.end())
     {
   AddList(*adfCap, true);
   AddList(*adfCap, false);
   AddAllList(*adfCap, true);
   AddAllList(*adfCap, false);
   adfCap->supportLevel = kSDISupportLevelAvailable;
  }else{
   AddList(*adfCap, false);
   AddAllList(*adfCap, false);
  }
 }
 capability = *adfCap;
 adf_.swap(adfCap);
}
void AutoCropInscribed::GetCapability(SDICapability &capability)
{
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
 {
  GetADFCapability(capability);
  return;
 }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
 {
  SDICapability adfCap;
  GetADFCapability(adfCap);
  if (adfCap.supportLevel != kSDISupportLevelNone)
  {
   capability.supportLevel = kSDISupportLevelUnavailable;
  }else{
   capability.supportLevel = kSDISupportLevelNone;
  }
  ResetList(capability);
  return;
 }
}
ESDictionary AutoCropInscribed::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
