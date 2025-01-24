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
//  TransferEvent.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <Image.hpp>
#include <Utility.hpp>
#include "EpsonScan2.h"
namespace epsonscan {
enum EventType
{
   kEventTypePaperJam,
   kEventTypeImage,
   kEventTypeComplete,
   kEventTypeCancel,
   kEventTypeAFMStartConituousScan,
   kEventTypeAFMStopContinuousScan
};
class TransferEvent
{
public:
    TransferEvent(EventType type, Image* image, SDIError error) : type_(type), image_(image), error_(error)
    {
        SDI_TRACE_LOG("Enter");
        if (image_)
        {
            image_->AddReference();
        }
        SDI_TRACE_LOG("Leave");
    }
    TransferEvent(EventType type, SDIError error) : type_(type), image_(nullptr), error_(error)
    {
         SDI_TRACE_LOG("Enter");
         SDI_TRACE_LOG("Leave");
    }
    TransferEvent(const TransferEvent& transferEvent)
    {
        image_ = transferEvent.GetImage();
        if(image_){
            image_->AddReference();
        }
        type_ = transferEvent.GetType();
        error_ = transferEvent.GetError();
    }
    virtual ~TransferEvent()
    {
        SDI_TRACE_LOG("Destroy TransferEvent");
        Release();
    }
    void Release()
    {
        if (image_)
        {
            image_->Release();
        }
    }
 Image* GetImage() const
 {
  return image_;
 }
    EventType GetType() const
    {
        return type_;
    }
    void SetError(SDIError error)
    {
        error_ = error;
    }
    SDIError GetError() const
    {
        return error_;
    }
private:
    Image* image_;
    EventType type_;
    SDIError error_;
};
}
