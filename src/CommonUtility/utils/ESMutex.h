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
//  ESMutex.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCommonTypedef.h"
#ifdef WIN32
#include <Windows.h>
#endif
class CESMutex
{
private:
 HANDLE m_hMutex;
public:
 CESMutex(void);
 virtual ~CESMutex(void);
 BOOL InitMutex(LPCTSTR strMutexName,BOOL* pbAlreadyExist = NULL);
 static BOOL IsExistMutex(LPCTSTR strMutexName);
 BOOL EnterMutex();
 void Release();
 void CloseMutex();
};
class CBlockMutex
{
public:
 explicit CBlockMutex(CESMutex& mutex)
 {
  m_pMutex = &mutex;
  m_pMutex->EnterMutex();
 }
 ~CBlockMutex()
 {
  m_pMutex->Release();
 }
private:
 CESMutex* m_pMutex;
};
