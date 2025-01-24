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
//  FKTiffWriter.h -- template and derived ESC/I ESC/I-2 protocol commands

#include "FKWriter.h"
class FKTiffEncodeUtil;
class CFKTiffWriter : public CFKWriter
{
private:
 FKTiffEncodeUtil* m_pCFKTiffEncodeUtil;
 uint32_t m_unBytesPerLine;
public:
 CFKTiffWriter();
 ~CFKTiffWriter();
protected:
 virtual BOOL Initialize();
 virtual BOOL InitializeWriterWithDestination(CFKDestination* pCFKDestination,
  FKWriterInitializeDestDict* pOption,
  ENUM_FK_ERROR_CODE& eError);
 virtual BOOL OpenWriterPageWithImageInfo(ESImageInfo* pImageInfo,
  FKWriterPageOpenDict* pOption,
  ENUM_FK_ERROR_CODE& eError);
 virtual BOOL CloseWriterPageWithOption(FKWriterPageCloseDict* pOption,
  ENUM_FK_ERROR_CODE& eError);
 virtual BOOL FinalizeWriterWithOption(FKWriterFinalizeDestDict* pOption,
  ENUM_FK_ERROR_CODE& eError);
 virtual BOOL IsMultiPageSupport();
 virtual BOOL AppendSourceToDestination(CFKSource* pSource, ENUM_FK_ERROR_CODE& eError);
 virtual BOOL AppendConstSourceToDestination(const CFKSource* pSource, ENUM_FK_ERROR_CODE& eError);
 virtual BOOL CheckFileFormatMaxbytes(ESNumber nNextImageSize) ;
};
