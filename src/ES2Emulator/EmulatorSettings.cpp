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
//  EmulatorSettings.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "EmulatorSettings.h"
EmulatorSettings::EmulatorSettings(void)
{
}
EmulatorSettings::~EmulatorSettings(void)
{
}
void EmulatorSettings::SetEmulatorControllerDir(ESString strCtrlerDir)
{
 m_strCtrlerDir = strCtrlerDir;
}
ESString EmulatorSettings::GetEmulatorControllerDir()
{
 return m_strCtrlerDir;
}
#ifdef WIN32
ESString EmulatorSettings::GetEmulatorSettingIniPath()
{
 if (!ES_CMN_FUNCS::PATH::ES_IsExistFile(m_strSettingIniPath))
 {
  ES_CMN_FUNCS::PATH::ES_CombinePath(m_strSettingIniPath, GetEmulatorControllerDir(), ES_STRING("DummyInfo"));
  ES_CMN_FUNCS::PATH::ES_CombinePath(m_strSettingIniPath, m_strSettingIniPath, ES_STRING("EmulatorSetting.ini"));
 }
 return m_strSettingIniPath;
}
BOOL EmulatorSettings::IsEnabledCreateDummyInfoMode()
{
 ESString strINIfilePath = GetEmulatorSettingIniPath();
 UINT nEnabledDummyInfo = GetPrivateProfileInt(ES_STRING("function"), ES_STRING("EnableCreateDummyInfo"), 0, strINIfilePath.c_str());
 return nEnabledDummyInfo != 0;
}
BOOL EmulatorSettings::IsScanSpeedUp()
{
 ESString strINIfilePath = GetEmulatorSettingIniPath();
 UINT nScanSpeedUp = GetPrivateProfileIntW(ES_STRING("scan"), ES_STRING("ScanSpeedUp "), 0, strINIfilePath.c_str());
 return nScanSpeedUp != 0;
}
BOOL EmulatorSettings::IsIndicatedPageNumber()
{
 ESString strINIfilePath = GetEmulatorSettingIniPath();
 UINT nIndicate = GetPrivateProfileIntW(ES_STRING("scan"), ES_STRING("IndicatedPageNumber "), 1, strINIfilePath.c_str());
 return nIndicate != 0;
}
BOOL EmulatorSettings::IsShowErrorCode()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nErrCode = GetPrivateProfileIntW(ES_STRING("function"), ES_STRING("errcode"), 0, strPath.c_str());
 if (nErrCode != 0)
 {
  return TRUE;
 }
 return FALSE;
}
BOOL EmulatorSettings::IsShowNickNameImage()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nNickName = GetPrivateProfileIntW(ES_STRING("function"), ES_STRING("nickname"), 0, strPath.c_str());
 if (nNickName != 0)
 {
  return TRUE;
 }
 return FALSE;
}
BOOL EmulatorSettings::IsInitialLoadPaper()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nLoad = GetPrivateProfileIntW(ES_STRING("paperLoading"), ES_STRING("LoadingPaper"), 0, strPath.c_str());
 return nLoad != 0;
}
INT EmulatorSettings::GetInitialLoadPaperNum()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nLoadNum = GetPrivateProfileIntW(ES_STRING("paperLoading"), ES_STRING("LoadingPaperNum"), 0, strPath.c_str());
 return nLoadNum;
}
BOOL EmulatorSettings::IsEnableDecresingPaper()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nDisableDecresing = GetPrivateProfileIntW(ES_STRING("paperLoading"), ES_STRING("DisableDecreseLoadingPaper "), 0, strPath.c_str());
 return nDisableDecresing == 0;
}
BOOL EmulatorSettings::IsEnablePagePerMinute()
{
 ESString strPath = GetEmulatorSettingIniPath();
 UINT nPPM = GetPrivateProfileIntW(ES_STRING("function"), ES_STRING("PagePerMinute"), 0, strPath.c_str());
 return nPPM != 0;
}
#endif
