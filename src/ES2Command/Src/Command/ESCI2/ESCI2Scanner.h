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
//  ESCI2Scanner.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Command/ESScanner.h"
#include "ESCI2Accessor.h"
class CESCI2Scanner : public CESCI2Accessor, virtual public CESScanner
{
public:
 CESCI2Scanner();
 virtual ~CESCI2Scanner();
 virtual ESErrorCode Initialize() override;
 virtual ESErrorCode SetDeviceInterface(IInterface* pDeviceInterface ) override;
 virtual IInterface* GetDeviceInterface() override;
 virtual void SetDelegate( IESScannerDelegate* pDelegate ) override;
 virtual void SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner ) override;
 virtual IESScannerDelegate* GetDelegate() override;
public:
 virtual ESErrorCode Open() override;
 virtual ESErrorCode Close() override;
 virtual bool IsOpened() const override;
 virtual ESErrorCode Scan() override;
 virtual ESErrorCode Cancel() override;
 virtual ESErrorCode Abort() override;
 virtual bool IsScanning() const override;
 virtual void SetScanning( bool bScanning ) override;
 virtual void SetCancelled( bool bCanncelled ) override;
 virtual ESErrorCode DoCleaning() override;
 virtual ESErrorCode DoCalibration() override;
 virtual ESErrorCode Reset() override;
 virtual bool IsInterrupted() const override;
 virtual bool IsAfmEnabled() const override;
 virtual ESErrorCode ScheduleAutoFeedingModeTimeout() override;
 virtual ESErrorCode StartJobInMode( ESJobMode eJobMode ) override;
 virtual ESErrorCode StopJobInMode( ESJobMode eJobMode ) override;
 virtual ESErrorCode DoAutoFocus(ESFloat* pfOutFocus) override;
 virtual ESErrorCode SetPanelToPushScanReady( BOOL bPushScanReady ) override;
 virtual ESErrorCode UnlockAdministratorLock() override;
 virtual ESErrorCode LockAdministratorLock() override;
 virtual BOOL IsScannableDeviceConfig() override;
public:
 virtual const ESStringArray& GetAllKeys() override;
 virtual ESErrorCode GetCapabilityForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult ) override;
protected:
 virtual ESStringArray GetPriorKeys() override;
