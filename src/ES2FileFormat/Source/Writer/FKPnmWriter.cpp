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
//  FKPnmWriter.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESImageInfo.h"
#include "FileFormatKitErrors.h"
#include "FKPnmWriter.h"
#include "../PnmUtil/FKPnmUtil.h"
#include "ESAnyCastUtils.h"
#include "DbgLog.h"
CFKPnmWriter::CFKPnmWriter()
{
 m_pCFKPnmEncodeUtil = NULL;
}
CFKPnmWriter::~CFKPnmWriter()
{
 delete m_pCFKPnmEncodeUtil;
 m_pCFKPnmEncodeUtil = NULL;
}
BOOL CFKPnmWriter::Initialize()
{
 m_pCFKPnmEncodeUtil = safeNew CFKPnmEncodeUtil();
 if (m_pCFKPnmEncodeUtil == NULL){
  return FALSE;
 }
 return TRUE;
}
BOOL CFKPnmWriter::InitializeWriterWithDestination(
 CFKDestination* pCFKDestination,
 FKWriterInitializeDestDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 eError = kFKNoError;
 ES_ErrorBailWithAction(m_pCFKPnmEncodeUtil != NULL, BAIL, this, eError = kFKInconsistentError, ES_STRING("not initialized"));
 ES_ErrorBailWithAction((pCFKDestination->GetFKDestinationType() == kFKDestinationTypePath || pCFKDestination->GetFKDestinationType() == kFKDestinationTypeData),
  BAIL, this, eError = kFKUnsupportedDestination, ES_STRING("unsupported dest"));
BAIL:;
 return eError == kFKNoError;
}
BOOL CFKPnmWriter::OpenWriterPageWithImageInfo(
 ESImageInfo* pImageInfo,
 FKWriterPageOpenDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 ESNumber nResolutionFormetadata = ES_IMAGE_INFO::GetESImageOutputResolution(*pImageInfo);
 if (nResolutionFormetadata == 0) {
  nResolutionFormetadata = ES_IMAGE_INFO::GetESImageResolutionX(*pImageInfo);
 }
 if (m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypePath){
  ESString strPath = (LPTSTR)(((GetCFKDestination()->GetSource())).GetBufferPtr());
  if (!this->m_pCFKPnmEncodeUtil->StartEncodingWithPath(strPath, *pImageInfo,nResolutionFormetadata, eError)){
   eError = kFKUnknownError;
   ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("startWithPath fails"));
  }
 }
 else if (m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypeData || m_pCFKDestination->GetFKDestinationType() == kFKDestinationTypeEmpty){
  if (!this->m_pCFKPnmEncodeUtil->StartEncodingWithData(m_pCFKDestination, *pImageInfo,nResolutionFormetadata, eError)){
   eError = kFKUnknownError;
   ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("startWithPath fails"));
  }
 }
 m_eState = kFKWriterStateProcessing;
BAIL:;
 return eError == kFKNoError;
}
BOOL CFKPnmWriter::CloseWriterPageWithOption(FKWriterPageCloseDict* pOption, ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 eError = kFKNoError;
 return eError == kFKNoError;
}
BOOL CFKPnmWriter::AppendSourceToDestination( CFKSource* pSource, ENUM_FK_ERROR_CODE& eError )
{
 return AppendConstSourceToDestination(pSource,eError);
}
BOOL CFKPnmWriter::AppendConstSourceToDestination(const CFKSource* pSource, ENUM_FK_ERROR_CODE& eError){
 ENUM_FK_ERROR_CODE errorCode = kFKNoError;
 ES_ErrorBailWithAction((pSource->GetFKSourceType() == kFKSourceTypeData), BAIL, this, errorCode = kFKUnsupportedDestination, ES_STRING("unsupported dest"));
 {
  BOOL bSuccess = m_pCFKPnmEncodeUtil->WriteScanlinesWithData(pSource->GetConstSource(), m_pCFKDestination, errorCode);
  ES_ErrorBail(bSuccess, BAIL, this, ES_STRING("writeScanLines fails"));
 }
BAIL:;
 eError = errorCode;
 return errorCode == kFKNoError;
}
BOOL CFKPnmWriter::IsMultiPageSupport()
{
 return FALSE;
}
BOOL CFKPnmWriter::FinalizeWriterWithOption(FKWriterFinalizeDestDict* pOption,
 ENUM_FK_ERROR_CODE& eError)
{
 UNREFERENCED_PARAMETER(pOption);
 m_eState = kFKWriterStateNotOpened;
 if (!m_pCFKPnmEncodeUtil->FinalizeEncodingAndReturnError(m_pCFKDestination, eError)) {
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("finalize fails"));
 }
 return TRUE;
BAIL:;
 return FALSE;
}
