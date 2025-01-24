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
//  Utilities.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <math.h>
#ifdef WIN32
#include <rpc.h>
#else
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost::uuids;
#endif
#endif
namespace ES_CMN_FUNCS
{
 inline float roundf(float x)
 {
  return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
 }
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
 inline bool GenerateUUID(ESString& strResult)
 {
#ifdef WIN32
  UUID uuid;
  if(UuidCreate(&uuid) == RPC_S_OK)
  {
   ES_CHAR* pUuid = NULL;
   if(UuidToStringW(&uuid, reinterpret_cast<RPC_WSTR*>(&pUuid)) == RPC_S_OK)
   {
    if(pUuid)
    {
     strResult = ESString(pUuid);
     std::transform(strResult.cbegin(), strResult.cend(), strResult.begin(), toupper);
     RpcStringFree(reinterpret_cast<RPC_WSTR*>(&pUuid));
     return true;
    }
   }
  }
  return false;
#else
  const uuid id = random_generator()();
  strResult = boost::lexical_cast<std::string>(id);
  return true;
#endif
 }
#endif
};
