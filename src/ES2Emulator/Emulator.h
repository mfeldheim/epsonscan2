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
//  Emulator.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "stdafx.h"
#include <es2CommnoType.h>
#include <ESResultString.h>
#include <pthread.h>
#include "ESCommandProperties.h"
#include "ESPropertyKeys.h"
#include "IESScanner.h"
#include "utils/CritSec.h"
#include "Image/ESScannedImage.h"
#include "EmulatorSettings.h"
typedef ES_CHAR* ES_JSON_PTR;
typedef const ES_CHAR* ES_JSON_CPTR;
typedef enum
{
 eLoadImgTypeDocument = 0,
 eLoadImgTypePhotoThumbnail,
 eLoadImgTypeNegaFilm,
 eLoadImgTypePosiFilm,
}VIRTUAL_ENUM_LOAD_IMAGE_TYPE;
class Emulator;
class Emulator : public IESScanner
{
public:
 Emulator(void);
 ~Emulator(void);
 pthread_t GetVirtualUIThread(){
  return m_pThread;
 }
 ESErrorCode Initialize()
 {
  return kESErrorNoError;
 }
 void SetScanCanceled(bool bCancel){
  m_ValueCritSec.Lock();
  m_bCancel = bCancel;
  m_ValueCritSec.Unlock();
 }
 bool GetScanCanceled(){
  return m_bCancel;
 }
 bool GetScanning(){
  return m_bScanning;
 }
 ESString GetModelName(){
  return m_strModelName;
 }
 void SetInterrupted(bool bInterrupted){
  m_ValueCritSec.Lock();
  m_bIsInterrupted = bInterrupted;
  m_ValueCritSec.Unlock();
 }
 bool IsPaperLoaded(){
  return m_bIsPaperLoaded;
 }
 void SetCurrentUnitType(ESString strCurUnitType){
  m_strCurUnitType = strCurUnitType;
 }
 ESString GetCurrentUnitType(){
  return m_strCurUnitType;
 }
 void SetAllCurrentValues(ESDictionary& dictAllCurrentValues){
  m_dictAllCurrentValues = dictAllCurrentValues;
 }
 void SetAllValues(ESDictionary& dictAllValues){
  m_dictAllValues = dictAllValues;
 }
 void SetAllAvailableValues(ESDictionary& dictAllAvailableValues){
  m_dictAllAvailableValues = dictAllAvailableValues;
 }
 int GetErrorCodeNum(){
  return m_nErrorCodeNum;
 }
 void SetErrorCodeNum(int nErrorCodeNum){
  m_ValueCritSec.Lock();
  m_nErrorCodeNum = nErrorCodeNum;
  m_ValueCritSec.Unlock();
 }
 int GetPagePerMinute(){
  return m_nPPM;
 }
 void SetPagePerMinute(int nPPM){
  m_nPPM = nPPM;
 }
 int GetLoadingPaperNum(){
  return m_nLoadingPaperNum;
 }
 void SetLoadingPaperNum(int nLoadingPapernum){
  m_ValueCritSec.Lock();
  m_nLoadingPaperNum = nLoadingPapernum;
  m_ValueCritSec.Unlock();
 }
 ESNumber GetPreviousPageNum(){
  return m_nPreviousPageNum;
 }
 void SetPreviousPageNum(ESNumber nPrePageNum){
  m_nPreviousPageNum = nPrePageNum;
 }
 template<typename T>
 T GetScanParamForKey_Internal(ES_CHAR_CPTR pszKey,T defaultValue)
 {
  ES_LOG_TRACE_FUNC();
  CBlockCriticalSection cValueBlock(m_ValueCritSec);
  return SAFE_ANY_VALUE_FROM_DICT(m_dictScanParameter,pszKey,T,defaultValue);
 }
 template<typename T>
 T GetCurrentValueForKey_Internal(ES_CHAR_CPTR pszKey,T defaultValue)
 {
  ES_LOG_TRACE_FUNC();
  CBlockCriticalSection cValueBlock(m_ValueCritSec);
  return SAFE_ANY_VALUE_FROM_DICT(m_dictAllCurrentValues,pszKey,T,defaultValue);
 }
 template<typename T>
 void SetCurrentValueForKey_Internal(ES_CHAR_CPTR pszKey,T Value)
 {
  ES_LOG_TRACE_FUNC();
  CBlockCriticalSection cValueBlock(m_ValueCritSec);
  m_dictAllCurrentValues[pszKey] = Value;
 }
 template<typename T>
 T GetAvailableValueForKey_Internal(ES_CHAR_CPTR pszKey,T defaultValue){
  ES_LOG_TRACE_FUNC();
  CBlockCriticalSection cValueBlock(m_ValueCritSec);
  return SAFE_ANY_VALUE_FROM_DICT(m_dictAllAvailableValues,pszKey,T,defaultValue);
 }
 template<typename T>
 T GetAllValueForKey_Internal(ES_CHAR_CPTR pszKey,T defaultValue){
  return SAFE_ANY_VALUE_FROM_DICT(m_dictAllValues,pszKey,T,defaultValue);
 }
 virtual void SetDelegate( IESScannerDelegate* pDelegate );
 virtual ESErrorCode SetConnection( ES_JSON_CPTR pszJSON );
 virtual ESErrorCode DestroyInstance();
 virtual ESErrorCode Open();
 virtual ESErrorCode Close();
 virtual bool IsOpened() const;
 virtual ESErrorCode CaptureScanner();
 virtual ESErrorCode ReleaseScanner();
 virtual ESErrorCode Scan();
 virtual ESErrorCode ScanInBackground();
 virtual ESErrorCode Cancel();
 virtual ESErrorCode Abort();
 virtual bool IsScanning() const;
 virtual ESErrorCode DoCleaning();
 virtual ESErrorCode DoCalibration();
 virtual bool IsInterrupted() const;
 virtual bool IsAfmEnabled() const;
 virtual ESErrorCode StartScanningInAutoFeedingMode();
 virtual ESErrorCode StopScanningInAutoFeedingMode();
 virtual ESErrorCode ScheduleAutoFeedingModeTimeout()
 {
  return kESErrorNoError;
 }
 virtual ESErrorCode StartJobInMode( ESJobMode eJobMode );
 virtual ESErrorCode StopJobInMode( ESJobMode eJobMode );
 virtual ESErrorCode DoAutoFocus( ESFloat* pfOutFocus );
 virtual ESErrorCode SetPanelToPushScanReady( BOOL bPushScanReady );
 virtual ESErrorCode Reset();
 virtual ESErrorCode GetAllKeys( IESResultString* pstrResult );
 virtual ESErrorCode GetDefaultValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult );
 ESAny GetValue(ES_CHAR_CPTR pszKey, ESDictionary& dict);
 virtual ESErrorCode GetValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult );
 virtual ESErrorCode SetValueForKey( ES_CHAR_CPTR pszKey, ES_JSON_CPTR pszJSON );
 virtual ESErrorCode SetValuesWithJSON( ES_JSON_CPTR pszJSON );
 virtual ESErrorCode GetAllValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult );
 virtual ESErrorCode GetAllValues( IESResultString* pstrResult );
 virtual ESErrorCode GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult );
 virtual ESErrorCode GetAllAvailableValues( IESResultString* pstrResult );
 BOOL IsDuplex();
 ESNumber GetFunctionalUnitNameTypeFromDict(ESDictionary& dict);
 ESString GetDummyInfoFolderPath();
 ESString GetDummyModelInfoDir();
