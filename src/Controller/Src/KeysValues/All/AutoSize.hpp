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
//  AutoSize.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Key.hpp"
#include "EpsonScan2.h"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
 class AutoSize : public Key<SDIInt>
 {
  public:
  explicit AutoSize(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider) , processSoftwareAutoCrop_(false)
  {
  }
  std::string GetName() const override
  {;
   return std::string(kSDIAutoSizeKey);
  }
  void SetValue(const SDIInt& intVal) override;
  void GetValue(SDIInt& outIntVal) override;
  void GetCapability(SDICapability &capability) override;
  void Reset() override;
  bool IsHardwareAvailable();
  bool IsCRPAvailable();
  bool IsDetectedDocumentSizeAvailable(ESFunctionalUnitType funcUnit);
  bool IsAdvancedSotwareAutoCropEnabled();
  bool IsSoftwareAvailable();
  bool IsLongPaperAvailable();
  ESDictionary GetEngineKeyValues() override;
  bool GetProcessSoftwareAutoCrop()
  {
   return processSoftwareAutoCrop_;
  }
  bool processSoftwareAutoCrop_;
 };
}
