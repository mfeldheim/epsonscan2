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
//  ESScanner.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "CommonUtility/utils/ESJsonUtils.h"
#include "CommonUtility/utils/ESBuffer.h"
using namespace ES_CMN_FUNCS::BUFFER;
#include "ESScanner.h"
#include "ESScannerDefs.h"
#include "ESCI/ESCIScanner.h"
#include "ESCI2/ESCI2Scanner.h"
CESScanner* CESScanner::CreateInstance(ESCommandType eCommandType)
{
 switch ( eCommandType ) {
 case kESCommandTypeESCI:
  return new CESCIScanner;
 case kESCommandTypeESCI2:
  return new CESCI2Scanner;
 default:
  ES_LOG_INVALID_COMMAND_TYPE_PARAM();
  throw std::invalid_argument("Invalid Command Type");
 }
 return NULL;
}
void CESScanner::DestroyInstance()
{
 ES_LOG_TRACE_FUNC();
 try {
  delete this;
 } catch (...){
  ES_LOG_EXCEPTION_ERROR();
 }
}
CESScanner::CESScanner()
{
 PROPERTY_RW( kESWorkFolder, CESScanner, ESString, GetWorkFolder, ESString, SetWorkFolder );
 PROPERTY_R ( kESErrorStatus, CESScanner, ESNumber, GetErrorStatus );
 PROPERTY_R ( kESAuthentication, CESScanner, bool, IsAuthenticationSupported );
 PROPERTY_RW( kESAuthenticationEnabled, CESScanner, bool, IsAuthenticationEnabled, bool, SetAuthenticationEnabled );
 PROPERTY_RW( kESAuthUsername, CESScanner, ESString, GetAuthUserName, ESString, SetAuthUserName );
 PROPERTY_RW( kESAuthPassword, CESScanner, ESString, GetAuthPassword, ESString, SetAuthPassword );
 PROPERTY_RW( kESFunctionalUnitType, CESScanner, ESNumber, GetFunctionalUnitType, ESNumber, SetFunctionalUnitType );
 PROPERTY_RW( kESXResolution, CESScanner, ESNumber, GetXResolution, ESNumber, SetXResolution );
 PROPERTY_RW( kESYResolution, CESScanner, ESNumber, GetYResolution, ESNumber, SetYResolution );
 PROPERTY_R ( kESOpticalResolution, CESScanner, ESNumber, GetOpticalResolution );
 PROPERTY_R ( kESMaxScanSize, CESScanner, ST_ES_SIZE_F, GetMaxScanSize );
 PROPERTY_RW( kESScanArea, CESScanner, ST_ES_RECT_F, GetScanArea, ST_ES_RECT_F, SetScanArea );
 PROPERTY_RW( kESScanAreaInPixel, CESScanner, ST_ES_RECT_UN32, GetScanAreaInPixel, ST_ES_RECT_UN32, SetScanAreaInPixel );
 PROPERTY_RW( kESScanSize, CESScanner, ST_ES_SIZE_F, GetScanSize, ST_ES_SIZE_F, SetScanSize );
 PROPERTY_RW( kESScanSizeInPixel, CESScanner, ST_ES_SIZE_UN32, GetScanSizeInPixel, ST_ES_SIZE_UN32, SetScanSizeInPixel );
 PROPERTY_RW( kESXOffsetMargin, CESScanner, ESFloat, GetXOffsetMargin, ESFloat, SetXOffsetMargin );
 PROPERTY_RW( kESYOffsetMargin, CESScanner, ESFloat, GetYOffsetMargin, ESFloat, SetYOffsetMargin );
 PROPERTY_RW( kESColorFormat, CESScanner, ESNumber, GetColorFormat, ESNumber, SetColorFormat );
 PROPERTY_RW( kESColorMatrix, CESScanner, ESAny, GetColorMatrix, ESFloatArray, SetColorMatrix );
 PROPERTY_R ( kESBitsPerPixel, CESScanner, ESNumber, GetBitsPerPixel );
 PROPERTY_RW( kESGammaMode, CESScanner, ESNumber, GetGammaMode, ESNumber, SetGammaMode );
 PROPERTY_RW( kESGammaTableMono, CESScanner, ESAny, GetGammaTableMono, ESIndexArray, SetGammaTableMono );
 PROPERTY_RW( kESGammaTableRed, CESScanner, ESAny, GetGammaTableRed, ESIndexArray, SetGammaTableRed );
 PROPERTY_RW( kESGammaTableGreen, CESScanner, ESAny, GetGammaTableGreen, ESIndexArray, SetGammaTableGreen );
 PROPERTY_RW( kESGammaTableBlue, CESScanner, ESAny, GetGammaTableBlue, ESIndexArray, SetGammaTableBlue );
 PROPERTY_RW( kESThreshold, CESScanner, ESNumber, GetThreshold, ESNumber, SetThreshold );
 PROPERTY_RW( kESQuietMode, CESScanner, ESNumber, GetQuietMode, ESNumber, SetQuietMode );
 PROPERTY_RW( kESBufferSize, CESScanner, ESNumber, GetBufferSize, ESNumber, SetBufferSize );
 PROPERTY_R ( kESDuplexType, CESScanner, ESNumber, GetDuplexType );
 PROPERTY_RW( kESDuplex, CESScanner, bool, IsDuplexEnabled, bool, SetDuplexEnabled );
 PROPERTY_RW( kESDoubleFeedDetection, CESScanner, ESNumber, GetDoubleFeedDetection, ESNumber, SetDoubleFeedDetection );
 PROPERTY_RW( kESPagesToBeScanned, CESScanner, ESNumber, GetPagesToBeScanned, ESNumber, SetPagesToBeScanned );
 PROPERTY_R ( kESDocumentLoaded, CESScanner, bool, IsDocumentLoaded );
 PROPERTY_R ( kESCleaning, CESScanner, bool, IsCleaningSupported );
 PROPERTY_R ( kESCalibration, CESScanner, bool, IsCalibrationSupported );
 this->GetAllKeys();
}
CESScanner::~CESScanner()
{
}
ESErrorCode CESScanner::Initialize()
{
 return kESErrorNoError;
}
ESErrorCode CESScanner::SetConnection( ES_JSON_CPTR pszJSON )
{
 ES_LOG_TRACE_FUNC();
 IInterface* pInterface = nullptr;
 ESErrorCode err = CreateInterface(pszJSON, &pInterface);
 if (!pInterface){
  ES_LOG_INVALID_INPUT_PARAM();
  return err;
 }
 return SetDeviceInterface(pInterface);
}
ESErrorCode CESScanner::GetTargetCapabilityForKey( ES_CHAR_CPTR pszKey, ES_CHAR_CPTR pszTarget, ESDictionary& dicResult )
{
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') || pszTarget == NULL || pszTarget[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicCapability;
 ESErrorCode err = GetCapabilityForKey( pszKey, dicCapability );
 if ( IS_ERR_CODE( err ) ){
  ES_ERROR_LOG( ES_STRING("Failed get capability for key. Key:%s, Target:%s"), pszKey, pszTarget);
  return err;
 }
 if ( dicCapability.count( pszTarget ) != 0 ){
  dicResult[ pszKey ] = dicCapability[ pszTarget ];;
 }
 return kESErrorNoError;
}
ESErrorCode CESScanner::GetDefaultValueForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult )
{
 ES_LOG_TRACE_FUNC();
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_DEFAULT, dicResult );
}
ESErrorCode CESScanner::GetAllValuesForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult )
{
 ES_LOG_TRACE_FUNC();
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_ALLVALUES, dicResult );
}
ESErrorCode CESScanner::GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult )
{
 ES_LOG_TRACE_FUNC();
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_AVAILABLEVALUES, dicResult );
}
ESDictionary CESScanner::GetAllValuesDictionary()
{
 ES_LOG_TRACE_FUNC();
 ESDictionary dicResult;
 const ESStringArray& arKeyList = GetAllKeys();
 for(const ESString& strKey : arKeyList){
  GetAllValuesForKey( strKey.c_str(), dicResult );
 }
 return dicResult;
}
ESDictionary CESScanner::GetAvailableDictionary()
{
 ES_LOG_TRACE_FUNC();
 ESDictionary dicResult;
 const ESStringArray& arKeyList = GetAllKeys();
 for(const ESString& strKey : arKeyList){
  GetAvailableValuesForKey( strKey.c_str(), dicResult );
 }
 return dicResult;
}
ESErrorCode CESScanner::GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue )
{
 ES_LOG_TRACE_FUNC();
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ES_INFO_LOG( ES_STRING("Key = %s"), pszKey );
 ESErrorCode err = kESErrorNoError;
 if ( m_mapAccessor.count( pszKey ) != 0 ){
  err = m_mapAccessor[ pszKey ].GetValue( anyValue );
 } else {
  err = GetValueForUndefinedKey( pszKey, anyValue );
 }
 return err;
}
ESErrorCode CESScanner::SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue )
{
 ES_LOG_TRACE_FUNC();
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ES_INFO_LOG( ES_STRING("Key = %s"), pszKey );
 ESErrorCode err = kESErrorNoError;
 if ( m_mapAccessor.count( pszKey ) != 0 ){
  err = m_mapAccessor[ pszKey ].SetValue( anyValue );
  if ( IS_ERR_CODE( err ) ){
   ES_ERROR_LOG( ES_STRING("Failed set value for %s key."), pszKey );
  }
 } else {
  err = SetValueForUndefinedKey( pszKey, anyValue );
 }
 return err;
}
ESStringArray CESScanner::GetPriorKeys()
{
 const ES_CHAR_CPTR KeyList[] ={
  kESFunctionalUnitType,
  kESXResolution,
  kESYResolution,
  kESXOffsetMargin,
  kESYOffsetMargin,
  kESColorFormat,
  NULL
 };
 static ESStringArray s_arPriorKeys(&KeyList[0], &KeyList[ _countof(KeyList)-1 ] );
 return s_arPriorKeys;
}
ESErrorCode CESScanner::SetValuesForKeysWithDictionary( ESDictionary& dicKeysValues )
{
 ES_LOG_TRACE_FUNC();
 ESErrorCode err = kESErrorNoError;
 ESDictionary dicValues = dicKeysValues;
 const ESStringArray& arKeyList = GetPriorKeys();
 for(const ESString& strKey : arKeyList){
  if ( dicKeysValues.count( strKey.c_str() ) ){
   ESErrorCode errRet = SetValueForKey( strKey.c_str(), dicValues[ strKey.c_str() ] );
   if ( errRet != kESErrorNoError ){
    err = errRet;
   }
   dicValues.erase( strKey.c_str() );
  }
 }
 ESDictionary::const_iterator itDic;
 for ( itDic = dicValues.begin(); itDic != dicValues.end() ; ++itDic ){
  ESErrorCode errRet = SetValueForKey( itDic->first.c_str(), itDic->second );
  if ( errRet != kESErrorNoError ){
   err = errRet;
  }
 }
 return err;
}
ESErrorCode CESScanner::GetValueForUndefinedKey( ES_CHAR_CPTR pszKey, ESAny& anyValue )
{
 ES_WARM_LOG( ES_STRING("%s key is not defined."), pszKey);
 anyValue = nullptr;
 return kESErrorInvalidParameter;
}
ESErrorCode CESScanner::SetValueForUndefinedKey( ES_CHAR_CPTR pszKey, ESAny anyValue )
{
 ES_WARM_LOG( ES_STRING("%s key is not defined."), pszKey);
 return kESErrorInvalidParameter;
}
ESErrorCode CESScanner::GetAllKeys( IESResultString* pstrResult )
{
 if ( pstrResult == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 const ESStringArray& arKeys = GetAllKeys();
 ESDictionary dicSrc;
 ESString strJSON;
 dicSrc[ ES_JSON_KEY_ALLKEYS ] = arKeys;
 UInt32 ret = ES_CMN_FUNCS::JSON::DictionaryToJSON( dicSrc, strJSON );
 assert( ret == 0 );
 return ( pstrResult->Set(strJSON.c_str()) ? kESErrorNoError : kESErrorFatalError );
}
ESErrorCode CESScanner::GetTargetCapabilityForKey( ES_CHAR_CPTR pszKey, ES_CHAR_CPTR pszTarget, IESResultString* pstrResult )
{
 if ( pstrResult == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicValues;
 ESErrorCode err = GetTargetCapabilityForKey( pszKey, pszTarget, dicValues );
 if ( IS_ERR_CODE( err ) ){
  ES_ERROR_LOG( ES_STRING("Failed get target capability for keys. key:%s, target:%s"), pszKey, pszTarget );
  return err;
 }
 if ( dicValues.empty() ){
  return kESErrorNoError;
 }
 ESString strJSON;
 UInt32 ret = ES_CMN_FUNCS::JSON::DictionaryToJSON( dicValues, strJSON );
 assert( ret == 0 );
 return ( pstrResult->Set(strJSON.c_str()) ? kESErrorNoError : kESErrorFatalError );
}
ESErrorCode CESScanner::GetDefaultValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_DEFAULT, pstrResult );
}
ESErrorCode CESScanner::GetAllValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_ALLVALUES, pstrResult );
}
ESErrorCode CESScanner::GetAvailableValuesForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 return GetTargetCapabilityForKey( pszKey, ES_CAPABILITY_KEY_AVAILABLEVALUES, pstrResult );
}
ESErrorCode CESScanner::GetValueForKey( ES_CHAR_CPTR pszKey, IESResultString* pstrResult )
{
 if ( pstrResult == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESAny anyValue;
 ESErrorCode err = GetValueForKey( pszKey, anyValue );
 if ( IS_ERR_CODE( err ) ){
  ES_ERROR_LOG( ES_STRING("Failed get value for key.") );
  return err;
 }
 ESDictionary dicResult;
 dicResult[ pszKey ] = anyValue;
 ESString strJSON;
 UInt32 ret = ES_CMN_FUNCS::JSON::DictionaryToJSON( dicResult, strJSON );
 assert( ret == 0 );
 return ( pstrResult->Set(strJSON.c_str()) ? kESErrorNoError : kESErrorFatalError );
}
ESErrorCode CESScanner::SetValueForKey( ES_CHAR_CPTR pszKey, ES_JSON_CPTR pszJSON )
{
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') || pszJSON == NULL || pszJSON[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicValue;
 UInt32 un32ErrCounter = ES_CMN_FUNCS::JSON::JSONtoDictionary( pszJSON, dicValue );
 assert( un32ErrCounter == 0 );
 if ( dicValue.count( pszKey ) == 0 ){
  ES_LOG_INVALID_JSON_FORMAT( pszJSON );
  return kESErrorFatalError;
 }
 return SetValueForKey( pszKey, dicValue[ pszKey ] );
}
ESErrorCode CESScanner::SetValuesWithJSON( ES_JSON_CPTR pszJSON )
{
 if ( pszJSON == NULL || pszJSON[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicValue;
 UInt32 un32ErrCounter = ES_CMN_FUNCS::JSON::JSONtoDictionary( pszJSON, dicValue );
 assert( un32ErrCounter == 0 );
 return SetValuesForKeysWithDictionary( dicValue );
}
ESErrorCode CESScanner::GetAllValues( IESResultString* pstrResult )
{
 if ( pstrResult == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicValue = GetAllValuesDictionary();
 ESString strJSON;
 UInt32 ret = ES_CMN_FUNCS::JSON::DictionaryToJSON( dicValue, strJSON );
 assert( ret == 0 );
 return ( pstrResult->Set(strJSON.c_str()) ? kESErrorNoError : kESErrorFatalError );
}
ESErrorCode CESScanner::GetAllAvailableValues( IESResultString* pstrResult )
{
 if ( pstrResult == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 ESDictionary dicValue = GetAvailableDictionary();
 ESString strJSON;
 UInt32 ret = ES_CMN_FUNCS::JSON::DictionaryToJSON( dicValue, strJSON );
 assert( ret == 0 );
 return ( pstrResult->Set(strJSON.c_str()) ? kESErrorNoError : kESErrorFatalError );
}
void* CESScanner::EnterScannerThread(void* vpContext)
{
 ES_LOG_TRACE_FUNC();
 if(vpContext)
 {
  CESScanner* pcThis =(CESScanner*) vpContext;
  pcThis->Scan();
 }
 pthread_exit(0);
 return (void*)NULL;
}
ESErrorCode CESScanner::ScanInBackground()
{
 ES_LOG_TRACE_FUNC();
 ((CESScanner*)this)->SetScanning( true );
 ((CESScanner*)this)->SetCancelled( false );
 pthread_t thread;
 if (pthread_create(&thread, NULL, &CESScanner::EnterScannerThread, this) == 0)
 {
  pthread_detach(thread);
  return kESErrorNoError;
 }
 return kESErrorFatalError;
}
ESErrorCode CESScanner::DoAutoFocus( ESFloat* pfOutFocus )
{
 return kESErrorNoError;
}
BOOL CESScanner::IsScannableDeviceConfig()
{
 return TRUE;
}
