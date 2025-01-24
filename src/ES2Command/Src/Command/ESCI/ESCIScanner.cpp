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
//  ESCIScanner.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCIScanner.h"
CESCIScanner::CESCIScanner()
{
 PROPERTY_R ( kESVersion, CESCIScanner, ESString, GetVersion );
 PROPERTY_R ( kESProductName, CESCIScanner, ESString, GetProductName );
 PROPERTY_RW( kESDisableJobContinue, CESCIScanner, bool, IsDisableJobContinue, bool, SetDisableJobContinue );
 PROPERTY_R ( kESWarmingUp, CESCIScanner, bool, IsWarmingUp );
 PROPERTY_R ( kESButtonStatus, CESCIScanner, ESNumber, GetButtonStatus );
 PROPERTY_RW( kESLampMode, CESCIScanner, ESNumber, GetLampMode, ESNumber, SetLampMode );
 PROPERTY_RW( kESPowerOffTime, CESCIScanner, ESNumber, GetPowerOffTime, ESNumber, SetPowerOffTime );
 PROPERTY_RW( kESHalftone, CESCIScanner, ESNumber, GetHalftones, ESNumber, SetHalftones );
 PROPERTY_R ( kESMaxFocus, CESCIScanner, ESFloat, GetMaxFocus );
 PROPERTY_R ( kESMinFocus, CESCIScanner, ESFloat, GetMinFocus );
 PROPERTY_RW( kESFocus, CESCIScanner, ESFloat, GetFocus, ESFloat, SetFocus );
 PROPERTY_RW( kESDigitalICE, CESCIScanner, ESNumber, GetDigitalICE, ESNumber, SetDigitalICE );
 PROPERTY_RW( kESFilmType, CESCIScanner, ESNumber, GetFilmType, ESNumber, SetFilmType );
 PROPERTY_R ( kESDetectedDocumentSize, CESCIScanner, ST_ES_SIZE_F, GetDetectedDocumentSize );
 PROPERTY_RW( kESSimplexScanCounter, CESCIScanner, ESNumber, GetSimplexScanCounter, ESNumber, SetSimplexScanCounter );
 PROPERTY_RW( kESDuplexScanCounter, CESCIScanner, ESNumber, GetDuplexScanCounter, ESNumber, SetDuplexScanCounter );
 PROPERTY_RW( kESLamp1Counter, CESCIScanner, ESNumber, GetLamp1Counter, ESNumber, SetLamp1Counter );
 PROPERTY_RW( kESLamp2Counter, CESCIScanner, ESNumber, GetLamp2Counter, ESNumber, SetLamp2Counter );
 PROPERTY_RW( kESPickupRollerCounter, CESCIScanner, ESNumber, GetPickupRollerCounter, ESNumber, SetPickupRollerCounter );
 PROPERTY_RW( kESScanCounter, CESCIScanner, ESNumber, GetScanCounter, ESNumber, SetScanCounter );
 PROPERTY_RW( kESPaperEndDetection, CESCIScanner, bool, IsPaperEndDetectionEnabled, bool, SetPaperEndDetectionEnabled );
 PROPERTY_RW( kESCaptureCommandSupported, CESCIScanner, bool, IsCaptureCommandSupported, bool, SetCaptureCommandSupported );
 PROPERTY_RW( kESShouldIgnoreCancelFromScanner, CESCIScanner, bool, IsShouldIgnoreCancelFromScanner, bool, SetShouldIgnoreCancelFromScanner );
 PROPERTY_R ( kESGuidePosition, CESCIScanner, ESNumber, GetGuidePosition );
 PROPERTY_RW( kESGuidePositionFB, CESCIScanner, ESNumber, GetGuidePositionFB, ESNumber, SetGuidePositionFB );
 PROPERTY_RW( kESGuidePositionADF, CESCIScanner, ESNumber, GetGuidePositionADF, ESNumber, SetGuidePositionADF );
 PROPERTY_RW( kESMaxScanSizeInLongLength, CESCIScanner, ST_ES_SIZE_F, GetMaxScanSizeInLongLength, ST_ES_SIZE_F, SetMaxScanSizeInLongLength );
 PROPERTY_RW( kESOverScan, CESCIScanner, bool, IsOverScanEnabled, bool, SetOverScanEnabled );
 PROPERTY_RW( kESScanningMode, CESCIScanner, ESNumber, GetScanningMode, ESNumber, SetScanningMode );
 PROPERTY_RW( kESLightIntensityFB, CESCIScanner, ESNumber, GetLightIntensityFB, ESNumber, SetLightIntensityFB );
 this->GetAllKeys();
}
CESCIScanner::~CESCIScanner()
{
}
ESErrorCode CESCIScanner::Initialize()
{
 return CESCIAccessor::Initialize();
}
ESErrorCode CESCIScanner::SetDeviceInterface(IInterface* pDeviceInterface )
{
 return CESCIAccessor::SetDeviceInterface( pDeviceInterface );
}
IInterface* CESCIScanner::GetDeviceInterface()
{
 return CESCIAccessor::GetDeviceInterface();
}
void CESCIScanner::SetDelegate( IESScannerDelegate* pDelegate )
{
 CESCIAccessor::SetDelegate( pDelegate, this );
}
void CESCIScanner::SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner )
{
 CESCIAccessor::SetDelegate( pDelegate, pScanner );
}
IESScannerDelegate* CESCIScanner::GetDelegate()
{
 return CESCIAccessor::GetDelegate();
}
ESErrorCode CESCIScanner::Open()
{
 return CESCIAccessor::Open();
}
ESErrorCode CESCIScanner::Close()
{
 return CESCIAccessor::Close();
}
bool CESCIScanner::IsOpened() const
{
 return CESCIAccessor::IsOpened();
}
ESErrorCode CESCIScanner::Scan()
{
 return CESCIAccessor::Scan();
}
ESErrorCode CESCIScanner::Cancel()
{
 return CESCIAccessor::Cancel();
}
ESErrorCode CESCIScanner::Abort()
{
 return kESErrorNoError;
}
bool CESCIScanner::IsScanning() const
{
 return CESCIAccessor::IsScanning();
}
void CESCIScanner::SetScanning( bool bScanning )
{
 CESCIAccessor::SetScanning( bScanning );
}
void CESCIScanner::SetCancelled( bool bCanncelled )
{
 CESCIAccessor::SetCancelled( bCanncelled );
}
ESErrorCode CESCIScanner::DoCleaning()
{
 return CESCIAccessor::DoCleaning();
}
ESErrorCode CESCIScanner::DoCalibration()
{
 return CESCIAccessor::DoCalibration();
}
ESErrorCode CESCIScanner::Reset()
{
 return CESCIAccessor::Reset();
}
bool CESCIScanner::IsInterrupted() const
{
 return CESCIAccessor::IsInterrupted();
}
bool CESCIScanner::IsAfmEnabled() const
{
 return false;
}
ESErrorCode CESCIScanner::ScheduleAutoFeedingModeTimeout()
{
 return kESErrorNoError;
}
ESErrorCode CESCIScanner::StartJobInMode( ESJobMode eJobMode )
{
 return CESCIAccessor::StartJobInMode( eJobMode );
}
ESErrorCode CESCIScanner::StopJobInMode( ESJobMode eJobMode )
{
 return CESCIAccessor::StopJobInMode( eJobMode );
}
ESErrorCode CESCIScanner::DoAutoFocus( ESFloat* pfOutFocus )
{
 return CESCIAccessor::DoAutoFocus( pfOutFocus );
}
ESErrorCode CESCIScanner::SetPanelToPushScanReady( BOOL bPushScanReady )
{
 return kESErrorNoError;
}
ESErrorCode CESCIScanner::UnlockAdministratorLock()
{
 return kESErrorNoError;
}
ESErrorCode CESCIScanner::LockAdministratorLock()
{
 return kESErrorNoError;
}
