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
//  ESCANLIB.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "devicelist.h"
#include "LibHelper.h"
#include "InstanceMgr.h"
#include "supervisor.h"
#include <DbgLog.h>
#define SDI_TRACE_LOG(message,...) \
        AfxGetLog()->MessageLog(ENUM_LOG_LEVEL::LogLevelTrace,__FUNCTION__,__FILE__,__LINE__, message, ##__VA_ARGS__ )
CInstanceMgr* g_pInstMgr = NULL;
BOOL WINAPI eslInit(DWORD* pInstance, LPCSTR pszKey, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslInit");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  g_pInstMgr = new CInstanceMgr();
 }
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
   UNREFERENCED_PARAMETER(pszKey);
    *pInstance = g_pInstMgr->createScanMgr();
 if (*pInstance == 0) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr->createScanMgr failed");
  SetErrorCode(pErrCode, ESL_ERR_LOW_MEMORY);
  return FALSE;
 }
    return TRUE;
}
BOOL WINAPI eslFree(const DWORD Instance, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslFree");
    SetErrorCode(pErrCode, ESL_SUCCESS);
    if (g_pInstMgr) {
  if (!g_pInstMgr->getScanMgr(Instance)) {
   SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
   SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
   return FALSE;
  }else {
   SDI_TRACE_LOG("[INFO]ScanMgr Instance free successful");
   g_pInstMgr->getScanMgr(Instance)->free();
            delete g_pInstMgr;
            g_pInstMgr = NULL;
        }
 }
 return TRUE;
}
BOOL WINAPI eslOpenScanner(const DWORD Instance, const ConnectInfo* pScanner, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslOpenScanner");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
 CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
 DWORD err = ESL_SUCCESS;
 err = scan->openScanner(pScanner);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]Device open failed");
  SetErrorCode(pErrCode, err);
  return FALSE;
 }
    return TRUE;
}
BOOL WINAPI eslCtrlParameter(const DWORD Instance, const eParamOpType OpType, EslParamHdr* pParam, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslCtrlParameter");
    SetErrorCode(pErrCode, ESL_SUCCESS);
    if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
 CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    DWORD err = ESL_SUCCESS;
 err = scan->ctrlParameter(OpType, pParam);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]scan->ctrlParameter failed");
  SetErrorCode(pErrCode, err);
  return FALSE;
 }
 return TRUE;
}
BOOL WINAPI eslExecute(const DWORD Instance, const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslExecute");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
 CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    DWORD err = ESL_SUCCESS;
 err = scan->execute(ExecType, pCbFunc, pPrivate);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]scan->execute failed");
  SetErrorCode(pErrCode, err);
  return FALSE;
 }
 return TRUE;
}
BOOL WINAPI eslCloseScanner(const DWORD Instance, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslCloseScanner");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
    CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    scan->closeScanner();
    return TRUE;
}
BOOL WINAPI eslGetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, INT* select)
{
 SDI_TRACE_LOG("eslGetSettingParameter");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
    CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    return scan->getSettingParameter(SpecifiedParameter, select);
}
BOOL WINAPI eslSetSettingParameter(const DWORD Instance, const eSpecifiedParameter SpecifiedParameter, DWORD* pErrCode, const INT setparam)
{
 SDI_TRACE_LOG("eslSetSettingParameter");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
    CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    return scan->setSettingParameter(SpecifiedParameter, setparam);
}
#ifndef WIN32
BOOL WINAPI eslGetDeviceStatus(const DWORD Instance, DWORD* pStatusCode, DWORD* pErrCode)
{
 SDI_TRACE_LOG("eslGetDeviceStatus");
    SetErrorCode(pErrCode, ESL_SUCCESS);
 if (!g_pInstMgr) {
  SDI_TRACE_LOG("[ERROR]g_pInstMgr is NULL");
  SetErrorCode(pErrCode, ESL_ERR_NOT_INITIALIZED);
  return FALSE;
 }
    CScanMgr* scan = g_pInstMgr->getScanMgr(Instance);
 if (!scan) {
  SDI_TRACE_LOG("[ERROR]scan is NULL");
  SetErrorCode(pErrCode, ESL_ERR_INVALID_PARAM);
  return FALSE;
 }
    *pStatusCode = scan->getEslDeviceStatus();
    return TRUE;
}
#endif
