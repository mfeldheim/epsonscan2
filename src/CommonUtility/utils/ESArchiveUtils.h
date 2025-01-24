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
//  ESArchiveUtils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/ESCommonTypedef.h"
#ifdef WIN32
#include "CommonUtility/utils/ESZipfileUtils.h"
#endif
#include "CommonUtility/utils/ESJsonUtils.h"
#ifdef WIN32
#if 1
#define _ZIP_DB 
#endif
#endif
namespace ES_CMN_FUNCS
{
 namespace ARCHIVE
 {
#ifdef _ZIP_DB
  static UInt32 ArchiveToDictionary(const ESString& strDBPath, const ESString& strEntryPath, ESDictionary& dictDst)
  {
   const UInt32 nRet = ES_CMN_FUNCS::ZIPFILE::ZipfileToDictionary(strDBPath, strEntryPath, dictDst);
   assert(nRet == 0);
   return nRet;
  }
#else
  static UInt32 ArchiveToDictionary(const ESString& strDBPath, const ESString& strEntryPath, ESDictionary& dictDst)
  {
   return ES_CMN_FUNCS::JSON::JSONFiletoDictionary(strEntryPath, dictDst);
  }
#endif
 };
};
