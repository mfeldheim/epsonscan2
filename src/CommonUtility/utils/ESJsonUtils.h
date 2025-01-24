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
//  ESJsonUtils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCommonTypedef.h"
namespace ES_CMN_FUNCS
{
 namespace JSON
 {
  STATIC_CONST_KEY TYPE_NO_DATA = ES_STRING("no_data");
  STATIC_CONST_KEY TYPE_INT = ES_STRING("int");
  STATIC_CONST_KEY TYPE_INT_U = ES_STRING("int_u");
  STATIC_CONST_KEY TYPE_FLOAT = ES_STRING("float");
  STATIC_CONST_KEY TYPE_BOOLEAN = ES_STRING("boolean");
  STATIC_CONST_KEY TYPE_INDEX = ES_STRING("index");
  STATIC_CONST_KEY TYPE_ARRAY = ES_STRING("array");
  STATIC_CONST_KEY TYPE_ARRAY_U = ES_STRING("array_u");
  STATIC_CONST_KEY TYPE_ARRAY_F = ES_STRING("array_f");
  STATIC_CONST_KEY TYPE_ARRAY_STR = ES_STRING("array_str");
  STATIC_CONST_KEY TYPE_ARRAY_BYTE = ES_STRING("array_byte");
  STATIC_CONST_KEY TYPE_MULTI_ARRAY = ES_STRING("multi_array");
  STATIC_CONST_KEY TYPE_MULTI_ARRAY_U = ES_STRING("multi_array_u");
  STATIC_CONST_KEY TYPE_MULTI_ARRAY_F = ES_STRING("multi_array_f");
  STATIC_CONST_KEY TYPE_MULTI_ARRAY_STR = ES_STRING("multi_array_str");
  STATIC_CONST_KEY TYPE_STRING = ES_STRING("string");
  STATIC_CONST_KEY TYPE_RANGE = ES_STRING("range");
  STATIC_CONST_KEY TYPE_RANGE_U = ES_STRING("range_u");
  STATIC_CONST_KEY TYPE_RANGE_F = ES_STRING("range_f");
  STATIC_CONST_KEY TYPE_SIZE = ES_STRING("size");
  STATIC_CONST_KEY TYPE_SIZE_U = ES_STRING("size_u");
  STATIC_CONST_KEY TYPE_SIZE_F = ES_STRING("size_f");
  STATIC_CONST_KEY TYPE_RECT = ES_STRING("rect");
  STATIC_CONST_KEY TYPE_RECT_U = ES_STRING("rect_u");
  STATIC_CONST_KEY TYPE_RECT_F = ES_STRING("rect_f");
  STATIC_CONST_KEY TYPE_POINT = ES_STRING("point");
  STATIC_CONST_KEY TYPE_POINT_U = ES_STRING("point_u");
  STATIC_CONST_KEY TYPE_POINT_F = ES_STRING("point_f");
  STATIC_CONST_KEY LB_RANGE_MIN = ES_STRING("min");
  STATIC_CONST_KEY LB_RANGE_MAX = ES_STRING("max");
  STATIC_CONST_KEY LB_RANGE_STEP = ES_STRING("step");
  STATIC_CONST_KEY LB_SIZE_X = ES_STRING("x");
  STATIC_CONST_KEY LB_SIZE_Y = ES_STRING("y");
  STATIC_CONST_KEY LB_RECT_X = ES_STRING("x");
  STATIC_CONST_KEY LB_RECT_Y = ES_STRING("y");
  STATIC_CONST_KEY LB_RECT_W = ES_STRING("w");
  STATIC_CONST_KEY LB_RECT_H = ES_STRING("h");
  STATIC_CONST_KEY LB_POINT_X = ES_STRING("x");
  STATIC_CONST_KEY LB_POINT_Y = ES_STRING("y");
  const UInt32 ES_JSON_INVALID_ERR = (UInt32)-1;
  UInt32 DictionaryToJSON( const ESDictionary& dicSrc, ESString& strDstJSON );
  UInt32 JSONtoDictionary( const ESString& strSrcJSON, ESDictionary& dicDst );
  UInt32 DictionaryToJSONFile( const ESDictionary& dicSrc, const ESString& strDstFile );
  UInt32 JSONFiletoDictionary( const ESString& strSrcFile, ESDictionary& dicDst );
 };
};
