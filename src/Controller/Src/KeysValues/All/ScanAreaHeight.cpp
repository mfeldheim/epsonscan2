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
//  ScanAreaHeight.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ScanAreaHeight.hpp"
#include "Scanner.hpp"
#include "Resolution.hpp"
#include "AutoSize.hpp"
#include "PaperDeskew.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void ScanAreaHeight::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void ScanAreaHeight::Reset()
{
 current_ = 11.4 * 200;
}
void ScanAreaHeight::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void ScanAreaHeight::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
}
void ScanAreaHeight::UpdateScanAreaWithDetectedSize(ESFunctionalUnitType funcUnit, ESDictionary& dict)
{
 ST_ES_SIZE_F detectedSize = {0};
 dataProvider_->GetScanner()->GetValueForKey(kESDetectedDocumentSize, detectedSize, funcUnit);
   if (detectedSize.cx < 1 && detectedSize.cy < 1)
   {
   dataProvider_->GetScanner()->GetValueForKey(kESMaxScanSize, detectedSize, funcUnit);
   }
   dict[kESScanSize] = detectedSize;
}
bool ScanAreaHeight::IsOverScanForCroppingAvailable()
{
 ESIndexSet availaleValues;
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetAvailableValueForKey(kESOverScanForCropping, availaleValues, kESFunctionalUnitDocumentFeeder);
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
ESDictionary ScanAreaHeight::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 SDIInt outputResolution = GetValueInt(kSDIResolutionKey);
 SDIInt scanResolutionX = dataProvider_->GetCommandValueAsNumber(kESXResolution);
 SDIInt scanResolutionY = dataProvider_->GetCommandValueAsNumber(kESYResolution);
 ESNumber adfOffset = kPrvHRD_ADFOffset_Left;
 if (dataProvider_->GetModelInfo()->GetValue(kPrvHRD_ADFOffset, adfOffset))
 {
  if (adfOffset == kPrvHRD_ADFOffset_Right_Manual)
  {
   dataProvider_->GetScanner()->SetValueForKey(kESGuidePositionADF, (ESNumber)kESGuidePositionRight);
  }
  if (adfOffset == kPrvHRD_ADFOffset_Left)
  {
   dataProvider_->GetScanner()->SetValueForKey(kESGuidePositionADF, (ESNumber)kESGuidePositionLeft);
  }
  if (adfOffset == kPrvHRD_ADFOffset_Center_Auto || adfOffset == kPrvHRD_ADFOffset_Center_Manual)
  {
   dataProvider_->GetScanner()->SetValueForKey(kESGuidePositionADF, (ESNumber)kESGuidePositionCenter);
  }
 }
 SDIInt offsetX = GetValueInt(kSDIScanAreaOffsetXKey) * scanResolutionX / outputResolution;
 SDIInt offsetY = GetValueInt(kSDIScanAreaOffsetYKey) * scanResolutionY / outputResolution;
 SDIInt width = GetValueInt(kSDIScanAreaWidthKey) * scanResolutionX / outputResolution;
 SDIInt height = GetValueInt(kSDIScanAreaHeightKey) * scanResolutionY / outputResolution;
 SDIFunctionalUnit funcUnit = (SDIFunctionalUnit)GetValueInt(kSDIFunctionalUnitKey);
 auto autoSize = (AutoSize*)(dataProvider_->GetKeyInstance(kSDIAutoSizeKey).get());
 auto paperDeskew = (PaperDeskew*)dataProvider_->GetKeyInstance(kSDIPaperDeskewKey).get();
 if (funcUnit == kSDIFunctionalUnitFlatbed)
 {
  if (autoSize->IsDetectedDocumentSizeAvailable(kESFunctionalUnitFlatbed) && GetValueInt(kSDIAutoSizeKey) == kSDIAutoSizeStandard)
  {
   UpdateScanAreaWithDetectedSize(kESFunctionalUnitFlatbed, dict);
  }
  else if (autoSize->IsAdvancedSotwareAutoCropEnabled())
  {
     ST_ES_SIZE_F maxSize = {0};
     dataProvider_->GetScanner()->GetValueForKey(kESMaxScanSize, maxSize, kESFunctionalUnitFlatbed);
     dict[kESScanSize] = maxSize;
  }
  else{
   dict[kESScanAreaInPixel] = MakeRect<UInt32>(offsetX,
              offsetY,
              offsetX + width,
              offsetY + height);
  }
 }
 else
 {
  if (GetValueInt(kSDIAutoSizeKey) == kSDIAutoSizeStandard)
  {
   if (autoSize->IsAdvancedSotwareAutoCropEnabled())
   {
    dict[kESScanSizeInPixel] = MakeSize<UInt32>(GetValueInt(kSDIMaxScanAreaWidthKey) / 100.0 * scanResolutionX,
              GetValueInt(kSDIMaxScanAreaHeightKey) / 100.0 * scanResolutionY);
    if (IsOverScanForCroppingAvailable())
    {
     dict[kESOverScanForCropping] = (bool)true;
    }
   }
    else if (autoSize->IsCRPAvailable())
    {
    dict[kESScanSizeInPixel] = MakeSize<UInt32>(GetValueInt(kSDIMaxScanAreaWidthKey) / 100.0 * scanResolutionX,
              GetValueInt(kSDIMaxScanAreaHeightKey) / 100.0 * scanResolutionY);
    dict[kESPaperEndDetection] = (bool)false;
    }
    else if (autoSize->IsDetectedDocumentSizeAvailable(kESFunctionalUnitDocumentFeeder))
    {
     UpdateScanAreaWithDetectedSize(kESFunctionalUnitDocumentFeeder, dict);
     dict[kESPaperEndDetection] = (bool)true;
    }else{
    dict[kESScanSizeInPixel] = MakeSize<UInt32>(GetValueInt(kSDIMaxScanAreaWidthKey) / 100.0 * scanResolutionX,
               GetValueInt(kSDIMaxScanAreaHeightKey) / 100.0 * scanResolutionY);
    dict[kESPaperEndDetection] = (bool)true;
    dict[kESOverScan] = (bool)true;
    }
   return dict;
  }else if (GetValueInt(kSDIAutoSizeKey) == kSDIAutoSizeLongPaper)
  {
   int heightMax = std::min(120* scanResolutionY, (int)(GetValueInt(kSDIMaxScanAreaHeightInLongPaperKey) / 100.0 * scanResolutionY));
   dict[kESScanSizeInPixel] = MakeSize<UInt32>(GetValueInt(kSDIMaxScanAreaWidthKey) / 100.0 * scanResolutionX, heightMax);
   dict[kESPaperEndDetection] = (bool)true;
   dict[kESOverScan] = (bool)true;
   return dict;
  }else if (GetValueInt(kSDIPaperEndDetectionKey) == 1)
  {
   int maxHeight = std::min((int)(GetValueInt(kSDIMaxScanAreaHeightInLongPaperKey)/ 100.0 * scanResolutionY), 215 * 300);
   dict[kESScanSizeInPixel] = MakeSize<UInt32>(width, maxHeight);
   dict[kESPaperEndDetection] = (bool)true;
   return dict;
  }
  if (paperDeskew->IsAutoDeskewForWhiteBGEnabled())
  {
   dict[kESScanSizeInPixel] = MakeSize<UInt32>(GetValueInt(kSDIMaxScanAreaWidthKey) / 100.0 * scanResolutionX,
              GetValueInt(kSDIMaxScanAreaHeightKey) / 100.0 * scanResolutionY);
   if (IsOverScanForCroppingAvailable())
   {
    dict[kESOverScanForCropping] = (bool)true;
   }
   return dict;
  }else{
   if (offsetX == 0 && offsetY== 0 )
   {
    dict[kESScanSizeInPixel] = MakeSize<UInt32>(width,
               height);
   }else{
    dict[kESScanAreaInPixel] = MakeRect<UInt32>(offsetX,
               offsetY,
               offsetX + width,
               offsetY + height);
   }
   dict[kESPaperEndDetection] = (bool)false;
  }
 }
 return dict;
}
}
