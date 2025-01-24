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
//  UnscannableScanParameterForAFMC.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "UnscannableScanParameterForAFMC.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void UnscannableScanParameterForAFMC::SetValue(const SDIInt& intVal)
{
}
void UnscannableScanParameterForAFMC::Reset()
{
}
void UnscannableScanParameterForAFMC::GetValue(SDIInt& intVal)
{
 auto containsObject = [](const ESIndexArray &ar, ESNumber findValue) -> bool {
  return (std::find(std::begin(ar), std::end(ar), findValue) != std::end(ar));
 };
 ESIndexArray unscanParamStatus;
 Scanner* scanner = dataProvider_->GetScanner().get();
 scanner->GetValueForKey(kESUnavailableScanParameterStatus, unscanParamStatus, kESFunctionalUnitDocumentFeeder);
 if (containsObject(unscanParamStatus, kESUnavailableScanParameterStatusAFMC)) {
  intVal = 1;
  return;
 }else{
  intVal = 0;
 }
}
void UnscannableScanParameterForAFMC::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
}
ESDictionary UnscannableScanParameterForAFMC::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
