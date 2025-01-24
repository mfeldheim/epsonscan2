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
//  PaperDeskew.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "PaperDeskew.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
#include "ESIMP2.hpp"
namespace epsonscan {
void PaperDeskew::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void PaperDeskew::Reset()
{
 current_ = true;
 adf_ = nullptr;
}
void PaperDeskew::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
bool PaperDeskew::IsAutoDeskewForWhiteBGEnabled()
{
 if ( ESIMP2::IsESIMP2Available() == false)
 {
  return false;
 }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder &&
  GetValueInt(kSDIBackgroundColorKey) == kSDIBackgroundColorWhite)
 {
  double maxScanAreaInch = GetValueInt(kSDIMaxScanAreaHeightKey) / 100.0;
  double scanAreaInch = GetValueInt(kSDIScanAreaHeightKey) / GetValueInt(kSDIResolutionKey);
  if (scanAreaInch > maxScanAreaInch || GetValueInt(kSDIPaperEndDetectionKey))
  {
   return false;
  }
  return current_;
 }
 return false;
}
void PaperDeskew::GetADFCapability(SDICapability &capability)
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
 if(scanner && scanner->GetAvailableValueForKey(kESSkewCorrection, available, kESFunctionalUnitDocumentFeeder)) {
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
void PaperDeskew::GetCapability(SDICapability &capability)
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
ESDictionary PaperDeskew::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 dict[kESSkewCorrection] = (bool)current_;
 return dict;
}
}
