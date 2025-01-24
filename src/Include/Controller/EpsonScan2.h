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
//  EpsonScan2.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#ifndef _cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdlib.h>
typedef struct SDIScannerDriver SDIScannerDriver;
typedef struct SDIDeviceFinder SDIDeviceFinter;
typedef struct SDIImage SDIImage;
typedef int32_t SDIInt;
typedef const char SDIChar;
#define MAX_MODEL_ID 20
#define MAX_IP_ADDR 64
#define MAX_DISPLAYNAME 50
typedef struct {
 SDIInt version;
 char modelID[MAX_MODEL_ID];
 SDIInt productID;
 char ipAddress[MAX_IP_ADDR];
 char displayName[MAX_DISPLAYNAME];
}SDIDeviceInfo;
typedef enum
{
  kSDITrasnferEventTypeImage,
  kSDITransferEventTypeComplete,
  kSDITransferEventTypeCancel,
  kSDITransferEventTypeStartContinuousScanInAFM,
  kSDITransferEventTypeStopContinuousScanInAFM
} SDITransferEventType;
typedef enum {
 kSDISupportLevelNone,
 kSDISupportLevelUnavailable,
 kSDISupportLevelAvailable
}SDISupportLevel;
typedef enum {
 kSDICapabilitTypeList,
    kSDICapabilitTypeRange
}SDICapabilityType;
#define SDI_CAPABILITY_LISTMAX 20
typedef struct {
 SDIInt version;
    SDISupportLevel supportLevel;
    SDICapabilityType capabilityType;
 SDIInt minValue;
 SDIInt maxValue;
 SDIInt allMinValue;
 SDIInt allMaxValue;
    SDIInt list[SDI_CAPABILITY_LISTMAX];
 SDIInt countOfList;
 SDIInt allList[SDI_CAPABILITY_LISTMAX];
 SDIInt countOfAllList;
}SDICapability;
typedef enum : SDIInt {
 kSDIErrorNone = 0,
 kSDIErrorUnknownError = 1,
 kSDIErrorInvalidParam = 2,
 kSDIErrorFileNotFound = 3,
 kSDIErrorDeviceNotOpened = 10,
 kSDIErrorDeviceNotClosed = 11,
 kSDIErrorDeviceInUse = 12,
 kSDIErrorDeviceInBusy = 13,
 kSDIErrorPaperEmpty = 14,
 kSDIErrorPaperJam = 15,
 kSDIErrorPaperDoubleFeed = 16,
 kSDIErrorCoverOpen = 17,
 kSDIErrorTrayClose = 19,
 kSDIErrorCRLock = 20,
 kSDIErrorLamp = 21,
 kSDIErrorLampTime = 22,
 kSDIErrorAuthFailure = 23,
 kSDIErrorNoPermission = 24,
 kSDIErrorLowBattery = 25,
 kSDIErrorDataSend = 26,
 kSDIErrorDataReceive = 27,
 kSDIErrorInvalidResponse = 29,
 kSDIErrorDeviceOpen = 30,
 kSDIErrorDeviceIncorrect = 31,
 kSDIErrorConnectionTimeout = 32,
 kSDIErrorDeviceDisconnected = 33,
 kSDIErrorDeviceNotFound = 34,
 kSDIErrorDeviceFatalError = 35,
 kSDIErrorServerError = 36,
 kSDIErrorCRSheetSensorError = 37,
 kSDIErrorPaperProtect = 38,
 kSDIErrorGapSensorError = 39,
 kSDIErrorDeviceFormUnstable = 40,
 kSDIErrorDeviceFormChangedInterruptedly = 41,
 kSDIErrorSepLeverChangedInterruptedly = 42,
 kSDIErrorUnscannableDeviceConfig1 = 43,
 kSDIErrorPaperDoubleFeed2 = 45,
 kSDIErrorETSensorError = 46,
 kSDIErrorPESensorError = 47,
 kSDIErrorDiskFull = 100,
 kSDIErrorWriteFile = 102,
 kSDIErrorWriteTempFile = 103,
 kSDIErrorFileNameConflict = 104,
 kSDIErrorCreateWorkDir = 105,
 kSDIErrorNoMemory = 151,
 kSDIErrorLongPaperUnsupporetedResolution = 207,
 kSDIErrorScanAreaTooLarge = 209,
 kSDIErrorScanAreaTooSmall = 210,
 kSDIErrorDocumentSeparationLever = 211,
 kSDIErrorCardLever = 212,
 kSDIErrorRotateUnsupportedResolution = 213,
 kSDIErrorJsonParse = 251,
 kSDIErrorValueType = 254,
 kSDIErrorModuleNotFound = 253,
 kSDIErrorUserAuthEnabled = 255,
 kSDIErrorPaperRemoveError = 326,
    kSDIErrorSkewDetectError = 327,
} SDIError;
typedef enum : SDIInt
{
  kSDIInterruptEventTypePushScan,
 kSDIInterruptEventTypeDisconnect,
 kSDIInterruptEventTypeGlassDirty,
 kSDIInterruptEventTypeGlassFlatbedModel,
 kSDIInterruptEventTypeCleaningRequired
} SDIInterruptEventType;
typedef enum : SDIInt
{
 kSDIValueTypeInt,
 kSDIValueTypeString
} SDIValueType;
typedef enum : SDIInt
{
  kSDIOperationTypeNew,
  kSDIOperationTypeCancel,
  kSDIOperationTypeStartAFM,
  kSDIOperationTypeStopAFM,
  kSDIOperationTypeStartAFMC,
  kSDIOperationTypeStopAFMC
} SDIOperationType;
typedef void (*DeviceFinderCallBackProc)(SDIDeviceFinder* finder, const SDIDeviceInfo* info, void* userdata);
typedef void (*InterruptEventCallBackProc)(SDIScannerDriver* driver, SDIInterruptEventType event , void* userdata);
typedef SDIError (*SDIDeviceFinder_CreatePtr)(SDIDeviceFinter** outFinder);
typedef SDIError (*SDIDeviceFinder_StartDiscoveryPtr)(SDIDeviceFinder* finder,DeviceFinderCallBackProc callBack, void* param);
typedef SDIError (*SDIDeviceFinder_StopDiscoveryPtr)(SDIDeviceFinder* finder);
typedef SDIError (*SDIDeviceFinder_SetTimeoutPtr)(SDIDeviceFinder* finder, SDIInt seconds);
typedef SDIError (*SDIDeviceFinder_GetDevicesPtr)(SDIDeviceFinder* finder, SDIDeviceInfo** outDevices, SDIInt* outCount);
typedef SDIError (*SDIDeviceFinder_FreeDevicesPtr)(SDIDeviceInfo* devices);
typedef SDIError (*SDIDeviceFinder_DisposePtr)(SDIDeviceFinder* finder);
typedef SDIError (*SDIScannerDriver_CreatePtr)(SDIScannerDriver** driver,
              const SDIDeviceInfo* deviceInfo,
                 InterruptEventCallBackProc callBack,
                 void *userdata);
