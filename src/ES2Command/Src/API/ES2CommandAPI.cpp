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
//  ES2CommandAPI.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "Include/ES2Command/ES2CommandAPI.h"
#include "Command/ESScanner.h"
extern "C" ESSCANNER_API ESErrorCode ESCreateScanner( ESCommandType eCommandType, IESScanner** ppScanner )
{
 ES_LOG_TRACE_FUNC();
 if ( ppScanner == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 *ppScanner = NULL;
 CESScanner* pScanner = NULL;
 try {
  pScanner = CESScanner::CreateInstance(eCommandType);
 } catch( const std::bad_alloc& ){
  ES_LOG_MEMORY_ALLOCATE_ERROR();
  return kESErrorMemoryError;
 } catch( const std::invalid_argument& ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorFatalError;
 } catch(...){
  ES_LOG_EXCEPTION_ERROR();
  return kESErrorFatalError;
 }
 ESErrorCode ret = kESErrorFatalError;
 if (pScanner){
  ret = pScanner->Initialize();
  if ( IS_ERR_SUCCESS(ret) ){
   *ppScanner = dynamic_cast< IESScanner* >( pScanner );
  } else {
   pScanner->DestroyInstance();
  }
 }
 return ret;
}
