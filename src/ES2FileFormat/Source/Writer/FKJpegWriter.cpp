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
//  FKJpegWriter.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "FKJpegWriter.h"
#include "../JpegUtil/FKJpegEncodeUtil.h"
#include "FKWriterKeys.h"
static const ESNumber kDefaultJpegQuality = 84;
static const BOOL kProgressiveModeDefault = FALSE;
CFKJpegWriter::CFKJpegWriter()
{
 m_pCFKJpegEncodeUtil = NULL;
}
CFKJpegWriter::~CFKJpegWriter()
{
 if(m_pCFKJpegEncodeUtil) {
  delete m_pCFKJpegEncodeUtil;
  m_pCFKJpegEncodeUtil = NULL;
 }
}
BOOL CFKJpegWriter::Initialize()
{
 m_pCFKJpegEncodeUtil = new (std::nothrow) CFKJpegEncodeUtil();
 if(!m_pCFKJpegEncodeUtil){
  return FALSE;
 }
 return TRUE;
}
BOOL CFKJpegWriter::InitializeWriterWithDestination( CFKDestination* pCFKDestination,
           FKWriterInitializeDestDict* pOption,
           ENUM_FK_ERROR_CODE& eError)
{
 return TRUE;
}
BOOL CFKJpegWriter::OpenWriterPageWithImageInfo( ESImageInfo* pImageInfo,
          FKWriterPageOpenDict* pOption,
          ENUM_FK_ERROR_CODE& eError)
{
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 ES_ErrorBailWithAction( (pImageInfo != NULL ) , BAIL, this, errorCode = kFKParameterError, ES_STRING("imageInfo is NULL"));
 ES_ErrorBailWithAction( (m_pCFKJpegEncodeUtil != NULL ) , BAIL, this, errorCode = kFKParameterError, ES_STRING("m_pCFKJpegEncodeUtil is NULL"));
 {
  BOOL bSuccess = m_pCFKJpegEncodeUtil->StartEncodingWithDest( (CFKDestination*)m_pCFKDestination,
                 pImageInfo,
                 SAFE_ANY_VALUE_FROM_DICT(*pOption,kFKWriterPageOpenOptionJpegQualityKey ,ESNumber,85),
                 SAFE_ANY_VALUE_FROM_DICT(*pOption,kFKWriterPageOpenOptionJpegProgressiveModeKey ,bool,false),
                 SAFE_ANY_VALUE_FROM_DICT(*pOption,kFKWriterPageOpenOptionJpegICCProfilePathKey ,ESString,ES_STRING("")),
                 errorCode
                 );
    ES_ErrorBailWithAction(bSuccess, BAIL, this, errorCode = kFKFileCreateError, ES_STRING("startEncondingFails"));
 }
BAIL:;
    eError = errorCode;
    return errorCode == kFKNoError;
}
BOOL CFKJpegWriter::CloseWriterPageWithOption( FKWriterPageCloseDict* pOption,
        ENUM_FK_ERROR_CODE& eError )
{
 if(!m_pCFKJpegEncodeUtil) {
  return FALSE;
 }
 return m_pCFKJpegEncodeUtil->FinalizeEncodingAndReturnError(eError);
}
BOOL CFKJpegWriter::AppendSourceToDestination( CFKSource* pSource, ENUM_FK_ERROR_CODE& eError )
{
 return AppendConstSourceToDestination(pSource,eError);
}
BOOL CFKJpegWriter::AppendConstSourceToDestination(const CFKSource* pSource, ENUM_FK_ERROR_CODE& eError)
{
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 ES_ErrorBailWithAction( (pSource->GetFKSourceType() == kFKSourceTypeData), BAIL, this, errorCode = kFKUnsupportedDestination, ES_STRING("unsupported dest"));
 {
  BOOL bSuccess = m_pCFKJpegEncodeUtil->WriteScanlinesWithData(pSource->GetConstSource(), eError);
  ES_ErrorBailWithAction(bSuccess, BAIL, this, errorCode = kFKParameterError, ES_STRING("writeScanLines fails"));
 }
BAIL:;
    eError = errorCode;
 return errorCode == kFKNoError;
}
BOOL CFKJpegWriter::IsMultiPageSupport()
{
 return FALSE;
}
BOOL CFKJpegWriter::FinalizeWriterWithOption( FKWriterFinalizeDestDict* pOption,
         ENUM_FK_ERROR_CODE& eError )
{
 return TRUE;
}
