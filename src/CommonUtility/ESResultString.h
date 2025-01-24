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
//  ESResultString.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "ESCommonTypedef.h"
class IESResultString {
public:
 virtual ~IESResultString() {
 }
 virtual bool Set(const ES_CHAR *pszString) = 0;
 virtual const ES_CHAR *Get() = 0;
};
class CESResultString : public IESResultString{
public:
 CESResultString() {
  m_String.clear();
 }
 virtual ~CESResultString() {
  m_String.clear();
 }
 virtual bool Set(const ES_CHAR *pszString) {
  if (!pszString){
   return false;
  }
  try {
   m_String = pszString;
  }
  catch (const std::bad_alloc &) {
   _ASSERT(FALSE);
   return false;
  }
  return true;
 }
 virtual const ES_CHAR *Get() {
  return m_String.c_str();
 }
 ESString m_String;
};
