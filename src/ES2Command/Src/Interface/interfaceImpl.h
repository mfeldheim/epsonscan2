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
//  interfaceImpl.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "IInterface.h"
class IInterfaceImpl
{
public:
    virtual ~IInterfaceImpl(){}
    virtual void SetDelegate(IInterfaceDelegate *delegate) = 0;
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
