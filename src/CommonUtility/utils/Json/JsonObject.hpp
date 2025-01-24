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
//  JsonObject.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template< typename ValueType >
  class CJsonObject {
  public:
   static LPCTSTR Label(){ return NULL; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ValueType& value ){
    return 1;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESNumber& value ){
    return 1;
   }
  };
  template<> class CJsonObject< ESNumber > {
  public:
   static LPCTSTR Label(){ return TYPE_INT; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESNumber& value )
   {
    writer.Int( (int)value );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESNumber& value )
   {
    if ( json.IsInt() ){
     value = (ESNumber)json.GetInt();
    } else if ( json.IsString() ){
#ifdef WIN32
     value = (ESNumber)_wtoi( json.GetString() );
#else
     value = (ESNumber)atoi( json.GetString() );
#endif
    } else {
     return 1;
    }
    return 0;
   }
  };
  template<> class CJsonObject< ESUnsigned > {
  public:
     static LPCTSTR Label(){ return TYPE_INT_U; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESUnsigned& value )
   {
    writer.Uint( (unsigned int)value );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESUnsigned& value )
   {
    if ( json.IsUint() ){
     value = (UInt32)json.GetUint();
    } else if ( json.IsInt() ){
     value = (UInt32)json.GetInt();
    } else if ( json.IsString() ){
#ifdef WIN32
     value = (UInt32)_wtoi( json.GetString() );
#else
     value = (UInt32)atoi( json.GetString() );
#endif
    } else {
     return 1;
    }
    return 0;
   }
  };
  template<> class CJsonObject< ESFloat > {
  public:
     static LPCTSTR Label(){ return TYPE_FLOAT; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESFloat& value )
   {
    char buffer[32] ={};
    sprintf_s( buffer, 32, "%f", value );
    double d = atof(buffer);
    writer.Double( d );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESFloat& value )
   {
    if ( json.IsDouble() ){
     value = (ESFloat)json.GetDouble();
    } else if ( json.IsInt() ){
     value = (ESFloat)json.GetInt();
    } else if ( json.IsUint() ){
     value = (ESFloat)json.GetUint();
    } else if ( json.IsString() ){
#ifdef WIN32
     value = (ESFloat)_wtof( json.GetString() );
#else
     value = (ESFloat)atof( json.GetString() );
#endif
    } else {
     return 1;
    }
    return 0;
   }
  };
  template<> class CJsonObject< bool > {
  public:
     static LPCTSTR Label(){ return TYPE_BOOLEAN; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const bool& value )
   {
    writer.Bool( value );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, bool& value )
   {
    if ( json.IsBool() ){
     value = json.GetBool();
    } else if ( json.IsString() ){
     ESString s = json.GetString();
     if ( s == ES_STRING("true") ){
      value = true;
     } else if ( s == ES_STRING("false") ){
      value = false;
     } else {
      return 1;
     }
    } else {
     return 1;
    }
    return 0;
   }
  };
  template<> class CJsonObject< ESString > {
  public:
     static LPCTSTR Label(){ return TYPE_STRING; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESString& value )
   {
    writer.String( value.c_str() );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESString& value )
   {
    if ( json.IsString() ){
     value = json.GetString();
    } else {
     return 1;
    }
    return 0;
   }
  };
  template<> class CJsonObject< ES_CHAR_CPTR > {
  public:
     static LPCTSTR Label(){ return TYPE_STRING; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ES_CHAR_CPTR& value )
   {
    writer.String( value );
    return 0;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ES_CHAR_CPTR& value )
   {
    return 1;
   }
  };
 };
};
