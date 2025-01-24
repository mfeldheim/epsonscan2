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
//  ESCIAccessor.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "ESCICommand.h"
#include "Utils/event_caller.hpp"
enum {
 kBitDepth1 = 0x01,
 kBitDepth8 = 0x08,
 kBitDepth16 = 0x10,
};
typedef UInt8 ENUM_ESCI_BIT_DEPTH;
enum {
 kColorModeMono = 0x00,
 kColorModeMonoDropR = 0x10,
 kColorModeMonoDropG = 0x20,
 kColorModeMonoDropB = 0x30,
 kColorModeLineSeq = 0x12,
 kColorModePixelSeq = 0x13,
 kColorModeRGB = kColorModePixelSeq,
};
typedef UInt8 ENUM_ESCI_CLOLOR_MODE;
#define FOCUS_PHYSICAL_TO_COMMAND(x) (((x) * 10.0) + 0x40)
#define FOCUS_COMMAND_TO_PHYSICAL(x) (((x) - 0x40) / 10.0)
class CESCIAccessor : public CESCICommand
{
public:
 CESCIAccessor();
 virtual ~CESCIAccessor();
 void Setup();
 ESErrorCode Finalize();
protected:
 ESErrorCode Open();
 ESErrorCode Close();
 bool IsOpened() const;
 void DeviceDisconnected() override;
 ESErrorCode CaptureScanner();
 ESErrorCode ReleaseScanner();
 ESErrorCode StartJobInMode( ESJobMode eJobMode );
 ESErrorCode StopJobInMode( ESJobMode eJobMode );
 ESErrorCode StartJobInStandard();
 ESErrorCode StopJobInStandard();
 ESErrorCode StartJobInContinue();
 ESErrorCode StopJobInContinue();
 ESJobMode GetJobMode();
 ESErrorCode SetJobMode( ESJobMode eJobMode );
 bool IsDisableJobContinue();
 ESErrorCode SetDisableJobContinue( bool bDisableJobContinue );
protected:
 ESErrorCode Scan();
 CESScannedImage* CreateImageInstance();
 ESErrorCode ScanForDigitalICE();
 ESErrorCode ScanForFilmICE();
 ESErrorCode ScanForPrintICE();
 ESErrorCode ScanForDocumentFeeder();
 ESErrorCode ScanForNormal();
 ESErrorCode Cancel();
 virtual ESErrorCode ApplyColorMatrix( ES_CMN_FUNCS::BUFFER::IESBuffer& cScannedData, UInt32 nDataLength ) override;
 bool ShouldObserveButtonWithCommand(bool initialize = false);
 DWORD ButtonObservationInterval();
 void StartButtonChecking();
 void StopButtonChecking();
protected:
 ESErrorCode GetIdentity();
 ESErrorCode GetExtIdentity();
 ESErrorCode GetStatus();
 ESErrorCode Reset();
public:
 virtual ESString GetVersion();
 virtual ESErrorCode GetErrorStatus() override;
 virtual bool IsShouldIgnoreCancelFromScanner() override;
 ESErrorCode SetShouldIgnoreCancelFromScanner( bool bIgnore );
 virtual bool IsCaptureCommandSupported() override;
 ESErrorCode SetCaptureCommandSupported( bool bSupported );
 virtual bool IsCaptured() override;
 virtual void SetCaptured( bool bCaptured ) override;
 virtual ESNumber GetBufferSize() override;
 ESErrorCode SetBufferSize( ESNumber nBufferSize );
 virtual bool IsDumb() override;
 virtual bool IsWarmingUp() override;
 virtual bool IsAuthenticationSupported() override;
 bool IsAuthenticationEnabled() override;
 ESErrorCode SetAuthenticationEnabled( bool bEnabled );
 virtual ESString GetAuthUserName() override;
 virtual ESErrorCode SetAuthUserName( ESString strAuthUserName );
 virtual ESString GetAuthPassword() override;
 virtual ESErrorCode SetAuthPassword( ESString strAuthPassword );
 ESString GetProductName() override;
 bool IsPowerOffSupported();
 ESNumber GetPowerOffTime();
 ESErrorCode SetPowerOffTime( ESNumber nPowerOffTime );
 bool IsPushButtonSupported();
 UInt8 GetButtonStatus();
 ENUM_ESCI_OPTION_CONTROL GetOptionControl();
 bool SetOptionControl( ENUM_ESCI_OPTION_CONTROL eOptionControl );
 ESIndexSet GetSupportedFunctionalUnitTypes();
 ESFunctionalUnitType GetFunctionalUnitType();
 ESErrorCode SetFunctionalUnitType( ESNumber nFunctionalUnitType );
 ESAny GetSupportedXResolutions();
 ESAny GetSupportedYResolutions();
 ESNumber GetXResolution();
 ESNumber GetYResolution();
 ESErrorCode SetXResolution( ESNumber xResolution );
 ESErrorCode SetYResolution( ESNumber yResolution );
 ESNumber GetOpticalResolution();
 ST_ES_SIZE_F GetMaxScanSize();
 ST_ES_RECT_F GetScanArea();
 ESErrorCode SetScanArea( ST_ES_RECT_F rcScanArea, bool bShouldAlign );
 ESErrorCode SetScanArea( ST_ES_RECT_F rcScanArea );
 ST_ES_SIZE_F GetMaxScanSizeInLongLength();
 ESErrorCode SetMaxScanSizeInLongLength( ST_ES_SIZE_F maxScanSizeInLongLength );
 ST_ES_RECT_UN32 GetScanAreaInPixel();
 ESErrorCode SetScanAreaInPixel( ST_ES_RECT_UN32 rcScanAreaInPixel, bool bShouldAlign );
 ESErrorCode SetScanAreaInPixel( ST_ES_RECT_UN32 rcScanAreaInPixel );
 ST_ES_SIZE_F GetScanSize();
 ESErrorCode SetScanSize( ST_ES_SIZE_F sizeScan );
 ST_ES_SIZE_UN32 GetScanSizeInPixel();
 ESErrorCode SetScanSizeInPixel( ST_ES_SIZE_UN32 sizeScan );
 ESFloat GetXOffsetMargin();
 ESErrorCode SetXOffsetMargin( ESFloat fMargin );
 ESFloat GetYOffsetMargin();
 ESErrorCode SetYOffsetMargin( ESFloat fMargin );
 ESGuidePosition GetGuidePosition();
 ESGuidePosition GetGuidePositionFB();
 ESGuidePosition GetGuidePositionADF();
 ESErrorCode SetGuidePositionFB( ESNumber nGuidePosition );
 ESErrorCode SetGuidePositionADF( ESNumber nGuidePosition );
 ENUM_ESCI_BIT_DEPTH GetBitDepth();
 bool SetBitDepth( ENUM_ESCI_BIT_DEPTH eBitDepth );
 ENUM_ESCI_CLOLOR_MODE GetColorMode();
 bool SetColorMode( ENUM_ESCI_CLOLOR_MODE eColorMode );
 ESIndexSet GetSupportedColorFormats();
 ESNumber GetColorFormat();
 ESErrorCode SetColorFormat( ESNumber nColorFormat );
 ESNumber GetBitsPerSample();
 ESNumber GetSamplesPerPixel();
 ESNumber GetBitsPerPixel();
 ESAny GetColorMatrix();
 ESErrorCode SetColorMatrix( ESFloatArray arColorMatrix );
 ESIndexSet GetSupportedHalftones();
 ESHalftone GetHalftones();
 ESErrorCode SetHalftones( ESNumber nHalftone );
 ESIndexSet GetSupportedGammaModes();
 ESGammaMode GetGammaMode();
 ESErrorCode SetGammaMode( ESNumber nGammaMode );
 ESAny GetGammaTableMono ();
 ESAny GetGammaTableRed ();
 ESAny GetGammaTableGreen();
 ESAny GetGammaTableBlue ();
 ESErrorCode SetGammaTable ( const ESIndexArray& arGammaTable, ESGammaChannel eChannel );
 ESErrorCode SetGammaTableMono ( ESIndexArray arGammaTable );
 ESErrorCode SetGammaTableRed ( ESIndexArray arGammaTable );
 ESErrorCode SetGammaTableGreen( ESIndexArray arGammaTable );
 ESErrorCode SetGammaTableBlue ( ESIndexArray arGammaTable );
 ESErrorCode RequestSetGammaTables();
 ESAny GetSupportedThreshold();
 ESNumber GetThreshold();
 ESErrorCode SetThreshold( ESNumber nThreshold );
 ESErrorCode DoAutoFocus( ESFloat* pfOutFocus );
 ESFloat GetFocus();
 ESFloat GetMaxFocus();
 ESFloat GetMinFocus();
 ESErrorCode SetFocus( ESFloat fFocus );
 virtual ESErrorCode CreateScanningParametersParam( __out ST_ESCI_SCANNING_PARAMETER& stOutScanningParameter ) override;
 ESErrorCode SetScanningParameters();
 ESIndexSet GetSupportedDigitalICEs();
 ESDigitalICE GetDigitalICE();
 ESErrorCode SetDigitalICE( ESNumber nDigitalICE );
 bool IsQuietModeSupported();
 ESIndexSet GetSupportedQuietModes();
 ESQuietMode GetQuietMode();
 ESErrorCode SetQuietMode( ESNumber nQuietMode);
 ESScanningMode GetScanningMode();
 ESErrorCode SetScanningMode( ESNumber nScanningMode);
 bool IsDocumentSizeDetectionSupported();
 ST_ES_SIZE_F GetDetectedDocumentSize();
 bool IsFeederSupported();
 virtual bool IsFeederEnabled() override;
 bool IsAutoScanSupported();
 bool IsAutoScanEnabled();
 void SetAutoScanEnabled( bool bAutoScanEnabled );
 bool IsPageFeedTypeDocumentFeeder();
 ESDuplexType GetDuplexType();
 bool IsDuplexSupported();
 bool IsDuplexEnabled();
 ESErrorCode SetDuplexEnabled( bool bEnabled );
 bool IsDoubleFeedDetectionSupported();
 ESIndexSet GetSupportedDoubleFeedDetections();
 ESDoubleFeedDetection GetDoubleFeedDetection();
 ESErrorCode SetDoubleFeedDetection( ESNumber nDoubleFeedDetection );
 bool IsPaperEndDetectionSupported();
 virtual bool IsPaperEndDetectionEnabled() override;
 ESErrorCode SetPaperEndDetectionEnabled( bool bPperEndDetectionEnabled );
 bool IsOverScanEnabled();
 ESErrorCode SetOverScanEnabled( bool bOverScanEnabled );
 bool IsDocumentLoaded();
 ESNumber GetPagesToBeScanned();
 ESErrorCode SetPagesToBeScanned( ESNumber nPagesToBeScanned );
 bool IsPrefeed();
 bool IsTransparencyUnitSupported();
 bool IsTransparencyUnit2ndAreaSupported();
 bool IsInfraRedLampSupported();
 ESIndexSet GetSupportedFilmTypes();
 ESFilmType GetFilmType();
 ESErrorCode SetFilmType( ESNumber nFilmType );
 bool IsFlatbedSupported();
 bool IsLampChangeSupported();
 virtual ESIndexSet GetSupportedLampModes();
 ESLampMode GetLampMode();
 ESErrorCode SetLampMode( ESNumber nLampMode );
 bool IsCleaningSupported();
 bool IsCalibrationSupported();
 ESAny GetSupportedLightIntensitiesFB();
 ESNumber GetLightIntensityFB();
 ESErrorCode SetLightIntensityFB(ESNumber nLightIntensity);
protected:
 ESErrorCode DoCleaning();
 ESErrorCode DoCalibration();
 ESNumber GetLamp1Counter();
 ESErrorCode SetLamp1Counter(ESNumber nLamp1Counter);
 ESNumber GetLamp2Counter();
 ESErrorCode SetLamp2Counter(ESNumber nLamp2Counter);
 ESNumber GetSimplexScanCounter();
 ESErrorCode SetSimplexScanCounter(ESNumber nSimplexScanCounter);
 ESNumber GetDuplexScanCounter();
 ESErrorCode SetDuplexScanCounter(ESNumber nDuplexScanCounter);
 ESNumber GetPickupRollerCounter();
 ESErrorCode SetPickupRollerCounter(ESNumber nPickupRollerCounter);
 ESNumber GetScanCounter();
 ESErrorCode SetScanCounter(ESNumber nScanCounter);
private:
 bool m_bCaptureCommandSupport;
 bool m_bShouldIgnoreCancelFromScanner;
 bool m_bCaptured;
 ESNumber m_nBufferSize;
 ESJobMode m_eJobMode;
 bool m_bIsDisableJobContinue;
 ST_ESCI_IDENTITY m_stIdentity;
 ST_ESCI_EXTENDED_IDENTITY m_stExtIdentity;
 ST_ESCI_HW_PROPERTY m_stHwProperty;
 ST_ESCI_SCANNER_STATUS m_stScannerStatus;
 ST_ESCI_SCANNING_PARAMETER m_stParameters;
 ST_ES_SIZE_F m_sizeMaxScanSizeInLongLength;
 ESAny m_anySupportedResolutions;
 ESDigitalICE m_eDigitalICE;
 ESGuidePosition m_eGuidePositionFB;
 ESGuidePosition m_eGuidePositionADF;
 ESString m_strAuthUsername;
 ESString m_strAuthPassword;
 bool m_bIsAuthenticationEnabled;
 ESNumber m_nPagesToBeScanned;
 bool m_bPaperEndDetectionEnabled;
 bool m_bOverScanEnabled;
 std::recursive_mutex m_event_mtx;
 std::unique_ptr<event_caller> m_interruptCheckTimer;
 CESColorMatrix m_cColorMatrix;
 ESFloat m_fXOffsetMargin;
 ESFloat m_fYOffsetMargin;
 ESIndexArray m_arGammaTableMono;
 ESIndexArray m_arGammaTableRed;
 ESIndexArray m_arGammaTableGreen;
 ESIndexArray m_arGammaTableBlue;
 bool m_bIsShouldObserveButtonWithCommand;
};
