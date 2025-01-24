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
//  stringutils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCommonTypedef.h"
namespace ES_CMN_FUNCS
{
 namespace STRING
 {
  ESStringW MBStringToUnicode(const ESStringA& strSrcA);
  ESStringA UnicodeToMBString(const ESStringW& strSrcW);
  ESStringA UnicodeToUTF8(const ESStringW& strSrcW);
  ESStringW UTF8ToUnincode(const ESStringA& strSrcA);
  ESStringW ReplaceStr( ESStringW StringIn, ESStringW StringSrc, ESStringW StringNew );
#ifndef __ES_CMN_CONVERT_STRING__
#define __ES_CMN_CONVERT_STRING__ 
 #ifdef WIN32
  inline ESString ToESString(const ESStringA& s){
   return MBStringToUnicode(s);
  }
  inline ESString ToESString(const ES_CHAR_A* s){
   return MBStringToUnicode(s);
  }
  inline ESString ToESString(const ESStringW& s){
   return s;
  }
  inline ESString ToESString(const ES_CHAR_W* s){
   return s;
  }
 #else
  inline ESString ToESString(const ESStringA& s){
   return s;
  }
  inline ESString ToESString(const ES_CHAR_A* s){
   return s;
  }
  inline ESString ToESString(const ESStringW& s){
   return UnicodeToMBString(s);
  }
  inline ESString ToESString(const ES_CHAR_W* s){
   return UnicodeToMBString(s);
  }
 #endif
#endif
 }
}
