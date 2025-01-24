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
//  AutoColorPixelType.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class AutoColorPixelType : public Key<SDIInt>
 {
  public:
  explicit AutoColorPixelType(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDIAutoColorPixelTypeKey;
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
         SetDefaultListCapability(capability);
            capability.supportLevel = kSDISupportLevelAvailable;
            AddList(capability, kSDIAutoColorPixelTypeMono);
            AddList(capability, kSDIAutoColorPixelTypeGray);
            ESNumber isAutoColorSupported = 0;
            bool isHardwareImageProcessModel = false;
            Brightness* brigtness = (Brightness*)dataProvider_->GetKeyInstance(kSDIBrightnessKey).get();
            if (brigtness && brigtness->IsSupportBrightnessCommand())
            {
                isHardwareImageProcessModel = true;
            }
            if(dataProvider_->GetModelInfo()->GetValue(kPrvHRD_AutoColorGrayMono, isAutoColorSupported))
            {
                if (isAutoColorSupported && isHardwareImageProcessModel == false)
                {
                    AddList(capability, kSDIAutoColorPixelTypeAuto);
                }
            }
        }
  void Reset() override
        {
            current_ = kSDIAutoColorPixelTypeMono;
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            return dict;
        }
 };
}
