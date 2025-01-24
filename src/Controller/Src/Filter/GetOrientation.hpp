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
//  GetOrientation.hpp -- template and derived ESC/I ESC/I-2 protocol commands

#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "ModelInfo.hpp"
#include "Filter.hpp"
#include "Utility.hpp"
namespace epsonscan
{
    class GetOrientation : public Filter
    {
    public:
        GetOrientation(std::shared_ptr<KeyMgr> keyMgr,
                        std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo)
        {
        }
        virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override;
        std::string Name() override
        {
            return "GetOrientation";
        }
        static bool IsPluginAvailable();
        SDIOrientation GetJudgeResult()
        {
            return judgeResult_;
        }
    private:
        SDIOrientation judgeResult_ = kSDIOrientationNone;
    };
}
