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
//  main.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include <iostream>
#include "../ESCANLIB.h"
#define LICENSE_KEY "EPSON"
#define DEVICE_NAME "PX-M780F Series"
BOOL CALLBACK eslCallback(EslCBDataHdr* pData, PVOID pPrivate)
{
 if (pData == NULL) {
  return FALSE;
 }
 switch (pData->type) {
  case CBDT_STATUS_SCAN:
  {
   EslCBDataScanStatus* pstatus = (EslCBDataScanStatus*)pData;
   switch (pstatus->status) {
   case STATUS_SCAN_UPDATE_PROGRESS:
    break;
   case STATUS_SCAN_PAGE_END:
    break;
   default:
    std::cout << "[ERROR]Invalid CallbackData Status\n" << std::endl;
   }
   BOOL cancelReqfromApp = FALSE;
   if (cancelReqfromApp) {
    return FALSE;
   }
   break;
  }
  case CBDT_IMAGE_FILE:
  {
   EslCBDImageFile* pstatus = (EslCBDImageFile*)pData;
   switch (pstatus->status) {
   case STATUS_IMAGE_FILE_INFO:
    break;
   default:
    std::cout << "[ERROR]Invalid CallbackData Status\n" << std::endl;
   }
   break;
  }
  default:
   std::cout << "[ERROR]Invalid CallbackData Status\n" << std::endl;
 }
 return TRUE;
}
DWORD SCAN_SAVE_Default(void)
{
 std::cout << "[INFO]SCAN_SAVE_Default" << std::endl;
 DWORD instance = 0;
 DWORD err = 0;
 BOOL ret = eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  ConnectInfo scanner = {CT_DEFAULT, DEVICE_NAME};
  ret = eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   if (ret) {
    ret = eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
    ret = eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
    ret = eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
    ret = eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, &err);
   }
   ret = eslCloseScanner(instance, &err);
  }
  eslFree(instance, &err);
 }
 return err;
}
int APIENTRY main()
{
 SCAN_SAVE_Default();
 std::cout << "[INFO]Last!!" << std::endl;
 return 0;
}
