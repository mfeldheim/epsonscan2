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
//  FKJpegEncodeUtil.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#define HAVE_BOOLEAN 
typedef int boolean;
#include "jpeglib.h"
#include "FileFormatKitErrors.h"
#include "jpegUserDefines.h"
#include "FKDestination.h"
class CFKJpegEncodeUtil
{
private:
 struct jpeg_compress_struct m_stCInfo;
 struct my_error_mgr m_stJerr;
 FILE* m_pCFile;
 BOOL m_bStarted;
public:
 CFKJpegEncodeUtil();
 ~CFKJpegEncodeUtil();
 BOOL StartEncodingWithDest( CFKDestination* pDestination,
        ESImageInfo* pImageInfo,
        INT32 nQuality,
        BOOL bProgressiveMode,
        ESString strIccProfilePath,
        ENUM_FK_ERROR_CODE& eError );
 BOOL WriteScanlinesWithData(const ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError );
 BOOL FinalizeEncodingAndReturnError( ENUM_FK_ERROR_CODE& eError );
 BOOL OpenOutFileWithPath( ESString* outFilePath );
 void CloseOutFile();
 ENUM_FK_ERROR_CODE UpdateJpegStructWithDest( CFKDestination* pDestination,
           ESImageInfo* pImageInfo,
           INT32 nQuality,
           BOOL bProgressiveMode);
};
