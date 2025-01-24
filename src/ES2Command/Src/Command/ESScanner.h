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
//  ESScanner.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <pthread.h>
#include "Include/ES2Command/ES2CommandAPI.h"
#include "Interface/IInterface.h"
#include "Utils/ESAccessor.h"
class IESScannerDelegate;
class CESScanner : public IESScanner
{
public:
 static CESScanner* CreateInstance(ESCommandType eCommandType);
public:
 CESScanner();
 virtual ~CESScanner();
 virtual void DestroyInstance() override;
 virtual ESErrorCode Initialize();
 virtual void SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner ) = 0;
 virtual IESScannerDelegate* GetDelegate() = 0;
 virtual ESErrorCode SetDeviceInterface(IInterface* pDeviceInterface ) = 0;
 virtual IInterface* GetDeviceInterface() = 0;
 virtual ESErrorCode SetConnection( ES_JSON_CPTR pszJSON ) override;
 virtual ESErrorCode ScanInBackground() override;
 virtual void SetScanning( bool bScanning ) = 0;
 virtual void SetCancelled( bool bCanncelled ) = 0;
 virtual ESErrorCode DoAutoFocus( ESFloat* pfOutFocus ) override;
 virtual BOOL IsScannableDeviceConfig() override;
 virtual ESErrorCode GetAllKeys( IESResultString* pstrResult ) override;
 virtual ESErrorCode GetDefaultValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) override;
 virtual ESErrorCode GetAllValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) override;
 virtual ESErrorCode GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) override;
 virtual ESErrorCode GetAllValues( IESResultString* pstrResult ) override;
 virtual ESErrorCode GetAllAvailableValues( IESResultString* pstrResult ) override;
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) override;
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ES_JSON_CPTR pszJSON ) override;
 virtual ESErrorCode SetValuesWithJSON( ES_JSON_CPTR pszJSON ) override;
protected:
 virtual const ESStringArray& GetAllKeys();
 virtual ESErrorCode GetCapabilityForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult );
 ESErrorCode GetTargetCapabilityForKey( ES_CHAR_CPTR pszKey, ES_CHAR_CPTR pszTarget, ESDictionary& dicResult );
 virtual ESErrorCode GetDefaultValueForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult );
 virtual ESErrorCode GetAllValuesForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult );
 virtual ESErrorCode GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult );
 virtual ESDictionary GetAllValuesDictionary();
 virtual ESDictionary GetAvailableDictionary();
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue );
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue );
 virtual ESStringArray GetPriorKeys();
 virtual ESErrorCode SetValuesForKeysWithDictionary( ESDictionary& dicKeysValues );
 virtual ESErrorCode GetValueForUndefinedKey( ES_CHAR_CPTR pszKey, ESAny& anyValue );
 virtual ESErrorCode SetValueForUndefinedKey( ES_CHAR_CPTR pszKey, ESAny anyValue );
 ESErrorCode GetTargetCapabilityForKey( ES_CHAR_CPTR pszKey, ES_CHAR_CPTR pszTarget, IESResultString* pstrResult );
