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
//  CommandBase.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/utils/CritSec.h"
#include "Interface/IInterface.h"
class IESScanner;
class IESScannedImage;
class IESScannerDelegate;
class CCommandBase : public IInterfaceDelegate
{
public:
 CCommandBase();
 virtual ~CCommandBase();
 void SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner );
 IESScannerDelegate* GetDelegate();
 virtual ESErrorCode CallDelegateScannerWillBeginContinuousScanning();
 virtual ESErrorCode CallDelegateScannerDidEndContinuousScanning();
 virtual ESErrorCode CallDelegateScannerWillScanToScannedImage( IESScannedImage* pESImage );
 virtual ESErrorCode CallDelegateScannerDidScanToScannedImage( IESScannedImage* pESImage );
 virtual ESErrorCode CallDelegateScannerWillCancelScanning();
 virtual ESErrorCode CallDelegateScannerDidCancelScanning();
 virtual ESErrorCode CallDelegateScannerDidCompleteScanningWithError( ESErrorCode err);
 virtual ESErrorCode CallDelegateScannerDidInterruptScanningWithError( ESErrorCode err);
 virtual ESErrorCode CallDelegateScannerDidEncounterDeviceCommunicationError( ESErrorCode err );
 virtual ESErrorCode CallDelegateScannerWillWarmUp();
 virtual ESErrorCode CallDelegateScannerDidWarmUp();
 virtual ESErrorCode CallDelegateNetworkScannerDidRequestStartScanning();
 virtual ESErrorCode CallDelegateNetworkScannerDidRequestStopScanning();
 virtual ESErrorCode CallDelegateScannerDidDisconnect();
 virtual ESErrorCode CallDelegateNetworkScannerDidReceiveServerError();
 virtual BOOL CallDelegateNetworkScannerShouldPreventTimeout();
 virtual ESErrorCode CallDelegateNetworkScannerScannerDidTimeout();
 virtual ESErrorCode CallDelegateScannerIsReservedByHost( const ES_CHAR* pszAddress );
 virtual ESErrorCode CallDelegateScannerDidPressButton( UInt8 un8ButtonNumber );
 virtual ESErrorCode CallDelegateScannerDidRequestStop();
 virtual ESErrorCode CallDelegateScannerDidRequestPushScanConnection();
 virtual ESErrorCode CallDelegateScannerDidNotifyStatusChange();
 virtual void CALLBACK DidPressButton( UInt8 un8ButtonNumber ) override;
 virtual void CALLBACK DidRequestStartScanning() override;
 virtual void CALLBACK DidRequestStopScanning() override;
 virtual void CALLBACK DidRequestStartOrStop() override;
 virtual void CALLBACK DidRequestStop() override;
 virtual void CALLBACK DidReceiveServerError() override;
 virtual void CALLBACK DidDisconnect() override;
 virtual void CALLBACK DidRequestPushScanConnection() override;
 virtual BOOL CALLBACK ShouldPreventTimeout() override;
 virtual void CALLBACK DidTimeout() override;
 virtual void CALLBACK IsReservedByHost(IInterface* pDeviceInterface, const ES_CHAR* pszAddress ) override;
 virtual BOOL CALLBACK ShouldStopScanning( IInterface* pDeviceInterface ) override;
 virtual void CALLBACK DidRequestGetImageData() override;
 virtual void CALLBACK DidNotifyStatusChange() override;
 virtual void CALLBACK DeviceCommunicationError( ESErrorCode err ) override;
 ESErrorCode SetDeviceInterface(IInterface* pDeviceInterface );
 virtual ESErrorCode OpenDevice();
 virtual ESErrorCode CloseDevice();
 IInterface* GetDeviceInterface();
 virtual void DeviceDisconnected();
 bool IsDeviceOpened() const;
 bool IsScanning() const;
 bool IsCancelled();
 bool IsInterrupted() const;
protected:
 void SetScanning( bool bScanning );
 void SetCancelled( bool bCanncelled );
 void SetInterrupted( bool bInterrupted );
protected:
 typedef enum {
  EOT = 0x04,
  ESC = 0x1B,
  FS = 0x1C,
  CAN = 0x18,
  FORM_FEED = 0x0C,
  PAPER_FEED = 0x19,
 } ENUM_CONTROL_CODE;
 typedef enum {
  ACK = 0x06,
  NACK = 0x15,
  BUSY = 0x07,
 } ENUM_ACK_CODE;
#if 0
 ESErrorCode Write ( __in PESByte pBuf, __in UInt32 un32BufferLen );
#endif
 ESErrorCode Write ( __in PESByte pBuf, __in UInt32 un32BufferLen, __in UInt32 un32ComittedReadLength );
 ESErrorCode Read ( __out PESByte pBuf, __in UInt32 un32BufferLen );
 ESErrorCode SendAck();
 ESErrorCode ReceiveAck( __out ESByte& outAck );
 ESString GetWorkFolder();
 ESErrorCode SetWorkFolder( ESString strWorkFolder );
 CritSec& GetCriticalSection() const { return m_cCriticalSection; }
 enum {
  MAX_USERNAME_LENGTH = 20,
  HASH_DATA_SIZE = 20,
  HASH_DATA_SIZE_32 = 32,
  HASH_SOLT_LENGTH = 16
 };
 ESErrorCode CreateSha1HashedPasswordData( __in const ESStringA strAuthUserNameA, __in const ESStringA strPasswordDataA, __out ESByteData& bdPasswordData );
 ESErrorCode CreateSha1HashedData(__in const ESStringA strDataA, __out ESByteData& bdSha1HashData);
 ESErrorCode CreateSha256HashedData(__in const ESStringA strPasswordDataA, __out ESByteData& bdPasswordData);
protected:
 mutable CritSec m_cCriticalSection;
 mutable CritSec m_cDelegateCriticalSection;
 IInterface *m_pDevInterface;
 IESScannerDelegate* m_pDelegate;
 IESScanner* m_pScanner;
 bool m_bCancelled;
 bool m_bScanning;
 bool m_bIsInterrupted;
 ESString m_strWorkFolder;
};
#define SYNCHRONIZED_START { CBlockCriticalSection cBlockCriticalSection( GetCriticalSection() );
#define SYNCHRONIZED_END }
