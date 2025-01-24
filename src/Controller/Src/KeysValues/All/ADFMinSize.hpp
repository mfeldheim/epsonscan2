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
//  ADFMinSize.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class ADFMinSize : public Key<SDIInt>
 {
  public:
  explicit ADFMinSize(IKeyDataProvider* dataProvider, std::string sdiKey, std::string modelInfoKey) :
                 Key<SDIInt>(dataProvider),
                 sdiKeyName_(sdiKey),
                 modelInfoKeyName_(modelInfoKey)
  {
  }
  std::string GetName() const override
  {
   return sdiKeyName_;
  }
  void SetValue(const SDIInt& intVal) override
        {
        }
  void GetValue(SDIInt& outIntVal) override
        {
            ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
            ESNumber maxSizeInMM = 0;
            modelInfo->GetValue(modelInfoKeyName_.c_str(), maxSizeInMM);
            current_ = MMtoInch(maxSizeInMM/10.0) * 100;
            outIntVal = current_;
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultListCapability(capability);
        }
  void Reset() override
        {
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            return dict;
        }
        std::string sdiKeyName_;
        std::string modelInfoKeyName_;
 };
}
