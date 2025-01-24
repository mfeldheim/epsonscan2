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
//  ScanHeightMaxInLongPaperResolutionTable.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ScanHeightMaxInLongPaperResolutionTable.hpp"
#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void ScanHeightMaxInLongPaperResolutionTable::SetValue(const std::string& intVal)
{
}
void ScanHeightMaxInLongPaperResolutionTable::Reset()
{
}
void ScanHeightMaxInLongPaperResolutionTable::GetValue(std::string& intVal)
{
 Scanner* scanner = dataProvider_->GetScanner().get();
 if (scanner)
 {
  ESDicArray dictArray;
  if (scanner->GetValueForKey(kESMaxLongLengthTable, dictArray) == false)
  {
   return;
  }
  ESString outVal = "[";
  for(ESDictionary dic : dictArray)
  {
   ESString localVal;
   ES_CMN_FUNCS::JSON::DictionaryToJSON(dic, localVal);
   outVal += localVal;
   outVal += ",";
  }
  outVal.pop_back();
  outVal += "]";
  intVal = outVal;
 }
}
void ScanHeightMaxInLongPaperResolutionTable::GetCapability(SDICapability &capability)
{
 SetDefaultRangeCapability(capability);
 Scanner* scanner = dataProvider_->GetScanner().get();
 if (scanner)
 {
  ESDictionary dict;
  if(scanner->GetValueForKey(kESMaxLongLengthTable, dict))
  {
   capability.supportLevel = kSDISupportLevelAvailable;
  }else{
   capability.supportLevel = kSDISupportLevelNone;
  }
 }
}
ESDictionary ScanHeightMaxInLongPaperResolutionTable::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
