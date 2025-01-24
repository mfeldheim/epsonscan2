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
//  ESCI2DataEnumerator.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCI2DataEnumerator.h"
CESCI2DataEnumerator::CESCI2DataEnumerator( ES_CMN_FUNCS::BUFFER::CESHeapBuffer& data )
 : m_pDataSource( NULL ),
    m_cBufferStream( &data )
{
}
CESCI2DataEnumerator::~CESCI2DataEnumerator(void)
{
}
void CESCI2DataEnumerator::SetDataSource( IESCI2DataEnumeratorDataSource* pDataSource )
{
 m_pDataSource = pDataSource;
}
UInt32 CESCI2DataEnumerator::Read( PESByte pBuffer, UInt32 un32Length )
{
 if ( pBuffer == NULL ){
  return 0;
 }
 memset( pBuffer, 0, un32Length );
 UInt32 un32Read = m_cBufferStream.Read( pBuffer, un32Length );
 if ( ( un32Read < un32Length ) && ( m_pDataSource != NULL ) ){
  un32Read += m_pDataSource->ReadFromEnumerator( this, pBuffer + un32Read, un32Length - un32Read );
 }
 return un32Read;
}
ESAny CESCI2DataEnumerator::Nextdata()
{
 char szFourBytes[5] = {0};
 int res = Read( (LPBYTE)szFourBytes, 4 );
 if ( res <= 0 ){
  return nullptr;
 }
 char chDataType = szFourBytes[0];
 switch ( chDataType ){
  case 'd':
   {
    char buf[4] = {0};
    memcpy(buf, szFourBytes + 1, 3);
    ESNumber nValue = (ESNumber)strtol( buf, NULL, 10 );
    return nValue;
   }
   break;
  case 'i':
   {
    char buf[8] = {0};
    memcpy(buf, szFourBytes + 1, 3);
    res = Read( (PESByte)buf+3, 4 );
    if ( res < 4 ){
     return nullptr;
    }
    ESNumber nValue = (ESNumber)strtol( buf, NULL, 10 );
    return nValue;
   }
   break;
  case 'x':
   {
    char buf[8] = {0};
    memcpy(buf, szFourBytes + 1, 3);
    res = Read( (PESByte)buf+3, 4 );
    if ( res < 4 ){
     return nullptr;
    }
    ESNumber nValue = (ESNumber)strtol( buf, NULL, 16 );
    return nValue;
   }
   break;
  case 'h':
   {
    char buf[4] = {0};
    memcpy(buf, szFourBytes + 1, 3);
    long lDataSize = strtol( buf, NULL, 16 );
    long lAlignedLength = ((lDataSize + 3) / 4) * 4;
    if ( lAlignedLength <= 0 ){
     return nullptr;
    }
    ESByteData data(lAlignedLength, 0);
    res = Read( &data[0], (UInt32)lAlignedLength );
    if ( res < lAlignedLength ){
     return nullptr;
    }
    data.resize(lDataSize);
    return data;
   }
   break;
  default:
   {
    ESStringA strValue = szFourBytes;
    return strValue;
   }
   break;
 }
}
