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
//  ESAccessor.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/ESCommonTypedef.h"
#include <functional>
#include "ESDebugLog.h"
#define PROPERTY_RW(key,theClass,typeRead,fnRead,typeWrite,fnWrite) \
 m_mapAccessor[ key ] = CESAccessor( \
       std::function<typeRead(void)>(std::bind( &theClass::fnRead, this)), \
       std::function<ESErrorCode(typeWrite)>(std::bind( &theClass::fnWrite, this, std::placeholders::_1)) )
#define PROPERTY_R(key,theClass,typeRead,fnRead) \
 m_mapAccessor[ key ] = CESAccessor( \
       std::function<typeRead(void)>(std::bind( &theClass::fnRead, this)) )
class CESAccessor{
public:
 CESAccessor()
  : m_pGetter(nullptr),m_pSetter(nullptr),m_bReadOnly(false)
 {}
 template < typename _GetterValueType, typename _SetterValueType>
 CESAccessor(std::function<_GetterValueType(void)> fnGetter,
             std::function<ESErrorCode(_SetterValueType)> fnSetter )
  : m_pGetter(new CGetterFunc<_GetterValueType>(fnGetter))
  , m_pSetter(new CSetterFunc<_SetterValueType>(fnSetter))
 {
  m_bReadOnly = false;
 }
 template < typename _GetterValueType >
 CESAccessor(std::function<_GetterValueType(void)> fnGetter)
  : m_pGetter(new CGetterFunc<_GetterValueType>(fnGetter))
  , m_pSetter(nullptr)
 {
  m_bReadOnly = true;
 }
 CESAccessor(const CESAccessor& rhs)
 {
  m_bReadOnly = rhs.m_bReadOnly;
  if (rhs.m_pGetter){
   m_pGetter = rhs.m_pGetter->Clone();
  } else {
   m_pGetter = nullptr;
  }
  if (rhs.m_pSetter){
   m_pSetter = rhs.m_pSetter->Clone();
  } else {
   m_pSetter = nullptr;
  }
 }
 virtual ~CESAccessor()
 {
  if (m_pGetter){
   delete m_pGetter;
   m_pGetter = nullptr;
  }
  if (m_pSetter){
   delete m_pSetter;
   m_pSetter = nullptr;
  }
 }
 CESAccessor& operator = (const CESAccessor& rhs)
 {
  if (this != &rhs){
   m_bReadOnly = rhs.m_bReadOnly;
   if (m_pGetter){
    delete m_pGetter;
    m_pGetter = nullptr;
   }
   if (m_pSetter){
    delete m_pSetter;
    m_pSetter = nullptr;
   }
   if (rhs.m_pGetter){
    m_pGetter = rhs.m_pGetter->Clone();
   }
   if (rhs.m_pSetter){
    m_pSetter = rhs.m_pSetter->Clone();
   }
  }
  return *this;
 }
public:
 ESErrorCode SetValue(ESAny& anyIn)
 {
  if(m_bReadOnly){
   return kESErrorFatalError;
  }
  if (m_pSetter){
   return m_pSetter->SetValue(anyIn);
  }else{
   ES_Error_Log(this,ES_STRING("Wrong Property set!!"));
   return kESErrorFatalError;
  }
 }
 ESErrorCode GetValue(ESAny& anyOut)
 {
  if (m_pGetter){
   anyOut = m_pGetter->GetValue();
   return kESErrorNoError;
  } else{
   ES_Error_Log(this,ES_STRING("Wrong Property get!!"));
   return kESErrorFatalError;
  }
 }
protected:
 class IGetterFunc
 {
 public:
  virtual ~IGetterFunc(){}
  virtual ESAny GetValue() = 0;
  virtual IGetterFunc* Clone() = 0;
 };
 template < typename _ValueType >
 class CGetterFunc : public IGetterFunc
 {
 public:
  CGetterFunc(std::function<_ValueType(void)> func)
   : m_func(func)
  {
  }
  CGetterFunc(const CGetterFunc& rhs)
   : m_func(rhs.m_func)
  {
  }
  virtual IGetterFunc* Clone()
  {
   try {
    return new CGetterFunc<_ValueType>(m_func);
   } catch(...){
    ES_Error_Log(this, ES_STRING("Memory Allocate Error."));
    return nullptr;
   }
  }
  virtual ESAny GetValue()
  {
   try {
    return (_ValueType)m_func();
   } catch(...){
    ES_Error_Log(this, _T("Unknown Exception."));
    return nullptr;
   }
  }
 protected:
  std::function<_ValueType(void)> m_func;
 };
 class ISetterFunc
 {
 public:
  virtual ~ISetterFunc(){}
  virtual ESErrorCode SetValue(ESAny value) = 0;
  virtual ISetterFunc* Clone() = 0;
 };
 template < typename _ValueType>
 class CSetterFunc : public ISetterFunc
 {
 public:
  CSetterFunc(std::function<ESErrorCode(_ValueType)> func)
   : m_func( func )
  {
  }
  CSetterFunc(const CSetterFunc& rhs)
   : m_func(rhs.func)
  {
  }
  virtual ISetterFunc* Clone()
  {
   try {
    return new CSetterFunc<_ValueType>(m_func);
   } catch(...){
    ES_Error_Log(this, _T("Memory Allocate Error."));
    return NULL;
   }
  }
  virtual ESErrorCode SetValue(ESAny value)
  {
   try {
    if (strcmp(typeid(_ValueType).name(), value.type().name()) != 0){
     ES_Error_Log(this,_T("Wrong type Property set!!"));
     return kESErrorFatalError;
    } else {
     return m_func(boost::any_cast<_ValueType>(value));
    }
   } catch(const boost::bad_any_cast&) {
    ES_Error_Log(this, _T("Bad cast."));
    return kESErrorFatalError;
   } catch(...){
    ES_Error_Log(this, _T("Unknown Exception."));
    return kESErrorFatalError;
   }
  }
 protected:
  std::function<ESErrorCode(_ValueType)> m_func;
 };
private:
 IGetterFunc* m_pGetter;
 ISetterFunc* m_pSetter;
 bool m_bReadOnly;
};
typedef std::map< ESString, CESAccessor > ACCESSOR_MAP;
typedef ACCESSOR_MAP::value_type ACCESSOR_MAP_PAIR;
