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
//  FKTiffJpegEncodeUtil.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FKDestination.h"
#include "tiffio.h"
#include "FKTiffEncodeUtil.h"
class FKTiffJpegEncodeUtil : public FKTiffEncodeUtil
{
public:
 FKTiffJpegEncodeUtil();
 virtual ~FKTiffJpegEncodeUtil();
 virtual BOOL WriteScanlinesWithData(const ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError) override;
protected:
 virtual uint32_t GetRowsPerStrip(uint32_t compression) override;
 virtual uint32_t GetRgbColorSpaceForCompression(uint32_t compression) override;
 virtual BOOL StartWriting() override;
 virtual BOOL FinalizeWriting() override;
private:
 std::vector<uint8_t> m_pageBuffer;
};
