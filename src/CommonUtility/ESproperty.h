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
//  ESproperty.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "ESCommonTypedef.h"
#include "DbgLog.h"
class CESProperty{
public:
 CESProperty()
 {
  m_bReadOnly = FALSE;
 }
 explicit CESProperty(ESAny anyIn,BOOL bReadOnly = FALSE)
 {
  m_bReadOnly = bReadOnly;
  m_anyValue =anyIn;
  m_strTypeName =anyIn.type().name();
 }
 explicit CESProperty(ESStringA strTypeName,BOOL bReadOnly = FALSE)
 {
  m_bReadOnly = bReadOnly;
  ESAny empty;
  m_anyValue =empty;
  m_strTypeName =strTypeName;
 }
 CESProperty( const CESProperty& rhs )
 {
  m_bReadOnly = rhs.m_bReadOnly;
  m_anyValue = rhs.m_anyValue;
  m_strTypeName = rhs.m_strTypeName;
 }
 ~CESProperty()
 {
 }
 CESProperty& operator = ( const CESProperty& rhs )
 {
  m_bReadOnly = rhs.m_bReadOnly;
  m_anyValue = rhs.m_anyValue;
  m_strTypeName = rhs.m_strTypeName;
  return *this;
 }
public:
 BOOL SetValue(const ESAny& anyIn)
 {
  if(m_bReadOnly){
   return FALSE;
  }
  if ( anyIn.type().name() == m_strTypeName ){
   m_anyValue = anyIn;
   return TRUE;
  }else{
   ES_Error_Log(this, ES_STRING("Wrong type Property set!!"));
   return FALSE;
  }
 }
 ESAny GetValue()
 {
  return m_anyValue;
 }
private:
 BOOL m_bReadOnly;
 ESAny m_anyValue;
 ESStringA m_strTypeName;
};
typedef std::unordered_map< ESString, CESProperty > PROPERTY_MAP;
typedef PROPERTY_MAP::value_type PROPERTY_MAP_PAIR;
