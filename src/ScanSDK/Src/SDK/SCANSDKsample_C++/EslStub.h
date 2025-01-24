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
//  EslStub.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#ifndef WIN32
#define WINAPI 
#endif
#include <dlfcn.h>
#include <cassert>
#include "ESCANLIB.h"
typedef BOOL WINAPI tfeslInit(DWORD* pInstance, LPCSTR pszKey, DWORD* pErrCode);
typedef BOOL WINAPI tfeslFree(const DWORD Instance, DWORD* pErrCode);
typedef BOOL WINAPI tfeslOpenScanner(const DWORD Instance, const ConnectInfo* pScanner, DWORD* pErrCode);
typedef BOOL WINAPI tfeslCtrlParameter(const DWORD Instance, const eParamOpType OpType, EslParamHdr* pParam, DWORD* pErrCode);
typedef BOOL WINAPI tfeslExecute(const DWORD Instance, const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate, DWORD* pErrCode);
typedef BOOL WINAPI tfeslCloseScanner(const DWORD Instance, DWORD* pErrCode);
typedef BOOL WINAPI tfeslGetDeviceStatus(const DWORD Instance, DWORD* pStatus, DWORD* pErrCode);
typedef BOOL WINAPI tfeslGetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, INT* select);
typedef BOOL WINAPI tfeslSetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, const INT setparam);
class CEslStub {
public:
 CEslStub(LPCTSTR pszLibModule);
 ~CEslStub();
 void Exit(void);
 BOOL eslInit(DWORD* pInstance, LPCSTR pszKey, DWORD* pErrCode);
 BOOL eslFree(const DWORD Instance, DWORD* pErrCode);
 BOOL eslOpenScanner(const DWORD Instance, const ConnectInfo* pScanner, DWORD* pErrCode);
 BOOL eslCtrlParameter(const DWORD Instance, const eParamOpType OpType, EslParamHdr* pParam, DWORD* pErrCode);
 BOOL eslExecute(const DWORD Instance, const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate, DWORD* pErrCode);
 BOOL eslCloseScanner(const DWORD Instance, DWORD* pErrCode);
 BOOL eslGetDeviceStatus(const DWORD Instance, DWORD* pStatus, DWORD* pErrCode);
 BOOL eslGetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, INT* select);
 BOOL eslSetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, const INT setparam);
protected:
 void* es2lib_;
 tfeslInit* m_peslInit;
 tfeslFree* m_peslFree;
 tfeslOpenScanner* m_peslOpenScanner;
 tfeslCtrlParameter* m_peslCtrlParameter;
 tfeslExecute* m_peslExecute;
 tfeslCloseScanner* m_peslCloseScanner;
 tfeslGetDeviceStatus* m_peslGetDeviceStatus;
 tfeslGetSettingParameter* m_peslGetSettingParameter;
 tfeslSetSettingParameter* m_peslSetSettingParameter;
};
