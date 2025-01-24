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
//  InstanceMgr.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "InstanceMgr.h"
CInstanceMgr::CInstanceMgr(void) :
m_pScanMgr(NULL)
{
}
CInstanceMgr::~CInstanceMgr(void)
{
 destroyScanMgr(1);
}
DWORD CInstanceMgr::createScanMgr(void)
{
 if (m_pScanMgr) {
  return 1;
 }
 m_pScanMgr = new CScanMgr();
 if (m_pScanMgr) {
  return 1;
 }
 return 0;
}
CScanMgr* CInstanceMgr::getScanMgr(DWORD Instance)
{
 return m_pScanMgr;
}
BOOL CInstanceMgr::destroyScanMgr(DWORD Instance)
{
 if (Instance != 1) {
  return FALSE;
 }
 if (m_pScanMgr) {
  delete m_pScanMgr;
  m_pScanMgr = NULL;
 }
 return TRUE;
}
