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
//  FKTiffJpegEncodeUtil.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "FKTiffJpegEncodeUtil.h"
#include "FileFormatKit.h"
#include "FileFormatKitErrors.h"
#include "ESImageInfo.h"
#include "ESFile.h"
FKTiffJpegEncodeUtil::FKTiffJpegEncodeUtil()
{
}
FKTiffJpegEncodeUtil::~FKTiffJpegEncodeUtil()
{
}
uint32_t FKTiffJpegEncodeUtil::GetRowsPerStrip(uint32_t compression)
{
 uint32_t height = 0;
 if (TIFFGetField(m_pOutFile, TIFFTAG_IMAGELENGTH, &height) != 1) {
 }
 return height;
}
uint32_t FKTiffJpegEncodeUtil::GetRgbColorSpaceForCompression(uint32_t compression)
{
 UNREFERENCED_PARAMETER(compression);
 return PHOTOMETRIC_YCBCR;
}
BOOL FKTiffJpegEncodeUtil::StartWriting()
{
 m_pageBuffer = std::vector<uint8_t>();
 return TRUE;
}
BOOL FKTiffJpegEncodeUtil::WriteScanlinesWithData(const ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
 try{
  uint32_t currentLen = m_pageBuffer.size();
  m_pageBuffer.resize(currentLen + cData.GetLength());
  ES_ErrorBailWithAction((m_pageBuffer.size() >= (cData.GetLength() + currentLen)), BAIL, this, eError = kFKTiffWriteScanLineError, L"WriteScanlinesWithData fails");
  memcpy((&m_pageBuffer[0] + currentLen), cData.GetConstBufferPtr(), cData.GetLength());
 }
 catch (const std::bad_alloc& e){
  UNREFERENCED_PARAMETER(e);
 }
BAIL:
 return eError == kFKNoError;
}
BOOL FKTiffJpegEncodeUtil::FinalizeWriting()
{
 ENUM_FK_ERROR_CODE eError = kFKNoError;
 if (TIFFWriteRawStrip(m_pOutFile, 0, &m_pageBuffer[0], m_pageBuffer.size()) == 0) {
  eError = kFKTiffWriteScanLineError;
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, ES_STRING("TIFFWriteRawStrip fails"));
 }
BAIL:;
 m_pageBuffer = std::vector<uint8_t>();
 return eError == kFKNoError;
}
