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
//  FKWriter.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FKWriterKeys.h"
#include "FKSource.h"
#include "FKDestination.h"
#include "FileFormatKit.h"
enum FKWriterState
{
    kFKWriterStateNotInitialized = 0,
    kFKWriterStateNotOpened = 1,
    kFKWriterStateProcessing = 2,
};
class CFKWriter : public IFKWriter
{
protected:
    FKWriterState m_eState;
    ESImageInfo m_dictEsImageInfo;
    IFKDestination* m_pCFKDestination;
    ESNumber m_uPages;
public:
 CFKWriter();
 virtual ~CFKWriter();
 static CFKWriter* CreateFKWriterWithType(FKWriterType eType,ESDictionary& dictOpetion);
 void Destroy(){
  delete this;
 }
 ESImageInfo& GetImageInfo()
 {
  return m_dictEsImageInfo;
 }
 IFKDestination* GetCFKDestination()
 {
  return m_pCFKDestination;
 }
 virtual BOOL IsMultiPageSupport() = 0;
 ESNumber GetPageCount();
 BOOL InitializeDestination( IFKDestination* pDestination, ENUM_FK_ERROR_CODE& eError );
 BOOL InitializeDestinationAsJson( IFKDestination* pDestination, ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 BOOL OpenPageWithImageInfo( ES_CHAR_CPTR pszImageInfoAsJson, ENUM_FK_ERROR_CODE& eError );
 BOOL OpenPageWithImageInfoAsJson( ES_CHAR_CPTR pszImageInfoAsJson, ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 BOOL ClosePageAndReturnError( ENUM_FK_ERROR_CODE& eError );
 BOOL ClosePageAndReturnErrorAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 BOOL FinalizeAndReturnError( ENUM_FK_ERROR_CODE& eError );
 BOOL FinalizeAndReturnErrorAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError );
 virtual BOOL AppendSource(IFKSource* pSource, ENUM_FK_ERROR_CODE& eError );
 virtual BOOL AppendConstSource(const IFKSource* pSource, ENUM_FK_ERROR_CODE& eError );
protected:
 BOOL CheckWriterState( FKWriterState ePreferedState, ENUM_FK_ERROR_CODE& eError ) const;
protected:
 virtual BOOL Initialize()=0;
 virtual BOOL InitializeWriterWithDestination( CFKDestination* pCFKDestination,
           FKWriterInitializeDestDict* pOption,
           ENUM_FK_ERROR_CODE& eError) = 0;
 virtual BOOL OpenWriterPageWithImageInfo( ESImageInfo* pImageInfo,
          FKWriterPageOpenDict* pOption,
          ENUM_FK_ERROR_CODE& eError) = 0;
 virtual BOOL CloseWriterPageWithOption( FKWriterPageCloseDict* pOption,
         ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL FinalizeWriterWithOption( FKWriterFinalizeDestDict* pOption,
         ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL AppendSourceToDestination( CFKSource* pSource, ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL AppendConstSourceToDestination(const CFKSource* pSource, ENUM_FK_ERROR_CODE& eError ) = 0;
 virtual BOOL CheckFileFormatMaxbytes(ESNumber nNextImageSize) {
  return TRUE;
 }
};
