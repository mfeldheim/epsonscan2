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
//  SleepTimer.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class SleepTimer : public Key<SDIInt>
 {
  public:
  explicit SleepTimer(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDISleepTimeKey;
  }
  void SetValue(const SDIInt& intVal) override
        {
            SDICapability capability;
            GetCapability(capability);
            if (capability.supportLevel != kSDISupportLevelNone)
            {
                dataProvider_->GetScanner()->SetValueForKey(kESPowerSaveTime, (ESNumber)intVal);
            }
        }
  void GetValue(SDIInt& outIntVal) override
        {
            Scanner* scanner = dataProvider_->GetScanner().get();
            ESNumber value = 0;
            scanner->GetValueForKey(kESPowerSaveTime, value);
            current_ = value;
            outIntVal = current_;
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultRangeCapability(capability);
            Scanner* scanner = dataProvider_->GetScanner().get();
            ESNumber value = 0;
            if(scanner->GetValueForKey(kESPowerSaveTime, value) == false)
            {
                capability.supportLevel = kSDISupportLevelNone;
                return;
            }else{
                ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
       ESNumber powerOfftimer = kPrvHRD_SleepTime_NotSupport;
       modelInfo->GetValue(kPrvHRD_SleepTime, powerOfftimer);
               if (powerOfftimer == kPrvHRD_SleepTime_NotSupport)
                {
                       capability.supportLevel = kSDISupportLevelNone;
                       return;
                }
                else
                {
                        capability.supportLevel = kSDISupportLevelAvailable;
                }
            }
            ESNumber min = 0;
            ESNumber max = 0;
            if(scanner->GetAvailableValueForKey(kESPowerSaveTime, min, max))
            {
                capability.minValue = min;
                capability.allMinValue = min;
                capability.maxValue = max;
                capability.allMaxValue = max;
            }
        }
  void Reset() override
        {
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            return dict;
        }
 };
}
