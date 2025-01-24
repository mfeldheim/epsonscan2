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
//  Emulator.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Emulator.h"
Emulator::Emulator(void)
{
 m_pcDelegate = NULL;
 m_bOpen = false;
 m_bScanning = false;
 m_bCancel = false;
 m_bAfmEnabled = false;
 m_bIsInterrupted = false;
 m_nErrorCodeNum = kESErrorNoError;
}
Emulator::~Emulator(void)
{
}
void Emulator::SetDelegate( IESScannerDelegate* pDelegate )
{
 m_pcDelegate = pDelegate;
}
ESErrorCode Emulator::SetConnection( ES_JSON_CPTR pszJSON )
{
 ES_LOG_TRACE_FUNC();
 ESDictionary dictConnect;
 ES_CMN_FUNCS::JSON::JSONtoDictionary(pszJSON,dictConnect);
 try{
  ESDictionary dictSetting = boost::any_cast<ESDictionary>(dictConnect[ES_CNCT_KEY_ROOT]);
  if(dictSetting.find(ES_STRING("modelID")) != dictSetting.end()){
   ESNumber nModelID = boost::any_cast<ESNumber>(dictSetting[ES_STRING("modelID")]);
   m_strModelName = (boost::format(ES_STRING("ES%04X")) % nModelID).str();
  }
 }catch(...){
 }
 ES_LOG_LEAVE_FUNC();
 return kESErrorNoError;
}
ESErrorCode Emulator::InitializeDummyInfo(ESString strFunctionalUnit){
 ESErrorCode eError = kESErrorNoError;
 BOOL bLoaded = FALSE;
 if(GetDummyModelInfoDir().empty() == FALSE){
  ESString strDummyInfo;
  ES_CMN_FUNCS::PATH::ES_CombinePath(strDummyInfo, GetDummyModelInfoDir(), strFunctionalUnit);
  if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(strDummyInfo)){
   ESDictionary dictAllCurrentValues;
   LoadDummyInfo(strDummyInfo, ES_STRING("AllCurrentValues.json") , dictAllCurrentValues);
   SetAllCurrentValues(dictAllCurrentValues);
   ESDictionary dictAllValues;
   LoadDummyInfo(strDummyInfo, ES_STRING("AllValues.json") , dictAllValues);
   SetAllValues(dictAllValues);
   ESDictionary dictAllAvailableValues;
   LoadDummyInfo(strDummyInfo, ES_STRING("AllAvailableValues.json") , dictAllAvailableValues);
   SetAllAvailableValues(dictAllAvailableValues);
   bLoaded = TRUE;
  }
 }
 if(bLoaded == FALSE){
  ESString strDBName = GetDummyDBPath();
  if(strDBName.empty() == FALSE){
   ESDictionary dictAllCurrentValues;
   LoadDummyInfoFromDB(strDBName ,strFunctionalUnit.c_str(), ES_STRING("AllCurrentValues.json") , dictAllCurrentValues);
   SetAllCurrentValues(dictAllCurrentValues);
   ESDictionary dictAllValues;
   LoadDummyInfoFromDB(strDBName ,strFunctionalUnit.c_str(), ES_STRING("AllValues.json") , dictAllValues);
   SetAllValues(dictAllValues);
   ESDictionary dictAllAvailableValues;
   LoadDummyInfoFromDB(strDBName ,strFunctionalUnit.c_str(), ES_STRING("AllAvailableValues.json") , dictAllAvailableValues);
   SetAllAvailableValues(dictAllAvailableValues);
   bLoaded = TRUE;
  }
 }
 if(bLoaded == FALSE){
  eError = kESErrorDeviceOpenError;
 }
 return eError;
}
ESErrorCode Emulator::DestroyInstance()
{
 delete this;
 return kESErrorNoError;
}
ESErrorCode Emulator::Open()
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode eError = kESErrorNoError;
 m_cEmulatorSettings.SetEmulatorControllerDir(GetEmulatorCtrlerDir());
 SetCurrentUnitType(GetFirstUnitType());
 eError = InitializeDummyInfo(GetFirstUnitType());
 if(eError == kESErrorNoError)
 {
  m_bOpen = true;
 }
 else
 {
  ES_Error_Log(this, ES_STRING("InitializeDummyInfo Error."));
  eError = kESErrorDeviceOpenError;
 }
 ES_LOG_LEAVE_FUNC();
 return eError;
}
ESErrorCode Emulator::Close()
{
 ES_LOG_TRACE_FUNC();
 m_bOpen = false;
 ES_LOG_LEAVE_FUNC();
 return kESErrorNoError;
}
bool Emulator::IsOpened() const
{
 return m_bOpen;
}
ESErrorCode Emulator::CaptureScanner()
{
 return kESErrorNoError;
}
ESErrorCode Emulator::ReleaseScanner()
{
 return kESErrorNoError;
}
ESErrorCode Emulator::Scan()
{
 ES_LOG_TRACE_FUNC();
 ES_LOG_LEAVE_FUNC();
 return kESErrorInvalidParameter;
}
void Emulator::DoScan(ESNumber nLoadingPaperNum, ESNumber& nPreviousPageNum)
{
 ES_LOG_TRACE_FUNC();
 BOOL bDuplex = IsDuplex();
 if (bDuplex)
 {
  nLoadingPaperNum = nLoadingPaperNum * 2;
  ESNumber nPPM = GetPagePerMinute();
  SetPagePerMinute(nPPM * 2);
 }
 ESNumber nTotalPageNum = nPreviousPageNum + nLoadingPaperNum;
 ESNumber nError = kESErrorNoError;
 int nPageNum = nPreviousPageNum;
 for (; nPageNum < nTotalPageNum; nPageNum++)
 {
  CESScannedImage* pImage = new CESScannedImage();
  InitScanImage(pImage,nPageNum +1);
  m_pcDelegate->ScannerWillScanToScannedImage(this,pImage);
  pImage->Open();
  nError = GetErrorCodeNum();
  if (GetScanCanceled()){
   m_pcDelegate->ScannerWillCancelScanning(this);
   m_pcDelegate->ScannerDidCancelScanning(this);
   ES_Info_Log(this, ES_STRING("Scan is Canceled -- ErrorCode : %d ."),GetErrorCodeNum());
   goto BAIL;
  }else if ( nError == kESErrorPaperJam || nError == kESErrorPaperDoubleFeed){
   if((nPageNum+1)%2 == 1){
    SetInterrupted(true);
    nTotalPageNum = pImage->GetSerialNumber();
    pImage->Abort();
    nPreviousPageNum = nTotalPageNum - 1;
    goto BAIL;
   }else{
    nError = kESErrorNoError;
   }
  }
  if ( nPageNum == nPreviousPageNum)
  {
   m_csImagePath = ES_STRING("Resources/DummyInfo/test.raw");
  }
  CESFile cFile;
  UInt32 un32ReadedLen = 0;
  if(ES_CMN_FUNCS::PATH::ES_IsExistFile(m_csImagePath ) && cFile.Open(m_csImagePath ))
  {
   while(!GetScanCanceled() && nError == kESErrorNoError)
   {
    ES_CMN_FUNCS::BUFFER::CESHeapBuffer cBuf;
    cFile.SeekToFileOffset(un32ReadedLen);
    UInt32 nReadDataLen = std::min<UInt32>(pImage->GetBytesPerRow() * 50, cFile.GetLength() - un32ReadedLen);
    INT nReaded = 0;
    if (pImage->GetImageFormat() == kESImageFormatJPEG)
    {
     nReaded = cFile.ReadDataOfLength(256*1024, cBuf);
    }
    else
    {
     nReaded = cFile.ReadDataOfLength(nReadDataLen, cBuf);
    }
    un32ReadedLen += nReaded;
    if(nReaded == 0){
     ES_Error_Log(this, ES_STRING("Read Data Length is 0."));
     break;
    }
    pImage->WriteData(cBuf);
    if(un32ReadedLen == cFile.GetLength()){
     ES_Error_Log(this, ES_STRING("un32ReadedLen [%d] == cFile.GetLength() [%d]."), un32ReadedLen, cFile.GetLength());
     break;
    }
   }
   cFile.CloseFile();
  }else{
   m_pcDelegate->ScannerDidEncounterDeviceCommunicationError(this,kESErrorDataReceiveFailure);
  }
  pImage->Close();
  m_pcDelegate->ScannerDidScanToScannedImage(this,pImage);
   pImage->DeleteInstance();
 }
 nPreviousPageNum = nTotalPageNum;
BAIL:
 ES_LOG_LEAVE_FUNC();
}
void Emulator::ScannerThread()
{
 ES_LOG_TRACE_FUNC();
 {
  m_ValueCritSec.Lock();
  m_bScanning = true;
  m_ValueCritSec.Unlock();
 }
 ESNumber nPrePageNum = 0;
 if (IsInterrupted())
 {
  SetInterrupted(false);
  nPrePageNum = GetPreviousPageNum();
  SetPreviousPageNum(0);
 }
 m_pcDelegate->ScannerWillBeginContinuousScanning(this);
 int nLoadingNum = 1;
 ESNumber nUnitType = GetFunctionalUnitNameTypeFromDict(m_dictScanParameter);
 if (nUnitType != kESFunctionalUnitDocumentFeeder)
 {
  nLoadingNum = 1;
 }else if(nLoadingNum == 0){
  SetErrorCodeNum(kESErrorPaperEmpty);
 }
 ESNumber nToBeScanned = GetScanParamForKey_Internal(kESPagesToBeScanned, (ESNumber)0);
 if (nToBeScanned > 0)
 {
  nLoadingNum = 1;
 }
 DoScan(nLoadingNum, nPrePageNum);
 m_pcDelegate->ScannerDidEndContinuousScanning(this);
 if (!IsInterrupted())
 {
  m_pcDelegate->ScannerDidCompleteScanningWithError(this,(ESErrorCode)GetErrorCodeNum());
 }
 else
 {
  m_pcDelegate->ScannerDidInterruptScanningWithError(this, (ESErrorCode)GetErrorCodeNum());
  ES_Info_Log(this, L"Scan is Interrupted -- ErrorCode : %d .",GetErrorCodeNum());
  SetPreviousPageNum(nPrePageNum);
 }
 {
  m_ValueCritSec.Lock();
  m_bScanning = false;
  m_ValueCritSec.Unlock();
 }
 SetScanCanceled(false);
 ES_LOG_LEAVE_FUNC();
}
void* Emulator::EnterScannerThread(void* vpContext)
{
 ES_LOG_TRACE_FUNC();
 if(vpContext)
 {
  Emulator* pcThis =(Emulator*) vpContext;
  pcThis->ScannerThread();
 }
 ES_LOG_LEAVE_FUNC();
 return (void*)NULL;
}
ESErrorCode Emulator::ScanInBackground()
{
 ES_LOG_TRACE_FUNC();
 if(GetEmulatorCtrlerDir().empty()){
  m_pcDelegate->ScannerDidCompleteScanningWithError(this,kESErrorCoverOpen);
  return kESErrorFileReadError;
 }
 pthread_create(&m_pScannerThread, NULL, &Emulator::EnterScannerThread, this);
 ES_LOG_LEAVE_FUNC();
 return kESErrorNoError;
}
ESErrorCode Emulator::Cancel()
{
 ES_LOG_TRACE_FUNC();
 SetScanCanceled(true);
 ES_LOG_LEAVE_FUNC();
 return kESErrorNoError;
}
ESErrorCode Emulator::Abort()
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESErrorCode eErr = kESErrorNoError;
 assert(!IsScanning());
 if (IsInterrupted())
 {
  SetInterrupted(false);
  m_pcDelegate->ScannerDidCompleteScanningWithError(this, kESErrorNoError);
 }
 ES_LOG_LEAVE_FUNC();
 return eErr;
}
bool Emulator::IsScanning() const
{
 ES_LOG_TRACE_FUNC();
 bool bRet =false;
 m_ValueCritSec.Lock();
 bRet = m_bScanning;
 m_ValueCritSec.Unlock();
 ES_LOG_LEAVE_FUNC();
 return bRet;
}
ESErrorCode Emulator::DoCleaning()
{
 return kESErrorNoError;
}
ESErrorCode Emulator::DoCalibration()
{
 return kESErrorNoError;
}
bool Emulator::IsInterrupted() const
{
 return m_bIsInterrupted;
}
bool Emulator::IsAfmEnabled() const
{
 return m_bAfmEnabled;
}
void* Emulator::EnterMSSThread(void* vpContext)
{
 ES_LOG_TRACE_FUNC();
 if(vpContext)
 {
  Emulator* pcThis =(Emulator*) vpContext;
  pcThis->MSSThread();
 }
 ES_LOG_LEAVE_FUNC();
 return (void*)NULL;
}
void Emulator::MSSThread()
{
 ES_LOG_TRACE_FUNC();
 while (IsAfmEnabled() && !IsInterrupted())
 {
  if (IsPaperLoaded())
  {
   while (GetLoadingPaperNum() > 0 )
   {
    m_pcDelegate->ScannerWillBeginContinuousScanning(this);
    ESNumber nPrePageNum = GetPreviousPageNum();
    DoScan(GetLoadingPaperNum(), nPrePageNum);
    SetPreviousPageNum(nPrePageNum);
    if (!IsInterrupted())
    {
     m_pcDelegate->ScannerDidEndContinuousScanning(this);
    }
    else
    {
     m_pcDelegate->ScannerDidInterruptScanningWithError(this, (ESErrorCode)GetErrorCodeNum());
     ES_Info_Log(this, ES_STRING("Scan is Interrupted -- ErrorCode : %d ."),GetErrorCodeNum());
     break;
    }
    if (!IsPaperLoaded())
    {
     break;
    }
   }
  }
  sleep(1);
 }
 ES_LOG_LEAVE_FUNC();
}
ESErrorCode Emulator::StartScanningInAutoFeedingMode()
{
 ES_LOG_TRACE_FUNC();
 if (IsInterrupted())
 {
  SetInterrupted(false);
 }
 pthread_create(&m_pMSSThread, NULL, &Emulator::EnterMSSThread, NULL);
 ES_LOG_LEAVE_FUNC();
 return kESErrorNoError;
}
ESErrorCode Emulator::StopScanningInAutoFeedingMode()
{
 return kESErrorNoError;
}
ESErrorCode Emulator::StartJobInMode( ESJobMode eJobMode )
{
 ESErrorCode eErr = kESErrorNoError;
 if (eJobMode == kESJobModeAFM)
 {
  eErr = StartScanningInAutoFeedingMode();
 }
 return eErr;
}
ESErrorCode Emulator::StopJobInMode( ESJobMode eJobMode )
{
 return kESErrorNoError;
}
ESErrorCode Emulator::DoAutoFocus( ESFloat* pfOutFocus )
{
 return kESErrorNoError;
}
ESErrorCode Emulator::SetPanelToPushScanReady( BOOL bPushScanReady )
{
 return kESErrorNoError;
}
ESErrorCode Emulator::Reset()
{
 return kESErrorNoError;
}
ESErrorCode Emulator::GetAllKeys( IESResultString* pstrResult )
{
 return kESErrorInvalidParameter;
}
ESErrorCode Emulator::GetDefaultValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 return kESErrorInvalidParameter;
}
ESAny Emulator::GetValue(ES_CHAR_CPTR pszKey, ESDictionary& dict)
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ES_Trace_Log2(__FUNCTION__, ES_STRING("GetValue [%s]"), pszKey);
 ESAny anyValue;
 if(dict.count(pszKey))
 {
  anyValue = dict[pszKey];
 }
 ES_LOG_LEAVE_FUNC();
 return anyValue;
}
ESErrorCode Emulator::GetValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode eErr = kESErrorNoError;
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 if (m_dictAllCurrentValues.size() == 0)
 {
  ES_Error_Log(this, ES_STRING("Key:%s  m_dictAllCurrentValues is Null."), pszKey);
 }
 ESAny any = GetValue(pszKey, m_dictAllCurrentValues);
 if(!any.empty())
 {
  ESDictionary dictRet;
  dictRet[pszKey] = any;
  ESString strJson;
  ES_CMN_FUNCS::JSON::DictionaryToJSON(dictRet,strJson);
  if(pstrResult){
   pstrResult->Set(strJson.c_str());
  }
 }
 ES_LOG_LEAVE_FUNC();
 return eErr;
}
ESErrorCode Emulator::SetValueForKey( ES_CHAR_CPTR pszKey, ES_JSON_CPTR pszJSON )
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESErrorCode eErr = kESErrorInvalidParameter;
 if (pszJSON)
 {
  ESDictionary dict;
  ES_CMN_FUNCS::JSON::JSONtoDictionary(pszJSON, dict);
  if (!dict.empty())
  {
   if (m_dictAllCurrentValues.count(pszKey))
   {
    m_dictAllCurrentValues[pszKey] = dict.at(pszKey);
    eErr = kESErrorNoError;
   }
  }
 }
 ESString strKey = pszKey;
 if (strKey.compare(kESFunctionalUnitType) == 0)
 {
  BOOL bChanged = IsChangedFunctionalUnit();
  if (bChanged)
  {
   SetCurrentUnitType(GetFunctionalUnitTypeFromDictionary());
   InitializeDummyInfo(GetCurrentUnitType());
  }
 }
 ES_LOG_LEAVE_FUNC();
 return eErr;
}
ESErrorCode Emulator::SetValuesWithJSON( ES_JSON_CPTR pszJSON )
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESErrorCode eRet = kESErrorInvalidParameter;
 if (pszJSON)
 {
  ESDictionary dict;
  ES_CMN_FUNCS::JSON::JSONtoDictionary(pszJSON, dict);
  if (!dict.empty())
  {
   m_dictScanParameter = dict;
   eRet = kESErrorNoError;
  }
 }
 ES_LOG_LEAVE_FUNC();
 return eRet;
}
ESErrorCode Emulator::GetAllValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode eErr = kESErrorNoError;
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESAny any = GetValue(pszKey, m_dictAllValues);
 if(!any.empty())
 {
  ESDictionary dictRet;
  dictRet[pszKey] = any;
  ESString strJson;
  ES_CMN_FUNCS::JSON::DictionaryToJSON(dictRet,strJson);
  if(pstrResult){
   pstrResult->Set(strJson.c_str());
  }
 }
 ES_LOG_LEAVE_FUNC();
 return eErr;
}
ESErrorCode Emulator::GetAllValues( IESResultString* pstrResult )
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESString strJson;
 ES_CMN_FUNCS::JSON::DictionaryToJSON(m_dictAllValues,strJson);
 if(pstrResult){
  pstrResult->Set(strJson.c_str());
  return kESErrorNoError;
 }
 ES_LOG_LEAVE_FUNC();
 return kESErrorInvalidParameter;
}
ESErrorCode Emulator::GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode eErr = kESErrorNoError;
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESAny any = GetValue(pszKey, m_dictAllAvailableValues);
 if(!any.empty())
 {
  ESDictionary dictRet;
  dictRet[pszKey] = any;
  ESString strJson;
  ES_CMN_FUNCS::JSON::DictionaryToJSON(dictRet,strJson);
  if(pstrResult){
   pstrResult->Set(strJson.c_str());
  }
 }
 ES_LOG_LEAVE_FUNC();
 return eErr;
}
ESErrorCode Emulator::GetAllAvailableValues( IESResultString* pstrResult )
{
 ES_LOG_TRACE_FUNC();
 CBlockCriticalSection cValueBlock(m_ValueCritSec);
 ESString strJson;
 ES_CMN_FUNCS::JSON::DictionaryToJSON(m_dictAllAvailableValues, strJson);
 if(pstrResult){
  pstrResult->Set(strJson.c_str());
  return kESErrorNoError;
 }
 ES_LOG_LEAVE_FUNC();
 return kESErrorInvalidParameter;
}
ESString Emulator::GetFunctionalUnitTypeFromDictionary()
{
 ES_LOG_TRACE_FUNC();
 ESString strUnitType;
 ESNumber nUnitType = GetFunctionalUnitNameTypeFromDict(m_dictAllCurrentValues);
 switch(nUnitType)
 {
 case kESFunctionalUnitFlatbed:
  strUnitType = ES_STRING("Flatbed/");
  break;
 case kESFunctionalUnitDocumentFeeder:
  strUnitType = ES_STRING("ADF/");
  break;
 case kESFunctionalUnitTransparent:
  strUnitType = ES_STRING("Transparent/");
  break;
 case kESFunctionalUnitTPUAreaGuide:
  strUnitType = ES_STRING("AreaGuide/");
  break;
 default:
  break;
 }
 ES_LOG_LEAVE_FUNC();
 return strUnitType;
}
ESString Emulator::GetFirstUnitType()
{
 ES_LOG_TRACE_FUNC();
 ESString strFirstUnitType;
 ESString strDummyInfoPath = GetDummyModelInfoDir();
 if(strDummyInfoPath.empty() == FALSE){
  if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(strDummyInfoPath+ES_STRING("Flatbed/")))
  {
   strFirstUnitType = ES_STRING("Flatbed/");
  }
  else if (ES_CMN_FUNCS::PATH::ES_IsExistFolder(strDummyInfoPath+ES_STRING("ADF/")))
  {
   strFirstUnitType = ES_STRING("ADF/");
  }
  else
  {
   ES_Error_Log(this, ES_STRING("FunctionalUnit is No Folder."));
  }
 }
 ES_LOG_LEAVE_FUNC();
 return strFirstUnitType;
}
BOOL Emulator::IsChangedFunctionalUnit()
{
 ES_LOG_TRACE_FUNC();
 BOOL bChanged = FALSE;
 ESString strUnitType = GetFunctionalUnitTypeFromDictionary();
 if (GetCurrentUnitType() != strUnitType)
 {
  bChanged = TRUE;
 }
 ES_LOG_LEAVE_FUNC();
 return bChanged;
}
BOOL Emulator::IsDuplex()
{
 ES_LOG_TRACE_FUNC();
 ES_LOG_LEAVE_FUNC();
 return GetScanParamForKey_Internal(kESDuplex, false);
}
ESNumber Emulator::GetFunctionalUnitNameTypeFromDict(ESDictionary& dict)
{
 ES_LOG_TRACE_FUNC();
 ESNumber nFunctionalUnitType = (ESNumber)kESFunctionalUnitFlatbed;
 nFunctionalUnitType = SAFE_ANY_VALUE_FROM_DICT( dict,kESFunctionalUnitType,ESNumber, nFunctionalUnitType);
 ES_LOG_LEAVE_FUNC();
 return nFunctionalUnitType;
}
ESString Emulator::GetDummyInfoFolderPath()
{
 ESString strDummyInfoDir;
 strDummyInfoDir = GetEmulatorCtrlerDir();
 if (ES_CMN_FUNCS::PATH::ES_IsExistFolder(strDummyInfoDir))
 {
  ES_CMN_FUNCS::PATH::ES_CombinePath(strDummyInfoDir, strDummyInfoDir, ES_STRING("DummyInfo"));
 }
 return strDummyInfoDir;
}
ESString Emulator::GetDummyModelInfoDir()
{
 if(GetDummyInfoFolderPath().empty()){
  return ES_STRING("");
 }
 ESString strDummyInfoDir;
 ES_CMN_FUNCS::PATH::ES_CombinePath(strDummyInfoDir, GetDummyInfoFolderPath(), GetModelName());
 ES_CMN_FUNCS::PATH::ES_AddBackYen(strDummyInfoDir);
 if(!ES_CMN_FUNCS::PATH::ES_IsExistFolder(strDummyInfoDir)){
  return ES_STRING("");
 }
 return strDummyInfoDir;
}
ESString Emulator::GetDummyDBPath(){
  ESString strModelInfo = GetModelInfoPath();
  ESString strModelName = GetModelName();
  ESString strPath;
  ES_CMN_FUNCS::PATH::ES_CombinePath(strPath,strModelInfo,strModelName);
  ESString strDBName = strPath + ES_STRING("/") + strModelName+ ES_STRING("_HW.db");
  if(ES_CMN_FUNCS::PATH::ES_IsExistFile(strDBName)){
   return strDBName;
  }
  return ES_STRING("");
}
ESString Emulator::GetEmulatorCtrlerDir()
{
 ES_LOG_TRACE_FUNC();
 ESString strCtrlerDir ;
 if(m_strCtrlerDirCache.empty() == FALSE){
  return m_strCtrlerDirCache;
 }
 m_strCtrlerDirCache = ES_STRING("Resources");
 ES_LOG_LEAVE_FUNC();
 return m_strCtrlerDirCache;
}
ESString Emulator::GetModelInfoPath()
{
 ES_LOG_TRACE_FUNC();
 ESString strModelInfoPath;
 ESString strTempDataPath ;
 ES_CMN_FUNCS::PATH::ES_GetModuleFolder(NULL, strTempDataPath);
 strTempDataPath += ES_STRING("/Resources/Models/");
 if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(strTempDataPath)){
  return strTempDataPath;
 }
 BOOL bRet = FALSE;
 if (bRet)
 {
  strModelInfoPath += ES_STRING("/Models/");
 }
 else
 {
 }
 ES_LOG_LEAVE_FUNC();
 return strModelInfoPath;
}
#ifdef WIN32
ESString Emulator::CreateImageWithImageCreator(CESScannedImage* pcImage)
{
 ES_LOG_TRACE_FUNC();
 ESString csImagePath;
 ESString csCmdParam = MakeImageCreateCommand(pcImage,csImagePath);
 if(!csImagePath.IsEmpty() && !csCmdParam.IsEmpty())
 {
  ES_Info_Log(this,ES_STRING("CallImageCreator[%s]"),csCmdParam.GetString());
  if (pcImage->GetImageFormat() == kESImageFormatJPEG)
  {
   csImagePath += ES_STRING(".jpeg");
  }
 }
 ESString strGammaJson;
 ES_CMN_FUNCS::PATH::ES_CombinePath(strGammaJson, GetEmulatorCtrlerDir(), ES_STRING("GammaTable.json"));
 DeleteFile(strGammaJson.c_str());
 ES_LOG_LEAVE_FUNC();
 return csImagePath;
}
ESString Emulator::MakeImageCreateCommand(CESScannedImage* pImage, ESString& csImagePath)
{
 ES_LOG_TRACE_FUNC();
 ESString csCmdParam;
 csCmdParam.AppendFormat(ES_STRING(" /MODEL %s") , m_strModelName.c_str());
 ESNumber nPixelX = 0;
 ESNumber nPixelY = 0;
 BOOL bArea = FALSE;
 ESNumber nOffsetX = 0;
 ESNumber nOffsetY = 0;
 GetScanSizeInPixel(nPixelX, nPixelY, bArea, nOffsetX, nOffsetY);
 csCmdParam.AppendFormat(ES_STRING(" /PIXEL %d %d") , nPixelX, nPixelY);
 ESNumber nBitsPerSample = 0;
 ESNumber nSamplesPerPixel = 0;
 GetColorSample(nBitsPerSample, nSamplesPerPixel);
 ESNumber nBytesPerRow = nPixelX * nSamplesPerPixel;
 csCmdParam.AppendFormat(ES_STRING(" /SAMPLE %d") , nSamplesPerPixel);
 csCmdParam.AppendFormat(ES_STRING(" /BITS %d") , nBitsPerSample);
 csCmdParam.AppendFormat(ES_STRING(" /PAGE %d") , pImage->GetSerialNumber());
 csCmdParam.AppendFormat(ES_STRING(" /PAPER %d") , pImage->GetPaperSerialNumber());
 csCmdParam.AppendFormat(ES_STRING(" /SIDE %d") , pImage->GetSurfaceType());
 csCmdParam.AppendFormat(ES_STRING(" /FORM %d") , pImage->GetImageFormat());
 csCmdParam.AppendFormat(ES_STRING(" /UPSIDE_DOWN %d") , (BOOL)pImage->IsUpsideDown());
 csImagePath.Format(ES_STRING("%sImageTest_Page%d"), GetEmulatorCtrlerDir().c_str(), pImage->GetPaperSerialNumber());
 csCmdParam.AppendFormat(ES_STRING(" /FNAME \"%s\"") , csImagePath);
 ESNumber nResX = 0;
 ESNumber nResY = 0;
 GetResolution(nResX, nResY);
 csCmdParam.AppendFormat(ES_STRING(" /RESOLUTION %d %d") , nResX, nResY);
 ESNumber nImageType = GetLoadImageType();
 csCmdParam.AppendFormat(ES_STRING(" /IMGTYPE %d") , nImageType);
 if (nImageType == eLoadImgTypeDocument)
 {
  ST_ES_SIZE_F stfMaxScanSize = GetMaxScanSizeInPixel((ESFloat)nResX, (ESFloat)nResY);
  int nBackOffset = GetBackOffset((ESFloat)nResX, stfMaxScanSize.cx);
  if(!bArea)
  {
   nOffsetX = SetOffsetXInPixel(nPixelX, nBackOffset, stfMaxScanSize.cx);
  }
  else
  {
   nOffsetX += nBackOffset;
  }
 }
 csCmdParam.AppendFormat(ES_STRING(" /OFFSET %d %d") , nOffsetX, nOffsetY);
 ESNumber nThreshold = GetScanParamForKey_Internal(kESThreshold, 0);
 csCmdParam.AppendFormat(ES_STRING(" /THRESHOLD %d") , nThreshold);
 ESDictionary dictGammaTbl;
 if (pImage->GetBitsPerPixel() == 24 || pImage->GetBitsPerPixel() == 48)
 {
  dictGammaTbl[kESGammaTableRedChannelKey] = GetScanParamForKey_Internal(kESGammaTableRed ,ESIndexArray());
  dictGammaTbl[kESGammaTableGreenChannelKey] = GetScanParamForKey_Internal(kESGammaTableGreen ,ESIndexArray());
  dictGammaTbl[kESGammaTableBlueChannelKey] = GetScanParamForKey_Internal(kESGammaTableBlue ,ESIndexArray());
 }
 else
 {
  dictGammaTbl[kESGammaTableMonoChannelKey] = GetScanParamForKey_Internal(kESGammaTableMono,ESIndexArray());
 }
 ESString strGammaJson;
 ES_CMN_FUNCS::PATH::ES_CombinePath(strGammaJson, GetEmulatorCtrlerDir(), ES_STRING("GammaTable.json"));
 ES_CMN_FUNCS::JSON::DictionaryToJSONFile(dictGammaTbl,strGammaJson);
 csCmdParam.AppendFormat(ES_STRING(" /GAMMA_TBL \"%s\" ") , strGammaJson.c_str());
 csCmdParam.AppendFormat(ES_STRING(" /DRAW_TEXT %d") , m_cVirtualSettings.IsIndicatedPageNumber());
 return csCmdParam;
 ES_LOG_LEAVE_FUNC();
}
#endif
void Emulator::LoadDummyInfo(ESString strDummyInfoPath, LPCTSTR strJsonFileName, ESDictionary& dictDummyInfo)
{
 ES_LOG_TRACE_FUNC();
 strDummyInfoPath += strJsonFileName;
 ES_CMN_FUNCS::JSON::JSONFiletoDictionary(strDummyInfoPath,dictDummyInfo);
 ES_LOG_LEAVE_FUNC();
}
void Emulator::LoadDummyInfoFromDB(ESString strDummyInfoDBPath,LPCTSTR strFunctionalUnitName,LPCTSTR strJsonName,ESDictionary& dictDummyInfo){
 ES_LOG_TRACE_FUNC();
 ESString strPath = strFunctionalUnitName;
 strPath= strPath + strJsonName;
 ES_LOG_LEAVE_FUNC();
}
void Emulator::InitScanImage(CESScannedImage* pImage,INT nPageNumber)
{
 ES_LOG_TRACE_FUNC();
 ESString strPath;
 ES_CMN_FUNCS::PATH::ES_GetSystemTempDir(strPath);
 ESNumber nPixelX = 0;
 ESNumber nPixelY = 0;
 BOOL bArea = FALSE;
 ESNumber nOffsetX = 0;
 ESNumber nOffsetY = 0;
 GetScanSizeInPixel(nPixelX, nPixelY, bArea, nOffsetX, nOffsetY);
 ESNumber nBitsPerSample = 0;
 ESNumber nSamplesPerPixel = 0;
 GetColorSample(nBitsPerSample, nSamplesPerPixel);
 ESNumber nBytesPerRow = nPixelX * nSamplesPerPixel;
 if (nBitsPerSample == 1)
 {
  nBytesPerRow = (nBytesPerRow+7)/8;
 }
 if(pImage->Init(nPixelX,nPixelY, nBytesPerRow, nBitsPerSample, nSamplesPerPixel, strPath)== kESErrorNoError)
 {
  pImage->SetSerialNumber(nPageNumber);
  if (IsDuplex())
  {
   if ((nPageNumber)%2 == 0)
   {
    pImage->SetSurfaceType(kESSurfaceTypeBackSide);
   }
   pImage->SetPaperSerialNumber((nPageNumber +1)/2);
  }
  else
  {
   pImage->SetPaperSerialNumber(nPageNumber);
  }
  ESAny anyImgFormat = GetValue(kESImageFormat, m_dictScanParameter);
  const ESNumber* pnImgFormat = NULL;
  pnImgFormat = SAFE_ANY_DATA_CPTR(anyImgFormat, ESNumber);
  if (pnImgFormat)
  {
   pImage->SetImageFormat((ESImageFormat)*pnImgFormat);
  }
 }
 ESNumber nDuplexType = GetCurrentValueForKey_Internal(kESDuplexType, (ESNumber)kESDuplexType1Pass);
 if (nDuplexType == (ESNumber)kESDuplexType2Pass && pImage->GetSurfaceType() == kESSurfaceTypeBackSide)
 {
  pImage->SetUpsideDown(true);
 }
 ES_LOG_LEAVE_FUNC();
}
void Emulator::GetScanSizeInPixel(ESNumber& nPixelX, ESNumber& nPixelY,BOOL& bArea ,ESNumber& nOffsetX,ESNumber& nOffsetY)
{
 ES_LOG_TRACE_FUNC();
 bArea = FALSE;
 ESAny anySizeInPixel = GetValue(kESScanSizeInPixel, m_dictScanParameter);
 const ST_ES_SIZE_UN32* pnPixel = NULL;
 pnPixel = SAFE_ANY_DATA_CPTR(anySizeInPixel, ST_ES_SIZE_UN32);
 if (pnPixel)
 {
  nPixelX = pnPixel->cx;
  nPixelY = pnPixel->cy;
 }
 else
 {
  ESAny anySizeInch = GetValue(kESScanSize, m_dictScanParameter);
  const ST_ES_SIZE_F* pnInch = NULL;
  pnInch = SAFE_ANY_DATA_CPTR(anySizeInch, ST_ES_SIZE_F);
  if (pnInch)
  {
   ESNumber nResX = 0;
   ESNumber nResY = 0;
   GetResolution(nResX, nResY);
   nPixelX = (ESNumber)((pnInch->cx) * nResX);
   nPixelY = (ESNumber)((pnInch->cy) * nResY);
  }
  else
  {
   ESAny anyAreaInPixel = GetValue(kESScanAreaInPixel, m_dictScanParameter);
   const ST_ES_RECT_UN32* pnArea = NULL;
   pnArea = SAFE_ANY_DATA_CPTR(anyAreaInPixel, ST_ES_RECT_UN32);
   if (pnArea)
   {
    nPixelX = pnArea->right - pnArea->left;
    nPixelY = pnArea->bottom- pnArea->top;
    nOffsetX = pnArea->left;
    nOffsetY = pnArea->top;
    bArea = TRUE;
   }
  }
 }
 if (nPixelX == 0)
 {
  nPixelX = 2482;
 }
 if (nPixelY == 0)
 {
  nPixelY = 3507;
 }
 ES_LOG_LEAVE_FUNC();
}
void Emulator::GetResolution(ESNumber& nResX, ESNumber& nResY)
{
 ES_LOG_TRACE_FUNC();
 nResX = GetScanParamForKey_Internal(kESXResolution, nResX);
 nResY = GetScanParamForKey_Internal(kESYResolution, nResY);
 ES_LOG_LEAVE_FUNC();
}
void Emulator::GetColorSample(ESNumber& nBitsPerSample, ESNumber& nSamplesPerPixel)
{
 ES_LOG_TRACE_FUNC();
 ESNumber nColor = GetScanParamForKey_Internal(kESColorFormat, (ESNumber)kESColorFormatRGB24);
 switch (nColor)
 {
 case kESColorFormatRGB48:
 case kESColorFormatRGB24:
  nSamplesPerPixel = 3;
  break;
 case kESColorFormatMono16:
 case kESColorFormatMonoDropR16:
 case kESColorFormatMonoDropG16:
 case kESColorFormatMonoDropB16:
 case kESColorFormatMono8:
 case kESColorFormatMonoDropR8:
 case kESColorFormatMonoDropG8:
 case kESColorFormatMonoDropB8:
 case kESColorFormatMono1:
 case kESColorFormatMonoDropR1:
 case kESColorFormatMonoDropG1:
 case kESColorFormatMonoDropB1:
  nSamplesPerPixel = 1;
  break;
 default:
  nSamplesPerPixel = 0;
  break;
 }
 switch (nColor)
 {
 case kESColorFormatRGB48:
 case kESColorFormatMono16:
 case kESColorFormatMonoDropR16:
 case kESColorFormatMonoDropG16:
 case kESColorFormatMonoDropB16:
  nBitsPerSample = 16;
  break;
 case kESColorFormatRGB24:
 case kESColorFormatMono8:
 case kESColorFormatMonoDropR8:
 case kESColorFormatMonoDropG8:
 case kESColorFormatMonoDropB8:
  nBitsPerSample = 8;
  break;
 case kESColorFormatMono1:
 case kESColorFormatMonoDropR1:
 case kESColorFormatMonoDropG1:
 case kESColorFormatMonoDropB1:
  nBitsPerSample = 1;
  break;
 default:
  nBitsPerSample = 0;
  break;
 }
 ES_LOG_LEAVE_FUNC();
}
#include "../Include/ES2Command/ES2CommandAPI.h"
extern "C" ESSCANNER_API ESErrorCode ESCreateScanner( ESCommandType eCommandType, IESScanner** ppScanner )
{
 ES_LOG_TRACE_FUNC();
 Emulator* pScanner = NULL;
 if (ppScanner == NULL ){
  return kESErrorInvalidParameter;
 }
 *ppScanner = NULL;
 try {
  pScanner = new Emulator();
 } catch( std::bad_alloc ){
  return kESErrorMemoryError;
 } catch( std::invalid_argument ){
  return kESErrorFatalError;
 } catch(...){
  return kESErrorFatalError;
 }
 ESErrorCode ret = pScanner->Initialize();
 if ( ret == kESErrorNoError ){
  *ppScanner = dynamic_cast< IESScanner* >( pScanner );
 }
 ES_LOG_LEAVE_FUNC();
 return ret;
}
