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
//  ESL_SAMPLE.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ESL_SAMPLE.h"
#include "EslStub.h"
#include <iostream>
#include <cctype>
#define LICENSE_KEY "EPSON"
#define DEVICE_NAME "DS-C480W:534245393030303049"
#define SAVE_PATH "."
#define SAVE_FILE_NAME "img"
#define IP_ADDRESS "10.8.106.99"
BOOL isDigits(const char* str) {
 if (*str == '-'){
        ++str;
 }
    while (*str) {
        if (!isdigit(*str))
            return FALSE;
        ++str;
    }
    return TRUE;
}
BOOL CALLBACK eslCallback(EslCBDataHdr* pData, PVOID pPrivate)
{
 std::cout << "[INFO]eslCallback" << std::endl;
 if (pData == NULL) {
  std::cout << "[INFO]pData is NULL" << std::endl;
  return FALSE;
 }
 BOOL cancelReqfromApp = FALSE;
 switch (pData->type) {
  case CBDT_STATUS_SCAN:
  {
   EslCBDataScanStatus* pstatus = (EslCBDataScanStatus*)pData;
   switch (pstatus->status) {
   case STATUS_SCAN_UPDATE_PROGRESS:
    break;
   case STATUS_SCAN_PAGE_END:
    std::cout << "[INFO]PageCount: " << pstatus->count << std::endl;
    std::cout << "[INFO]Proguress: " << pstatus->progress << std::endl;
    break;
   default:
    std::cout << "[ERROR]Invalid CallbackData Status\n" << std::endl;
   }
   if (cancelReqfromApp) {
    return FALSE;
   }
   break;
  }
  case CBDT_IMAGE_FILE:
  {
   EslCBDImageFile* pstatus = (EslCBDImageFile*)pData;
   std::cout << "[INFO]FileName: " << pstatus->filename << std::endl;
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
BOOL Parameter_Check(const char* param, checkOption check_option, DWORD* pErrCode){
 *pErrCode = 0;
 if (param == NULL){
  std::cout << "Parameter error." << std::endl;
  std::cout << "Option followed by a parameter." << std::endl;
  *pErrCode = 1;
  return FALSE;
 }
 switch (check_option) {
 case CO_DEVICEID:
  if (isDigits(param) == TRUE){
   std::cout << "Parameter error." << std::endl;
   std::cout << "Invaild parameter." << std::endl;
   *pErrCode = 1;
   return FALSE;
  }
  break;
 case CO_VALUE:
  if (isDigits(param) == FALSE){
   std::cout << "Parameter error." << std::endl;
   std::cout << "Invaild parameter." << std::endl;
   *pErrCode = 1;
   return FALSE;
  }
  break;
 default:
  std::cout << "Error. Invaild checkOption." << check_option << std::endl;
  *pErrCode = 2;
  return FALSE;
 }
 return TRUE;
}
BOOL Setup_ConnectInfo (const char* device_name, const connectionMethod connection_method, ConnectInfo* scanner, DWORD* pErrCode){
  switch (connection_method) {
  case CM_USB:
   scanner->connectType = CT_DEFAULT;
   memcpy(scanner->deviceName, device_name, strlen(device_name)+1);
   break;
  case CM_NETWORK:
   scanner->connectType = CT_NET_IPV4;
   memcpy(scanner->networkAddress, device_name, strlen(device_name)+1);
   break;
  default:
   std::cout << "Error. Invaild connectionMethod." << connection_method << std::endl;
   *pErrCode = 1;
   return FALSE;
  }
  return TRUE;
}
BOOL SCAN_SAVE(const char* device_name, int argc, char *argv[], const connectionMethod connection_method , DWORD* pErrCode)
{
 DWORD instance = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, pErrCode);
 if (ret) {
  ConnectInfo scanner = {};
  ret = Setup_ConnectInfo(device_name, connection_method, &scanner, pErrCode);
  ret = eslib.eslOpenScanner(instance, &scanner, pErrCode);
  if (ret) {
   EslParamScanExV1 scan_params;
   scan_params.type = ESL_PARAM_SCAN_EX_V1;
   scan_params.size = sizeof(scan_params);
   EslParamSaveBasic save_params;
   save_params.type = ESL_PARAM_SAVE_BASIC;
   save_params.size = sizeof(save_params);
   ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&scan_params, pErrCode);
   if (ret){
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&save_params, pErrCode);
    if (ret){
     strncpy((char *)save_params.filePath, SAVE_PATH, sizeof(save_params.filePath));
     strncpy((char *)save_params.fileNamePrefix, SAVE_FILE_NAME, sizeof(save_params.fileNamePrefix));
     int i = 1;
     while(i < argc){
      if(strcmp(argv[i], OPTION_MODE) == 0){
       std::cout << "--mode option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.imgType = (eImageType)atoi(argv[i]);
       }else{
        std::cout << "--mode option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_SOURCE) == 0){
       std::cout << "--source option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.docSource = (eDocSource)atoi(argv[i]);
       }else{
        std::cout << "--source option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_SCAN_AREA) == 0){
       std::cout << "--scan-area option." << std::endl;
       if(Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.docSize = (eDocSize)atoi(argv[i]);
        if(scan_params.docSize == DS_USER){
         BOOL x_area_flag = FALSE;
         BOOL y_area_flag = FALSE;
         scan_params.sizeUnit = SU_MILLIMETER;
         std::cout << "argv[i+1] = " << argv[i+1] << std::endl;
         while(argv[i+1] && (strcmp(argv[i+1],"-l") == 0 || strcmp(argv[i+1],"-t") == 0 || strcmp(argv[i+1],"-x") == 0 || strcmp(argv[i+1],"-y") == 0)){
          i++;
          std::cout << "while argv[i+1] = " << argv[i+1] << std::endl;
          if(Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
           if(strcmp(argv[i],"-l") == 0){
            scan_params.sizeUser.left = atoi(argv[i+1]);
            i++;
           }else if(strcmp(argv[i],"-t") == 0){
            scan_params.sizeUser.top = atoi(argv[i+1]);
            i++;
           }else if(strcmp(argv[i],"-x") == 0){
            scan_params.sizeUser.right = atoi(argv[i+1]);
            i++;
            x_area_flag = TRUE;
           }else if(strcmp(argv[i],"-y") == 0){
            scan_params.sizeUser.bottom = atoi(argv[i+1]);
            i++;
            y_area_flag = TRUE;
           }
          }else{
           std::cout << "user area parameter err: " << *pErrCode << std::endl;
           goto Exit;
          }
         }
         if (!x_area_flag || !y_area_flag){
          *pErrCode = 1;
          std::cout << "user area option err: " << *pErrCode << std::endl;
          std::cout << "When specifying user size, be sure to specify area with the -x and -y options, as shown below." << std::endl;
          std::cout << "sdksample --scan [Device ID] --scan-area 0 -x 21000 -y 29700" << std::endl;
          goto Exit;
         }
        }
       }else{
        std::cout << "--scan-area option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_RESOLUTION) == 0){
       std::cout << "--resolution option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.resolution = atoi(argv[i]);
       }else{
        std::cout << "--resolution option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_ROTATE) == 0){
       std::cout << "--rotate option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.docRotate = (eDocRotate)atoi(argv[i]);
       }else{
        std::cout << "--rotate option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_BRIGHTNESS) == 0){
       std::cout << "--brightness option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.brightness = atoi(argv[i]);
       }else{
        std::cout << "--brightness option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_CONTRAST) == 0){
       std::cout << "--contrast option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.contrast = atoi(argv[i]);
       }else{
        std::cout << "--contrast option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_THRESHOLD) == 0){
       std::cout << "--threshold option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.threshold = atoi(argv[i]);
       }else{
        std::cout << "--threshold option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_DROPOUT) == 0){
       std::cout << "--dropout option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.colorFilter = (eColorFilter)atoi(argv[i]);
       }else{
        std::cout << "--dropout option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_BLANKPAGE_SKIP) == 0){
       std::cout << "--blankpage-skip option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.optBlankPageSkip = (eBPSkip)atoi(argv[i]);
       }else{
        std::cout << "--blankpage-skip option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }else if(strcmp(argv[i], OPTION_DOUBLE_FEED_DETECTION) == 0){
       std::cout << "--double-feed-detection option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        scan_params.optDoubleFeedDetect = (eDFDetect)atoi(argv[i]);
       }else{
        std::cout << "--double-feed-detection option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }
      else if(strcmp(argv[i], OPTION_IMAGE_FORMAT) == 0){
       std::cout << "--image-format option." << std::endl;
       if (Parameter_Check(argv[i+1], CO_VALUE, pErrCode)){
        i++;
        save_params.fileFormat = (eFileFormat)atoi(argv[i]);
       }else{
        std::cout << "--image-format option err: " << *pErrCode << std::endl;
        goto Exit;
       }
      }
      i++;
     }
     ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&scan_params, pErrCode);
     if (ret){
      ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&save_params, pErrCode);
     }else{
      std::cout << "[ERROR]scan_params eslCtrlParameter(POT_SET) err: " << *pErrCode << std::endl;
      goto Exit;
     }
    }else{
     std::cout << "[ERROR]save_params eslCtrlParameter(POT_GET_DEFAULT) err: " << *pErrCode << std::endl;
     goto Exit;
    }
   }else{
    std::cout << "[ERROR]scan_params eslCtrlParameter(POT_GET_DEFAULT) err: " << *pErrCode << std::endl;
    goto Exit;
   }
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, pErrCode);
    if (ret){
     if (!eslib.eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, pErrCode)){
      std::cout << "[ERROR]eslExecute(ET_SAVE_STORED_IMAGE) err: " << *pErrCode << std::endl;
      goto Exit;
     }
    }else{
     std::cout << "[ERROR]eslExecute(ET_SCAN_AND_STORE) err: " << *pErrCode << std::endl;
     goto Exit;
    }
   }else{
    std::cout << "[ERROR]save_params eslCtrlParameter(POT_SET) err: " << *pErrCode << std::endl;
    goto Exit;
   }
  }else{
   std::cout << "[ERROR]eslOpenScanner err: " << *pErrCode << std::endl;
  }
 }else{
  std::cout << "[ERROR]eslInit err: " << *pErrCode << std::endl;
 }
