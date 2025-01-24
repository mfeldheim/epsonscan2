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
//  ESUtils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/utils/Utilities.h"
bool IsThreadAlive( HANDLE hThread );
bool IsPassedInterval( DWORD dwLastTickCount, DWORD dwInterval_ms, DWORD* pdwPassedTime_ms );
int ESCIGetBytesPerRow(int nImageWidth, int nBitsPerPixel);
void ESCIRoundColorCorrectionMatrix(int mult, double org_cct[], int rnd_cct[]);
ESIndexSet AnyArrayToIndexSet( ESAnyArray& anyArray );
ESStringA& LTrimSpace(ESStringA& s);
ESStringA& RTrimSpace(ESStringA& s);
ESStringA& TrimSpace(ESStringA& s);
#ifdef WIN32
ESErrorCode LoadJsonResouce( ESDictionary& dicOutput, const ESString& strResouceType, const ESString& strResouceName );
ESErrorCode RegQueryDWORDValue(HKEY hKeyRoot, LPCWSTR lpszSubKey, WCHAR *pszEntry, DWORD *pdwData);
#endif
