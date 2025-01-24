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
//  ScanHeightMaxInLongPaperResolutionTable.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "EpsonScan2.h"
namespace epsonscan {
 class ScanHeightMaxInLongPaperResolutionTable : public Key<std::string>
 {
  public:
  explicit ScanHeightMaxInLongPaperResolutionTable(IKeyDataProvider* dataProvider) : Key<std::string>(dataProvider)
  {
  }
  std::string GetName() const override
  {;
   return std::string(kSDIMaxScanAreaHeightInLongPaperResolutionTableKey);
  }
  void SetValue(const std::string& intVal) override;
  void GetValue(std::string& outIntVal) override;
  void GetCapability(SDICapability &capability) override;
  void Reset() override;
  ESDictionary GetEngineKeyValues() override;
 };
}
