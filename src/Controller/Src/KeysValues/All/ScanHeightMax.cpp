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
//  ScanHeightMax.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ScanHeightMax.hpp"
#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void ScanHeightMax::SetValue(const SDIInt& intVal)
{
}
void ScanHeightMax::Reset()
{
}
SDIInt ScanHeightMax::ADFValue()
{
 ST_ES_SIZE_F stSize={0};
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetValueForKey(kESMaxScanSize, stSize, kESFunctionalUnitDocumentFeeder);
 return (SDIInt)(stSize.cy * 100);
}
SDIInt ScanHeightMax::FlatbedValue()
{
 ST_ES_SIZE_F stSize={0};
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetValueForKey(kESMaxScanSize, stSize, kESFunctionalUnitFlatbed);
 return (SDIInt)(stSize.cy * 100);
}
SDIInt ScanHeightMax::AutoValue()
{
 return std::max(ADFValue(), FlatbedValue());
}
void ScanHeightMax::GetValue(SDIInt& intVal)
{
 SDIFunctionalUnit func = (SDIFunctionalUnit)GetValueInt(kSDIFunctionalUnitKey);
 switch(func)
 {
  case kSDIFunctionalUnitFlatbed:
   intVal = FlatbedValue();
   return;
  case kSDIFunctionalUnitDocumentFeeder:
    intVal = ADFValue();
   return;
 }
}
void ScanHeightMax::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
}
ESDictionary ScanHeightMax::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
