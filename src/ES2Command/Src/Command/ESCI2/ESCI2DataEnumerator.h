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
//  ESCI2DataEnumerator.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/utils/ESBuffer.h"
class CESCI2DataEnumerator;
class IESCI2DataEnumeratorDataSource
{
public:
 virtual UInt32 ReadFromEnumerator( CESCI2DataEnumerator* pSender, PESByte pBuffer, UInt32 un32Length ) = 0;
};
class CESCI2DataEnumerator
{
public:
 explicit CESCI2DataEnumerator( ES_CMN_FUNCS::BUFFER::CESHeapBuffer& data );
 ~CESCI2DataEnumerator(void);
 void SetDataSource( IESCI2DataEnumeratorDataSource* pDataSouce );
 ESAny Nextdata();
protected:
 UInt32 Read( PESByte pBuffer, UInt32 un32Length );
private:
 ES_CMN_FUNCS::BUFFER::CESIBufferStream m_cBufferStream;
 IESCI2DataEnumeratorDataSource* m_pDataSource;
};
