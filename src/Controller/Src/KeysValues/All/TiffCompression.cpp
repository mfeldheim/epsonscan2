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
//  TiffCompression.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "TiffCompression.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void TiffCompression::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void TiffCompression::Reset()
{
 current_ = false;
}
void TiffCompression::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void TiffCompression::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 AddList(capability, kSDITiffCompressionNone);
 AddList(capability, kSDITiffCompressionCCITFAX4);
 AddAllList(capability, kSDITiffCompressionNone);
 AddAllList(capability, kSDITiffCompressionCCITFAX4);
}
ESDictionary TiffCompression::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