protected:
 virtual void GetVersionCapability ( ESDictionary& dicResult ) override;
 virtual void GetScanSizeCapability ( ESDictionary& dicResult ) override;
 virtual void GetColorMatrixCapability ( ESDictionary& dicResult ) override;
 virtual void GetDisableJobContinueCapability ( ESDictionary& dicResult );
 virtual void GetDisableKeepingCaptureCapability ( ESDictionary& dicResult );
 virtual void GetErrorCodeCapability ( ESDictionary& dicResult );
 virtual void GetBatteryStatusCapability ( ESDictionary& dicResult );
 virtual void GetSensorGlassStatusCapability ( ESDictionary& dicResult );
 virtual void GetScannerPositionStatusCapability ( ESDictionary& dicResult );
 virtual void GetSensorGlassDirtSensitivityCapability ( ESDictionary& dicResult );
 virtual void GetInterruptionEnabledCapability ( ESDictionary& dicResult );
 virtual void GetWarningStatusCapability ( ESDictionary& dicResult );
 virtual void GetUnavailableScanParameterStatusCapability ( ESDictionary& dicResult );
 virtual void GetLengthPaddingCapability ( ESDictionary& dicResult );
 virtual void GetAutoFeedingModeCapability ( ESDictionary& dicResult );
 virtual void GetContinuousAutoFeedingModeCapability ( ESDictionary& dicResult );
 virtual void GetAutoFeedingModeTimeoutCapability ( ESDictionary& dicResult );
 virtual void GetSerialNumberCapability ( ESDictionary& dicResult );
 virtual void GetMaxImagePixelsCapability ( ESDictionary& dicResult );
 virtual void GetMaxScanSizeInLongLengthCapability ( ESDictionary& dicResult );
 virtual void GetMaxLongLengthTableCapability ( ESDictionary& dicResult );
 virtual void GetMinScanSizeCapability ( ESDictionary& dicResult );
 virtual void GetGuidePositionCapability ( ESDictionary& dicResult );
 virtual void GetGuidelessADFCapability ( ESDictionary& dicResult );
 virtual void GetImageFormatCapability ( ESDictionary& dicResult );
 virtual void GetColorMatrixModeCapability ( ESDictionary& dicResult );
 virtual void GetLaminatedPaperModeCapability ( ESDictionary& dicResult );
 virtual void GetSkewCorrectionCapability ( ESDictionary& dicResult );
 virtual void GetJPEGQualityCapability ( ESDictionary& dicResult );
 virtual void GetPaperEndDetectionCapabiliy ( ESDictionary& dicResult );
 virtual void GetCarrierSheetDetectionCapabiliy ( ESDictionary& dicResult );
 virtual void GetPassportCarrierSheetCapabiliy ( ESDictionary& dicResult );
 virtual void GetOverScanCapability ( ESDictionary& dicResult );
 virtual void GetOverScanForCroppingCapability ( ESDictionary& dicResult );
 virtual void GetMinDoubleFeedDetectionRangeLengthCapability ( ESDictionary& dicResult );
 virtual void GetDoubleFeedDetectionRangeOffsetCapability ( ESDictionary& dicResult );
 virtual void GetDoubleFeedDetectionRangeLengthCapability ( ESDictionary& dicResult );
 virtual void GetLenghtDoubleFeedDetectionCapability ( ESDictionary& dicResult );
 virtual void GetLengthDoubleFeedDetectionLengthCapability ( ESDictionary& dicResult );
 virtual void GetImageDoubleFeedDetectionCapability ( ESDictionary& dicResult );
 virtual void GetImagePaperProtectionCapability ( ESDictionary& dicResult );
 virtual void GetDetectedDocumentSizeCapability ( ESDictionary& dicResult );
 virtual void GetDocumentSeparationCapability ( ESDictionary& dicResult );
 virtual void GetCardScanningCapability ( ESDictionary& dicResult );
 virtual void GetAutoCroppingCapability ( ESDictionary& dicResult );
 virtual void GetAutoCroppingInscribedCapability ( ESDictionary& dicResult );
 virtual void GetCroppableResolutionsCapability ( ESDictionary& dicResult );
 virtual void GetCroppingSizeCapability ( ESDictionary& dicResult );
 virtual void GetFilmTypeCapability ( ESDictionary& dicResult );
 virtual void GetEdgeFillColorCapability ( ESDictionary& dicResult );
 virtual void GetEdgeFillWidthCapability ( ESDictionary& dicResult );
 virtual void GetPowerSaveTimeCapability ( ESDictionary& dicResult );
 virtual void GetPowerOffTimeCapability ( ESDictionary& dicResult );
 virtual void GetPowerOffTime2ndCapability ( ESDictionary& dicResult );
 virtual void GetMaxFocusCapability ( ESDictionary& dicResult );
 virtual void GetMinFocusCapability ( ESDictionary& dicResult );
 virtual void GetFocusCapability ( ESDictionary& dicResult );
 virtual void GetFirstPCConnectionDateCapability ( ESDictionary& dicResult );
 virtual void GetSimplexScanCounterCapability ( ESDictionary& dicResult );
 virtual void GetDuplexScanCounterCapability ( ESDictionary& dicResult );
 virtual void GetDocumentFeederLamp1CounterCapability ( ESDictionary& dicResult );
 virtual void GetDocumentFeederLamp2CounterCapability ( ESDictionary& dicResult );
 virtual void GetPaperJamCounterCapability ( ESDictionary& dicResult );
 virtual void GetUltraSonicDoubleFeedCounterCapability ( ESDictionary& dicResult );
 virtual void GetLengthDoubleFeedCounterCapability ( ESDictionary& dicResult );
 virtual void GetImageDoubleFeedCounterCapability ( ESDictionary& dicResult );
 virtual void GetPaperProtectionCounterCapability ( ESDictionary& dicResult );
 virtual void GetRollerKitCounterCapability ( ESDictionary& dicResult );
 virtual void GetRetardRollerCounterCapability ( ESDictionary& dicResult );
 virtual void GetPickupRollerCounterCapability ( ESDictionary& dicResult );
 virtual void GetSeparationPadCounterCapability ( ESDictionary& dicResult );
 virtual void GetSpecialDocumentCounterCapability ( ESDictionary& dicResult );
 virtual void GetPassportCarrierSheetCounterCapability ( ESDictionary& dicResult );
 virtual void GetScanCounterCapability ( ESDictionary& dicResult );
 virtual void GetSimplexCardScanCounterCapability ( ESDictionary& dicResult );
 virtual void GetDuplexCardScanCounterCapability ( ESDictionary& dicResult );
 virtual void GetFlatbedLamp1CounterCapability ( ESDictionary& dicResult );
 virtual void GetFlatbedLamp2CounterCapability ( ESDictionary& dicResult );
 virtual void GetDocumentTopCorrectionFrontCapability ( ESDictionary& dicResult );
 virtual void GetDocumentTopCorrectionBackCapability ( ESDictionary& dicResult );
 virtual void GetDocumentDriveCorrectionFrontCapability ( ESDictionary& dicResult );
 virtual void GetDocumentDriveCorrectionBackCapability ( ESDictionary& dicResult );
 virtual void GetLightIntensityBackCapability ( ESDictionary& dicResult );
 virtual void GetDocumentFeederBGLevelFrontCapability ( ESDictionary& dicResult );
 virtual void GetDocumentFeederBGLevelBackCapability ( ESDictionary& dicResult );
 virtual void GetPickupRollerLifeLimitCapability ( ESDictionary& dicResult );
 virtual void GetRollerKitLifeLimitCapability ( ESDictionary& dicResult );
 virtual void GetRetardRollerLifeLimitCapability ( ESDictionary& dicResult );
 virtual void GetSeparationPadLifeLimitCapability ( ESDictionary& dicResult );
 virtual void GetPickupRollerNearendCapability ( ESDictionary& dicResult );
 virtual void GetRollerKitNearendCapability ( ESDictionary& dicResult );
 virtual void GetRetardRollerNearendCapability ( ESDictionary& dicResult );
 virtual void GetSeparationPadNearendCapability ( ESDictionary& dicResult );
 virtual void GetScanningModeCapability ( ESDictionary& dicResult );
 virtual void GetBGColorCapability ( ESDictionary& dicResult );
 virtual void GetDirectPowerOnCapability ( ESDictionary& dicResult );
 virtual void GetNonConnectPowerOffCapability ( ESDictionary& dicResult );
 virtual void GetADFPaperProtectionCapability ( ESDictionary& dicResult );
 virtual void GetBehaviorWhenDoubleFeedCapability ( ESDictionary& dicResult );
 virtual void GetCleaningWarningNotifyCountCapability ( ESDictionary& dicResult );
 virtual void GetRollerKitNotifyCountCapability ( ESDictionary& dicResult );
 virtual void GetRetardRollerNotifyCountCapability ( ESDictionary& dicResult );
 virtual void GetSeparationPadNotifyCountCapability ( ESDictionary& dicResult );
 virtual void GetPickupRollerNotifyCountCapability ( ESDictionary& dicResult );
 virtual void GetCleaningWarningCounterCapability ( ESDictionary& dicResult );
 virtual void GetCleaningWarningNotifyCapability ( ESDictionary& dicResult );
 virtual void GetAdminLockCapability ( ESDictionary& dicResult );
 virtual void GetAdminLockEnabledCapability ( ESDictionary& dicResult );
 virtual void GetAdminLockPasswordCapability ( ESDictionary& dicResult );
 virtual void GetDefaultPasswordTypeCapability ( ESDictionary& dicResult );
 virtual void GetClientApplicationCapability ( ESDictionary& dicResult );
    virtual void GetBrightnessCapablity ( ESDictionary& dicResult );
    virtual void GetContrastCapablity ( ESDictionary& dicResult );
    virtual void GetGammaScaleCapablity ( ESDictionary& dicResult );
    virtual void GetBackgroundRemovalCapablity ( ESDictionary& dicResult );
    virtual void GetSharpnessFilterCapablity ( ESDictionary& dicResult );
    virtual void GetADFLoadCapablity (ESDictionary& dicResult );
 virtual void GetDetectBlankPageCapablity ( ESDictionary& dicResult );
 virtual void GetDetectBlankPageLevelCapablity ( ESDictionary& dicResult );
 virtual void GetDetectColorTypeCapablity ( ESDictionary& dicResult );
 virtual void GetSkipImageCapablity ( ESDictionary& dicResult );
 virtual void GetColorCounterTypeCapability ( ESDictionary& dicResult );
