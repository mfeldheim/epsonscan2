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
//  SkipBlankPageOnOff.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class SkipBlankPageOnOff : public Key<SDIInt>
 {
  public:
  explicit SkipBlankPageOnOff(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider) , isSupportHardwareBlankPageOnOff_(false)
  {
  }
  std::string GetName() const override
  {
   return std::string(kSDIBlankPageSkipKey);
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
    bool hasAdf = false;
    ESIndexSet functionalUnits = dataProvider_->GetScanner().get()->GetSupportedFunctionalUnit();
    if (functionalUnits.find(kESFunctionalUnitDocumentFeeder) != functionalUnits.end())
    {
     hasAdf = true;
    }
    if ((DTR::IsDTRAvailable() || isSupportHardwareBlankPageOnOff_) && hasAdf)
    {
     if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
     {
      capability.supportLevel = kSDISupportLevelUnavailable;
     }else{
      capability.supportLevel = kSDISupportLevelAvailable;
      AddList(capability, false);
      AddList(capability, true);
      AddAllList(capability, false);
      AddAllList(capability, true);
     }
    }else{
     capability.supportLevel = kSDISupportLevelNone;
    }
        }
  void Reset() override
        {
            current_ = 0;
   bool currentBlankPageOnOff = false;
   Scanner* scannerSupportBlankPageOnOff = dataProvider_->GetScanner().get();
   if(scannerSupportBlankPageOnOff && scannerSupportBlankPageOnOff->GetValueForKey(kESDetectBlankPageEnabled, currentBlankPageOnOff)) {
    isSupportHardwareBlankPageOnOff_ = true;
   }else{
    isSupportHardwareBlankPageOnOff_ = false;
   }
        }
  ESDictionary GetEngineKeyValues() override
        {
            auto dict = ESDictionary();
   if(isSupportHardwareBlankPageOnOff_ == true && GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitDocumentFeeder)
   {
    dict[kESDetectBlankPageEnabled] = (bool)current_;
   }
            return dict;
        }
  bool IsSupportHardwareBlankPageOnOff()
  {
   return isSupportHardwareBlankPageOnOff_;
  }
  private:
   bool isSupportHardwareBlankPageOnOff_;
 };
}
