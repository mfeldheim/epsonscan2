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
//  DocumentType.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "DocumentType.hpp"
#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include "FunctionalUnit.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void DocumentType::SetValue(const SDIInt& intVal)
{
 SDI_TRACE_LOG("SetValue = %d", intVal);;
 SDICapability cap = {};
 GetCapability(cap);
 if (cap.supportLevel == kSDISupportLevelNone)
 {
  current_ = kSDIDocumentTypeReflective;
 }else{
  current_ = intVal;
 }
}
void DocumentType::Reset()
{
 current_ = kSDIDocumentTypeReflective;
}
void DocumentType::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void DocumentType::GetCapability(SDICapability &capability)
{
 if (cache_)
 {
  capability = *cache_;
  return;
 }
 std::unique_ptr<SDICapability> cap(new SDICapability());
 cap->capabilityType = kSDICapabilitTypeList;
 cap->supportLevel = kSDISupportLevelNone;
 ESIndexSet available;
 auto functionalUnit = (FunctionalUnit*)dataProvider_->GetKeyInstance(kSDIDocumentTypeKey).get();
 if (functionalUnit->TransparentAvailable() == false)
 {
  cap->supportLevel = kSDISupportLevelNone;
 }else{
  cap->supportLevel = kSDISupportLevelAvailable;
  AddList(*cap, kSDIDocumentTypeReflective);
  AddAllList(*cap, kSDIDocumentTypeReflective);
  AddList(*cap, kSDIDocumentTypePositiveFilm);
  AddAllList(*cap, kSDIDocumentTypePositiveFilm);
  AddList(*cap, kSDIDocumentTypeColorNegativeFilm);
  AddAllList(*cap, kSDIDocumentTypeColorNegativeFilm);
  AddList(*cap, kSDIDocumentTypeMonoNegativeFilm);
  AddAllList(*cap, kSDIDocumentTypeMonoNegativeFilm);
 }
 capability = *cap;
 cache_.swap(cap);
}
ESDictionary DocumentType::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 if (current_ == kSDIDocumentTypePositiveFilm || current_ == kSDIDocumentTypeMonoNegativeFilm)
 {
  dict[kESFilmType] = (ESNumber)kESFilmTypePositive;
 }
 if (current_ == kSDIDocumentTypeColorNegativeFilm)
 {
  dict[kESFilmType] = (ESNumber)kESFilmTypeNegative;
 }
 return dict;
}
}