typedef SDIError (*SDIScannerDriver_OpenPtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIScannerDriver_ResetPtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIScannerDriver_GetAllKeysPtr)(SDIScannerDriver* driver, SDIChar **outKeys, SDIInt* outCount);
typedef SDIError (*SDIScannerDriver_SetValuePtr)(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value, SDIInt size);
typedef SDIError (*SDIScannerDriver_GetValuePtr)(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value, SDIInt size);
typedef SDIError (*SDIScannerDriver_GetDefaultPtr)(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value);
typedef SDIError (*SDIScannerDriver_GetCapabilityPtr)(SDIScannerDriver* driver, SDIChar* key, SDICapability* outCapability);
typedef SDIError (*SDIScannerDriver_DoScanJobPtr)(SDIScannerDriver* driver,
                SDIOperationType operationType);
typedef bool (*SDIScannerDriver_CheckNextTransferEventPtr)(SDIScannerDriver* driver ,bool waitUntilReceived);
typedef SDIError (*SDIScannerDriver_GetNextTransferEventPtr)(SDIScannerDriver* driver,
                 SDITransferEventType* outType,
                  SDIImage* outImageData,
                     SDIError* outError);
typedef SDIError (*SDIScannerDriver_ClosePtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIScannerDriver_DisposePtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIImage_CreatePtr)(SDIImage** image);
typedef SDIInt (*SDIImage_GetWidthPtr)(SDIImage* image);
typedef SDIInt (*SDIImage_GetHeightPtr)(SDIImage* image);
typedef SDIInt (*SDIImage_GetSamplesPerPixelPtr)(SDIImage* image);
typedef SDIInt (*SDIImage_GetBitsPerSamplePtr)(SDIImage* image);
typedef SDIInt (*SDIImage_GetPathPtr)(SDIImage* image, SDIChar* buf, SDIInt bufSize);
typedef SDIInt (*SDIImage_DisposePtr)(SDIImage* image);
typedef bool (*SDIDeviceInfo_ResolvePtr)(SDIDeviceInfo* resolveDevice);
typedef void (*SDIScannerDriver_CheckCautionStatusPtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIScannerDriver_UnlockAdministratorLockPtr)(SDIScannerDriver* driver);
typedef SDIError (*SDIScannerDriver_LockAdministratorLockPtr)(SDIScannerDriver* driver);
static SDIChar* kSDIFunctionalUnitKey = "FunctionalUnit";
typedef enum : SDIInt
{
  kSDIFunctionalUnitFlatbed = 0,
  kSDIFunctionalUnitDocumentFeeder = 1,
  kSDIFunctionalUnitCarrierSheet = 2
}SDIFunctionalUnit;
static SDIChar* kSDIGuidePositionKey = "GuidePosition";
typedef enum : SDIInt
{
  kSDIGuidePositionLeft = 0,
  kSDIGuidePositionCenter = 1,
  kSDIGuidePositionCenterManual = 2,
  kSDIGuidePositionRight = 3
}SDIGuidePosition;
static SDIChar* kSDIColorTypeKey = "ColorType";
typedef enum : SDIInt
{
  kSDIColorTypeAuto = -1,
        kSDIColorTypeRGB24 = 0,
        kSDIColorTypeMono8 = 1,
        kSDIColorTypeMono1 = 2,
        kSDIColorTypeRGB48 = 3,
        kSDIColorTypeMono16 = 4
}SDIColorType;
static SDIChar* kSDIResolutionKey = "Resolution";
static SDIChar* kSDIScanAreaWidthKey = "ScanAreaWidth";
static SDIChar* kSDIScanAreaHeightKey = "ScanAreaHeight";
static SDIChar* kSDIScanAreaOffsetXKey = "ScanAreaOffsetX";
static SDIChar* kSDIScanAreaOffsetYKey = "ScanAreaOffsetY";
static SDIChar* kSDIMaxScanAreaWidthKey = "ScanAreaMaxWidth";
static SDIChar* kSDIMaxScanAreaHeightKey = "ScanAreaMaxHeight";
static SDIChar* kSDIMaxScanAreaHeightInLongPaperKey = "ScanAreaMaxHeightInLongPaper";
static SDIChar* kSDIMaxScanAreaHeightInLongPaperResolutionTableKey = "ScanAreaMaxHeightInLongPaperResolutionTable";
static SDIChar* kSDIDropoutColorKey = "DropoutColor";
typedef enum : SDIInt
{
 kSDIDropoutColorNone = 0,
 kSDIDropoutColorRed = 1,
 kSDIDropoutColorGreen = 2,
 kSDIDropoutColorBlue = 3
} SDIDropoutColor;
static SDIChar* kSDIOrientationKey = "Orientation";
typedef enum : SDIInt
{
 kSDIOrientationNone = 0,
 kSDIOrientation90 = 1,
 kSDIOrientation180 = 2,
 kSDIOrientation270 = 3,
 kSDIOrientationAuto = 4
} SDIOrientation;
static SDIChar* kSDIGammaKey = "Gamma";
static SDIChar* kSDIImageFormatKey = "ImageFormat";
typedef enum : SDIInt
{
  kSDIImageFormatRaw,
  kSDIImageFormatJPEG,
  kSDIImageFormatTIFF,
  kSDIImageFormatPDF,
  kSDIImageFormatPNG,
  kSDIImageFormatPNM,
  kSDIImageFormatColorJpegMonoPNM,
  kSDIImageFormatBMP,
  kSDIImageFormatOFD
}SDIImageFormat;
static SDIChar* kSDIMultiTiffEnabledKey = "MultiTiffEnabled";
static SDIChar* kSDIOFDSupportedKey = "OFDSupported";
static SDIChar* kSDITiffCompressionKey = "MultiTiffCompression";
typedef enum : SDIInt
{
 kSDITiffCompressionNone,
 kSDITiffCompressionCCITFAX4
} SDITiffCompression;
static SDIChar* kSDIThresholdKey = "Threshold";
static SDIChar* kSDIBrightnessKey = "Brightness";
static SDIChar* kSDIContrastKey = "Contrast";
static SDIChar* kSDIJpegQuality = "JpegQuality";
static SDIChar* kSDIJpegProgressiveKey = "jpegProgressive";
static SDIChar* kSDIDuplexTypeKey = "DuplexType";
static SDIChar* kSDIPaperLoadedKey = "PaperLoaded";
static SDIChar* kSDIPagesTobeScannedKey = "PagesTobeScanned";
static SDIChar* kSDIDoubleFeedDetectionKey = "DoubleFeedDetection";
static SDIChar* kSDIDoubleFeedDetectionAreaMinKey = "DoubleFeedDetectionAreaMin";
static SDIChar* kSDIDoubleFeedDetectionAreaLengthKey = "DoubleFeedDetectionAreaLength";
static SDIChar* kSDIDoubleFeedDetectionLevelKey = "DoubleFeedDetectionLevel";
typedef enum : SDIInt
{
  kSDIDoubleFeedDetectionLow = 0,
  kSDIDoubleFeedDetectionHigh = 1,
  kSDIDoubleFeedDetectionVeryLow = 2,
} SDIDoubleFeedDetectionLevel;
static SDIChar* kSDIBlankPageSkipKey = "BlankPageSkip";
static SDIChar* kSDIBlankPageSkipLevelKey = "BlankPageSkipLevel";
static SDIChar* kSDIPaperDeskewKey = "PaperDeskew";
static SDIChar* kSDIBackgroundRemovalKey = "BackgroundRemoval";
typedef enum : SDIInt
{
   kSDIBackgroundRemovalNone = 0,
   kSDIBackgroundRemovalNormal = 1,
   kSDIBackgroundRemovalHigh = 2
}SDIBackgroundRemoval;
static SDIChar* kSDIAutoSizeKey = "AutoSize";
typedef enum : SDIInt
{
 kSDIAutoSizeNone = 0,
 kSDIAutoSizeStandard = 1,
 kSDIAutoSizeLongPaper = 2
}SDIAutoSizeType;
static SDIChar* kSDITransferCompressionKey = "TransferCompression";
typedef enum : SDIInt
{
 kSDITransferCompressionRAW = 0,
 kSDITransferCompressionJPEG = 1,
}SDITransferCompression;
static SDIChar* kSDISleepTimeKey = "SleepTime";
 static SDIChar* kSDIAutoPowerOffTimeKey = "AutoPowerOffTime";
 static SDIChar* kSDIAutoPowerOffTimeBatteryKey = "AutoPowerOffTimeBattery";
