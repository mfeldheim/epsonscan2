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
//  ESBuffer.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCommonTypedef.h"
#include "../../Include/IESBuffer.h"
namespace ES_CMN_FUNCS
{
 namespace BUFFER
 {
  UInt8* AllocHeapBuffer( UInt32 nSize);
  void FreeHeapBuffer( void* pBuff );
  UInt8* AllocGlobalBuffer( UInt32 nSize);
  void FreeGlobalBuffer( void* pBuff);
  UInt8* AllocVirtuallBuffer( UInt32 nSize);
  void FreeVirtualBuffer( void* pBuff);
  class CESBuffer : public IESBuffer{
  public:
   virtual ENUM_BUFFER_TYPE GetBufferType() = 0;
   CESBuffer();
   virtual ~CESBuffer();
   bool IsEmpty();
   UInt32 GetLength() const;
   UInt8* GetConstBufferPtr() const;
   UInt8* GetBufferPtr();
   bool AllocBuffer( UInt32 nBufferSize );
   bool FillBuffer(UInt8 nValue);
   bool ReAllocBuffer(UInt32 nBufferSize);
   void FreeBuffer();
   bool Attach( IESBuffer& cSrcBuffer );
   UInt8* Detach();
   bool CopyBuffer( const IESBuffer& cInBuffer );
   bool CopyBuffer( const UInt8* pBuffer, UInt32 nBufferSize, UInt32 nAllocSize = 0);
   bool CopyBuffer( const UInt32 nOffset,const UInt8* pBuffer, UInt32 nBufferSize);
   bool AppendBuffer( const UInt8* pBuffer, UInt32 nBufferSize );
   bool GetStreamBuffer(UInt32 nBufferLen, UInt32 nExpandLen);
   bool ReleaseStreamBuffer();
   UInt32 GetValidDataLen();
  protected:
   virtual UInt8* AllocMemory( UInt32 ) = 0;
   virtual void FreeMemory( void* pBuff ) = 0;
   virtual UInt8* ReAllocMemory( void*, UInt32 ) = 0;
   void Attach( UInt8* pBuffer, UInt32 un32Size );
  private:
   UInt8* m_pBuffer;
   UInt32 m_nBufferSize;
   UInt32 m_nValidDataLen;
   UInt32 m_nStreamExpandLen;
  };
  class CESHeapBuffer : public CESBuffer
  {
  public:
   ENUM_BUFFER_TYPE GetBufferType() override{
    return BUFFER_TYPE_HEAP;
   }
   CESHeapBuffer();
   CESHeapBuffer( UInt32 nBufferSize );
   CESHeapBuffer( ESString strSrc );
   CESHeapBuffer( const CESHeapBuffer& rhs );
   virtual ~CESHeapBuffer();
   CESHeapBuffer& operator=( CESHeapBuffer& rhs );
   CESHeapBuffer& operator+=( CESHeapBuffer& rhs );
  protected:
   virtual UInt8* AllocMemory( UInt32 ) override;
   virtual void FreeMemory( void* pBuff ) override;
   virtual UInt8* ReAllocMemory( void*, UInt32 ) override;
  };
#ifdef WIN32
  class CESGlobalBuffer : public CESBuffer
  {
  public:
   ENUM_BUFFER_TYPE GetBufferType(){
    return BUFFER_TYPE_GLOBAL;
   }
   CESGlobalBuffer();
   CESGlobalBuffer( UInt32 nBufferSize );
   CESGlobalBuffer( ESString strSrc );
   CESGlobalBuffer( const CESGlobalBuffer& rhs );
   virtual ~CESGlobalBuffer();
   CESGlobalBuffer& operator=( CESGlobalBuffer& rhs );
   CESGlobalBuffer& operator+=( CESGlobalBuffer& rhs );
  protected:
   virtual UInt8* AllocMemory( UInt32 ) override;
   virtual void FreeMemory( void* pBuff ) override;
   virtual UInt8* ReAllocMemory( void*, UInt32 ) override;
  };
  class CESVirtualBuffer : public CESBuffer
  {
  public:
   ENUM_BUFFER_TYPE GetBufferType(){
    return BUFFER_TYPE_VIRTUAL;
   }
   CESVirtualBuffer();
   CESVirtualBuffer( UInt32 nBufferSize );
   CESVirtualBuffer( ESString strSrc );
   CESVirtualBuffer( const CESVirtualBuffer& rhs );
   virtual ~CESVirtualBuffer();
   CESVirtualBuffer& operator=( CESVirtualBuffer& rhs );
   CESVirtualBuffer& operator+=( CESVirtualBuffer& rhs );
  protected:
   virtual UInt8* AllocMemory( UInt32 ) override;
   virtual void FreeMemory( void* pBuff ) override;
   virtual UInt8* ReAllocMemory( void*, UInt32 ) override;
  };
#endif
  class CESIBufferStream {
  public:
   CESIBufferStream( IESBuffer* pBuffer );
   UInt32 GetLength();
   UInt32 Read( UInt8* pOutBuffer, UInt32 nSize );
  protected:
   IESBuffer* m_pBuffer;
   UInt32 m_nSeekPos;
  };
  class CESOBufferStream {
  public:
   CESOBufferStream( IESBuffer* pBuffer );
   UInt32 GetLength();
   UInt32 GetWrittenLength();
   UInt32 Write( UInt8* pOutBuffer, UInt32 nSize );
  protected:
   IESBuffer* m_pBuffer;
   UInt32 m_nSeekPos;
  };
 };
};
