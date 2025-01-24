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
//  defines.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef defines_h
#define defines_h 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef __cplusplus
extern "C"
{
#endif
#define MM_PER_INCH 25.4
#ifndef __cplusplus
typedef enum {
  false = 0,
  true
} bool;
#endif
#include <stdlib.h>
#define _assert(type,condition) \
  if (!(condition)) \
  { \
    exit (EXIT_FAILURE); \
  }
#define require(condition) _assert ("require", condition)
#define promise(condition) _assert ("promise", condition)
#include <alloca.h>
#include <stdlib.h>
#define t_alloca(sz,t) ((t *) alloca ((sz) * sizeof (t)))
#define t_calloc(sz,t) ((t *) calloc ((sz) , sizeof (t)))
#define t_malloc(sz,t) ((t *) malloc ((sz) * sizeof (t)))
#define t_realloc(p,sz,t) ((t *) realloc ((p), (sz) * sizeof (t)))
#define num_of(p) (sizeof (p) / sizeof (*p))
#define delete(p) do { if (p) free (p); p = 0; } while (0)
#define const_delete(p,t) do { if (p) free ((t) p); p = 0; } while (0)
#ifdef __unix
#define PATH_SEP_STR ":"
#define PATH_SEP PATH_SEP_STR[0]
#define FILE_SEP_STR "/"
#define FILE_SEP FILE_SEP_STR[0]
#else
#define PATH_SEP_STR ";"
#define PATH_SEP PATH_SEP_STR[0]
#define FILE_SEP_STR "\\"
#define FILE_SEP FILE_SEP_STR[0]
#endif
  typedef unsigned char byte;
#ifdef __cplusplus
}
#endif
#endif