static SDIChar* kSDIScanCounterKey = "ScanCounterKey";
static SDIChar* kSDIADFScanCounterKey = "ADFScanCounterKey";
static SDIChar* kSDIADFDuplexCounterKey = "ADFDuplexScanCounterKey";
static SDIChar* kSDIADFCarrierSheetCounterKey = "ADFCarrierSheetScanCounterKey";
static SDIChar* kSDICardScanCounterKey = "CardScanCounterKey";
static SDIChar* kSDIPaperJamCounterKey = "PaperJamCounter";
static SDIChar* kSDIDoubleFeedCounterKey = "DoubleFeedCounter";
static SDIChar* kSDIPickupRollerCounterKey = "PickupRollerCounter";
static SDIChar* kSDIPaperEndDetectionKey = "PaperEndDetection";
static SDIChar* kSDIADFHeightMinKey = "ADFHeightMin";
static SDIChar* kSDIADFDuplexHeightMinKey = "ADFDuplexHeightMin";
static SDIChar* kSDIADFWidthMinKey = "ADFWidthMin";
static SDIChar* kSDI2in1ModeKey = "2in1Mode";
static SDIChar* kSDIScannerPositionKey = "ScannerPositon";
 typedef enum : SDIInt
{
 kSDIScannerPositionFlat = 0,
 kSDIScannerPositionTilt = 1,
 kSDIScannerPositionInvalid = 2
}SDIScannerPosition;
static SDIChar* kSDIUnscannebleScanParameterStatusAllKey = "UnscannebleScanParameter";
static SDIChar* kSDIUnscannebleScanParameterForAFMCStatusAllKey = "UnscannebleScanParameterForAFMC";
static SDIChar* kSDIBackgroundColorKey = "BackgroundColor";
 typedef enum : SDIInt
{
 kSDIBackgroundColorWhite = 0,
 kSDIBackgroundColorBlack = 1,
 kSDIBackgroundColorGray = 2,
 kSDIBackgroundColorNone = 3
}SDIBackgroundColor;
static SDIChar* kSDIAutoColorPixelTypeKey = "AutoColorPixelType";
typedef enum : SDIInt
{
  kSDIAutoColorPixelTypeMono,
  kSDIAutoColorPixelTypeGray,
  kSDIAutoColorPixelTypeAuto
}SDIAutoColorPixelType;
static SDIChar* kSDIAutoColorPixelLevelKey = "AutoColorPixelLevel";
static SDIChar* kSDIAFMModeKey = "AFMMode";
static SDIChar* kSDIRollerKitCounterKey = "RollerKitCounter";
static SDIChar* kSDIRollerKitLifeLimitKey = "RollerKitLifeLimit";
static SDIChar* kSDIRollerKitNearEndKey = "RollerKitNearEnd";
static SDIChar* kSDIRollerCounterKey = "RollerCounter";
static SDIChar* kSDIRollerLifeLimitKey = "RollerLifeLimit";
static SDIChar* kSDIRollerNearEndKey = "RollerNearEnd";
static SDIChar* kSDIRetardRollerCounterKey = "RetardRollerCounter";
static SDIChar* kSDIRetardRollerLifeLimitKey = "RetardRollerLifeLimit";
static SDIChar* kSDIRetardRollerNearEndKey = "RetardRollerNearEnd";
static SDIChar* kSDIRestrictFunctionKey = "RestrictFunction";
static SDIChar* kSDIAFMTimeoutKey = "AFMTimeout";
static SDIChar* kSDIErrorStatusKey = "ErrorStatus";
static SDIChar* kSDICleaningAlertLimitCountKey = "CleaningAlertLimitCount";
static SDIChar* kSDIDocumentTypeKey = "DocumentType";
typedef enum : SDIInt
{
 kSDIDocumentTypeReflective = 0,
 kSDIDocumentTypePositiveFilm = 1,
 kSDIDocumentTypeMonoNegativeFilm = 2,
 kSDIDocumentTypeColorNegativeFilm = 3
}SDIDocumentType;
static SDIChar* kSDIFilmAreaGuideKey = "FilmAreaGuide";
static SDIChar* kSDIFocusPositionKey = "FocusPostion";
static SDIChar* kSDIADFCardKey = "ESADFCard";
typedef enum: uint32_t
{
 kSDIADFCardNotSupport = 0,
 kSDIADFCardSupport,
 kSDIADFCardPortrait,
 kSDIADFCardLandscape,
}SDIADFCard;
static SDIChar* kSDIDirectPowerOnKey = "directPowerOn";
typedef enum: uint32_t
{
 kSDIDirectPowerOn_Off = 0,
 kSDIDirectPowerOn_On
}SDIDirectPowerOn;
static SDIChar* kSDINonConnectPowerOffKey = "nonConnectPowerOff";
typedef enum: uint32_t
{
 kSDINonConnectPowerOff_Off = 0,
 kSDINonConnectPowerOff_On
}SDINonConnectPowerOff;
static SDIChar* kSDIADFPaperProtectionKey = "adfPaperProtection";
typedef enum: uint32_t
{
 kSDIADFPaperProtection_Off = 0,
 kSDIADFPaperProtection_Low = 1,
 kSDIADFPaperProtection_Normal = 2,
 kSDIADFPaperProtection_High = 3,
}SDIADFPaperProtection;
static SDIChar* kSDIBehaviorWhenDoubleFeedKey = "behaviorWhenDoubleFeed";
typedef enum: uint32_t
{
 kSDIBehaviorWhenDoubleFeed_Immediately = 0,
 kSDIBehaviorWhenDoubleFeed_StopAfterEjecting
}SDIBehaviorWhenDoubleFeed;
static SDIChar* kSDICleaningWarningNotifyCountKey = "cleaningWarningNotifyCount";
static SDIChar* kSDIRollerKitNotifyCountKey = "rollerKitNotifyCount";
static SDIChar* kSDIRetardRollerNotifyCountKey = "retardRollerNotifyCount";
static SDIChar* kSDISeparationPadNotifyCountKey = "separationPadNotifyCount";
static SDIChar* kSDIPickupRollerNotifyCountKey = "pickupRollerNotifyCount";
static SDIChar* kSDICleaningWarningCounterKey = "cleaningWarningCounter";
static SDIChar* kSDICleaningWarningNotifyKey = "cleaningWarningNotify";
typedef enum: uint32_t
{
 kSDICleaningWarningNotify_Off = 0,
 kSDICleaningWarningNotify_On
}SDICleaningWarningNotiy;
static SDIChar* kSDISensorGlassDirtSensitivity = "sensorGlassDirtySensitivity";
typedef enum: uint32_t
{
 kSDISensorGlassDirtSensitivityOff = 0,
 kSDISensorGlassDirtSensitivityLow = 1,
 kSDISensorGlassDirtSensitivityNormal = 2,
}SDISensorGlassDirtSensitivity;
static SDIChar* kSDIPaperProtectionCounterKey = "paperProtectionCounter";
static SDIChar* KSDIScannerKindKey = "scannerKind";
typedef enum: uint32_t
{
 kSDIKindSFDocument = 11,
 kSDIKindSFPhoto = 12,
 kSDIKindMFBusiness = 21,
 kSDIKindMFConsumer = 22,
 kSDIKindMFLargeFormat = 23,
}SDIScannerKind;
static SDIChar* kSDIADFDuplexTypeKey = "adfDuplexType";
typedef enum: uint32_t
{
 kSDIADFDuplexType1Pass = 1,
    kSDIADFDuplexType2Pass = 2,
}SDIDuplexType;
static SDIChar* kSDIFirmwareVersionKey = "firmwareVersion";
static SDIChar* kSDISerialNumberKey = "serialNumber";
static SDIChar* kSDITextEnhanceKey = "textEnhance";
typedef enum: uint32_t
{
 kSDITextEnhanceLevelNone = 0,
 kSDITextEnhanceLevelStandard = 1,
    kSDITextEnhanceLevelHigh = 2
}SDITextEnhanceLevel;
static SDIChar* kSDITextEnhanceNoiseReductionLevelKey = "textEnhanceNoiseReductionLevel";
static SDIChar* kSDITextEnhanceSensitivityKey = "textEnhanceSensitivity";
static SDIChar* kSDITextEnhancePaperCreaseReductionKey = "textEnhancePaperCreaseReduction";
static SDIChar* kSDITextEnhanceThresholdAdjustmentKey = "thresholdAdjustment";
static SDIChar* kSDIDefaultPasswordTypeKey = "defaultPasswordType";
typedef enum: uint32_t
{
 kSDIDefaultPasswordTypeSerial = 0,
 kSDIDefaultPasswordTypeUnique = 1,
}SDIDefaultPasswordType;
static SDIChar* kSDIAdminLockKey = "adminLock";
static SDIChar* kSDIAdminLockEnabledKey = "adminLockEnabled";
static SDIChar* kSDIAdminLockPasswordKey = "adminLockPassword";
static SDIChar* kSDIContinuousAutoFeedingModeKey = "continuousAutoFeedingMode";
static SDIChar* kSDIRemovePunchholeKey = "RemovePunchHole";
typedef enum : SDIInt
{
 kSDIRemovePunchHoleNone = 0,
 kSDIRemovePunchHoleAll = 1,
 kSDIRemovePunchHoleTopBottom = 2,
 kSDIRemovePunchHoleLeftRight = 3,
}SDIRemovePunchhole;
static SDIChar* kSDIAutoCroppingInscribedKey = "AutoCroppingInscribed";
static SDIChar* kSDIDeficiencyCorrectionKey = "DeficienryCorrection";
static SDIChar* kSDIADFSpecialErrorMessageForPassportKey = "ADFSpecialErrorMessageForPassport";
static SDIChar* kSDIDeviceErrorCodeKey = "DeviceErrorCode";
static SDIChar* kSDISocImageProcessKey = "SocImageProcess";
SDIError SDIDeviceFinder_Create(SDIDeviceFinter** outFinder);
SDIError SDIDeviceFinder_StartDiscovery(SDIDeviceFinder* finder,DeviceFinderCallBackProc callBack, void* userdata);
SDIError SDIDeviceFinder_StopDiscovery(SDIDeviceFinder* finder);
SDIError SDIDeviceFinder_SetTimeout(SDIDeviceFinder* finder, SDIInt seconds);
SDIError SDIDeviceFinder_GetDevices(SDIDeviceFinder* finder, SDIDeviceInfo** outDevices, SDIInt* outCount);
SDIError SDIDeviceFinder_Dispose(SDIDeviceFinder* finder);
bool SDIDeviceInfo_Resolve(SDIDeviceInfo* resolveDevice);
SDIError SDIScannerDriver_Create(SDIScannerDriver** driver,
          const SDIDeviceInfo* deviceInfo,
            InterruptEventCallBackProc callBack,
           void *userdata);
