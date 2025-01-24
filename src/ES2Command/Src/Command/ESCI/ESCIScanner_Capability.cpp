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
//  ESCIScanner_Capability.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCIScanner.h"
#include "../ESScannerDefs.h"
const bool BOOLEAN_ARRAY_DATA[2] ={ true, false };
const ESIndexSet BOOLEAN_ARRAY( BOOLEAN_ARRAY_DATA, BOOLEAN_ARRAY_DATA+2);
const ESStringArray& CESCIScanner::GetAllKeys()
{
 const ES_CHAR_CPTR KeyList[] = {
  kESWarmingUp,
  kESButtonStatus,
  kESLampMode,
  kESPowerOffTime,
  kESMaxFocus,
  kESMinFocus,
  kESFocus,
  kESDigitalICE,
  kESDetectedDocumentSize,
  kESHalftone,
  kESPaperEndDetection,
  kESOverScan,
  kESFilmType,
  kESScanningMode,
  kESCaptureCommandSupported,
  kESShouldIgnoreCancelFromScanner,
  kESGuidePosition,
  kESGuidePositionFB,
  kESGuidePositionADF,
  kESMaxScanSizeInLongLength,
  kESDisableJobContinue,
  kESSimplexScanCounter,
  kESDuplexScanCounter,
  kESLamp1Counter,
  kESLamp2Counter,
  kESPickupRollerCounter,
  kESScanCounter,
  kESLightIntensityFB,
  NULL
 };
 if ( m_arAllKeys.empty() ){
  const ESStringArray& arParentAllKeys = CESScanner::GetAllKeys();
  m_arAllKeys.insert( m_arAllKeys.end(), arParentAllKeys.begin(), arParentAllKeys.end() );
  m_arAllKeys.insert( m_arAllKeys.end(), KeyList, KeyList+_countof(KeyList)-1 );
 }
 return m_arAllKeys;
}
ESErrorCode CESCIScanner::GetCapabilityForKey( ES_CHAR_CPTR pszKey, ESDictionary& dicResult )
{
 if ( pszKey == NULL || pszKey[0] == L'\0' ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 if ( m_funcCapability.empty() ){
  m_funcCapability[ kESDisableJobContinue ] = FN_CAPA(&CESCIScanner::GetDisableJobContinueCapability );
  m_funcCapability[ kESMaxScanSizeInLongLength ] = FN_CAPA(&CESCIScanner::GetMaxScanSizeInLongLengthCapability );
  m_funcCapability[ kESWarmingUp ] = FN_CAPA(&CESCIScanner::GetWarmingUpCapability );
  m_funcCapability[ kESButtonStatus ] = FN_CAPA(&CESCIScanner::GetButtonStatusCapability );
  m_funcCapability[ kESLampMode ] = FN_CAPA(&CESCIScanner::GetLampModeCapability );
  m_funcCapability[ kESPowerOffTime ] = FN_CAPA(&CESCIScanner::GetPowerOffTimeCapability );
  m_funcCapability[ kESHalftone ] = FN_CAPA(&CESCIScanner::GetHalftoneCapability );
  m_funcCapability[ kESMaxFocus ] = FN_CAPA(&CESCIScanner::GetMaxFocusCapability );
  m_funcCapability[ kESMinFocus ] = FN_CAPA(&CESCIScanner::GetMinFocusCapability );
  m_funcCapability[ kESFocus ] = FN_CAPA(&CESCIScanner::GetFocusCapability );
  m_funcCapability[ kESDigitalICE ] = FN_CAPA(&CESCIScanner::GetDigitalICECapability );
  m_funcCapability[ kESFilmType ] = FN_CAPA(&CESCIScanner::GetFilmTypeCapability );
  m_funcCapability[ kESScanningMode ] = FN_CAPA(&CESCIScanner::GetScanningModeCapability );
  m_funcCapability[ kESDetectedDocumentSize ] = FN_CAPA(&CESCIScanner::GetDetectedDocumentSizeCapability );
  m_funcCapability[ kESPaperEndDetection ] = FN_CAPA(&CESCIScanner::GetPaperEndDetectionCapability );
  m_funcCapability[ kESOverScan ] = FN_CAPA(&CESCIScanner::GetOverScanCapability );
  m_funcCapability[ kESSimplexScanCounter ] = FN_CAPA(&CESCIScanner::GetSimplexScanCounterCapability );
  m_funcCapability[ kESDuplexScanCounter ] = FN_CAPA(&CESCIScanner::GetDuplexScanCounterCapability );
  m_funcCapability[ kESColorMatrixMode ] = FN_CAPA(&CESCIScanner::GetColorMatrixModeCapability );
  m_funcCapability[ kESCaptureCommandSupported ] = FN_CAPA(&CESCIScanner::GetCaptureCommandSupportedCapability );
  m_funcCapability[ kESShouldIgnoreCancelFromScanner ] = FN_CAPA(&CESCIScanner::GetShouldIgnoreCancelFromScannerCapability );
  m_funcCapability[ kESGuidePosition ] = FN_CAPA(&CESCIScanner::GetGuidePositionReadOnlyCapability );
  m_funcCapability[ kESGuidePositionFB ] = FN_CAPA(&CESCIScanner::GetGuidePositionCapability );
  m_funcCapability[ kESGuidePositionADF ] = FN_CAPA(&CESCIScanner::GetGuidePositionCapability );
  m_funcCapability[ kESLamp1Counter ] = FN_CAPA(&CESCIScanner::GetLamp1CounterCapability );
  m_funcCapability[ kESLamp2Counter ] = FN_CAPA(&CESCIScanner::GetLamp2CounterCapability );
  m_funcCapability[ kESPickupRollerCounter ] = FN_CAPA(&CESCIScanner::GetPickupRollerCounterCapability );
  m_funcCapability[ kESScanCounter ] = FN_CAPA(&CESCIScanner::GetScanCounterCapability );
  m_funcCapability[ kESLightIntensityFB ] = FN_CAPA(&CESCIScanner::GetLightIntensityCapability );
 }
 if ( m_funcCapability.count( pszKey ) != 0 ){
  (m_funcCapability[ pszKey ])( this, dicResult );
  return kESErrorNoError;
 }
 return CESScanner::GetCapabilityForKey( pszKey, dicResult );
}
bool CESCIScanner::IsSupportedLogFunction(ESCILogFunctionKey function)
{
 using namespace epsonscan2::es2command;
 return ModelInfo::Instance().IsSupportedLogFunctions(GetProductName(), function);
}
void CESCIScanner::GetVersionCapability( ESDictionary& dicResult )
{
 if ( !GetVersion().empty() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = GetVersion();
 }
}
void CESCIScanner::GetColorMatrixCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
}
void CESCIScanner::GetDisableJobContinueCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = BOOLEAN_ARRAY;
}
void CESCIScanner::GetMaxScanSizeInLongLengthCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = GetMaxScanSizeInLongLength();
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
}
void CESCIScanner::GetWarmingUpCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
}
void CESCIScanner::GetButtonStatusCapability( ESDictionary& dicResult )
{
 if ( IsPushButtonSupported() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
 }
}
void CESCIScanner::GetLampModeCapability( ESDictionary& dicResult )
{
 ESIndexSet values = GetSupportedLampModes();
 if ( !values.empty() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESLampModeDefault;
 }
}
void CESCIScanner::GetHalftoneCapability( ESDictionary& dicResult )
{
 ESIndexSet values = GetSupportedHalftones();
 if ( !values.empty() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESHalftoneNone;
 }
}
void CESCIScanner::GetMaxFocusCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = GetMaxFocus();
}
void CESCIScanner::GetMinFocusCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = GetMinFocus();
}
void CESCIScanner::GetFocusCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESFloat)0.0f;
}
void CESCIScanner::GetDigitalICECapability( ESDictionary& dicResult )
{
 ESIndexSet values = GetSupportedDigitalICEs();
 if ( !values.empty() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESDigitalICEDisable;
 }
}
void CESCIScanner::GetFilmTypeCapability( ESDictionary& dicResult )
{
 ESIndexSet values = GetSupportedFilmTypes();
 if ( !values.empty() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESFilmTypePositive;
 }
}
void CESCIScanner::GetScanningModeCapability( ESDictionary& dicResult )
{
 ESIndexSet values;
 values.insert( kESScanningModeHighSpeed );
 values.insert( kESScanningModeNormal );
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
 dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESScanningModeNormal;
}
void CESCIScanner::GetColorMatrixModeCapability( ESDictionary& dicResult )
{
 ESIndexSet values;
 values.insert ( kESColorMatrixUnit );
 values.insert ( kESColorMatrix8 );
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
 dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)kESColorMatrixUnit;
}
void CESCIScanner::GetDetectedDocumentSizeCapability( ESDictionary& dicResult )
{
 if ( IsDocumentSizeDetectionSupported() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
 }
}
void CESCIScanner::GetSimplexScanCounterCapability( ESDictionary& dicResult )
{
 if ( IsFeederSupported() && IsSupportedLogFunction(ESCILogFunctionSimplexScanCounter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetDuplexScanCounterCapability( ESDictionary& dicResult )
{
 if ( IsFeederSupported() && IsDuplexSupported() && IsSupportedLogFunction(ESCILogFunctionDuplexScanCounter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetCaptureCommandSupportedCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = BOOLEAN_ARRAY;
}
void CESCIScanner::GetShouldIgnoreCancelFromScannerCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = BOOLEAN_ARRAY;
}
void CESCIScanner::GetGuidePositionReadOnlyCapability( ESDictionary& dicResult )
{
 ESIndexSet values;
 values.insert ( kESGuidePositionLeft );
 values.insert ( kESGuidePositionCenter );
 values.insert ( kESGuidePositionRight );
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
}
void CESCIScanner::GetGuidePositionCapability( ESDictionary& dicResult )
{
 ESIndexSet values;
 values.insert ( kESGuidePositionLeft );
 values.insert ( kESGuidePositionCenter );
 values.insert ( kESGuidePositionRight );
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = values;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = values;
}
void CESCIScanner::GetLamp1CounterCapability( ESDictionary& dicResult )
{
 if ( IsFlatbedSupported() && IsSupportedLogFunction(ESCILogFunctionLamp1Counter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetLamp2CounterCapability( ESDictionary& dicResult )
{
 if ( IsFlatbedSupported() && IsSupportedLogFunction(ESCILogFunctionLamp2Counter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetPickupRollerCounterCapability( ESDictionary& dicResult )
{
 if ( IsFeederSupported() && IsSupportedLogFunction(ESCILogFunctionPickupRollerCounter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetScanCounterCapability( ESDictionary& dicResult )
{
 if ( IsFlatbedSupported() && IsSupportedLogFunction(ESCILogFunctionFlatbedScanCounter) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
 }
}
void CESCIScanner::GetPaperEndDetectionCapability( ESDictionary& dicResult )
{
 if ( IsPaperEndDetectionSupported() ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = BOOLEAN_ARRAY;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = false;
 }
}
void CESCIScanner::GetOverScanCapability( ESDictionary& dicResult )
{
 dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = BOOLEAN_ARRAY;
 dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = BOOLEAN_ARRAY;
 dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = false;
}
void CESCIScanner::GetPowerOffTimeCapability( ESDictionary& dicResult )
{
 if ( IsPowerOffSupported() && IsSupportedLogFunction(ESCILogFunctionPowerOffTime) ){
  dicResult[ ES_CAPABILITY_KEY_ALLVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_AVAILABLEVALUES ] = nullptr;
  dicResult[ ES_CAPABILITY_KEY_DEFAULT ] = (ESNumber)0;
 }
}
void CESCIScanner::GetLightIntensityCapability(ESDictionary& dicResult)
{
 ESAny values = GetSupportedLightIntensitiesFB();
 if (!values.empty()) {
  dicResult[ES_CAPABILITY_KEY_ALLVALUES] = values;
  dicResult[ES_CAPABILITY_KEY_AVAILABLEVALUES] = values;
 }
}
