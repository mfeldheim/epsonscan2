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
//  Padding.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "KeyMgr.hpp"
#include "ModelInfo.hpp"
#include "Filter.hpp"
namespace epsonscan
{
class Padding : public Filter
{
public:
    Padding(std::shared_ptr<KeyMgr> keyMgr,
           std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo)
    {
    }
    virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override
    {
        if ( ES_IMAGE_INFO::GetESImageSize(imageInfo) != inDataBuf.GetLength())
        {
            SDI_TRACE_LOG("Padding will do process");
   UInt8* pInBytes = inDataBuf.GetConstBufferPtr();
      ES_CMN_FUNCS::BUFFER::CESHeapBuffer outDataBuf;
   if (outDataBuf.AllocBuffer(ES_IMAGE_INFO::GetESImageSize(imageInfo)) == false)
            {
                SDI_TRACE_LOG("AllocBuffer fails");
                throw std::bad_alloc();
            }
   UInt8* pOutBytes = outDataBuf.GetBufferPtr();
            memcpy(pOutBytes, pInBytes, outDataBuf.GetLength());
   inDataBuf.FreeBuffer();
   inDataBuf.Attach(outDataBuf);
            SDI_TRACE_LOG("Padding end  process");
        }
    }
    std::string Name() override
    {
      return "Padding";
    }
private:
};
}
