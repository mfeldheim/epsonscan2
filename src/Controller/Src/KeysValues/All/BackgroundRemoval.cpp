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
//  BackgroundRemoval.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "BackgroundRemoval.hpp"
#include "Scanner.hpp"
#include "Lut.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void BackgroundRemoval::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void BackgroundRemoval::Reset()
{
 ESNumber kind = kPrvHRD_Kind_SF_Document;
 dataProvider_->GetModelInfo()->GetValue(kPrvHRD_Kind, kind);
 if(kind == kPrvHRD_Kind_MF_LFP)
 {
  current_ = kSDIBackgroundRemovalNormal;
 }else{
  current_ = kSDIBackgroundRemovalNone;
 }
}
void BackgroundRemoval::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void BackgroundRemoval::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 capability.supportLevel = kSDISupportLevelNone;
 ESIndexSet availableBackgroundRemovalTypes;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESBackgroundRemoval, availableBackgroundRemovalTypes)) {
  AddList(capability, kSDIBackgroundRemovalNone);
  AddList(capability, kSDIBackgroundRemovalNormal);
  AddList(capability, kSDIBackgroundRemovalHigh);
  capability.supportLevel = kSDISupportLevelAvailable;
  AddAllList(capability, kSDIBackgroundRemovalNone);
  AddAllList(capability, kSDIBackgroundRemovalNormal);
  AddAllList(capability, kSDIBackgroundRemovalHigh);
 }else if (Lut::isFitPluginAvailable())
 {
  ESIndexSet availableColorTypes;
  if (GetValueInt(kSDIColorTypeKey) != kSDIColorTypeMono1)
  {
   AddList(capability, kSDIBackgroundRemovalNone);
   AddList(capability, kSDIBackgroundRemovalNormal);
   AddList(capability, kSDIBackgroundRemovalHigh);
   capability.supportLevel = kSDISupportLevelAvailable;
  }else
  {
   capability.supportLevel = kSDISupportLevelUnavailable;
  }
  AddAllList(capability, kSDIBackgroundRemovalNone);
  AddAllList(capability, kSDIBackgroundRemovalNormal);
  AddAllList(capability, kSDIBackgroundRemovalHigh);
 }
}
ESDictionary BackgroundRemoval::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 ESIndexSet availableBackgroundRemovalTypes;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESBackgroundRemoval, availableBackgroundRemovalTypes)) {
  ENUM_ES_BACKGROUNDREMOVAL_LEVEL backgroundRemovalLevel = kESBackgroundRemovalLevelOff;
  if(current_ == kSDIBackgroundRemovalNone)
  {
   backgroundRemovalLevel = kESBackgroundRemovalLevelOff;
  }
  else if(current_ == kSDIBackgroundRemovalNormal)
  {
   backgroundRemovalLevel = kESBackgroundRemovalLevelLow;
  }
  else if(current_ == kSDIBackgroundRemovalHigh)
  {
   backgroundRemovalLevel = kESBackgroundRemovalLevelHigh;
  }
  dict[kESBackgroundRemoval] = (ESNumber)backgroundRemovalLevel;
 }
 return dict;
}
}
