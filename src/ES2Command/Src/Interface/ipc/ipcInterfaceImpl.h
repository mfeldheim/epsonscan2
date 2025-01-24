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
//  ipcInterfaceImpl.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <memory>
#include <mutex>
#include <sys/types.h>
#include "CommonUtility/ESCommonTypedef.h"
#include "../interfaceImpl.h"
#include "../interface.h"
#include "ipc_header.hpp"
#include "ipc_interrupt.hpp"
namespace ipc {
typedef std::streamsize streamsize;
class IPCInterfaceImpl : public IInterfaceImpl
{
private:
 IPCInterfaceImpl();
public:
    explicit IPCInterfaceImpl(std::string name);
 virtual ~IPCInterfaceImpl();
 ESErrorCode Init(std::string udi, ESNumber nConnectionTimeout_s, ESNumber nTimeout_s);
    virtual void SetDelegate(IInterfaceDelegate *delegate);
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
    virtual ESErrorCode ReadExtendedTransfer(PESByte outBytes, UInt32 length);
    virtual ESErrorCode AbortExtendedTransferWithCode(UInt8 code);
    virtual bool IsAvoidsAckWhileImageTransfer();
    virtual int WaitTimeAfterFinalize();
    void recv_interrupt_event();
private:
    bool connect_();
    bool fork_();
    bool recv_reply(uint32_t* token = nullptr);
    bool open_(key_t sem_key);
    bool get_status_(uint32_t status_type, uint32_t& stat);
    bool get_status_();
    streamsize send_message_(ipc_header hdr, const char * payload);
    streamsize recv_message_(ipc_header& hdr, char *& payload);
    streamsize send_message_(const void *data, streamsize size);
    streamsize recv_message_( void *data, streamsize size);
    streamsize write (int fd, const void *buf, streamsize count);
    streamsize read (int fd, void *buf, streamsize count);
private:
 IInterfaceDelegate *delegate_;
    std::string name_;
    std::string udi_;
    int pid_;
    int port_;
    int socket_;
    uint32_t id_;
    double timeout_s_;
    static double default_timeout_;
    bool isInterruptSupported_;
    bool isExtendedTransferSupported_;
    std::recursive_mutex mtx_;
    std::unique_ptr<ipc_interrupt> interrupt_;
};
}
