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
//  rotateimage.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "rotateimage.h"
#include <QGraphicsScene>
RotateImage::RotateImage(ColorType type)
{
    m_type = type;
}
void RotateImage::Rotate(std::string image_path, int angle, ImageFormat format, bool multiTiffEnabled, int OFDEnabled)
{
    std::string file_format;
    if (format == kSDIImageFormatJPEG)
    {
        file_format = "JPG";
    }else if (format == ImageFormatColorJpegMonoRaw)
    {
        if(m_type == ColorTypeMono1){
            file_format = "PBM";
        }else {
            file_format = "JPG";
        }
    }else if (format == kSDIImageFormatPNM && !multiTiffEnabled)
    {
        file_format = "PPM";
    }else if (format == kSDIImageFormatTIFF)
    {
        file_format = "TIFF";
    }else if (format == kSDIImageFormatPNG)
    {
        file_format = "PNG";
    }else if (format == kSDIImageFormatPNM && multiTiffEnabled)
    {
        file_format = "PPM";
    }else if (format == kSDIImageFormatPNM && OFDEnabled)
    {
        file_format = "OFD";
    }
    QImage srcImg(image_path.c_str());
    QPoint center = srcImg.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(angle);
    QImage dstImg = srcImg.transformed(matrix);
    dstImg.save(QString::fromStdString(image_path), file_format.c_str(), -1);
}
