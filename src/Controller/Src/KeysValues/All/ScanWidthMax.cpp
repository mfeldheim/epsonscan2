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
//  ScanWidthMax.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ScanWidthMax.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void ScanWidthMax::SetValue(const SDIInt& intVal)
{
}
void ScanWidthMax::Reset()
{
}
SDIInt ScanWidthMax::ADFValue()
{
 ST_ES_SIZE_F stSize={0};
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetValueForKey(kESMaxScanSize, stSize, kESFunctionalUnitDocumentFeeder);
 return (SDIInt)(stSize.cx * 100);
}
SDIInt ScanWidthMax::FlatbedValue()
{
 ST_ES_SIZE_F stSize={0};
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetValueForKey(kESMaxScanSize, stSize, kESFunctionalUnitFlatbed);
 return (SDIInt)(stSize.cx * 100);
}
SDIInt ScanWidthMax::AutoValue()
{
 return std::max(ADFValue(), FlatbedValue());
}
void ScanWidthMax::GetValue(SDIInt& intVal)
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
void ScanWidthMax::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
}
ESDictionary ScanWidthMax::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
