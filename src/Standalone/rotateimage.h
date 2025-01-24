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
//  rotateimage.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef ROTATEIMAGE_H
#define ROTATEIMAGE_H 
#include <QImage>
#include "supervisor.h"
class RotateImage
{
public:
    RotateImage(ColorType type);
    void Rotate(std::string image_path, int angle, ImageFormat format, bool multiTiffEnabled, int OFDEnabled);
private:
    ColorType m_type;
};
#endif
