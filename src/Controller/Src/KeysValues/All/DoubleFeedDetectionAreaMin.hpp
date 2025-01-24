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
//  DoubleFeedDetectionAreaMin.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class DoubleFeedDetectionAreaMin : public Key<SDIInt>
 {
  public:
  explicit DoubleFeedDetectionAreaMin(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return std::string(kSDIDoubleFeedDetectionAreaMinKey);
  }
  void SetValue(const SDIInt& intVal) override
        {
            current_ = intVal;
        }
  void GetValue(SDIInt& outIntVal) override
        {
            outIntVal = current_;
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultRangeCapability(capability);
           capability.supportLevel = kSDISupportLevelNone;
         ESFloat minValue;
            auto maxAreaHeight = GetValueInt(kSDIMaxScanAreaHeightKey);
            Scanner* scanner = dataProvider_->GetScanner().get();
         if(scanner && scanner->GetValueForKey(kESDoubleFeedDetectionRangeOffset, minValue))
            {
                capability.supportLevel = kSDISupportLevelAvailable;
                capability.maxValue = maxAreaHeight - 100;
                capability.minValue = 0;
            }
        }
  void Reset() override
        {
            current_ = 0;
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            dict[kESDoubleFeedDetectionRangeOffset] = (ESFloat)(current_ / 100.0);
            return dict;
        }
 };
}
