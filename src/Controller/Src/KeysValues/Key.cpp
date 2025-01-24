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
//  Key.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Key.hpp"
#include "Error.hpp"
#include "Utility.hpp"
#include <memory.h>
#include <boost/format.hpp>
#include <algorithm>
namespace epsonscan {
  template<> void Key<SDIInt>::SetValue(SDIValueType valType, void* value, SDIInt size)
  {
   if (value) {
    SDI_TRACE_LOG("SetValueInt %s %d", GetName().c_str(), *reinterpret_cast<SDIInt*>(value));
    SetValue(*reinterpret_cast<SDIInt*>(value));
   }
  }
  template<> void Key<std::string>::SetValue(SDIValueType valType, void* value, SDIInt size)
  {
   if (value) {
     std::string stringVal = std::string(reinterpret_cast<SDIChar*>(value));
     SetValue(stringVal);
    }
  }
  template<> void Key<SDIInt>::GetValue(SDIValueType valType, void* value, SDIInt size)
  {
   if (value) {
      SDIInt intVal = 0;
      GetValue(intVal);
      memcpy(value, &intVal, sizeof(SDIInt));
      SDI_TRACE_LOG("GetValueInt %s %d", GetName().c_str(), intVal);
    }
  }
  template<> void Key<std::string>::GetValue(SDIValueType valType, void* value, SDIInt size)
  {
   if (value) {
      std::string string;
      GetValue(string);
      memcpy(value, string.c_str(), std::min<int32_t>(size, string.size()));
    }
  }
}
