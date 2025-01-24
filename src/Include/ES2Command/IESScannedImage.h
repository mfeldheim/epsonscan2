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
//  IESScannedImage.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../es2CommnoType.h"
#include "../IESBuffer.h"
#include "ESCommandProperties.h"
typedef enum {
    kESSurfaceTypeFrontSide = 0,
    kESSurfaceTypeBackSide = 1,
} ENUM_ES_SURFACE_TYPE;
typedef enum {
    kESDocumentTypeStandard = 0,
    kESDocumentTypeCarrierSheet = 1,
} ENUM_ES_DOCUMENT_TYPE;
typedef enum {
    kESDigitalICEImageTypeNone = 0,
    kESDigitalICEImageTypeTransparent = 1,
    kESDigitalICEImageTypeTransparentIR = 2,
    kESDigitalICEImageTypeFlatbedLamp1 = 3,
    kESDigitalICEImageTypeFlatbedLamp2 = 4,
} ENUM_ES_DIGITAL_ICE_IMAGE_TYPE;
typedef enum {
    kESStorageTypeFile = 0,
    kESStorageTypeNone = 1,
} ENUM_ES_STORAGE_TYPE;
class IESScannedImage;
class IESScannedImageDelegate
{
public:
 virtual void CALLBACK ScannedImageDidBeginReceiving( IESScannedImage* pScannedImage ) = 0;
 virtual void CALLBACK ScannedImageDidEndReceiving( IESScannedImage* pScannedImage ) = 0;
 virtual void CALLBACK ScannedImageDidAbortReceiving(IESScannedImage* pScannedImage) = 0;
 virtual void CALLBACK ScannedImageDidReceiveImageData( IESScannedImage* pScannedImage, ES_CMN_FUNCS::BUFFER::IESBuffer* pDidReceiveImageData ) = 0;
};
class IESScannedImage {
public:
 virtual void DeleteInstance() = 0;
 virtual void RelegationOwner() = 0;
 virtual bool IsRelegationOwner() = 0;
 virtual ESErrorCode SetDelegate( IESScannedImageDelegate* pDelegate ) = 0;
 virtual void Open() = 0;
 virtual void Close() = 0;
 virtual void CloseWithWidth( ESNumber nWidth, ESNumber nHeight ) = 0;
 virtual bool IsClosed() = 0;
 virtual void Abort() = 0;
 virtual void SeekToOffset( UInt32 un32Offset ) = 0;
 virtual void ReadDataOfLength( UInt32 un32Length, ES_CMN_FUNCS::BUFFER::IESBuffer& cReadImageData ) = 0;
 virtual void ReadDataToEnd( ES_CMN_FUNCS::BUFFER::IESBuffer& cReadImageData ) = 0;
 virtual UInt32 GetSerialNumber() = 0;
 virtual UInt32 GetPaperSerialNumber() = 0;
 virtual ENUM_ES_SURFACE_TYPE GetSurfaceType() = 0;
 virtual ENUM_ES_DOCUMENT_TYPE GetDocumentType() =0;
 virtual bool IsProgressAvailable() = 0;
 virtual ESNumber GetProgressInPercent() = 0;
 virtual bool IsAutoCropped() = 0;
 virtual bool IsUpsideDown() = 0;
 virtual bool IsDoubleFeed() = 0;
 virtual bool IsAutoDetectMonoPage() = 0;
 virtual bool IsAutoDetectBlankPage() = 0;
 virtual ESImageFormat GetImageFormat() = 0;
 virtual ENUM_ES_DIGITAL_ICE_IMAGE_TYPE GetDigitalICEImageType() = 0;
 virtual ENUM_ES_STORAGE_TYPE GetStorageType() = 0;
 virtual void SetStorageType( ENUM_ES_STORAGE_TYPE eStorageType ) = 0;
 virtual ST_ES_SIZE_UN32 GetExpectedImageSize() = 0;
 virtual ST_ES_SIZE_UN32 GetImageSize() = 0;
 virtual ESNumber GetWidth() = 0;
 virtual ESNumber GetHeight() = 0;
 virtual ESNumber GetBitsPerPixel() = 0;
 virtual ESNumber GetSamplesPerPixel() = 0;
 virtual ESNumber GetBitsPerSample() = 0;
 virtual ESNumber GetBytesPerRow() = 0;
};
