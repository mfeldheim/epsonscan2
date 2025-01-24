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
//  JpegDecode.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "KeyMgr.hpp"
#include "ModelInfo.hpp"
#include "Filter.hpp"
#include "../FileFormat/FFManager.hpp"
namespace epsonscan
{
    class JpegDecode : public Filter
    {
        public:
           JpegDecode(std::shared_ptr<KeyMgr> keyMgr,
                      std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo)
            {
            }
            virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override
            {
    if (ES_IMAGE_INFO::GetESImageDataType(imageInfo) == (ESNumber)kESImageFormatJPEG)
    {
                    FFManager ffMgr = FFManager::GetInstance();
     imageInfo[ES_IMAGE_INFO::kESImageInfoDataTypeKey] = (ESNumber)ES_IMAGE_INFO::kESImageDataTypeJpeg;
     DumpImage(imageInfo, inDataBuf, "sourceJpeg");
                    bool decodeOnlyValid = false;
                    if (keyMgr_->GetCommandValueAsBool(kESPaperEndDetection))
                    {
                        decodeOnlyValid = true;
                    }
     if(ffMgr.DecodeJpeg(inDataBuf,
                                       (ESNumber)ES_IMAGE_INFO::GetESImageHeight(imageInfo),
                                       (ESNumber)ES_IMAGE_INFO::GetESImageSize(imageInfo),
                                       decodeOnlyValid
                                        ) == false)
     {
      SDI_TRACE_LOG("DecodeJpeg fails for page = %d", ES_IMAGE_INFO::GetESImagePageCount(imageInfo));
      throw std::bad_alloc();
     }
     imageInfo[ES_IMAGE_INFO::kESImageInfoDataTypeKey] = (ESNumber)ES_IMAGE_INFO::kESImageDataTypeRaw;
    }
            }
            std::string Name() override
            {
                return "JpegDecode";
            }
    };
}
