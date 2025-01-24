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
//  FKPAPI.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifdef WIN32
#ifdef FILEFORMATKIT_EXPORTS
#define FILEFORMATKIT_API __declspec(dllexport)
#else
#define FILEFORMATKIT_API __declspec(dllimport)
#endif
#else
#define FILEFORMATKIT_API 
#endif
#include "../Include/ES2FileFormat/FileFormatKit.h"
#include "../CommonUtility/utils/ESBuffer.h"
typedef IFKSource* (*PFN_INIT_FKSOURCE_INSTANCE )(FKSourceType eSourceType, ES_CMN_FUNCS::BUFFER::IESBuffer& pcSource, BOOL bIsFull);
typedef IFKDestination* (*PFN_INIT_FKDESTINATION_INSTANCE)(FKDestinationType eType, ES_CMN_FUNCS::BUFFER::IESBuffer& pcSource);
typedef IFKReader* (*PFN_INIT_FKREADER_INSTANCE )(FKReaderType eReaderType);
typedef IFKWriter* (*PFN_INIT_FKWRITER_INSTANCE )(FKWriterType eWriterType, ES_CHAR_CPTR pszOptionAsJson);
typedef BOOL (*PFN_DECODE_JPEG_WITH_RESIZE )(const ES_CMN_FUNCS::BUFFER::IESBuffer& cSrcJpegData, const ES_CMN_FUNCS::BUFFER::IESBuffer& cOutResizedRawData, const ST_ES_SIZE_UN32& stRequestSize, const IESResultString& strOutImageInfoAsJson);
#ifdef WIN32
#define FILE_FORMAT_KIT_MODULE_NAME ES_STRING("ES2FileFormat.dll")
#else
#define FILE_FORMAT_KIT_MODULE_NAME ES_STRING("libes2fileformat.so")
#endif
extern "C" {
 FILEFORMATKIT_API IFKSource* CreateAndInitFKSourceInstance(FKSourceType eSourceType, ES_CMN_FUNCS::BUFFER::IESBuffer& pcSource, BOOL bIsFull);
 FILEFORMATKIT_API IFKDestination* CreateAndInitFKDestinationInstance(FKDestinationType eType, ES_CMN_FUNCS::BUFFER::IESBuffer& pcSource);
 FILEFORMATKIT_API IFKReader* CreateAndInitFKReaderInstance(FKReaderType eReaderType);
 FILEFORMATKIT_API IFKWriter* CreateAndInitFKWriterInstance(FKWriterType eWriterType, ES_CHAR_CPTR pszOptionAsJson);
 FILEFORMATKIT_API BOOL DecodeJpegWithResize(const ES_CMN_FUNCS::BUFFER::IESBuffer& cSrcJpegData,ES_CMN_FUNCS::BUFFER::IESBuffer& cOutResizedRawData,ST_ES_SIZE_UN32& stRequestSize,IESResultString& strOutImageInfoAsJson);
}
