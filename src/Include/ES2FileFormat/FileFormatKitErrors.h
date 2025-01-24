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
//  FileFormatKitErrors.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <stdint.h>
typedef enum : uint32_t {
 kFKNoError = 0,
 kFKUnsupportedDestination = 1000,
 kFKUnsupportedSource = 1001,
 kFKInconsistentError = 3001,
 kFKParameterError = 3002,
 kFKUnknownError = 3003,
 kFKMemError = 3004,
 kFKTiffSetFieldError = 3101,
 kFKTiffGetFieldError = 3102,
 kFKTiffWriteScanLineError = 3103,
 kFKTiffReadScanLineError = 3104,
 kFKPDFInvalidArgError = 3201,
 kFKPDFWriteError = 3202,
 kFKPDFMutexError = 3203,
 kFKPDFMemError = 3204,
 kFKPDFOCRError = 3205,
 kFKPDFConvertError = 3206,
 kFKJpegStartCompressError = 3301,
 kFKJpegWriteScanlineError = 3302,
 kFKJpegFinishCompressError = 3303,
 kFKJpegStartDecompressError = 3401,
 kFKJpegReadHaderError = 3402,
 kFKJpegScanError = 3403,
 kFKJpegFinishDecompressError = 3404,
 kFKFileCreateError = 3501,
 kFKPNGInitializeError = 3601,
 kFKPNGWriteError = 3602,
 kFKBMPWriteError = 3701
}ENUM_FK_ERROR_CODE;
