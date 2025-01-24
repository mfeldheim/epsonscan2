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
//  FKPnmWriter.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../Base/FKConcreteWriterProtocol.h"
class CFKPnmEncodeUtil;
class CFKPnmWriter : public CFKWriter
{
public:
 CFKPnmWriter();
 ~CFKPnmWriter();
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
private:
 CFKPnmEncodeUtil* m_pCFKPnmEncodeUtil;
};
