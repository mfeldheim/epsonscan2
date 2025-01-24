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
//  JsonObjectMultiArray.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
#include "JsonObjectArray.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template<> class CJsonObject< ESIndexMultiArray > {
  public:
   static LPCTSTR Label(){ return TYPE_MULTI_ARRAY; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESIndexMultiArray& value )
   {
    writer.StartArray();
    for( ESIndexMultiArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESIndexArray>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESIndexMultiArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESIndexArray ar;
      if ( CJsonObject<ESIndexArray>::Read<JsonValue>( json[i], ar ) == 0 ){
       value.push_back( ar );
      } else {
       un32Ret = 1;
      }
     }
    } else {
     return 1;
    }
    return un32Ret;
   }
  };
  template<> class CJsonObject< ESUnsignedMultiArray > {
  public:
   static LPCTSTR Label(){ return TYPE_MULTI_ARRAY_U; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESUnsignedMultiArray& value )
   {
    writer.StartArray();
    for( ESUnsignedMultiArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESUnsignedArray>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESUnsignedMultiArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESUnsignedArray ar;
      if ( CJsonObject<ESUnsignedArray>::Read<JsonValue>( json[i], ar ) == 0 ){
       value.push_back( ar );
      } else {
       un32Ret = 1;
      }
     }
    } else {
     return 1;
    }
    return un32Ret;
   }
  };
  template<> class CJsonObject< ESFloatMultiArray > {
  public:
   static LPCTSTR Label(){ return TYPE_MULTI_ARRAY_F; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESFloatMultiArray& value )
   {
    writer.StartArray();
    for( ESFloatMultiArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESFloatArray>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESFloatMultiArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESFloatArray ar;
      if ( CJsonObject<ESFloatArray>::Read<JsonValue>( json[i], ar ) == 0 ){
       value.push_back( ar );
      } else {
       un32Ret = 1;
      }
     }
    } else {
     return 1;
    }
    return un32Ret;
   }
  };
  template<> class CJsonObject< ESStringMultiArray > {
  public:
   static LPCTSTR Label(){ return TYPE_MULTI_ARRAY_STR; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESStringMultiArray& value )
   {
    writer.StartArray();
    for( ESStringMultiArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESStringArray>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESStringMultiArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESStringArray ar;
      if ( CJsonObject<ESStringArray>::Read<JsonValue>( json[i], ar ) == 0 ){
       value.push_back( ar );
      } else {
       un32Ret = 1;
      }
     }
    } else {
     return 1;
    }
    return un32Ret;
   }
  };
 };
};
