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
//  JsonObjectNoData.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  class CJsonNoDataObject {
  public:
   static LPCTSTR Label(){ return TYPE_NO_DATA; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESAny& value )
   {
    writer.StartObject();
    {
     writer.String( Label() );
     writer.Null();
    }
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESAny& anyDst )
   {
    anyDst = nullptr;
    return 0;
   }
  };
 };
};
