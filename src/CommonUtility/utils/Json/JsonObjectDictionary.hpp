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
//  JsonObjectDictionary.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  class CJsonDictionaryObject {
  public:
   static LPCTSTR Label(){ return NULL; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESAny& value );
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESDictionary& dicDst );
  };
  class CJsonDicArrayObject {
  public:
   static LPCTSTR Label(){ return NULL; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESAny& value )
   {
    UInt32 un32ErrCounter = 0;
    if ( const ESDicArray* pDicArray = boost::any_cast<ESDicArray>( &value ) ){
     writer.StartArray();
     {
      writer.StartArray();
      {
       for( ESDicArray::const_iterator it = pDicArray->begin(); it != pDicArray->end(); ++it ){
        un32ErrCounter += CJsonDictionaryObject::Write<Writer>( writer, *it );
       }
      }
      writer.EndArray();
     }
     writer.EndArray();
     return un32ErrCounter;
    } else {
     writer.StartObject();
     writer.EndObject();
     return 1;
    }
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESDicArray& arDic )
   {
    UInt32 un32ErrCounter = 0;
    for ( SizeType i = 0; i < json.Size(); i++){
     if ( !json[i].IsArray() ){
      un32ErrCounter++;
      continue;
     }
     for ( SizeType j = 0; j < json[i].Size(); j++){
      ESDictionary dicSub;
      arDic.push_back(dicSub);
      un32ErrCounter += CJsonDictionaryObject::Read<JsonValue>( json[i][j], arDic.back() );
     }
    }
    return un32ErrCounter;
   }
  };
 };
};
