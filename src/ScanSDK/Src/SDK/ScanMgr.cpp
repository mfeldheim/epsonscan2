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
//  ScanMgr.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "ScanMgr.h"
#include <DbgLog.h>
#define SDI_TRACE_LOG(message,...) \
        AfxGetLog()->MessageLog(ENUM_LOG_LEVEL::LogLevelTrace,__FUNCTION__,__FILE__,__LINE__, message, ##__VA_ARGS__ )
extern HMODULE g_hModule;
BOOL CALLBACK scanstatusCallback(EslCBDataScanStatus* scanstatus, PVOID pPrivate)
{
 CScanMgr* pScanMgr = (CScanMgr*)pPrivate;
 if (pScanMgr) {
  return pScanMgr->sendAppCallbackScanStatus(scanstatus);
 }
 return FALSE;
}
BOOL CALLBACK imagefileCallback(EslCBDImageFile* imagefile, PVOID pPrivate)
{
 CScanMgr* pScanMgr = (CScanMgr*)pPrivate;
 if (pScanMgr) {
  return pScanMgr->sendAppCallbackImageFile(imagefile);
 }
 return FALSE;
}
CScanMgr::CScanMgr(void) :
m_ShowIndicators(TRUE),
m_ColorSlipReduction(FALSE),
m_pCbFunc(NULL),
m_pPrivate(NULL),
m_sv(NULL)
{
}
CScanMgr::~CScanMgr(void)
{
 SDI_TRACE_LOG("CScanMgr::~CScanMgr");
 if(m_sv->driver){
        m_sv->SDIScannerDriver_DisposePtr_(m_sv->driver);
  SDI_TRACE_LOG("[INFO]Dispose OK");
        m_sv->driver = nullptr;
    }
 if(m_sv){
  m_sv->Terminate();
  delete m_sv;
        m_sv = NULL;
 }
}
void CScanMgr::free(void)
{
 DeviceList::device_list.clear();
    DeviceList::manu_network_device_list.clear();
}
DWORD CScanMgr::openScanner(const ConnectInfo* pScanner)
{
 SDI_TRACE_LOG("openScannerr");
 m_sv = new Supervisor();
 if(!m_sv){
  SDI_TRACE_LOG("[ERROR]m_sv is null");
        return ESL_ERR_GENERAL;
 }
 SDIDeviceInfo devInfo;
 DWORD err = ESL_SUCCESS;
 m_sv->SetUp();
 DeviceList* finder = new DeviceList();
    if(finder == NULL){
  SDI_TRACE_LOG("[ERROR]An unexpected error occurred. Epson Scan 2 will close.");
        return ESL_ERR_GENERAL;
    }
 SDI_TRACE_LOG("[INFO]Connect Device : %s", (const char*)pScanner->deviceName);
 switch (pScanner->connectType) {
 case CT_DEFAULT:
 case CT_LOCAL:
  SDI_TRACE_LOG("[INFO]ConnectType : CT_LOCAL");
  devInfo = finder->list((const char*)pScanner->deviceName);
  if(devInfo.displayName[0] == '\0'){
   m_sv->m_LastError = kSDIErrorDeviceNotFound;
   delete finder;
      finder = NULL;
   return ESL_ERR_OPEN_FAIL;
  }else {
   SDI_TRACE_LOG("/////////USB DEVICE Information//////////");
   SDI_TRACE_LOG("[INFO]displayName : %s", devInfo.displayName);
   SDI_TRACE_LOG("[INFO]modelID : %d", devInfo.modelID);
   SDI_TRACE_LOG("[INFO]productID : %d", devInfo.productID);
  }
  break;
 case CT_NET_IPV4:
  SDI_TRACE_LOG("[INFO]ConnectType : CT_NET_IPV4");
  devInfo = finder->list((const char*)pScanner->networkAddress, true);
  if(devInfo.ipAddress[0] != '\0'){
   SDI_TRACE_LOG("/////////Network DEVICE Information//////////");
   SDI_TRACE_LOG("[INFO]ipAddress : %s", devInfo.ipAddress);
   SDI_TRACE_LOG("[INFO]modelID : %d", devInfo.modelID);
   SDI_TRACE_LOG("[INFO]productID : %d", devInfo.productID);
  }else {
   m_sv->m_LastError = kSDIErrorDeviceNotFound;
   delete finder;
      finder = NULL;
   return ESL_ERR_OPEN_FAIL;
  }
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  delete finder;
     finder = NULL;
  return ESL_ERR_INVALID_PARAM;
 }
 delete finder;
    finder = NULL;
    m_sv->SDIScannerDriver_CreatePtr_(&m_sv->driver, &devInfo, nullptr, nullptr);
    SDI_TRACE_LOG("[INFO]Create OK", devInfo.ipAddress);
    if(m_sv->driver == nullptr){
  SDI_TRACE_LOG("[ERROR]driver is null");
        assert(false);
    }
    m_sv->m_LastError = m_sv->SDIScannerDriver_OpenPtr_(m_sv->driver);
    if(m_sv->m_LastError != kSDIErrorNone){
  SDI_TRACE_LOG("[ERROR]ESL_ERR_OPEN_FAIL");
        err = ESL_ERR_OPEN_FAIL;
    } else {
        err = ESL_SUCCESS;
    }
 this->loadScanDefault();
 this->loadDefault();
 return err;
}
void CScanMgr::closeScanner(void)
{
 SDI_TRACE_LOG("closeScanner");
 this->m_pCbFunc = NULL;
 this->m_pPrivate = NULL;
    if(m_sv->driver){
        m_sv->SDIScannerDriver_ClosePtr_(m_sv->driver);
  m_sv->SDIScannerDriver_DisposePtr_(m_sv->driver);
  m_sv->driver = nullptr;
  SDI_TRACE_LOG("[INFO]Close OK");
    }else {
  SDI_TRACE_LOG("[ERROR]driver is null");
 }
}
DWORD CScanMgr::ctrlParameter(const eParamOpType OpType, EslParamHdr* pParam)
{
 SDI_TRACE_LOG("ctrlParameter");
 DWORD err = ESL_SUCCESS;
 switch (OpType) {
 case POT_SET:
  err = this->setParameter(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]setParameter failed");
  }
  break;
 case POT_GET_CURRENT:
  err = this->getCurrentParameter(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]getCurrentParameter failed");
  }
  break;
 case POT_GET_DEFAULT:
  err = this->getDefaultParameter(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]getDefaultParameter failed");
  }
  break;
 }
 return err;
}
DWORD CScanMgr::execute(const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate)
{
 SDI_TRACE_LOG("execute");
 m_execType = ExecType;
 DWORD err = ESL_SUCCESS;
 m_pCbFunc = pCbFunc;
 SDI_TRACE_LOG("[INFO]Callback function pointer set");
 m_pPrivate = pPrivate;
 if (m_pCbFunc == NULL || m_pPrivate == NULL) {
  SDI_TRACE_LOG("[INFO]Callback function pointer is not set");
 }
 m_sv->setCallback(CBDT_STATUS_SCAN, (PVOID)scanstatusCallback, this);
 m_sv->setCallback(CBDT_IMAGE_FILE, (PVOID)imagefileCallback, this);
 switch (ExecType) {
 case ET_SCAN_AND_SAVE:
 case ET_SCAN_AND_STORE:
  err = this->execScan(ExecType);
  break;
 case ET_SAVE_STORED_IMAGE:
 case ET_GET_STORED_IMAGE:
  err = this->execSave(ExecType);
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  err = ESL_ERR_INVALID_PARAM;
 }
 this->showEslError(err);
 return err;
}
void CScanMgr::setSDKDefault(void)
{
 SDI_TRACE_LOG("setSDKDefault");
 m_sv->device_data.AutomaticFeedingMode.select = 0;
 m_sv->device_data.AFMTimeout.select = 0;
 m_sv->device_data.Add_Pages = 0;
 m_sv->device_data.ScanArea.AutoSize.select = 1;
 m_sv->device_data.BackgroundColor.select = 1;
 m_sv->device_data.BackgroundRemoval.select = 0;
 m_sv->device_data.BlankPageSkipKey.select = 0;
 m_sv->device_data.BlankPageSkipLevelKey.select = 10;
 m_sv->device_data.Brightness.select = 0;
 m_sv->device_data.ColorType.select = 0;
 m_sv->device_data.Contrast.select = 0;
 m_sv->device_data.DNShow_LongPaperWarning_dialog = 0;
 m_sv->device_data.DNShow_PlasticCard_dialog = 0;
 m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select = 1;
 m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionAreaLength.select = 1550;
 m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionAreaMin.select = 0;
 m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select = 0;
 m_sv->device_data.DropoutColor.select = 0;
 m_sv->device_data.DuplexType.select = 1;
 m_sv->device_data.FileName_Counter = 0;
 m_sv->device_data.FileName_OverWrite = 0;
 m_sv->device_data.Prefix = "img";
 m_sv->device_data.ScanArea.FixedSize = (DocumentSize)0;
    m_sv->device_data.Folder = 101;
 m_sv->device_data.FunctionalUnit.select = 0;
 m_sv->device_data.FunctionalUnit_Auto = 0;
 m_sv->device_data.Gamma.select = 22;
    m_sv->device_data.ImageFormatSettings.ImageFormat.select = 6;
 m_sv->device_data.ImageOption = 0;
 m_sv->device_data.ImageFormatSettings.JpegQuality.select = 80;
 m_sv->device_data.ImageFormatSettings.JpegQuality_forJPEG = 80;
 m_sv->device_data.ImageFormatSettings.JpegQuality_forPDF = 30;
 m_sv->device_data.ImageFormatSettings.TiffCompression.select = 0;
 m_sv->device_data.ImageFormatSettings.MultiTiffEnabled.select = 0;
 m_sv->device_data.NearDurationAlert = 0;
 m_sv->device_data.Orientation.select = 0;
 m_sv->device_data.OverDurationAlert = 0;
    m_sv->device_data.ImageFormatSettings.PDFImgFormatOption.AllPage = 1;
    m_sv->device_data.ImageFormatSettings.PDFImgFormatOption.page = 1;
 m_sv->device_data.PagesTobeScanned.select = 0;
 m_sv->device_data.PaperDeskew.select = 1;
 m_sv->device_data.ScanArea.PaperEndDetection.select = 0;
 m_sv->device_data.ScanArea.PaperEndDetectionMemory = 0;
 m_sv->device_data.Resolution.select = 200;
 m_sv->device_data.ScanArea.ScanAreaHeight.select = 2280;
 m_sv->device_data.ScanArea.ScanAreaOffsetX.select = 0;
 m_sv->device_data.ScanArea.ScanAreaOffsetY.select = 0;
 m_sv->device_data.ScanArea.ScanAreaWidth.select = 2280;
 m_sv->device_data.Threshold.select = 0;
 m_sv->device_data.TransferCompression.select = 1;
    m_sv->device_data.UserDefinePath = ".";
 m_sv->device_data.ScanArea.UserDefine_Width = 0;
 m_sv->device_data.ScanArea.UserDefine_Length = 0;
 m_sv->device_data.ImageFormatSettings.JpegProgressive.select = 0;
 m_sv->device_data.textEnhance.select = 0;
 if(m_sv->device_data.Folder == USER_DEFINE){
        m_sv->device_data.SelectPath = m_sv->device_data.UserDefinePath;
    }
}
BOOL CScanMgr::getSettingParameter(const eSpecifiedParameter SpecifiedParameter, INT* select){
 BOOL ret = TRUE;
 SDI_TRACE_LOG("[INFO]getSettingParameter");
 m_sv->Get_All_Value();
 switch (SpecifiedParameter)
 {
 case SP_SLEEP_TIMER:
  *select = m_sv->device_data.SleepTime.select;
  SDI_TRACE_LOG("[INFO]getSettingParameter select = %d", m_sv->device_data.SleepTime.select);
  break;
 case SP_POWER_OFF_TIME:
  *select = m_sv->device_data.AutoPowerOffTime.select;
  SDI_TRACE_LOG("[INFO]getSettingParameter select = %d", m_sv->device_data.AutoPowerOffTime.select);
  break;
 default:
  SDI_TRACE_LOG("[ERROR]SpecifiedParameter Error.");
  ret = FALSE;
  break;
 }
 return ret;
}
BOOL CScanMgr::setSettingParameter(const eSpecifiedParameter SpecifiedParameter, const INT setparam){
 BOOL ret = TRUE;
 BOOL parameter_exist = FALSE;
 SDI_TRACE_LOG("[INFO]setSettingParameter");
 m_sv->Get_All_Value();
 switch (SpecifiedParameter)
 {
 case SP_SLEEP_TIMER:
  if (m_sv->device_data.SleepTime.capability.minValue <= setparam <= m_sv->device_data.SleepTime.capability.maxValue){
   m_sv->device_data.SleepTime.select = setparam;
   parameter_exist = TRUE;
   SDI_TRACE_LOG("[INFO]setSettingParameter SleepTime set: %d", m_sv->device_data.SleepTime.select);
  }
  break;
 case SP_POWER_OFF_TIME:
  int i;
  if (m_sv->device_data.AutoPowerOffTime.capability.capabilityType == kSDICapabilitTypeList){
   for (i = 0; i < m_sv->device_data.AutoPowerOffTime.capability.countOfList; i++){
    if (setparam == m_sv->device_data.AutoPowerOffTime.capability.list[i]){
     m_sv->device_data.AutoPowerOffTime.select = setparam;
     parameter_exist = TRUE;
     SDI_TRACE_LOG("[INFO]setSettingParameter AutoPowerOffTime set: %d", m_sv->device_data.AutoPowerOffTime.select);
     break;
    }
   }
  }else{
   if (m_sv->device_data.AutoPowerOffTime.capability.minValue <= setparam <= m_sv->device_data.AutoPowerOffTime.capability.maxValue){
    m_sv->device_data.AutoPowerOffTime.select = setparam;
    parameter_exist = TRUE;
    SDI_TRACE_LOG("[INFO]setSettingParameter AutoPowerOffTime set: %d", m_sv->device_data.AutoPowerOffTime.select);
   }
  }
  break;
 default:
  ret = FALSE;
  break;
 }
 if(parameter_exist){
  m_sv->Set_All_Value();
 }else if(!ret){
  SDI_TRACE_LOG("[ERROR]setSettingParameter SpecifiedParameter:%d is an invalid parameter.", SpecifiedParameter);
 }else{
  ret = FALSE;
  SDI_TRACE_LOG("[ERROR]setSettingParameter setparam:%d is an invalid parameter.", setparam);
 }
 return ret;
}
void CScanMgr::loadScanDefault(void)
{
 SDI_TRACE_LOG("loadScanDefault");
 memset(&m_ParamScanDefault, 0, sizeof(EslParamScanExV1));
 this->setSDKDefault();
 m_sv->Get_All_Value();
 if(m_sv->device_data.FunctionalUnit.select == Auto){
  m_ParamScanDefault.docSource = SRC_AUTO;
 }else if(m_sv->device_data.FunctionalUnit.select == Flatbed){
  m_ParamScanDefault.docSource = SRC_FLATBED;
 }else if(m_sv->device_data.FunctionalUnit.select == ADF){
  if(m_sv->device_data.DuplexType.select == Single_Sided){
   m_ParamScanDefault.docSource = SRC_FEEDER_SIMPLEX;
  }else if(m_sv->device_data.DuplexType.select == Double_Sided){
   m_ParamScanDefault.docSource = SRC_FEEDER_DUPLEX;
  }
 }
 if(m_sv->device_data.ColorType.select == ColorTypeAuto){
  m_ParamScanDefault.imgType = IT_AUTO;
 }else if(m_sv->device_data.ColorType.select == ColorTypeRGB24){
  m_ParamScanDefault.imgType = IT_COLOR;
 }else if(m_sv->device_data.ColorType.select == ColorTypeMono8){
  m_ParamScanDefault.imgType = IT_GRAY;
 }else if(m_sv->device_data.ColorType.select == ColorTypeMono1){
  m_ParamScanDefault.imgType = IT_MONO;
 }
 m_ParamScanDefault.resolution = m_sv->device_data.Resolution.select;
 m_ParamScanDefault.docSize = DS_A4;
 m_ParamScanDefault.sizeUnit = SU_INCH;
 m_ParamScanDefault.sizeUser.bottom = 0;
 m_ParamScanDefault.sizeUser.left = 0;
 m_ParamScanDefault.sizeUser.right = 0;
 m_ParamScanDefault.sizeUser.top = 0;
 if(m_sv->device_data.Orientation.select == OrientationAuto){
  m_ParamScanDefault.docRotate = DR_AUTO;
 }else if(m_sv->device_data.Orientation.select == OrientationNone){
  m_ParamScanDefault.docRotate = DR_NONE;
 }else if(m_sv->device_data.Orientation.select == Orientation90){
  m_ParamScanDefault.docRotate = DR_R90;
 }else if(m_sv->device_data.Orientation.select == Orientation180){
  m_ParamScanDefault.docRotate = DR_R180;
 }else if(m_sv->device_data.Orientation.select == Orientation270){
  m_ParamScanDefault.docRotate = DR_R270;
 }
 m_ParamScanDefault.brightness = m_sv->device_data.Brightness.select * 10;
 m_ParamScanDefault.contrast = m_sv->device_data.Contrast.select * 10;
 m_ParamScanDefault.threshold = m_sv->device_data.Threshold.select;
 if(m_sv->device_data.DropoutColor.select == DropoutColorNone){
  m_ParamScanDefault.colorFilter = CF_NONE;
 }else if(m_sv->device_data.DropoutColor.select == DropoutColorRed){
  m_ParamScanDefault.colorFilter = CF_DROPOUT_RED;
 }else if(m_sv->device_data.DropoutColor.select == DropoutColorGreen){
  m_ParamScanDefault.colorFilter = CF_DROPOUT_GREEN;
 }else if(m_sv->device_data.DropoutColor.select == DropoutColorBlue){
  m_ParamScanDefault.colorFilter = CF_DROPOUT_BLUE;
 }
 m_ParamScanDefault.numScan = m_sv->device_data.PagesTobeScanned.select;
 if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select == false){
  m_ParamScanDefault.optDoubleFeedDetect = DFD_NONE;
 }else if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select == true){
  if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select == DoubleFeedDetectionLow){
   m_ParamScanDefault.optDoubleFeedDetect = DFD_LOW;
  }else if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select == DoubleFeedDetectionHigh){
   m_ParamScanDefault.optDoubleFeedDetect = DFD_HIGH;
  }
 }
 m_ParamScanDefault.optBlankPageSkip = BPS_NONE;
 if(m_sv->device_data.PaperDeskew.select == false){
  m_ParamScanDefault.skewCorrect = SC_NONE;
 }else if(m_sv->device_data.PaperDeskew.select == true){
  m_ParamScanDefault.skewCorrect = SC_EDGE;
 }
 if(m_sv->device_data.textEnhance.select == TextEnhanceNone){
  m_ParamScanDefault.docEnhance = DE_NONE;
 }else if(m_sv->device_data.textEnhance.select == TextEnhanceNormal){
  m_ParamScanDefault.docEnhance = DE_TET_STD;
 }else if(m_sv->device_data.textEnhance.select == TextEnhanceHigh){
  m_ParamScanDefault.docEnhance = DE_TET_HIGH;
 }
 memcpy_s(&m_ParamScanCurrent, sizeof(EslParamScanExV1), &m_ParamScanDefault, sizeof(EslParamScanExV1));
}
void CScanMgr::loadDefault(void)
{
 SDI_TRACE_LOG("loadDefault");
 memset(&m_ParamSaveDefault, 0, sizeof(EslParamSaveBasic));
 memset(&m_ParamJpegDefault, 0, sizeof(EslParamSaveJPEG));
 memset(&m_ParamTiffDefault, 0, sizeof(EslParamSaveTIFF));
 m_ParamSaveDefault.type = ESL_PARAM_SAVE_BASIC;
 m_ParamSaveDefault.size = sizeof(EslParamSaveBasic);
 m_ParamSaveDefault.numPageStart = 0;
 m_ParamSaveDefault.numPageEnd = 0;
 m_ParamSaveDefault.fileFormat = FF_JPEG;
 memcpy_s(m_ParamSaveDefault.filePath, MAX_PATH, ".", strlen(".")+1);
 m_ParamSaveDefault.fileNameType = FN_PREFIX;
 memcpy_s(m_ParamSaveDefault.fileNamePrefix, 40, "image", strlen("image")+1);
 m_ParamSaveDefault.fileNumStartCount = 0;
 memcpy_s(&m_ParamSaveCurrent, sizeof(EslParamSaveBasic), &m_ParamSaveDefault, sizeof(EslParamSaveBasic));
 m_ParamJpegDefault.type = ESL_PARAM_SAVE_JPEG;
 m_ParamJpegDefault.size = sizeof(EslParamSaveJPEG);
 m_ParamJpegDefault.imgQuality = 80;
 m_ParamJpegDefault.encProgressive = FALSE;
 memcpy_s(&m_ParamJpegCurrent, sizeof(EslParamSaveJPEG), &m_ParamJpegDefault, sizeof(EslParamSaveJPEG));
 m_ParamTiffDefault.type = ESL_PARAM_SAVE_TIFF;
 m_ParamTiffDefault.size = sizeof(EslParamSaveTIFF);
 m_ParamTiffDefault.compMono = TC_NONE;
 memcpy_s(&m_ParamTiffCurrent, sizeof(EslParamSaveTIFF), &m_ParamTiffDefault, sizeof(EslParamSaveTIFF));
}
DWORD CScanMgr::setParameter(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("setParameter");
 DWORD err = ESL_SUCCESS;
 switch (pParam->type) {
 case ESL_PARAM_SCAN_BASIC:
 case ESL_PARAM_SCAN_EX_V1:
  err = this->setParamScan(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->setParamScan failed");
  }
  break;
 case ESL_PARAM_SAVE_BASIC:
 case ESL_PARAM_SAVE_JPEG:
 case ESL_PARAM_SAVE_TIFF:
  err = this->setParamSave(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->setParamSave failed");
  }
  break;
 default:
  SDI_TRACE_LOG("[ERROR]Invalid operation for this type of parameter struct");
  err = ESL_ERR_INVALID_OPERATION;
 }
 return err;
}
DWORD CScanMgr::getCurrentParameter(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getCurrentParameter");
 DWORD err = ESL_SUCCESS;
 switch (pParam->type) {
 case ESL_PARAM_SCAN_BASIC:
 case ESL_PARAM_SCAN_EX_V1:
  err = this->getCurrentParamScan(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getCurrentParamScan failed");
  }
  break;
 case ESL_PARAM_SAVE_BASIC:
 case ESL_PARAM_SAVE_JPEG:
 case ESL_PARAM_SAVE_TIFF:
  err = this->getCurrentParamSave(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getCurrentParamSave failed");
  }
  break;
 case ESL_PARAM_INFO_BASIC:
  err = this->getParamInfo(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getParamInfo failed");
  }
  break;
 }
 return err;
}
DWORD CScanMgr::getDefaultParameter(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getDefaultParameter");
 DWORD err = ESL_SUCCESS;
 switch (pParam->type) {
 case ESL_PARAM_SCAN_BASIC:
 case ESL_PARAM_SCAN_EX_V1:
  err = this->getDefaultParamScan(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getDefaultParamScan failed");
  }
  break;
 case ESL_PARAM_SAVE_BASIC:
 case ESL_PARAM_SAVE_JPEG:
 case ESL_PARAM_SAVE_TIFF:
  err = this->getDefaultParamSave(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getDefaultParamSaveBasic failed");
  }
  break;
 case ESL_PARAM_INFO_BASIC:
  err = this->getParamInfo(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]this->getParamInfo failed");
  }
  break;
 }
 return err;
}
DWORD CScanMgr::setParamScan(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("setParamScan");
 DWORD err = ESL_SUCCESS;
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 err = this->setScanCapabilities(pParam);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return err;
}
DWORD CScanMgr::getCurrentParamScan(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getCurrentParamScan");
 switch (pParam->type) {
 case ESL_PARAM_SCAN_BASIC:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SCAN_BASIC get");
  memcpy_s(pParam, sizeof(EslParamScanBasic), &m_ParamScanCurrent, sizeof(EslParamScanBasic));
  pParam->type = ESL_PARAM_SCAN_BASIC;
  pParam->size = sizeof(EslParamScanBasic);
  break;
 case ESL_PARAM_SCAN_EX_V1:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SCAN_EX_V1 get");
  memcpy_s(pParam, sizeof(EslParamScanExV1), &m_ParamScanCurrent, sizeof(EslParamScanExV1));
  pParam->type = ESL_PARAM_SCAN_EX_V1;
  pParam->size = sizeof(EslParamScanExV1);
  break;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::getDefaultParamScan(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getDefaultParamScan");
 switch (pParam->type) {
 case ESL_PARAM_SCAN_BASIC:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SCAN_BASIC get");
  memcpy_s(pParam, sizeof(EslParamScanBasic), &m_ParamScanDefault, sizeof(EslParamScanBasic));
  pParam->type = ESL_PARAM_SCAN_BASIC;
  pParam->size = sizeof(EslParamScanBasic);
  break;
 case ESL_PARAM_SCAN_EX_V1:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SCAN_EX_V1 get");
  memcpy_s(pParam, sizeof(EslParamScanExV1), &m_ParamScanDefault, sizeof(EslParamScanExV1));
  pParam->type = ESL_PARAM_SCAN_EX_V1;
  pParam->size = sizeof(EslParamScanExV1);
  break;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::setParamSave(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getDefaultParamScan");
 DWORD err = ESL_SUCCESS;
 err = this->setParam(pParam);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return err;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::getCurrentParamSave(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getCurrentParamSave");
 switch (pParam->type) {
 case ESL_PARAM_SAVE_BASIC:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_BASIC get");
  memcpy_s(pParam, sizeof(EslParamSaveBasic), &m_ParamSaveCurrent, sizeof(EslParamSaveBasic));
  pParam->type = ESL_PARAM_SAVE_BASIC;
  pParam->size = sizeof(EslParamSaveBasic);
  break;
 case ESL_PARAM_SAVE_JPEG:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_JPEG get");
  memcpy_s(pParam, sizeof(EslParamSaveJPEG), &m_ParamJpegCurrent, sizeof(EslParamSaveJPEG));
  break;
 case ESL_PARAM_SAVE_TIFF:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_TIFF get");
  memcpy_s(pParam, sizeof(EslParamSaveTIFF), &m_ParamTiffCurrent, sizeof(EslParamSaveTIFF));
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::getDefaultParamSave(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getDefaultParamSave");
 switch (pParam->type) {
 case ESL_PARAM_SAVE_BASIC:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_BASIC get");
  memcpy_s(pParam, sizeof(EslParamSaveBasic), &m_ParamSaveDefault, sizeof(EslParamSaveBasic));
  pParam->type = ESL_PARAM_SAVE_BASIC;
  pParam->size = sizeof(EslParamSaveBasic);
  break;
 case ESL_PARAM_SAVE_JPEG:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_JPEG get");
  memcpy_s(pParam, sizeof(EslParamSaveJPEG), &m_ParamJpegDefault, sizeof(EslParamSaveJPEG));
  break;
 case ESL_PARAM_SAVE_TIFF:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_SAVE_TIFF get");
  memcpy_s(pParam, sizeof(EslParamSaveTIFF), &m_ParamTiffDefault, sizeof(EslParamSaveTIFF));
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::getParamInfo(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getParamInfo");
 DWORD err = ESL_SUCCESS;
 switch (pParam->type) {
 case ESL_PARAM_INFO_BASIC:
  SDI_TRACE_LOG("[INFO]ESL_PARAM_INFO_BASIC get");
  err = this->getInfoCapabilities(pParam);
  if (err != ESL_SUCCESS) {
   SDI_TRACE_LOG("[ERROR]getInfoCapabilities is failed");
   return err;
  }
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::setScanCapabilities(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("setScanCapabilities");
 DWORD err = ESL_SUCCESS;
 EslParamScanExV1 param;
 memcpy_s(&param, sizeof(EslParamScanExV1), &m_ParamScanCurrent, sizeof(EslParamScanExV1));
 if (pParam->type == ESL_PARAM_SCAN_BASIC) {
  memcpy_s(&param, sizeof(EslParamScanExV1), pParam, sizeof(EslParamScanBasic));
 } else if (pParam->type == ESL_PARAM_SCAN_EX_V1) {
  memcpy_s(&param, sizeof(EslParamScanExV1), pParam, sizeof(EslParamScanExV1));
 } else {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 if (err == ESL_SUCCESS) {
  memcpy_s(&m_ParamScanCurrent, sizeof(EslParamScanExV1), &param, sizeof(EslParamScanExV1));
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::conversionSaveCapSDKtoSV(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("conversionSaveCapSDKtoSV");
 DWORD err = ESL_SUCCESS;
 EslParamSaveBasic param;
 memcpy_s(&param, sizeof(EslParamSaveBasic), &m_ParamSaveCurrent, sizeof(EslParamSaveBasic));
 if (pParam->type == ESL_PARAM_SAVE_BASIC) {
  memcpy_s(&param, sizeof(EslParamSaveBasic), pParam, sizeof(EslParamSaveBasic));
 } else {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 SDI_TRACE_LOG("[INFO]---------------------------");
 SDI_TRACE_LOG("[INFO]type: %d", param.type);
 SDI_TRACE_LOG("[INFO]size: %d", param.size);
 SDI_TRACE_LOG("[INFO]numPageStart: %d", param.numPageStart);
 SDI_TRACE_LOG("[INFO]numPageEnd: %d", param.numPageEnd);
 SDI_TRACE_LOG("[INFO]fileFormat: %d", param.fileFormat);
 SDI_TRACE_LOG("[INFO]filePath: %s", param.filePath);
 SDI_TRACE_LOG("[INFO]fileNameType: %d", param.fileNameType);
 SDI_TRACE_LOG("[INFO]fileNamePrefix: %s", param.fileNamePrefix);
 SDI_TRACE_LOG("[INFO]fileNumStartCount: %d", param.fileNumStartCount);
 SDI_TRACE_LOG("[INFO]---------------------------");
 m_sv->m_numPageStart = param.numPageStart;
 m_sv->m_numPageEnd = param.numPageEnd;
 if(param.fileFormat == FF_BMP){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatPNM;
 }else if(param.fileFormat == FF_JPEG){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatJPEG;
 }else if(param.fileFormat == FF_TIFF){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatTIFF;
 }else if(param.fileFormat == FF_MULTITIFF){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatPNM;
        m_sv->device_data.ImageFormatSettings.MultiTiffEnabled.select = true;
 }else if(param.fileFormat == FF_PDF){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatColorJpegMonoRaw;
 }else if(param.fileFormat == FF_PNG){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatPNG;
 }else if(param.fileFormat == FF_OFD){
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatPNM;
  m_sv->device_data.ImageFormatSettings.OFDEnabled.select = true;
 }else{
  m_sv->device_data.ImageFormatSettings.ImageFormat.select = ImageFormatJPEG;
 }
 m_sv->device_data.SelectPath = m_sv->device_data.UserDefinePath = param.filePath;
 SDI_TRACE_LOG("[INFO]UserDefinePath: %s", m_sv->device_data.UserDefinePath.c_str());
 m_sv->device_data.Prefix = param.fileNamePrefix;
 m_sv->m_fileNumStartCount = param.fileNumStartCount;
 return ESL_SUCCESS;
}
DWORD CScanMgr::conversionJpegCapSDKtoSV(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("conversionJpegCapSDKtoSV");
 DWORD err = ESL_SUCCESS;
 EslParamSaveJPEG param;
 memcpy_s(&param, sizeof(EslParamSaveJPEG), &m_ParamJpegCurrent, sizeof(EslParamSaveJPEG));
 if (pParam->type == ESL_PARAM_SAVE_JPEG) {
  memcpy_s(&param, sizeof(EslParamSaveJPEG), pParam, sizeof(EslParamSaveJPEG));
 } else {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 SDI_TRACE_LOG("[INFO]-----------JPEG----------------");
 SDI_TRACE_LOG("[INFO]type: %d", param.type);
 SDI_TRACE_LOG("[INFO]size: %d", param.size);
 SDI_TRACE_LOG("[INFO]imgQuality: %d", param.imgQuality);
 SDI_TRACE_LOG("[INFO]encProgressive: %d", param.encProgressive);
 SDI_TRACE_LOG("[INFO]---------------------------");
 m_sv->device_data.ImageFormatSettings.JpegQuality_forJPEG = m_sv->device_data.ImageFormatSettings.JpegQuality.select = param.imgQuality;
 m_sv->device_data.ImageFormatSettings.JpegProgressive.select = param.encProgressive;
 return ESL_SUCCESS;
}
DWORD CScanMgr::conversionTiffCapSDKtoSV(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("conversionTiffCapSDKtoSV");
 DWORD err = ESL_SUCCESS;
 EslParamSaveTIFF param;
 memcpy_s(&param, sizeof(EslParamSaveTIFF), &m_ParamTiffCurrent, sizeof(EslParamSaveTIFF));
 if (pParam->type == ESL_PARAM_SAVE_TIFF) {
  memcpy_s(&param, sizeof(EslParamSaveTIFF), pParam, sizeof(EslParamSaveTIFF));
 } else {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 SDI_TRACE_LOG("[INFO]-----------TIFF----------------");
 SDI_TRACE_LOG("[INFO]type: %d", param.type);
 SDI_TRACE_LOG("[INFO]size: %d", param.size);
 SDI_TRACE_LOG("[INFO]compMono: %d", param.compMono);
 SDI_TRACE_LOG("[INFO]---------------------------");
 if(param.compMono == TC_NONE){
  m_sv->device_data.ImageFormatSettings.TiffCompression.select = TiffCompressionNone;
 }else if(param.compMono == TC_CCITT_G4){
  m_sv->device_data.ImageFormatSettings.TiffCompression.select = TiffCompressionCCITFAX4;
 }
 return ESL_SUCCESS;
}
DWORD CScanMgr::conversionScanCapSDKtoSV(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("conversionScanCapSDKtoSV");
 DWORD err = ESL_SUCCESS;
 EslParamScanExV1 param;
 memcpy_s(&param, sizeof(EslParamScanExV1), &m_ParamScanCurrent, sizeof(EslParamScanExV1));
 if (pParam->type == ESL_PARAM_SCAN_BASIC) {
  memcpy_s(&param, sizeof(EslParamScanExV1), pParam, sizeof(EslParamScanBasic));
 } else if (pParam->type == ESL_PARAM_SCAN_EX_V1) {
  memcpy_s(&param, sizeof(EslParamScanExV1), pParam, sizeof(EslParamScanExV1));
 } else {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 SDI_TRACE_LOG("[INFO]---------------------------");
 SDI_TRACE_LOG("[INFO]type: %d", param.type);
 SDI_TRACE_LOG("[INFO]size: %d", param.size);
 SDI_TRACE_LOG("[INFO]docSource: %d", param.docSource);
 SDI_TRACE_LOG("[INFO]imgType: %d", param.imgType);
 SDI_TRACE_LOG("[INFO]resolution: %d", param.resolution);
 SDI_TRACE_LOG("[INFO]docSize: %d", param.docSize);
 SDI_TRACE_LOG("[INFO]sizeUnit: %d", param.sizeUnit);
 SDI_TRACE_LOG("[INFO]sizeUser.left: %d", param.sizeUser.left);
 SDI_TRACE_LOG("[INFO]sizeUser.top: %d", param.sizeUser.top);
 SDI_TRACE_LOG("[INFO]sizeUser.right: %d", param.sizeUser.right);
 SDI_TRACE_LOG("[INFO]sizeUser.bottom: %d", param.sizeUser.bottom);
 SDI_TRACE_LOG("[INFO]docRotate: %d", param.docRotate);
 SDI_TRACE_LOG("[INFO]brightness: %d", param.brightness);
 SDI_TRACE_LOG("[INFO]contrast: %d", param.contrast);
 SDI_TRACE_LOG("[INFO]threshold: %d", param.threshold);
 SDI_TRACE_LOG("[INFO]colorFilter: %d", param.colorFilter);
 SDI_TRACE_LOG("[INFO]numScan: %d", param.numScan);
 SDI_TRACE_LOG("[INFO]optDoubleFeedDetect: %d", param.optDoubleFeedDetect);
 SDI_TRACE_LOG("[INFO]optBlankPageSkip: %d", param.optBlankPageSkip);
 SDI_TRACE_LOG("[INFO]skewCorrect: %d", param.skewCorrect);
 SDI_TRACE_LOG("[INFO]docEnhance: %d", param.docEnhance);
 SDI_TRACE_LOG("[INFO]---------------------------");
 int i;
 for(i = 0; i < m_sv->device_data.FunctionalUnit.capability.countOfList; i++){
  if(m_sv->device_data.FunctionalUnit.capability.list[i] == Auto && param.docSource == SRC_AUTO){
   m_sv->device_data.FunctionalUnit.select = Auto;
   break;
  }else if(m_sv->device_data.FunctionalUnit.capability.list[i] == Flatbed && param.docSource == SRC_FLATBED){
   m_sv->device_data.FunctionalUnit.select = Flatbed;
   break;
  }else if(m_sv->device_data.FunctionalUnit.capability.list[i] == ADF){
   int j;
   BOOL isExist = FALSE;
   for (j = 0; j < m_sv->device_data.DuplexType.capability.countOfAllList; j++){
    if(m_sv->device_data.DuplexType.capability.allList[j] == Single_Sided && param.docSource == SRC_FEEDER_SIMPLEX){
     m_sv->device_data.FunctionalUnit.select = ADF;
     m_sv->device_data.DuplexType.select = Single_Sided;
     isExist = TRUE;
     break;
    }else if(m_sv->device_data.DuplexType.capability.allList[j] == Double_Sided && param.docSource == SRC_FEEDER_DUPLEX){
     m_sv->device_data.FunctionalUnit.select = ADF;
     m_sv->device_data.DuplexType.select = Double_Sided;
     isExist = TRUE;
     break;
    }
   }
   if (isExist){
    break;
   }
  }
 }
 if(param.imgType == IT_AUTO){
  m_sv->device_data.ColorType.select = ColorTypeAuto;
 }else if(param.imgType == IT_COLOR){
  m_sv->device_data.ColorType.select = ColorTypeRGB24;
 }else if(param.imgType == IT_GRAY){
  m_sv->device_data.ColorType.select = ColorTypeMono8;
 }else if(param.imgType == IT_MONO){
  m_sv->device_data.ColorType.select = ColorTypeMono1;
 }else{
  m_sv->device_data.ColorType.select = ColorTypeMono1;
 }
 if (m_ParamSaveCurrent.fileFormat == FF_OFD){
  if(m_sv->device_data.Resolution.select < MIN_OFD_RESOLUTION){
   m_sv->device_data.Resolution.select = MIN_OFD_RESOLUTION;
  }else if(m_sv->device_data.Resolution.select > MAX_OFD_RESOLUTION){
   m_sv->device_data.Resolution.select = MAX_OFD_RESOLUTION;
  }
 }else{
  if(param.resolution < m_sv->device_data.Resolution.capability.minValue){
   m_sv->device_data.Resolution.select = m_sv->device_data.Resolution.capability.minValue;
  }else if(param.resolution > m_sv->device_data.Resolution.capability.maxValue){
   m_sv->device_data.Resolution.select = m_sv->device_data.Resolution.capability.maxValue;
  }else{
   m_sv->device_data.Resolution.select = param.resolution;
  }
 }
 this->StandardSizeToPixel(param.docSize, param.sizeUnit, param.sizeUser);
 if(param.docRotate == DR_AUTO){
  m_sv->device_data.Orientation.select = OrientationAuto;
 }else if(param.docRotate == DR_NONE){
  m_sv->device_data.Orientation.select = OrientationNone;
 }else if(param.docRotate == DR_R90){
  m_sv->device_data.Orientation.select = Orientation90;
 }else if(param.docRotate == DR_R180){
  m_sv->device_data.Orientation.select = Orientation180;
 }else if(param.docRotate == DR_R270){
  m_sv->device_data.Orientation.select = Orientation270;
 }
 if(param.brightness < MIN_IMAGE_QUALITY_VALUE){
  m_sv->device_data.Brightness.select = MIN_IMAGE_QUALITY_VALUE / 10;
 }else if(param.brightness > MAX_IMAGE_QUALITY_VALUE){
  m_sv->device_data.Brightness.select = MAX_IMAGE_QUALITY_VALUE / 10;
 }else{
  m_sv->device_data.Brightness.select = param.brightness / 10;
 }
 if(param.contrast < MIN_IMAGE_QUALITY_VALUE){
  m_sv->device_data.Contrast.select = MIN_IMAGE_QUALITY_VALUE / 10;
 }else if(param.contrast > MAX_IMAGE_QUALITY_VALUE){
  m_sv->device_data.Contrast.select = MAX_IMAGE_QUALITY_VALUE / 10;
 }else{
  m_sv->device_data.Contrast.select = param.contrast / 10;
 }
 if(param.threshold < MIN_THRESHOLD_VALUE){
  m_sv->device_data.Threshold.select = MIN_THRESHOLD_VALUE;
 }else if(param.threshold > MAX_THRESHOLD_VALUE){
  m_sv->device_data.Threshold.select = MAX_THRESHOLD_VALUE;
 }else{
  m_sv->device_data.Threshold.select = param.threshold;
 }
 if(param.colorFilter == CF_NONE){
  m_sv->device_data.DropoutColor.select = DropoutColorNone;
 }else if(param.colorFilter == CF_DROPOUT_RED){
  m_sv->device_data.DropoutColor.select = DropoutColorRed;
 }else if(param.colorFilter == CF_DROPOUT_GREEN){
  m_sv->device_data.DropoutColor.select = DropoutColorGreen;
 }else if(param.colorFilter == CF_DROPOUT_BLUE){
  m_sv->device_data.DropoutColor.select = DropoutColorBlue;
 }else{
  m_sv->device_data.DropoutColor.select = DropoutColorNone;
 }
 m_sv->device_data.PagesTobeScanned.select = param.numScan;
 for(i = 0; i < m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.capability.countOfList; i++){
  if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.capability.list[i] == false && param.optDoubleFeedDetect == DFD_NONE){
   m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select = false;
   break;
  }else if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.capability.list[i] == true){
   int j;
   BOOL isExist = FALSE;
   for (j = 0; j < m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.capability.countOfList; j++){
    if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.capability.list[j] == DoubleFeedDetectionLow && param.optDoubleFeedDetect == DFD_LOW){
     m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select = true;
     m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select = DoubleFeedDetectionLow;
     isExist = TRUE;
     break;
    }else if(m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.capability.list[j] == DoubleFeedDetectionHigh && param.optDoubleFeedDetect == DFD_HIGH){
     m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select = true;
     m_sv->device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select = DoubleFeedDetectionHigh;
     isExist = TRUE;
     break;
    }
   }
   if (isExist){
    break;
   }
  }
 }
 if (param.optBlankPageSkip == BPS_NONE){
  m_sv->device_data.BlankPageSkipKey.select = false;
 }else if(param.optBlankPageSkip == BPS_VERY_LOW){
  m_sv->device_data.BlankPageSkipKey.select = true;
  m_sv->device_data.BlankPageSkipLevelKey.select = 3;
 }else if(param.optBlankPageSkip == BPS_LOW){
  m_sv->device_data.BlankPageSkipKey.select = true;
  m_sv->device_data.BlankPageSkipLevelKey.select = 19;
 }else if(param.optBlankPageSkip == BPS_MEDIUM){
  m_sv->device_data.BlankPageSkipKey.select = true;
  m_sv->device_data.BlankPageSkipLevelKey.select = 22;
 }else if(param.optBlankPageSkip == BPS_HIGH){
  m_sv->device_data.BlankPageSkipKey.select = true;
  m_sv->device_data.BlankPageSkipLevelKey.select = 25;
 }else{
  m_sv->device_data.BlankPageSkipKey.select = false;
 }
 if(param.skewCorrect == SC_NONE){
  m_sv->device_data.PaperDeskew.select = false;
 }else if(param.skewCorrect == SC_EDGE){
  m_sv->device_data.PaperDeskew.select = true;
 }
 if(param.docEnhance == DE_NONE){
  m_sv->device_data.textEnhance.select = TextEnhanceNone;
 }else if(param.docEnhance == DE_TET_STD){
  m_sv->device_data.textEnhance.select = TextEnhanceNormal;
 }else if(param.docEnhance == DE_TET_HIGH){
  m_sv->device_data.textEnhance.select = TextEnhanceHigh;
 }
 return ESL_SUCCESS;
}
double CScanMgr::calculate_pixel_size(double value)
{
 int res = m_sv->device_data.Resolution.select;
    double mpp = 25.4 / (double)res;
    return value / mpp;
}
void CScanMgr::StandardSizeToPixel(eDocSize docSize, eSizeUnit sizeUnit, RECT sizeUser)
{
 SDI_TRACE_LOG("StandardSizeToPixel");
 m_sv->device_data.ScanArea.AutoSize.select = AutoSizeNone;
    if(docSize == DS_AUTO){
        m_sv->device_data.ScanArea.AutoSize.select = AutoSizeStandard;
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(210);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(297);
    }else if(docSize == DS_A3){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(297);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(420);
    }else if(docSize == DS_A4){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(210);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(297);
    }else if(docSize == DS_A5){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(148);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(210);
    }else if(docSize == DS_B4){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(257);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(364);
    }else if(docSize == DS_B5){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(182);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(257);
    }else if(docSize == DS_US_LETTER){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(216);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(279);
    }else if(docSize == DS_US_LEGAL){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(216);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(356);
    }else if(docSize == DS_US_LEDGER){
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(279);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(432);
    }else if(docSize == DS_USER){
  double left = sizeUser.left;
  double top = sizeUser.top;
  double right = sizeUser.right;
  double bottom = sizeUser.bottom;
  if (sizeUnit != SU_PIXEL) {
   left /= 100;
   top /= 100;
   right /= 100;
   bottom /= 100;
  }
  if(sizeUnit == SU_INCH){
   m_sv->device_data.ScanArea.ScanAreaOffsetX.select = left * m_sv->device_data.Resolution.select;
   m_sv->device_data.ScanArea.ScanAreaOffsetY.select = top * m_sv->device_data.Resolution.select;
            m_sv->device_data.ScanArea.ScanAreaWidth.select = (right - left) * m_sv->device_data.Resolution.select;
            m_sv->device_data.ScanArea.ScanAreaHeight.select = (bottom - top) * m_sv->device_data.Resolution.select;
  }else if(sizeUnit == SU_MILLIMETER){
   m_sv->device_data.ScanArea.ScanAreaOffsetX.select = calculate_pixel_size(left);
   m_sv->device_data.ScanArea.ScanAreaOffsetY.select = calculate_pixel_size(top);
            m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(right - left);
            m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(bottom - top);
        }else if(sizeUnit == SU_PIXEL){
   m_sv->device_data.ScanArea.ScanAreaOffsetX.select = left;
   m_sv->device_data.ScanArea.ScanAreaOffsetY.select = top;
            m_sv->device_data.ScanArea.ScanAreaWidth.select = right - left;
            m_sv->device_data.ScanArea.ScanAreaHeight.select = bottom - top;
        }
  SDI_TRACE_LOG("[INFO]User : ScanAreaOffsetX = %d", m_sv->device_data.ScanArea.ScanAreaOffsetX.select);
  SDI_TRACE_LOG("[INFO]User : ScanAreaOffsetY = %d", m_sv->device_data.ScanArea.ScanAreaOffsetY.select);
  SDI_TRACE_LOG("[INFO]User : ScanAreaWidth = %d", m_sv->device_data.ScanArea.ScanAreaWidth.select);
  SDI_TRACE_LOG("[INFO]User : ScanAreaHeight = %d", m_sv->device_data.ScanArea.ScanAreaHeight.select);
    }else{
  m_sv->device_data.ScanArea.AutoSize.select = AutoSizeStandard;
        m_sv->device_data.ScanArea.ScanAreaWidth.select = calculate_pixel_size(210);
        m_sv->device_data.ScanArea.ScanAreaHeight.select = calculate_pixel_size(297);
 }
}
DWORD CScanMgr::getInfoCapabilities(EslParamHdr* pParam)
{
 SDI_TRACE_LOG("getInfoCapabilities");
 DWORD err = ESL_SUCCESS;
 m_sv->Get_All_Value();
 if (pParam->type != ESL_PARAM_INFO_BASIC) {
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 EslParamInfoBasic* pInfo = (EslParamInfoBasic*)pParam;
 strncpy((char *)pInfo->serialNumber, m_sv->device_data.Serial_Number_value.c_str(), sizeof(pInfo->serialNumber));
 SDI_TRACE_LOG("");
 memset(pInfo->reserved1, 0, sizeof(pInfo->reserved1));
 memset(pInfo->reserved2, 0, sizeof(pInfo->reserved2));
 return ESL_SUCCESS;
}
DWORD CScanMgr::execScan(eExecType ExecType)
{
 SDI_TRACE_LOG("execScan");
 DWORD err = ESL_SUCCESS;
 m_ParamScanCurrent.type = ESL_PARAM_SCAN_BASIC;
 if(m_sv->device_data.Folder == USER_DEFINE){
        m_sv->device_data.SelectPath = m_sv->device_data.UserDefinePath;
    }
 err = this->conversionScanCapSDKtoSV((EslParamHdr*)&m_ParamScanCurrent);
 this->conversionSaveCapSDKtoSV((EslParamHdr*)&m_ParamSaveCurrent);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]conversionScanCapSDKtoSV failed");
  return err;
 }
 this->conversionJpegCapSDKtoSV((EslParamHdr*)&m_ParamJpegCurrent);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]conversionJpegCapSDKtoSV failed");
  return err;
 }
 this->conversionTiffCapSDKtoSV((EslParamHdr*)&m_ParamTiffCurrent);
 if (err != ESL_SUCCESS) {
  SDI_TRACE_LOG("[ERROR]conversionTiffCapSDKtoSV failed");
  return err;
 }
 if(m_sv->device_data.FunctionalUnit.select == Auto){
  if(m_sv->GetPaperLoadedStatus()){
   SDI_TRACE_LOG("[INFO]FunctionalUnit Auto : ADF");
   m_sv->device_data.FunctionalUnit.select = kSDIFunctionalUnitDocumentFeeder;
   m_sv->device_data.DuplexType.select = Single_Sided;
     }else {
   SDI_TRACE_LOG("[INFO]FunctionalUnit Auto : Flatbed");
   m_sv->device_data.FunctionalUnit.select = kSDIFunctionalUnitFlatbed;
  }
 }
 m_scanFileFormat = m_ParamSaveCurrent.fileFormat;
 switch (ExecType) {
 case ET_SCAN_AND_SAVE:
  this->execScanAndSave();
  err = (DWORD)m_sv->m_LastError;
  break;
 case ET_SCAN_AND_STORE:
  this->execScanAndStore();
  err = (DWORD)m_sv->m_LastError;
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return err;
}
DWORD CScanMgr::execSave(eExecType ExecType)
{
 SDI_TRACE_LOG("execSave");
 DWORD err = ESL_SUCCESS;
 ExecType = ET_SAVE_STORED_IMAGE;
 this->conversionSaveCapSDKtoSV((EslParamHdr*)&m_ParamSaveCurrent);
 switch (ExecType) {
 case ET_SAVE_STORED_IMAGE:
  this->execSaveStored();
  err = (DWORD)m_sv->m_LastError;
  break;
 case ET_GET_STORED_IMAGE:
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return err;
}
void CScanMgr::execScanAndSave(void)
{
 SDI_TRACE_LOG("execScanAndSave");
 bool gs_cancel_do = false;
    m_sv->scanning_status = SAVE;
    if(m_sv->Scan_Start(kSDIOperationTypeNew)){
        while(m_sv->scanning_status == SAVE){
            if(gs_cancel_do){
                m_sv->scanning_status = CANCEL;
            }
            if(m_sv->scanning_status == CANCEL){
                m_sv->Cancel_Scanning();
                m_sv->outEventType = kSDITransferEventTypeCancel;
                break;
            }else {
                if(m_sv->CheckNextTransferEvent(false)){
                    if(m_sv->Scanning()){
                        if(m_sv->outEventType == kSDITrasnferEventTypeImage){
                            m_sv->Get_Image();
                            m_sv->Save_Path();
                        }
                    }else {
                        m_sv->Get_Image();
      m_sv->Dispose_Ptr();
                        break;
                    }
     m_sv->Dispose_Ptr();
                }else if(m_sv->outEventType == kSDITransferEventTypeComplete){
                    break;
                }
            }
        }
    }
 this->execSaveStored();
}
void CScanMgr::execScanAndStore(void)
{
 SDI_TRACE_LOG("execScanAndStore");
 bool gs_cancel_do = false;
    m_sv->scanning_status = SAVE;
    if(m_sv->Scan_Start(kSDIOperationTypeNew)){
        while(m_sv->scanning_status == SAVE){
            if(gs_cancel_do){
                m_sv->scanning_status = CANCEL;
            }
            if(m_sv->scanning_status == CANCEL){
                m_sv->Cancel_Scanning();
                m_sv->outEventType = kSDITransferEventTypeCancel;
                break;
            }else {
                if(m_sv->CheckNextTransferEvent(false)){
                    if(m_sv->Scanning()){
                        if(m_sv->outEventType == kSDITrasnferEventTypeImage){
                            m_sv->Get_Image();
       if (m_sv->scanning_status == CANCEL){
        m_sv->Cancel_Scanning();
           while(m_sv->outEventType != kSDITransferEventTypeComplete){
         if(m_sv->CheckNextTransferEvent(false))
         {
          m_sv->Scanning();
          m_sv->Dispose_Ptr();
         }else{
          m_sv->outEventType = kSDITransferEventTypeComplete;
         }
        }
        m_sv->outEventType = kSDITransferEventTypeCancel;
        break;
       }
                            m_sv->Save_Path();
                        }
                    }else {
                        m_sv->Get_Image();
      m_sv->Dispose_Ptr();
                        break;
                    }
     m_sv->Dispose_Ptr();
                }else if(m_sv->outEventType == kSDITransferEventTypeComplete){
                    break;
                }
            }
        }
    }
}
void CScanMgr::execSaveStored(void)
{
 SDI_TRACE_LOG("execSaveStored");
        if(m_sv->scanning_status == SAVE){
   SDI_TRACE_LOG("m_sv->scanning_status == SAVE");
            if(m_sv->Save_Image2(m_scanFileFormat == FF_JPEG)){
    SDI_TRACE_LOG("m_sv->Save_Image2()");
                const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFile(m_sv->device_data.SelectPath);
                if (!result) {
     SDI_TRACE_LOG("[ERROR]Unable to save scanned files.");
                }
            }else {
                if(m_sv->m_LastError == kSDIErrorWriteFile){
     SDI_TRACE_LOG("[ERROR]Unable to save scanned files.");
                }else if(m_sv->scanning_status == CANCEL){
     SDI_TRACE_LOG("[INFO]Scanning cancel.");
    }else {
     SDI_TRACE_LOG("[ERROR]All scanned pages were blank.");
                }
            }
        }
 SDI_TRACE_LOG("m_sv->m_LastError != kSDIErrorNone");
 SDI_TRACE_LOG("m_sv->m_LastError == %d\n", (int)m_sv->m_LastError);
}
void CScanMgr::showEslError(DWORD Code)
{
 SDI_TRACE_LOG("showEslError");
 switch (Code) {
 case ESL_SUCCESS:
  SDI_TRACE_LOG("[INFO]ESL_SUCCESS");
  break;
 case ESL_CANCEL:
  SDI_TRACE_LOG("[INFO]ESL_CANCEL");
  break;
 case ESL_ERR_GENERAL:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_GENERAL");
  break;
 case ESL_ERR_NOT_INITIALIZED:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_NOT_INITIALIZED");
  break;
 case ESL_ERR_INVALID_PARAM:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  break;
 case ESL_ERR_LOW_MEMORY:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_LOW_MEMORY");
  break;
 case ESL_ERR_LOW_DISKSPACE:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_LOW_DISKSPACE");
  break;
 case ESL_ERR_WRITE_FAIL:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_WRITE_FAIL");
  break;
 case ESL_ERR_READ_FAIL:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_READ_FAIL");
  break;
 case ESL_ERR_SCAN_GENERAL:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_SCAN_GENERAL");
  break;
 case ESL_ERR_INVALID_KEY:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_KEY");
  break;
 case ESL_ERR_NOT_SUPPORTED:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_NOT_SUPPORTED");
  break;
 case ESL_ERR_NO_DRIVER:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_NO_DRIVER");
  break;
 case ESL_ERR_OPEN_FAIL:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_OPEN_FAIL");
  break;
 default:
  SDI_TRACE_LOG("[ERROR]Unknown: %d", Code);
 }
}
void CScanMgr::showEslDeviceStatus(DWORD Code)
{
 SDI_TRACE_LOG("showEslDeviceStatus");
 switch (Code) {
 case ESL_STAT_READY:
  SDI_TRACE_LOG("[INFO]ESL_STAT_READY");
  break;
 case ESL_STAT_ERR_COVER_OPEN:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_COVER_OPEN");
  break;
 case ESL_STAT_ERR_PAPER_JAM:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_PAPER_JAM");
  break;
 case ESL_STAT_ERR_PAPER_EMPTY:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_PAPER_EMPTY");
  break;
 case ESL_STAT_ERR_FATAL:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_FATAL");
  break;
 case ESL_STAT_ERR_LAMP_TIME_FATAL:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_LAMP_TIME_FATAL");
  break;
 case ESL_STAT_ERR_CR_LOCK:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_CR_LOCK");
  break;
 case ESL_STAT_ERR_DOUBLE_FEED:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_DOUBLE_FEED");
  break;
 case ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE");
  break;
 case ESL_STAT_ERR_LOW_BATTERY:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_LOW_BATTERY");
  break;
 case ESL_STAT_ERR_CARRIER_SHEET_SENSOR:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_CARRIER_SHEET_SENSOR");
  break;
 case ESL_STAT_ERR_EDGE_TRACKING_SENSOR:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_EDGE_TRACKING_SENSOR");
  break;
 case ESL_STAT_ERR_PAPER_PROTECTION:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_PAPER_PROTECTION");
  break;
 case ESL_STAT_ERR_SEPARATION_LEVER:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_SEPARATION_LEVER");
  break;
 case ESL_STAT_ERR_POSE:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_POSE");
  break;
 case ESL_STAT_ERR_GAP_SENSOR:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_GAP_SENSOR");
  break;
 case ESL_STAT_ERR_UNKNOWN:
  SDI_TRACE_LOG("[ERROR]ESL_STAT_ERR_UNKNOWN");
  break;
 default:
  SDI_TRACE_LOG("[ERROR]Unknown: %d", Code);
 }
}
DWORD CScanMgr::getEslDeviceStatus(void)
{
 SDI_TRACE_LOG("getEslDeviceStatus");
 DWORD status = ESL_STAT_READY;
 m_sv->m_LastError = m_sv->CheckDeviceErrorStatus();
 switch (m_sv->m_LastError) {
 case kSDIErrorNone:
  status = ESL_STAT_READY;
  break;
 case kSDIErrorCoverOpen:
  status = ESL_STAT_ERR_COVER_OPEN;
  break;
 case kSDIErrorPaperJam:
  status = ESL_STAT_ERR_PAPER_JAM;
  break;
 case kSDIErrorPaperEmpty:
  status = ESL_STAT_ERR_PAPER_EMPTY;
  break;
 case kSDIErrorDeviceFatalError:
  status = ESL_STAT_ERR_FATAL;
  break;
 case kSDIErrorLampTime:
  status = ESL_STAT_ERR_LAMP_TIME_FATAL;
  break;
 case kSDIErrorCRLock:
  status = ESL_STAT_ERR_CR_LOCK;
  break;
 case kSDIErrorPaperDoubleFeed:
 case kSDIErrorPaperDoubleFeed2:
  status = ESL_STAT_ERR_DOUBLE_FEED;
  break;
 case kSDIErrorTrayClose:
  status = ESL_STAT_ERR_DOCUMENT_TRAY_CLOSE;
  break;
 case kSDIErrorLowBattery:
  status = ESL_STAT_ERR_LOW_BATTERY;
  break;
 case kSDIErrorCRSheetSensorError:
  status = ESL_STAT_ERR_CARRIER_SHEET_SENSOR;
  break;
 case kSDIErrorETSensorError:
  status = ESL_STAT_ERR_EDGE_TRACKING_SENSOR;
  break;
 case kSDIErrorPaperProtect:
  status = ESL_STAT_ERR_PAPER_PROTECTION;
  break;
 case kSDIErrorSepLeverChangedInterruptedly:
  status = ESL_STAT_ERR_SEPARATION_LEVER;
  break;
 case kSDIErrorDeviceFormUnstable:
 case kSDIErrorDeviceFormChangedInterruptedly:
  status = ESL_STAT_ERR_POSE;
  break;
 case kSDIErrorGapSensorError:
  status = ESL_STAT_ERR_GAP_SENSOR;
  break;
 case kSDIErrorUnknownError:
  status = ESL_STAT_ERR_UNKNOWN;
  break;
 default:
  SDI_TRACE_LOG("[ERROR]Unknown: %d", m_sv->m_LastError);
 }
 this->showEslDeviceStatus(status);
 return status;
}
DWORD CScanMgr::setParam(const EslParamHdr* pParam)
{
 SDI_TRACE_LOG("setParam");
 switch (pParam->type) {
 case ESL_PARAM_SAVE_BASIC:
  SDI_TRACE_LOG("[INFO]setParam : ESL_PARAM_SAVE_BASIC");
  memcpy_s(&m_ParamSaveCurrent, sizeof(EslParamSaveBasic), pParam, sizeof(EslParamSaveBasic));
  break;
 case ESL_PARAM_SAVE_JPEG:
  SDI_TRACE_LOG("[INFO]setParam : ESL_PARAM_SAVE_JPEG");
  memcpy_s(&m_ParamJpegCurrent, sizeof(EslParamSaveJPEG), pParam, sizeof(EslParamSaveJPEG));
  break;
 case ESL_PARAM_SAVE_TIFF:
  SDI_TRACE_LOG("[INFO]setParam : ESL_PARAM_SAVE_TIFF");
  memcpy_s(&m_ParamTiffCurrent, sizeof(EslParamSaveTIFF), pParam, sizeof(EslParamSaveTIFF));
  break;
 default:
  SDI_TRACE_LOG("[ERROR]ESL_ERR_INVALID_PARAM");
  return ESL_ERR_INVALID_PARAM;
 }
 return ESL_SUCCESS;
}
BOOL CScanMgr::sendAppCallbackScanStatus(EslCBDataScanStatus* scanstatus)
{
 SDI_TRACE_LOG("CScanMgr::sendAppCallbackScanStatus");
 if (this->m_pCbFunc) {
  return this->m_pCbFunc((EslCBDataHdr*)scanstatus, this->m_pPrivate);
 }
 return TRUE;
}
BOOL CScanMgr::sendAppCallbackImageFile(EslCBDImageFile* imagefile)
{
 SDI_TRACE_LOG("CScanMgr::sendAppCallbackImageFile");
 if (this->m_pCbFunc) {
  return this->m_pCbFunc((EslCBDataHdr*)imagefile, this->m_pPrivate);
 }
 return TRUE;
}
