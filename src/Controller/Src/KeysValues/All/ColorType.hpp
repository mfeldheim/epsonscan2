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
//  ColorType.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Key.hpp"
#include "EpsonScan2.h"
#include "ESImageInfo.h"
namespace epsonscan {
 class ColorType : public Key<SDIInt>
 {
  public:
  explicit ColorType(IKeyDataProvider* dataProvider) : Key<SDIInt>(dataProvider) ,
                isSupportHardwareColorTypeAuto_(false),
                scanGammaMode_(0),
                saveGammaMode_(0)
  {
  }
  std::string GetName() const override
  {
   return std::string(kSDIColorTypeKey);
  }
  void SetValue(const SDIInt& intVal) override;
  void GetValue(SDIInt& outIntVal) override;
  void GetCapability(SDICapability &capability) override;
  void Reset() override;
  ESNumber GetScanCounterColorType();
  ESNumber GetColorType();
  ESDictionary GetEngineKeyValues() override;
  bool IsHardawaDropout();
  bool IsSoftwareDropout();
  bool IsSupportHardwareColorTypeAuto();
  ESNumber GetScanGammaMode() const
  {
   return scanGammaMode_;
  }
  ESNumber GetSaveGammaMode() const
  {
   return saveGammaMode_;
  }
  private:
   void GetGammaTable(ESGammaTable& outGammaTable);
   bool isSupportHardwareColorTypeAuto_;
   ESNumber scanGammaMode_;
   ESNumber saveGammaMode_;
 };
}
