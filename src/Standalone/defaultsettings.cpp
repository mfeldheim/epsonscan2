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
//  defaultsettings.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "defaultsettings.h"
#include <fstream>
#define BOOST_NO_CXX11_RVALUE_REFERENCES 1
#include <boost/any.hpp>
#include <utils/PathUtils.h>
#if !(defined(NO_QTMODE) || defined(BUILDSANE))
#include <QStandardPaths>
#endif
#include "devicelist.h"
#include "../Include/Config.h"
DefaultSettings::DefaultSettings()
{
#ifdef AKBMODE
   std::string strDst = ".";
   strDst = strDst + DRIVER_NAME;
   std::string dir3((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3, (strDst + "/").c_str());
   this->SettingsFilePath = dir3.c_str();
#else
#if defined(NO_QTMODE) || defined(BUILDSANE)
   std::string dir3 = std::getenv("HOME");
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3,".epsonscan2/");
   this->SettingsFilePath = dir3.c_str();
#else
   std::string dir3((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3,".epsonscan2/");
   this->SettingsFilePath = dir3.c_str();
#endif
#endif
}
bool DefaultSettings::CheckDefaultSettingsFile()
{
#if defined(NO_QTMODE) || defined(BUILDSANE)
    std::string dir1 = std::getenv("HOME");
#else
    std::string dir1((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
#endif
#ifdef AKBMODE
    std::string strDst = ".";
    strDst = strDst + DRIVER_NAME;
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, (strDst + "/").c_str());
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1,".epsonscan2/");
#endif
    if(!(bool)ES_CMN_FUNCS::PATH::ES_IsExistFile(dir1)){
        ES_CMN_FUNCS::PATH::ES_MakeFolder(dir1);
    }
    if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(this->SettingsFilePath) == FALSE)
    {
        ES_CMN_FUNCS::PATH::ES_MakeFolder(this->SettingsFilePath);
    }
    std::string default_settings_file = this->SettingsFilePath.c_str();
    ES_CMN_FUNCS::PATH::ES_CombinePath(default_settings_file, default_settings_file, "DefaultSettings.SF2");
    return ES_CMN_FUNCS::PATH::ES_IsExistFile(default_settings_file);
}
void DefaultSettings::DeleteDefaultSettingsFile()
{
    std::string default_settings_file = this->SettingsFilePath.c_str();
    default_settings_file = default_settings_file + "DefaultSettings.SF2";
    try {
        DeleteFile(default_settings_file.c_str());
    }
    catch (...) {
        throw;
    }
}
bool DefaultSettings::ReadSettingsFile(SCANPARA* device_data)
{
    std::string user_settings_file = this->SettingsFilePath.c_str();
    user_settings_file = user_settings_file + "/DefaultSettings.SF2";
    const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFolder(user_settings_file);
    if ( !result ) {
        return false;
    }
    this->SetDeviceData(user_settings_file, device_data);
    return true;
}
#include "ESAnyCastUtils.h"
void DefaultSettings::SetDeviceData(std::string settings_file_path, SCANPARA* device_data)
{
    try{
        ESDictionary out;
        ES_CMN_FUNCS::JSON::JSONFiletoDictionary(settings_file_path, out);
        ESDictionary preset = SAFE_ANY_VALUE_FROM_DICT(out,"Preset",ESDictionary, ESDictionary());
        ESDictionary devnum = SAFE_ANY_VALUE_FROM_DICT(preset,"0",ESDictionary, ESDictionary());
        device_data->FunctionalUnit.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"FunctionalUnit",ESNumber,ADF);
        device_data->FunctionalUnit_Auto = SAFE_ANY_VALUE_FROM_DICT(devnum,"FunctionalUnit_Auto",ESNumber,0);
        device_data->ColorType.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ColorType",ESNumber,ColorTypeRGB24);
        device_data->AutoColorPixelType.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AutoColorPixelType",ESNumber,AutoColorPixelTypeMono);
        device_data->AutoColorPixelLevel.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AutoColorPixelLevel",ESNumber,0);
        device_data->Resolution.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Resolution",ESNumber,200);
        device_data->ImageFormatSettings.ImageFormat.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ImageFormat",ESNumber,ImageFormatColorJpegMonoRaw);
        device_data->Gamma.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Gamma",ESNumber,22);
        device_data->ScanArea.ScanAreaWidth.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ScanAreaWidth",ESNumber,0);
        device_data->ScanArea.ScanAreaHeight.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ScanAreaHeight",ESNumber,0);
        device_data->ScanArea.ScanAreaOffsetX.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ScanAreaOffsetX",ESNumber,0);
        device_data->ScanArea.ScanAreaOffsetY.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"ScanAreaOffsetY",ESNumber,0);
        device_data->ScanArea.FixedSize = (DocumentSize)SAFE_ANY_VALUE_FROM_DICT(devnum,"FixedDocumentSize",ESNumber,Auto_Detect);
        device_data->ScanArea.UserDefine_Width = SAFE_ANY_VALUE_FROM_DICT(devnum,"UserScanAreaWidth",ESNumber,0);
        device_data->ScanArea.UserDefine_Width /= 100;
        device_data->ScanArea.UserDefine_Length = SAFE_ANY_VALUE_FROM_DICT(devnum,"UserScanAreaHeight",ESNumber,0);
        device_data->ScanArea.UserDefine_Length /= 100;
        device_data->DropoutColor.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DropoutColor",ESNumber,DropoutColorNone);
        device_data->Orientation.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Orientation",ESNumber,OrientationNone);
        device_data->ImageFormatSettings.MultiTiffEnabled.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"MultiTiffEnabled",ESNumber,0);
        device_data->ImageFormatSettings.TiffCompression.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"MultiTiffCompression",ESNumber,TiffCompressionNone);
        device_data->ImageFormatSettings.OFDEnabled.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"OFDEnabled",ESNumber,0);
        device_data->Contrast.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Contrast",ESNumber,0);
        device_data->Brightness.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Brightness",ESNumber,0);
        device_data->Threshold.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"Threshold",ESNumber,110);
        device_data->ImageFormatSettings.JpegQuality.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"JpegQuality",ESNumber,85);
        device_data->ImageFormatSettings.JpegQuality_forJPEG = SAFE_ANY_VALUE_FROM_DICT(devnum,"JpegQualityForJpeg",ESNumber,85);
        device_data->ImageFormatSettings.JpegQuality_forPDF = SAFE_ANY_VALUE_FROM_DICT(devnum,"JpegQualityForPdf",ESNumber,37);
        device_data->ImageFormatSettings.JpegProgressive.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"jpegProgressive",ESNumber,false);
        device_data->DuplexType.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DuplexType",ESNumber,Double_Sided);
        device_data->PagesTobeScanned.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"PagesTobeScanned",ESNumber,0);
        device_data->DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DoubleFeedDetectionLevel",ESNumber,DoubleFeedDetectionLow);
        device_data->DoubleFeedDetectionValue.DoubleFeedDetection.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DoubleFeedDetection",ESNumber,true);
        device_data->DoubleFeedDetectionValue.DoubleFeedDetectionAreaMin.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DoubleFeedDetectionAreaMin",ESNumber,0);
        device_data->DoubleFeedDetectionValue.DoubleFeedDetectionAreaLength.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DoubleFeedDetectionAreaLength",ESNumber,0);
        device_data->BlankPageSkipKey.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"BlankPageSkip",ESNumber,false);
        device_data->BlankPageSkipLevelKey.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"BlankPageSkipLevel",ESNumber,10);
        device_data->BackgroundRemoval.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"BackgroundRemoval",ESNumber,BackgroundRemovalNone);
        device_data->PaperDeskew.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"PaperDeskew",ESNumber,true);
        device_data->ScanArea.AutoSize.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AutoSize",ESNumber,true);
        device_data->ScanArea.PaperEndDetection.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"PaperEndDetection",ESNumber,false);
        device_data->ScanArea.PaperEndDetectionMemory = SAFE_ANY_VALUE_FROM_DICT(devnum,"PaperEndDetectionMemory",ESNumber,false);
        device_data->TransferCompression.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"TransferCompression",ESNumber,true);
        device_data->Add_Pages = SAFE_ANY_VALUE_FROM_DICT(devnum,"AddPages",ESNumber,false);
        device_data->Prefix = SAFE_ANY_VALUE_FROM_DICT(devnum,"FileNamePrefix",ESString,"img");
        device_data->FileName_OverWrite = SAFE_ANY_VALUE_FROM_DICT(devnum,"FileNameOverWrite",ESNumber,false);
        device_data->FileName_Counter = SAFE_ANY_VALUE_FROM_DICT(devnum,"FileNameCounter",ESNumber,false);
        device_data->ImageFormatSettings.PDFImgFormatOption.AllPage = SAFE_ANY_VALUE_FROM_DICT(devnum,"PDFAllPages",ESNumber,true);
        if(device_data->ImageFormatSettings.PDFImgFormatOption.AllPage){
            device_data->ImageFormatSettings.PDFImgFormatOption.page = SAFE_ANY_VALUE_FROM_DICT(devnum,"PDFSelectPage",ESNumber,0);
        }else {
            device_data->ImageFormatSettings.PDFImgFormatOption.page = SAFE_ANY_VALUE_FROM_DICT(devnum,"PDFSelectPage",ESNumber,1);
        }
        device_data->AutoCroppingInscribed.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AutoCroppingInscribed",ESNumber,true);
    #if defined(NO_QTMODE) || defined(BUILDSANE)
        device_data->UserDefinePath = SAFE_ANY_VALUE_FROM_DICT(devnum,"UserDefinePath",ESString, std::getenv("HOME"));
        device_data->Folder = SAFE_ANY_VALUE_FROM_DICT(devnum,"Folder",ESNumber,USER_DEFINE);
    #else
        device_data->UserDefinePath = SAFE_ANY_VALUE_FROM_DICT(devnum,"UserDefinePath",ESString,(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toLocal8Bit()).constData());
        device_data->Folder = SAFE_ANY_VALUE_FROM_DICT(devnum,"Folder",ESNumber,Document);
    #endif
        device_data->ImageOption = SAFE_ANY_VALUE_FROM_DICT(devnum,"ImageOption",ESNumber,ImageOptionNone);
        device_data->DNShow_PlasticCard_dialog = SAFE_ANY_VALUE_FROM_DICT(devnum,"DNShow_PlasticCard_dialog",ESNumber,false);
        device_data->DNShow_LongPaperWarning_dialog = SAFE_ANY_VALUE_FROM_DICT(devnum,"DNShow_LongPaperWarning_dialog",ESNumber,false);
        device_data->OverDurationAlert = SAFE_ANY_VALUE_FROM_DICT(devnum,"OverDurationAlert",ESNumber,false);
        device_data->NearDurationAlert = SAFE_ANY_VALUE_FROM_DICT(devnum,"NearDurationAlert",ESNumber,false);
        device_data->AutomaticFeedingMode.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AFMMode",ESNumber,false);
        device_data->AFMTimeout.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AFMTimeout",ESNumber,180);
        device_data->BackgroundColor.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"BackgroundColor",ESNumber,BackgroundColorBlack);
    }
    catch (...) {
        std::cout << "A problem was found in the contents of the DefaultSettings.SF2 file." << std::endl;
        throw;
    }
}
