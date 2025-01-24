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
//  ESCI2Scanner.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCI2Scanner.h"
CESCI2Scanner::CESCI2Scanner()
{
 PROPERTY_R ( kESVersion, CESCI2Scanner, ESString, GetVersion );
 PROPERTY_R ( kESProductName, CESCI2Scanner, ESString, GetProductName );
 PROPERTY_RW( kESDisableJobContinue, CESCI2Scanner, bool, IsDisableJobContinue, bool, SetDisableJobContinue );
 PROPERTY_RW( kESDisableKeepingCapture, CESCI2Scanner, bool, IsDisableKeepingCapture, bool, SetDisableKeepingCapture );
 PROPERTY_R ( kESBatteryStatus, CESCI2Scanner, ESNumber, GetBatteryStatus );
 PROPERTY_R ( kESErrorCode, CESCI2Scanner, ESNumber, GetErrorCode );
 PROPERTY_R ( kESSensorGlassStatus, CESCI2Scanner, ESNumber, GetSensorGlassStatus );
 PROPERTY_R ( kESScannerPositionStatus, CESCI2Scanner, ESNumber, GetScannerPositionStatus );
 PROPERTY_RW( kESSensorGlassDirtSensitivity, CESCI2Scanner, ESNumber, GetSensorGlassDirtSensitivity, ESNumber, SetSensorGlassDirtSensitivity );
 PROPERTY_RW( kESInterruptionEnabled, CESCI2Scanner, bool, IsInterruptionEnabled, bool, SetInterruptionEnabled );
 PROPERTY_R ( kESLengthPadding, CESCI2Scanner, bool, IsLengthPaddingSupported );
 PROPERTY_R ( kESAutoFeedingMode, CESCI2Scanner, bool, IsAfmEnabled );
 PROPERTY_R ( kESContinuousAutoFeedingMode, CESCI2Scanner, bool, IsContinuousAutoFeedingModeSupported );
 PROPERTY_RW( kESAutoFeedingModeTimeout, CESCI2Scanner, ESNumber, GetAutoFeedingModeTimeout, ESNumber, SetAutoFeedingModeTimeout );
 PROPERTY_R ( kESSerialNumber, CESCI2Scanner, ESString, GetSerialNumber );
 PROPERTY_R ( kESMaxImagePixels, CESCI2Scanner, ST_ES_SIZE_F, GetMaxImagePixels );
 PROPERTY_R ( kESMaxScanSizeInLongLength, CESCI2Scanner, ST_ES_SIZE_F, GetMaxScanSizeInLongLength );
 PROPERTY_R ( kESMaxLongLengthTable, CESCI2Scanner, ESDicArray, GetMaxLongLengthTable );
 PROPERTY_R ( kESMinScanSize, CESCI2Scanner, ST_ES_SIZE_F, GetMinScanSize );
 PROPERTY_RW( kESImageFormat, CESCI2Scanner, ESNumber, GetImageFormat, ESNumber, SetImageFormat );
 PROPERTY_RW( kESColorMatrixMode, CESCI2Scanner, ESNumber, GetColorMatrixMode, ESNumber, SetColorMatrixMode );
 PROPERTY_RW( kESLaminatedPaperMode, CESCI2Scanner, ESNumber, GetLaminatedPaperMode, ESNumber, SetLaminatedPaperMode );
 PROPERTY_RW( kESSkewCorrection, CESCI2Scanner, bool, IsSkewCorrectionEnabled, bool, SetSkewCorrectionEnabled );
 PROPERTY_RW( kESJPEGQuality, CESCI2Scanner, ESNumber, GetJPEGQuality, ESNumber, SetJPEGQuality );
 PROPERTY_RW( kESPaperEndDetection, CESCI2Scanner, bool, IsPaperEndDetectionEnabled, bool, SetPaperEndDetectionEnabled );
 PROPERTY_R ( kESCarrierSheetDetection, CESCI2Scanner, bool, IsCarrierSheetDetectionSupported );
 PROPERTY_RW( kESOverScan, CESCI2Scanner, bool, IsOverScanEnabled, bool, SetOverScanEnabled );
 PROPERTY_RW( kESOverScanForCropping, CESCI2Scanner, bool, IsOverScanForCroppingEnabled, bool, SetOverScanForCroppingEnabled );
 PROPERTY_RW( kESPassportCarrierSheetScan, CESCI2Scanner, bool, IsPassportCarrierSheetSupported, bool, SetPassportCarrierSheetEnabled );
 PROPERTY_R ( kESMinDoubleFeedDetectionRangeLength, CESCI2Scanner, ESFloat, GetMinDoubleFeedDetectionRangeLength );
 PROPERTY_RW( kESDoubleFeedDetectionRangeOffset, CESCI2Scanner, ESFloat, GetDoubleFeedDetectionRangeOffset, ESFloat, SetDoubleFeedDetectionRangeOffset );
 PROPERTY_RW( kESDoubleFeedDetectionRangeLength, CESCI2Scanner, ESFloat, GetDoubleFeedDetectionRangeLength, ESFloat, SetDoubleFeedDetectionRangeLength );
 PROPERTY_RW( kESLenghtDoubleFeedDetection, CESCI2Scanner, bool, IsLengthDoubleFeedDetectionEnabled, bool, SetLengthDoubleFeedDetectionEnabled );
 PROPERTY_RW( kESLengthDoubleFeedDetectionLength, CESCI2Scanner, ESFloat, GetLengthDoubleFeedDetectionLength, ESFloat, SetLengthDoubleFeedDetectionLength );
 PROPERTY_RW( kESImageDoubleFeedDetection, CESCI2Scanner, bool, IsImageDoubleFeedDetectionEnabled, bool, SetImageDoubleFeedDetectionEnabled );
 PROPERTY_RW( kESImagePaperProtection, CESCI2Scanner, bool, IsImagePaperProtectionEnabled, bool, SetImagePaperProtectionEnabled );
 PROPERTY_RW( kESFilmType, CESCI2Scanner, ESNumber, GetFilmType, ESNumber, SetFilmType );
 PROPERTY_R ( kESDetectedDocumentSize, CESCI2Scanner, ST_ES_SIZE_F, GetDetectedDocumentSize );
 PROPERTY_RW( kESAutoCropping, CESCI2Scanner, bool, IsAutoCroppingEnabled, bool, SetAutoCroppingEnabled );
 PROPERTY_RW( kESAutoCroppingInscribed, CESCI2Scanner, bool, IsAutoCroppingInscribedEnabled, bool, SetAutoCroppingInscribedEnabled );
 PROPERTY_R ( kESCroppableResolutions, CESCI2Scanner, ESAny, GetCroppableResolutions );
 PROPERTY_RW( kESCroppingSize, CESCI2Scanner, ESFloat, GetCroppingSize, ESFloat, SetCroppingSize );
 PROPERTY_RW( kESEdgeFillColor, CESCI2Scanner, ESNumber, GetEdgeFillColor, ESNumber, SetEdgeFillColor );
 PROPERTY_RW( kESEdgeFillWidthRight, CESCI2Scanner, ESFloat, GetEdgeFillWidthRight, ESFloat, SetEdgeFillWidthRight );
 PROPERTY_RW( kESEdgeFillWidthTop, CESCI2Scanner, ESFloat, GetEdgeFillWidthTop, ESFloat, SetEdgeFillWidthTop );
 PROPERTY_RW( kESEdgeFillWidthLeft, CESCI2Scanner, ESFloat, GetEdgeFillWidthLeft, ESFloat, SetEdgeFillWidthLeft );
 PROPERTY_RW( kESEdgeFillWidthBottom, CESCI2Scanner, ESFloat, GetEdgeFillWidthBottom, ESFloat, SetEdgeFillWidthBottom );
 PROPERTY_RW( kESPowerSaveTime, CESCI2Scanner, ESNumber, GetPowerSaveTime, ESNumber, SetPowerSaveTime );
 PROPERTY_RW( kESPowerOffTime, CESCI2Scanner, ESNumber, GetPowerOffTime, ESNumber, SetPowerOffTime );
 PROPERTY_RW( kESPowerOffTime2nd, CESCI2Scanner, ESNumber, GetPowerOffTime2nd, ESNumber, SetPowerOffTime2nd );
 PROPERTY_R ( kESMaxFocus, CESCI2Scanner, ESFloat, GetMaxFocus );
 PROPERTY_R ( kESMinFocus, CESCI2Scanner, ESFloat, GetMinFocus );
 PROPERTY_RW( kESFocus, CESCI2Scanner, ESFloat, GetFocus, ESFloat, SetFocus );
 PROPERTY_R ( kESFirstPCConnectionDate, CESCI2Scanner, ESString, GetFirstPCConnectionDate );
 PROPERTY_RW( kESSimplexScanCounter, CESCI2Scanner, ESNumber, GetSimplexScanCounter, ESNumber, SetSimplexScanCounter );
 PROPERTY_RW( kESDuplexScanCounter, CESCI2Scanner, ESNumber, GetDuplexScanCounter, ESNumber, SetDuplexScanCounter );
 PROPERTY_RW( kESDocumentFeederLamp1Counter, CESCI2Scanner, ESNumber, GetDocumentFeederLamp1Counter, ESNumber, SetDocumentFeederLamp1Counter );
 PROPERTY_RW( kESDocumentFeederLamp2Counter, CESCI2Scanner, ESNumber, GetDocumentFeederLamp2Counter, ESNumber, SetDocumentFeederLamp2Counter );
 PROPERTY_RW( kESPaperJamCounter, CESCI2Scanner, ESNumber, GetPaperJamCounter, ESNumber, SetPaperJamCounter );
 PROPERTY_RW( kESUltraSonicDoubleFeedCounter, CESCI2Scanner, ESNumber, GetUltraSonicDoubleFeedCounter, ESNumber, SetUltraSonicDoubleFeedCounter );
 PROPERTY_RW( kESLengthDoubleFeedCounter, CESCI2Scanner, ESNumber, GetLengthDoubleFeedCounter, ESNumber, SetLengthDoubleFeedCounter );
 PROPERTY_RW( kESImageDoubleFeedCounter, CESCI2Scanner, ESNumber, GetImageDoubleFeedCounter, ESNumber, SetImageDoubleFeedCounter );
 PROPERTY_RW( kESPaperProtectionCounter, CESCI2Scanner, ESNumber, GetPaperProtectionCounter, ESNumber, SetPaperProtectionCounter );
 PROPERTY_RW( kESRollerKitCounter, CESCI2Scanner, ESNumber, GetRollerKitCounter, ESNumber, SetRollerKitCounter );
 PROPERTY_RW( kESRetardRollerCounter, CESCI2Scanner, ESNumber, GetRetardRollerCounter, ESNumber, SetRetardRollerCounter );
 PROPERTY_RW( kESPickupRollerCounter, CESCI2Scanner, ESNumber, GetPickupRollerCounter, ESNumber, SetPickupRollerCounter );
 PROPERTY_RW( kESSeparationPadCounter, CESCI2Scanner, ESNumber, GetSeparationPadCounter, ESNumber, SetSeparationPadCounter );
 PROPERTY_RW( kESSpecialDocumentCounter, CESCI2Scanner, ESNumber, GetSpecialDocumentCounter, ESNumber, SetSpecialDocumentCounter );
 PROPERTY_RW( kESPassportCarrierSheetCounter, CESCI2Scanner, ESNumber, GetPassportCarrierSheetCounter, ESNumber, SetPassportCarrierSheetCounter );
 PROPERTY_RW( kESScanCounter, CESCI2Scanner, ESNumber, GetScanCounter, ESNumber, SetScanCounter );
 PROPERTY_RW( kESSimplexCardScanCounter, CESCI2Scanner, ESNumber, GetSimplexCardScanCounter, ESNumber, SetSimplexCardScanCounter );
 PROPERTY_RW( kESDuplexCardScanCounter, CESCI2Scanner, ESNumber, GetDuplexCardScanCounter, ESNumber, SetDuplexCardScanCounter );
 PROPERTY_RW( kESFlatbedLamp1Counter, CESCI2Scanner, ESNumber, GetFlatbedLamp1Counter, ESNumber, SetFlatbedLamp1Counter );
 PROPERTY_RW( kESFlatbedLamp2Counter, CESCI2Scanner, ESNumber, GetFlatbedLamp2Counter, ESNumber, SetFlatbedLamp2Counter );
 PROPERTY_R ( kESDocumentSeparation, CESCI2Scanner, ESNumber, GetDocumentSeparation );
 PROPERTY_R ( kESCardScanning, CESCI2Scanner, bool, IsCardScanningEnabled );
 PROPERTY_RW( kESDocumentTopCorrectionFront, CESCI2Scanner, ESFloat, GetDocumentTopCorrectionFront, ESFloat, SetDocumentTopCorrectionFront );
 PROPERTY_RW( kESDocumentTopCorrectionBack, CESCI2Scanner, ESFloat, GetDocumentTopCorrectionBack, ESFloat, SetDocumentTopCorrectionBack );
 PROPERTY_RW( kESDocumentDriveCorrectionFront, CESCI2Scanner, ESFloat, GetDocumentDriveCorrectionFront, ESFloat, SetDocumentDriveCorrectionFront );
 PROPERTY_RW( kESDocumentDriveCorrectionBack, CESCI2Scanner, ESFloat, GetDocumentDriveCorrectionBack, ESFloat, SetDocumentDriveCorrectionBack );
 PROPERTY_RW( kESLightIntensityBack, CESCI2Scanner, ESNumber, GetLightIntensityBack, ESNumber, SetLightIntensityBack );
 PROPERTY_R ( kESGuidePosition, CESCI2Scanner, ESNumber, GetGuidePosition );
 PROPERTY_R ( kESGuidelessADF, CESCI2Scanner, bool, IsGuidelessADF );
 PROPERTY_R ( kESDocumentFeederBGLevelFront, CESCI2Scanner, ESDictionary, GetDocumentFeederBGLevelFront );
 PROPERTY_R ( kESDocumentFeederBGLevelBack, CESCI2Scanner, ESDictionary, GetDocumentFeederBGLevelBack );
 PROPERTY_R ( kESPickupRollerLifeLimit, CESCI2Scanner, ESNumber, GetPickupRollerLifeLimit );
 PROPERTY_R ( kESSeparationPadLifeLimit, CESCI2Scanner, ESNumber, GetSeparationPadLifeLimit );
 PROPERTY_R ( kESRollerKitLifeLimit, CESCI2Scanner, ESNumber, GetRollerKitLifeLimit );
 PROPERTY_R ( kESRetardRollerLifeLimit, CESCI2Scanner, ESNumber, GetRetardRollerLifeLimit );
 PROPERTY_R ( kESPickupRollerNearend, CESCI2Scanner, ESNumber, GetPickupRollerNearend );
 PROPERTY_R ( kESSeparationPadNearend, CESCI2Scanner, ESNumber, GetSeparationPadNearend );
 PROPERTY_R ( kESRollerKitNearend, CESCI2Scanner, ESNumber, GetRollerKitNearend );
 PROPERTY_R ( kESRetardRollerNearend, CESCI2Scanner, ESNumber, GetRetardRollerNearend );
 PROPERTY_R ( kESWarningStatus, CESCI2Scanner, ESNumber, GetWarningStatus );
 PROPERTY_RW( kESScanningMode, CESCI2Scanner, ESNumber, GetScanningMode, ESNumber, SetScanningMode );
 PROPERTY_R ( kESUnavailableScanParameterStatus, CESCI2Scanner, ESIndexArray, GetUnavailableScanParameterStatus );
 PROPERTY_RW( kESBGColor, CESCI2Scanner, ESNumber, GetBGColor, ESNumber, SetBGColor );
 PROPERTY_RW( kESColorCounterType, CESCI2Scanner, ESNumber, GetColorCounterType, ESNumber, SetColorCounterType );
 PROPERTY_RW( kESDirectPowerOn, CESCI2Scanner, ESNumber, GetDirectPowerOn, ESNumber, SetDirectPowerOn );
 PROPERTY_RW( kESNonConnectPowerOff, CESCI2Scanner, ESNumber, GetNonConnectPowerOff, ESNumber, SetNonConnectPowerOff );
 PROPERTY_RW( kESADFPaperProtection, CESCI2Scanner, ESNumber, GetADFPaperProtection, ESNumber, SetADFPaperProtection );
 PROPERTY_RW( kESBehaviorWhenDoubleFeed, CESCI2Scanner, ESNumber, GetBehaviorWhenDoubleFeed, ESNumber, SetBehaviorWhenDoubleFeed );
 PROPERTY_RW( kESRollerKitNotifyCount, CESCI2Scanner, ESNumber, GetRollerKitNotifyCount, ESNumber, SetRollerKitNotifyCount );
 PROPERTY_RW( kESRetardRollerNotifyCount, CESCI2Scanner, ESNumber, GetRetardRollerNotifyCount, ESNumber, SetRetardRollerNotifyCount );
 PROPERTY_RW( kESSeparationPadNotifyCount, CESCI2Scanner, ESNumber, GetSeparationPadNotifyCount, ESNumber, SetSeparationPadNotifyCount );
 PROPERTY_RW( kESPickupRollerNotifyCount, CESCI2Scanner, ESNumber, GetPickupRollerNotifyCount, ESNumber, SetPickupRollerNotifyCount );
 PROPERTY_RW( kESCleaningWarningCounter, CESCI2Scanner, ESNumber, GetCleaningWarningCounter, ESNumber, SetCleaningWarningCounter );
 PROPERTY_RW( kESCleaningWarningNotify, CESCI2Scanner, ESNumber, GetCleaningWarningNotify, ESNumber, SetCleaningWarningNotify );
 PROPERTY_RW( kESCleaningWarningNotifyCount, CESCI2Scanner, ESNumber, GetCleaningWarningNotifyCount, ESNumber, SetCleaningWarningNotifyCount );
    PROPERTY_RW( kESClientApplication, CESCI2Scanner, ESNumber, GetClientApplication, ESNumber, SetClientApplication );
    PROPERTY_RW( kESBackgroundRemoval, CESCI2Scanner, ESNumber, GetBackGroundRemoval, ESNumber, SetBackGroundRemoval );
    PROPERTY_RW( kESBrightness, CESCI2Scanner, ESNumber, GetBrightness, ESNumber, SetBrightness );
    PROPERTY_RW( kESContrast, CESCI2Scanner, ESNumber, GetContrast, ESNumber, SetContrast );
    PROPERTY_RW( kESGammaScale, CESCI2Scanner, ESNumber, GetGammaScale, ESNumber, SetGammaScale );
    PROPERTY_RW( kESSharpnessFilter, CESCI2Scanner, ESNumber, GetSharpnessLevel, ESNumber, SetSharpnessLevel );
    PROPERTY_R ( kESADFLoadSupported, CESCI2Scanner, bool, IsAdfLoadSupported);
 PROPERTY_RW( kESDetectColorTypeEnabled, CESCI2Scanner, bool, IsDetectColorTypeEnabled, bool, SetDetectColorTypeEnabled );
 PROPERTY_RW( kESDetectBlankPageEnabled, CESCI2Scanner, bool, IsDetectBlankPageEnabled, bool, SetDetectBlankPageEnabled );
 PROPERTY_RW( kESDetectBlankPageLevel, CESCI2Scanner, ESNumber, GetDetectBlankPageLevel, ESNumber, SetDetectBlankPageLevel );
 PROPERTY_RW( kESSkipImageEnhancement, CESCI2Scanner, bool, IsSkipImageEnabled, bool, SetSkipImageEnabled );
 PROPERTY_R ( kESAdminLock, CESCI2Scanner, bool, IsAdminLockSupported );
 PROPERTY_R ( kESAdminLockEnabled, CESCI2Scanner, bool, IsAdminLockEnabled );
 PROPERTY_RW( kESAdminLockPassword, CESCI2Scanner, ESString, GetAdminLockPassword, ESString, SetAdminLockPassword );
 PROPERTY_R ( kESDefaultPasswordType, CESCI2Scanner, ESNumber, GetDefaultPasswordType );
this->GetAllKeys();}
CESCI2Scanner::~CESCI2Scanner()
{
}
ESErrorCode CESCI2Scanner::Initialize()
{
 return CESCI2Accessor::Initialize();
}
ESErrorCode CESCI2Scanner::SetDeviceInterface(IInterface* pDeviceInterface )
{
 return CESCI2Accessor::SetDeviceInterface( pDeviceInterface );
}
IInterface* CESCI2Scanner::GetDeviceInterface()
{
 return CESCI2Accessor::GetDeviceInterface();
}
void CESCI2Scanner::SetDelegate( IESScannerDelegate* pDelegate )
{
 CESCI2Accessor::SetDelegate( pDelegate, this );
}
void CESCI2Scanner::SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner )
{
 CESCI2Accessor::SetDelegate( pDelegate, pScanner );
}
IESScannerDelegate* CESCI2Scanner::GetDelegate()
{
 return CESCI2Accessor::GetDelegate();
}
ESErrorCode CESCI2Scanner::Open()
{
 return CESCI2Accessor::Open();
}
ESErrorCode CESCI2Scanner::Close()
{
 return CESCI2Accessor::Close();
}
bool CESCI2Scanner::IsOpened() const
{
 return CESCI2Accessor::IsOpened();
}
ESErrorCode CESCI2Scanner::Scan()
{
 return CESCI2Accessor::Scan();
}
ESErrorCode CESCI2Scanner::Cancel()
{
 return CESCI2Accessor::Cancel();
}
ESErrorCode CESCI2Scanner::Abort()
{
 return CESCI2Accessor::Abort();
}
bool CESCI2Scanner::IsScanning() const
{
 return CESCI2Accessor::IsScanning();
}
void CESCI2Scanner::SetScanning( bool bScanning )
{
 CESCI2Accessor::SetScanning( bScanning );
}
void CESCI2Scanner::SetCancelled( bool bCanncelled )
{
 CESCI2Accessor::SetCancelled( bCanncelled );
}
ESErrorCode CESCI2Scanner::DoCleaning()
{
 return CESCI2Accessor::DoCleaning();
}
ESErrorCode CESCI2Scanner::DoCalibration()
{
 return CESCI2Accessor::DoCalibration();
}
ESErrorCode CESCI2Scanner::Reset()
{
 return CESCI2Accessor::Reset();
}
bool CESCI2Scanner::IsInterrupted() const
{
 return CESCI2Accessor::IsInterrupted();
}
bool CESCI2Scanner::IsAfmEnabled() const
{
 return CESCI2Accessor::IsAfmEnabled();
}
ESErrorCode CESCI2Scanner::ScheduleAutoFeedingModeTimeout()
{
 return CESCI2Accessor::ScheduleAutoFeedingModeTimeout();
}
ESErrorCode CESCI2Scanner::StartJobInMode( ESJobMode eJobMode )
{
 return CESCI2Accessor::StartJobInMode(eJobMode);
}
ESErrorCode CESCI2Scanner::StopJobInMode( ESJobMode eJobMode )
{
 return CESCI2Accessor::StopJobInMode(eJobMode);
}
ESErrorCode CESCI2Scanner::DoAutoFocus(ESFloat* pfOutFocus)
{
 return CESCI2Accessor::DoAutoFocus(pfOutFocus);
}
ESErrorCode CESCI2Scanner::SetPanelToPushScanReady( BOOL bPushScanReady )
{
 return CESCI2Accessor::SetPanelToPushScanReady(bPushScanReady);
}
ESErrorCode CESCI2Scanner::UnlockAdministratorLock()
{
 return CESCI2Accessor::UnlockAdministratorLock();
}
ESErrorCode CESCI2Scanner::LockAdministratorLock()
{
 return CESCI2Accessor::LockAdministratorLock();
}
BOOL CESCI2Scanner::IsScannableDeviceConfig()
{
 return CESCI2Accessor::IsScannableDeviceConfig();
}
