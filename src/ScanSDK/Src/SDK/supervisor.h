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
//  supervisor.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SUPERVISOR_H
#define SUPERVISOR_H 
#include "../../../Include/Controller/EpsonScan2.h"
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <boost/format.hpp>
#include <string.h>
#include "capitem.h"
#include "configuration.h"
#include "../ESCANLIB.h"
#define INIT_POSITION_X 50
#define INIT_POSITION_Y 50
#define INIT_MAINWINDOW_WIDTH 488
#define INIT_MAINWINDOW_HEIGHT 670
#define DEVICE_SEARCH_TIME 1
typedef enum {CONTINUE, SAVE, CANCEL, ERROR, DISCARD, EDIT}ScanningStatus;
typedef enum {
    IMMEDIATE,
    AFTER_EJECT
} DoubleFeedMode;
typedef struct {
    bool AllPage;
    SDIInt page;
} PDF_IMGFMT_OPTION;
typedef struct {
    SDIInt select;
    SDICapability capability;
} INT_SETTING_VALUE;
typedef struct {
    INT_SETTING_VALUE ScanAreaWidth;
    INT_SETTING_VALUE ScanAreaHeight;
    INT_SETTING_VALUE ScanAreaOffsetX;
    INT_SETTING_VALUE ScanAreaOffsetY;
    INT_SETTING_VALUE MaxScanAreaWidth;
    INT_SETTING_VALUE MaxScanAreaHeight;
    INT_SETTING_VALUE MaxScanAreaHeightInLongPaper;
    INT_SETTING_VALUE ADFHeightMin;
    INT_SETTING_VALUE ADFDuplexHeightMin;
    INT_SETTING_VALUE ADFWidthMin;
    INT_SETTING_VALUE AutoSize;
    INT_SETTING_VALUE PaperEndDetection;
    bool PaperEndDetectionMemory;
    DocumentSize FixedSize;
    double UserDefine_Width;
    double UserDefine_Length;
    double FBWidthMin;
    double FBHeightMin;
    INT_SETTING_VALUE ADFCard;
} SCAN_AREA_VALUE;
typedef struct {
    INT_SETTING_VALUE ImageFormat;
    INT_SETTING_VALUE MultiTiffEnabled;
    INT_SETTING_VALUE OFDEnabled;
    INT_SETTING_VALUE TiffCompression;
    INT_SETTING_VALUE JpegQuality;
    SDIInt JpegQuality_forJPEG;
    SDIInt JpegQuality_forPDF;
    INT_SETTING_VALUE JpegProgressive;
    PDF_IMGFMT_OPTION PDFImgFormatOption;
} IMAGE_FORMAT_SETTINGS_VALUE;
typedef struct {
    INT_SETTING_VALUE ScanCounterKey;
    INT_SETTING_VALUE ADFScanCounterKey;
    INT_SETTING_VALUE ADFDuplexScanCounterKey;
    INT_SETTING_VALUE ADFCarrierSheetScanCounterKey;
    INT_SETTING_VALUE CardScanCounterKey;
    INT_SETTING_VALUE PaperJamCounter;
    INT_SETTING_VALUE DoubleFeedCounter;
    INT_SETTING_VALUE RollerKitCounter;
    INT_SETTING_VALUE RollerKitLifeLimit;
    INT_SETTING_VALUE RollerKitNearEnd;
    INT_SETTING_VALUE RollerCounter;
    INT_SETTING_VALUE RollerLifeLimit;
    INT_SETTING_VALUE RollerNearEnd;
    INT_SETTING_VALUE RetardRollerCounter;
    INT_SETTING_VALUE RetardRollerLifeLimit;
    INT_SETTING_VALUE RetardRollerNearEnd;
    INT_SETTING_VALUE RestrictFunction;
    INT_SETTING_VALUE CleaningAlertLimitCount;
    INT_SETTING_VALUE CleaningWarningNotifyCount;
    INT_SETTING_VALUE RollerKitNotifyCount;
    INT_SETTING_VALUE RetardRollerNotifyCount;
    INT_SETTING_VALUE SeparationPadNotifyCount;
    INT_SETTING_VALUE PickupRollerNotifyCount;
    INT_SETTING_VALUE CleaningWarningCounter;
    INT_SETTING_VALUE CleaningWarningNotify;
    INT_SETTING_VALUE PaperProtectionCounter;
} CONFIGURE_COUNTER_VALUE;
typedef struct {
    INT_SETTING_VALUE DoubleFeedDetection;
    INT_SETTING_VALUE DoubleFeedDetectionLevel;
    INT_SETTING_VALUE DoubleFeedDetectionAreaMin;
    INT_SETTING_VALUE DoubleFeedDetectionAreaLength;
} DOUBLE_FEED_DETECTION_VALUE;
typedef struct {
    INT_SETTING_VALUE FunctionalUnit;
    INT_SETTING_VALUE GuidePosition;
    INT_SETTING_VALUE ColorType;
    INT_SETTING_VALUE AutoColorPixelType;
    INT_SETTING_VALUE AutoColorPixelLevel;
    INT_SETTING_VALUE Resolution;
    SCAN_AREA_VALUE ScanArea;
    INT_SETTING_VALUE DropoutColor;
    INT_SETTING_VALUE Orientation;
    INT_SETTING_VALUE Gamma;
    IMAGE_FORMAT_SETTINGS_VALUE ImageFormatSettings;
    INT_SETTING_VALUE Threshold;
    INT_SETTING_VALUE Brightness;
    INT_SETTING_VALUE Contrast;
    INT_SETTING_VALUE DuplexType;
    INT_SETTING_VALUE PaperLoaded;
    INT_SETTING_VALUE PagesTobeScanned;
    DOUBLE_FEED_DETECTION_VALUE DoubleFeedDetectionValue;
    INT_SETTING_VALUE BlankPageSkipKey;
    INT_SETTING_VALUE BlankPageSkipLevelKey;
    INT_SETTING_VALUE PaperDeskew;
    INT_SETTING_VALUE BackgroundRemoval;
    INT_SETTING_VALUE TransferCompression;
    INT_SETTING_VALUE SleepTime;
    INT_SETTING_VALUE AutoPowerOffTime;
    INT_SETTING_VALUE AutoPowerOffTimeBattery;
    CONFIGURE_COUNTER_VALUE ConfigureCounter;
    INT_SETTING_VALUE SensorGlassDirtSensitivity;
    INT_SETTING_VALUE ADFPaperProtection;
    INT_SETTING_VALUE BehaviorWhenDoubleFeed;
    INT_SETTING_VALUE DirectPowerOn;
    INT_SETTING_VALUE NonConnectPowerOff;
    INT_SETTING_VALUE Use2in1Mode;
    INT_SETTING_VALUE AdfDuplexType;
    INT_SETTING_VALUE ScannerKind;
    INT_SETTING_VALUE FirmwareVersion;
    std::string Firmware_Version_value;
    INT_SETTING_VALUE SerialNumber;
    std::string Serial_Number_value;
    INT_SETTING_VALUE textEnhance;
    INT_SETTING_VALUE textEnhanceNoiseReductionLevel;
    INT_SETTING_VALUE textEnhanceSensitivity;
    INT_SETTING_VALUE textEnhancePaperCreaseReduction;
    INT_SETTING_VALUE thresholdAdjustment;
    bool FunctionalUnit_Auto;
    bool Add_Pages;
    std::string Prefix;
    bool FileName_OverWrite;
    bool FileName_Counter;
    SDIInt Folder;
    std::string UserDefinePath;
    std::string SelectPath;
    SDIInt ImageOption;
    std::string MaxScanArea_height_table;
    bool DNShow_PlasticCard_dialog;
    bool DNShow_LongPaperWarning_dialog;
    bool OverDurationAlert;
    bool NearDurationAlert;
    INT_SETTING_VALUE BackgroundColor;
    INT_SETTING_VALUE AutomaticFeedingMode;
    INT_SETTING_VALUE AFMTimeout;
    AdministratorStatus admin_status;
} SCANPARA;
#include "Platform.h"
typedef DWORD (CALLBACK *supervisorStatusCallback)(EslCBDataScanStatus* scanstatus, PVOID pPrivate);
typedef DWORD (CALLBACK *supervisorImageCallback)(EslCBDImageFile* imagefile, PVOID pPrivate);
class Supervisor {
public:
    Supervisor();
    void* es2lib_;
    SDIDeviceFinder_CreatePtr SDIDeviceFinder_CreatePtr_;
    SDIDeviceFinder_DisposePtr SDIDeviceFinder_DisposePtr_;
    SDIDeviceFinder_StartDiscoveryPtr SDIDeviceFinder_StartDiscoveryPtr_;
    SDIDeviceFinder_StopDiscoveryPtr SDIDeviceFinder_StopDiscoveryPtr_;
    SDIDeviceFinder_GetDevicesPtr SDIDeviceFinder_GetDevicesPtr_;
    SDIScannerDriver_CreatePtr SDIScannerDriver_CreatePtr_;
    SDIScannerDriver_OpenPtr SDIScannerDriver_OpenPtr_;
    SDIScannerDriver_ClosePtr SDIScannerDriver_ClosePtr_;
    SDIScannerDriver_DisposePtr SDIScannerDriver_DisposePtr_;
    SDIScannerDriver_SetValuePtr SDIScannerDriver_SetValuePtr_;
    SDIScannerDriver_GetValuePtr SDIScannerDriver_GetValuePtr_;
    SDIScannerDriver_GetCapabilityPtr SDIScannerDriver_GetCapability_;
    SDIScannerDriver_DoScanJobPtr SDIScannerDriver_DoScanJobPtr_;
    SDIScannerDriver_CheckNextTransferEventPtr SDIScannerDriver_CheckNextTransferEventPtr_;
    SDIScannerDriver_GetNextTransferEventPtr SDIScannerDriver_GetNextTransferEventPtr_;
    SDIImage_CreatePtr SDIImage_CreatePtr_;
    SDIImage_GetPathPtr SDIImage_GetPathPtr_;
    SDIImage_DisposePtr SDIImage_DisposePtr_;
    SDIImage_GetWidthPtr SDIImage_GetWidthPtr_;
    SDIImage_GetHeightPtr SDIImage_GetHeightPtr_;
    SDIImage_GetSamplesPerPixelPtr SDIImage_GetSamplesPerPixelPtr_;
    SDIImage_GetBitsPerSamplePtr SDIImage_GetBitsPerSamplePtr_;
    SDIMultipage_StartPtr SDIMultipage_StartPtr_;
    SDIMultipage_AddPtr SDIMultipage_AddPtr_;
    SDIMultipage_FinPtr SDIMultipage_FinPtr_;
    SDIConvertJpegToFormatPtr SDIConvertJpegToFormat_;
    SDIDeviceInfo_ResolvePtr SDIDeviceInfo_ResolvePtr_;
    SDIImage_CheckImageIsBlankPtr SDIImage_CheckImageIsBlankPtr_;
    SDIScannerDriver_CheckCautionStatusPtr SDIScannerDriver_CheckCautionStatusPtr_;
    SDIScannerDriver_UnlockAdministratorLockPtr SDIScannerDriver_UnlockAdministratorLockPtr_;
    SDIScannerDriver_LockAdministratorLockPtr SDIScannerDriver_LockAdministratorLockPtr_;
    void setCallback(DWORD Type, PVOID pCbFunc, PVOID pPrivate);
    SCANPARA device_data;
    SDIScannerDriver* driver;
    std::string Filer;
    void SetUp();
    void Terminate();
    SDIError Connecting_Scanner(SDIDeviceInfo devInfo, InterruptEventCallBackProc AlertFunc);
    void Disconnecting_Scanner(void);
    void Dispose_Scanner(void);
    void Cancel_Scanning(void);
    void Continue_Scanning(void);
    bool Get_All_Value(void);
    bool Get_Counter_Value(void);
    bool Set_All_Value(void);
    bool Reset_RollerCouunter_Value(void);
    bool Set_RollerCouunter_Value(void);
    bool Get_Exclusion_Value(void);
    bool Set_Exclusion_Value(void);
    bool GetPaperLoadedStatus(void);
    bool GetUnscannebleScanParameterStatus(void);
    bool GetScannerPosition(void);
    bool Scan_Start(SDIOperationType operation_type);
    bool Scan_Terminate();
    bool CheckNextTransferEvent(bool wait);
    bool Scanning(void);
    bool CheckScanningError(SDIError outError);
    SDIError CheckDeviceErrorStatus();
    void Scan_Complete(uint32_t imageCount);
    void Get_Image();
    void Save_Path(void);
    bool CheckImageIsBlank();
    bool Save_Image2(bool scanFormatIsJpeg);
    void Dispose_Ptr(void);
    bool Check_SupportAdministratorRestricted(void);
    bool Get_AdministratorRestrictedStatus(void);
    bool Send_AdministratorRestrictedPassword(std::string password);
    bool SANEManuNetfinder();
    bool DeviceInfoResolve(SDIDeviceInfo* devInfo);
    SDITransferEventType outEventType;
    SDIError m_LastError;
    ScanningStatus scanning_status;
    bool bAllReset;
    bool edit_mode;
    std::string setting_file_path;
    bool m_DoneBlanckPage;
    bool m_ExistsPage;
    FunctionalUnit m_Preview_FunctionalUnit;
    ImageFormat m_PreserveImageFormat;
    supervisorStatusCallback m_pCbStFunc;
    supervisorImageCallback m_pCbImgFunc;
    PVOID m_pPrivate;
    int m_fileNumStartCount;
    int m_numPageStart;
    int m_numPageEnd;
private:
    SDIImage* outImageData;
    unsigned char* output_path;
    int m_ScanCounter;
    BOOL sendAppCallbackScanStatus(DWORD Type, DWORD Status, DWORD Count, LONG Progress);
    BOOL sendAppCallbackImageFile(DWORD Type, DWORD Status, LPCTSTR FileName);
};
#endif
