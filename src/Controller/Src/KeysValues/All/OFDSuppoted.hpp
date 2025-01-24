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
//  OFDSuppoted.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
#include "GetOrientation.hpp"
#include <utils/PathUtils.h>
namespace epsonscan {
 class OFDSuppoted : public Key<SDIInt>
 {
  public:
  explicit OFDSuppoted(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return kSDIOFDSupportedKey;
  }
  void SetValue(const SDIInt& intVal) override
        {
        }
  bool IsOfdPluginAvailable()
  {
       return ES_CMN_FUNCS::PATH::ES_IsExistFile("/opt/epson/epsonscan2-ofd-component/libepsonscan2-ofd-component.so");
  }
  void GetValue(SDIInt& outIntVal) override
        {
            outIntVal = IsOFDAvailable();
        }
  void GetCapability(SDICapability &capability) override
        {
         SetDefaultListCapability(capability);
   if (IsOFDAvailable())
   {
    capability.supportLevel = kSDISupportLevelAvailable;
   }else{
    capability.supportLevel = kSDISupportLevelNone;
   }
        }
  bool IsOFDAvailable()
  {
     SDIScannerKind kind = (SDIScannerKind)GetValueInt(KSDIScannerKindKey);
   if (kind != kSDIKindSFDocument && kind != kSDIKindSFPhoto)
   {
    return false;
   }
   return GetOrientation::IsPluginAvailable() && IsOfdPluginAvailable();
  }
  void Reset() override
        {
   current_ = IsOFDAvailable();
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
            return dict;
        }
 };
}
