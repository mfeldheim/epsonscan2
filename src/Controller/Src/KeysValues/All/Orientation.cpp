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
//  Orientation.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Orientation.hpp"
#include "Scanner.hpp"
#include "GetOrientation.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void Orientation::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void Orientation::Reset()
{
 current_ = kSDIOrientationNone;
}
void Orientation::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void Orientation::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 AddList(capability, kSDIOrientationNone);
 AddAllList(capability, kSDIOrientationNone);
 AddList(capability, kSDIOrientation90);
 AddAllList(capability, kSDIOrientation90);
 AddList(capability, kSDIOrientation180);
 AddAllList(capability, kSDIOrientation180);
 AddList(capability, kSDIOrientation270);
 AddAllList(capability, kSDIOrientation270);
 if (GetOrientation::IsPluginAvailable())
 {
  ESNumber kind = kPrvHRD_Kind_SF_Document;
  dataProvider_->GetModelInfo()->GetValue(kPrvHRD_Kind, kind);
  if(kind != kPrvHRD_Kind_MF_LFP)
  {
   AddList(capability, kSDIOrientationAuto);
   AddAllList(capability, kSDIOrientationAuto);
  }
 }
}
ESDictionary Orientation::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
