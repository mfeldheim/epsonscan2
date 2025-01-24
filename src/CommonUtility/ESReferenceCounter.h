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
//  ESReferenceCounter.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../Include/es2CommnoType.h"
#include <assert.h>
class CESReferenceCounter
{
public:
 CESReferenceCounter(void){
  m_lRefCounter = 0;
 }
 virtual ~CESReferenceCounter(void){
 }
 LONG IncrementReference(){
#ifdef WIN32
  return InterlockedIncrement(&m_lRefCounter);
#else
  CBlockCriticalSection sec(m_sec);
  m_lRefCounter++;
  return m_lRefCounter;
#endif
 }
 LONG DecrementReference(){
#ifdef WIN32
  return InterlockedDecrement(&m_lRefCounter);
#else
  CBlockCriticalSection sec(m_sec);
  m_lRefCounter--;
  return m_lRefCounter;
#endif
 }
 LONG GetReferenceCounter(){
  return m_lRefCounter;
 }
private:
 LONG m_lRefCounter;
#ifndef WIN32
 CritSec m_sec;
#endif
};
