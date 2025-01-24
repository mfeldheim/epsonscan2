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
//  IESScanner.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../es2CommnoType.h"
#include "../../CommonUtility/ESResultString.h"
#include "ESCommandProperties.h"
#include "ESPropertyKeys.h"
typedef ES_CHAR* ES_JSON_PTR;
typedef const ES_CHAR* ES_JSON_CPTR;
class IESScanner;
class IESScannedImage;
class IESScannerDelegate
{
public:
 virtual void CALLBACK ScannerWillBeginContinuousScanning(IESScanner* pScanner) = 0;
 virtual void CALLBACK ScannerDidEndContinuousScanning(IESScanner* pScanenr) = 0;
 virtual void CALLBACK ScannerWillScanToScannedImage( IESScanner* pScanner, IESScannedImage* pESImage ) = 0;
 virtual void CALLBACK ScannerDidScanToScannedImage( IESScanner* pScanner, IESScannedImage* pESImage ) = 0;
 virtual void CALLBACK ScannerWillCancelScanning( IESScanner* pScanner ) = 0;
 virtual void CALLBACK ScannerDidCancelScanning( IESScanner* pScanner) = 0;
 virtual void CALLBACK ScannerDidCompleteScanningWithError( IESScanner* pScanner, ESErrorCode err) = 0;
 virtual void CALLBACK ScannerDidInterruptScanningWithError(IESScanner* pcScanner ,ESErrorCode err) = 0;
 virtual void CALLBACK ScannerDidEncounterDeviceCommunicationError( IESScanner* pScanner, ESErrorCode err ) = 0;
 virtual void CALLBACK ScannerWillWarmUp( IESScanner* pScanner ) = 0;
 virtual void CALLBACK ScannerDidWarmUp( IESScanner* pScanner ) = 0;
 virtual void CALLBACK NetworkScannerDidRequestStartScanning( IESScanner* pScanner ) = 0;
 virtual void CALLBACK NetworkScannerDidRequestStopScanning( IESScanner* pScanner ) = 0;
 virtual void CALLBACK ScannerDidDisconnect( IESScanner* pScanner ) = 0;
 virtual void CALLBACK NetworkScannerDidReceiveServerError( IESScanner* pScanner ) = 0;
 virtual BOOL CALLBACK NetworkScannerShouldPreventTimeout( IESScanner* pScanner ) = 0;
 virtual void CALLBACK NetworkScannerDidTimeout( IESScanner* pScanner ) = 0;
 virtual void CALLBACK ScannerIsReservedByHost( IESScanner* pScanner, const ES_CHAR* pszAddress ) = 0;
 virtual void CALLBACK ScannerDidPressButton( UInt8 un8ButtonNumber ) = 0;
 virtual void CALLBACK ScannerDidRequestStop(IESScanner *pScanner) = 0;
 virtual void CALLBACK ScannerDidRequestPushScanConnection(IESScanner *pScanner) = 0;
 virtual void CALLBACK ScannerDidNotifyStatusChange(IESScanner *pScanner) = 0;
};
class IESScanner
{
public:
 virtual void SetDelegate( IESScannerDelegate* pDelegate ) = 0;
 virtual ESErrorCode SetConnection( ES_JSON_CPTR pszJSON ) = 0;
 virtual void DestroyInstance() = 0;
 virtual ESErrorCode Open() = 0;
 virtual ESErrorCode Close() = 0;
 virtual bool IsOpened() const = 0;
 virtual ESErrorCode Scan() = 0;
 virtual ESErrorCode ScanInBackground() = 0;
 virtual ESErrorCode Cancel() = 0;
 virtual ESErrorCode Abort() = 0;
 virtual bool IsScanning() const = 0;
 virtual ESErrorCode DoCleaning() = 0;
 virtual ESErrorCode DoCalibration() = 0;
 virtual bool IsInterrupted() const = 0;
 virtual bool IsAfmEnabled() const = 0;
 virtual ESErrorCode ScheduleAutoFeedingModeTimeout() = 0;
 virtual ESErrorCode StartJobInMode( ESJobMode eJobMode ) = 0;
 virtual ESErrorCode StopJobInMode( ESJobMode eJobMode ) = 0;
 virtual ESErrorCode DoAutoFocus( ESFloat* pfOutFocus ) = 0;
 virtual ESErrorCode SetPanelToPushScanReady( BOOL bPushScanReady ) = 0;
 virtual BOOL IsScannableDeviceConfig() = 0;
 virtual ESErrorCode UnlockAdministratorLock() = 0;
 virtual ESErrorCode LockAdministratorLock() = 0;
 virtual ESErrorCode Reset() = 0;
 virtual ESErrorCode GetAllKeys( IESResultString* pstrResult ) = 0;
 virtual ESErrorCode GetDefaultValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) = 0;
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) = 0;
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ES_JSON_CPTR pszJSON ) = 0;
 virtual ESErrorCode SetValuesWithJSON( ES_JSON_CPTR pszJSON ) = 0;
 virtual ESErrorCode GetAllValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) = 0;
 virtual ESErrorCode GetAllValues( IESResultString* pstrResult ) = 0;
 virtual ESErrorCode GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult ) = 0;
 virtual ESErrorCode GetAllAvailableValues( IESResultString* pstrResult ) = 0;
};
STATIC_CONST_KEY ES_JSON_KEY_ALLKEYS = ES_STRING("AllKeys");
