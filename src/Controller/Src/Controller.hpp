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
//  Controller.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "EpsonScan2.h"
#include "Engine.hpp"
#include "TransferEvent.hpp"
#include "FFManager.hpp"
#include <memory>
#include <vector>
#include <string>
namespace epsonscan {
class Scanner;
class ModelInfo;
class TransferMgr;
class KeyMgr;
class Image;
class Controller {
  public:
    Controller(const SDIDeviceInfo& devInfo, SDIScannerDriver* driver);
    virtual ~Controller();
    SDIError Open();
    void Close();
    void Reset();
    void SetValue(const std::string& key, SDIValueType valType, void* value, SDIInt size);
    void GetValue(const std::string& key, SDIValueType valType, void* value, SDIInt size);
    void GetDefault(const std::string& key, SDIValueType valType, void* value, SDIInt size);
    void GetCapability(const std::string& key, SDICapability& capability);
    SDIError Scan();
    SDIError StartAFM(bool continuous);
    SDIError StopAFM(bool continuous);
    void Cancel();
    boost::optional<TransferEvent> DequeueEvent() ;
    bool CheckNextEvent(bool waitUntilReceived);
    void SetInterruptEventCallBackProc(InterruptEventCallBackProc interruptEventCallBack, void* interruptEventCallBackUserData)
    {
     interruptEventCallBack_ = interruptEventCallBack;
     interruptEventCallBackUserData_ = interruptEventCallBackUserData;
    }
    void SetInterruptionEnabled(bool interruptionEnabled)
    {
     interruptionEnabled_ = interruptionEnabled;
    }
    void CheckGlassDirtStatus();
    bool SDIMultipage_Start(const char* destPath, SDIImageFormat format)
    {
     return FFManager::GetInstance().MultipageStart(destPath, format, keyMgr_);
    }
    bool SDIMultipage_Add(const char* sourcePath)
    {
     return FFManager::GetInstance().MultipageAdd(sourcePath);
    }
    bool SDIMultipage_Fin()
    {
     return FFManager::GetInstance().MultipageFin();
    }
    bool ConvertJpegToFormat(const char* filepath, SDIImageFormat format)
    {
     return FFManager::GetInstance().ConvertJpegToFormat(filepath, format, keyMgr_);
    }
       SDIError UnlockAdministratorLock();
      SDIError LockAdministratorLock();
  private:
    void ScannerCallBackReceiver(EngineEventType type, Image* image, SDIError error);
    std::shared_ptr<ModelInfo> modelInfo_;
    std::shared_ptr<Scanner> scanner_;
    std::shared_ptr<TransferMgr> transferMgr_;
    std::shared_ptr<KeyMgr> keyMgr_;
    bool opened_;
    bool interruptionEnabled_;
    SDIScannerDriver* driver_;
    InterruptEventCallBackProc interruptEventCallBack_;
    void* interruptEventCallBackUserData_;
};
}
