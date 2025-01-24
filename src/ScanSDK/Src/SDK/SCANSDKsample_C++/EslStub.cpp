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
//  EslStub.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "EslStub.h"
#include <iostream>
#define SCANSDK_DLL_X86_64 "/usr/lib/x86_64-linux-gnu/epsonscan2/libepsonscansdk.so"
#define SCANSDK_DLL_ARM "/usr/lib/aarch64-linux-gnu/epsonscan2/libepsonscansdk.so"
#define SCANSDK_DLL_MIPS "/usr/lib/mips64el-linux-gnuabi64/epsonscan2/libepsonscansdk.so"
#define SCANSDK_DLL_LOONGARCH "/usr/lib/loongarch64-linux-gnu/epsonscan2/libepsonscansdk.so"
CEslStub::CEslStub(LPCTSTR pszLibModule) :
es2lib_(NULL),
m_peslInit(NULL),
m_peslFree(NULL),
m_peslOpenScanner(NULL),
m_peslCtrlParameter(NULL),
m_peslExecute(NULL),
m_peslCloseScanner(NULL),
m_peslGetDeviceStatus(NULL),
m_peslGetSettingParameter(NULL),
m_peslSetSettingParameter(NULL)
{
 std::cout << "[INFO]CEslStub Constracter\n" << std::endl;
    if(dlopen(SCANSDK_DLL_X86_64, RTLD_LAZY) != NULL){
        es2lib_ = dlopen(SCANSDK_DLL_X86_64, RTLD_LAZY);
    }else if(dlopen(SCANSDK_DLL_ARM, RTLD_LAZY) != NULL){
        es2lib_ = dlopen(SCANSDK_DLL_ARM, RTLD_LAZY);
    }else if(dlopen(SCANSDK_DLL_MIPS, RTLD_LAZY) != NULL){
        es2lib_ = dlopen(SCANSDK_DLL_MIPS, RTLD_LAZY);
    }else if(dlopen(SCANSDK_DLL_LOONGARCH, RTLD_LAZY) != NULL){
        es2lib_ = dlopen(SCANSDK_DLL_LOONGARCH, RTLD_LAZY);
    }else{
        std::cout << "[ERROR]libepsonscansdk.so not found." << std::endl;
        Exit();
    }
 m_peslInit = (tfeslInit*)dlsym(es2lib_, "eslInit");
 m_peslFree = (tfeslFree*)dlsym(es2lib_, "eslFree");
 m_peslOpenScanner = (tfeslOpenScanner*)dlsym(es2lib_, "eslOpenScanner");
 m_peslCtrlParameter = (tfeslCtrlParameter*)dlsym(es2lib_, "eslCtrlParameter");
 m_peslExecute = (tfeslExecute*)dlsym(es2lib_, "eslExecute");
 m_peslCloseScanner = (tfeslCloseScanner*)dlsym(es2lib_, "eslCloseScanner");
 m_peslGetDeviceStatus = (tfeslGetDeviceStatus*)dlsym(es2lib_, "eslGetDeviceStatus");
 m_peslGetSettingParameter = (tfeslGetSettingParameter*)dlsym(es2lib_, "eslGetSettingParameter");
 m_peslSetSettingParameter = (tfeslSetSettingParameter*)dlsym(es2lib_, "eslSetSettingParameter");
 if (m_peslInit && m_peslFree && m_peslOpenScanner && m_peslCtrlParameter
  && m_peslExecute && m_peslCloseScanner && m_peslGetDeviceStatus
  && m_peslGetSettingParameter && m_peslSetSettingParameter) {
  std::cout << "[INFO]Required function pointers READY\n" << std::endl;
  return;
 } else {
  std::cout << "[ERROR]Required function pointers NOT READY\n" << std::endl;
  Exit();
 }
}
CEslStub::~CEslStub()
{
 Exit();
}
void CEslStub::Exit()
{
 if (es2lib_ != NULL) {
       dlclose(es2lib_);
     es2lib_ = NULL;
  m_peslInit = NULL;
  m_peslFree = NULL;
  m_peslOpenScanner = NULL;
  m_peslCtrlParameter = NULL;
  m_peslExecute = NULL;
  m_peslCloseScanner = NULL;
  m_peslGetDeviceStatus = NULL;
  m_peslGetSettingParameter = NULL;
  m_peslSetSettingParameter = NULL;
 }
}
BOOL CEslStub::eslInit(DWORD* pInstance, LPCSTR pszKey, DWORD* pErrCode)
{
 if (NULL == m_peslInit) {
  *pErrCode = 1;
  return FALSE;
 }
 return m_peslInit(pInstance, pszKey, pErrCode);
}
BOOL CEslStub::eslFree(const DWORD Instance, DWORD* pErrCode)
{
 if (NULL == m_peslFree) {
  return FALSE;
 }
 return m_peslFree(Instance, pErrCode);
}
BOOL CEslStub::eslOpenScanner(const DWORD Instance, const ConnectInfo* pScanner, DWORD* pErrCode)
{
 if (NULL == m_peslOpenScanner) {
  return FALSE;
 }
 return m_peslOpenScanner(Instance, pScanner, pErrCode);
}
BOOL CEslStub::eslCtrlParameter(const DWORD Instance, const eParamOpType OpType, EslParamHdr* pParam, DWORD* pErrCode)
{
 if (NULL == m_peslCtrlParameter) {
  return FALSE;
 }
 return m_peslCtrlParameter(Instance, OpType, pParam, pErrCode);
}
BOOL CEslStub::eslExecute(const DWORD Instance, const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate, DWORD* pErrCode)
{
 if (NULL == m_peslExecute) {
  return FALSE;
 }
 return m_peslExecute(Instance, ExecType, pCbFunc, pPrivate, pErrCode);
}
BOOL CEslStub::eslCloseScanner(const DWORD Instance, DWORD* pErrCode)
{
 if (NULL == m_peslCloseScanner) {
  return FALSE;
 }
 return m_peslCloseScanner(Instance, pErrCode);
}
BOOL CEslStub::eslGetDeviceStatus(const DWORD Instance, DWORD* pStatus, DWORD* pErrCode)
{
 if (NULL == m_peslGetDeviceStatus) {
  return FALSE;
 }
 return m_peslGetDeviceStatus(Instance, pStatus, pErrCode);
}
BOOL CEslStub::eslGetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, INT* select)
{
 if (NULL == m_peslGetSettingParameter) {
  return FALSE;
 }
 return m_peslGetSettingParameter(Instance, SpecifiedParameter, pErrCode, select);
}
BOOL CEslStub::eslSetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, const INT setparam)
{
 if (NULL == m_peslSetSettingParameter) {
  return FALSE;
 }
 return m_peslSetSettingParameter(Instance, SpecifiedParameter, pErrCode, setparam);
}
