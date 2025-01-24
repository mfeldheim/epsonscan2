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
//  ESCI2ScannedImage.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "ESScannedImage.h"
class CESCI2ScannedImage : public CESScannedImage
{
public:
 CESCI2ScannedImage();
 virtual ~CESCI2ScannedImage();
 virtual void DeleteInstance() override;
 ESNumber GetStoreBufferSize();
 void SetStoreBufferSize(ESNumber nBufferSize);
 ESNumber GetDummyBytesPerLine();
 void SetDummyBytesPerLine( ESNumber nDummyBytesPerLine );
 virtual void CloseWithWidth( ESNumber nWidth, ESNumber nHeight ) override;
 virtual ESErrorCode WriteData( ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cImageData ) override;
 virtual bool IsProgressAvailable() override;
protected:
 ESNumber m_nDummyBytesPerLine;
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_cRemainingData;
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_cJpegTempBuf;
 ESNumber m_nStoreBufferSize;
};
