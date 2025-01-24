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
//  ModelInfo.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <cstdint>
#include <string>
#include <mutex>
#include "CommonUtility/ESCommonTypedef.h"
#include "Include/ES2Command/ESCommandProperties.h"
typedef enum {
    ESCILogFunctionLamp1Counter,
    ESCILogFunctionLamp2Counter,
    ESCILogFunctionFlatbedScanCounter,
    ESCILogFunctionSimplexScanCounter,
    ESCILogFunctionDuplexScanCounter,
    ESCILogFunctionPickupRollerCounter,
    ESCILogFunctionPowerOffTime,
} ESCILogFunctionKey;
namespace epsonscan2 {
namespace es2command {
class ModelInfo
{
private:
    ModelInfo();
public:
    static ModelInfo& Instance();
    ~ModelInfo();
    bool IsShouldKeepControlMode(const std::string& model_name);
    bool IsShouldSyncFunctionalUnit(const std::string& model_name);
    bool IsShouldZeroClearEdgeFillForFB(const std::string& model_name);
    bool IsShouldIgnoreDateAndTime(const std::string& model_name);
    bool IsShouldObserveButtonWithCommand(const std::string& model_name);
    bool IsShouldAlwaysWaitAtIMGRequest(const std::string& model_name);
    bool IsShouldIgnoreCancelResponse(const std::string& model_name);
    int32_t CustomButtonObservationInterval_ms(const std::string& model_name);
    bool IsSupportedLogFunctions(const std::string& model_name, ESCILogFunctionKey function);
    bool IsShouldSendStatAfterADFScan(const std::string& model_name);
private:
    static std::mutex sm_mtx;
    ESDictionary m_dicInfo;
};
}
}
