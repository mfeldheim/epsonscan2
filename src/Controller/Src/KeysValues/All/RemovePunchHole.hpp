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
//  RemovePunchHole.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
#include "DeficiencyCorrection.hpp"
namespace epsonscan {
 class RemovePunchHole : public Key<SDIInt>
 {
  public:
  explicit RemovePunchHole(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider)
  {
  }
  std::string GetName() const override
  {
   return std::string(kSDIRemovePunchholeKey);
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
   bool SupportRemovePunchHole = true;
   Brightness* brigtness = (Brightness*)dataProvider_->GetKeyInstance(kSDIBrightnessKey).get();
   if (brigtness && brigtness->IsSupportBrightnessCommand())
   {
    capability.supportLevel = kSDISupportLevelNone;
   }
   else
   {
    bool hasAdf = false;
    ESIndexSet functionalUnits = dataProvider_->GetScanner().get()->GetSupportedFunctionalUnit();
    if (functionalUnits.find(kESFunctionalUnitDocumentFeeder) != functionalUnits.end())
    {
     hasAdf = true;
    }
    ESNumber punchHole = kPrvHRD_RemovePunchHole_NotSupport;
    ModelInfo* modelInfo = dataProvider_->GetModelInfo().get();
    if (modelInfo)
    {
     if (modelInfo->GetValue(kPrvHRD_RemovePunchHole, punchHole) == false)
     {
      punchHole = kPrvHRD_RemovePunchHole_NotSupport;
     }
    }
    SDICapability deficiencyCap = {0};
    GetCapabilityWithKey(kSDIDeficiencyCorrectionKey, deficiencyCap);
    if (deficiencyCap.supportLevel != kSDISupportLevelNone)
    {
     capability.supportLevel = kSDISupportLevelAvailable;
     AddList(capability, kSDIRemovePunchHoleNone);
     AddList(capability, kSDIRemovePunchHoleAll);
     AddAllList(capability, kSDIRemovePunchHoleNone);
     AddAllList(capability, kSDIRemovePunchHoleAll);
     if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
     {
      capability.supportLevel = kSDISupportLevelUnavailable;
      ResetRange(capability);
     }
    }
    else if (DTR::IsDTRAvailable() && hasAdf && (punchHole == kPrvHRD_RemovePunchHole_Support || punchHole == kPrvHRD_RemovePunchHole_Range ) )
    {
     capability.supportLevel = kSDISupportLevelAvailable;
     AddList(capability, kSDIRemovePunchHoleNone);
     AddList(capability, kSDIRemovePunchHoleAll);
     AddList(capability, kSDIRemovePunchHoleTopBottom);
     AddList(capability, kSDIRemovePunchHoleLeftRight);
     AddAllList(capability, kSDIRemovePunchHoleNone);
     AddAllList(capability, kSDIRemovePunchHoleAll);
     AddAllList(capability, kSDIRemovePunchHoleTopBottom);
     AddAllList(capability, kSDIRemovePunchHoleLeftRight);
     if (GetValueInt(kSDIFunctionalUnitKey) == kSDIFunctionalUnitFlatbed)
     {
      capability.supportLevel = kSDISupportLevelUnavailable;
      ResetRange(capability);
     }
    }else{
     capability.supportLevel = kSDISupportLevelNone;
    }
   }
  }
  void Reset() override
  {
   current_ = kSDIRemovePunchHoleNone;
  }
  ESDictionary GetEngineKeyValues() override
  {
   auto dict = ESDictionary();
   return dict;
  }
 };
}
