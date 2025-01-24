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
//  ESManageFileFormatKit.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <ES2FileFormat/FileFormatKit.h>
#include <ES2FileFormat/FKPAPI.h>
class CESManageFileFormatKit
{
 HMODULE m_hModule;
public:
 CESManageFileFormatKit() ;
 virtual ~CESManageFileFormatKit(void);
 virtual bool LoadModule(const TCHAR* pszModulePath) ;
 virtual BOOL _FreeModule() ;
 IFKSource* Call_CreateAndInitFKSource(FKSourceType eSourceType, ES_CMN_FUNCS::BUFFER::IESBuffer& cSource, BOOL bIsFull)
 {
  if (m_pPFNCreateAndInitFKSourceInstance) {
   return m_pPFNCreateAndInitFKSourceInstance(eSourceType, cSource, bIsFull);
  }
  return NULL ;
 }
 IFKDestination* Call_CreateAndInitFKDestination(FKDestinationType eType, ES_CMN_FUNCS::BUFFER::IESBuffer& cSource)
 {
  if (m_pPFNCreateAndInitFKDestinationInstance) {
   return m_pPFNCreateAndInitFKDestinationInstance(eType, cSource) ;
  }
  return NULL ;
 }
 IFKReader* Call_CreateAndInitFKReaderInstance( FKReaderType eReaderType)
 {
  if (m_pPFNCreateAndInitFKReaderInstance) {
   return m_pPFNCreateAndInitFKReaderInstance(eReaderType) ;
  }
  return NULL ;
 }
 IFKWriter* Call_CreateAndInitFKWriterInstance( FKWriterType eWriterType, ES_CHAR_CPTR pszOptionAsJson)
 {
  if (m_pPFNCreateAndInitFKWriterInstance) {
   return m_pPFNCreateAndInitFKWriterInstance(eWriterType, pszOptionAsJson) ;
  }
  return NULL ;
 }
 BOOL Call_DecodeJpegWithResize(const ES_CMN_FUNCS::BUFFER::IESBuffer& cSrcJpegData,const ES_CMN_FUNCS::BUFFER::IESBuffer& cOutResizedRawData,const ST_ES_SIZE_UN32& stRequestSize,const IESResultString& strOutImageInfoAsJson)
 {
  if (m_pPFNDecodeJpegWithResize) {
   return m_pPFNDecodeJpegWithResize(cSrcJpegData, cOutResizedRawData,stRequestSize,strOutImageInfoAsJson) ;
  }
  return FALSE ;
 }
private:
 PFN_INIT_FKSOURCE_INSTANCE m_pPFNCreateAndInitFKSourceInstance ;
 PFN_INIT_FKDESTINATION_INSTANCE m_pPFNCreateAndInitFKDestinationInstance ;
 PFN_INIT_FKREADER_INSTANCE m_pPFNCreateAndInitFKReaderInstance ;
 PFN_INIT_FKWRITER_INSTANCE m_pPFNCreateAndInitFKWriterInstance ;
 PFN_DECODE_JPEG_WITH_RESIZE m_pPFNDecodeJpegWithResize;
};
