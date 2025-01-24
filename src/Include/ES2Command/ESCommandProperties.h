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
//  ESCommandProperties.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../es2CommnoType.h"
typedef enum {
 kESErrorNoError = 0,
 kESErrorFatalError = 1,
 kESErrorInvalidParameter = 2,
 kESErrorMemoryError = 100,
 kESErrorSequenceError = 101,
 kESErrorFileWriteError = 102,
 kESErrorFileReadError = 103,
 kESErrorScanAreaTooLargeError = 104,
 kESErrorDataSendFailure = 200,
 kESErrorDataReceiveFailure = 201,
 kESErrorInvalidResponse = 202,
 kESErrorDeviceOpenError = 203,
 kESErrorDeviceInUse = 300,
 kESErrorDeviceInBusy = 301,
 kESErrorPaperEmpty = 302,
 kESErrorPaperJam = 303,
 kESErrorPaperDoubleFeed = 304,
 kESErrorCoverOpen = 305,
 kESErrorTrayClose = 307,
 kESErrorCRLock = 308,
 kESErrorLampError = 309,
 kESErrorLampTime = 310,
 kESErrorAuthFailure = 311,
 kESErrorNoPermission = 312,
 kESErrorLowBattery = 313,
 kESErrorFocusError = 314,
 kESErrorDeviceFatalError = 315,
 kESErrorCRSheetSensorError = 316,
 kESErrorPaperProtect = 317,
 kESErrorGAPSensorError = 318,
 kESErrorPaperDoubleFeed2 = 319,
 kESErrorPoseError = 320,
 kESErrorSeparationLeverError = 321,
 kESErrorETSensorError = 322,
    kESErrorADFLiftError = 323,
 kESErrorUserAuthEnabled = 324,
    kESErrorPrintStackerError = 325,
    kESErrorPaperRemoveError = 326,
    kESErrorSkewDetectError = 327,
 kESErrorPESensorError = 328,
} ESErrorCode;
typedef enum {
 kESErrorStatusNoError = kESErrorNoError,
 kESErrorStatusFatalError = kESErrorFatalError,
 kESErrorStatusDeviceInBusy = kESErrorDeviceInBusy,
 kESErrorStatusPaperEmpty = kESErrorPaperEmpty,
 kESErrorStatusPaperJam = kESErrorPaperJam,
 kESErrorStatusPaperDoubleFeed = kESErrorPaperDoubleFeed,
 kESErrorStatusCoverOpen = kESErrorCoverOpen,
 kESErrorStatusTrayClose = kESErrorTrayClose,
 kESErrorStatusCRLock = kESErrorCRLock,
 kESErrorStatusLampError = kESErrorLampError,
 kESErrorStatusLampTime = kESErrorLampTime,
 kESErrorStatusAuthFailure = kESErrorAuthFailure,
 kESErrorStatusNoPermission = kESErrorNoPermission,
 kESErrorStatusLowBattery = kESErrorLowBattery,
 kESErrorStatusCRSheetSensorError = kESErrorCRSheetSensorError,
 kESErrorStatusPaperProtect = kESErrorPaperProtect,
 kESErrorStatusGAPSensorError = kESErrorGAPSensorError,
 kESErrorStatusPoseError = kESErrorPoseError,
 kESErrorStatusSeparationLeverError = kESErrorSeparationLeverError,
 kESErrorStatusETSensorError = kESErrorETSensorError,
    kESErrorStatusADFLiftError = kESErrorADFLiftError,
    kESErrorStatusPrintStackerError = kESErrorPrintStackerError,
    kESErrorStatusPaperRemoveError= kESErrorPaperRemoveError,
    kESErrorStatusSkewDetectError = kESErrorSkewDetectError,
 kESErrorStatusPESensorError = kESErrorPESensorError,
} ESErrorStatus;
typedef enum {
 kESScannerPositionStatusFlat = 0,
 kESScannerPositionStatusTilt = 1,
 kESScannerPositionStatusInvalid = 2,
} ESScannerPositionStatus;
typedef enum {
 kESDocumentSeparationStatusOff = 0,
 kESDocumentSeparationStatusOn = 1,
 kESDocumentSeparationStatusSoft = 2,
} ESDocumentSeparationStatus;
typedef enum {
 kESBatteryStatusNone = 0,
 kESBatteryStatusLow = 1,
} ESBatteryStatus;
typedef enum {
 kESSensorGlassNone = 0,
 kESSensorGlassDirty = 1,
} ESSensorGlassStatus;
typedef enum {
 kESWarningNone = 0,
 kESWarningNeedCleaning = 1,
} ESWarningStatus;
typedef enum {
 kESUnavailableScanParameterStatusAll = 0,
 kESUnavailableScanParameterStatusAFMC= 1,
 kESUnavailableScanParameterStatusPCS = 2,
} ESUnavailableScanParameterStatus;
typedef enum {
 kESCommandTypeESCI = 0,
 kESCommandTypeESCI2 = 1,
} ESCommandType;
typedef enum {
 kESFunctionalUnitUnknown = 0,
 kESFunctionalUnitFlatbed = 1,
 kESFunctionalUnitDocumentFeeder = 2,
 kESFunctionalUnitTransparent = 3,
 kESFunctionalUnitTPUAreaGuide = 6,
} ESFunctionalUnitType;
typedef enum {
 kESColorFormatMonoDropR1 = 0x0101,
 kESColorFormatMonoDropG1 = 0x0201,
 kESColorFormatMonoDropB1 = 0x0401,
 kESColorFormatMono1 = 0x0801,
 kESColorFormatMonoDropR8 = 0x0108,
 kESColorFormatMonoDropG8 = 0x0208,
 kESColorFormatMonoDropB8 = 0x0408,
 kESColorFormatMono8 = 0x0808,
 kESColorFormatMonoDropR16 = 0x0110,
 kESColorFormatMonoDropG16 = 0x0210,
 kESColorFormatMonoDropB16 = 0x0410,
 kESColorFormatMono16 = 0x0810,
 kESColorFormatRGB3 = 0x0701,
 kESColorFormatRGB24 = 0x0708,
 kESColorFormatRGB48 = 0x0710,
} ESColorFormat;
typedef enum {
 kESColorFormatMaskBitDepth = 0x00FF,
 kESColorFormatMaskChannel = 0xFF00,
 kESColorFormatMaskRChannel = 0x0100,
 kESColorFormatMaskGChannel = 0x0200,
 kESColorFormatMaskBChannel = 0x0400,
 kESColorFormatMaskMChannel = 0x0800,
 kESColorFormatMaskRGBChannel = 0x0700,
} ESColorFormatMask;
enum {
 kESHalftoneNone = 0x01,
 kESHalftoneA = 0x00,
 kESHalftoneB = 0x10,
 kESHalftoneC = 0x20,
 kESHalftoneTET = 0x03,
 kESHalftoneDitherA = 0x80,
 kESHalftoneDitherB = 0x90,
 kESHalftoneDitherC = 0xA0,
 kESHalftoneDitherD = 0xB0,
 kESHalftoneUserDefinedDitherA = 0xC0,
 kESHalftoneUserDefinedDitherB = 0xD0,
};
typedef UInt8 ESHalftone;
typedef enum {
 kESImageFormatRaw = 0,
 kESImageFormatJPEG = 1,
} ESImageFormat;
enum {
 kESGammaMode10 = 0x03,
 kESGammaMode18 = 0x04,
 kESGammaMode22 = 0x22,
};
typedef UInt8 ESGammaMode;
enum {
 kESGammaChannelMaster = 'M',
 kESGammaChannelRed = 'R',
 kESGammaChannelGreen = 'G',
 kESGammaChannelBlue = 'B',
};
typedef UInt8 ESGammaChannel;
enum {
 kESScanningModeNormal = 0x00,
 kESScanningModeHighSpeed = 0x01,
};
typedef UInt8 ESScanningMode;
enum {
 kESQuietModePreferDeviceSetting = 0x00,
 kESQuietModeOff = 0x01,
 kESQuietModeOn = 0x02,
};
typedef UInt8 ESQuietMode;
enum {
 kESLaminatedPaperModeOff = 0,
 kESLaminatedPaperModeOn = 1,
};
typedef UInt8 ESLaminatedPaperMode;
typedef enum {
 kESColorMatrixUnit = 0,
 kESColorMatrix8 = 1,
 kESColorMatrix16 = 2,
} ESColorMatrixMode;
enum {
 kESDuplexType1Pass = 1,
    kESDuplexType2Pass = 2,
};
typedef UInt8 ESDuplexType;
typedef enum {
 kESLampModeDefault = 0x00,
 kESLampModeUseLamp1 = 0x01,
 kESLampModeUseLamp2 = 0x02,
} ESLampMode;
enum {
 kESDoubleFeedDetectionDisable = 0x00,
 kESDoubleFeedDetectionLow = 0x01,
 kESDoubleFeedDetectionHigh = 0x02,
 kESDoubleFeedDetectionVeryLow = 0x03,
};
typedef UInt8 ESDoubleFeedDetection;
enum {
 kESFocusDefault = 0x40,
 kESFocusAuto = 0xFF,
};
typedef UInt8 ESFocus;
typedef enum {
 kESEdgeFillColorWhite = 0,
 kESEdgeFillColorBlack = 1,
} ESEdgeFillColor;
typedef enum {
 kESDigitalICEDisable = 0,
 kESDigitalICEEnable = 1,
 kESDigitalICELiteEnable = 2,
} ESDigitalICE;
typedef enum {
 kESGuidePositionLeft = 0,
 kESGuidePositionCenter = 1,
 kESGuidePositionRight = 2,
} ESGuidePosition;
enum {
 kESFilmTypePositive = 0,
 kESFilmTypeNegative = 1,
};
typedef UInt8 ESFilmType;
enum {
 kESJobModeNone = 0,
 kESJobModeStandard = 1,
 kESJobModeContinue = 2,
 kESJobModeAFM = 3,
 kESJobModeAFMC = 4,
};
typedef UInt8 ESJobMode;
enum {
 kESSensorGlassDirtSensitivityOff = 0,
 kESSensorGlassDirtSensitivityLow = 1,
 kESSensorGlassDirtSensitivityNormal = 2,
};
typedef UInt8 ESSensorGlassDirtSensitivity;
enum {
 kESBGColorWhite = 0,
 kESBGColorBlack = 1,
 kESBGColorGray = 2,
};
typedef UInt8 ESBGColor;
enum {
    kESClientApplicationES2 = 0,
    kESClientApplicationESS = 1
};
typedef UInt8 ESClientApplication;
enum {
    kESBackgroundRemovalLevelOff = 0,
    kESBackgroundRemovalLevelLow = 1,
    kESBackgroundRemovalLevelHigh = 2,
};
typedef UInt8 ENUM_ES_BACKGROUNDREMOVAL_LEVEL;
enum {
    kESSharpnessFilterLevelSmoothingHigh = 8,
    kESSharpnessFilterLevelSmoothingMiddle = 7,
    kESSharpnessFilterLevelSmoothingLow = 6,
    kESSharpnessFilterLevelSmoothingVeryLow = 5,
    kESSharpnessFilterLevelNorm = 0,
    kESSharpnessFilterLevelSharpVeryLow = 1,
    kESSharpnessFilterLevelSharpLow = 2,
    kESSharpnessFilterLevelSharpMiddle = 3,
    kESSharpnessFilterLevelSharpHigh = 4,
};
typedef UInt8 ENUM_ES_SHARPNESSFILTER_LEVEL;
enum {
 kESDefaultPasswordTypeSerial = 0,
 kESDefaultPasswordTypeUnique = 1,
};
typedef UInt8 ENUM_ES_DEFAULTPASSWORD_TYPE;
enum {
 kESDirectPowerOn_Off = 0,
 kESDirectPowerOn_On = 1,
};
typedef UInt8 ENUM_ES_DIRECTPOWERON_MODE;
enum {
 kESNonConnectPowerOff_Off = 0,
 kESNonConnectPowerOff_On = 1,
};
typedef UInt8 ENUM_ES_NONCONNECTPOWEROFF_MODE;
enum {
 kESADFPaperProtection_Off = 0,
 kESADFPaperProtection_Low = 1,
 kESADFPaperProtection_Normal = 2,
 kESADFPaperProtection_High = 3,
};
typedef UInt8 ENUM_ES_ADFPAPERPROTECTION_MODE;
enum {
 kESBehaviorWhenDoubleFeed_Immediately = 0,
 kESBehaviorWhenDoubleFeed_StopAfterEjecting = 1,
};
typedef UInt8 ENUM_ES_BEHAVIORWHENDOUBLEFEED_MODE;
enum {
 kESCleaningWarningNotify_Off = 0,
 kESCleaningWarningNotify_On = 1,
};
typedef UInt8 ENUM_ES_CLEANINGWARNINGNOTIFY_MODE;
enum {
 kESHashTypeTypeNone = 0,
 kESHashType1 = 1,
};
typedef UInt8 ENUM_ES_HASH_TYPE;
typedef enum {
 kESConnectionLocal = 0,
 kESConnectionNetworkIS = 1,
 kESConnectionNetworkNT = 2,
 kESConnectionInterpreter = 3,
} ESConnectionType;
enum {
 kESColorCounterTypePref = 0,
 kESColorCounterTypeColor = 1,
 kESColorCounterTypeMono = 2,
};
typedef UInt8 ENUM_ES_COLORCOUNTER_TYPE;
STATIC_CONST_KEY ES_CNCT_KEY_ROOT = ES_STRING("ConnectionSetting");
STATIC_CONST_KEY ES_CNCT_KEY_TYPE = ES_STRING("ConnectType");
STATIC_CONST_KEY ES_CNCT_KEY_INTERNALNAME = ES_STRING("InternalName");
STATIC_CONST_KEY ES_CNCT_KEY_VID = ES_STRING("VID");
STATIC_CONST_KEY ES_CNCT_KEY_PID = ES_STRING("PID");
STATIC_CONST_KEY ES_CNCT_KEY_SERIAL_NUMBER = ES_STRING("SERIAL_NUMBER");
STATIC_CONST_KEY ES_CNCT_KEY_ADDRESS = ES_STRING("Address");
STATIC_CONST_KEY ES_CNCT_KEY_CONNECTION_TIMEOUT = ES_STRING("ConnectionTimeout");
STATIC_CONST_KEY ES_CNCT_KEY_COMMUNICATION_TIMEOUT = ES_STRING("CommunicationTimeout");
STATIC_CONST_KEY ES_CNCT_KEY_INTERPRETER_NAME = ES_STRING("InterpreterName");
