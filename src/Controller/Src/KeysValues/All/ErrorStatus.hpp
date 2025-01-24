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
//  ErrorStatus.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class ErrorStatus : public Key<SDIInt>
 {
  public:
  explicit ErrorStatus(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDIErrorStatusKey;
  }
  void SetValue(const SDIInt& intVal) override
        {
        }
  void GetValue(SDIInt& outIntVal) override
        {
            Scanner* scanner = dataProvider_->GetScanner().get();
            ESNumber value = 0;
            scanner->GetValueForKey(kESErrorStatus, value);
            outIntVal = ExchangeError((ESErrorCode)value);
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
 };
}
