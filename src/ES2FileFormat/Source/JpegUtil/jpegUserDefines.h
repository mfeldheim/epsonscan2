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
//  jpegUserDefines.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#define HAVE_BOOLEAN 
typedef int boolean;
#include "jpeglib.h"
#include <setjmp.h>
struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr * my_error_ptr;
METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
 my_error_ptr myerr = (my_error_ptr) cinfo->err;
 char buffer[JMSG_LENGTH_MAX];
 (*cinfo->err->format_message) (cinfo, buffer);
#ifdef WIN32
 ES_Error_Log(NULL,ES_STRING("Jpeg encode error [%s]"),ES_CMN_FUNCS::STRING::MBStringToUnicode(buffer).c_str());
#else
 ES_Error_Log(NULL,ES_STRING("Jpeg encode error [%s]"),buffer);
#endif
 longjmp(myerr->setjmp_buffer,1);
}
LOCAL(struct jpeg_error_mgr *) jpeg_custom_error (struct my_error_mgr * err)
{
 jpeg_error_mgr* pRet = jpeg_std_error(&(err->pub));
 err->pub.error_exit = my_error_exit;
 return pRet;
}
