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
//  FKWriterKeys.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
typedef ESDictionary FKWriterInitDict;
typedef ESDictionary FKWriterInitializeDestDict;
typedef ESDictionary FKWriterPageOpenDict;
typedef ESDictionary FKWriterPageCloseDict;
typedef ESDictionary FKWriterFinalizeDestDict;
STATIC_CONST_KEY kFKWriterInitOptionPDFLibPathKey = ES_STRING("pdfLibPath");
STATIC_CONST_KEY kFKWriterInitOptionPDFEncryptionModulePathKey = ES_STRING("pdfEncryptionPath");
STATIC_CONST_KEY kFKWriterInitOptionOCRComponentModulePathKey = ES_STRING("pdfOCRComponentPath");
STATIC_CONST_KEY kFKWriterPageOpenOptionJpegQualityKey = ES_STRING("quality");
STATIC_CONST_KEY kFKWriterPageOpenOptionJpegProgressiveModeKey = ES_STRING("progressiveMode");
STATIC_CONST_KEY kFKWriterPageOpenOptionJpegICCProfilePathKey = ES_STRING("iccProfilePath");
STATIC_CONST_KEY kFKWriterPageOpenOptionPDFTopMarginKey = ES_STRING("topMarginInch");
STATIC_CONST_KEY kFKWriterPageOpenOptionPDFLeftMarginKey = ES_STRING("leftMarginInch");
STATIC_CONST_KEY kFKWriterPageOpenOptionPDFPaperWidthKey = ES_STRING("paperWidthInch");
STATIC_CONST_KEY kFKWriterPageOpenOptionPDFPaperHeightKey = ES_STRING("paperHeightInch");
STATIC_CONST_KEY kFKWriterPageOpenOptionPDFRotationKey = ES_STRING("rotation");
typedef enum :uint32_t
{
    kFKWriterPageOpenOptionPDFRotation0 = 0,
    kFKWriterPageOpenOptionPDFRotation90 = 90,
    kFKWriterPageOpenOptionPDFRotation180 = 180,
    kFKWriterPageOpenOptionPDFRotation270 = 270,
}FKWriterPageOpenOptionPDFRotation;
STATIC_CONST_KEY kFKWriterInitializeDestOptionPDFA = ES_STRING("isPDFA");
STATIC_CONST_KEY kFKWriterInitializeDestOptionUserPasseword = ES_STRING("userPassword");
STATIC_CONST_KEY kFKWriterInitializeDestOptionOwnerPasseword = ES_STRING("ownerPassword");
STATIC_CONST_KEY kFKWriterInitializeDestOptionAllowsEditing = ES_STRING("allowsEditing");
STATIC_CONST_KEY kFKWriterInitializeDestOptionAllowsPrinting = ES_STRING("allowsPrinting");
STATIC_CONST_KEY kFKWriterInitializeDestOptionCompression = ES_STRING("compression");
typedef enum:uint8_t
{
   kFKWriterInitializeDestOptionCompressionStd,
   kFKWriterInitializeDestOptionCompressionHigh,
}FKWriterInitializeDestOptionCompression;
STATIC_CONST_KEY kFKWriterInitializeDestOptionSearchablePDFEnabled = ES_STRING("searchablePDFEnabled");
STATIC_CONST_KEY kFKWriterInitializeDestOptionSearchablePDFLang = ES_STRING("searchablePDFLang");
STATIC_CONST_KEY kFKWriterInitializeDestOptionPDFICCProfilePathKey = ES_STRING("iccProfilePath");
STATIC_CONST_KEY kFKWriterInitializeDestOptionPDFICCProfileChannelsKey = ES_STRING("iccProfileChannels");
STATIC_CONST_KEY kFKWriterInitializeDestOptionTiffDataTypeKey = ES_STRING("dataType");
typedef enum : uint8_t
{
    kFKWriterInitializeDestOptionTiffDataTypeRaw,
    kFKWriterInitializeDestOptionTiffDataTypeEncoded,
}FKWriterInitializeDestOptionTiffDataType;
STATIC_CONST_KEY kFKWriterPageOpenOptionTiffAppendModeKey = ES_STRING("appendMode");
STATIC_CONST_KEY kFKWriterPageOpenOptionTiffICCProfilePathKey = ES_STRING("iccProfilePath");
STATIC_CONST_KEY kFKWriterPageOpenOptionTiffCompressionKey = ES_STRING("compression");
typedef enum : uint8_t
{
    kFKWriterPageOpenOptionTiffCompressionNone,
    kFKWriterPageOpenOptionTiffCompressionCCITG4,
    kFKWriterPageOpenOptionTiffCompressionLzw,
    kFKWriterPageOpenOptionTiffCompressionJpeg
}FKWriterPageOpenOptionTiffCompression;
static LPCTSTR kFKWriterPageOpenIsBmpTopDown = ES_STRING("isBmpTopDown");
