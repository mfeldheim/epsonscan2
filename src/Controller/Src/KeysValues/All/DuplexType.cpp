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
//  DuplexType.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "DuplexType.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void DuplexType::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void DuplexType::Reset()
{
 current_ = false;
 hasCache_ = false;
 isDuplexAvailable_ = false;
 if (hasCache_ == false)
 {
  isDuplexAvailable_= false;
  ESIndexSet available;
  Scanner* scanner = dataProvider_->GetScanner().get();
  if(scanner && scanner->GetAvailableValueForKey(kESDuplex, available, kESFunctionalUnitDocumentFeeder)) {
   if (available.find(true) != available.end())
   {
    isDuplexAvailable_ = true;
    SDIDuplexType duplexType = (SDIDuplexType)GetValueInt(kSDIADFDuplexTypeKey);
    SDIScannerKind kind = (SDIScannerKind)GetValueInt(KSDIScannerKindKey);
    if (kind == kSDIKindSFDocument && duplexType == kSDIADFDuplexType1Pass)
    {
     current_ = true;
    }else{
     current_ = false;
    }
   }
  }
  hasCache_ = true;
 }
}
void DuplexType::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void DuplexType::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
   capability.supportLevel = kSDISupportLevelNone;
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
 {
  if (isDuplexAvailable_)
  {
   AddList(capability, true);
   AddList(capability, false);
   AddAllList(capability, true);
   AddAllList(capability, false);
   capability.supportLevel = kSDISupportLevelAvailable;
  }else
  {
   capability.supportLevel = kSDISupportLevelNone;
  }
 }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
 {
  if (isDuplexAvailable_)
  {
   AddAllList(capability, true);
   AddAllList(capability, false);
   capability.supportLevel = kSDISupportLevelUnavailable;
  }else{
   capability.supportLevel = kSDISupportLevelNone;
  }
 }
}
ESDictionary DuplexType::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 SDICapability cap;
 GetCapability(cap);
 if (cap.supportLevel == kSDISupportLevelUnavailable)
 {
  dict[kESDuplex] = (bool)false;
  return dict;
 }
 dict[kESDuplex] = (bool)current_;
 return dict;
}
}
