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
//  CritSec.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "CritSec.h"
#ifdef WIN32
CritSec::InitializeCriticalSectionExProc CritSec::s_fpInitProc = NULL;
void CritSec::InitializeCriticalSectionEx(CRITICAL_SECTION& section)
{
 DWORDLONG dwlConditionMask = 0;
 OSVERSIONINFOEX osVer = {0 };
 osVer.dwMajorVersion = 6;
 VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
 if(s_fpInitProc == NULL && ::VerifyVersionInfo(&osVer, VER_MAJORVERSION, dwlConditionMask)){
  HMODULE hInst = ::LoadLibrary(TEXT("kernel32.dll"));
  if(hInst){
   s_fpInitProc = (InitializeCriticalSectionExProc)GetProcAddress(hInst, "InitializeCriticalSectionEx");
  }
 }
 if(s_fpInitProc){
  (*s_fpInitProc)(&section, 4000, CRITICAL_SECTION_NO_DEBUG_INFO);
 }
 else{
  InitializeCriticalSection( &section );
 }
}
#endif
