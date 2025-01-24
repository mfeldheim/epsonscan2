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
//  backend.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "backend.h"
#include "version.hpp"
#include "assert.h"
#include "epsonscan.h"
#include "list.h"
#include "loadnetworksetting.h"
#include <sstream>
extern SANE_Status epsonscan_open (const char *, SANE_Handle *);
typedef struct
{
  void *cfg;
  void *net;
  list *sane_dev;
  void **dev_list;
} backend_type;
static backend_type *epson_backend = NULL;
static void be_sane_dev_dtor (void *);
static bool backend_is_usable = true;
static SANE_Auth_Callback auth_cb = NULL;
extern "C" {
SANE_Status check_error (SDIError inError);
SANE_Status
sane_init (SANE_Int *version_code, SANE_Auth_Callback authorize)
{
  SANE_Status status = SANE_STATUS_GOOD;
  SANE_TRACE_LOG("--------------sane_init--------------");
  if(epson_backend)
  {
      return status;
  }
  if (version_code)
    {
      *version_code = SANE_VERSION_CODE (BACKEND_MAJOR, BACKEND_MINOR,
                                             BACKEND_BUILD);
    }
  epson_backend = t_calloc (1, backend_type);
  if (!epson_backend)
    {
      return SANE_STATUS_NO_MEM;
    }
  auth_cb = authorize;
  return SANE_STATUS_GOOD;
}
void
sane_exit (void)
{
  SANE_TRACE_LOG("--------------sane_exit--------------");
  if (!epson_backend)
    {
      return;
    }
  delete (epson_backend->dev_list);
  list_destroy (epson_backend->sane_dev, be_sane_dev_dtor);
  if(epson_backend){
    delete (epson_backend);
    epson_backend = NULL;
  }
  return;
}
#include <iostream>
SANE_Status
sane_get_devices (const SANE_Device ***device_list, SANE_Bool local_only)
{
  SANE_TRACE_LOG("--------------sane_get_devices--------------");
  SANE_Status status = SANE_STATUS_GOOD;
  list *sane_dev = NULL;
  sane_dev = list_create ();
  Supervisor* sv = new Supervisor();
  sv->SetUp();
  if (sane_dev)
  {
    SDIInt count = 0;
    SDIDeviceFinder* finder = nullptr;
    sv->SDIDeviceFinder_CreatePtr_(&finder);
    sv->SDIDeviceFinder_StartDiscoveryPtr_(finder, nullptr, nullptr);
    sv->SDIDeviceFinder_StopDiscoveryPtr_(finder);
    SDIDeviceInfo* sdidevices = nullptr;
    sv->SDIDeviceFinder_GetDevicesPtr_(finder, &sdidevices, &count);
     std::list<SDIDeviceInfo> netdevs;
     GetNetworkDevcicesFromIni(netdevs);
    for (int i = 0; i < count; i++)
    {
      SANE_Device* dev = (SANE_Device*)malloc(sizeof(SANE_Device));
      if(!dev){
        status = SANE_STATUS_NO_MEM;
        goto DELETE;
      }
      {
        std::stringstream nameStream;
        nameStream << sdidevices[i].displayName;
        nameStream << ":esci2:usb:";
        nameStream << sdidevices[i].modelID;
        nameStream << ":";
        nameStream << sdidevices[i].productID;
        dev->name = (SANE_String)malloc(nameStream.str().length() + 1);
        memset((void*)dev->name, 0, nameStream.str().length() + 1);
        strcpy((char*)dev->name, nameStream.str().c_str() );
      }
      {
#ifdef AKBMODE
        std::string vender = V_NAME;
#else
        std::string vender = "EPSON";
#endif
         dev->vendor = (SANE_String)malloc(vender.length() + 1);
         memset((void*)dev->vendor, 0, vender.length() + 1);
         strcpy((char*)dev->vendor, vender.c_str() );
      }
      {
         std::string model = sdidevices[i].displayName;;
         dev->model = (SANE_String)malloc(model.length() + 1);
         memset((void*)dev->model, 0, model.length() + 1);
         strcpy((char*)dev->model, model.c_str() );
      }
      {
         std::string type = "flatbed scanner";
         dev->type = (SANE_String)malloc(type.length() + 1);
         memset((void*)dev->type, 0, type.length() + 1);
         strcpy((char*)dev->type, type.c_str() );
      }
     list_append(sane_dev, dev);
    }
    for (auto netdev : netdevs)
    {
      SANE_Device* dev = (SANE_Device*)malloc(sizeof(SANE_Device));
      if(!dev){
        status = SANE_STATUS_NO_MEM;
        goto DELETE;
      }
      {
        std::stringstream nameStream;
        nameStream << "networkscanner:esci2:network:";
        nameStream << netdev.ipAddress;
        dev->name = (SANE_String)malloc(nameStream.str().length() + 1);
        memset((void*)dev->name, 0, nameStream.str().length() + 1);
        strcpy((char*)dev->name, nameStream.str().c_str() );
      }
      {
#ifdef AKBMODE
        std::string vender = V_NAME;
#else
        std::string vender = "EPSON";
#endif
         dev->vendor = (SANE_String)malloc(vender.length() + 1);
         memset((void*)dev->vendor, 0, vender.length() + 1);
         strcpy((char*)dev->vendor, vender.c_str() );
      }
      {
         std::string model = "network scanner";;
         dev->model = (SANE_String)malloc(model.length() + 1);
         memset((void*)dev->model, 0, model.length() + 1);
         strcpy((char*)dev->model, model.c_str() );
      }
      {
         std::string type = "flatbed scanner";
         dev->type = (SANE_String)malloc(type.length() + 1);
         memset((void*)dev->type, 0, type.length() + 1);
         strcpy((char*)dev->type, type.c_str() );
      }
      list_append(sane_dev, dev);
    }
    if (epson_backend->sane_dev)
    {
      delete (epson_backend->dev_list);
      list_destroy (epson_backend->sane_dev, be_sane_dev_dtor);
    }
    epson_backend->sane_dev = sane_dev;
    sv->SDIDeviceFinder_DisposePtr_(finder);
    finder = nullptr;
  }
  epson_backend->dev_list = list_normalize (epson_backend->sane_dev);
  *device_list = (const SANE_Device **)epson_backend->dev_list;
  if (!*device_list)
  {
    status = SANE_STATUS_NO_MEM;
  }
  delete sv;
  sv = nullptr;
  return status;
DELETE:
  list_destroy (sane_dev, be_sane_dev_dtor);
  sane_dev = NULL;
  delete sv;
  sv = nullptr;
  return status;
}
SANE_Status
sane_open (SANE_String_Const device_name, SANE_Handle *handle)
{
  SANE_TRACE_LOG("--------------sane_open--------------");
  SANE_TRACE_LOG("%s", device_name);
  const SANE_Device *sane_dev = NULL;
  if (!epson_backend)
  {
    return SANE_STATUS_ACCESS_DENIED;
  }
  if (!handle)
  {
    return SANE_STATUS_INVAL;
  }
  return epsonscan_open(device_name, handle);
}
void
dip_flip_bits (SANE_Byte *buf, SANE_Int total_size)
{
  SANE_Byte *p;
  int i = 0;
  p = buf;
  while (i < total_size)
    {
      *p = ~*p;
      ++p;
      i++;
    }
}
SANE_Status
check_error (SDIError inError)
{
  SANE_Status status = SANE_STATUS_GOOD;
  SANE_TRACE_LOG("Error Code : %d", inError);
  if(inError != kSDIErrorNone){
    if(inError == kSDIErrorPaperEmpty){
      SANE_TRACE_LOG("ERROR : Load the originals in the ADF.");
      status = SANE_STATUS_NO_DOCS;
    }else if(inError == kSDIErrorPaperJam){
      SANE_TRACE_LOG("ERROR : A paper jam has occurred. See the documentation for instructions on removing your originals.");
      status = SANE_STATUS_JAMMED;
    }else if(inError == kSDIErrorPaperDoubleFeed){
      SANE_TRACE_LOG("ERROR : Double feed detected. See the documentation for instructions on removing your originals.");
      status = SANE_STATUS_JAMMED;
    }else if(inError == kSDIErrorPaperDoubleFeed2){
      SANE_TRACE_LOG("ERROR : Double feed detected.");
      status = SANE_STATUS_JAMMED;
    }else if(inError == kSDIErrorPaperProtect){
      SANE_TRACE_LOG("ERROR : A paper jam has occurred. See the documentation for instructions on removing your originals.");
      status = SANE_STATUS_JAMMED;
    }else if(inError == kSDIErrorDeviceInBusy){
      SANE_TRACE_LOG("ERROR : kSDIErrorDeviceInBusy");
      status = SANE_STATUS_DEVICE_BUSY;
    }else if(inError == kSDIErrorCoverOpen){
      SANE_TRACE_LOG("ERROR : ADF or ADF cover is open. Close it and reload the originals.");
      status = SANE_STATUS_COVER_OPEN;
    }else if(inError == kSDIErrorTrayClose){
      SANE_TRACE_LOG("ERROR : The input tray is closed. Open the input tray.");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorDataSend){
      SANE_TRACE_LOG("ERROR : Unable to send data. Check the connection to the scanner and try again.");
      status = SANE_STATUS_IO_ERROR;
    }else if(inError == kSDIErrorDataReceive){
      SANE_TRACE_LOG("ERROR : Unable to receive data. Check the connection to the scanner and try again.");
      status = SANE_STATUS_IO_ERROR;
    }else if(inError == kSDIErrorDeviceInUse){
      SANE_TRACE_LOG("ERROR : The scanner is in use or unavailable. Please wait.");
      status = SANE_STATUS_DEVICE_BUSY;
    }else if(inError == kSDIErrorNoMemory){
#ifdef AKBMODE
      SANE_TRACE_LOG("ERROR : Not enough memory for Scanner Driver. Close other applications and try again.");
#else
      SANE_TRACE_LOG("ERROR : Not enough memory for Epson Scan 2. Close other applications and try again.");
#endif
      status = SANE_STATUS_NO_MEM;
    }else if(inError == kSDIErrorUnknownError){
#ifdef AKBMODE
      SANE_TRACE_LOG("ERROR : An unexpected error occurred. Scanner Driver will close.");
#else
      SANE_TRACE_LOG("ERROR : An unexpected error occurred. Epson Scan 2 will close.");
#endif
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorDeviceFormChangedInterruptedly){
      SANE_TRACE_LOG("ERROR : DeviceFormChangedInterruptedly");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorDeviceFormUnstable){
      SANE_TRACE_LOG("ERROR : DeviceFormUnstable");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorSepLeverChangedInterruptedly){
      SANE_TRACE_LOG("ERROR : SepLeverChangedInterruptedly");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorUnscannableDeviceConfig1){
      SANE_TRACE_LOG("ERROR : UnscannableDeviceConfig");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorETSensorError){
      SANE_TRACE_LOG("ERROR : ETSensor");
      status = SANE_STATUS_INVAL;
    }else if(inError == kSDIErrorUserAuthEnabled){
      SANE_TRACE_LOG("ERROR : UserAuthEnabled");
      status = SANE_STATUS_INVAL;
    }else {
#ifdef AKBMODE
      SANE_TRACE_LOG("ERROR : An unexpected error occurred. Scanner Driver will close.");
#else
      SANE_TRACE_LOG("ERROR : An unexpected error occurred. Epson Scan 2 will close.");
#endif
      status = SANE_STATUS_INVAL;
    }
  }
  return status;
}
double calculate_pixel_size(int base_res, double value)
{
    double mpp = 25.4 / base_res;
    return value / mpp;
}
#define BASE_RESOLUTION 100
bool handle_scan_area (Epson_Scanner *s, double* current_pixel_x, double* current_pixel_y)
{
  int base_res = s->hw->sv->device_data.Resolution.select;
  *current_pixel_x = s->hw->sv->device_data.ScanArea.ScanAreaWidth.select / BASE_RESOLUTION * base_res;
  *current_pixel_y = s->hw->sv->device_data.ScanArea.ScanAreaHeight.select / BASE_RESOLUTION * base_res;
  SANE_TRACE_LOG("doc size : %s", s->hw->cur_doc_size);
  SANE_TRACE_LOG("base res : %d", s->hw->sv->device_data.Resolution.select);
  if(s->hw->sv->device_data.ScanArea.FixedSize == A3){
    *current_pixel_x = calculate_pixel_size(base_res, 297);
    *current_pixel_y = calculate_pixel_size(base_res, 420);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A4){
    *current_pixel_x = calculate_pixel_size(base_res, 210);
    *current_pixel_y = calculate_pixel_size(base_res, 297);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A4_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 297);
    *current_pixel_y = calculate_pixel_size(base_res, 210);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A5){
    *current_pixel_x = calculate_pixel_size(base_res, 148);
    *current_pixel_y = calculate_pixel_size(base_res, 210);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A5_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 210);
    *current_pixel_y = calculate_pixel_size(base_res, 148);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A6){
    *current_pixel_x = calculate_pixel_size(base_res, 105);
    *current_pixel_y = calculate_pixel_size(base_res, 148);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A6_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 148);
    *current_pixel_y = calculate_pixel_size(base_res, 105);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A8){
    *current_pixel_x = calculate_pixel_size(base_res, 52);
    *current_pixel_y = calculate_pixel_size(base_res, 74);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == A8_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 74);
    *current_pixel_y = calculate_pixel_size(base_res, 52);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == B4_JIS){
    *current_pixel_x = calculate_pixel_size(base_res, 257);
    *current_pixel_y = calculate_pixel_size(base_res, 364);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == B4_JIS_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 364);
    *current_pixel_y = calculate_pixel_size(base_res, 257);
 }else if(s->hw->sv->device_data.ScanArea.FixedSize == B5_JIS){
    *current_pixel_x = calculate_pixel_size(base_res, 182);
    *current_pixel_y = calculate_pixel_size(base_res, 257);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == B5_JIS_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 257);
    *current_pixel_y = calculate_pixel_size(base_res, 182);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Letter){
    *current_pixel_x = calculate_pixel_size(base_res, 216);
    *current_pixel_y = calculate_pixel_size(base_res, 279);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Letter_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 279);
    *current_pixel_y = calculate_pixel_size(base_res, 216);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Legal){
    *current_pixel_x = calculate_pixel_size(base_res, 216);
    *current_pixel_y = calculate_pixel_size(base_res, 356);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Postcard){
    *current_pixel_x = calculate_pixel_size(base_res, 100);
    *current_pixel_y = calculate_pixel_size(base_res, 148);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Postcard_Landscape){
    *current_pixel_x = calculate_pixel_size(base_res, 148);
    *current_pixel_y = calculate_pixel_size(base_res, 100);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == PlasticCard){
    *current_pixel_x = calculate_pixel_size(base_res, 85.6);
    *current_pixel_y = calculate_pixel_size(base_res, 54);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Tabloid){
    *current_pixel_x = calculate_pixel_size(base_res, 279);
    *current_pixel_y = calculate_pixel_size(base_res, 432);
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Maximum_Size){
    *current_pixel_x = (double)s->hw->sv->device_data.ScanArea.MaxScanAreaWidth.select / (double)BASE_RESOLUTION * (double)base_res;
    *current_pixel_y = (double)s->hw->sv->device_data.ScanArea.MaxScanAreaHeight.select / (double)BASE_RESOLUTION * (double)base_res;
  }else if(s->hw->sv->device_data.ScanArea.FixedSize == Manual){
    s->hw->sv->device_data.ScanArea.AutoSize.select = 0;
    return true;
  }else {
    return false;
  }
  SANE_TRACE_LOG ("x, y :(%f , %f)", *current_pixel_x, *current_pixel_y);
  s->hw->sv->device_data.ScanArea.AutoSize.select = 0;
  return true;
}
#include "epsonsane.h"
SANE_Status
sane_get_parameters (SANE_Handle handle, SANE_Parameters *parameters)
{
  SANE_TRACE_LOG("--------------sane_get_parameters--------------");
  Epson_Scanner *s = (Epson_Scanner *) handle;
  SANE_Status status = SANE_STATUS_GOOD;
  int width = 0;
  int height = 0;
  if(s->scan_ready){
    SDITransferEventType outType = kSDITrasnferEventTypeImage;
    unsigned int nSize = 100;
    unsigned char* tmp_buf = (unsigned char*)::malloc(nSize);
    SDIChar* output_path;
    if(tmp_buf){
      memset(tmp_buf, 0, nSize);
    }else {
      SANE_TRACE_LOG("Status is SANE_STATUS_NO_MEM.");
      status = SANE_STATUS_NO_MEM;
      goto ERROR_2;
    }
    output_path = (SDIChar*)tmp_buf;
    SDIError outError;
    while (true)
    {
      s->hw->sv->SDIImage_CreatePtr_(&s->outImageData);
      s->hw->sv->SDIScannerDriver_GetNextTransferEventPtr_(s->hw->sv->driver,
                                             &outType,
                                             s->outImageData,
                                             &outError);
      if((outType == kSDITrasnferEventTypeImage) && s->hw->sv->SDIImage_CheckImageIsBlankPtr_(s->outImageData))
      {
        SANE_TRACE_LOG("blankptr.");
        s->hw->sv->SDIImage_DisposePtr_(s->outImageData);
      }else{
        break;
      }
    }
    status = check_error(outError);
    if(status != SANE_STATUS_GOOD){
      SANE_TRACE_LOG("Status is no SANE_STATUS_GOOD. %d", outError);
      goto ERROR;
    }
    if (outType == kSDITrasnferEventTypeImage)
    {
      SANE_TRACE_LOG("kSDITrasnferEventTypeImage -> SDIImage_GetPathPtr_");
      s->hw->sv->SDIImage_GetPathPtr_(s->outImageData, output_path, 0);
    }else if (outType == kSDITransferEventTypeCancel){
      SANE_TRACE_LOG("Button Cancel");
      s->cancel_requested = true;
      s->scan_complete = true;
    }else {
      SANE_TRACE_LOG("Other EventType");
    }
    if(s->hw->sv->device_data.ColorType.select == kSDIColorTypeRGB24)
    {
      SANE_TRACE_LOG("SANE_FRAME_RGB");
      parameters->format = SANE_FRAME_RGB;
    }else if(s->hw->sv->device_data.ColorType.select == kSDIColorTypeMono8 ||
            s->hw->sv->device_data.ColorType.select == kSDIColorTypeMono1)
    {
      SANE_TRACE_LOG("SANE_FRAME_GRAY");
      parameters->format = SANE_FRAME_GRAY;
    }
    width = s->hw->sv->SDIImage_GetWidthPtr_(s->outImageData);
    height = s->hw->sv->SDIImage_GetHeightPtr_(s->outImageData);
    parameters->lines = height;
    parameters->depth = s->hw->sv->SDIImage_GetBitsPerSamplePtr_(s->outImageData);
    s->hw->ChannelPerPixel = s->hw->sv->SDIImage_GetSamplesPerPixelPtr_(s->outImageData);
    parameters->bytes_per_line = (width * s->hw->ChannelPerPixel * parameters->depth + 7) / 8;
    parameters->pixels_per_line = width;
    s->total_datasize = parameters->bytes_per_line * height;
    SANE_TRACE_LOG("width : %d", width);
    SANE_TRACE_LOG("height : %d", height);
    SANE_TRACE_LOG("parameters->last_frame : %d", parameters->last_frame);
    SANE_TRACE_LOG("parameters->format : %d", parameters->format);
    SANE_TRACE_LOG("parameters->bytes_per_line : %d", parameters->bytes_per_line);
    SANE_TRACE_LOG("parameters->pixels_per_line : %d", parameters->pixels_per_line);
    SANE_TRACE_LOG("parameters->lines : %d", parameters->lines);
    SANE_TRACE_LOG("parameters->depth : %d", parameters->depth);
    SANE_TRACE_LOG("s->hw->ChannelPerPixel : %d", s->hw->ChannelPerPixel);
    SANE_TRACE_LOG("total_datasize : %d", s->total_datasize);
    if (s->cancel_requested == true){
      SANE_TRACE_LOG("Cancel requested");
      goto ERROR;
    }
    s->cur_pos = 0;
    if(output_path){
      FILE *fp = nullptr;
      SANE_TRACE_LOG("output_path : %s", output_path);
      if(s->out_buffer){
        free(s->out_buffer);
        s->out_buffer = NULL;
      }
      s->out_buffer = (SANE_Byte *)malloc(s->total_datasize);
      if(!s->out_buffer){
        status = SANE_STATUS_NO_MEM;
        goto ERROR;
      }
      if((fp = fopen(output_path, "rb")) != nullptr){
        if(fread(s->out_buffer, 1, s->total_datasize, fp) != s->total_datasize){
          status = SANE_STATUS_INVAL;
          if(fp != nullptr){
            fclose(fp);
          }
          goto ERROR;
        }else {
          if(fp != nullptr){
            fclose(fp);
          }
          parameters->last_frame = SANE_TRUE;
        }
      }else {
        status = SANE_STATUS_INVAL;
        goto ERROR;
      }
      if(s->hw->sv->device_data.ColorType.select == kSDIColorTypeMono1){
        dip_flip_bits(s->out_buffer, s->total_datasize);
      }
    }
  ERROR:
    s->hw->sv->SDIImage_DisposePtr_(s->outImageData);
  ERROR_2:
    if(tmp_buf){
      free(tmp_buf);
      tmp_buf = nullptr;
    }
    if(s->cancel_requested == true){
      SANE_TRACE_LOG("Cancel requested2");
      status = SANE_STATUS_CANCELLED;
    }
}else {
  if(s->hw->sv->device_data.ColorType.select == ColorTypeRGB24)
  {
    SANE_TRACE_LOG("SANE_FRAME_RGB");
    parameters->format = SANE_FRAME_RGB;
  }else if(s->hw->sv->device_data.ColorType.select == ColorTypeMono8 ||
          s->hw->sv->device_data.ColorType.select == ColorTypeMono1)
  {
    SANE_TRACE_LOG("SANE_FRAME_GRAY");
    parameters->format = SANE_FRAME_GRAY;
  }
  double current_pixel_x = 0;
  double current_pixel_y = 0;
  if(!handle_scan_area(s, &current_pixel_x, &current_pixel_y)){
    select_current_doc_size(s, s->hw->sv->device_data);
    handle_scan_area(s, &current_pixel_x, &current_pixel_y);
  }
  SANE_TRACE_LOG("device_data.ScanArea.FixedSize : %d", s->hw->sv->device_data.ScanArea.FixedSize);
  SANE_TRACE_LOG("current_pixel_x : %f", current_pixel_x);
  SANE_TRACE_LOG("current_pixel_y : %f", current_pixel_y);
  SANE_TRACE_LOG("s->val[OPT_SCAN_AREA].w : %d", s->val[OPT_SCAN_AREA].w);
  SANE_TRACE_LOG("s->val[OPT_TL_X].w : %f", s->val[OPT_TL_X].w);
  SANE_TRACE_LOG("s->val[OPT_TL_Y].w : %f", s->val[OPT_TL_Y].w);
  SANE_TRACE_LOG("s->val[OPT_BR_X].w : %f", s->val[OPT_BR_X].w);
  SANE_TRACE_LOG("s->val[OPT_BR_Y].w : %f", s->val[OPT_BR_Y].w);
  width = current_pixel_x;
  height = current_pixel_y;
  parameters->lines = height;
  if(s->hw->sv->device_data.ColorType.select == ColorTypeRGB24){
    parameters->depth = 8;
    s->hw->ChannelPerPixel = 3;
  }else if(s->hw->sv->device_data.ColorType.select == ColorTypeMono8){
    parameters->depth = 8;
    s->hw->ChannelPerPixel = 1;
  }else if(s->hw->sv->device_data.ColorType.select == ColorTypeMono1){
    parameters->depth = 1;
    s->hw->ChannelPerPixel = 1;
  }
  parameters->bytes_per_line = (width * s->hw->ChannelPerPixel * parameters->depth + 7) / 8;
  parameters->pixels_per_line = width;
  s->total_datasize = parameters->bytes_per_line * height;
    SANE_TRACE_LOG("parameters->last_frame : %d", parameters->last_frame);
    SANE_TRACE_LOG("parameters->format : %d", parameters->format);
    SANE_TRACE_LOG("parameters->bytes_per_line : %d", parameters->bytes_per_line);
    SANE_TRACE_LOG("parameters->pixels_per_line : %d", parameters->pixels_per_line);
    SANE_TRACE_LOG("parameters->lines : %d", parameters->lines);
    SANE_TRACE_LOG("parameters->depth : %d", parameters->depth);
    SANE_TRACE_LOG("total_datasize : %d", s->total_datasize);
}
  return status;
}
SANE_Status
sane_read (SANE_Handle handle, SANE_Byte *buffer, SANE_Int max_length,
           SANE_Int *length)
{
  SANE_TRACE_LOG("--------------sane_read--------------");
  SANE_Status status = SANE_STATUS_GOOD;
  Epson_Scanner *s;
  if (length) *length = 0;
  if (!handle)
    {
      return SANE_STATUS_INVAL;
    }
  s = (Epson_Scanner *) handle;
  if(s->out_buffer == NULL)
  {
    *length = 0;
    return SANE_STATUS_GOOD;
  }
  if(s->total_datasize == 0){
    SANE_TRACE_LOG("image data -> EOF");
    s->image_count++;
    s->scan_complete = true;
    if(s->out_buffer){
      free(s->out_buffer);
      s->out_buffer = NULL;
    }
    return SANE_STATUS_EOF;
  }else if(length){
    if((s->total_datasize - max_length) < 0){
      SANE_TRACE_LOG("Last data size : %d", s->total_datasize);
      *length = s->total_datasize;
    }else {
      *length = max_length;
    }
    memcpy(buffer, s->out_buffer + s->cur_pos, *length);
    s->total_datasize -= *length;
    s->cur_pos += *length;
    SANE_TRACE_LOG("length : %d", *length);
  }
  SANE_TRACE_LOG("cur_pos : %d", s->cur_pos);
  return status;
}
void
sane_cancel (SANE_Handle handle)
{
  SANE_TRACE_LOG("--------------sane_cancel--------------");
  SANE_Status status = SANE_STATUS_GOOD;
  Epson_Scanner *s;
  s = (Epson_Scanner *) handle;
  s->image_count = 0;
  s->scan_ready = false;
  if(s->scan_complete == false){
    if(s->cancel_requested == false){
      s->cancel_requested = true;
    }else if(s->cancel_requested == true){
      SANE_TRACE_LOG("Scan cancel terminated.");
      s->hw->sv->SDIScannerDriver_DoScanJobPtr_(s->hw->sv->driver, kSDIOperationTypeCancel);
    }
  }else {
    s->hw->sv->SDIImage_CreatePtr_(&s->outImageData);
    s->hw->sv->SDIScannerDriver_GetNextTransferEventPtr_(s->hw->sv->driver,
                                           0,
                                           s->outImageData,
                                           0);
    s->hw->sv->SDIImage_DisposePtr_(s->outImageData);
  }
  SANE_TRACE_LOG("--------------sane_cancel--------------");
  return;
}
SANE_Status
sane_set_io_mode (SANE_Handle handle, SANE_Bool non_blocking)
{
  SANE_TRACE_LOG("--------------sane_set_io_mode--------------");
 handle = handle;
 non_blocking = non_blocking;
 return SANE_STATUS_UNSUPPORTED;
}
SANE_Status
sane_get_select_fd (SANE_Handle handle, SANE_Int *fdp)
{
  SANE_TRACE_LOG("--------------sane_get_select_fd--------------");
 handle = handle;
 return SANE_STATUS_UNSUPPORTED;
}
}
static void
be_sane_dev_dtor (void *p)
{
  SANE_Device *sd = (SANE_Device *) p;
  if (!sd) return;
  free((void*)sd->name);
  free((void*)sd->vendor);
  free((void*)sd->type);
  free((void*)sd->model);
  free (sd);
}