SDIError SDIScannerDriver_Open(SDIScannerDriver* driver);
SDIError SDIScannerDriver_Reset(SDIScannerDriver* driver);
SDIError SDIScannerDriver_GetAllKeys(SDIScannerDriver* driver, SDIChar **outKeys, SDIInt* outCount);
SDIError SDIScannerDriver_SetValue(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value, SDIInt size);
SDIError SDIScannerDriver_GetValue(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value, SDIInt size);
SDIError SDIScannerDriver_GetDefault(SDIScannerDriver* driver, SDIChar* key, SDIValueType valType, void* value);
SDIError SDIScannerDriver_GetCapability(SDIScannerDriver* driver, SDIChar* key, SDICapability* outCapability);
void SDIScannerDriver_CheckCautionStatus(SDIScannerDriver* driver);
SDIError SDIScannerDriver_UnlockAdministratorLock(SDIScannerDriver* driver);
SDIError SDIScannerDriver_LockAdministratorLock(SDIScannerDriver* driver);
SDIError SDIScannerDrive_DoScanJob(SDIScannerDriver* driver,
           SDIOperationType operationType);
bool SDIScannerDriver_CheckNextTransferEvent(SDIScannerDriver* driver, bool waitUntilReceived);
SDIError SDIScannerDriver_GetNextTransferEvent(SDIScannerDriver* driver,
              SDITransferEventType* outType,
              SDIImage* outImageData,
              SDIError* outError
             );