Exit:
 if (*pErrCode != ESL_SUCCESS){
  return FALSE;
 }
 eslib.eslCloseScanner(instance, pErrCode);
 eslib.eslFree(instance, pErrCode);
 return TRUE;
}
DWORD SCAN_SAVE_Default(const char* device_name)
{
 std::cout << "[INFO]SCAN_SAVE_Default" << std::endl;
 DWORD instance = 0;
 DWORD err = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  ConnectInfo scanner = {CT_DEFAULT};
  memcpy(scanner.deviceName, device_name, strlen(device_name)+1);
  ret = eslib.eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SCAN_AND_SAVE, eslCallback, NULL, &err);
   }
   ret = eslib.eslCloseScanner(instance, &err);
  }
  eslib.eslFree(instance, &err);
 }
 return err;
}
DWORD SCN_Get_Setting_Parameter(const char* device_name, eSpecifiedParameter SpecifiedParameter, INT* select, const connectionMethod connection_method, DWORD* pErrCode){
 DWORD instance = 0;
 CEslStub eslib(NULL);
 if (!eslib.eslInit(&instance, LICENSE_KEY, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter eslInit err: " << *pErrCode << std::endl;
  return FALSE;
 }
 ConnectInfo scanner = {};
 if (!Setup_ConnectInfo(device_name, connection_method, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter Setup_ConnectInfo err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if (!eslib.eslOpenScanner(instance, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter eslOpenScanner err: " << *pErrCode << std::endl;
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 if (!eslib.eslGetSettingParameter(instance, SpecifiedParameter, pErrCode, select)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter eslGetSettingParameter err: " << *pErrCode << std::endl;
  if(!eslib.eslCloseScanner(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Setting_Parameter eslCloseScanner err: " << *pErrCode << std::endl;
  }
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 if(!eslib.eslCloseScanner(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter eslCloseScanner err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if(!eslib.eslFree(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  return FALSE;
 }
 return TRUE;
}
DWORD SCN_Set_Setting_Parameter(const char* device_name, eSpecifiedParameter SpecifiedParameter, const INT setparam, const connectionMethod connection_method, DWORD* pErrCode)
{
 DWORD instance = 0;
 CEslStub eslib(NULL);
 if (!eslib.eslInit(&instance, LICENSE_KEY, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter eslInit err: " << *pErrCode << std::endl;
  return FALSE;
 }
 ConnectInfo scanner = {};
 if (!Setup_ConnectInfo(device_name, connection_method, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter Setup_ConnectInfo err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if (!eslib.eslOpenScanner(instance, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter eslOpenScanner err: " << *pErrCode << std::endl;
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Set_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 if (!eslib.eslSetSettingParameter(instance, SpecifiedParameter, pErrCode, setparam)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter eslSetSettingParameter err: " << *pErrCode << std::endl;
  if(!eslib.eslCloseScanner(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Set_Setting_Parameter eslCloseScanner err: " << *pErrCode << std::endl;
  }
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Set_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 if(!eslib.eslCloseScanner(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter eslCloseScanner err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if(!eslib.eslFree(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter eslFree err: " << *pErrCode << std::endl;
  return FALSE;
 }
 return TRUE;
}
BOOL SCN_Get_Device_Status(const char* device_name, const connectionMethod connection_method, DWORD* pErrCode){
 DWORD instance = 0;
 CEslStub eslib(NULL);
 if (!eslib.eslInit(&instance, LICENSE_KEY, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Device_Status eslInit err: " << *pErrCode << std::endl;
  return FALSE;
 }
 ConnectInfo scanner = {};
 if (!Setup_ConnectInfo(device_name, connection_method, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Set_Setting_Parameter Setup_ConnectInfo err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if (!eslib.eslOpenScanner(instance, &scanner, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Device_Status eslOpenScanner err: " << *pErrCode << std::endl;
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Device_Status eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 DWORD status = 0;
 if(!eslib.eslGetDeviceStatus(instance, &status, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Device_Status eslGetDeviceStatus err: " << *pErrCode << std::endl;
  if(!eslib.eslCloseScanner(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Device_Status eslCloseScanner err: " << *pErrCode << std::endl;
  }
  if(!eslib.eslFree(instance, pErrCode)){
   std::cout << "[ERROR]SCN_Get_Device_Status eslFree err: " << *pErrCode << std::endl;
  }
  return FALSE;
 }
 DISPLAY_DEVICE_STATUS(status);
 if(!eslib.eslCloseScanner(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Device_Status eslCloseScanner err: " << *pErrCode << std::endl;
  return FALSE;
 }
 if(!eslib.eslFree(instance, pErrCode)){
  std::cout << "[ERROR]SCN_Get_Device_Status eslFree err: " << *pErrCode << std::endl;
  return FALSE;
 }
 return TRUE;
}
DWORD SCAN_STORE_SAVE_Default(const char* device_name)
{
 DWORD instance = 0;
 DWORD err = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  ConnectInfo scanner = {CT_DEFAULT};
  memcpy(scanner.deviceName, device_name, strlen(device_name)+1);
  ret = eslib.eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   EslParamInfoBasic info_params;
   info_params.type = ESL_PARAM_INFO_BASIC;
   info_params.size = sizeof(info_params);
   ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&info_params, &err);
   std::cout << "[INFO]Serial No: " << info_params.serialNumber << std::endl;
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
   }
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, &err);
   }
   DWORD status = 0;
   ret = eslib.eslGetDeviceStatus(instance, &status, &err);
   DISPLAY_DEVICE_STATUS(status);
   ret = eslib.eslCloseScanner(instance, &err);
  }
  eslib.eslFree(instance, &err);
 }
 return err;
}
DWORD SCAN_SAVE_JPEG(const char* device_name)
{
 DWORD instance = 0;
 DWORD err = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  ConnectInfo scanner = {CT_DEFAULT};
  memcpy(scanner.deviceName, device_name, strlen(device_name)+1);
  ret = eslib.eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   EslParamScanExV1 scan_params;
   scan_params.type = ESL_PARAM_SCAN_EX_V1;
   scan_params.size = sizeof(scan_params);
   ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&scan_params, &err);
   if (ret) {
    scan_params.docSource = SRC_FLATBED;
    scan_params.imgType = IT_COLOR;
    scan_params.resolution = 300;
    scan_params.docSize = DS_A4;
    scan_params.docRotate = DR_NONE;
    scan_params.brightness = 0;
    scan_params.contrast = 0;
    scan_params.threshold = 128;
    scan_params.colorFilter = CF_NONE;
    scan_params.numScan = 0;
    scan_params.optDoubleFeedDetect = DFD_NONE;
    scan_params.optBlankPageSkip = BPS_NONE;
    scan_params.skewCorrect = SC_EDGE;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&scan_params, &err);
   }
   EslParamSaveBasic save_params;
   save_params.type = ESL_PARAM_SAVE_BASIC;
   save_params.size = sizeof(save_params);
   if (ret) {
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&save_params, &err);
   }
   if (ret) {
    save_params.fileFormat = FF_JPEG;
    strncpy((char *)save_params.filePath, ".", sizeof(save_params.filePath));
    strncpy((char *)save_params.fileNamePrefix, "img", sizeof(save_params.fileNamePrefix));
    save_params.fileNumStartCount = 1;
    save_params.numPageStart = 0;
    save_params.numPageEnd = 0;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&save_params, &err);
   }
   EslParamSaveJPEG jpeg_params;
   jpeg_params.type = ESL_PARAM_SAVE_JPEG;
   jpeg_params.size = sizeof(jpeg_params);
   if (ret) {
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&jpeg_params, &err);
   }
   if (ret) {
    jpeg_params.imgQuality = 90;
    jpeg_params.encProgressive = FALSE;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&jpeg_params, &err);
   }
   EslParamSaveTIFF tiff_params;
   tiff_params.type = ESL_PARAM_SAVE_TIFF;
   tiff_params.size = sizeof(tiff_params);
   if (ret) {
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&tiff_params, &err);
   }
   if (ret) {
    tiff_params.compMono = TC_NONE;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&tiff_params, &err);
   }
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
   }
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, &err);
   }
   ret = eslib.eslCloseScanner(instance, &err);
  }
  eslib.eslFree(instance, &err);
 }
 return err;
}
DWORD SCAN_SAVE_PDF(const char* device_name)
{
 DWORD instance = 0;
 DWORD err = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  ConnectInfo scanner = {CT_DEFAULT};
  memcpy(scanner.deviceName, device_name, strlen(device_name)+1);
  ret = eslib.eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   EslParamScanExV1 scan_params;
   scan_params.type = ESL_PARAM_SCAN_BASIC;
   scan_params.size = sizeof(scan_params);
   ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&scan_params, &err);
   if (ret) {
    scan_params.docSource = SRC_AUTO;
    scan_params.imgType = IT_COLOR;
    scan_params.resolution = 300;
    scan_params.docSize = DS_A4;
    scan_params.docRotate = DR_AUTO;
    scan_params.brightness = 0;
    scan_params.contrast = 0;
    scan_params.threshold = 110;
    scan_params.colorFilter = CF_NONE;
    scan_params.numScan = 5;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&scan_params, &err);
   }
   EslParamSaveBasic save_params;
   save_params.type = ESL_PARAM_SAVE_BASIC;
   save_params.size = sizeof(save_params);
   if (ret) {
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&save_params, &err);
   }
   if (ret) {
    save_params.fileFormat = FF_PDF;
    strncpy((char *)save_params.filePath, ".", sizeof(save_params.filePath));
    strncpy((char *)save_params.fileNamePrefix, "img", sizeof(save_params.fileNamePrefix));
    save_params.fileNumStartCount = 1;
    save_params.numPageStart = 0;
    save_params.numPageEnd = 0;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&save_params, &err);
   }
   if (ret) {
    ret = eslib.eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
    ret = eslib.eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, &err);
   }
   ret = eslib.eslCloseScanner(instance, &err);
  }
  eslib.eslFree(instance, &err);
 }
 return err;
}
DWORD SCAN_SAVE_OFD(const char* device_name)
{
 DWORD instance = 0;
 DWORD err = 0;
 CEslStub eslib(NULL);
 BOOL ret = eslib.eslInit(&instance, LICENSE_KEY, &err);
 if (ret) {
  std::cout << "[INFO]Open Scanner\n" << std::endl;
  ConnectInfo scanner = {CT_DEFAULT};
  memcpy(scanner.deviceName, device_name, strlen(device_name)+1);
  ret = eslib.eslOpenScanner(instance, &scanner, &err);
  if (ret) {
   std::cout << "[INFO]Update Scan Basic parameters\n" << std::endl;
   EslParamScanExV1 scan_params;
   scan_params.type = ESL_PARAM_SCAN_BASIC;
   scan_params.size = sizeof(scan_params);
   std::cout << "[INFO]Get default parameters\n" << std::endl;
   ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&scan_params, &err);
   if (ret) {
    std::cout << "[INFO]Change some parameters...\n" << std::endl;
    scan_params.docSource = SRC_AUTO;
    scan_params.imgType = IT_COLOR;
    scan_params.resolution = 200;
    scan_params.docSize = DS_A4;
    scan_params.docRotate = DR_AUTO;
    scan_params.brightness = 0;
    scan_params.contrast = 0;
    scan_params.threshold = 110;
    scan_params.colorFilter = CF_NONE;
    scan_params.numScan = 5;
    std::cout << "[INFO]Set parameters\n" << std::endl;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&scan_params, &err);
   }
   std::cout << "[INFO]Update Save Basic parameters\n" << std::endl;
   EslParamSaveBasic save_params;
   save_params.type = ESL_PARAM_SAVE_BASIC;
   save_params.size = sizeof(save_params);
   if (ret) {
    std::cout << "[INFO]Get default parameters\n" << std::endl;
    ret = eslib.eslCtrlParameter(instance, POT_GET_DEFAULT, (pEslParamHdr)&save_params, &err);
   }
   std::cout << "[INFO]Get default parameters ret = " << ret << std::endl;
   if (ret) {
    std::cout << "[INFO]Change some parameters...\n" << std::endl;
    save_params.fileFormat = FF_OFD;
    std::cout << "[INFO]save_params.fileFormat = " << save_params.fileFormat << std::endl;
    strncpy((char *)save_params.filePath, ".", sizeof(save_params.filePath));
    std::cout << "[INFO]save_params.filePath = " << save_params.filePath << std::endl;
    std::cout << "[INFO]sizeof(save_params.filePath) = " << sizeof(save_params.filePath) << std::endl;
    strncpy((char *)save_params.fileNamePrefix, "ofd_output", sizeof(save_params.fileNamePrefix));
    save_params.fileNumStartCount = 1;
    save_params.numPageStart = 0;
    save_params.numPageEnd = 0;
    ret = eslib.eslCtrlParameter(instance, POT_SET, (pEslParamHdr)&save_params, &err);
   }
   if (ret) {
    std::cout << "[INFO]Scan start(Scan and Save)\n" << std::endl;
    ret = eslib.eslExecute(instance, ET_SCAN_AND_STORE, eslCallback, NULL, &err);
    ret = eslib.eslExecute(instance, ET_SAVE_STORED_IMAGE, eslCallback, NULL, &err);
   }
   ret = eslib.eslCloseScanner(instance, &err);
  }
  eslib.eslFree(instance, &err);
 }
 return err;
}
int APIENTRY main(int argc, char *argv[])
{
 char * device_name;
 DWORD err = 0;
 int i = 1;
 connectionMethod connection_method = CM_USB;
 if (argc > MIN_ARGUMENTS){
  if (Parameter_Check(argv[i+1], CO_DEVICEID, &err)){
   size_t ip_prefix_length = strlen("IP:");
   size_t adjust_length = 0;
   if (strncmp(argv[i+1], "IP:", ip_prefix_length) == 0){
    adjust_length = ip_prefix_length;
    connection_method = CM_NETWORK;
   }
   device_name = (char*)malloc(strlen(argv[i+1]) - adjust_length + 1);
   memcpy(device_name, argv[i+1] + adjust_length, strlen(argv[i+1]) - adjust_length + 1);
   if(strcmp(argv[i], OPTION_SCAN) == 0 || strcmp(argv[i], OPTION_SCAN_S) == 0){
    std::cout << "--scan option." << std::endl;
    if(!SCAN_SAVE(device_name, argc, argv, connection_method, &err)){
     std::cout << "Scan error." << std::endl;
    }
   }else if(strcmp(argv[i], OPTION_GET_STATUS) == 0 || strcmp(argv[i], OPTION_GET_STATUS_S) == 0){
    std::cout << "--get-status option." << std::endl;
    if(!SCN_Get_Device_Status(device_name, connection_method, &err)){
     std::cout << "Get device status error." << std::endl;
    }
   }else if(strcmp(argv[i], OPTION_GET_SLEEPTIMER) == 0){
    std::cout << "--get-sleeptimer option." << std::endl;
    INT select = 0;
    if (SCN_Get_Setting_Parameter(device_name, SP_SLEEP_TIMER, &select, connection_method, &err)){
     std::cout << "sleeptimer setting for " << select << std::endl;
    }else{
     std::cout << "sleeptimer setting error" << std::endl;
    }
   }else if(strcmp(argv[i], OPTION_SET_SLEEPTIMER) == 0){
    std::cout << "--set-sleeptimer option." << std::endl;
    if (Parameter_Check(argv[i+2], CO_VALUE, &err)){
     INT setparam = atoi(argv[i+2]);
     if(SCN_Set_Setting_Parameter(device_name, SP_SLEEP_TIMER, setparam, connection_method, &err)){
      std::cout << "sleeptimer set success param: " << setparam << std::endl;
     }else{
      std::cout << "sleeptimer set error: " << std::endl;
     }
    }else{
     std::cout << "Parameter error. The value to be set is not a number." << std::endl;
     std::cout << "example: ./sdksample --set-sleeptimer 30(minute)" << std::endl;
     err = 1;
    }
   }else if(strcmp(argv[i], OPTION_GET_AUTOPWOFF) == 0){
    std::cout << "--get-autopwoff option." << std::endl;
    INT select = 0;
    if (SCN_Get_Setting_Parameter(device_name, SP_POWER_OFF_TIME, &select, connection_method, &err)){
     std::cout << "auto power off setting for " << select << std::endl;
    }else{
     std::cout << "auto power off setting error." << std::endl;
    }
   }else if(strcmp(argv[i], OPTION_SET_AUTOPWOFF) == 0){
    std::cout << "--set-autopwoff option." << std::endl;
    if (Parameter_Check(argv[i+2], CO_VALUE, &err)){
     INT setparam = atoi(argv[i+2]);
     if(SCN_Set_Setting_Parameter(device_name, SP_POWER_OFF_TIME, setparam, connection_method, &err)){
      std::cout << "auto power off set success param: " << setparam << std::endl;
     }else{
      std::cout << "auto power off set error: " << std::endl;
     }
    }else{
     std::cout << "Parameter error. The value to be set is not a number." << std::endl;
     std::cout << "example: ./sdksample --set-sleeptimer 30(minute)" << std::endl;
     err = 1;
    }
   }else {
    std::cout << "ERROR : Option format invalid." << std::endl;
    std::cout << "Options begin with one of the following." << std::endl;
    std::cout << OPTION_SCAN << "(" << OPTION_SCAN_S << ")" << std::endl;
    std::cout << OPTION_GET_STATUS << "(" << OPTION_GET_STATUS_S << ")" << std::endl;
    std::cout << OPTION_GET_SLEEPTIMER << std::endl;
    std::cout << OPTION_SET_SLEEPTIMER << std::endl;
    std::cout << OPTION_GET_AUTOPWOFF << std::endl;
    std::cout << OPTION_SET_AUTOPWOFF << std::endl;
    err = 1;
   }
  }else{
   std::cout << "ERROR : DeviceID format invalid." << std::endl;
   err = 1;
  }
 }else{
  std::cout << "ERROR : Argument error." << std::endl;
  std::cout << "ERROR : Specify [option] and [DeviceID] as follows." << std::endl;
  std::cout << "./sdksample [option(--scan, etc.)] [DeviceID]" << std::endl;
  err = 1;
 }
 free(device_name);
 return err;
}
void DISPLAY_DEVICE_STATUS(DWORD Code)
{
 switch (Code) {
 case ESL_STAT_READY:
  std::cout << "[INFO]ESL_STAT_READY" << std::endl;
  break;
 case ESL_STAT_ERR_COVER_OPEN:
  std::cout << "[ERROR]ESL_STAT_ERR_COVER_OPEN" << std::endl;
  break;
 case ESL_STAT_ERR_PAPER_JAM:
  std::cout << "[ERROR]ESL_STAT_ERR_PAPER_JAM" << std::endl;
  break;
 case ESL_STAT_ERR_PAPER_EMPTY:
  std::cout << "[ERROR]ESL_STAT_ERR_PAPER_EMPTY" << std::endl;
  break;
 case ESL_STAT_ERR_FATAL:
  std::cout << "[ERROR]ESL_STAT_ERR_FATAL" << std::endl;
  break;
 case ESL_STAT_ERR_LAMP_TIME_FATAL:
  std::cout << "[ERROR]ESL_STAT_ERR_LAMP_TIME_FATAL" << std::endl;
  break;
 case ESL_STAT_ERR_CR_LOCK:
  std::cout << "[ERROR]ESL_STAT_ERR_CR_LOCK" << std::endl;
  break;
 case ESL_STAT_ERR_DOUBLE_FEED:
  std::cout << "[ERROR]ESL_STAT_ERR_DOUBLE_FEED" << std::endl;
  break;
 case ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE:
  std::cout << "[ERROR]ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE" << std::endl;
  break;
 case ESL_STAT_ERR_LOW_BATTERY:
  std::cout << "[ERROR]ESL_STAT_ERR_LOW_BATTERY" << std::endl;
  break;
 case ESL_STAT_ERR_CARRIER_SHEET_SENSOR:
  std::cout << "[ERROR]ESL_STAT_ERR_CARRIER_SHEET_SENSOR" << std::endl;
  break;
 case ESL_STAT_ERR_EDGE_TRACKING_SENSOR:
  std::cout << "[ERROR]ESL_STAT_ERR_EDGE_TRACKING_SENSOR" << std::endl;
  break;
 case ESL_STAT_ERR_PAPER_PROTECTION:
  std::cout << "[ERROR]ESL_STAT_ERR_PAPER_PROTECTION" << std::endl;
  break;
 case ESL_STAT_ERR_SEPARATION_LEVER:
  std::cout << "[ERROR]ESL_STAT_ERR_SEPARATION_LEVER" << std::endl;
  break;
 case ESL_STAT_ERR_POSE:
  std::cout << "[ERROR]ESL_STAT_ERR_POSE" << std::endl;
  break;
 case ESL_STAT_ERR_GAP_SENSOR:
  std::cout << "[ERROR]ESL_STAT_ERR_GAP_SENSOR" << std::endl;
  break;
 case ESL_STAT_ERR_UNKNOWN:
  std::cout << "[ERROR]ESL_STAT_ERR_UNKNOWN" << std::endl;
  break;
 default:
  std::cout << "[ERROR]Unknown: " << Code << std::endl;
 }
}
