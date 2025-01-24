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
//  lastusedsettings.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include <fstream>
#define BOOST_NO_CXX11_RVALUE_REFERENCES 1
#include <boost/any.hpp>
#include <utils/PathUtils.h>
#ifndef NO_QTMODE
#include <QStandardPaths>
#endif
#include "devicelist.h"
#include "lastusedsettings.h"
#include "../Include/Config.h"
LastUsedSettings::LastUsedSettings()
{
#ifdef AKBMODE
    std::string strDst = ".";
    strDst = strDst + DRIVER_NAME;
    std::string dir1((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, (strDst + "/Connection").c_str());
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1,"PreferredInfo.dat");
    this->PreferredInfoFilePath = dir1.c_str();
    std::string dir3((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3, (strDst + "/Settings/").c_str());
    this->SettingsFilePath = dir3.c_str();
#else
#ifdef NO_QTMODE
    std::string dir1 = std::getenv("HOME");
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, ".epsonscan2/Connection");
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, "PreferredInfo.dat");
    this->PreferredInfoFilePath = dir1.c_str();
    std::string dir3 = std::getenv("HOME");
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3,".epsonscan2/Settings/");
    this->SettingsFilePath = dir3.c_str();
#else
   std::string dir1((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, ".epsonscan2/Connection");
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, "PreferredInfo.dat");
   this->PreferredInfoFilePath = dir1.c_str();
   std::string dir3((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
   ES_CMN_FUNCS::PATH::ES_CombinePath(dir3, dir3,".epsonscan2/Settings/");
   this->SettingsFilePath = dir3.c_str();
#endif
#endif
}
bool LastUsedSettings::CheckLastUsedDevice()
{
#ifdef NO_QTMODE
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
    std::string folder;
    ES_CMN_FUNCS::PATH::ES_GetFolderPath(folder, this->PreferredInfoFilePath);
    if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(folder) == FALSE)
    {
        ES_CMN_FUNCS::PATH::ES_MakeFolder(folder);
        return false;
    }
    const std::string connect_path(this->PreferredInfoFilePath.c_str());
    return (bool)ES_CMN_FUNCS::PATH::ES_IsExistFile(connect_path);
}
bool LastUsedSettings::ReadPreferredInfo()
{
  ESDictionary out;
  try{
      if(!this->CheckLastUsedDevice()){
          return false;
      }
      ES_CMN_FUNCS::JSON::JSONFiletoDictionary(this->PreferredInfoFilePath.c_str(), out);
      ESString connection = boost::any_cast<ESString>(out["Connection"]);
      ESString display_name = boost::any_cast<ESString>(out["ESDisplayName"]);
      if(connection == "USB"){
          if(!this->SelectUSBDevice(display_name)){
              return false;
          }
      }else {
          if(!this->SelectNetworkDevice(connection)){
              return false;
          }
      }
  }
  catch (...) {
      DeleteFile(this->PreferredInfoFilePath.c_str());
  }
  return true;
}
bool LastUsedSettings::SelectUSBDevice(std::string display_name)
{
    auto device = DeviceList::device_list.begin();
    int i = 0;
    while(i < (signed)DeviceList::device_list.size()){
        if(device->displayName == display_name){
            DeviceList::select_device = i;
            return true;
        }
        ++device;
        i++;
    }
    return false;
}
bool LastUsedSettings::SelectNetworkDevice(std::string ip)
{
    auto device = DeviceList::device_list.begin();
    int i = 0;
    while(i < (signed)DeviceList::device_list.size()){
        if(device->ipAddress == ip){
            DeviceList::select_device = i;
            return true;
        }
        ++device;
        i++;
    }
    device = DeviceList::manu_network_device_list.begin();
    i = 0;
    while(i < (signed)DeviceList::manu_network_device_list.size()){
        if(strncmp(ip.c_str(), device->ipAddress, strlen(ip.c_str())) == 0){
            DeviceList::select_device = i + DeviceList::device_list.size();
            return true;
        }
        ++device;
        i++;
    }
    return false;
}
void LastUsedSettings::CreatePreferredInfo(SDIDeviceInfo dev_info)
{
    if(this->CheckLastUsedDevice()){
        try {
            DeleteFile(this->PreferredInfoFilePath.c_str());
        }
        catch (...) {
            throw;
        }
    }
    try{
        ESDictionary dict;
        if(dev_info.ipAddress[0] == '\0'){
            dict["ESDisplayName"] = (ESString)dev_info.displayName;
            dict["Connection"] = (ESString)"USB";
        }else {
            dict["ESDisplayName"] = (ESString)"Network Scanner";
            dict["Connection"] = (ESString)dev_info.ipAddress;
        }
        ES_CMN_FUNCS::JSON::DictionaryToJSONFile(dict, this->PreferredInfoFilePath.c_str());
    }
    catch (...) {
        DeleteFile(this->PreferredInfoFilePath.c_str());
    }
}
void LastUsedSettings::DeletePreferredInfo(void)
{
    try {
        DeleteFile(this->PreferredInfoFilePath.c_str());
    }
    catch (...) {
        throw;
    }
}
bool LastUsedSettings::CheckCommonSettingsFile()
{
#ifdef NO_QTMODE
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
    std::string common_settings_file = this->SettingsFilePath.c_str();
    ES_CMN_FUNCS::PATH::ES_CombinePath(common_settings_file, common_settings_file, "CommonSettings.SF2");
    return ES_CMN_FUNCS::PATH::ES_IsExistFile(common_settings_file);
}
CONFIGURATION LastUsedSettings::ReadCommonSettingsFile()
{
    CONFIGURATION config_val;
    memset(&config_val, 0, sizeof(CONFIGURATION));
    try{
        if(this->CheckCommonSettingsFile()){
            std::string common_settings_file = this->SettingsFilePath.c_str();
            common_settings_file = common_settings_file + "CommonSettings.SF2";
            ESDictionary out;
            ES_CMN_FUNCS::JSON::JSONFiletoDictionary(common_settings_file, out);
            config_val.units = (Units)boost::any_cast<ESNumber>(out["ESUnit"]);
            config_val.last_used_settings = boost::any_cast<ESNumber>(out["ESLastUsedSettings"]);
            config_val.compression = boost::any_cast<ESNumber>(out["ESCompression"]);
            config_val.open_img_folder = boost::any_cast<ESNumber>(out["ESOpenFolder"]);
            config_val.quality_preview = boost::any_cast<ESNumber>(out["ESQualityPreview"]);
            if(config_val.quality_preview){
                config_val.preview_resolution = 150;
            }else {
                config_val.preview_resolution = 50;
            }
        }else {
            config_val.units = (Units)unit_inchi;
            config_val.last_used_settings = true;
            config_val.compression = true;
            config_val.open_img_folder = true;
            config_val.quality_preview = false;
            config_val.preview_resolution = 50;
        }
    }
    catch (...) {
        DeleteFile((this->SettingsFilePath + "CommonSettings.SF2").c_str());
    }
    return config_val;
}
CONFIGURATION LastUsedSettings::ReadMainWindowInfo()
{
    Configuration& config = Configuration::GetConfiguration();
    if(this->CheckCommonSettingsFile()){
        try{
            std::string common_settings_file = this->SettingsFilePath.c_str();
            common_settings_file = common_settings_file + "CommonSettings.SF2";
            ESDictionary out;
            ES_CMN_FUNCS::JSON::JSONFiletoDictionary(common_settings_file, out);
            config.config_para.WindowPositionX = boost::any_cast<ESNumber>(out["WindowPositionX"]);
            config.config_para.WindowPositionY = boost::any_cast<ESNumber>(out["WindowPositionY"]);
            config.config_para.WindowWidth = boost::any_cast<ESNumber>(out["WindowWidth"]);
            config.config_para.WindowHeight = boost::any_cast<ESNumber>(out["WindowHeight"]);
        }
        catch (...) {
            DeleteFile((this->SettingsFilePath + "CommonSettings.SF2").c_str());
        }
    }
    return config.config_para;
}
void LastUsedSettings::CreateCommonSettingsFile(Configuration& config)
{
    std::string common_settings_file = this->SettingsFilePath.c_str();
    common_settings_file = common_settings_file + "CommonSettings.SF2";
    if(this->CheckCommonSettingsFile()){
        this->DeleteCommonSettingsFile();
    }
    try{
        ESDictionary dict;
        dict["ESUnit"] = (ESNumber)config.config_para.units;
        dict["ESLastUsedSettings"] = (ESNumber)config.config_para.last_used_settings;
        dict["ESCompression"] = (ESNumber)config.config_para.compression;
        dict["ESOpenFolder"] = (ESNumber)config.config_para.open_img_folder;
        dict["ESQualityPreview"] = (ESNumber)config.config_para.quality_preview;
        dict["WindowPositionX"] = (ESNumber)config.config_para.WindowPositionX;
        dict["WindowPositionY"] = (ESNumber)config.config_para.WindowPositionY;
        dict["WindowWidth"] = (ESNumber)config.config_para.WindowWidth;
        dict["WindowHeight"] = (ESNumber)config.config_para.WindowHeight;
        ES_CMN_FUNCS::JSON::DictionaryToJSONFile(dict, common_settings_file);
    }
    catch (...) {
        DeleteFile((this->SettingsFilePath + "CommonSettings.SF2").c_str());
    }
}
void LastUsedSettings::DeleteCommonSettingsFile()
{
    std::string common_settings_file = this->SettingsFilePath.c_str();
    common_settings_file = common_settings_file + "CommonSettings.SF2";
    try {
        DeleteFile(common_settings_file.c_str());
    }
    catch (...) {
        throw;
    }
}
bool LastUsedSettings::CreateSettingsFile(std::string model_id, const SCANPARA device_data)
{
    std::string model_id_folder = this->SettingsFilePath.c_str();
    model_id_folder = model_id_folder + model_id;
    std::string user_settings_file = model_id_folder + "/UserSettings.SF2";
#ifdef NO_QTMODE
    std::string dir1 = std::getenv("HOME");
#else
    std::string dir1((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
#endif
#ifdef AKBMODE
    std::string strDst = "/.";
    strDst = strDst + DRIVER_NAME;
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, (strDst + "/").c_str());
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1,"/.epsonscan2/");
#endif
    if(!(bool)ES_CMN_FUNCS::PATH::ES_IsExistFile(dir1)){
        ES_CMN_FUNCS::PATH::ES_MakeFolder(dir1);
    }
    if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(this->SettingsFilePath) == FALSE)
    {
        ES_CMN_FUNCS::PATH::ES_MakeFolder(this->SettingsFilePath);
    }
    bool result = (bool)ES_CMN_FUNCS::PATH::ES_IsExistFile(model_id_folder);
    if ( !result ) {
        result = ES_CMN_FUNCS::PATH::ES_MakeFolder(model_id_folder);
        if ( !result ) {
            return false;
        }
    }
    result =ES_CMN_FUNCS::PATH::ES_IsExistFile(user_settings_file);
    if ( !result ) {
       std::ofstream(user_settings_file.c_str());
       std::fstream SettingFile(user_settings_file.c_str());
       if (SettingFile.fail())
       {
           return false;
       }
    }
    this->CreateSettingsDict(user_settings_file, device_data);
    return true;
}
void LastUsedSettings::CreateSettingsDict(std::string user_settngs_file, const SCANPARA device_data)
{
    ESDictionary dict;
    ESDictionary preset;
    ESDictionary devnum;
    dict["FunctionalUnit"] = (ESNumber)device_data.FunctionalUnit.select;
    dict["FunctionalUnit_Auto"] = (ESNumber)device_data.FunctionalUnit_Auto;
    dict["ColorType"] = (ESNumber)device_data.ColorType.select;
    dict["AutoColorPixelType"] = (ESNumber)device_data.AutoColorPixelType.select;
    dict["AutoColorPixelLevel"] = (ESNumber)device_data.AutoColorPixelLevel.select;
    dict["Resolution"] = (ESNumber)device_data.Resolution.select;
    dict["ImageFormat"] = (ESNumber)device_data.ImageFormatSettings.ImageFormat.select;
    dict["Gamma"] = (ESNumber)device_data.Gamma.select;
    dict["ScanAreaWidth"] = (ESNumber)device_data.ScanArea.ScanAreaWidth.select;
    dict["ScanAreaHeight"] = (ESNumber)device_data.ScanArea.ScanAreaHeight.select;
    dict["ScanAreaOffsetX"] = (ESNumber)device_data.ScanArea.ScanAreaOffsetX.select;
    dict["ScanAreaOffsetY"] = (ESNumber)device_data.ScanArea.ScanAreaOffsetY.select;
    dict["FixedDocumentSize"] = (ESNumber)device_data.ScanArea.FixedSize;
    int temp_num = device_data.ScanArea.UserDefine_Width * 100;
    dict["UserScanAreaWidth"] = (ESNumber)temp_num;
    temp_num = device_data.ScanArea.UserDefine_Length * 100;
    dict["UserScanAreaHeight"] = (ESNumber)temp_num;
    dict["DropoutColor"] = (ESNumber)device_data.DropoutColor.select;
    dict["Orientation"] = (ESNumber)device_data.Orientation.select;
    dict["MultiTiffEnabled"] = (ESNumber)device_data.ImageFormatSettings.MultiTiffEnabled.select;
    dict["OFDEnabled"] = (ESNumber)device_data.ImageFormatSettings.OFDEnabled.select;
    dict["MultiTiffCompression"] = (ESNumber)device_data.ImageFormatSettings.TiffCompression.select;
    dict["Contrast"] = (ESNumber)device_data.Contrast.select;
    dict["Brightness"] = (ESNumber)device_data.Brightness.select;
    dict["Threshold"] = (ESNumber)device_data.Threshold.select;
    dict["JpegQuality"] = (ESNumber)device_data.ImageFormatSettings.JpegQuality.select;
    dict["JpegQualityForJpeg"] = (ESNumber)device_data.ImageFormatSettings.JpegQuality_forJPEG;
    dict["JpegQualityForPdf"] = (ESNumber)device_data.ImageFormatSettings.JpegQuality_forPDF;
    dict["jpegProgressive"] = (ESNumber)device_data.ImageFormatSettings.JpegProgressive.select;
    dict["DuplexType"] = (ESNumber)device_data.DuplexType.select;
    dict["PagesTobeScanned"] = (ESNumber)device_data.PagesTobeScanned.select;
    dict["DoubleFeedDetectionLevel"] = (ESNumber)device_data.DoubleFeedDetectionValue.DoubleFeedDetectionLevel.select;
    dict["DoubleFeedDetection"] = (ESNumber)device_data.DoubleFeedDetectionValue.DoubleFeedDetection.select;
    dict["DoubleFeedDetectionAreaMin"] = (ESNumber)device_data.DoubleFeedDetectionValue.DoubleFeedDetectionAreaMin.select;
    dict["DoubleFeedDetectionAreaLength"] = (ESNumber)device_data.DoubleFeedDetectionValue.DoubleFeedDetectionAreaLength.select;
    dict["BlankPageSkip"] = (ESNumber)device_data.BlankPageSkipKey.select;
    dict["BlankPageSkipLevel"] = (ESNumber)device_data.BlankPageSkipLevelKey.select;
    dict["BackgroundRemoval"] = (ESNumber)device_data.BackgroundRemoval.select;
    dict["PaperDeskew"] = (ESNumber)device_data.PaperDeskew.select;
    dict["AutoSize"] = (ESNumber)device_data.ScanArea.AutoSize.select;
    dict["PaperEndDetection"] = (ESNumber)device_data.ScanArea.PaperEndDetection.select;
    dict["PaperEndDetectionMemory"] = (ESNumber)device_data.ScanArea.PaperEndDetectionMemory;
    dict["TransferCompression"] = (ESNumber)device_data.TransferCompression.select;
    dict["AddPages"] = (ESNumber)device_data.Add_Pages;
    dict["FileNamePrefix"] = (ESString)device_data.Prefix;
    dict["FileNameOverWrite"] = (ESNumber)device_data.FileName_OverWrite;
    dict["FileNameCounter"] = (ESNumber)device_data.FileName_Counter;
    dict["PDFAllPages"] = (ESNumber)device_data.ImageFormatSettings.PDFImgFormatOption.AllPage;
    dict["PDFSelectPage"] = (ESNumber)device_data.ImageFormatSettings.PDFImgFormatOption.page;
    dict["UserDefinePath"] = (ESString)device_data.UserDefinePath;
    dict["Folder"] = (ESNumber)device_data.Folder;
    dict["ImageOption"] = (ESNumber)device_data.ImageOption;
    dict["DNShow_PlasticCard_dialog"] = (ESNumber)device_data.DNShow_PlasticCard_dialog;
    dict["DNShow_LongPaperWarning_dialog"] = (ESNumber)device_data.DNShow_LongPaperWarning_dialog;
    dict["OverDurationAlert"] = (ESNumber)device_data.OverDurationAlert;
    dict["NearDurationAlert"] = (ESNumber)device_data.NearDurationAlert;
    dict["AFMMode"] = (ESNumber)device_data.AutomaticFeedingMode.select;
    dict["AFMTimeout"] = (ESNumber)device_data.AFMTimeout.select;
    dict["BackgroundColor"] = (ESNumber)device_data.BackgroundColor.select;
    dict["textEnhance"] = (ESNumber)device_data.textEnhance.select;
    dict["textEnhanceNoiseReductionLevel"] = (ESNumber)device_data.textEnhanceNoiseReductionLevel.select;
    dict["textEnhanceSensitivity"] = (ESNumber)device_data.textEnhanceSensitivity.select;
    dict["textEnhancePaperCreaseReduction"] = (ESNumber)device_data.textEnhancePaperCreaseReduction.select;
    dict["thresholdAdjustment"] = (ESNumber)device_data.thresholdAdjustment.select;
    dict["RemovePunchHole"] = (ESNumber)device_data.RemovePunchHoles.select;
    dict["DeficiencyCorrection"] = (ESNumber)device_data.DeficiencyCorrection.select;
    dict["documentType"] = (ESNumber)device_data.documentType.select;
    dict["focusPosition"] = (ESNumber)device_data.focusPosition.select;
    dict["AutoCroppingInscribed"] = (ESNumber)device_data.AutoCroppingInscribed.select;
    dict["continuousAutoFeedingMode"] = (ESNumber)device_data.use_continuousAutoFeedingMode;
    devnum["0"] = dict;
    preset["Preset"] = devnum;
    ES_CMN_FUNCS::JSON::DictionaryToJSONFile(preset, user_settngs_file);
}
bool LastUsedSettings::ReadSettingsFile(std::string model_id, SCANPARA* device_data)
{
    std::string user_settings_file = this->SettingsFilePath.c_str();
    user_settings_file = user_settings_file + model_id + "/UserSettings.SF2";
    const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFolder(user_settings_file);
    if ( !result ) {
        device_data->ImageFormatSettings.OFDEnabled.select = 0;
        return false;
    }
    this->SetDeviceData(user_settings_file, device_data);
    return true;
}
bool LastUsedSettings::ReadCmdSettingsFile(std::string settings_file_path, SCANPARA* device_data)
{
    const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFolder(settings_file_path);
    if ( !result ) {
        return false;
    }
    this->SetDeviceData(settings_file_path, device_data);
    return true;
}
#include "ESAnyCastUtils.h"
void LastUsedSettings::SetDeviceData(std::string settings_file_path, SCANPARA* device_data)
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
        device_data->ImageFormatSettings.OFDEnabled.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"OFDEnabled",ESNumber,0);
        device_data->ImageFormatSettings.TiffCompression.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"MultiTiffCompression",ESNumber,TiffCompressionNone);
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
    #ifdef NO_QTMODE
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
        device_data->textEnhance.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"textEnhance",ESNumber,TextEnhanceLevelNone);
        device_data->textEnhanceNoiseReductionLevel.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"textEnhanceNoiseReductionLevel",ESNumber,1);
        device_data->textEnhanceSensitivity.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"textEnhanceSensitivity",ESNumber,0);
        device_data->textEnhancePaperCreaseReduction.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"textEnhancePaperCreaseReduction",ESNumber,false);
        device_data->thresholdAdjustment.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"thresholdAdjustment",ESNumber,0);
        device_data->use_continuousAutoFeedingMode = SAFE_ANY_VALUE_FROM_DICT(devnum,"continuousAutoFeedingMode",ESNumber,false);
        device_data->RemovePunchHoles.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"RemovePunchHole",ESNumber,RemovePunchHoleNone);
        device_data->documentType.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"documentType",ESNumber,Reflective);
        device_data->focusPosition.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"focusPosition",ESNumber,0);
        device_data->DeficiencyCorrection.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"DeficiencyCorrection",ESNumber,0);
        device_data->AutoCroppingInscribed.select = SAFE_ANY_VALUE_FROM_DICT(devnum,"AutoCroppingInscribed",ESNumber,true);
    }
    catch (...) {
        DeleteFile(settings_file_path.c_str());
    }
}
