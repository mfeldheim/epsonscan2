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
//  JsonObjectArray.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template<> class CJsonObject< ESIndexSet > {
  public:
   static LPCTSTR Label(){ return TYPE_INDEX; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESIndexSet& value )
   {
    writer.StartArray();
    for( ESIndexSet::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESNumber>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESIndexSet& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESNumber n;
      if ( CJsonObject<ESNumber>::Read<JsonValue>( json[i], n ) == 0 ){
       value.insert( n );
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
  template<> class CJsonObject< ESIndexArray > {
  public:
   static LPCTSTR Label(){ return TYPE_ARRAY; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESIndexArray& value )
   {
    writer.StartArray();
    for( ESIndexArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESNumber>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESIndexArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESNumber n;
      if ( CJsonObject<ESNumber>::Read<JsonValue>( json[i], n ) == 0 ){
       value.push_back( n );
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
  template<> class CJsonObject< ESUnsignedArray > {
  public:
   static LPCTSTR Label(){ return TYPE_ARRAY_U; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESUnsignedArray& value )
   {
    writer.StartArray();
    for( ESUnsignedArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESUnsigned>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESUnsignedArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESUnsigned u;
      if ( CJsonObject<ESUnsigned>::Read<JsonValue>( json[i], u ) == 0 ){
       value.push_back( u );
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
  template<> class CJsonObject< ESFloatArray > {
  public:
   static LPCTSTR Label(){ return TYPE_ARRAY_F; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESFloatArray& value )
   {
    writer.StartArray();
    for( ESFloatArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESFloat>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESFloatArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESFloat f;
      if ( CJsonObject<ESFloat>::Read<JsonValue>( json[i], f ) == 0 ){
       value.push_back( f );
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
  template<> class CJsonObject< ESStringArray > {
  public:
   static LPCTSTR Label(){ return TYPE_ARRAY_STR; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESStringArray& value )
   {
    writer.StartArray();
    for( ESStringArray::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESString>::Write<Writer>(writer, *it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESStringArray& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESString s;
      if ( CJsonObject<ESString>::Read<JsonValue>( json[i], s ) == 0 ){
       value.push_back( s );
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
  template<> class CJsonObject< ESByteData > {
  public:
   static LPCTSTR Label(){ return TYPE_ARRAY_BYTE; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESByteData& value )
   {
    writer.StartArray();
    for( ESByteData::const_iterator it = value.begin(); it != value.end(); ++it ){
     CJsonObject<ESNumber>::Write<Writer>(writer, (ESNumber)*it );
    }
    writer.EndArray();
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESByteData& value )
   {
    UInt32 un32Ret = 0;
    if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      ESNumber n;
      if ( CJsonObject<ESNumber>::Read<JsonValue>( json[i], n ) == 0 ){
       value.push_back( (UInt8)n );
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