SDIError SDIScannerDriver_Close(SDIScannerDriver* driver);
SDIError SDIScannerDriver_Dispose(SDIScannerDriver* driver);
SDIError SDIImage_Create(SDIImage** image);
SDIInt SDIImage_GetWidth(SDIImage* image);
SDIInt SDIImage_GetHeight(SDIImage* image);
SDIInt SDIImage_GetSamplesPerPixel(SDIImage* image);
SDIInt SDIImage_GetBitsPerSample(SDIImage* image);
SDIInt SDIImage_GetPath(SDIImage* image, int8_t * buf, SDIInt bufSize);
typedef bool (*SDIImage_CheckImageIsBlankPtr)(SDIImage* image);
bool SDIImage_CheckImageIsBlank(SDIImage* image);
SDIInt SDIImage_Dispose(SDIImage* image);
typedef bool (*SDIMultipage_StartPtr)(SDIScannerDriver* driver, const char* destPath, SDIImageFormat format);
typedef bool (*SDIMultipage_AddPtr)(SDIScannerDriver* driver, const char* sourcePath);
typedef bool (*SDIMultipage_FinPtr)(SDIScannerDriver* driver);
typedef bool (*SDIConvertJpegToFormatPtr)(SDIScannerDriver* driver, const char* sourcePath, SDIImageFormat imageFormat);
bool SDIMultipage_Start(SDIScannerDriver* driver, const char* destPath, SDIImageFormat format);
bool SDIMultipage_Add(SDIScannerDriver* driver, const char* sourcePath);
bool SDIMultipage_Fin(SDIScannerDriver* driver);
bool SDIConvertJpegToFormat(SDIScannerDriver* driver, const char* sourcePath, SDIImageFormat imageFormat);
#ifndef _cplusplus
}
#endif
