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
//  JsonObjectRect.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template<> class CJsonObject< ST_ES_RECT_S32 > {
  public:
   static LPCTSTR Label(){ return TYPE_RECT; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_RECT_S32& value )
   {
    writer.StartObject();
    writer.String( LB_RECT_X );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.left );
    writer.String( LB_RECT_Y );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.top );
    writer.String( LB_RECT_W );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.right - value.left );
    writer.String( LB_RECT_H );
    CJsonObject<ESNumber>::Write<Writer>(writer, value.bottom - value.top );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_RECT_S32& value )
   {
    if ( json.IsObject() &&
      json.HasMember( LB_RECT_X ) &&
      json.HasMember( LB_RECT_Y ) &&
      json.HasMember( LB_RECT_W ) &&
      json.HasMember( LB_RECT_H ) ){
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_RECT_X], value.left );
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_RECT_Y], value.top );
     ESNumber w;
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_RECT_W], w );
     value.right = value.left + w;
     ESNumber h;
     CJsonObject<ESNumber>::Read<JsonValue>(json[LB_RECT_H], h );
     value.bottom = value.top + h;
     return 0;
    } else {
     return 1;
    }
   }
  };
  template<> class CJsonObject< ST_ES_RECT_UN32 > {
  public:
   static LPCTSTR Label(){ return TYPE_RECT_U; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_RECT_UN32& value )
   {
    writer.StartObject();
    writer.String( LB_RECT_X );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.left );
    writer.String( LB_RECT_Y );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.top );
    writer.String( LB_RECT_W );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.right - value.left );
    writer.String( LB_RECT_H );
    CJsonObject<ESUnsigned>::Write<Writer>(writer, value.bottom - value.top );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_RECT_UN32& value )
   {
    if ( json.IsObject() &&
      json.HasMember( LB_RECT_X ) &&
      json.HasMember( LB_RECT_Y ) &&
      json.HasMember( LB_RECT_W ) &&
      json.HasMember( LB_RECT_H ) ){
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_RECT_X], value.left );
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_RECT_Y], value.top );
     ESUnsigned w;
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_RECT_W], w );
     value.right = value.left + w;
     ESUnsigned h;
     CJsonObject<ESUnsigned>::Read<JsonValue>(json[LB_RECT_H], h );
     value.bottom = value.top + h;
     return 0;
    } else {
     return 1;
    }
   }
  };
  template<> class CJsonObject< ST_ES_RECT_F > {
  public:
   static LPCTSTR Label(){ return TYPE_RECT_F; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ST_ES_RECT_F& value )
   {
    writer.StartObject();
    writer.String( LB_RECT_X );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.left );
    writer.String( LB_RECT_Y );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.top );
    writer.String( LB_RECT_W );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.right - value.left );
    writer.String( LB_RECT_H );
    CJsonObject<ESFloat>::Write<Writer>(writer, value.bottom - value.top );
    writer.EndObject();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ST_ES_RECT_F& value )
   {
    if ( json.IsObject() &&
      json.HasMember( LB_RECT_X ) &&
      json.HasMember( LB_RECT_Y ) &&
      json.HasMember( LB_RECT_W ) &&
      json.HasMember( LB_RECT_H ) ){
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_RECT_X], value.left );
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_RECT_Y], value.top );
     ESFloat w;
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_RECT_W], w );
     value.right = value.left + w;
     ESFloat h;
     CJsonObject<ESFloat>::Read<JsonValue>(json[LB_RECT_H], h );
     value.bottom = value.top + h;
     return 0;
    } else {
     return 1;
    }
   }
  };
 };
};
