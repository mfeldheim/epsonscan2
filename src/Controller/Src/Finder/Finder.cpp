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
//  Finder.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Finder.hpp"
#include "NetFinder.hpp"
#include "UsbFinder.hpp"
#include "Utility.hpp"
#include <functional>
#include <memory>
#include <iostream>
namespace epsonscan {
  Finder::Finder() :
  usbFinder_(std::make_shared<UsbFinder>()), netFinder_(std::make_shared<NetFinder>())
  {
  }
  void Finder::Start(bool searchSecondDevice )
  {
   usbFinder_.get()->Start(devices_, searchSecondDevice);
   if (searchSecondDevice == false)
   {
    netFinder_.get()->Reset();
    notifyThread_ = std::make_shared<std::thread>([this]() {
    NetFinderCallBack finderCallBack = [this](SDIDeviceInfo& device) {
     SDI_TRACE_LOG("network device found ip = %s modelID = %s displayname = %s", device.ipAddress, device.modelID, device.displayName);
     devices_.push_back(device);
    };
     netFinder_.get()->Start(finderCallBack);
    });
   }
  }
  void Finder::Stop() {
   if (notifyThread_) {
    netFinder_.get()->Stop();
    notifyThread_.get()->join();
    notifyThread_ = nullptr;
   }
  }
  SDIDeviceInfo* Finder::GetDevicesPointer()
  {
   return &devices_[0];
  }
  int32_t Finder::GetDevicesCount() const
  {
   return static_cast<int32_t>(devices_.size());
  }
}
