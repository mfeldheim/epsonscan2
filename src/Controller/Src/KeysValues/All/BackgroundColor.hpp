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
//  BackgroundColor.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class BackgroundColor : public Key<SDIInt>
 {
  public:
  explicit BackgroundColor(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {;
   return std::string(kSDIBackgroundColorKey);
  }
  void SetValue(const SDIInt& intVal) override
  {
   SDICapability cap;
   GetCapability(cap);
   if (cap.supportLevel != kSDISupportLevelNone)
   {
    current_ = intVal;
   }
  }
  void GetValue(SDIInt& outIntVal) override
  {
   outIntVal = current_;
  }
  void GetCapability(SDICapability &capability) override
  {
   SetDefaultListCapability(capability);
   ESIndexSet available;
   Scanner* scanner = dataProvider_->GetScanner().get();
   if(scanner && scanner->GetAvailableValueForKey(kESBGColor, available)) {
    AddList(capability, kSDIBackgroundColorBlack);
    AddAllList(capability, kSDIBackgroundColorBlack);
    AddList(capability, kSDIBackgroundColorWhite);
    AddAllList(capability, kSDIBackgroundColorWhite);
    capability.supportLevel = kSDISupportLevelAvailable;
   }else{
    capability.supportLevel = kSDISupportLevelNone;
   }
  }
  void Reset() override
  {
   SDICapability cap;
   GetCapability(cap);
   if (cap.supportLevel != kSDISupportLevelNone)
   {
    current_ = kSDIBackgroundColorBlack;
   }else{
    current_ = kSDIBackgroundColorNone;
   }
  }
  ESDictionary GetEngineKeyValues() override
  {
   auto dict = ESDictionary();
   SDICapability cap;
   GetCapability(cap);
   if (cap.supportLevel != kSDISupportLevelAvailable)
   {
    return dict;
   }
   if (current_ == kSDIBackgroundColorBlack)
   {
    dict[kESBGColor] = (ESNumber)kESBGColorBlack;
   }
   if (current_ == kSDIBackgroundColorWhite)
   {
    dict[kESBGColor] = (ESNumber)kESBGColorWhite;
   }
   return dict;
  }
 };
}
