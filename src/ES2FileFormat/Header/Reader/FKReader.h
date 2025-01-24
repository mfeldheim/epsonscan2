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
//  FKReader.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FileFormatKit.h"
#include "FKReaderKeys.h"
#include "FKSource.h"
#include "FKDestination.h"
class CFKReader : public IFKReader
{
protected:
 BOOL m_bOpen;
 ESNumber m_nValidImageHeight;
 BOOL m_bReadOnlyValidData;
 IFKDestination* m_piFkDestination;
 ESImageInfo m_esImageInfo;
public:
 CFKReader();
 virtual ~CFKReader();
 static CFKReader* CreateFKReaderWithType(FKReaderType eType);
 void SetValidImageHeight(ESNumber nHeight,BOOL bReadOnlyValidData) override
 {
  m_nValidImageHeight = nHeight;
  m_bReadOnlyValidData = bReadOnlyValidData;
 }
 IFKDestination* GetCFkDestionation()
 {
  return m_piFkDestination;
 }
 ESImageInfo& GetImageInfo(void);
 virtual void GetImageInfoAsJson(IESResultString& strJson) override;
 BOOL OpenWithDestination( IFKDestination* pcDestination, ENUM_FK_ERROR_CODE& eError );
 BOOL OpenWithDestinationAsJson( IFKDestination* pcDestination, ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 virtual BOOL AppendSource(IFKSource* source, ENUM_FK_ERROR_CODE& eError);
 BOOL CloseAndReturnError( ENUM_FK_ERROR_CODE& eError );
 BOOL CloseWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 virtual BOOL OpenReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL AppendSourceToReader( IFKSource* pcSource, ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL CloseReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError ) = 0;
 void Destroy(){
  delete this;
 }
};
