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
//  FKBmpReader.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "FKBmpReader.h"
#include "../BmpUtil/FKBmpUtil.h"
#include "ESImageInfo.h"
CFKBmpReader::CFKBmpReader()
{
 m_bStarted = FALSE;
 memset(&m_stBmInfo, 0, sizeof(m_stBmInfo));
 m_dataPosition = 0;
 m_MaxLoadLine=0;
 m_currentLine=0;
}
CFKBmpReader::~CFKBmpReader()
{
}
BOOL CFKBmpReader::GetImageInfo(ESImageInfo &outImageInfo)
{
 if (!m_bStarted){
  return FALSE;
 }
 outImageInfo.clear();
 outImageInfo[ES_IMAGE_INFO::kESImageInfoWidthKey] = m_stBmInfo.biWidth;
 outImageInfo[ES_IMAGE_INFO::kESImageInfoHeightKey] = std::abs(m_stBmInfo.biHeight);
 switch (m_stBmInfo.biBitCount){
 case 1:
  outImageInfo[ES_IMAGE_INFO::kESImageInfoSamplesPerPixelKey] = 1;
  outImageInfo[ES_IMAGE_INFO::kESImageInfoBitsPerSampleKey] = 1;
 case 8:
  outImageInfo[ES_IMAGE_INFO::kESImageInfoSamplesPerPixelKey] = 1;
  outImageInfo[ES_IMAGE_INFO::kESImageInfoBitsPerSampleKey] = 8;
  break;
 case 24:
  outImageInfo[ES_IMAGE_INFO::kESImageInfoSamplesPerPixelKey] = 3;
  outImageInfo[ES_IMAGE_INFO::kESImageInfoBitsPerSampleKey] = 8;
  break;
 default:
  return FALSE;
 }
 return TRUE;
}
BOOL CFKBmpReader::OpenReaderWithOptionAsJson(ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
 if(pszOptionAsJson){
  ESDictionary dictParam;
  ES_CMN_FUNCS::JSON::JSONtoDictionary(pszOptionAsJson,dictParam);
  m_MaxLoadLine = SAFE_ANY_VALUE_FROM_DICT(dictParam,kFKReaderReadOptionMaximumLines,ESNumber,0);
 }
 m_piFkDestination->NotifyDidBeginReceivingForImageInfo(pszOptionAsJson);
 m_dataPosition = 0;
 m_currentLine = 0;
 m_strImageInfoJson.clear();
 return TRUE;
}
BOOL CFKBmpReader::CloseReaderWithOptionAsJson(ES_CHAR_CPTR pszOptionAsJson, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
 m_bStarted = FALSE;
 if (m_currentLine == (uint32_t)std::abs(m_stBmInfo.biHeight) && m_currentLine > 0){
  m_piFkDestination->NotifyDidEndReceivingForImageInfo(pszOptionAsJson);
  return TRUE;
 }
 else{
  eError = kFKUnknownError;
  return FALSE;
 }
}
BOOL CFKBmpReader::Notify(ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ENUM_FK_ERROR_CODE& eError)
{
 if (m_piFkDestination->GetFKDestinationType() == kFKDestinationTypeData) {
  (m_piFkDestination->GetSource()).AppendBuffer(cData.GetBufferPtr(), cData.GetLength());
 }
 else if (m_piFkDestination->GetFKDestinationType() == kFKDestinationTypeEmpty) {
 }
 else{
  eError = kFKUnsupportedDestination;
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, L"unsupported destination");
 }
 try
 {
  if (m_strImageInfoJson.length() == 0){
   ESImageInfo ImageInfo;
   GetImageInfo(ImageInfo);
   ES_IMAGE_INFO::GetImageInfoAsJson(m_strImageInfoJson,ImageInfo);
  }
  m_piFkDestination->NotifyReceiveImageData(cData, (ES_CHAR_CPTR)m_strImageInfoJson.c_str());
 }
 catch (const std::bad_alloc& e){
  UNREFERENCED_PARAMETER(e);
  eError = kFKMemError;
 }
