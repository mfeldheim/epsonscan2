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
//  ESFile.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#ifndef WIN32
#include <iostream>
#include <fstream>
#endif
#include "../ESCommonTypedef.h"
#include "ESBuffer.h"
class CESFile
{
public:
typedef enum _ES_OPEN_MODES {
 ES_OPEN_MODE_READ,
 ES_OPEN_MODE_WRITE,
 ES_OPEN_MODE_APPEND,
 ES_OPEN_MODE_READ_PLUS,
 ES_OPEN_MODE_WRITE_PLUS
} ES_OPEN_MODE;
private:
#ifdef WIN32
 HANDLE m_hFileHandle;
#else
 std::fstream* m_hFileHandle;
 ES_OPEN_MODE m_reOpenMode;
#endif
 ESString m_strFilePath;
public:
 CESFile(void);
 virtual ~CESFile(void);
 static CESFile* CreateFileInstanceWithPath(ESString strPath,ES_OPEN_MODE un32Mode = ES_OPEN_MODE_READ);
 static CESFile* CreateTempFileInstanceWithPrefix(ESString strFolder, ESString strPrefix, ES_OPEN_MODE un32Mode = ES_OPEN_MODE_READ);
 ESString GetFileName();
 BOOL IsOpen();
 HANDLE GetFileHandle(){
  return m_hFileHandle;
 }
 BOOL Open(ESString strPath,ES_OPEN_MODE eOpenMode = ES_OPEN_MODE_READ);
 BOOL CreateTempFile(ESString strFolder, ESString strPrefix, ES_OPEN_MODE eOpenMode = ES_OPEN_MODE_WRITE_PLUS);
 BOOL WriteData(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer);
 BOOL WriteData(UInt32 un32Length,LPVOID pData);
 void Flush(void);
 void ReadAvailableData(ES_CMN_FUNCS::BUFFER::IESBuffer& cOutBuf);
 void ReadDataToEndOfFile(ES_CMN_FUNCS::BUFFER::IESBuffer& cOutBuf);
 int ReadDataOfLength(UInt32 un32Length,ES_CMN_FUNCS::BUFFER::IESBuffer& cOutBuf);
 int ReadDataOfLength(UInt32 un32Length,LPVOID pBuf);
 BOOL SeekToHead();
 BOOL SeekToFileOffset(UInt32 un32Offset);
 BOOL SeekToEndOfFile();
 UInt32 GetLength();
 BOOL CloseFile();
};
