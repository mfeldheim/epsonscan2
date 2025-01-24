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
//  FKReader.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "FileFormatKitErrors.h"
#include "FKReader.h"
#include "../Reader/FKJpegReader.h"
#ifdef WIN32
#include "../Reader/FKBmpReader.h"
#else
#endif
using namespace ES_CMN_FUNCS;
CFKReader::CFKReader()
{
 m_bOpen = FALSE;
 m_nValidImageHeight = 0;
 m_piFkDestination = NULL;
 m_esImageInfo.clear();
}
CFKReader::~CFKReader()
{
 if( m_piFkDestination ){
  m_piFkDestination->Destroy();
  m_piFkDestination = NULL;
 }
 m_esImageInfo.clear();
}
CFKReader* CFKReader::CreateFKReaderWithType(FKReaderType eType){
 CFKReader* pcFKReader = NULL;
 if (eType == kFKReaderTypeJpeg ){
  pcFKReader = new (std::nothrow) CFKJpegReader();
#ifdef WIN32
 }else if (eType == kFKReaderTypeBmp){
  pcFKReader = new (std::nothrow) CFKBmpReader();
#endif
 }else{
  assert(false);
  return NULL;
 }
 return pcFKReader;
}
ESImageInfo& CFKReader::GetImageInfo(void)
{
    return m_esImageInfo;
}
void CFKReader::GetImageInfoAsJson(IESResultString& strImageInfoAsJson){
 ESString strOut;
 ES_IMAGE_INFO::GetImageInfoAsJson(strOut,GetImageInfo());
 strImageInfoAsJson.Set(strOut.c_str());
}
BOOL CFKReader::OpenWithDestination( IFKDestination* pcDestination, ENUM_FK_ERROR_CODE& eError )
{
 return OpenWithDestinationAsJson(pcDestination, NULL, eError);
}
BOOL CFKReader::OpenWithDestinationAsJson( IFKDestination* pcDestination, ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError )
{
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 if ( m_bOpen ){
  errorCode = kFKInconsistentError;
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("Reader is not closed"));
 }
 m_bOpen = TRUE;
 m_nValidImageHeight = 0;
 m_piFkDestination = pcDestination;
 if ( OpenReaderWithOptionAsJson( pszOptionAsJson, eError ) == FALSE ) {
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("OpenReaderWithOptionAsJson fails"));
 }
BAIL:
 eError = errorCode;
 return errorCode == kFKNoError;
}
BOOL CFKReader::AppendSource( IFKSource* source, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
    if (m_bOpen == FALSE) {
        eError = kFKInconsistentError;
        ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("Reader is not opened"));
    }
  {
     BOOL isSuccess = AppendSourceToReader(source, eError);
     if (isSuccess == FALSE) {
   if(eError == kFKNoError){
    eError = kFKUnknownError;
   }
         ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("readSourcelinesWithData fails"));
     }
  }
BAIL:
    return eError == kFKNoError;
}
BOOL CFKReader::CloseAndReturnError( ENUM_FK_ERROR_CODE& eError )
{
 return CloseWithOptionAsJson( NULL, eError );
}
BOOL CFKReader::CloseWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError )
{
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 if ( !m_bOpen ){
        errorCode = kFKInconsistentError;
        ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("Reader is not opened"));
 }
 if ( CloseReaderWithOptionAsJson( pszOptionAsJson, eError ) == FALSE ){
        ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("CloseReaderWithOption fails"));
 }
 m_bOpen = FALSE;
BAIL:
    errorCode = eError;
    return errorCode == kFKNoError;
}
