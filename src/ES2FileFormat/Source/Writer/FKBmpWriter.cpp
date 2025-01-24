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
//  FKBmpWriter.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#ifdef __linux__
#include "Platform.h"
#endif
#include "stdafx.h"
#include "ESImageInfo.h"
#include "FileFormatKitErrors.h"
#include "FKBmpWriter.h"
#include "../BmpUtil/FKBmpUtil.h"
#include "ESAnyCastUtils.h"
#include "DbgLog.h"
CFKBmpWriter::CFKBmpWriter()
{
 m_pCFKBmpEncodeUtil = NULL;
}
CFKBmpWriter::~CFKBmpWriter()
{
 delete m_pCFKBmpEncodeUtil;
 m_pCFKBmpEncodeUtil = NULL;
}
BOOL CFKBmpWriter::Initialize()
{
 m_pCFKBmpEncodeUtil = safeNew CFKBmpEncodeUtil();
 if (m_pCFKBmpEncodeUtil == NULL){
  return FALSE;
 }
 return TRUE;
}
BOOL CFKBmpWriter::InitializeWriterWithDestination(
 CFKDestination* pCFKDestination,
 FKWriterInitializeDestDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 eError = kFKNoError;
 ES_ErrorBailWithAction(m_pCFKBmpEncodeUtil != NULL, BAIL, this, eError = kFKInconsistentError, L"not initialized");
 ES_ErrorBailWithAction((pCFKDestination->GetFKDestinationType() == kFKDestinationTypePath || pCFKDestination->GetFKDestinationType() == kFKDestinationTypeData),
  BAIL, this, eError = kFKUnsupportedDestination, L"unsupported dest");
BAIL:;
 return eError == kFKNoError;
}
BOOL CFKBmpWriter::OpenWriterPageWithImageInfo(
 ESImageInfo* pImageInfo,
 FKWriterPageOpenDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 bool bTopDown = false;
 ESNumber nResolutionFormetadata = ES_IMAGE_INFO::GetESImageOutputResolution(*pImageInfo);
 if (nResolutionFormetadata == 0) {
  nResolutionFormetadata = ES_IMAGE_INFO::GetESImageResolutionX(*pImageInfo);
 }
 if(pOption){
  bool* pbTopDown = SAFE_KEYS_DATA_PTR(*pOption,kFKWriterPageOpenIsBmpTopDown,bool);
  if(pbTopDown){
   bTopDown = *pbTopDown;
  }
 }
 if (m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypePath){
  ESString strPath = (LPCSTR)(((GetCFKDestination()->GetSource())).GetBufferPtr());
  if (!this->m_pCFKBmpEncodeUtil->StartEncodingWithPath(strPath, *pImageInfo, bTopDown,nResolutionFormetadata, eError)){
   eError = kFKUnknownError;
   ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("startWithPath fails"));
  }
 }
 else if (m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypeData || m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypeEmpty){
  if (!this->m_pCFKBmpEncodeUtil->StartEncodingWithData(m_pCFKDestination, *pImageInfo, bTopDown,nResolutionFormetadata, eError)){
   eError = kFKUnknownError;
   ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("startWithPath fails"));
  }
 }
 m_eState = kFKWriterStateProcessing;
BAIL:;
 return eError == kFKNoError;
}
BOOL CFKBmpWriter::CloseWriterPageWithOption(FKWriterPageCloseDict* pOption, ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 eError = kFKNoError;
 return eError == kFKNoError;
}
BOOL CFKBmpWriter::AppendSourceToDestination( CFKSource* pSource, ENUM_FK_ERROR_CODE& eError )
{
 return AppendConstSourceToDestination(pSource,eError);
}
BOOL CFKBmpWriter::AppendConstSourceToDestination(const CFKSource* pSource, ENUM_FK_ERROR_CODE& eError){
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 ES_ErrorBailWithAction((pSource->GetFKSourceType() == kFKSourceTypeData), BAIL, this, errorCode = kFKUnsupportedDestination, ES_STRING("unsupported dest"));
 {
  BOOL bSuccess = m_pCFKBmpEncodeUtil->WriteScanlinesWithData(pSource->GetConstSource(), m_pCFKDestination, errorCode);
  ES_ErrorBail(bSuccess, BAIL, this, ES_STRING("writeScanLines fails"));
 }
BAIL:;
 eError = errorCode;
 return errorCode == kFKNoError;
}
BOOL CFKBmpWriter::IsMultiPageSupport()
{
 return FALSE;
}
BOOL CFKBmpWriter::FinalizeWriterWithOption(FKWriterFinalizeDestDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 m_eState = kFKWriterStateNotOpened;
 if (!m_pCFKBmpEncodeUtil->FinalizeEncodingAndReturnError(m_pCFKDestination, eError)) {
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("finalize fails"));
 }
 return TRUE;
BAIL:;
 return FALSE;
}
