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
//  FKPngEncodeUtil.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FKDestination.h"
#include "png.h"
class CFKPngEncodeUtil
{
public:
 CFKPngEncodeUtil();
 virtual ~CFKPngEncodeUtil();
 BOOL StartEncodingWithPath(const ESString& strPath, const ESImageInfo& pImageInfo, ENUM_FK_ERROR_CODE& eError);
 BOOL WriteScanlinesWithData(const ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError);
 BOOL FinalizeEncodingAndReturnError(ENUM_FK_ERROR_CODE& eError);
private:
 void DestroyPngResources(bool bDeleteFile = false);
 uint32_t m_rowBytes;
 FILE* m_pTarget;
 png_structp m_pPng;
 png_infop m_pPngInfo;
 ESString m_strTargetPath;
};
