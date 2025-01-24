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
//  ESBuffer.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESBuffer.h"
#include <assert.h>
#ifdef WIN32
#include <algorithm>
#endif
namespace ES_CMN_FUNCS
{
 namespace BUFFER
 {
  UInt8* AllocHeapBuffer( UInt32 nSize)
  {
#ifdef WIN32
   HANDLE hProcessHeap = ::GetProcessHeap();
   if ( hProcessHeap != NULL ){
    return (UInt8*)::HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, nSize);
   }
#else
   UInt8* tmp_buf = (UInt8*)::malloc(nSize);
   if(tmp_buf){
    return (UInt8*)memset(tmp_buf, 0, nSize);
   }
#endif
   return NULL;
  }
  void FreeHeapBuffer( void* pBuff )
  {
   try {
    if ( pBuff != NULL ){
#ifdef WIN32
     HANDLE hProcessHeap = ::GetProcessHeap();
     if ( hProcessHeap != NULL ){
      ::HeapFree(hProcessHeap, 0, (LPVOID)pBuff);
     }
#else
     free(pBuff);
     pBuff = NULL;
#endif
    }
   } catch(...){
   }
  }
  UInt8* ReAllocHeapBuffer( void* pBuff, UInt32 nSize )
  {
#ifdef WIN32
   HANDLE hProcessHeap = ::GetProcessHeap();
   if ( hProcessHeap != NULL ){
    return (UInt8*)::HeapReAlloc(hProcessHeap, HEAP_ZERO_MEMORY, pBuff, nSize);
   }
   return NULL;
#else
   return (UInt8*)realloc(pBuff, nSize);
#endif
  }
#ifdef WIN32
  UInt8* AllocGlobalBuffer( UInt32 nSize)
  {
#ifdef WIN32
   return (UInt8*)::GlobalAlloc( GPTR, nSize );
#else
   return (UInt8*)AllocHeapBuffer( nSize );
#endif
  }
  void FreeGlobalBuffer( void* pBuff)
  {
   try {
    if ( pBuff != NULL ){
#ifdef WIN32
     ::GlobalFree((HGLOBAL) pBuff);
#else
     free(pBuff);
     pBuff = NULL;
#endif
    }
   } catch(...){
   }
  }
  UInt8* ReAllocGlobalBuffer( void* pBuff, UInt32 nSize )
  {
#ifdef WIN32
   return (UInt8*)::GlobalReAlloc( (HGLOBAL)pBuff, nSize, GPTR );
#else
   return (UInt8*)realloc( (void*)pBuff, nSize );
#endif
  }
  UInt8* AllocVirtualBuffer( UInt32 nSize)
  {
#ifdef WIN32
   return (UInt8*)::VirtualAlloc(NULL,nSize,MEM_COMMIT,PAGE_READWRITE);
#else
   return (UInt8*)AllocHeapBuffer(nSize);
#endif
  }
  void FreeVirtualBuffer( void* pBuff)
  {
   try {
    if ( pBuff != NULL ){
#ifdef WIN32
     ::VirtualFree( pBuff,0,MEM_RELEASE);
#else
     free(pBuff);
     pBuff = NULL;
#endif
    }
   } catch(...){
   }
  }
  UInt8* ReAllocVirtualBuffer( void* pBuff,UInt32 nOldSize, UInt32 nNewSize )
  {
   void* pNewBuf = AllocVirtualBuffer(nNewSize);
   if(pNewBuf){
    memcpy_s(pNewBuf,nNewSize,pBuff,nOldSize);
    FreeVirtualBuffer(pBuff);
   }
   return (UInt8*)pNewBuf;;
  }
#endif
  CESBuffer::CESBuffer()
   : m_pBuffer( NULL ),
     m_nBufferSize( 0 ),
     m_nValidDataLen(0),
     m_nStreamExpandLen(0)
  {
  }
  CESBuffer::~CESBuffer(){
  }
  bool CESBuffer::IsEmpty()
  {
   return (m_pBuffer == NULL ) ? true : false;
  }
  UInt32 CESBuffer::GetLength() const
  {
   return m_nBufferSize;
  }
  UInt8* CESBuffer::GetConstBufferPtr() const
  {
   return m_pBuffer;
  }
  UInt8* CESBuffer::GetBufferPtr()
  {
   return m_pBuffer;
  }
  bool CESBuffer::AllocBuffer( UInt32 nBufferSize )
  {
   FreeBuffer();
   m_pBuffer = AllocMemory( nBufferSize );
   if ( m_pBuffer != NULL ){
    m_nBufferSize = nBufferSize;
    m_nValidDataLen = nBufferSize;
    return true;
   } else {
    assert(false);
    return false;
   }
  }
  bool CESBuffer::FillBuffer(UInt8 nValue)
  {
   for (UInt32 i = 0; i < m_nBufferSize; i++)
   {
    m_pBuffer[i] = nValue;
   }
   return true;
  }
  bool CESBuffer::ReAllocBuffer( UInt32 nBufferSize )
  {
   if (nBufferSize > m_nBufferSize)
   {
    UInt8* pBuffer = ReAllocMemory(m_pBuffer, nBufferSize );
    if (pBuffer != NULL) {
     m_pBuffer = pBuffer;
     m_nBufferSize = nBufferSize;
     m_nValidDataLen= nBufferSize;
     return true;
    } else {
     return false;
    }
   }else{
    m_nBufferSize = nBufferSize;
    m_nValidDataLen= nBufferSize;
    return true;
   }
  }
  void CESBuffer::FreeBuffer()
  {
   if ( m_pBuffer ){
    FreeMemory( (void*)m_pBuffer );
    m_pBuffer = NULL;
    m_nBufferSize = 0;
    m_nValidDataLen= 0;
   }
  }
  bool CESBuffer::Attach( IESBuffer& cSrcBuffer )
  {
   bool bRet = true;
   if ( GetBufferType() == cSrcBuffer.GetBufferType() ){
    UInt32 un32Len = cSrcBuffer.GetLength();
    UInt8* pBufTemp = cSrcBuffer.Detach();
    CESBuffer::Attach( pBufTemp, un32Len );
    bRet = true;
   } else {
    bRet = CESBuffer::CopyBuffer( cSrcBuffer );
    if ( bRet ){
     cSrcBuffer.FreeBuffer();
    }
   }
   return bRet;
  }
  UInt8* CESBuffer::Detach()
  {
   UInt8* pTmp = m_pBuffer;
   m_pBuffer = NULL;
   m_nBufferSize = 0;
   m_nValidDataLen=0;
   return pTmp;
  }
  bool CESBuffer::CopyBuffer( const IESBuffer& cInBuffer )
  {
   return CopyBuffer( cInBuffer.GetConstBufferPtr(), cInBuffer.GetLength(), cInBuffer.GetLength() );
  }
  bool CESBuffer::CopyBuffer( const UInt8* pBuffer, UInt32 nBufferSize, UInt32 nAllocSize )
  {
   FreeBuffer();
   if ( nBufferSize == 0 ){
    return true;
   }
   try {
    if ( nAllocSize < nBufferSize ){
     nAllocSize = nBufferSize;
    }
    AllocBuffer( nAllocSize );
    if ( IsEmpty() ){
     return false;
    }
    errno_t err = ::memcpy_s( m_pBuffer, m_nBufferSize, pBuffer, nBufferSize );
    return ( err == 0 );
   } catch(...){
    return false;
   }
  }
  bool CESBuffer::CopyBuffer( const UInt32 nOffset,const UInt8* pBuffer, UInt32 nBufferSize){
   if ( nBufferSize == 0 ){
    return true;
   }
   try {
    if ( nOffset + nBufferSize > GetLength() ){
     return false;
    }
    errno_t err = ::memcpy_s( m_pBuffer + nOffset, m_nBufferSize- nOffset, pBuffer, nBufferSize );
    return ( err == 0 );
   } catch(...){
    return false;
   }
  }
  void CESBuffer::Attach( UInt8* pBuffer, UInt32 un32Size )
  {
   FreeBuffer();
   m_pBuffer = pBuffer;
   m_nBufferSize = un32Size;
   m_nValidDataLen = un32Size;
  }
  bool CESBuffer::AppendBuffer( const UInt8* pBuffer, UInt32 nBufferSize )
  {
   if ( nBufferSize == 0 ){
    return true;
   }
   UInt8* pCpyPos = NULL;
   if ( IsEmpty() ){
    if ( !AllocBuffer( nBufferSize ) ){
     return false;
    }
    pCpyPos = GetBufferPtr();
    m_nValidDataLen = 0;
   } else {
    UInt32 nNewBufferSize = GetLength();
    if(m_nStreamExpandLen != 0){
     if( GetValidDataLen() + nBufferSize > GetLength()){
      nNewBufferSize = GetValidDataLen() + std::max<UInt32>(m_nStreamExpandLen,nBufferSize);
     }
     pCpyPos = GetBufferPtr() + GetValidDataLen();
    }else{
     nNewBufferSize = m_nBufferSize + nBufferSize;
     pCpyPos = GetBufferPtr();
    }
    if(nNewBufferSize > GetLength()){
     UInt8* pRealloc = ReAllocMemory( GetBufferPtr(), nNewBufferSize );
     if ( pRealloc == NULL ){
      assert(false);
      return false;
     } else {
      m_pBuffer = pRealloc;
      m_nBufferSize = nNewBufferSize;
      pCpyPos = m_pBuffer + GetValidDataLen();
     }
    }
   }
   if ( pCpyPos != NULL ){
    memcpy_s( pCpyPos, m_nBufferSize - GetValidDataLen(), pBuffer, nBufferSize );
    m_nValidDataLen += nBufferSize;
   }
   return true;
  }
  bool CESBuffer::GetStreamBuffer(UInt32 nBufferLen, UInt32 nExpandLen){
   bool bRet= AllocBuffer(nBufferLen);
    if(bRet){
     m_nValidDataLen = 0;
     m_nStreamExpandLen = nExpandLen;
    }else{
     m_nStreamExpandLen = 0;
    }
   return bRet;
  }
  bool CESBuffer::ReleaseStreamBuffer(){
   if(m_nValidDataLen > m_nBufferSize){
    assert(false);
   }
   if(m_nValidDataLen ==0){
    FreeBuffer();
   }
   m_nBufferSize = m_nValidDataLen;
   m_nStreamExpandLen =0;
   return TRUE;
  }
  UInt32 CESBuffer::GetValidDataLen(){
   return m_nValidDataLen;
  }
  CESHeapBuffer::CESHeapBuffer()
  {
  }
  CESHeapBuffer::CESHeapBuffer( UInt32 nBufferSize )
  {
   AllocBuffer( nBufferSize );
  }
  CESHeapBuffer::CESHeapBuffer( ESString strSrc )
  {
   if ( !strSrc.empty() ){
    UInt32 nStrLength = (UInt32)(strSrc.length() * sizeof(ES_CHAR));
    UInt32 nBufferSize = nStrLength + sizeof(ES_CHAR);
    CopyBuffer( (UInt8*)strSrc.c_str(), nStrLength, nBufferSize );
   }
  }
  CESHeapBuffer::CESHeapBuffer( const CESHeapBuffer& rhs )
  {
   CopyBuffer( rhs );
  }
  CESHeapBuffer::~CESHeapBuffer()
  {
   FreeBuffer();
  }
  CESHeapBuffer& CESHeapBuffer::operator=( CESHeapBuffer& rhs )
  {
   CopyBuffer( rhs );
   return *this;
  }
  CESHeapBuffer& CESHeapBuffer::operator+=( CESHeapBuffer& rhs )
  {
   AppendBuffer( rhs.GetBufferPtr(), rhs.GetLength() );
   return *this;
  }
  UInt8* CESHeapBuffer::AllocMemory( UInt32 nSize)
  {
   return AllocHeapBuffer( nSize );
  }
  void CESHeapBuffer::FreeMemory( void* pBuff )
  {
   FreeHeapBuffer( pBuff );
  }
  UInt8* CESHeapBuffer::ReAllocMemory( void* pBuffer, UInt32 nSize )
  {
   return ReAllocHeapBuffer( pBuffer, nSize );
  }
#ifdef WIN32
  CESGlobalBuffer::CESGlobalBuffer()
  {
  }
  CESGlobalBuffer::CESGlobalBuffer( UInt32 nBufferSize )
  {
   AllocBuffer( nBufferSize );
  }
  CESGlobalBuffer::CESGlobalBuffer( ESString strSrc )
  {
   if ( !strSrc.empty() ){
    UInt32 nStrLength = strSrc.length() * sizeof(ES_CHAR);
    UInt32 nBufferSize = nStrLength + sizeof(ES_CHAR);
    CopyBuffer( (UInt8*)strSrc.c_str(), nStrLength, nBufferSize );
   }
  }
  CESGlobalBuffer::CESGlobalBuffer( const CESGlobalBuffer& rhs )
  {
   CopyBuffer( rhs );
  }
  CESGlobalBuffer::~CESGlobalBuffer()
  {
   FreeBuffer();
  }
  CESGlobalBuffer& CESGlobalBuffer::operator=( CESGlobalBuffer& rhs )
  {
   CopyBuffer( rhs );
   return *this;
  }
  CESGlobalBuffer& CESGlobalBuffer::operator+=( CESGlobalBuffer& rhs )
  {
   AppendBuffer( rhs.GetBufferPtr(), rhs.GetLength() );
   return *this;
  }
  UInt8* CESGlobalBuffer::AllocMemory( UInt32 nSize)
  {
   return AllocGlobalBuffer( nSize );
  }
  void CESGlobalBuffer::FreeMemory( void* pBuff)
  {
   FreeGlobalBuffer( pBuff );
  }
  UInt8* CESGlobalBuffer::ReAllocMemory( void* pBuffer, UInt32 nSize )
  {
   return ReAllocGlobalBuffer( pBuffer, nSize );
  }
  CESVirtualBuffer::CESVirtualBuffer()
  {
  }
  CESVirtualBuffer::CESVirtualBuffer( UInt32 nBufferSize )
  {
   AllocBuffer( nBufferSize );
  }
  CESVirtualBuffer::CESVirtualBuffer( ESString strSrc )
  {
   if ( !strSrc.empty() ){
    UInt32 nStrLength = strSrc.length() * sizeof(ES_CHAR);
    UInt32 nBufferSize = nStrLength + sizeof(ES_CHAR);
    CopyBuffer( (UInt8*)strSrc.c_str(), nStrLength, nBufferSize );
   }
  }
  CESVirtualBuffer::CESVirtualBuffer( const CESVirtualBuffer& rhs )
  {
   CopyBuffer( rhs );
  }
  CESVirtualBuffer::~CESVirtualBuffer()
  {
   FreeBuffer();
  }
  CESVirtualBuffer& CESVirtualBuffer::operator=( CESVirtualBuffer& rhs )
  {
   CopyBuffer( rhs );
   return *this;
  }
  CESVirtualBuffer& CESVirtualBuffer::operator+=( CESVirtualBuffer& rhs )
  {
   AppendBuffer( rhs.GetBufferPtr(), rhs.GetLength() );
   return *this;
  }
  UInt8* CESVirtualBuffer::AllocMemory( UInt32 nSize)
  {
   return AllocVirtualBuffer( nSize );
  }
  void CESVirtualBuffer::FreeMemory( void* pBuff)
  {
   FreeVirtualBuffer( pBuff );
  }
  UInt8* CESVirtualBuffer::ReAllocMemory( void* pBuffer, UInt32 nSize )
  {
   return ReAllocVirtualBuffer( pBuffer,GetLength(), nSize );
  }
#endif
  CESIBufferStream::CESIBufferStream( IESBuffer* pBuffer )
  {
   m_pBuffer = pBuffer;
   m_nSeekPos = 0;
  }
  UInt32 CESIBufferStream::GetLength(){
   return ( m_pBuffer == NULL ) ? 0 : m_pBuffer->GetLength();
  }
  UInt32 CESIBufferStream::Read( UInt8* pOutBuffer, UInt32 nSize )
  {
   UInt32 nRead = 0;
   UInt32 nDataSize = GetLength();
   if ( nDataSize <= m_nSeekPos ){
    return 0;
   }
   nDataSize -= m_nSeekPos;
   if ( nSize <= nDataSize ){
    nRead = nSize;
   } else {
    nRead = nSize - nDataSize;
   }
   errno_t err = memcpy_s( pOutBuffer, nSize, m_pBuffer->GetBufferPtr() + m_nSeekPos, nRead );
   m_nSeekPos += nRead;
   if ( err != 0 ){
    return 0;
   }
   return nRead;
  }
  CESOBufferStream::CESOBufferStream( IESBuffer* pBuffer )
  {
   m_pBuffer = pBuffer;
   m_nSeekPos = 0;
  }
  UInt32 CESOBufferStream::GetLength(){
   return ( m_pBuffer == NULL ) ? 0 : m_pBuffer->GetLength();
  }
  UInt32 CESOBufferStream::GetWrittenLength(){
   return m_nSeekPos;
  }
  UInt32 CESOBufferStream::Write( UInt8* pOutBuffer, UInt32 nSize )
  {
   UInt32 nWrite = 0;
   UInt32 nDataSize = GetLength();
   if ( nDataSize <= m_nSeekPos ){
    return 0;
   }
   nDataSize -= m_nSeekPos;
   if ( nSize <= nDataSize ){
    nWrite = nSize;
   } else {
    nWrite = nSize - nDataSize;
   }
   errno_t err = memcpy_s( m_pBuffer->GetBufferPtr() + m_nSeekPos, nDataSize, pOutBuffer, nWrite );
   m_nSeekPos += nWrite;
   if ( err != 0 ){
    return 0;
   }
   return nWrite;
  }
 };
};