private:
 pthread_t m_pThread;
 IESScannerDelegate* m_pcDelegate;
 bool m_bOpen;
 bool m_bScanning;
 bool m_bCancel;
 bool m_bAfmEnabled;
 bool m_bIsPaperLoaded;
 bool m_bIsInterrupted;
 EmulatorSettings m_cEmulatorSettings;
 CritSec m_ValueCritSec;
 ESString m_strModelName;
 pthread_t m_pScannerThread;
 pthread_t m_pcScanImageCreateThread;
 pthread_t m_pMSSThread;
 int m_nLoadingPaperNum;
 ESNumber m_nPreviousPageNum;
 int m_nErrorCodeNum;
 int m_nPPM;
 ESString m_strCtrlerDirCache;
 ESString m_strCmdModulePath;
 ESString m_strCurUnitType;
 ESString m_csImagePath;
 ESDictionary m_dictAllCurrentValues;
 ESDictionary m_dictAllValues;
 ESDictionary m_dictAllAvailableValues;
 ESDictionary m_dictScanParameter;
 void ScannerThread();
 static void* EnterScannerThread(void* vpContext);
 void MSSThread();
 static void* EnterMSSThread(void* vpContext);
 ESString GetFunctionalUnitTypeFromDictionary();
 ESString GetFirstUnitType();
 BOOL IsChangedFunctionalUnit();
 ESString GetDummyDBPath();
 void GetScanSizeInPixel(ESNumber& nPixelX, ESNumber& nPixelY,BOOL& bArea ,ESNumber& nOffsetX,ESNumber& nOffsetY);
 void GetResolution(ESNumber& nResX, ESNumber& nResY);
 void GetColorSample(ESNumber& nBitsPerSample, ESNumber& nSamplesPerPixel);
 ESString GetEmulatorCtrlerDir();
 ESString GetModelInfoPath();
 void InitScanImage(CESScannedImage* pcImage,INT nPageNumber);
 ESString CreateImageWithImageCreator(CESScannedImage* pcImage);
 ESString MakeImageCreateCommand(CESScannedImage* pcImage,ESString& csImagePath);
 void DoScan(ESNumber nLoadingPaperNum, ESNumber& nPreviousPageNum);
 void LoadDummyInfo(ESString strDummyInfoPath, LPCTSTR strJsonFileName, ESDictionary& dictDummyInfo);
 void LoadDummyInfoFromDB(ESString strDummyInfoDBPath,LPCTSTR strFunctionalUnitName,LPCTSTR strJsonName,ESDictionary& dictDummyInfo);
 ESErrorCode InitializeDummyInfo(ESString strFunctionalUnit);
};
