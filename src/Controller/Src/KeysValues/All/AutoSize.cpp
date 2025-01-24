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
//  AutoSize.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "AutoSize.hpp"
#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include "DTR.hpp"
#include "ESIMP2.hpp"
#include "PaperDeskew.hpp"
#include "Brightness.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void AutoSize::SetValue(const SDIInt& intVal)
{
 SDI_TRACE_LOG("SetValue = %d", intVal);;
 SDICapability cap = {0};
 GetCapability(cap);
 if (cap.supportLevel != kSDISupportLevelNone)
 {
  current_ = intVal;
 }else{
  current_ = kSDIAutoSizeNone;
 }
}
void AutoSize::Reset()
{
 SDICapability cap = {0};
 GetCapability(cap);
 if (cap.supportLevel != kSDISupportLevelNone)
 {
  if(GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed && IsSoftwareAvailable())
  {
   current_ = kSDIAutoSizeNone;
  }else{
   current_ = kSDIAutoSizeStandard;
  }
 }
 else
 {
  current_ = kSDIAutoSizeNone;
 }
}
void AutoSize::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
bool AutoSize::IsDetectedDocumentSizeAvailable(ESFunctionalUnitType funcUnit)
{
 ST_ES_SIZE_F detectedSize = {0};
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner->GetValueForKey(kESDetectedDocumentSize, detectedSize, funcUnit))
 {
  return true;
 }
 return false;
}
bool AutoSize::IsHardwareAvailable()
{
 SDI_TRACE_LOG("Enter");
 Scanner* scanner = dataProvider_->GetScanner().get();
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
 {
  return IsCRPAvailable() || IsDetectedDocumentSizeAvailable(kESFunctionalUnitDocumentFeeder);
 }else{
  return IsDetectedDocumentSizeAvailable(kESFunctionalUnitFlatbed);
 }
 SDI_TRACE_LOG("Leave false");
  return false;
}
bool AutoSize::IsCRPAvailable()
{
 ESIndexSet availaleValues;
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetAvailableValueForKey(kESAutoCropping, availaleValues, kESFunctionalUnitDocumentFeeder);
 if (availaleValues.find(true) != availaleValues.end()) {
  SDI_TRACE_LOG("Enter true");
  return true;
 }
 else
 {
  SDI_TRACE_LOG("Leave false");
  return false;
 }
}
bool AutoSize::IsAdvancedSotwareAutoCropEnabled()
{
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed && IsSoftwareAvailable())
 {
  if (current_ == kSDIAutoSizeStandard)
  {
   return true;
  }
 }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder &&
  IsCRPAvailable() &&
  GetValueInt(kSDIBackgroundColorKey) == kSDIBackgroundColorWhite)
 {
  if (current_ == kSDIAutoSizeStandard || current_ == kSDIAutoSizeLongPaper)
  {
   return true;
  }
 }
 PaperDeskew* paperDeskew = (PaperDeskew*)dataProvider_->GetKeyInstance(kSDIPaperDeskewKey).get();
 if (paperDeskew)
 {
  if (paperDeskew->IsAutoDeskewForWhiteBGEnabled())
  {
   return true;
  }
 }
 return false;
}
bool AutoSize::IsSoftwareAvailable()
{
 SDI_TRACE_LOG("Enter");
    Brightness* brigtness = (Brightness*)dataProvider_->GetKeyInstance(kSDIBrightnessKey).get();
    if (brigtness && brigtness->IsSupportBrightnessCommand())
  {
  SDI_TRACE_LOG("Leave false");
      return false;
    }
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
 {
  ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
  if (modelInfo)
  {
   ESNumber autoSize = false;
   if (modelInfo->GetValue(kPrvHRD_SWAutoSize, autoSize) == false)
   {
    autoSize = false;
   }
   SDI_TRACE_LOG("Get kPrvHRD_SWAutoSize  = %d", autoSize);
   return autoSize && DTR::IsDTRAvailable();
  }
 }else{
  ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
  if (modelInfo)
  {
   ESNumber autoSize = false;
   if (modelInfo->GetValue(kPrvHRD_SWAutoSizeFlatbed, autoSize) == false)
   {
    autoSize = false;
   }
   SDI_TRACE_LOG("Get kPrvHRD_SWAutoSizeFlatbed  = %d", autoSize);
   return autoSize == kPrvHRD_SWAutoSizeFlatbed_Support_Advanced && ESIMP2::IsESIMP2Available();
  }
 }
 SDI_TRACE_LOG("Leave false");
 return false;
}
bool AutoSize::IsLongPaperAvailable()
{
 if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
 {
  ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
  if (modelInfo)
  {
   ESNumber autoSize;
   modelInfo->GetValue(kPrvHRD_AutoDetectLongPaper, autoSize);
   return autoSize;
  }
 }
 return false;
}
void AutoSize::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 capability.supportLevel = kSDISupportLevelNone;
 if (IsSoftwareAvailable() || IsHardwareAvailable())
 {
  AddList(capability, kSDIAutoSizeStandard);
  AddList(capability, kSDIAutoSizeNone);
  AddAllList(capability, kSDIAutoSizeStandard);
  AddAllList(capability, kSDIAutoSizeNone);
  if (IsLongPaperAvailable() && IsSoftwareAvailable() )
  {
   AddList(capability, kSDIAutoSizeLongPaper);
   AddAllList(capability, kSDIAutoSizeLongPaper);
  }
  capability.supportLevel = kSDISupportLevelAvailable;
 }else{
  AddList(capability, kSDIAutoSizeNone);
  AddAllList(capability, kSDIAutoSizeNone);
 }
}
ESDictionary AutoSize::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 processSoftwareAutoCrop_ = false;
 if (IsAdvancedSotwareAutoCropEnabled())
 {
  ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
  if (modelInfo && GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
  {
   ESNumber reduceBrightness = 11111;
   modelInfo->GetValue(kPrvHRD_ReduceBirightness, reduceBrightness);
   dict[kESLightIntensityFB] = reduceBrightness;
  }
 }
 else if (current_ == kSDIAutoSizeStandard && IsCRPAvailable() && GetValueInt(kSDIFunctionalUnitKey) != kSDIFunctionalUnitFlatbed)
 {
  bool autoCropInscribed = (GetValueInt(kSDIAutoCroppingInscribedKey) == 1);
  if (autoCropInscribed)
  {
   dict[kESAutoCroppingInscribed] = (bool)true;
  }else{
   dict[kESAutoCropping] = (bool)true;
  }
 }
 else if (current_ == kSDIAutoSizeStandard && IsCRPAvailable() == false && IsSoftwareAvailable() && GetValueInt(kSDIFunctionalUnitKey) != kSDIFunctionalUnitFlatbed)
 {
  dict[kESAutoCropping] = (bool)false;
  processSoftwareAutoCrop_ = true;
 }
 else{
  dict[kESAutoCropping] = (bool)false;
  ESNumber kind = kPrvHRD_Kind_SF_Document;
  dataProvider_->GetModelInfo()->GetValue(kPrvHRD_Kind,kind);
  if(kind == kPrvHRD_Kind_MF_LFP)
  {
   dict[kESPaperEndDetection] = (bool)true;
  }
 }
 return dict;
}
}
