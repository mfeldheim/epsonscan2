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
//  FKBmpReader.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FKReader.h"
#include "../Base/FKConcreteReaderProtocol.h"
class CFKBmpReader : public CFKReader,IFKConcreteReaderProtocol
{
protected:
public:
 CFKBmpReader();
 ~CFKBmpReader();
 virtual BOOL GetImageInfo(ESImageInfo& outImageInfo);
 virtual BOOL OpenReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError) override;
 virtual BOOL AppendSourceToReader( IFKSource* pcSource, ENUM_FK_ERROR_CODE& eError ) override;
 virtual BOOL CloseReaderWithOptionAsJson( ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError ) override;
private :
 ES_CMN_FUNCS::BUFFER::IESBuffer* GetInputBuffer(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer);
 void StorePendingBuffer(ES_CMN_FUNCS::BUFFER::IESBuffer* pInputBuf, uint32_t bufferPosition);
 BOOL ReadHeaderFromData(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer, ENUM_FK_ERROR_CODE& eError);
 BOOL Notify(ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError);
 BOOL NotifyToDestination(ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError);
 void AppendSourceFromPath(ESString& strPath, ENUM_FK_ERROR_CODE& eError);
 void AppendSourceFromData(ES_CMN_FUNCS::BUFFER::IESBuffer& pBuffer, ENUM_FK_ERROR_CODE& eError);
 ESString m_strImageInfoJson;
 uint32_t m_currentLine;
 uint32_t m_MaxLoadLine;
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_pendingBuffer;
 BITMAPINFOHEADER m_stBmInfo;
 BOOL m_bStarted;
 __int64 m_dataPosition;
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_LoadedDataToNotify;
};
