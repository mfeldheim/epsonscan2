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
//  ESCI2DataConstructor.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
class CESCI2DataConstructor
{
public:
 CESCI2DataConstructor();
 ~CESCI2DataConstructor();
 void Init();
 void AppendFourCharString( const ESStringA& strFourChar );
 void AppendDecimal( unsigned short usDecimal );
 void AppendInteger( int nInteger );
 void AppendHex( unsigned long nHex );
 void AppendData( const ESByteData& data );
 ESByteData& GetData()
 {
  return m_data;
 }
 ESByteData* GetDataPtr()
 {
  return &m_data;
 }
protected:
 ESByteData m_data;
};
