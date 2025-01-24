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
//  ESZipfileUtils.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/ESCommonTypedef.h"
#include "CommonUtility/utils/zipfile/zipfile.h"
#include "CommonUtility/utils/PathUtils.h"
#include "CommonUtility/utils/stringutils.h"
#include "CommonUtility/utils/ESJsonUtils.h"
namespace ES_CMN_FUNCS
{
 namespace ZIPFILE
 {
  static std::string exchangeDelimiter(const std::string& strSrc)
  {
   std::stringstream ssTmp(strSrc);
   std::vector<std::string> vTmp;
   std::string strTmp;
   while(std::getline(ssTmp, strTmp, '\\'))
   {
    if(strTmp.size() != 0)
    {
     vTmp.push_back(strTmp);
    }
   }
   std::stringstream ssDst;
   for(auto itr = vTmp.begin(), itr_end = vTmp.end(); itr != itr_end; ++itr)
   {
    if(itr != vTmp.begin())
    {
     ssDst << '/';
    }
    ssDst << *itr;
   }
   return ssDst.str();
  }
  static UInt32 ZipfileToDictionary(const ESString& strFilePath, const ESString& strEntryPath, ESDictionary& dictDst)
  {
   ZipFile zipfile;
   if(!ES_CMN_FUNCS::PATH::ES_IsExistFile(strFilePath))
   {
    return ES_CMN_FUNCS::JSON::ES_JSON_INVALID_ERR;
   }
   int nRet = zipfile.Open(strFilePath.c_str());
   if(nRet)
   {
    return ES_CMN_FUNCS::JSON::ES_JSON_INVALID_ERR;
   }
#ifdef WIN32
   const ESStringA strEntryPathMB = exchangeDelimiter(ES_CMN_FUNCS::STRING::UnicodeToMBString(strEntryPath));
#else
   const ESStringA strEntryPathMB = exchangeDelimiter(strEntryPath);
#endif
   nRet = zipfile.Read(strEntryPathMB.c_str());
   if(nRet)
   {
    return ES_CMN_FUNCS::JSON::ES_JSON_INVALID_ERR;
   }
   const unsigned int nSize = zipfile.GetSize();
   const char* pTmp = zipfile.GetPtr();
   if(nSize > 0 && pTmp)
   {
#ifdef WIN32
    return ES_CMN_FUNCS::JSON::JSONtoDictionary(ES_CMN_FUNCS::STRING::UTF8ToUnincode(pTmp), dictDst);
#else
    return ES_CMN_FUNCS::JSON::JSONtoDictionary(pTmp, dictDst);
#endif
   }
   return ES_CMN_FUNCS::JSON::ES_JSON_INVALID_ERR;
  }
 };
};