protected:
 virtual void GetVersionCapability ( ESDictionary& dicResult ) = 0;
 virtual void GetWorkFolderCapability ( ESDictionary& dicResult );
 virtual void GetErrorStatusCapability ( ESDictionary& dicResult );
 virtual void GetAuthenticationCapability ( ESDictionary& dicResult );
 virtual void GetAuthenticationEnabledCapability ( ESDictionary& dicResult );
 virtual void GetAuthUserNameCapability ( ESDictionary& dicResult );
 virtual void GetAuthPasswordCapability ( ESDictionary& dicResult );
 virtual void GetProductNameCapability ( ESDictionary& dicResult );
 virtual void GetFunctionalUnitTypeCapability ( ESDictionary& dicResult );
 virtual void GetXResolutionCapability ( ESDictionary& dicResult );
 virtual void GetYResolutionCapability ( ESDictionary& dicResult );
 virtual void GetOpticalResolutionCapability ( ESDictionary& dicResult );
 virtual void GetMaxScanSizeCapability ( ESDictionary& dicResult );
 virtual void GetScanAreaCapability ( ESDictionary& dicResult );
 virtual void GetScanAreaInPixelCapability ( ESDictionary& dicResult );
 virtual void GetScanSizeCapability ( ESDictionary& dicResult );
 virtual void GetScanSizeInPixelCapability ( ESDictionary& dicResult );
 virtual void GetXOffsetMarginCapability ( ESDictionary& dicResult );
 virtual void GetYOffsetMarginCapability ( ESDictionary& dicResult );
 virtual void GetColorFormatCapability ( ESDictionary& dicResult );
 virtual void GetColorMatrixCapability ( ESDictionary& dicResult ) = 0;
 virtual void GetBitsPerPixelCapability ( ESDictionary& dicResult );
 virtual void GetGammaModeCapability ( ESDictionary& dicResult );
 virtual void GetGammaTableCapability ( ESDictionary& dicResult );
 virtual void GetThresholdCapability ( ESDictionary& dicResult );
 virtual void GetQuietModeCapability ( ESDictionary& dicResult );
 virtual void GetBufferSizeCapability ( ESDictionary& dicResult );
 virtual void GetDuplexTypeCapability ( ESDictionary& dicResult );
 virtual void GetDuplexCapability ( ESDictionary& dicResult );
 virtual void GetDoubleFeedDetectionCapability ( ESDictionary& dicResult );
 virtual void GetPagesToBeScannedCapability ( ESDictionary& dicResult );
 virtual void GetDocumentLoadedCapability ( ESDictionary& dicResult );
 virtual void GetCleaningCapability ( ESDictionary& dicResult );
 virtual void GetCalibrationCapability ( ESDictionary& dicResult );
 virtual ESString GetWorkFolder() = 0;
 virtual ESErrorCode SetWorkFolder( ESString strWorkFolder ) = 0;
 virtual ESErrorCode GetErrorStatus() = 0;
 virtual ESNumber GetBufferSize() = 0;
 virtual ESErrorCode SetBufferSize( ESNumber nBufferSize ) = 0;
 virtual bool IsAuthenticationSupported() = 0;
 virtual bool IsAuthenticationEnabled() = 0;
 virtual ESErrorCode SetAuthenticationEnabled( bool bEnabled ) = 0;
 virtual ESString GetAuthUserName() = 0;
 virtual ESErrorCode SetAuthUserName( ESString strAuthUserName ) = 0;
 virtual ESString GetAuthPassword() = 0;
 virtual ESErrorCode SetAuthPassword( ESString strAuthPasswordData ) = 0;
 virtual ESString GetProductName() = 0;
 virtual ESIndexSet GetSupportedFunctionalUnitTypes() = 0;
 virtual ESFunctionalUnitType GetFunctionalUnitType() = 0;
 virtual ESErrorCode SetFunctionalUnitType( ESNumber nFunctionalUnitType ) = 0;
 virtual ESAny GetSupportedXResolutions() = 0;
 virtual ESAny GetSupportedYResolutions() = 0;
 virtual ESNumber GetXResolution() = 0;
 virtual ESNumber GetYResolution() = 0;
 virtual ESErrorCode SetXResolution( ESNumber xResolution ) = 0;
 virtual ESErrorCode SetYResolution( ESNumber yResolution ) = 0;
 virtual ESNumber GetOpticalResolution() = 0;
 virtual ST_ES_SIZE_F GetMaxScanSize() = 0;
 virtual ST_ES_RECT_F GetScanArea() = 0;
 virtual ESErrorCode SetScanArea( ST_ES_RECT_F rcScanArea ) = 0;
 virtual ST_ES_RECT_UN32 GetScanAreaInPixel() = 0;
 virtual ESErrorCode SetScanAreaInPixel( ST_ES_RECT_UN32 rcScanAreaInPixel ) = 0;
 virtual ST_ES_SIZE_F GetScanSize() = 0;
 virtual ESErrorCode SetScanSize( ST_ES_SIZE_F sizeScan ) = 0;
 virtual ST_ES_SIZE_UN32 GetScanSizeInPixel() = 0;
 virtual ESErrorCode SetScanSizeInPixel( ST_ES_SIZE_UN32 sizeScan ) = 0;
 virtual ESFloat GetXOffsetMargin() = 0;
 virtual ESErrorCode SetXOffsetMargin( ESFloat fMargin ) = 0;
 virtual ESFloat GetYOffsetMargin() = 0;
 virtual ESErrorCode SetYOffsetMargin( ESFloat fMargin ) = 0;
 virtual ESIndexSet GetSupportedColorFormats() = 0;
 virtual ESNumber GetColorFormat() = 0;
 virtual ESErrorCode SetColorFormat( ESNumber nColorFormat ) = 0;
 virtual ESNumber GetBitsPerSample() = 0;
 virtual ESNumber GetSamplesPerPixel() = 0;
 virtual ESNumber GetBitsPerPixel() = 0;
 virtual ESAny GetColorMatrix() = 0;
 virtual ESErrorCode SetColorMatrix( ESFloatArray arColorMatrix ) = 0;
 virtual ESIndexSet GetSupportedGammaModes() = 0;
 virtual ESGammaMode GetGammaMode() = 0;
 virtual ESErrorCode SetGammaMode( ESNumber nGammaMode ) = 0;
 virtual ESAny GetGammaTableMono () = 0;
 virtual ESAny GetGammaTableRed () = 0;
 virtual ESAny GetGammaTableGreen() = 0;
 virtual ESAny GetGammaTableBlue () = 0;
 virtual ESErrorCode SetGammaTableMono ( ESIndexArray arGammaTable ) = 0;
 virtual ESErrorCode SetGammaTableRed ( ESIndexArray arGammaTable ) = 0;
 virtual ESErrorCode SetGammaTableGreen( ESIndexArray arGammaTable ) = 0;
 virtual ESErrorCode SetGammaTableBlue ( ESIndexArray arGammaTable ) = 0;
 virtual ESAny GetSupportedThreshold() = 0;
 virtual ESNumber GetThreshold() = 0;
 virtual ESErrorCode SetThreshold( ESNumber nThreshold ) = 0;
 virtual ESIndexSet GetSupportedQuietModes() = 0;
 virtual ESQuietMode GetQuietMode() = 0;
 virtual ESErrorCode SetQuietMode( ESNumber nQuiteMode ) = 0;
 virtual bool IsFeederSupported() = 0;
 virtual bool IsFeederEnabled() = 0;
 virtual ESDuplexType GetDuplexType() = 0;
 virtual bool IsDuplexSupported() = 0;
 virtual bool IsDuplexEnabled() = 0;
 virtual ESErrorCode SetDuplexEnabled( bool bEnabled ) = 0;
 virtual ESIndexSet GetSupportedDoubleFeedDetections() = 0;
 virtual ESDoubleFeedDetection GetDoubleFeedDetection() = 0;
 virtual ESErrorCode SetDoubleFeedDetection( ESNumber nDoubleFeedDetection ) = 0;
 virtual bool IsDocumentLoaded() = 0;
 virtual ESNumber GetPagesToBeScanned() = 0;
 virtual ESErrorCode SetPagesToBeScanned( ESNumber nPagesToBeScanned ) = 0;
 virtual bool IsCleaningSupported() = 0;
 virtual bool IsCalibrationSupported() = 0;
 virtual bool IsCaptureCommandSupported() = 0;
 virtual ESErrorCode SetCaptureCommandSupported( bool bSupported ) = 0;
 static void* EnterScannerThread(void* vpContext);
private:
 ACCESSOR_MAP m_mapAccessor;
 ESStringArray m_arAllKeys;
 typedef std::function<void(CESScanner*, ESDictionary&) > FN_CAPA;
 typedef std::map< ESString, FN_CAPA > CAPA_MAP;
 typedef CAPA_MAP::value_type CAPA_PAIR;
 CAPA_MAP m_funcCapability;
};
