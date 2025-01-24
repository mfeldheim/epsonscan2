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
//  ESCI2DataConstructor.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCI2DataConstructor.h"
CESCI2DataConstructor::CESCI2DataConstructor()
{
}
CESCI2DataConstructor::~CESCI2DataConstructor()
{
}
void CESCI2DataConstructor::Init()
{
 m_data.clear();
}
void CESCI2DataConstructor::AppendFourCharString( const ESStringA& strFourChar )
{
 char buf[5] = {0};
 memcpy_s( buf, sizeof(buf), strFourChar.c_str(), std::min<size_t>(strFourChar.length(), 4));
 m_data.insert( m_data.end(), buf, buf+4 );
}
void CESCI2DataConstructor::AppendDecimal( unsigned short usDecimal )
{
 assert(usDecimal <= 999);
 char buf[5] = {0};
 sprintf_s(buf, sizeof(buf), "d%03u", usDecimal);
 m_data.insert( m_data.end(), buf, buf+4 );
}
void CESCI2DataConstructor::AppendInteger( int nInteger )
{
 assert(-999999 <= nInteger && nInteger <= 9999999);
 char buf[9] = {0};
 sprintf_s(buf, sizeof(buf), "i%07d", nInteger);
 m_data.insert( m_data.end(), buf, buf+8 );
}
void CESCI2DataConstructor::AppendHex( unsigned long nHex )
{
 assert(nHex <= 0xFFFFFFF);
 char buf[9] = {0};
 sprintf_s(buf, sizeof(buf), "x%07lX", nHex);
 m_data.insert( m_data.end(), buf, buf+8 );
}
void CESCI2DataConstructor::AppendData( const ESByteData& data )
{
 UInt32 un32ength = (UInt32)data.size();
    assert(un32ength <= 0xFFF);
 char buf[5] = {0};
 sprintf_s(buf, sizeof(buf), "h%03X", (unsigned int)un32ength);
 m_data.insert( m_data.end(), buf, buf+4 );
 ESByteData alignedData( data.begin(), data.end() );
 int nAlignedLength = (int)( (alignedData.size() + 3)/ 4 ) * 4 ;
 alignedData.resize( nAlignedLength );
 m_data.insert( m_data.end(), alignedData.begin(), alignedData.end() );
}
