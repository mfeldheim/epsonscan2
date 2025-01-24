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
//  PathUtils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCommonTypedef.h"
#ifndef WIN32
DWORD
GetTempPath(
    DWORD nBufferLength,
    ESString& lpBuffer
    );
#endif
#ifndef __in
#define __in 
#endif
#ifndef __out
#define __out 
#endif
#ifndef __inout
#define __inout 
BOOL GetTempFileName(
    ESString lpPathName,
    ESString lpPrefixString,
    LPTSTR lpTempFileName
    );
BOOL PathIsDirectory(LPCSTR pszPath);
BOOL PathFileExists(LPCSTR pszPath);
BOOL PathAppend(LPSTR pszPath, LPCSTR pszMore);
#endif
namespace ES_CMN_FUNCS
{
 namespace PATH
 {
  BOOL ES_GetModuleFileName( __in HMODULE hModule, __out ESString& strDst );
  BOOL ES_GetModuleFolder( __in HMODULE hModule, __out ESString& strDst );
  BOOL ES_GetSystemTempDir( __out ESString& strDst );
  BOOL ES_GetTempFile( __out ESString& strCreateTempFilePath, __in const ESString& strPrefix );
  BOOL ES_GetTempFile( __out ESString& strCreateTempFilePath, __in const ESString& strTargetFolder, __in const ESString& strPrefix );
  BOOL ES_IsExistFolder( __in const ESString& strPath );
  BOOL ES_IsExistFile( __in const ESString& strPath, __in BOOL bIsFolderInclude = FALSE );
  BOOL ES_CombinePath( __out ESString& strDst, __in const ESString& strBasePath, __in const ESString& strAddPath );
  BOOL ES_AddBackYen( __inout ESString& strPath );
  BOOL ES_RemoveBackYen( __inout ESString& strPath );
  BOOL ES_GetDrive( __out ESString& strDst, __in const ESString& strSrcPath );
  BOOL ES_GetFolderPath( __out ESString& strDst, __in const ESString& strSrcPath );
  BOOL ES_GetFileName( __out ESString& strDst, __in const ESString& strSrcPath, __in BOOL bExt );
  BOOL ES_GetExtension( __out ESString& strDst, __in const ESString& strSrcPath );
  BOOL ES_RenameExt( __out ESString& strDst, __in const ESString& strSrcPath, __in const ESString& strExt);
  BOOL ES_ConvertFullpath( __out ESString& strDst, __in const ESString& strSrcPath);
  BOOL ES_IsRelative( __in const ESString& strPath );
  BOOL ES_NormalizeFilePath( __out ESString& strDst, __in const ESString& strCurrentPath, __in const ESString& strSrcPath );
  BOOL ES_RelativePathTo( __out ESString& strDst, __in const ESString& strFrom, __in DWORD dwAttrFrom, __in const ESString& strTo, __in DWORD dwAttrTo, __in BOOL bRemoveFirstDot = FALSE );
  BOOL ES_MakeFolder( __in const ESString& strPath );
  BOOL ES_DeleteFolder( __in const ESString& strPath, __in BOOL bRemoveReadOnly = FALSE );
  void ES_RemoveReadOnlyAttribute( __in const ESString& strPath );
  BOOL ES_IsWritableFolder( __in const ESString& strFolderPath );
  BOOL ES_IsWritableDrive( __in const ESString& strDrivePath );
  ESStringArray EnumFilesInDir(ESString strWildcard, ESString strDir);
  std::string ES_GetWorkTempPath();
  #ifndef WIN32
  DWORD ES_GetFileSize( __in const ESString& strPath );
  BOOL ES_IsDirectory(__in const ESString& strPath);
  BOOL ES_IsRegularFile(__in const ESString&);
  #endif
 };
};
