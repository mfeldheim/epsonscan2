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
//  Filter.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Filter.hpp"
#include "Utility.hpp"
#include <utils/PathUtils.h>
namespace epsonscan
{
    void Filter::Process(ESImageInfo& imageInfo,
          ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf)
    {
                SDI_TRACE_LOG("enter %s for page = %d", Name().c_str(), ES_IMAGE_INFO::GetESImagePageCount(imageInfo));
                DoProcess(imageInfo, inDataBuf);
    DumpImage(imageInfo, inDataBuf, Name().c_str());
                SDI_TRACE_LOG("leave %s for page = %d", Name().c_str(), ES_IMAGE_INFO::GetESImagePageCount(imageInfo));
     }
    std::string Filter::GetPluginRootDir()
    {
   std::string strModulePath = EPSON_INSTALL_PATH;
      ES_CMN_FUNCS::PATH::ES_CombinePath(strModulePath, strModulePath, ES_STRING("non-free-exec"));
   return strModulePath;
    }
}
