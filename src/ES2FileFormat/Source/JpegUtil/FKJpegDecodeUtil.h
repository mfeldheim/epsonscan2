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
//  FKJpegDecodeUtil.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#define HAVE_BOOLEAN 
typedef int boolean;
#include "jpeglib.h"
#include "FileFormatKitErrors.h"
#include "jpegUserDefines.h"
class CFKJpegDecodeUtil
{
private:
 struct jpeg_decompress_struct m_stCinfo;
 struct my_error_mgr m_stJerr;
 BOOL m_bHeaderRead;
    BOOL m_bStart;
public:
 CFKJpegDecodeUtil();
 ~CFKJpegDecodeUtil();
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_cJpegData;
 jpeg_decompress_struct* GetJpegDecompressInfo() {
  return &m_stCinfo;
 }
 BOOL IsStart() {
  return m_bStart;
 }
 BOOL StartDecodingAndReturnError( ENUM_FK_ERROR_CODE& eError );
 void AppendData( ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cData );
 BOOL DecodedDataAndReturnError(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cDestData, ENUM_FK_ERROR_CODE& eError ,ESNumber nValidHeight,BOOL bReadOnlyValidData);
 BOOL FinalizeDecodingAndReturnError( ENUM_FK_ERROR_CODE& eError );
 BOOL DecodeJpegDataWithResize(const ES_CMN_FUNCS::BUFFER::IESBuffer& cSrcJpegData,ES_CMN_FUNCS::BUFFER::IESBuffer& cDestResizedRawData, ST_ES_SIZE_UN32& stRequestSize,ESString& outImageInfoAsJsonn);
private:
 ENUM_FK_ERROR_CODE jpegStartDecompress();
 BOOL scanJpegLines(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cDestData,ESNumber nValidHeight,BOOL bReadOnlyValidData,ENUM_FK_ERROR_CODE& eError);
};
