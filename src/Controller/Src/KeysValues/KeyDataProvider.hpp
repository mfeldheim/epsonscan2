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
//  KeyDataProvider.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <memory>
#include <ESCommonTypedef.h>
namespace epsonscan
{
 class ModelInfo;
 class Scanner;
 class IKey;
 class IKeyDataProvider
 {
  public:
   virtual std::shared_ptr<ModelInfo> GetModelInfo() = 0;
   virtual std::shared_ptr<Scanner> GetScanner() = 0;
   virtual std::shared_ptr<IKey> GetKeyInstance(const std::string& key) = 0;
   virtual ESNumber GetCommandValueAsNumber(ESString key) = 0;
 };
}
