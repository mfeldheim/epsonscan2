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
//  ScanMgr.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../ESCANLIB.h"
#include "supervisor.h"
#include "devicelist.h"
#include "PathUtils.h"
#include <string.h>
#define ST_STATUS_IMAGE_FILE 0x00000001
#define ST_STATUS_IMAGE_MEMORY 0x00000002
#define MAX_IMAGE_QUALITY_VALUE 1000
#define MIN_IMAGE_QUALITY_VALUE -1000
#define MAX_THRESHOLD_VALUE 255
#define MIN_THRESHOLD_VALUE 0
#define MAX_OFD_RESOLUTION 600
#define MIN_OFD_RESOLUTION 200
BOOL CALLBACK scanstatusCallback(EslCBDataScanStatus* scanstatus, PVOID pPrivate);
BOOL CALLBACK imagefileCallback(EslCBDImageFile* imagefile, PVOID pPrivate);
class CScanMgr
{
public:
 CScanMgr(void);
 ~CScanMgr(void);
 void free(void);
 DWORD openScanner(const ConnectInfo* pScanner);
 void closeScanner(void);
 DWORD ctrlParameter(const eParamOpType OpType, EslParamHdr* pParam);
 DWORD execute(const eExecType ExecType, peslCallback pCbFunc, PVOID pPrivate);
 DWORD getEslDeviceStatus(void);
 BOOL sendAppCallbackScanStatus(EslCBDataScanStatus* scanstatus);
 BOOL sendAppCallbackImageFile(EslCBDImageFile* imagefile);
 BOOL getSettingParameter(const eSpecifiedParameter SpecifiedParameter, INT* select);
 BOOL setSettingParameter(const eSpecifiedParameter SpecifiedParameter, const INT setparam);
private:
 Supervisor* m_sv;
 EslParamScanExV1 m_ParamScanDefault;
 EslParamScanExV1 m_ParamScanCurrent;
 BOOL m_ShowIndicators;
 BOOL m_ColorSlipReduction;
 EslParamSaveBasic m_ParamSaveDefault;
 EslParamSaveBasic m_ParamSaveCurrent;
 EslParamSaveJPEG m_ParamJpegDefault;
 EslParamSaveJPEG m_ParamJpegCurrent;
 EslParamSaveTIFF m_ParamTiffDefault;
 EslParamSaveTIFF m_ParamTiffCurrent;
 void setSDKDefault(void);
 void loadScanDefault(void);
 void loadDefault(void);
 DWORD setParameter(EslParamHdr* pParam);
 DWORD getCurrentParameter(EslParamHdr* pParam);
 DWORD getDefaultParameter(EslParamHdr* pParam);
 DWORD setParamScan(const EslParamHdr* pParam);
 DWORD getCurrentParamScan(EslParamHdr* pParam);
 DWORD getDefaultParamScan(EslParamHdr* pParam);
 DWORD setParamSave(const EslParamHdr* pParam);
 DWORD getCurrentParamSave(EslParamHdr* pParam);
 DWORD getDefaultParamSave(EslParamHdr* pParam);
 DWORD getParamInfo(EslParamHdr* pParam);
 peslCallback m_pCbFunc;
 PVOID m_pPrivate;
 DWORD setScanCapabilities(const EslParamHdr* pParam);
 DWORD conversionSaveCapSDKtoSV(const EslParamHdr* pParam);
 DWORD conversionScanCapSDKtoSV(const EslParamHdr* pParam);
 DWORD conversionJpegCapSDKtoSV(const EslParamHdr* pParam);
 DWORD conversionTiffCapSDKtoSV(const EslParamHdr* pParam);
 void StandardSizeToPixel(eDocSize docSize, eSizeUnit sizeUnit, RECT sizeUser);
 double calculate_pixel_size(double value);
 DWORD getInfoCapabilities(EslParamHdr* pParam);
 DWORD execScan(eExecType ExecType);
 DWORD execSave(eExecType ExecType);
 void execScanAndSave(void);
 void execScanAndStore(void);
 void execSaveStored(void);
 static void showEslError(DWORD Code);
 static void showEslDeviceStatus(DWORD Code);
 DWORD setParam(const EslParamHdr* pParam);
 eExecType m_execType;
 eFileFormat m_scanFileFormat;
};
