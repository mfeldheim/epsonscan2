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
//  usbInterfaceImpl.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <libusb-1.0/libusb.h>
#include "../interfaceImpl.h"
#include "../interface.h"
#include "CommonUtility/ESCommonTypedef.h"
class USBInterfaceImpl : public IInterfaceImpl
{
public:
 USBInterfaceImpl();
 virtual ~USBInterfaceImpl();
    virtual void SetDelegate(IInterfaceDelegate *delegate);
 ESErrorCode Init(UInt16 vid, UInt16 pid);
 ESErrorCode Init(UInt16 vid, UInt16 pid, ESString serialNumber);
 virtual ESErrorCode Open();
 virtual bool IsOpened();
 virtual void Close();
    virtual ESErrorCode Read(PESByte outBytes, UInt32 length);
    virtual ESErrorCode Write(PESByte inBytes, UInt32 length);
    virtual ESErrorCode Write(PESByte inBytes, UInt32 length, UInt32 committedReadLength);
    virtual bool IsInterruptSupported();
    virtual void ReceiveInterruptEvent();
    virtual bool IsSupportsExtendedTransfer();
    virtual ESErrorCode StartExtendedTransferWithBlocks(UInt32 blocks, UInt32 bytesPerBlock, UInt32 bytesOfLastBlock);
    virtual ESErrorCode ReadExtendedTransfer(PESByte theBytes, UInt32 length);
    virtual ESErrorCode AbortExtendedTransferWithCode(UInt8 code);
    virtual bool IsAvoidsAckWhileImageTransfer();
    virtual int WaitTimeAfterFinalize();
private:
    bool IsMatchID(UInt16 vid, UInt16 pid, libusb_device* dev);
 bool IsMatchID(UInt16 vid, UInt16 pid, ESString serialNumber , libusb_device *dev);
 ESErrorCode SetupInterface();
private:
 IInterfaceDelegate *m_delegate;
 libusb_device_handle *m_handle;
 uint16_t m_vid;
 uint16_t m_pid;
 ESString m_serialNumber;
 int m_cfg;
 int m_if;
 bool m_bKernelDriverDetached;
 int m_bulk_in;
 int m_bulk_out;
    int m_interrupt;
 static bool sm_isInitialized;
 static int sm_nDefaultTimeout;
 static int sm_nConnectionCount;
 static libusb_context *sm_ctx;
};
