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
//  PaperLoaded.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "PaperLoaded.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void PaperLoaded::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void PaperLoaded::Reset()
{
 current_ = 0;
}
void PaperLoaded::GetValue(SDIInt& intVal)
{
 Scanner* scanner = dataProvider_->GetScanner().get();
  bool isLoaded = 0;
 scanner->GetValueForKey(kESDocumentLoaded, isLoaded, kESFunctionalUnitDocumentFeeder);
 SDI_TRACE_LOG("isLoaded = %d", intVal);;
 current_ = isLoaded;
 intVal = current_;
}
void PaperLoaded::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
}
ESDictionary PaperLoaded::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
