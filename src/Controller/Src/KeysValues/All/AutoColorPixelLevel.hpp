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
//  AutoColorPixelLevel.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class AutoColorPixelLevel : public Key<SDIInt>
 {
  public:
  explicit AutoColorPixelLevel(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDIAutoColorPixelLevelKey;
  }
  void SetValue(const SDIInt& intVal) override
        {
            current_ = intVal;
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultRangeCapability(capability);
            capability.supportLevel = kSDISupportLevelNone;
            ESNumber isAutoColorSupported = 0;
            if(dataProvider_->GetModelInfo()->GetValue(kPrvHRD_AutoColorGrayMono, isAutoColorSupported))
            {
                if (isAutoColorSupported)
                {
                    capability.supportLevel = kSDISupportLevelAvailable;
                }
            }
        }
  void GetValue(SDIInt& outIntVal) override
        {
            outIntVal = current_;
        }
  void Reset() override
        {
            current_ = 2;
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            return dict;
        }
 };
}
