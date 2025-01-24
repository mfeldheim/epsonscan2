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
//  epsonsane.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef sane_h
#define sane_h 
#ifdef __cplusplus
extern "C" {
#endif
#define SANE_CURRENT_MAJOR 1
#define SANE_CURRENT_MINOR 0
#define SANE_VERSION_CODE(major,minor,build) \
  ( (((SANE_Word) (major) & 0xff) << 24) \
   | (((SANE_Word) (minor) & 0xff) << 16) \
   | (((SANE_Word) (build) & 0xffff) << 0))
#define SANE_FALSE 0
#define SANE_TRUE 1
typedef unsigned char SANE_Byte;
typedef int SANE_Word;
typedef SANE_Word SANE_Bool;
typedef SANE_Word SANE_Int;
typedef char SANE_Char;
typedef SANE_Char *SANE_String;
typedef const SANE_Char *SANE_String_Const;
typedef void *SANE_Handle;
#define SANE_FIXED_SCALE_SHIFT 16
#define SANE_FIX(v) ((SANE_Word) ((v) * (1 << SANE_FIXED_SCALE_SHIFT)))
#define SANE_UNFIX(v) ((double)(v) / (1 << SANE_FIXED_SCALE_SHIFT))
typedef enum
  {
    SANE_STATUS_GOOD = 0,
    SANE_STATUS_UNSUPPORTED,
    SANE_STATUS_CANCELLED,
    SANE_STATUS_DEVICE_BUSY,
    SANE_STATUS_INVAL,
    SANE_STATUS_EOF,
    SANE_STATUS_JAMMED,
    SANE_STATUS_NO_DOCS,
    SANE_STATUS_COVER_OPEN,
    SANE_STATUS_IO_ERROR,
    SANE_STATUS_NO_MEM,
    SANE_STATUS_ACCESS_DENIED
  }
SANE_Status;
typedef enum
  {
    SANE_TYPE_BOOL = 0,
    SANE_TYPE_INT,
    SANE_TYPE_FIXED,
    SANE_TYPE_STRING,
    SANE_TYPE_BUTTON,
    SANE_TYPE_GROUP
  }
SANE_Value_Type;
typedef enum
  {
    SANE_UNIT_NONE = 0,
    SANE_UNIT_PIXEL,
    SANE_UNIT_BIT,
    SANE_UNIT_MM,
    SANE_UNIT_DPI,
    SANE_UNIT_PERCENT,
    SANE_UNIT_MICROSECOND
  }
SANE_Unit;
typedef struct
  {
    SANE_String_Const name;
    SANE_String_Const vendor;
    SANE_String_Const model;
    SANE_String_Const type;
  }
SANE_Device;
#define SANE_CAP_SOFT_SELECT (1 << 0)
#define SANE_CAP_SOFT_DETECT (1 << 2)
#define SANE_CAP_EMULATED (1 << 3)
#define SANE_CAP_INACTIVE (1 << 5)
#define SANE_CAP_ADVANCED (1 << 6)
#define SANE_INFO_INEXACT (1 << 0)
#define SANE_INFO_RELOAD_OPTIONS (1 << 1)
#define SANE_INFO_RELOAD_PARAMS (1 << 2)
typedef enum
  {
    SANE_CONSTRAINT_NONE = 0,
    SANE_CONSTRAINT_RANGE,
    SANE_CONSTRAINT_WORD_LIST,
    SANE_CONSTRAINT_STRING_LIST
  }
SANE_Constraint_Type;
typedef struct
  {
    SANE_Word min;
    SANE_Word max;
    SANE_Word quant;
  }
SANE_Range;
typedef struct
  {
    SANE_String_Const name;
    SANE_String_Const title;
    SANE_String_Const desc;
    SANE_Value_Type type;
    SANE_Unit unit;
    SANE_Int size;
    SANE_Int cap;
    SANE_Constraint_Type constraint_type;
    union
      {
 const SANE_String_Const *string_list;
 const SANE_Word *word_list;
 const SANE_Range *range;
      }
    constraint;
  }
SANE_Option_Descriptor;
typedef enum
  {
    SANE_ACTION_GET_VALUE = 0,
    SANE_ACTION_SET_VALUE,
    SANE_ACTION_SET_AUTO
  }
SANE_Action;
typedef enum
  {
    SANE_FRAME_GRAY,
    SANE_FRAME_RGB,
    SANE_FRAME_RED,
    SANE_FRAME_GREEN,
    SANE_FRAME_BLUE
  }
SANE_Frame;
typedef struct
  {
    SANE_Frame format;
    SANE_Bool last_frame;
    SANE_Int bytes_per_line;
    SANE_Int pixels_per_line;
    SANE_Int lines;
    SANE_Int depth;
  }
SANE_Parameters;
typedef void (*SANE_Auth_Callback) (SANE_String_Const resource,
        SANE_Char *username,
        SANE_Char *password);
extern SANE_Status sane_init (SANE_Int * version_code,
         SANE_Auth_Callback authorize);
extern void sane_exit (void);
extern SANE_Status sane_get_devices (const SANE_Device *** device_list,
         SANE_Bool local_only);
extern SANE_Status sane_open (SANE_String_Const devicename,
         SANE_Handle * handle);
extern void sane_close (SANE_Handle handle);
extern const SANE_Option_Descriptor *
  sane_get_option_descriptor (SANE_Handle handle, SANE_Int option);
extern SANE_Status sane_control_option (SANE_Handle handle, SANE_Int option,
     SANE_Action action, void *value,
     SANE_Int * info);
extern SANE_Status sane_get_parameters (SANE_Handle handle,
     SANE_Parameters * params);
extern SANE_Status sane_start (SANE_Handle handle);
extern SANE_Status sane_read (SANE_Handle handle, SANE_Byte * data,
         SANE_Int max_length, SANE_Int * length);
extern void sane_cancel (SANE_Handle handle);
extern SANE_Status sane_set_io_mode (SANE_Handle handle,
         SANE_Bool non_blocking);
extern SANE_Status sane_get_select_fd (SANE_Handle handle,
           SANE_Int * fd);
extern SANE_String_Const sane_strstatus (SANE_Status status);
#ifdef __cplusplus
}
#endif
#endif
