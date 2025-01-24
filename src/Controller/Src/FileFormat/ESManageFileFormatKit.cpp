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
//  ESManageFileFormatKit.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESManageFileFormatKit.h"
CESManageFileFormatKit::CESManageFileFormatKit()
{
 m_hModule = NULL;
 m_pPFNCreateAndInitFKSourceInstance = 0 ;
 m_pPFNCreateAndInitFKDestinationInstance = 0 ;
 m_pPFNCreateAndInitFKReaderInstance = 0 ;
 m_pPFNCreateAndInitFKWriterInstance = 0 ;
 m_pPFNDecodeJpegWithResize = 0;
}
CESManageFileFormatKit::~CESManageFileFormatKit(void)
{
 _FreeModule();
 m_pPFNCreateAndInitFKSourceInstance = 0 ;
 m_pPFNCreateAndInitFKDestinationInstance = 0 ;
 m_pPFNCreateAndInitFKReaderInstance = 0 ;
 m_pPFNCreateAndInitFKWriterInstance = 0 ;
 m_pPFNDecodeJpegWithResize = 0;
}
bool CESManageFileFormatKit::LoadModule(const TCHAR *pszModulePath)
{
 m_hModule = LoadLibraryEx(pszModulePath, NULL , LOAD_WITH_ALTERED_SEARCH_PATH) ;
 if (m_hModule) {
#ifdef WIN32
  m_pPFNCreateAndInitFKSourceInstance = (PFN_INIT_FKSOURCE_INSTANCE)::GetProcAddress(m_hModule,"CreateAndInitFKSourceInstance") ;
  m_pPFNCreateAndInitFKDestinationInstance = (PFN_INIT_FKDESTINATION_INSTANCE)::GetProcAddress(m_hModule,"CreateAndInitFKDestinationInstance") ;
  m_pPFNCreateAndInitFKReaderInstance = (PFN_INIT_FKREADER_INSTANCE)::GetProcAddress(m_hModule,"CreateAndInitFKReaderInstance") ;
  m_pPFNCreateAndInitFKWriterInstance = (PFN_INIT_FKWRITER_INSTANCE)::GetProcAddress(m_hModule,"CreateAndInitFKWriterInstance") ;
  m_pPFNDecodeJpegWithResize = (PFN_DECODE_JPEG_WITH_RESIZE)::GetProcAddress(m_hModule,"DecodeJpegWithResize") ;
#else
  m_pPFNCreateAndInitFKSourceInstance = (PFN_INIT_FKSOURCE_INSTANCE)dlsym(m_hModule,"CreateAndInitFKSourceInstance") ;
  m_pPFNCreateAndInitFKDestinationInstance = (PFN_INIT_FKDESTINATION_INSTANCE)dlsym(m_hModule,"CreateAndInitFKDestinationInstance") ;
  m_pPFNCreateAndInitFKReaderInstance = (PFN_INIT_FKREADER_INSTANCE)dlsym(m_hModule,"CreateAndInitFKReaderInstance") ;
  m_pPFNCreateAndInitFKWriterInstance = (PFN_INIT_FKWRITER_INSTANCE)dlsym(m_hModule,"CreateAndInitFKWriterInstance") ;
  m_pPFNDecodeJpegWithResize = (PFN_DECODE_JPEG_WITH_RESIZE)dlsym(m_hModule,"DecodeJpegWithResize") ;
#endif
  if (!m_pPFNCreateAndInitFKSourceInstance ||
   !m_pPFNCreateAndInitFKDestinationInstance ||
   !m_pPFNCreateAndInitFKReaderInstance ||
   !m_pPFNCreateAndInitFKWriterInstance ||
   !m_pPFNDecodeJpegWithResize) {
   return false ;
  }
 } else {
#ifdef WIN32
  ES_Error_Log(this,ES_STRING("Can not load library [%s] [%x]"),pszModulePath,GetLastError());
#endif
  return false ;
 }
 return true ;
}
BOOL CESManageFileFormatKit::_FreeModule()
{
 if(m_hModule){
  FreeLibrary(m_hModule) ;
  m_hModule = NULL;
 }
 return true;
}
