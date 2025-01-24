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
//  Gamma.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "Scanner.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
    class Gamma : public Key<SDIInt>
 {
  public:
  explicit Gamma(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider) , isSupportGammaCommand_(false)
  {
  }
  std::string GetName() const override
  {
   return std::string(kSDIGammaKey);
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
         capability.supportLevel = kSDISupportLevelAvailable;
            if (GetValueInt(kSDIColorTypeKey) == kSDIColorTypeMono1)
            {
                capability.minValue = 0;
                capability.maxValue = 0;
                capability.supportLevel= kSDISupportLevelUnavailable;
            }else
            {
                capability.minValue = 0;
                capability.maxValue = 30;
                capability.supportLevel= kSDISupportLevelAvailable;
            }
            capability.allMinValue = 0;
            capability.allMaxValue = 30;
        }
  void Reset() override
        {
         current_ = 22;
            ESNumber currentGamma;
            Scanner* scannerSupportGamma = dataProvider_->GetScanner().get();
            if(scannerSupportGamma && scannerSupportGamma->GetValueForKey(kESBrightness, currentGamma)) {
                isSupportGammaCommand_ = true;
            }else{
                isSupportGammaCommand_ = false;
            }
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
         if(isSupportGammaCommand_) {
          dict[kESGammaScale] = (ESNumber)current_;
         }
            return dict;
        }
        bool IsSupportGammaCommand()
        {
         return isSupportGammaCommand_;
        }
private:
        bool isSupportGammaCommand_;
 };
}
