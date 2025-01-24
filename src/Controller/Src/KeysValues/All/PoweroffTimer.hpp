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
//  PoweroffTimer.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class PoweroffTimer : public Key<SDIInt>
 {
  public:
  explicit PoweroffTimer(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDIAutoPowerOffTimeKey;
  }
  void SetValue(const SDIInt& intVal) override
        {
            SDICapability capability;
            GetCapability(capability);
           if (capability.supportLevel != kSDISupportLevelNone)
           {
                dataProvider_->GetScanner()->SetValueForKey(kESPowerOffTime, (ESNumber)intVal);
           }
        }
  void GetValue(SDIInt& outIntVal) override
        {
            Scanner* scanner = dataProvider_->GetScanner().get();
            ESNumber value = 0;
            scanner->GetValueForKey(kESPowerOffTime, value);
            current_ = value;
            outIntVal = current_;
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultListCapability(capability);
            Scanner* scanner = dataProvider_->GetScanner().get();
            ESNumber value = 0;
            if(scanner->GetValueForKey(kESPowerOffTime, value) == false)
            {
                capability.supportLevel = kSDISupportLevelNone;
                return;
            }else{
                ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
       ESNumber powerOfftimer = kPrvHRD_PowerOffTimer_NotSupport;
       modelInfo->GetValue(kPrvHRD_PowerOffTimer, powerOfftimer);
               if (powerOfftimer == kPrvHRD_PowerOffTimer_NotSupport)
                {
                       capability.supportLevel = kSDISupportLevelNone;
                       return;
                }
                else
                {
                        capability.supportLevel = kSDISupportLevelAvailable;
                }
            }
            ESDictionary availableValue;
            ESNumber presetList[] = {0, 30, 60, 120, 240, 480, 720};
            if (scanner->GetAvailableValueForKeyDict(kESPowerOffTime, availableValue)) {
                if (availableValue[kESPowerOffTime].type() == typeid(ESIndexSet)) {
                    ESIndexSet tmp;
                    if (SafeBoostAnyCast_Local(availableValue[kESPowerOffTime], tmp)) {
                        ESNumber min = *tmp.begin();
                        ESNumber max = *tmp.end();
                        for (int i = 0; i < sizeof(presetList) / sizeof(ESNumber) && i < SDI_CAPABILITY_LISTMAX; i++)
                        {
                            capability.list[i] = presetList[i];
                            capability.countOfList += 1;
                            capability.allList[i] = presetList[i];
                            capability.countOfAllList += 1;
                        }
                    }
                }
                else if (availableValue[kESPowerOffTime].type() == typeid(ESIndexArray)) {
                    ESIndexArray tmp;
                    if (SafeBoostAnyCast_Local(availableValue[kESPowerOffTime], tmp)) {
                        for (int i = 0; i < tmp.size() && i < SDI_CAPABILITY_LISTMAX; i++)
                        {
                            capability.list[i] = tmp.at(i);
                            capability.countOfList += 1;
                            capability.allList[i] = tmp.at(i);
                            capability.countOfAllList += 1;
                        }
                    }
                }
                else if (availableValue[kESPowerOffTime].type() == typeid(ST_ES_RANGE)) {
                    ST_ES_RANGE tmp;
                    if (SafeBoostAnyCast_Local(availableValue[kESPowerOffTime], tmp)) {
                        ESNumber min = tmp.nMin;
                        ESNumber max = tmp.nMax;
                        for (int i = 0; i < sizeof(presetList) / sizeof(ESNumber) && i < SDI_CAPABILITY_LISTMAX; i++)
                        {
                            capability.list[i] = presetList[i];
                            capability.countOfList += 1;
                            capability.allList[i] = presetList[i];
                            capability.countOfAllList += 1;
                        }
                    }
                }
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
