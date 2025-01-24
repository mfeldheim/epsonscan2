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
//  TextEnhance.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "TextEnhance.hpp"
#include "Scanner.hpp"
#include "DDEFilter.hpp"
#include "Brightness.hpp"
#include <ES2Command/ES2CommandAPI.h>
#include <utils/PathUtils.h>
#include <utils/ESFile.h>
namespace epsonscan {
void TextEnhance::SetValue(const SDIInt& intVal)
{
 if (GetValueInt(kSDIColorTypeKey) == kSDIColorTypeMono1)
 {
  if (intVal == 2)
  {
   current_ = 1;
  }else{
   current_ = intVal;
  }
 }else{
  current_ = intVal;
 }
}
void TextEnhance::Reset()
{
 current_ = kSDITextEnhanceLevelNone;
}
void TextEnhance::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void TextEnhance::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 ESIndexSet availableColorTypes;
   capability.supportLevel = kSDISupportLevelNone;
 capability.countOfList = 0;
 ESString ddeName;
 ESString imfName;
 ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
 ESNumber isTETSupport = kPrvHRD_TextEnhancementNotSupport_Support;
 if(dataProvider_->GetModelInfo()->GetValue(kPrvHRD_TextEnhancementNotSupport, isTETSupport))
 {
  if(isTETSupport == kPrvHRD_TextEnhancementNotSupport_NotSupport)
  {
   capability.supportLevel = kSDISupportLevelNone;
   return;
  }
 }
    ESNumber kind = 0;
    if(dataProvider_->GetModelInfo()->GetValue(kPrvHRD_Kind, kind))
 {
  if(kind == kPrvHRD_Kind_MF_LFP || kind == kPrvHRD_Kind_MF_Consumer || kind == kPrvHRD_Kind_MF_Business)
  {
   capability.supportLevel = kSDISupportLevelNone;
   return;
  }
 }
 Brightness* brigtness = (Brightness*)dataProvider_->GetKeyInstance(kSDIBrightnessKey).get();
 if (brigtness && brigtness->IsSupportBrightnessCommand())
 {
  capability.supportLevel = kSDISupportLevelNone;
  return;
 }
 modelInfo->GetValue(kPrvHRD_DDEName, ddeName);
 modelInfo->GetValue(kPrvHRD_ImageFilterName, imfName);
 if (DDEFilter::IsDDEAvailable())
 {
  capability.supportLevel = kSDISupportLevelAvailable;
  capability.countOfAllList = 3;
  capability.allList[0] = kSDITextEnhanceLevelNone;
  capability.allList[1] = kSDITextEnhanceLevelStandard;
  capability.allList[2] = kSDITextEnhanceLevelHigh;
  capability.countOfList = 3;
  capability.list[0] = kSDITextEnhanceLevelNone;
  capability.list[1] = kSDITextEnhanceLevelStandard;
  capability.list[2] = kSDITextEnhanceLevelHigh;
 }
}
ESDictionary TextEnhance::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
