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
//  JsonObjectPoint.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template<> class CJsonObject< ST_ES_POINT_S32 > {
  public:
   static LPCTSTR Label(){ return TYPE_POINT; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_POINT_S32& value )
   {
    writer.StartObject();
    writer.String( LB_POINT_X );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.x );
    writer.String( LB_POINT_Y );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.y );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_POINT_S32& value )
   {
    if ( json.IsObject() && json.HasMember( LB_POINT_X ) && json.HasMember( LB_POINT_Y ) ){
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_POINT_X], value.x );
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_POINT_Y], value.y );
     return 0;
    } else {
     return 1;
    }
   }
  };
  template<> class CJsonObject< ST_ES_POINT_UN32 > {
  public:
   static LPCTSTR Label(){ return TYPE_POINT_U; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_POINT_UN32& value )
   {
    writer.StartObject();
    writer.String( LB_POINT_X );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.x );
    writer.String( LB_POINT_Y );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.y );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_POINT_UN32& value )
   {
    if ( json.IsObject() && json.HasMember( LB_POINT_X ) && json.HasMember( LB_POINT_Y ) ){
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_POINT_X], value.x );
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_POINT_Y], value.y );
     return 0;
    } else {
     return 1;
    }
   }
  };
  template<> class CJsonObject< ST_ES_POINT_F > {
  public:
   static LPCTSTR Label(){ return TYPE_POINT_F; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_POINT_F& value )
   {
    writer.StartObject();
    writer.String( LB_POINT_X );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.x );
    writer.String( LB_POINT_Y );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.y );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_POINT_F& value )
   {
    if ( json.IsObject() && json.HasMember( LB_POINT_X ) && json.HasMember( LB_POINT_Y ) ){
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_POINT_X], value.x );
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_POINT_Y], value.y );
     return 0;
    } else {
     return 1;
    }
   }
  };
 };
};
