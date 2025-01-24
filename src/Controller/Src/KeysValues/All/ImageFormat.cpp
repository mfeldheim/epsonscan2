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
//  ImageFormat.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ImageFormat.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void ImageFormat::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void ImageFormat::Reset()
{
 current_ = kSDIImageFormatColorJpegMonoPNM;
}
void ImageFormat::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void ImageFormat::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
    capability.supportLevel = kSDISupportLevelAvailable;
 AddList(capability, kSDIImageFormatRaw);
 AddAllList(capability, kSDIImageFormatRaw);
 AddList(capability, kSDIImageFormatPNM);
 AddAllList(capability, kSDIImageFormatPNM);
 AddList(capability, kSDIImageFormatJPEG);
 AddAllList(capability, kSDIImageFormatJPEG);
 AddList(capability, kSDIImageFormatPNG);
 AddAllList(capability, kSDIImageFormatPNG);
 AddList(capability, kSDIImageFormatTIFF);
 AddAllList(capability, kSDIImageFormatTIFF);
 AddList(capability, kSDIImageFormatColorJpegMonoPNM);
 AddAllList(capability, kSDIImageFormatColorJpegMonoPNM);
}
ESDictionary ImageFormat::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 return dict;
}
}
