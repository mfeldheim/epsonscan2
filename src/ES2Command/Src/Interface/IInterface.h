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
//  IInterface.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "Platform.h"
#include "Include/ES2Command/ESCommandProperties.h"
class IInterface;
class IInterfaceDelegate
{
public:
    virtual ~IInterfaceDelegate(){}
 virtual void CALLBACK DidPressButton(UInt8 buttonNumber) = 0;
 virtual void CALLBACK DidRequestStartScanning() = 0;
 virtual void CALLBACK DidRequestStopScanning() = 0;
 virtual void CALLBACK DidRequestStartOrStop() = 0;
 virtual void CALLBACK DidRequestStop() = 0;
 virtual void CALLBACK DidReceiveServerError() = 0;
 virtual void CALLBACK DidDisconnect() = 0;
 virtual void CALLBACK DidRequestPushScanConnection() = 0;
 virtual BOOL CALLBACK ShouldPreventTimeout() = 0;
 virtual void CALLBACK DidTimeout() = 0;
 virtual void CALLBACK IsReservedByHost(IInterface *interface, const ES_CHAR *address) = 0;
 virtual BOOL CALLBACK ShouldStopScanning(IInterface* interface) = 0;
 virtual void CALLBACK DidRequestGetImageData() = 0;
 virtual void CALLBACK DidNotifyStatusChange() = 0;
 virtual void CALLBACK DeviceCommunicationError(ESErrorCode err) = 0;
};
class IInterface
{
public:
 virtual ~IInterface() {}
 virtual void DestroyInstance() = 0;
    virtual ESConnectionType ConnectionType() const = 0;
 virtual void SetDelegate(IInterfaceDelegate* delegate) = 0;
 virtual ESErrorCode Open() = 0;
 virtual bool IsOpened() = 0;
 virtual void Close() = 0;
 virtual ESErrorCode Read(PESByte outBytes, UInt32 length) = 0;
 virtual ESErrorCode Write(PESByte inBytes, UInt32 length) = 0;
 virtual ESErrorCode Write(PESByte inBytes, UInt32 length, UInt32 committedReadLength) = 0;
 virtual bool IsInterruptSupported() = 0;
 virtual void ReceiveInterruptEvent() = 0;
 virtual bool IsSupportsExtendedTransfer() = 0;
 virtual ESErrorCode StartExtendedTransferWithBlocks(UInt32 blocks, UInt32 bytesPerBlock, UInt32 bytesOfLastBlock) = 0;
 virtual ESErrorCode ReadExtendedTransfer(PESByte theBytes, UInt32 length) = 0;
 virtual ESErrorCode AbortExtendedTransferWithCode(UInt8 code) = 0;
 virtual bool IsAvoidsAckWhileImageTransfer() = 0;
 virtual int WaitTimeAfterFinalize() = 0;
};
ESErrorCode CreateInterface(const ES_CHAR *pszJSON, IInterface** ppInterface);
