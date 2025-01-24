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
//  version.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef sane_version_hpp_
#define sane_version_hpp_ 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#define PACKAGE_STRING 1
#define SANE_MAJOR 1
#define SANE_MINOR 0
extern "C" {
#include "epsonsane.h"
}
#if !((SANE_MAJOR == SANE_CURRENT_MAJOR) && (SANE_MINOR == 0))
#error "SANE installation violates versioning portability constraints."
#endif
#define BACKEND_MAJOR 1
#if (BACKEND_MAJOR != SANE_CURRENT_MAJOR)
#error "Backend assumptions do not match current SANE C API version."
#endif
#if (0 > BACKEND_MAJOR || 255 < BACKEND_MAJOR)
#error "BACKEND_MAJOR value out of range."
#endif
#define BACKEND_MINOR 1
#if (0 > BACKEND_MINOR || 255 < BACKEND_MINOR)
#error "BACKEND_MINOR value out of range."
#endif
#define BACKEND_BUILD 0
#if (0 > BACKEND_BUILD || 65535 < BACKEND_BUILD)
#error "BACKEND_BUILD value out of range."
#endif
#define BACKEND_SOURCE PACKAGE_STRING
#ifndef PACKAGE_STRING
#error "PACKAGE_STRING is not defined at this point."
#endif
#endif