BAIL:
 return eError == kFKNoError;
}
void CFKBmpReader::AppendSourceFromPath(ESString& strPath, ENUM_FK_ERROR_CODE& eError)
{
 FILE* fpBmp = NULL;
 eError = kFKNoError;
 try{
  errno_t err = _wfopen_s(&fpBmp, strPath.c_str(), L"rb");
  ES_ErrorBailWithAction(err == 0, BAIL, this, eError = kFKFileCreateError, L"cannot open file");
  BITMAPFILEHEADER FH;
  memset(&FH, 0, sizeof(FH));
  fread(&FH, sizeof(FH), 1, fpBmp);
  ES_ErrorBailWithAction((FH.bfType == 'MB'), BAIL, this, eError = kFKParameterError, L"Invlid BMP file");
  ES_ErrorBailWithAction(fread(&m_stBmInfo, sizeof(m_stBmInfo), 1, fpBmp), BAIL,
   this, eError = kFKUnknownError, L"read bm header fail");
  ES_ErrorBailWithAction((m_stBmInfo.biWidth > 0 && m_stBmInfo.biHeight != 0), BAIL,
   this, eError = kFKUnknownError, L"bm header field invalid or not supported");
  ES_ErrorBailWithAction((m_stBmInfo.biBitCount == 1 || m_stBmInfo.biBitCount == 8 || m_stBmInfo.biBitCount == 24), BAIL,
   this, eError = kFKUnknownError, L"Specified BitCount is not supported");
  uint32_t nHeaderSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * CFKBmpUtil::GetPaletteEntryCount(m_stBmInfo);
  uint32_t stride = CFKBmpUtil::GetStride(m_stBmInfo);
  uint32_t height = std::abs(m_stBmInfo.biHeight);
  if(m_MaxLoadLine != 0){
   m_MaxLoadLine = min(height,m_MaxLoadLine);
  }else{
   m_MaxLoadLine = height;
  }
  BOOL isTopDown = m_stBmInfo.biHeight < 0;
  ES_CMN_FUNCS::BUFFER::CESHeapBuffer cBufToNotify;
  cBufToNotify.GetStreamBuffer(stride*m_MaxLoadLine,stride*m_MaxLoadLine);
  ES_ErrorBailWithAction(cBufToNotify.GetBufferPtr() != NULL,BAIL,this, eError = kFKMemError, L"stream buffe allocate error");
  m_bStarted = TRUE;
  if (m_stBmInfo.biBitCount == 24){
   std::vector<uint8_t> vBuf(stride);
   for (uint32_t y = 0; y < height; y++){
    int err = 0;
    if (isTopDown){
     err = _fseeki64(fpBmp, nHeaderSize + stride * y, SEEK_SET);
    }
    else{
     err = _fseeki64(fpBmp, nHeaderSize + stride * (height - y - 1), SEEK_SET);
    }
    ES_ErrorBailWithAction(err == 0, BAIL,
     this, eError = kFKParameterError, L"bmp read error");
    ES_ErrorBailWithAction(fread(&vBuf[0], stride, 1, fpBmp), BAIL,
     this, eError = kFKParameterError, L"bmp read error");
    ES_CMN_FUNCS::BUFFER::CESHeapBuffer cData;
    cData.AllocBuffer(m_stBmInfo.biWidth * 3);
    ES_ErrorBailWithAction(cData.GetBufferPtr() != NULL,BAIL,this, eError = kFKMemError, L"AllocBuffer error");
    CFKBmpUtil::SwapCopyAsBGRBytes(&vBuf[0], cData.GetBufferPtr(), m_stBmInfo.biWidth);
    cBufToNotify.AppendBuffer(cData.GetBufferPtr(),cData.GetLength());
    if((y == m_MaxLoadLine -1) ||(y == height -1)){
     cBufToNotify.ReleaseStreamBuffer();
     ES_ErrorBailWithAction(Notify(cBufToNotify, eError), BAIL, this, eError = kFKUnsupportedDestination, L"unsupported destination");
     if(y != height -1){
      uint32_t nextTarget = min(y + m_MaxLoadLine,height);
      uint32_t streamSize = nextTarget - y;
      cBufToNotify.GetStreamBuffer(stride*streamSize,stride*streamSize);
      ES_ErrorBailWithAction(cBufToNotify.GetBufferPtr() != NULL,BAIL,this, eError = kFKMemError, L"stream buffer allocate error");
      m_MaxLoadLine = nextTarget;
     }
    }
   }
  }
  else{
   std::vector<uint8_t> vBuf(stride);
   for (uint32_t y = 0; y < height; y++){
    int err = 0;
    if (isTopDown){
     err = _fseeki64(fpBmp, nHeaderSize + stride * y, SEEK_SET);
    }
    else{
     err = _fseeki64(fpBmp, nHeaderSize + stride * (height - y - 1), SEEK_SET);
    }
    ES_ErrorBailWithAction(err == 0, BAIL, this, eError = kFKParameterError, L"bmp read seek error");
    ES_ErrorBailWithAction(fread(&vBuf[0], 1, stride, fpBmp), BAIL,
     this, eError = kFKParameterError, L"bmp read error");
    ES_CMN_FUNCS::BUFFER::CESHeapBuffer cData;
    int lLineByte = ((m_stBmInfo.biWidth * m_stBmInfo.biBitCount + 7) / 8);
    ES_ErrorBailWithAction(cData.AllocBuffer(lLineByte), BAIL, this, eError = kFKParameterError, L"bmp read error");
    memcpy(cData.GetBufferPtr(), &vBuf[0], lLineByte);
    cBufToNotify.AppendBuffer(cData.GetBufferPtr(),cData.GetLength());
    if((y == m_MaxLoadLine -1) ||(y == height -1)){
     cBufToNotify.ReleaseStreamBuffer();
     ES_ErrorBailWithAction(Notify(cBufToNotify, eError), BAIL, this, eError = kFKUnsupportedDestination, L"unsupported destination");
     if(y != height -1){
      uint32_t nextTarget = min(y + m_MaxLoadLine,height);
      uint32_t streamSize = nextTarget - y;
      cBufToNotify.GetStreamBuffer(streamSize*stride,streamSize*stride);
      ES_ErrorBailWithAction(cBufToNotify.GetBufferPtr() != NULL,BAIL,this, eError = kFKMemError, L"stream buffer allocate error");
      m_MaxLoadLine = nextTarget;
     }
    }
   }
  }
  m_currentLine = height;
 }
 catch (const std::bad_alloc& e){
  UNREFERENCED_PARAMETER(e);
  eError = kFKUnknownError;
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, L"unknown error");
 }
