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
//  stringutils.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "stringutils.h"
#ifdef WIN32
#include <windows.h>
#endif
namespace ES_CMN_FUNCS
{
 namespace STRING
 {
  inline ESStringW M2W(const ESStringA& strSrcA, const UINT CodePage)
  {
#ifdef WIN32
   if ( strSrcA.empty() ){
    return ES_STRING("");
   }
   try {
    ESStringW strDstW = ES_STRING("");
    int nConvRet = ::MultiByteToWideChar(CodePage, 0, strSrcA.c_str(), -1, NULL, 0);
    if (nConvRet <= 0) {
     return ES_STRING("");
    }
    int nDstSize = nConvRet + 1;
    char_t* lpDst = new char_t[nDstSize];
    if ( lpDst != NULL ){
     nConvRet = ::MultiByteToWideChar(CodePage, 0, strSrcA.c_str(), -1, lpDst, nDstSize);
     if (nConvRet > 0) {
      strDstW = lpDst;
     }
     delete[] lpDst;
    }
    return strDstW;
   } catch( const std::bad_alloc& ){
    return ES_STRING("");
   }
#else
   assert(FALSE);
#endif
  }
  inline ESStringA W2M(const ESStringW& strSrcW, const UINT CodePage)
  {
#ifdef WIN32
   if ( strSrcW.empty() ){
    return "";
   }
   try {
    ESStringA strDstA = "";
    int nConvRet = ::WideCharToMultiByte(CodePage, 0, strSrcW.c_str(), -1, (LPSTR)NULL, 0, (LPCSTR)NULL, (LPBOOL)NULL);
    if (nConvRet <= 0) {
     return "";
    }
    int nDstSize = nConvRet + 1;
    char* lpDst = new char[nDstSize];
    if ( lpDst != NULL){
     nConvRet = ::WideCharToMultiByte(CodePage, 0, strSrcW.c_str(), -1, lpDst, nDstSize, (LPCSTR)NULL, (LPBOOL)NULL);
     if (nConvRet > 0) {
      strDstA = lpDst;
     }
     delete[] lpDst;
    }
    return strDstA;
   } catch( const std::bad_alloc& ){
    return "";
   }
#else
   assert(FALSE);
#endif
  }
  ESStringW MBStringToUnicode(const ESStringA& strSrcA)
  {
#ifdef WIN32
   return M2W(strSrcA, CP_ACP);
#else
   assert(FALSE);
#endif
  }
  ESStringA UnicodeToMBString(const ESStringW& strSrcW)
  {
#ifdef WIN32
   return W2M(strSrcW, CP_ACP);
#else
   assert(FALSE);
#endif
  }
  ESStringA UnicodeToUTF8(const ESStringW& strSrcW)
  {
#ifdef WIN32
   return W2M(strSrcW, CP_UTF8);
#else
   assert(FALSE);
#endif
  }
  ESStringW UTF8ToUnincode(const ESStringA& strSrcA)
  {
#ifdef WIN32
   return M2W(strSrcA, CP_UTF8);
#else
   assert(FALSE);
#endif
  }
  ESStringW ReplaceStr( ESStringW StringIn, ESStringW StringSrc, ESStringW StringNew )
  {
#ifdef WIN32
   ESString::size_type Pos( StringIn.find( StringSrc ) );
   while( Pos != ESString::npos )
   {
    StringIn.replace( Pos, StringSrc.length(), StringNew );
    Pos = StringIn.find( StringSrc, Pos + StringNew.length() );
   }
   return StringIn;
#else
   assert(FALSE);
#endif
  }
 }
}
