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
//  FunctionalUnit.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "FunctionalUnit.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void FunctionalUnit::SetValue(const SDIInt& intVal)
{
 if (intVal == kSDIFunctionalUnitDocumentFeeder || intVal == kSDIFunctionalUnitCarrierSheet)
 {
  if (ADFAvailable())
  {
   current_ = intVal;
   return;
  }
 }
 if (intVal == kSDIFunctionalUnitFlatbed)
 {
  if (FlatbedAvailable())
  {
   current_ = intVal;
   return;
  }
 }
}
void FunctionalUnit::Reset()
{
 if (FlatbedAvailable())
 {
  current_ = kSDIFunctionalUnitFlatbed;
  return;
 }
 if (ADFAvailable())
 {
  current_ = kSDIFunctionalUnitDocumentFeeder;
  return;
 }
}
void FunctionalUnit::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
bool FunctionalUnit::TransparentAvailable()
{
 ESIndexSet availableFunctionalUnit;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESFunctionalUnitType, availableFunctionalUnit)) {
  if (availableFunctionalUnit.find(kESFunctionalUnitTransparent) != availableFunctionalUnit.end()) {
   return true;
  }
 }
 return false;
}
bool FunctionalUnit::TransarentAreaGuideAvailable()
{
 ESIndexSet availableFunctionalUnit;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESFunctionalUnitType, availableFunctionalUnit)) {
  if (availableFunctionalUnit.find(kESFunctionalUnitTPUAreaGuide) != availableFunctionalUnit.end()) {
   return true;
  }
 }
 return false;
}
bool FunctionalUnit::ADFAvailable()
{
 ESIndexSet availableFunctionalUnit;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESFunctionalUnitType, availableFunctionalUnit)) {
  if (availableFunctionalUnit.find(kESFunctionalUnitDocumentFeeder) != availableFunctionalUnit.end()) {
   return true;
  }
 }
 return false;
}
bool FunctionalUnit::FlatbedAvailable()
{
 ESIndexSet availableFunctionalUnit;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESFunctionalUnitType, availableFunctionalUnit)) {
  if (availableFunctionalUnit.find(kESFunctionalUnitFlatbed) != availableFunctionalUnit.end()) {
   return true;
  }
 }
 return false;
}
void FunctionalUnit::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
    capability.supportLevel = kSDISupportLevelAvailable;
 if (FlatbedAvailable()) {
  AddList(capability, kSDIFunctionalUnitFlatbed);
  AddAllList(capability, kSDIFunctionalUnitFlatbed);
 }
 if (ADFAvailable()) {
  AddList(capability, kSDIFunctionalUnitDocumentFeeder);
  AddAllList(capability, kSDIFunctionalUnitDocumentFeeder);
 }
}
ESDictionary FunctionalUnit::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 Scanner* scanner = dataProvider_->GetScanner().get();
 if (current_ == kSDIFunctionalUnitDocumentFeeder)
 {
  dict[kESFunctionalUnitType] = (ESNumber)kESFunctionalUnitDocumentFeeder;
  scanner->SetValueForKey(kESFunctionalUnitType, (ESNumber)kESFunctionalUnitDocumentFeeder);
 }
 if (current_ == kSDIFunctionalUnitFlatbed)
 {
  SDIDocumentType documentType = (SDIDocumentType)GetValueInt(kSDIDocumentTypeKey);
  if (documentType == kSDIDocumentTypeReflective)
  {
   dict[kESFunctionalUnitType] = (ESNumber)kESFunctionalUnitFlatbed;
   scanner->SetValueForKey(kESFunctionalUnitType, (ESNumber)kESFunctionalUnitFlatbed);
  }else{
   bool isFilmAreaGuide = (bool)GetValueInt(kSDIFilmAreaGuideKey);
   if (isFilmAreaGuide)
   {
    dict[kESFunctionalUnitType] = (ESNumber)kESFunctionalUnitTPUAreaGuide;
    scanner->SetValueForKey(kESFunctionalUnitType, (ESNumber)kESFunctionalUnitTPUAreaGuide);
   }else{
    dict[kESFunctionalUnitType] = (ESNumber)kESFunctionalUnitTransparent;
    scanner->SetValueForKey(kESFunctionalUnitType, (ESNumber)kESFunctionalUnitTransparent);
   }
  }
 }
 return dict;
}
}