public:
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue ) override;
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue ) override;
protected:
 ESString GetWorkFolder() override;
 ESErrorCode SetWorkFolder( ESString strWorkFolder ) override;
 ESErrorCode GetErrorStatus() override;
 virtual ESNumber GetBufferSize() override;
 ESErrorCode SetBufferSize( ESNumber nBufferSize ) override;
 ENUM_ES_HASH_TYPE GetMaintenanceHashType() override;
 bool IsAuthenticationSupported() override;
 bool IsAuthenticationEnabled() override;
 ESErrorCode SetAuthenticationEnabled( bool bEnabled ) override;
 ESString GetAuthUserName() override;
 ESErrorCode SetAuthUserName( ESString strAuthUserName ) override;
 ESString GetAuthPassword() override;
 ESErrorCode SetAuthPassword( ESString strAuthPassword ) override;
 ESString GetProductName() override;
 ESIndexSet GetSupportedFunctionalUnitTypes() override;
 ESFunctionalUnitType GetFunctionalUnitType() override;
 ESErrorCode SetFunctionalUnitType( ESNumber nFunctionalUnitType ) override;
 ESAny GetSupportedXResolutions() override;
 ESAny GetSupportedYResolutions() override;
 ESNumber GetXResolution() override;
 ESNumber GetYResolution() override;
 ESErrorCode SetXResolution( ESNumber xResolution ) override;
 ESErrorCode SetYResolution( ESNumber yResolution ) override;
 ESNumber GetOpticalResolution() override;
 ST_ES_SIZE_F GetMaxScanSize() override;
 ST_ES_RECT_F GetScanArea() override;
 ESErrorCode SetScanArea( ST_ES_RECT_F rcScanArea ) override;
 ST_ES_RECT_UN32 GetScanAreaInPixel() override;
 ESErrorCode SetScanAreaInPixel( ST_ES_RECT_UN32 rcScanAreaInPixel ) override;
 ST_ES_SIZE_F GetScanSize() override;
 ESErrorCode SetScanSize( ST_ES_SIZE_F sizeScan ) override;
 virtual ST_ES_SIZE_UN32 GetScanSizeInPixel() override;
 virtual ESErrorCode SetScanSizeInPixel( ST_ES_SIZE_UN32 sizeScan ) override;
 virtual ESFloat GetXOffsetMargin() override;
 virtual ESErrorCode SetXOffsetMargin( ESFloat fMargin ) override;
 virtual ESFloat GetYOffsetMargin() override;
 virtual ESErrorCode SetYOffsetMargin( ESFloat fMargin ) override;
 ESIndexSet GetSupportedColorFormats() override;
 ESNumber GetColorFormat() override;
 ESErrorCode SetColorFormat( ESNumber nColorFormat ) override;
 ESNumber GetBitsPerSample() override;
 ESNumber GetSamplesPerPixel() override;
 ESNumber GetBitsPerPixel() override;
 ESAny GetColorMatrix() override;
 ESErrorCode SetColorMatrix( ESFloatArray arColorMatrix ) override;
 ESIndexSet GetSupportedGammaModes() override;
 ESGammaMode GetGammaMode() override;
 ESErrorCode SetGammaMode( ESNumber nGammaMode ) override;
 ESAny GetGammaTableMono () override;
 ESAny GetGammaTableRed () override;
 ESAny GetGammaTableGreen() override;
 ESAny GetGammaTableBlue () override;
 ESErrorCode SetGammaTableMono ( ESIndexArray arGammaTable ) override;
 ESErrorCode SetGammaTableRed ( ESIndexArray arGammaTable ) override;
 ESErrorCode SetGammaTableGreen( ESIndexArray arGammaTable ) override;
 ESErrorCode SetGammaTableBlue ( ESIndexArray arGammaTable ) override;
 ESAny GetSupportedThreshold() override;
 ESNumber GetThreshold() override;
 ESErrorCode SetThreshold( ESNumber nThreshold ) override;
 ESIndexSet GetSupportedQuietModes() override;
 ESQuietMode GetQuietMode() override;
 ESErrorCode SetQuietMode( ESNumber nQuietMode) override;
 bool IsFeederSupported() override;
 bool IsFeederEnabled() override;
 ESDuplexType GetDuplexType() override;
 bool IsDuplexSupported() override;
 bool IsDuplexEnabled() override;
 ESErrorCode SetDuplexEnabled( bool bEnabled ) override;
 ESIndexSet GetSupportedDoubleFeedDetections() override;
 ESDoubleFeedDetection GetDoubleFeedDetection() override;
 ESErrorCode SetDoubleFeedDetection( ESNumber nDoubleFeedDetection ) override;
 bool IsDocumentLoaded() override;
 ESNumber GetPagesToBeScanned() override;
 ESErrorCode SetPagesToBeScanned( ESNumber nPagesToBeScanned ) override;
 bool IsCleaningSupported() override;
 bool IsCalibrationSupported() override;
 bool IsCaptureCommandSupported() override;
 ESErrorCode SetCaptureCommandSupported( bool bSupported ) override;
private:
 ACCESSOR_MAP m_mapAccessor;
 ESStringArray m_arAllKeys;
 typedef std::function<void(CESCI2Scanner*, ESDictionary&)> FN_CAPA;
 typedef std::map< ESString, FN_CAPA > CAPA_MAP;
 typedef CAPA_MAP::value_type CAPA_PAIR;
 CAPA_MAP m_funcCapability;
};
