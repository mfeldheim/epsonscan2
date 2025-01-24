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
//  JsonObjectAny.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "JsonCommon.h"
#include "JsonObject.hpp"
#include <typeinfo>
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  template< typename Writer, typename ValueType, typename ObjectType >
  static UInt32 WriteObject( Writer& writer, const ESAny& value )
  {
   UInt32 un32ErrCounter = 0;
   const ValueType* pV = boost::any_cast< ValueType >( &value );
   if ( pV != NULL ){
    writer.StartObject();
    {
     if ( CJsonObject<ObjectType>::Label() == NULL ){
      un32ErrCounter = 1;
     } else {
      writer.String( CJsonObject<ObjectType>::Label() );
      un32ErrCounter = CJsonObject<ObjectType>::template Write<Writer>( writer, *pV );
     }
    }
    writer.EndObject();
    return un32ErrCounter;
   } else {
    writer.StartObject();
    writer.EndObject();
    return 1;
   }
  }
  template< typename JsonValue, typename ValueType >
  static UInt32 ReadObject( const JsonValue& json, ESAny& anyDst )
  {
   ValueType v;
   anyDst = v;
   try {
    return CJsonObject<ValueType>::template Read<JsonValue>( json, *(boost::unsafe_any_cast<ValueType>(&anyDst)) );
   } catch(...){
    return 1;
   }
  }
  template<> class CJsonObject< ESAny > {
  public:
   static LPCTSTR Label(){ return NULL; }
   template< typename Writer >
   static UInt32 Write( Writer& writer, const ESAny& value )
   {
    typedef UInt32 (*PFN_PUSH_DATA)( Writer&, const ESAny& );
    typedef std::map< std::string, PFN_PUSH_DATA > FuncMap;
    typedef typename FuncMap::value_type MapPair;
    const MapPair c_MapList[] = {
     MapPair( typeid( nullptr ).name(), &CJsonNoDataObject::Write< Writer > ),
     MapPair( typeid( ESDictionary ).name(), &CJsonDictionaryObject::Write< Writer > ),
     MapPair( typeid( ESDicArray ).name(), &CJsonDicArrayObject::Write< Writer > ),
     MapPair( typeid( ESNumber ).name(), &WriteObject< Writer, ESNumber, ESNumber > ),
     MapPair( typeid( UInt8 ).name(), &WriteObject< Writer, UInt8, ESUnsigned > ),
     MapPair( typeid( ESUnsigned ).name(), &WriteObject< Writer, ESUnsigned, ESUnsigned > ),
     MapPair( typeid( ESFloat ).name(), &WriteObject< Writer, ESFloat, ESFloat > ),
     MapPair( typeid( double ).name(), &WriteObject< Writer, double, ESFloat > ),
     MapPair( typeid( bool ).name(), &WriteObject< Writer, bool, bool > ),
     MapPair( typeid( ESString ).name(), &WriteObject< Writer, ESString, ESString > ),
     MapPair( typeid( ES_CHAR_CPTR ).name(), &WriteObject< Writer, ES_CHAR_CPTR, ES_CHAR_CPTR > ),
     MapPair( typeid( ESIndexSet ).name(), &WriteObject< Writer, ESIndexSet, ESIndexSet > ),
     MapPair( typeid( ESIndexArray ).name(), &WriteObject< Writer, ESIndexArray, ESIndexArray > ),
     MapPair( typeid( ESUnsignedArray ).name(), &WriteObject< Writer, ESUnsignedArray, ESUnsignedArray > ),
     MapPair( typeid( ESFloatArray ).name(), &WriteObject< Writer, ESFloatArray, ESFloatArray > ),
     MapPair( typeid( ESStringArray ).name(), &WriteObject< Writer, ESStringArray, ESStringArray > ),
     MapPair( typeid( ESByteData ).name(), &WriteObject< Writer, ESByteData, ESByteData > ),
     MapPair( typeid( ESIndexMultiArray ).name(), &WriteObject< Writer, ESIndexMultiArray, ESIndexMultiArray > ),
     MapPair( typeid( ESUnsignedMultiArray ).name(), &WriteObject< Writer, ESUnsignedMultiArray, ESUnsignedMultiArray > ),
     MapPair( typeid( ESFloatMultiArray ).name(), &WriteObject< Writer, ESFloatMultiArray, ESFloatMultiArray > ),
     MapPair( typeid( ESStringMultiArray ).name(), &WriteObject< Writer, ESStringMultiArray, ESStringMultiArray > ),
     MapPair( typeid( ST_ES_RANGE ).name(), &WriteObject< Writer, ST_ES_RANGE, ST_ES_RANGE > ),
     MapPair( typeid( ST_ES_RANGE_UN32 ).name(), &WriteObject< Writer, ST_ES_RANGE_UN32, ST_ES_RANGE_UN32 > ),
     MapPair( typeid( ST_ES_RANGE_F ).name(), &WriteObject< Writer, ST_ES_RANGE_F, ST_ES_RANGE_F > ),
     MapPair( typeid( ST_ES_SIZE_S32 ).name(), &WriteObject< Writer, ST_ES_SIZE_S32, ST_ES_SIZE_S32 > ),
     MapPair( typeid( ST_ES_SIZE_UN32 ).name(), &WriteObject< Writer, ST_ES_SIZE_UN32, ST_ES_SIZE_UN32 > ),
     MapPair( typeid( ST_ES_SIZE_F ).name(), &WriteObject< Writer, ST_ES_SIZE_F, ST_ES_SIZE_F > ),
     MapPair( typeid( ST_ES_RECT_S32 ).name(), &WriteObject< Writer, ST_ES_RECT_S32, ST_ES_RECT_S32 > ),
     MapPair( typeid( ST_ES_RECT_UN32 ).name(), &WriteObject< Writer, ST_ES_RECT_UN32, ST_ES_RECT_UN32 > ),
     MapPair( typeid( ST_ES_RECT_F ).name(), &WriteObject< Writer, ST_ES_RECT_F, ST_ES_RECT_F > ),
     MapPair( typeid( ST_ES_POINT_S32 ).name(), &WriteObject< Writer, ST_ES_POINT_S32, ST_ES_POINT_S32 > ),
     MapPair( typeid( ST_ES_POINT_UN32 ).name(), &WriteObject< Writer, ST_ES_POINT_UN32, ST_ES_POINT_UN32 > ),
     MapPair( typeid( ST_ES_POINT_F ).name(), &WriteObject< Writer, ST_ES_POINT_F, ST_ES_POINT_F > ),
    };
    const FuncMap c_FuncMap( c_MapList, c_MapList + _countof( c_MapList ) );
    UInt32 un32ErrCounter = 0;
    if ( c_FuncMap.count( value.type().name() ) != 0 ) {
     un32ErrCounter += c_FuncMap.at( value.type().name() )( writer, value );
    } else {
     un32ErrCounter++;
     writer.StartObject();
     writer.EndObject();
    }
    return un32ErrCounter;
   }
   template< typename JsonValue >
   static UInt32 Read( const JsonValue& json, ESAny& anyDst )
   {
    typedef UInt32 (*PFN_POP_DATA )( const JsonValue&, ESAny& );
    typedef std::map< ESString, PFN_POP_DATA > FuncMap;
    typedef typename FuncMap::value_type MapPair;
    const MapPair c_MapList[] = {
     MapPair( CJsonNoDataObject::Label() , &CJsonNoDataObject::Read<JsonValue > ),
     MapPair( CJsonObject<ESNumber >::Label(), &ReadObject<JsonValue, ESNumber > ),
     MapPair( CJsonObject<ESUnsigned >::Label(), &ReadObject<JsonValue, ESUnsigned > ),
     MapPair( CJsonObject<ESFloat >::Label(), &ReadObject<JsonValue, ESFloat > ),
     MapPair( CJsonObject<bool >::Label(), &ReadObject<JsonValue, bool > ),
     MapPair( CJsonObject<ESString >::Label(), &ReadObject<JsonValue, ESString > ),
     MapPair( CJsonObject<ESIndexSet >::Label(), &ReadObject<JsonValue, ESIndexSet > ),
     MapPair( CJsonObject<ESIndexArray >::Label(), &ReadObject<JsonValue, ESIndexArray > ),
     MapPair( CJsonObject<ESUnsignedArray >::Label(), &ReadObject<JsonValue, ESUnsignedArray > ),
     MapPair( CJsonObject<ESFloatArray >::Label(), &ReadObject<JsonValue, ESFloatArray > ),
     MapPair( CJsonObject<ESStringArray >::Label(), &ReadObject<JsonValue, ESStringArray > ),
     MapPair( CJsonObject<ESByteData >::Label(), &ReadObject<JsonValue, ESByteData > ),
     MapPair( CJsonObject<ESIndexMultiArray >::Label(), &ReadObject<JsonValue, ESIndexMultiArray > ),
     MapPair( CJsonObject<ESUnsignedMultiArray >::Label(), &ReadObject<JsonValue, ESUnsignedMultiArray > ),
     MapPair( CJsonObject<ESFloatMultiArray >::Label(), &ReadObject<JsonValue, ESFloatMultiArray > ),
     MapPair( CJsonObject<ESStringMultiArray >::Label(), &ReadObject<JsonValue, ESStringMultiArray > ),
     MapPair( CJsonObject<ST_ES_RANGE >::Label(), &ReadObject<JsonValue, ST_ES_RANGE > ),
     MapPair( CJsonObject<ST_ES_RANGE_UN32 >::Label(), &ReadObject<JsonValue, ST_ES_RANGE_UN32 > ),
     MapPair( CJsonObject<ST_ES_RANGE_F >::Label(), &ReadObject<JsonValue, ST_ES_RANGE_F > ),
     MapPair( CJsonObject<ST_ES_SIZE_S32 >::Label(), &ReadObject<JsonValue, ST_ES_SIZE_S32 > ),
     MapPair( CJsonObject<ST_ES_SIZE_UN32 >::Label(), &ReadObject<JsonValue, ST_ES_SIZE_UN32 > ),
     MapPair( CJsonObject<ST_ES_SIZE_F >::Label(), &ReadObject<JsonValue, ST_ES_SIZE_F > ),
     MapPair( CJsonObject<ST_ES_RECT_S32 >::Label(), &ReadObject<JsonValue, ST_ES_RECT_S32 > ),
     MapPair( CJsonObject<ST_ES_RECT_UN32 >::Label(), &ReadObject<JsonValue, ST_ES_RECT_UN32 > ),
     MapPair( CJsonObject<ST_ES_RECT_F >::Label(), &ReadObject<JsonValue, ST_ES_RECT_F > ),
     MapPair( CJsonObject<ST_ES_POINT_S32 >::Label(), &ReadObject<JsonValue, ST_ES_POINT_S32 > ),
     MapPair( CJsonObject<ST_ES_POINT_UN32 >::Label(), &ReadObject<JsonValue, ST_ES_POINT_UN32 > ),
     MapPair( CJsonObject<ST_ES_POINT_F >::Label(), &ReadObject<JsonValue, ST_ES_POINT_F > ),
    };
    const FuncMap c_FuncMap( c_MapList, c_MapList + _countof( c_MapList ) );
    UInt32 un32ErrCounter = 0;
    if ( json.IsObject() ){
     auto itr = json.MemberBegin();
     if ( itr != json.MemberEnd() ){
      try {
       un32ErrCounter += c_FuncMap.at( itr->name.GetString() )( itr->value, anyDst );
      } catch(...){
       un32ErrCounter++;
      }
     } else {
      un32ErrCounter++;
     }
    } else if ( json.IsArray() ){
     for ( SizeType i = 0; i < json.Size(); i++){
      if ( json[i].IsObject() ){
       ESDictionary dic;
       anyDst = dic;
       try {
        un32ErrCounter += CJsonDictionaryObject::Read<JsonValue>( json[i], *(boost::unsafe_any_cast<ESDictionary>(&anyDst)) );
       } catch(...){
        un32ErrCounter++;
       }
      } else if ( json[i].IsArray() ){
       ESDicArray arDic;
       anyDst = arDic;
       try {
        un32ErrCounter += CJsonDicArrayObject::Read<JsonValue>( json[i], *(boost::unsafe_any_cast<ESDicArray>(&anyDst)) );
       } catch(...){
        un32ErrCounter++;
       }
      } else {
       un32ErrCounter++;
      }
     }
    } else {
     un32ErrCounter++;
    }
    return un32ErrCounter;
   }
  };
  template< typename Writer >
  UInt32 CJsonDictionaryObject::Write( Writer& writer, const ESAny& value )
  {
   UInt32 un32ErrCounter = 0;
   if ( const ESDictionary* pDic = boost::any_cast<ESDictionary>( &value ) ){
    writer.StartArray();
    {
     writer.StartObject();
     {
      for( ESDictionary::const_iterator it = pDic->begin(); it != pDic->end(); ++it ){
       writer.String( it->first.c_str() );
       un32ErrCounter += CJsonObject<ESAny>::Write< Writer >( writer, it->second );
      }
     }
     writer.EndObject();
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
  UInt32 CJsonDictionaryObject::Read( const JsonValue& json, ESDictionary& dicDst )
  {
   UInt32 un32ErrCounter = 0;
   for ( auto it = json.MemberBegin(); it != json.MemberEnd(); ++it ){
    un32ErrCounter += CJsonObject<ESAny>::Read<JsonValue>( it->value, dicDst[ it->name.GetString() ] );
   }
   return un32ErrCounter;
  }
 };
};
