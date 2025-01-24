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
//  Lut.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "ModelInfo.hpp"
#include "Filter.hpp"
#include "Utility.hpp"
namespace epsonscan
{
extern void BuildGammaTable(int brightness,
          int contrast,
          int gamma,
          unsigned char* GammaR,
                            unsigned char* GammaG,
          unsigned char* GammaB);
class Lut : public Filter
{
public:
           Lut(std::shared_ptr<KeyMgr> keyMgr,
                      std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo), autoJudgedColor_(true)
            {
            }
            virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override;
            static bool isFitPluginAvailable();
            bool isSKipLut();
            void SetAutoJudgedColor(bool autoJudgedColor)
            {
                autoJudgedColor_ = autoJudgedColor;
            }
protected:
            std::string Name() override
            {
                return "Lut";
            }
private:
    bool autoJudgedColor_;
 static void ProcessLUTUsingFit(ESImageInfo& imageInfo,
     ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf,
     ESNumber brightness,
     ESNumber contrast,
                    ESNumber gamma,
                    SDIBackgroundRemoval bgRemoval,
                    std::string workFolder
                    );
 static void ProcessLUT(ESImageInfo& imageInfo,
     ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf,
                    std::shared_ptr<KeyMgr> keyMgr,
                    std::shared_ptr<ModelInfo> modelInfo,
                    bool autoJudgedColor
                    );
      static void ProcessLUT(ESImageInfo& imageInfo,
     ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf,
                    unsigned char* gammaR,
                    unsigned char* gammaG,
                    unsigned char* gammaB
                    );
};
}
