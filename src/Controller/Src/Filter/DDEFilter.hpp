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
//  DDEFilter.hpp -- template and derived ESC/I ESC/I-2 protocol commands
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
enum ActionTypeDDE : ESNumber
{
    kActionTypeADE,
    kActionTypeBin
};
class DDEFilter : public Filter
{
public:
    DDEFilter(std::shared_ptr<KeyMgr> keyMgr,
          std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo),
                                                  actionType_(kActionTypeADE)
    {
    }
    void SetActionType(ActionTypeDDE type)
    {
        actionType_ = type;
    }
    virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override;
    std::string Name() override
    {
        return "TextEnhanceFilter";
    }
    static bool IsDDEAvailable();
private:
    ActionTypeDDE actionType_;
};
}
