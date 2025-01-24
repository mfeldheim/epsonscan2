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
//  backend.h -- template and derived ESC/I ESC/I-2 protocol commands

#include "../Include/Config.h"
#ifndef sane_backend_hpp_
#define sane_backend_hpp_ 
extern "C" {
#include "epsonsane.h"
}
#include <cstdio>
#include <boost/preprocessor/cat.hpp>
#include "../Include/Controller/EpsonScan2.h"
extern "C" {
#define API_ENTRY(backend,function) BOOST_PP_CAT(sane_,BOOST_PP_CAT(backend,BOOST_PP_CAT(_,function)))
SANE_Status
API_ENTRY (BACKEND_NAME, init) (SANE_Int *version_code,
                                SANE_Auth_Callback authorize);
void
API_ENTRY (BACKEND_NAME, exit) (void);
SANE_Status
API_ENTRY (BACKEND_NAME, get_devices) (const SANE_Device ***device_list,
                                       SANE_Bool local_only);
SANE_Status
API_ENTRY (BACKEND_NAME, open) (SANE_String_Const device_name,
                                SANE_Handle *handle);
void
API_ENTRY (BACKEND_NAME, close) (SANE_Handle handle);
const SANE_Option_Descriptor *
API_ENTRY (BACKEND_NAME, get_option_descriptor) (SANE_Handle handle,
                                                 SANE_Int index);
SANE_Status
API_ENTRY (BACKEND_NAME, control_option) (SANE_Handle handle, SANE_Int index,
                                          SANE_Action action, void *value,
                                          SANE_Word *info);
SANE_Status
API_ENTRY (BACKEND_NAME, get_parameters) (SANE_Handle handle,
                                          SANE_Parameters *parameters);
SANE_Status
API_ENTRY (BACKEND_NAME, start) (SANE_Handle handle);
SANE_Status
API_ENTRY (BACKEND_NAME, read) (SANE_Handle handle, SANE_Byte *buffer,
                                SANE_Int max_length, SANE_Int *length);
void
API_ENTRY (BACKEND_NAME, cancel) (SANE_Handle handle);
SANE_Status
API_ENTRY (BACKEND_NAME, set_io_mode) (SANE_Handle handle,
                                       SANE_Bool non_blocking);
SANE_Status
API_ENTRY (BACKEND_NAME, get_select_fd) (SANE_Handle handle,
                                         SANE_Int *fdp);
SANE_String_Const
API_ENTRY (BACKEND_NAME, strstatus) (SANE_Status status);
#ifdef BACKEND_CREATE_FORWARDERS
SANE_Status
sane_init (SANE_Int *version_code, SANE_Auth_Callback authorize)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, init) (version_code, authorize);
  return status;
}
void
sane_exit (void)
{
  API_ENTRY (BACKEND_NAME, exit) ();
  return;
}
SANE_Status
sane_get_devices (const SANE_Device ***device_list, SANE_Bool local_only)
{
  SANE_Status status;
  char ch[50] = "ABCDEFGH";
 FILE *fp;
 fp = fopen("/tmp/test.txt","w");
 fwrite(ch,1,6,fp);
 fclose(fp);
  status = API_ENTRY (BACKEND_NAME, get_devices) (device_list, local_only);
  return status;
}
SANE_Status
sane_open (SANE_String_Const device_name, SANE_Handle *handle)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, open) (device_name, handle);
  return status;
}
void
sane_close (SANE_Handle handle)
{
  API_ENTRY (BACKEND_NAME, close) (handle);
  return;
}
const SANE_Option_Descriptor *
sane_get_option_descriptor (SANE_Handle handle, SANE_Int index)
{
  const SANE_Option_Descriptor *desc;
  desc = API_ENTRY (BACKEND_NAME, get_option_descriptor) (handle, index);
  return desc;
}
SANE_Status
sane_control_option (SANE_Handle handle, SANE_Int index, SANE_Action action,
                     void *value, SANE_Word *info)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, control_option) (handle, index, action,
                                                     value, info);
  return status;
}
SANE_Status
sane_get_parameters (SANE_Handle handle, SANE_Parameters *parameters)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, get_parameters) (handle, parameters);
  return status;
}
SANE_Status
sane_start (SANE_Handle handle)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, start) (handle);
  return status;
}
SANE_Status
sane_read (SANE_Handle handle, SANE_Byte *buffer, SANE_Int max_length,
           SANE_Int *length)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, read) (handle, buffer, max_length,
                                           length);
  return status;
}
void
sane_cancel (SANE_Handle handle)
{
  API_ENTRY (BACKEND_NAME, cancel) (handle);
  return;
}
SANE_Status
sane_set_io_mode (SANE_Handle handle, SANE_Bool non_blocking)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, set_io_mode) (handle, non_blocking);
  return status;
}
SANE_Status
sane_get_select_fd (SANE_Handle handle, SANE_Int *fdp)
{
  SANE_Status status;
  status = API_ENTRY (BACKEND_NAME, get_select_fd) (handle, fdp);
  return status;
}
SANE_String_Const
sane_strstatus (SANE_Status status)
{
  SANE_String_Const str;
  str = API_ENTRY (BACKEND_NAME, strstatus) (status);
  return str;
}
#define SANE_I18N_(string) (string)
SANE_String_Const
API_ENTRY (BACKEND_NAME, strstatus) (SANE_Status status)
{
  switch (status)
    {
    case SANE_STATUS_GOOD:
      return SANE_I18N_("Success");
    case SANE_STATUS_UNSUPPORTED:
      return SANE_I18N_("Operation not supported");
    case SANE_STATUS_CANCELLED:
      return SANE_I18N_("Operation was cancelled");
    case SANE_STATUS_DEVICE_BUSY:
      return SANE_I18N_("Device busy");
    case SANE_STATUS_INVAL:
      return SANE_I18N_("Invalid argument");
    case SANE_STATUS_EOF:
      return SANE_I18N_("End of file reached");
    case SANE_STATUS_JAMMED:
      return SANE_I18N_("Document feeder jammed");
    case SANE_STATUS_NO_DOCS:
      return SANE_I18N_("Document feeder out of documents");
    case SANE_STATUS_COVER_OPEN:
      return SANE_I18N_("Scanner cover is open");
    case SANE_STATUS_IO_ERROR:
      return SANE_I18N_("Error during device I/O");
    case SANE_STATUS_NO_MEM:
      return SANE_I18N_("Out of memory");
    case SANE_STATUS_ACCESS_DENIED:
      return SANE_I18N_("Access to resource has been denied");
    default:
      {
        using utsushi::_;
        static char msg[80];
        snprintf (msg, 80, CCB_("Unknown SANE status code %d"), status);
        return msg;
      }
    }
}
#undef SANE_I18N_
#endif
#ifndef BACKEND_DISABLE_NAME_ALIASING
#define sane_init API_ENTRY (BACKEND_NAME, init)
#define sane_exit API_ENTRY (BACKEND_NAME, exit)
#define sane_get_devices API_ENTRY (BACKEND_NAME, get_devices)
#define sane_open API_ENTRY (BACKEND_NAME, open)
#define sane_close API_ENTRY (BACKEND_NAME, close)
#define sane_get_option_descriptor API_ENTRY (BACKEND_NAME, get_option_descriptor)
#define sane_control_option API_ENTRY (BACKEND_NAME, control_option)
#define sane_get_parameters API_ENTRY (BACKEND_NAME, get_parameters)
#define sane_start API_ENTRY (BACKEND_NAME, start)
#define sane_read API_ENTRY (BACKEND_NAME, read)
#define sane_cancel API_ENTRY (BACKEND_NAME, cancel)
#define sane_set_io_mode API_ENTRY (BACKEND_NAME, set_io_mode)
#define sane_get_select_fd API_ENTRY (BACKEND_NAME, get_select_fd)
#endif
}
#endif
