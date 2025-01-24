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
//  ProcOrientation.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <utils/ESBuffer.h>
#include "ESCommonTypedef.h"
#include "ESImageInfo.h"
#include "EpsonScan2.h"
#include "Filter.hpp"
#include "KeyMgr.hpp"
#include "ModelInfo.hpp"
namespace epsonscan
{
enum EIPRotateType : ESNumber
{
 kEIPRotateType90 = 90,
 kEIPRotateType180 = 180,
 kEIPRotateType270 = 270
};
class ProcOrientation : public Filter
{
public:
           ProcOrientation(std::shared_ptr<KeyMgr> keyMgr,
                         std::shared_ptr<ModelInfo> modelInfo) : Filter(keyMgr, modelInfo)
            {
            }
            virtual void DoProcess(ESImageInfo& imageInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf) override
            {
     if(orientation_ != kSDIOrientationNone)
     {
      if(RotateImage(imageInfo, inDataBuf, orientation_) == false)
      {
       throw std::bad_alloc();
      }
     }
            }
   void SetOrientation(SDIOrientation orientation)
   {
    orientation_ = orientation;
   }
private:
 bool RotateImage(ESImageInfo& imageInfo,
      ES_CMN_FUNCS::BUFFER::CESHeapBuffer& inDataBuf,
      SDIOrientation orientation
      )
 {
  ES_CMN_FUNCS::BUFFER::CESHeapBuffer dest;
  SDIError error = kSDIErrorNone;
  switch(orientation)
  {
   case kSDIOrientation90:
   {
    RotateImageOnMem(dest, kEIPRotateType90 , imageInfo, inDataBuf , error);
    ESNumber widthBefore = ES_IMAGE_INFO::GetESImageWidth(imageInfo);
    imageInfo[ES_IMAGE_INFO::kESImageInfoWidthKey] = ES_IMAGE_INFO::GetESImageHeight(imageInfo);
    imageInfo[ES_IMAGE_INFO::kESImageInfoHeightKey] = widthBefore;
   }
   break;
   case kSDIOrientation180:
   {
    RotateImageOnMem(dest, kEIPRotateType180 , imageInfo, inDataBuf , error);
   }
   break;
   case kSDIOrientation270:
   {
    RotateImageOnMem(dest, kEIPRotateType270 , imageInfo, inDataBuf , error);
    ESNumber widthBefore = ES_IMAGE_INFO::GetESImageWidth(imageInfo);
    imageInfo[ES_IMAGE_INFO::kESImageInfoWidthKey] = ES_IMAGE_INFO::GetESImageHeight(imageInfo);
    imageInfo[ES_IMAGE_INFO::kESImageInfoHeightKey] = widthBefore;
   }
   break;
   case kSDIOrientationNone:
   break;
  }
  inDataBuf.FreeBuffer();
  inDataBuf.Attach(dest);
  return error == kSDIErrorNone;
 }
 std::string Name() override
    {
      return "ProcOrientation";
    }
 static void RotateImageOnMem(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cDestData,
         EIPRotateType eRotateType,
         const ESImageInfo& dictImageInfo,
           ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cInData,
         SDIError& eOutError);
 static void RotateImageBy90OnMem(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cDestData,
                const ESImageInfo& dictImageInfo,
              ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cInData,
            BOOL bClockwise,
            SDIError& eOutError);
 static void RotateImageB1800OnMem(ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cDestData,
                const ESImageInfo& dictImageInfo,
            ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cInData,
           SDIError& eOutError);
 SDIOrientation orientation_ = kSDIOrientationNone;
};
}
