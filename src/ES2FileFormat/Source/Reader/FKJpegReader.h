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
//  FKJpegReader.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FKReader.h"
#include "../Base/FKConcreteReaderProtocol.h"
class CFKJpegDecodeUtil;
class CFKJpegReader : public CFKReader,IFKConcreteReaderProtocol
{
protected:
 CFKJpegDecodeUtil* m_pCFKJpegDecodeUtil;
public:
 CFKJpegReader();
 ~CFKJpegReader();
 virtual BOOL GetImageInfo(ESImageInfo& outImageInfo);
 virtual BOOL OpenReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError) override;
 virtual BOOL AppendSourceToReader( IFKSource* pcSource, ENUM_FK_ERROR_CODE& eError ) override;
 virtual BOOL CloseReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError ) override;
};
