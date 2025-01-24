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
//  Filter.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "KeyMgr.hpp"
#include "ModelInfo.hpp"
namespace epsonscan
{
    class Filter
    {
        public:
            Filter(std::shared_ptr<KeyMgr> keyMgr,
                   std::shared_ptr<ModelInfo> modelInfo) : keyMgr_(keyMgr), modelInfo_(modelInfo)
            {
            }
            void Process(ESImageInfo& imageInfo,
          ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf);
            virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) = 0;
        protected:
           std::shared_ptr<KeyMgr> keyMgr_;
           std::shared_ptr<ModelInfo> modelInfo_;
           virtual std::string Name() = 0;
            void DumpImage(const ESImageInfo& imageInfo, const ES_CMN_FUNCS::BUFFER::CESHeapBuffer& dataBuf, std::string name)
            {
                std::stringstream fileNameStream;
                fileNameStream << "LOGIMAGE_"
                            << ES_IMAGE_INFO::GetESImagePageCount(imageInfo)
                            << "_"
                            << ES_IMAGE_INFO::GetESImagePaperCount(imageInfo)
                            << "_"
                            << name;
                AfxGetLog()->InitImage(fileNameStream.str().c_str()
                                    ,(ENUM_IMAGE_TYPE::enumImageType)ES_IMAGE_INFO::GetESImageDataType(imageInfo)
                                    ,ES_IMAGE_INFO::GetESImageBitsPerPixel(imageInfo)
                                    ,ES_IMAGE_INFO::GetESImageWidth(imageInfo)
                                    ,ES_IMAGE_INFO::GetESImageHeight(imageInfo));
                AfxGetLog()->DumpImage(fileNameStream.str().c_str()
                                    ,(ENUM_IMAGE_TYPE::enumImageType)ES_IMAGE_INFO::GetESImageDataType(imageInfo)
                                    ,ES_IMAGE_INFO::GetESImageBitsPerPixel(imageInfo)
                                    ,*(ES_CMN_FUNCS::BUFFER::IESBuffer*)&dataBuf);
            }
            static std::string GetPluginRootDir();
    };
}
