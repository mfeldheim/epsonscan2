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
//  Scanner.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Scanner.hpp"
#include "ModelInfo.hpp"
#include "Engine.hpp"
#include "Utility.hpp"
#include "Finder.hpp"
#include <iostream>
#include <ES2Command/ES2CommandAPI.h>
#include <ESJsonUtils.h>
namespace epsonscan {
Scanner::Scanner(const SDIDeviceInfo& devInfo, std::shared_ptr<ModelInfo> modelInfo)
{
 SDI_TRACE_LOG("Enter");
 modelInfo_ = modelInfo;
 devInfo_ = devInfo;
 engine_ = MakeEngine(GetComTypeForFirst(), devInfo);
 InitSecondEngine();
 currentEngine_ = engine_;
 SDI_TRACE_LOG("Leave");
}
ESCommandType Scanner::GetComTypeForFirst()
{
 ESNumber comTypeHRD = kPrvHRD_CommandType_ESCI2;
 modelInfo_->GetValue(kPrvHRD_CommandType, comTypeHRD);
 if (comTypeHRD != kPrvHRD_CommandType_ESCI2)
 {
   return kESCommandTypeESCI;
 }
 return kESCommandTypeESCI2;
}
ESCommandType Scanner::GetComTypeForSecond()
{
 ESNumber comTypeHRD = kPrvHRD_CommandType_ESCI2;
 modelInfo_->GetValue(kPrvHRD_CommandTypeFlatbedOption, comTypeHRD);
 if (comTypeHRD != kPrvHRD_CommandType_ESCI2)
 {
   return kESCommandTypeESCI;
 }
 return kESCommandTypeESCI2;
}
bool Scanner::Is2in1Supporetd()
{
 if (devInfo_.productID == 0)
 {
  return false;
 }
 ESNumber isSupported = 0;
 return modelInfo_->GetValue(kPrvHRD_FlatbedOption, isSupported) == true;
}
std::shared_ptr<Engine> Scanner::MakeEngine(ESCommandType comType, const SDIDeviceInfo& devInfo)
{
 ESString es_deviceInfo;
 auto engine = std::make_shared<Engine>(comType);
 ESDictionary deviceDict;
 char devName[50];
 ESString serialNumber;
 std::string deviceNameString(devInfo.displayName);
 if (deviceNameString.find(":") != std::string::npos)
 {
  std::vector<std::string> values;
  std::stringstream stream{deviceNameString};
  std::string buf;
  while (std::getline(stream, buf, ':')) {
   values.push_back(buf);
  }
  if (values.size() > 1)
  {
   serialNumber = values[1];
  }
 }
 if (devInfo.productID != 0)
 {
  if (devInfo.productID == 0x13C ||
      devInfo.productID == 0x13D ||
   devInfo.productID == 0x13A ||
   devInfo.productID == 0x13B ||
   devInfo.productID == 0x13E ||
   devInfo.productID == 0x13F ||
   devInfo.productID == 0x142 ||
   devInfo.productID == 0x14A)
  {
   deviceDict[ES_CNCT_KEY_TYPE] = (ESNumber)kESConnectionInterpreter;
   deviceDict[ES_CNCT_KEY_PID] = (ESNumber)devInfo.productID;
   deviceDict[ES_CNCT_KEY_VID] = (ESNumber)kEpsonUSBVID;
   deviceDict[ES_CNCT_KEY_INTERPRETER_NAME] = ESString("es2intif");
   deviceDict[ES_CNCT_KEY_SERIAL_NUMBER] = ESString(serialNumber);
  }
  else
  {
   deviceDict[ES_CNCT_KEY_TYPE] = (ESNumber)kESConnectionLocal;
   deviceDict[ES_CNCT_KEY_PID] = (ESNumber)devInfo.productID;
   deviceDict[ES_CNCT_KEY_VID] = (ESNumber)kEpsonUSBVID;
   deviceDict[ES_CNCT_KEY_SERIAL_NUMBER] = ESString(serialNumber);
  }
 }else{
  deviceDict[ES_CNCT_KEY_TYPE] = (ESNumber)kESConnectionNetworkIS;
  deviceDict[ES_CNCT_KEY_ADDRESS] = ESString(devInfo.ipAddress);
 }
 ESDictionary esDeviceDict;
 esDeviceDict[ES_CNCT_KEY_ROOT] = deviceDict;
 ES_CMN_FUNCS::JSON::DictionaryToJSON(esDeviceDict, es_deviceInfo);
 ES_Dump_Json(deviceDict, "deviceDict");
 if(engine.get()->InitWithDeviceInfoDict(es_deviceInfo.c_str()) == false)
 {
  SDI_TRACE_LOG("InitDevice fails");
 }
  if (engine)
 {
  engine.get()->SetCallBackReceiver(std::bind(&Scanner::EngineCallBackReceiver,
               this,
               std::placeholders::_1,
               std::placeholders::_2,
               std::placeholders::_3
               ));
 }
 return engine;
}
void Scanner::InitSecondEngine()
{
 if (Is2in1Supporetd() == false)
 {
  return;
 }
 Finder finder;
 finder.Start(true);
 finder.Stop();
 auto devices = finder.GetDevicesPointer();
 auto count = finder.GetDevicesCount();
 for (int i = 0; i < count; i++)
 {
  SDIDeviceInfo devInfo = devices[i];
  int j = 0;
  while(k2in1FlatbedOptionVID[j] != 0x0)
  {
   if(devInfo.productID == k2in1FlatbedOptionVID[j])
   {
    SDI_TRACE_LOG("Will create second engine");
    engineSecond_ = MakeEngine(GetComTypeForSecond(), devInfo);
    if (engineSecond_)
    {
     SDI_TRACE_LOG("second engine creates success");
    }
    break;
   }
   j++;
  }
 }
}
Scanner::~Scanner()
{
 SDI_TRACE_LOG("Scanner Destroy");
}
void Scanner::EngineCallBackReceiver(EngineEventType eventType, Image* image, SDIError error)
{
 if (callBack_)
 {
  if (eventType == kEngineEventTypeDisconnect)
  {
   SDI_TRACE_LOG("engine receive kEngineEventTypeDisconnect");
   isOpened_ = false;
  }
  if (eventType == kEngineEventTypeScanEnd)
  {
   SDI_TRACE_LOG("engine receive kEngineEventTypeScanEnd");
   if (error == kSDIErrorDataReceive ||
       error == kSDIErrorDataSend ||
     error == kSDIErrorInvalidResponse ||
    error == kSDIErrorDeviceFatalError ||
    error == kESErrorDeviceOpenError )
   {
    SDI_TRACE_LOG("communication error occurs");
    isOpened_ = false;
   }
  }
  callBack_(eventType, image, error);
 }
}
SDIError Scanner::Open()
{
 SDIError err;
 if (engine_) {
  err = engine_->Open();
  if(err != kSDIErrorNone){
   return err;
  }
 }
 if (engineSecond_) {
  err = engineSecond_->Open();
  if(err != kSDIErrorNone){
   return err;
  }
 }
 isOpened_ = true;
 UpdateModelInfoUsingScanner();
 if (Is2in1Mode())
 {
  supportedFunctionalUnit_ .insert(kESFunctionalUnitDocumentFeeder);
  supportedFunctionalUnit_ .insert(kESFunctionalUnitFlatbed);
 }else{
  engine_->GetAvailableValueForKey(kESFunctionalUnitType, supportedFunctionalUnit_);
 }
 return kSDIErrorNone;
}
SDIError Scanner::Close()
{
 SDIError err;
 if (engine_) {
  err = engine_->Close();
  if(err != kSDIErrorNone){
   return err;
  }
 }
 if (engineSecond_) {
  err = engineSecond_->Close();
  if(err != kSDIErrorNone){
   return err;
  }
 }
  if (engine_)
 {
  engine_.get()->SetCallBackReceiver(nullptr);
 }
 if (engineSecond_)
 {
  engineSecond_.get()->SetCallBackReceiver(nullptr);
 }
 isOpened_ = false;
 return kSDIErrorNone;
}
SDIError Scanner::Scan()
{
 if (isOpened_ == false)
 {
  return kSDIErrorDeviceNotOpened;
 }
 if (currentEngine_) {
   currentEngine_->ScanInBackground();
 }
 return kSDIErrorNone;
}
SDIError Scanner::StartJobInMode(ESJobMode eJobMode)
{
 if (isOpened_ == false)
 {
  return kSDIErrorDeviceNotOpened;
 }
 if (currentEngine_) {
   currentEngine_->StartJobInMode(eJobMode);
 }
 return kSDIErrorNone;
}
SDIError Scanner::StopJobInMode(ESJobMode eJobMode)
{
 if (isOpened_ == false)
 {
  return kSDIErrorDeviceNotOpened;
 }
 if (currentEngine_) {
   currentEngine_->StopJobInMode(eJobMode);
 }
 return kSDIErrorNone;
}
SDIError Scanner::Cancel()
{
 if (currentEngine_) {
  return currentEngine_->Cancel();
 }
 return kSDIErrorNone;
}
void Scanner::SetValueForKey(const ESString& strKey, const ESAny& anyValue)
{
 if (isOpened_ == false)
 {
  SDI_TRACE_LOG("scanner is disconnected");
  throw RuntimeError("scanner is disconnected", kSDIErrorDataReceive);
 }
 if (engineSecond_)
 {
  if (strKey == kESFunctionalUnitType)
  {
   ESNumber funcUnitLocal = kESFunctionalUnitFlatbed;
   if(SafeBoostAnyCast_Local(anyValue, funcUnitLocal))
   {
    if (engineSecond_ && funcUnitLocal == kESFunctionalUnitFlatbed)
    {
     currentEngine_ = engineSecond_;
    }else{
     currentEngine_ = engine_;
    }
   }
  }
 }
 if (currentEngine_) {
  currentEngine_->SetValueForKey(strKey, anyValue);
 }
}
void Scanner::SetValuesForKeysWithDictionary(const ESDictionary& dictionary)
{
 if (isOpened_ == false)
 {
  SDI_TRACE_LOG("scanner is disconnected");
  throw RuntimeError("scanner is disconnected", kSDIErrorDataReceive);
 }
 if (currentEngine_) {
  currentEngine_->SetValuesForKeysWithDictionary(dictionary);
 }
}
void Scanner::UpdateModelInfoUsingScanner()
{
 if (engine_ && modelInfo_)
 {
  ESDictionary bgLevelFront;
  GetValueForKey(kESDocumentFeederBGLevelFront, bgLevelFront);
  modelInfo_->SetBackGroundColorFront(bgLevelFront);
  ESDictionary bgLevelBack;
  GetValueForKey(kESDocumentFeederBGLevelBack, bgLevelBack);
  modelInfo_->SetBackGroundColorBack(bgLevelBack);
 }
}
}
