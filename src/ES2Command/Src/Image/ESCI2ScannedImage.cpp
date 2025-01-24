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
//  ESCI2ScannedImage.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "CommonUtility/utils/ESBuffer.h"
#include "ESCI2ScannedImage.h"
using namespace ES_CMN_FUNCS::BUFFER;
static bool GetRowAlignedData( CESHeapBuffer& cImageData,
          UInt32 un32DummyBytesPerLine,
          UInt32 un32BytesPerRow,
          UInt32 un32ImageWidth,
          UInt32& un32OutLinesPerBlock,
          CESHeapBuffer& cOutRemainingData
          )
{
 try {
  CESHeapBuffer cDstImageData;
  UInt32 un32DataBytes = cImageData.GetLength();
  UInt32 un32LineBytes = un32BytesPerRow + un32DummyBytesPerLine;
  if ( un32LineBytes == 0 ){
   assert(false);
   return false;
  }
  un32OutLinesPerBlock = un32DataBytes / un32LineBytes;
  UInt32 un32RemainingBytes = un32DataBytes % un32LineBytes;
  if ( un32DummyBytesPerLine == 0 && un32RemainingBytes == 0 ){
   return true;
  }
  UInt32 un32OutDataBytes = un32OutLinesPerBlock * un32BytesPerRow;
  if ( un32DummyBytesPerLine > 0 ){
   cDstImageData.AllocBuffer( un32OutDataBytes );
   UInt8* pSrcBuffer = cImageData.GetBufferPtr();
   UInt8* pDstBuffer = cDstImageData.GetBufferPtr();
   UInt32 un32SrcDataOffset = 0, un32DstDataOffset = 0;
   for ( UInt32 un32Line = 0; un32Line < un32OutLinesPerBlock; un32Line++ ){
    memcpy( pDstBuffer + un32DstDataOffset, pSrcBuffer + un32SrcDataOffset, un32BytesPerRow );
    un32DstDataOffset += un32BytesPerRow;
    un32SrcDataOffset += un32BytesPerRow + un32DummyBytesPerLine;
   }
  } else {
   UInt8* pSrcBuffer = cImageData.GetBufferPtr();
   cDstImageData.AppendBuffer( pSrcBuffer, un32OutDataBytes );
  }
  if ( un32RemainingBytes > 0 ){
   UInt32 un32Offset = un32DataBytes - un32RemainingBytes;
   cOutRemainingData.AppendBuffer( cImageData.GetBufferPtr() + un32Offset, un32RemainingBytes );
  }
  cImageData.Attach( cDstImageData );
  return true;
 } catch( const std::bad_alloc& ){
  return false;
 }
}
CESCI2ScannedImage::CESCI2ScannedImage()
{
 m_nDummyBytesPerLine = 0;
 m_nStoreBufferSize = 0;
}
CESCI2ScannedImage::~CESCI2ScannedImage()
{
}
void CESCI2ScannedImage::DeleteInstance()
{
 delete this;
}
ESNumber CESCI2ScannedImage::GetStoreBufferSize()
{
 return m_nStoreBufferSize;
}
void CESCI2ScannedImage::SetStoreBufferSize(ESNumber nBufferSize)
{
 m_nStoreBufferSize = nBufferSize;
}
ESNumber CESCI2ScannedImage::GetDummyBytesPerLine()
{
 return m_nDummyBytesPerLine;
}
void CESCI2ScannedImage::SetDummyBytesPerLine( ESNumber nDummyBytesPerLine )
{
 m_nDummyBytesPerLine = nDummyBytesPerLine;
}
void CESCI2ScannedImage::CloseWithWidth( ESNumber nWidth, ESNumber nHeight )
{
 if ( GetImageFormat() == kESImageFormatRaw ){
  if ( !m_cRemainingData.IsEmpty() ){
   CESHeapBuffer cImageData;
   cImageData.Attach(m_cRemainingData);
   UInt32 un32Rows = 0;
   GetRowAlignedData( cImageData,
        m_nDummyBytesPerLine,
        m_nBytesPerRow,
        m_nWidth,
        un32Rows,
        m_cRemainingData );
   CESScannedImage::WriteData( cImageData );
  }
 } else if ( GetImageFormat() == kESImageFormatJPEG ) {
  if ( !m_cJpegTempBuf.IsEmpty() ){
   CESScannedImage::WriteData( m_cJpegTempBuf );
   m_cJpegTempBuf.FreeBuffer();
  }
 }
 CESScannedImage::CloseWithWidth(nWidth, nHeight);
}
#define JPEG_MIN_CHUNKSIZE 2048
ESErrorCode CESCI2ScannedImage::WriteData( CESHeapBuffer& cImageData )
{
 if ( GetImageFormat() == kESImageFormatRaw ){
  if ( GetStoreBufferSize() != 0 && (cImageData.GetLength() + m_cRemainingData.GetLength()) < GetStoreBufferSize() ) {
   m_cRemainingData += cImageData;
   return kESErrorNoError;
  }
  if ( !m_cRemainingData.IsEmpty() ){
   m_cRemainingData.AppendBuffer( cImageData.GetBufferPtr(), cImageData.GetLength() );
   cImageData.Attach( m_cRemainingData );
  }
  UInt32 un32Rows = 0;
  GetRowAlignedData( cImageData,
       m_nDummyBytesPerLine,
       m_nBytesPerRow,
       m_nWidth,
       un32Rows,
       m_cRemainingData );
 } else if ( GetImageFormat() == kESImageFormatJPEG ) {
  if ( !m_cJpegTempBuf.IsEmpty() ){
   m_cJpegTempBuf.AppendBuffer(cImageData.GetBufferPtr(),cImageData.GetLength());
   cImageData.Attach(m_cJpegTempBuf);
  }
  if ( cImageData.GetLength() < JPEG_MIN_CHUNKSIZE || (GetStoreBufferSize() != 0 && cImageData.GetLength() < GetStoreBufferSize() ) ) {
   m_cJpegTempBuf.AppendBuffer(cImageData.GetBufferPtr(),cImageData.GetLength());
   return kESErrorNoError;
  }
 }
 return CESScannedImage::WriteData( cImageData );
}
bool CESCI2ScannedImage::IsProgressAvailable()
{
 if ( m_eImageFormat == kESImageFormatJPEG ){
  return false;
 }
 return true;
}
