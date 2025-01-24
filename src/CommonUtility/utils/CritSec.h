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
//  CritSec.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#ifdef WIN32
#include <Windows.h>
#else
#include <mutex>
#endif
class CritSec
{
public:
#ifdef WIN32
 CritSec()
 {
  InitializeCriticalSectionEx(m_CriticalSection);
 }
 ~CritSec()
 {
  DeleteCriticalSection( &m_CriticalSection );
 }
 void Lock()
 {
  EnterCriticalSection(&m_CriticalSection);
 }
 void Unlock()
 {
  LeaveCriticalSection(&m_CriticalSection);
 }
 typedef BOOL (WINAPI *InitializeCriticalSectionExProc)(
  LPCRITICAL_SECTION lpCriticalSection,
  DWORD dwSpinCount,
  DWORD Flags
 );
 static void InitializeCriticalSectionEx(CRITICAL_SECTION& section);
public:
 CRITICAL_SECTION m_CriticalSection;
private:
 static InitializeCriticalSectionExProc s_fpInitProc;
};
#else
 CritSec()
 {
 }
 ~CritSec()
 {
 }
 void Unlock()
 {
  m_CriticalSection.unlock();
 }
 void Lock()
 {
  m_CriticalSection.lock();
 }
private:
 std::recursive_mutex m_CriticalSection;
};
#endif
class CBlockCriticalSection
{
public:
 explicit CBlockCriticalSection(CritSec& crit)
 {
  m_pCriticalSection = &crit;
  m_pCriticalSection->Lock();
 }
 ~CBlockCriticalSection()
 {
  m_pCriticalSection->Unlock();
 }
private:
 CritSec* m_pCriticalSection;
};
