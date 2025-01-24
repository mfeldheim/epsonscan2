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
//  ESIMP2.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include <ES2Command/ES2CommandAPI.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "ModelInfo.hpp"
#include "Filter.hpp"
#include "Utility.hpp"
#include "Error.hpp"
#include "AutoSize.hpp"
namespace epsonscan
{
class ESIMP2Wrapper;
class ESIMP2 : public Filter
{
public:
    ESIMP2(std::shared_ptr<KeyMgr> keyMgr, std::shared_ptr<ModelInfo> modelInfo);
    virtual ~ESIMP2(void);
    void Detect(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf);
    void Crop(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf);
    void DoDeficiencyCorrection(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf);
    virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override
    {
    }
    std::string Name() override
    {
        return "ESIMP2";
    }
    static std::string GetESIMP2Path();
    static bool IsESIMP2Available();
    bool IsCarrerSheetCrop(ESImageInfo& imageInfo);
private:
    void* locationData_;
};
}
