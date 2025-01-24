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
//  ESCIScanner.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Command/ESScanner.h"
#include "ESCIAccessor.h"
#include "../ModelInfo.h"
class CESCIScanner : public CESCIAccessor, virtual public CESScanner
{
public:
 CESCIScanner();
 virtual ~CESCIScanner();
 virtual ESErrorCode Initialize() override;
 virtual ESErrorCode SetDeviceInterface(IInterface* pDeviceInterface ) override;
 virtual IInterface* GetDeviceInterface() override;
 virtual void SetDelegate( IESScannerDelegate* pDelegate ) override;
 virtual void SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner ) override;
 virtual IESScannerDelegate* GetDelegate() override;
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
 virtual ESErrorCode DoAutoFocus( ESFloat* pfOutFocus ) override;
 virtual ESErrorCode SetPanelToPushScanReady( BOOL bPushScanReady ) override;
 virtual ESErrorCode UnlockAdministratorLock() override;
 virtual ESErrorCode LockAdministratorLock() override;
 virtual const ESStringArray& GetAllKeys() override;
 virtual ESErrorCode GetCapabilityForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult ) override;
protected:
 bool IsSupportedLogFunction(ESCILogFunctionKey function);
 virtual void GetVersionCapability ( ESDictionary& dicResult ) override;
 virtual void GetColorMatrixCapability ( ESDictionary& dicResult ) override;
 void GetDisableJobContinueCapability ( ESDictionary& dicResult );
 void GetMaxScanSizeInLongLengthCapability ( ESDictionary& dicResult );
 void GetWarmingUpCapability ( ESDictionary& dicResult );
 void GetButtonStatusCapability ( ESDictionary& dicResult );
 void GetLampModeCapability ( ESDictionary& dicResult );
 void GetHalftoneCapability ( ESDictionary& dicResult );
 void GetMaxFocusCapability ( ESDictionary& dicResult );
 void GetMinFocusCapability ( ESDictionary& dicResult );
 void GetFocusCapability ( ESDictionary& dicResult );
 void GetDigitalICECapability ( ESDictionary& dicResult );
 void GetFilmTypeCapability ( ESDictionary& dicResult );
 void GetScanningModeCapability ( ESDictionary& dicResult );
 void GetColorMatrixModeCapability ( ESDictionary& dicResult );
 void GetDetectedDocumentSizeCapability ( ESDictionary& dicResult );
 void GetSimplexScanCounterCapability ( ESDictionary& dicResult );
 void GetDuplexScanCounterCapability ( ESDictionary& dicResult );
 void GetCaptureCommandSupportedCapability ( ESDictionary& dicResult );
 void GetShouldIgnoreCancelFromScannerCapability ( ESDictionary& dicResult );
 void GetGuidePositionReadOnlyCapability ( ESDictionary& dicResult );
 void GetGuidePositionCapability ( ESDictionary& dicResult );
 void GetLamp1CounterCapability ( ESDictionary& dicResult );
 void GetLamp2CounterCapability ( ESDictionary& dicResult );
 void GetPickupRollerCounterCapability ( ESDictionary& dicResult );
 void GetScanCounterCapability ( ESDictionary& dicResult );
 void GetPaperEndDetectionCapability ( ESDictionary& dicResult );
 void GetOverScanCapability ( ESDictionary& dicResult );
 void GetPowerOffTimeCapability ( ESDictionary& dicResult );
 void GetLightIntensityCapability (ESDictionary& dicResult);
public:
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue ) override;
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue ) override;
protected:
 ESString GetWorkFolder() override;
 ESErrorCode SetWorkFolder( ESString strWorkFolder ) override;
 ESErrorCode GetErrorStatus() override;
 virtual ESNumber GetBufferSize() override;
 ESErrorCode SetBufferSize( ESNumber nBufferSize ) override;
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
 typedef std::function<void(CESCIScanner*, ESDictionary&)> FN_CAPA;
 typedef std::map< ESString, FN_CAPA > CAPA_MAP;
 typedef CAPA_MAP::value_type CAPA_PAIR;
 CAPA_MAP m_funcCapability;
};