BAIL:;
 if (fpBmp){
  fclose(fpBmp);
 }
}
BOOL CFKBmpReader::ReadHeaderFromData(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer, ENUM_FK_ERROR_CODE& eError)
{
 try{
  ES_ErrorBailWithAction((cBuffer.GetLength() > sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)),
   BAIL, this, eError = kFKMemError, L"invalid data length");
  BITMAPFILEHEADER* pFH = (BITMAPFILEHEADER*)cBuffer.GetBufferPtr();
  BITMAPINFOHEADER* pBmi = (BITMAPINFOHEADER*)(cBuffer.GetBufferPtr() + sizeof(BITMAPFILEHEADER));
  ES_ErrorBailWithAction((pFH->bfType == 'MB'), BAIL, this, eError = kFKParameterError, L"Invalid BMP file");
  ES_ErrorBailWithAction((pBmi->biWidth > 0 && pBmi->biHeight != 0), BAIL,
   this, eError = kFKUnknownError, L"bm header field invalid or not supported");
  ES_ErrorBailWithAction((pBmi->biBitCount == 1 || pBmi->biBitCount == 8 || pBmi->biBitCount == 24), BAIL,
   this, eError = kFKUnknownError, L"bm header field invalid or not supported");
  uint32_t nHeaderSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * CFKBmpUtil::GetPaletteEntryCount(*pBmi);
  ES_ErrorBailWithAction((cBuffer.GetLength() > nHeaderSize), BAIL,
   this, eError = kFKUnknownError, L"bm header field invalid or not supported");
  m_stBmInfo = *pBmi;
  m_dataPosition += nHeaderSize;
  return TRUE;
 }
 catch (const std::bad_alloc& e){
  UNREFERENCED_PARAMETER(e);
  eError = kFKMemError;
 }
