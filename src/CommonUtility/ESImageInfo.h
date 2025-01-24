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
//  ESImageInfo.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <assert.h>
#include "ESCommonTypedef.h"
#include "../Include/IESBuffer.h"
#include "utils/ESAnyCastUtils.h"
#include "../CommonUtility/utils/ESJsonUtils.h"
typedef ESFloatMultiArray ESProfileMatrix;
typedef ESFloatMultiArray ESGrayReproductionMatrix;
typedef ESDictionary ESGammaTable;
typedef ESDictionary ESMutableGammaTable;
STATIC_CONST_KEY kESGammaTableMaxKey = ES_STRING("gammaTabeType");
typedef enum
{
    kESGammaTableMax256 = 256,
} ESGammaTableMax;
STATIC_CONST_KEY kESGammaTableRedChannelKey = ES_STRING("redChannel");
STATIC_CONST_KEY kESGammaTableGreenChannelKey = ES_STRING("greenChannel");
STATIC_CONST_KEY kESGammaTableBlueChannelKey = ES_STRING("blueChannel");
STATIC_CONST_KEY kESGammaTableMonoChannelKey = ES_STRING("monoChannel");
STATIC_CONST_KEY kESImageInfoArray = ES_STRING("imageInfos");
static ESIndexArray getESGammaTableRBytes(const ESGammaTable& gammaTable)
{
 return SAFE_ANY_VALUE_FROM_DICT(gammaTable,kESGammaTableRedChannelKey,ESIndexArray,ESIndexArray());
}
static ESIndexArray getESGammaTableGBytes(const ESGammaTable& gammaTable)
{
 return SAFE_ANY_VALUE_FROM_DICT(gammaTable,kESGammaTableGreenChannelKey,ESIndexArray,ESIndexArray());
}
static ESIndexArray getESGammaTableBBytes(const ESGammaTable& gammaTable)
{
 return SAFE_ANY_VALUE_FROM_DICT(gammaTable,kESGammaTableBlueChannelKey,ESIndexArray,ESIndexArray());
}
static ESIndexArray getESGammaTableMonoBytes(const ESGammaTable& gammaTable)
{
 return SAFE_ANY_VALUE_FROM_DICT(gammaTable,kESGammaTableMonoChannelKey,ESIndexArray,ESIndexArray());
}
static void getESGammaTableRGBData(ES_CMN_FUNCS::BUFFER::IESBuffer& cBufDest,const ESGammaTable& dictGammaTable){
 cBufDest.FreeBuffer();
 ESIndexArray arR = getESGammaTableRBytes(dictGammaTable);
 ESIndexArray arG = getESGammaTableGBytes(dictGammaTable);
 ESIndexArray arB = getESGammaTableBBytes(dictGammaTable);
 if(arR.size() + arG.size() + arB.size() != kESGammaTableMax256*3){
  return;
 }
 if(!cBufDest.AllocBuffer( kESGammaTableMax256*3)){
  return;
 }
 UInt8* pTable = cBufDest.GetBufferPtr();
 for(size_t nLoop=0;nLoop<arR.size();nLoop++){
  UInt8 un8Data = arR[nLoop];
  *pTable = un8Data;
  pTable++;
 }
 for(size_t nLoop=0;nLoop<arG.size();nLoop++){
  UInt8 un8Data = arG[nLoop];
  *pTable = un8Data;
  pTable++;
 }
 for(size_t nLoop=0;nLoop<arB.size();nLoop++){
  UInt8 un8Data = arB[nLoop];
  *pTable = un8Data;
  pTable++;
 }
}
typedef std::map<ESString,ESNumber> ESImageInfo;
typedef std::deque<ESImageInfo> ESImageInfoArray;
namespace ES_IMAGE_INFO{
 STATIC_CONST_KEY kESImageInfoWidthKey = ES_STRING("width");
 STATIC_CONST_KEY kESImageInfoHeightKey = ES_STRING("height");
 STATIC_CONST_KEY kESImageInfoSamplesPerPixelKey = ES_STRING("samplesPerPixel");
 STATIC_CONST_KEY kESImageInfoBitsPerSampleKey = ES_STRING("bitsPerSample");
 STATIC_CONST_KEY kESImageInfoResolutionXKey = ES_STRING("resolutionX");
 STATIC_CONST_KEY kESImageInfoResolutionYKey = ES_STRING("resolutionY");
 STATIC_CONST_KEY kESImageInfoOutputResolutionKey = ES_STRING("outputResolution");
 STATIC_CONST_KEY kESImageInfoSurfaceTypeKey = ES_STRING("SurfaceType");
 ESNumber GetImageInfoValueForKey(const ESImageInfo& info,ESString strKey);
 void GetImageInfoAsDict(ESDictionary& dict,const ESImageInfo& imageInfo);
 void GetImageInfoAsJson(ESString& strImageInfoAsJson,const ESImageInfo& srcImageInfo);
 void GetImageInfoArrayAsJson(ESString& strImageInfoArrayAsJson,ESImageInfoArray& srcImageInfoArray);
 void MakeImageInfoFromDict(ESImageInfo& imageInfoDest,ESDictionary dictImageInfo);
 void MakeImageInfoFromJson(ESImageInfo& imageInfoDest,ESString strImageInfoAsJson);
 void MakeImageInfoArrayAsDicArray(ESDicArray& arDicImageInfos,const ESImageInfoArray& arImageInfos);
 void MakeImageInfoArrayFromDicArray(ESImageInfoArray& arDestImageInfos, const ESDicArray& arDicImageInfos);
 void MakeImageInfoArrayFromJson(ESImageInfoArray& arDestImageInfos,const ESString& strImageInfosAsJson);
 enum ESImageInfoSurfaceType{
  kESImageInfoSurfaceTypeFrontSide = 0,
  kESImageInfoSurfaceTypeBackSide
 };
 STATIC_CONST_KEY kESImageInfoDigitalICETypeKey = ES_STRING("DigitalICEType");
 typedef enum
 {
  kESImageInfoDigitalICETypeNone,
  kESImageInfoDigitalICETypeTransparent,
  kESImageInfoDigitalICETypeTransparentIR,
  kESImageInfoDigitalICETypeFlatbedLamp1,
  kESImageInfoDigitalICETypeFlatbedLamp2
 } ESImageInfoDigitalICEType;
 STATIC_CONST_KEY kESImageInfoScanCountKey = ES_STRING("scanCount");
 STATIC_CONST_KEY kESImageInfoPageCountKey = ES_STRING("pageCount");
 STATIC_CONST_KEY kESImageInfoPaperCountKey = ES_STRING("paperCount");
 STATIC_CONST_KEY kESImageInfoDataTypeKey = ES_STRING("dataType");
 typedef enum {
  kESImageDataTypeRaw = 0,
  kESImageDataTypeJpeg
 }ESImageDataType;
 STATIC_CONST_KEY kESImageInfoCarrierSheetTypeKey = ES_STRING("carrierSheet");
 typedef enum
 {
  kESImageInfoCarrierSheetTypeOFF,
  kESImageInfoCarrierSheetTypeON,
 } ESImageInfoCarrierSheetType;
 STATIC_CONST_KEY kESImageInfoUpsideDownKey = ES_STRING("upsideDown");
 STATIC_CONST_KEY kESImageInfoAutoCroppedKey = ES_STRING("autoCropped");
 STATIC_CONST_KEY kESImageInfoBlankPageKey = ES_STRING("blankpage");
 STATIC_CONST_KEY kESImageInfoMonoPageKey = ES_STRING("monopage");
 typedef enum {
   kESImageColorTypeRGB,
   kESImageColorTypeRGBA,
   kESImageColorTypeRGB16,
   kESImageColorTypeRGBA16,
   kESImageColorTypeRGBJpeg,
   kESImageColorTypeGray,
   kESImageColorTypeGray16,
   kESImageColorTypeGrayJpeg,
   kESImageColorTypeMono,
   kESImageColorTypeOthers,
 }ESImageColorType;
 ESNumber GetESImageResolutionX(const ESImageInfo& imageInfo);
 ESNumber GetESImageResolutionY(const ESImageInfo& imageInfo);
 ESNumber GetESImageOutputResolution(const ESImageInfo& imageInfo);
 ESNumber GetESImageBitsPerSample(const ESImageInfo& imageInfo);
 ESNumber GetESImageSamplesPerPixel(const ESImageInfo& imageInfo);
 ESNumber GetESImageBitsPerPixel(const ESImageInfo& imageInfo);
 ESNumber GetESImageHeight(const ESImageInfo& imageInfo);
 ESNumber GetESImageWidth(const ESImageInfo& imageInfo);
 ESNumber IsESImageEmpty(const ESImageInfo& imageinfo);
 ESNumber GetESImageBytesPerRow(const ESImageInfo& imageInfo);
 ESNumber GetESImageBytesPerCol(const ESImageInfo& imageInfo);
 ESNumber GetESImagePixelsPerRow(const ESImageInfo& imageInfo);
 ESNumber GetESImageSize(const ESImageInfo& imageInfo);
 UInt32 GetESImageSizeUN(const ESImageInfo& imageInfo);
 ESNumber GetESImagePageCount(const ESImageInfo& imageInfo);
 ESNumber GetESImagePaperCount(const ESImageInfo& imageInfo);
 ESNumber GetESImageScanCount(const ESImageInfo& imageInfo);
 ESImageDataType GetESImageDataType(const ESImageInfo& imageInfo);
 ESImageInfoSurfaceType GetESImageSurfaceType(const ESImageInfo& imageInfo);
 ESImageInfoSurfaceType GetESImageOthersideSurfaceType(const ESImageInfo& imageInfo);
 ESImageInfoCarrierSheetType GetESImageCarrierSheetType(const ESImageInfo& imageInfo) ;
 BOOL GetESImageUpsideDown(const ESImageInfo& imageInfo);
 BOOL GetESImageAutoCropped(const ESImageInfo& imageInfo);
 ESImageColorType GetESImageColorType(const ESImageInfo& imageInfo);
 bool GetESImageBlankPageSkip(const ESImageInfo& imageInfo);
 bool GetESImageMonoPage(const ESImageInfo& imageInfo);
 typedef ESDictionary ESBackgroundColor;
 STATIC_CONST_KEY kESBackgroundColorFrontKey = ES_STRING("front");
 STATIC_CONST_KEY kESBackgroundColorBackKey = ES_STRING("back");
 STATIC_CONST_KEY kESBackgroundColorRedKey = ES_STRING("red");
 STATIC_CONST_KEY kESBackgroundColorGreenKey = ES_STRING("green");
 STATIC_CONST_KEY kESBackgroundColorBlueKey = ES_STRING("blue");
 STATIC_CONST_KEY kESBackgroundColorRedRangeKey = ES_STRING("redRange");
 STATIC_CONST_KEY kESBackgroundColorGeenRangeKey = ES_STRING("greenRange");
 STATIC_CONST_KEY kESBackgroundColorBlueRangeKey = ES_STRING("blueRange");
 STATIC_CONST_KEY kESBackgroundColorMonoKey = ES_STRING("mono");
 STATIC_CONST_KEY kESBackgroundColorMonoRangeKey = ES_STRING("monoRange");
}
