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
//  ofdplugin.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <stdio.h>
#include <stdint.h>
typedef struct
{
    int32_t width;
    int32_t height;
    int32_t samplesPerPixel;
    int32_t bitsPerSample;
    uint8_t* imageData;
    uint32_t resolution;
    int32_t bytesPerRow;
}OfdImage;
#define OFD_OPTION_MAX_PATH 256
typedef struct
{
    int8_t targetFile[OFD_OPTION_MAX_PATH + 1];
    int8_t tempPDFFile[OFD_OPTION_MAX_PATH + 1];
}OfdOption;
typedef enum : int32_t
{
    kOfdErrorNone = 0,
    kOfdErrorGeneric = 1
} OfdError;
class IOfdPlugin
{
    public:
    virtual OfdError Initialize(OfdOption* option) = 0;
    virtual OfdError Add( OfdImage* image) = 0;
    virtual OfdError Fin() = 0;
};
#if __cplusplus
extern "C" {
#endif
OfdError OFDPluginCreate(IOfdPlugin** plugin);
OfdError OFDPluginFree(IOfdPlugin* plugin);
typedef OfdError (*OFDPluginCreatePtr)(IOfdPlugin** plugin);
typedef OfdError (*OFDPluginFreePtr)(IOfdPlugin* plugin);
#ifdef __cplusplus
}
#endif
