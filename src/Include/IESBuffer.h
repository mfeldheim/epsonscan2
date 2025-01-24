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
//  IESBuffer.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
namespace ES_CMN_FUNCS
{
 namespace BUFFER
 {
   enum ENUM_BUFFER_TYPE{
     BUFFER_TYPE_GLOBAL=0,
     BUFFER_TYPE_HEAP,
     BUFFER_TYPE_VIRTUAL
   };
   class IESBuffer{
     public:
       virtual ~IESBuffer() {}
       virtual ENUM_BUFFER_TYPE GetBufferType() = 0;
       virtual bool IsEmpty() = 0;
       virtual UInt32 GetLength() const = 0;
       virtual UInt8* GetConstBufferPtr() const = 0;
       virtual UInt8* GetBufferPtr() = 0;
       virtual bool AllocBuffer( UInt32 nBufferSize ) = 0;
       virtual bool FillBuffer(UInt8 nValue) = 0;
       virtual bool ReAllocBuffer(UInt32 nBufferSize) = 0;
       virtual void FreeBuffer() = 0;
       virtual bool Attach( IESBuffer& cSrcBuffer ) = 0;
       virtual UInt8* Detach() = 0;
       virtual bool CopyBuffer( const IESBuffer& cInBuffer ) = 0;
       virtual bool CopyBuffer( const UInt8* pBuffer, UInt32 nBufferSize, UInt32 nAllocSize = 0)= 0;
       virtual bool CopyBuffer(const UInt32 un32Offset,const UInt8* ,UInt32 nCopySize) =0;
       virtual bool AppendBuffer( const UInt8* pBuffer, UInt32 nBufferSize ) = 0;
       virtual bool GetStreamBuffer(UInt32 nBufferLen, UInt32 nExpandLen) = 0;
       virtual bool ReleaseStreamBuffer() = 0;
       virtual UInt32 GetValidDataLen() = 0;
    };
 }
}
