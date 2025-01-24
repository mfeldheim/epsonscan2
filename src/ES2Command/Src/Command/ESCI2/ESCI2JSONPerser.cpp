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
//  ESCI2JSONPerser.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include <string>
#include "CommonUtility/utils/ESBuffer.h"
#include "ESCI2JSONPerser.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>
#include <assert.h>
using namespace rapidjson;
using namespace std;
struct RapidJSONHandler
{
 ESDictionaryA& root;
 ESAnyArray containerStack;
 std::string cureKey;
 RapidJSONHandler(ESDictionaryA& dict)
  : root(dict)
 {
 }
 template<class T>
 bool storeValue(T value, bool isAddcontainer = false)
 {
  if (!cureKey.empty()){
   ESDictionaryA* dict;
   ESAny& back = containerStack.back();
   if (back.type().name() == typeid(ESDictionaryA*).name())
   {
    dict = boost::any_cast<ESDictionaryA*>(back);
   }
   else
   {
    return false;
   }
   (*dict)[cureKey] = value;
   if (isAddcontainer){
    containerStack.push_back(&boost::any_cast<T&>((*dict)[cureKey]));
   }
   cureKey.clear();
  } else {
   ESAny& back = containerStack.back();
   if (back.type().name() != typeid(ESAnyArray*).name()){
    return false;
   }
   ESAnyArray* ar = boost::any_cast<ESAnyArray*>(back);
   ar->push_back(value);
   if (isAddcontainer){
    containerStack.push_back(&boost::any_cast<T&>(ar->back()));
   }
  }
  return true;
 }
#pragma mark - Callbacks
 bool Null()
 {
  storeValue(nullptr);
  return true;
 }
 bool Bool(bool b)
 {
  storeValue(b);
  return true;
 }
 bool Int(int i)
 {
  storeValue((ESNumber)i);
  return true;
 }
 bool Uint(unsigned u)
 {
  storeValue((ESNumber) u);
  return true;
 }
 bool Int64(int64_t i)
 {
  storeValue((SInt64)i);
  return true;
 }
 bool Uint64(uint64_t u)
 {
  storeValue((UInt64)u);
  return true;
 }
 bool Double(double d)
 {
  storeValue((ESFloat)d);
  return true;
 }
 bool RawNumber(const char* str, SizeType length, bool copy)
 {
  storeValue(string(str, str+length));
  return true;
 }
 bool String(const char* str, SizeType length, bool copy)
 {
  storeValue(string(str, str+length));
  return true;
 }
 bool StartObject()
 {
  if (containerStack.size() == 0 ){
   containerStack.push_back(&root);
  } else {
   storeValue(ESDictionaryA(), true);
  }
  return true;
 }
 bool Key(const char* str, SizeType length, bool copy)
 {
  cureKey.assign(str, str+length);
  return true;
 }
 bool EndObject(SizeType memberCount)
 {
  if (containerStack.back().type().name() != typeid(ESDictionaryA*).name()){
   return false;
  }
  containerStack.pop_back();
  return true;
 }
 bool StartArray()
 {
  storeValue(ESAnyArray(), true);
  return true;
 }
    bool EndArray(SizeType elementCount)
    {
  if (containerStack.back().type() != typeid(ESAnyArray*)){
   return false;
  }
  containerStack.pop_back();
  return true;
 }
};
bool CESCI2JSONPerser::ParseWithData(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cData, ESDictionaryA& dict)
{
 try {
  string data(cData.GetBufferPtr(), cData.GetBufferPtr()+cData.GetLength());
  RapidJSONHandler handler(dict);
  Reader reader;
  StringStream ss(data.c_str());
  ParseResult res = reader.Parse(ss, handler);
  assert(res.Code() == kParseErrorNone);
  return (res.Code() == kParseErrorNone);
 } catch(...){
  return false;
 }
}