BAIL:
 return FALSE;
}
void CFKBmpReader::StorePendingBuffer(ES_CMN_FUNCS::BUFFER::IESBuffer* pInputBuf, uint32_t bufferPosition)
{
 if (pInputBuf == NULL){
  return;
 }
 if (bufferPosition < pInputBuf->GetLength()){
  ES_CMN_FUNCS::BUFFER::CESHeapBuffer cTemp;
  cTemp.AppendBuffer(pInputBuf->GetBufferPtr() + bufferPosition, pInputBuf->GetLength() - bufferPosition);
  m_pendingBuffer.FreeBuffer();
  m_pendingBuffer.Attach(cTemp);
 }
 else{
  m_pendingBuffer.FreeBuffer();
 }
}
ES_CMN_FUNCS::BUFFER::IESBuffer* CFKBmpReader::GetInputBuffer(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer)
{
 ES_CMN_FUNCS::BUFFER::IESBuffer* pInputBuf = &cBuffer;
 if (m_stBmInfo.biHeight < 0){
  if (!m_pendingBuffer.IsEmpty()){
   m_pendingBuffer.AppendBuffer(cBuffer.GetBufferPtr(), cBuffer.GetLength());
   pInputBuf = &m_pendingBuffer;
  }
  else{
   pInputBuf = &cBuffer;
  }
 }
 return pInputBuf;
}
void CFKBmpReader::AppendSourceFromData(ES_CMN_FUNCS::BUFFER::IESBuffer& cBuffer, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
 try{
  uint32_t bufferPosition = 0;
  if (m_dataPosition == 0){
   if (ReadHeaderFromData(cBuffer, eError)){
    bufferPosition = (uint32_t)m_dataPosition;
   }
   else{
    goto BAIL;
   }
  }
  else{
   ES_ErrorBailWithAction((m_stBmInfo.biWidth > 0 && m_stBmInfo.biBitCount > 0),
    BAIL, this, eError = kFKInconsistentError, L"invalid data");
  }
  if (m_currentLine == (uint32_t)std::abs(m_stBmInfo.biHeight)){
   return;
  }
  assert(cBuffer.GetLength() > 1500);
  m_bStarted = TRUE;
  uint32_t stride = CFKBmpUtil::GetStride(m_stBmInfo);
  uint32_t height = std::abs(m_stBmInfo.biHeight);
  BOOL isTopDown = m_stBmInfo.biHeight < 0;
  uint32_t nHeaderSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * CFKBmpUtil::GetPaletteEntryCount(m_stBmInfo);
  if(m_LoadedDataToNotify.GetLength() ==0){
   uint32_t maxHeight = height;
   if(m_MaxLoadLine != 0){
    maxHeight = min(height,m_MaxLoadLine);
   }
   m_LoadedDataToNotify.GetStreamBuffer(stride*maxHeight,stride*maxHeight);
  }
  ES_ErrorBailWithAction((((nHeaderSize + stride * height) <= cBuffer.GetLength()) || isTopDown), BAIL,
   this, eError = kFKUnknownError, L"source size is invalid. Caller must input full size Bitmap data for Bottom Up bitmap format.");
  ES_CMN_FUNCS::BUFFER::IESBuffer* pInputBuf = GetInputBuffer(cBuffer);
  int step = 0;
  uint8_t* pSrcImage = NULL;
  if (isTopDown){
   step = stride;
   pSrcImage = pInputBuf->GetBufferPtr() + bufferPosition;
  }
  else{
   step = -(int)stride;
   pSrcImage = cBuffer.GetBufferPtr() + nHeaderSize + stride * (height - m_currentLine - 1);
  }
  int lLineByte = ((m_stBmInfo.biWidth * m_stBmInfo.biBitCount + 7) / 8);
  int bitCount = m_stBmInfo.biBitCount;
  ES_CMN_FUNCS::BUFFER::CESHeapBuffer cData;
  while (pInputBuf->GetLength() - bufferPosition >= stride && height > m_currentLine){
   if (cData.GetLength() != lLineByte){
    ES_ErrorBailWithAction(cData.AllocBuffer(lLineByte), BAIL, this, eError = kFKMemError, L"bmp read error");
   }
   if (bitCount == 24){
    CFKBmpUtil::SwapCopyAsBGRBytes(pSrcImage, cData.GetBufferPtr(), m_stBmInfo.biWidth);
   }
   else{
    memcpy(cData.GetBufferPtr(), pSrcImage, lLineByte);
   }
   m_LoadedDataToNotify.AppendBuffer(cData.GetBufferPtr(),cData.GetLength());
   if((m_currentLine == m_MaxLoadLine -1) ||(m_currentLine == height -1)){
    m_LoadedDataToNotify.ReleaseStreamBuffer();
    ES_ErrorBailWithAction(Notify(m_LoadedDataToNotify, eError), BAIL, this, eError = kFKUnsupportedDestination, L"unsupported destination");
    if(m_currentLine != height -1){
     uint32_t nextTarget = min(m_currentLine + m_MaxLoadLine,height);
     uint32_t streamSize = nextTarget - m_currentLine;
     m_LoadedDataToNotify.GetStreamBuffer(streamSize*stride,streamSize*stride);
    }
   }
   pSrcImage += step;
   bufferPosition += stride;
   m_currentLine++;
  }
  if (isTopDown){
   StorePendingBuffer(pInputBuf, bufferPosition);
  }
 }
 catch (const std::bad_alloc& e){
  UNREFERENCED_PARAMETER(e);
  eError = kFKMemError;
  ES_Bail(BAIL, ENUM_LOG_LEVEL::LogLevelError, this, L"unknown error");
 }
BAIL:;
}
BOOL CFKBmpReader::AppendSourceToReader(IFKSource* pcSource, ENUM_FK_ERROR_CODE& eError)
{
 eError = kFKNoError;
 if (pcSource->GetFKSourceType() == kFKSourceTypePath){
  ESString strPath = (LPWSTR)(((pcSource->GetSource())).GetBufferPtr());
  AppendSourceFromPath(strPath, eError);
 }
 else if (pcSource->GetFKSourceType() == kFKSourceTypeData){
  AppendSourceFromData(pcSource->GetSource(), eError);
 }
 else{
  ES_ErrorBailWithAction(pcSource != NULL, BAIL, this, eError = kFKUnsupportedSource, L"unsupported source");
 }
BAIL:;
 return eError == kFKNoError;
}
