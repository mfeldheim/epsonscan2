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
//  ESCIScanner_Accessor.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCIScanner.h"
ESErrorCode CESCIScanner::GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue )
{
 ES_LOG_TRACE_FUNC();
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 const ESStringArray& arKeyList = GetAllKeys();
 ESStringArray::const_iterator it = std::find( arKeyList.begin(), arKeyList.end(), pszKey );
 if ( it == arKeyList.end() ){
  ES_WARM_LOG( ES_STRING("Unsuported Key : %s"), pszKey );
  anyValue = nullptr;
  return kESErrorInvalidParameter;
 } else {
  ESDictionary dicAllValue;
  GetAllValuesForKey( pszKey, dicAllValue );
  if ( dicAllValue.empty() ){
   ES_WARM_LOG( ES_STRING("Unsuported Key : %s"), pszKey );
   anyValue = nullptr;
   return kESErrorInvalidParameter;
  }
 }
 ES_INFO_LOG( ES_STRING("Key = %s"), pszKey );
 ESErrorCode err = kESErrorNoError;
 if ( m_mapAccessor.count( pszKey ) != 0 ){
  err = m_mapAccessor[ pszKey ].GetValue( anyValue );
 } else {
  err = CESScanner::GetValueForKey( pszKey, anyValue );
 }
 return err;
}
ESErrorCode CESCIScanner::SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue )
{
 ES_LOG_TRACE_FUNC();
 if ( pszKey == NULL || pszKey[0] == ES_STRING('\0') ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorInvalidParameter;
 }
 const ESStringArray& arKeyList = GetAllKeys();
 ESStringArray::const_iterator it = std::find( arKeyList.begin(), arKeyList.end(), pszKey );
 if ( it == arKeyList.end() ){
  ES_WARM_LOG( ES_STRING("Unsuported Key : %s"), pszKey );
  return kESErrorInvalidParameter;
 } else {
  ESDictionary dicAvailableValue;
  GetAvailableValuesForKey( pszKey, dicAvailableValue );
  if ( dicAvailableValue.empty() ){
   ES_WARM_LOG( ES_STRING("Unavailable key: %s"), pszKey );
   return kESErrorInvalidParameter;
  }
 }
 ES_INFO_LOG( ES_STRING("Key = %s"), pszKey );
 ESErrorCode err = kESErrorNoError;
 if ( m_mapAccessor.count( pszKey ) != 0 ){
  err = m_mapAccessor[ pszKey ].SetValue( anyValue );
  if ( IS_ERR_CODE( err ) ){
   ES_ERROR_LOG( ES_STRING("Failed set value for %s key."), pszKey );
  }
 } else {
  err = CESScanner::SetValueForKey( pszKey, anyValue );
 }
 return err;
}
ESString CESCIScanner::GetWorkFolder()
{
 return CESCIAccessor::GetWorkFolder();
}
ESErrorCode CESCIScanner::SetWorkFolder( ESString strWorkFolder )
{
 return CESCIAccessor::SetWorkFolder(strWorkFolder);
}
ESErrorCode CESCIScanner::GetErrorStatus()
{
 return CESCIAccessor::GetErrorStatus();
}
ESNumber CESCIScanner::GetBufferSize()
{
 return CESCIAccessor::GetBufferSize();
}
ESErrorCode CESCIScanner::SetBufferSize( ESNumber nBufferSize )
{
 return CESCIAccessor::SetBufferSize( nBufferSize );
}
bool CESCIScanner::IsAuthenticationSupported()
{
 return CESCIAccessor::IsAuthenticationSupported();
}
bool CESCIScanner::IsAuthenticationEnabled()
{
 return CESCIAccessor::IsAuthenticationEnabled();
}
ESErrorCode CESCIScanner::SetAuthenticationEnabled( bool bEnabled )
{
 return CESCIAccessor::SetAuthenticationEnabled( bEnabled );
}
ESString CESCIScanner::GetAuthUserName()
{
 return CESCIAccessor::GetAuthUserName();
}
ESErrorCode CESCIScanner::SetAuthUserName( ESString strAuthUserName )
{
 return CESCIAccessor::SetAuthUserName( strAuthUserName );
}
ESString CESCIScanner::GetAuthPassword()
{
 return CESCIAccessor::GetAuthPassword();
}
ESErrorCode CESCIScanner::SetAuthPassword( ESString strAuthPassword )
{
 return CESCIAccessor::SetAuthPassword( strAuthPassword );
}
ESString CESCIScanner::GetProductName()
{
 return CESCIAccessor::GetProductName();
}
ESIndexSet CESCIScanner::GetSupportedFunctionalUnitTypes()
{
 return CESCIAccessor::GetSupportedFunctionalUnitTypes();
}
ESFunctionalUnitType CESCIScanner::GetFunctionalUnitType()
{
 return CESCIAccessor::GetFunctionalUnitType();
}
ESErrorCode CESCIScanner::SetFunctionalUnitType( ESNumber nFunctionalUnitType )
{
 return CESCIAccessor::SetFunctionalUnitType( nFunctionalUnitType );
}
ESAny CESCIScanner::GetSupportedXResolutions()
{
 return CESCIAccessor::GetSupportedXResolutions();
}
ESAny CESCIScanner::GetSupportedYResolutions()
{
 return CESCIAccessor::GetSupportedYResolutions();
}
ESNumber CESCIScanner::GetXResolution()
{
 return CESCIAccessor::GetXResolution();
}
ESNumber CESCIScanner::GetYResolution()
{
 return CESCIAccessor::GetYResolution();
}
ESErrorCode CESCIScanner::SetXResolution( ESNumber xResolution )
{
 return CESCIAccessor::SetXResolution( xResolution );
}
ESErrorCode CESCIScanner::SetYResolution( ESNumber yResolution )
{
 return CESCIAccessor::SetYResolution( yResolution );
}
ESNumber CESCIScanner::GetOpticalResolution()
{
 return CESCIAccessor::GetOpticalResolution();
}
ST_ES_SIZE_F CESCIScanner::GetMaxScanSize()
{
 return CESCIAccessor::GetMaxScanSize();
}
ST_ES_RECT_F CESCIScanner::GetScanArea()
{
 return CESCIAccessor::GetScanArea();
}
ESErrorCode CESCIScanner::SetScanArea(ST_ES_RECT_F rcScanArea)
{
 return CESCIAccessor::SetScanArea( rcScanArea );
}
ST_ES_RECT_UN32 CESCIScanner::GetScanAreaInPixel()
{
 return CESCIAccessor::GetScanAreaInPixel();
}
ESErrorCode CESCIScanner::SetScanAreaInPixel( ST_ES_RECT_UN32 rcUn32ScanAreaInPixel)
{
 return CESCIAccessor::SetScanAreaInPixel( rcUn32ScanAreaInPixel );
}
ST_ES_SIZE_F CESCIScanner::GetScanSize()
{
 return CESCIAccessor::GetScanSize();
}
ESErrorCode CESCIScanner::SetScanSize( ST_ES_SIZE_F sizeScan )
{
 return CESCIAccessor::SetScanSize( sizeScan );
}
ST_ES_SIZE_UN32 CESCIScanner::GetScanSizeInPixel()
{
 return CESCIAccessor::GetScanSizeInPixel();
}
ESErrorCode CESCIScanner::SetScanSizeInPixel( ST_ES_SIZE_UN32 sizeScan )
{
 return CESCIAccessor::SetScanSizeInPixel( sizeScan );
}
ESFloat CESCIScanner::GetXOffsetMargin()
{
 return CESCIAccessor::GetXOffsetMargin();
}
ESErrorCode CESCIScanner::SetXOffsetMargin( ESFloat fMargin )
{
 return CESCIAccessor::SetXOffsetMargin( fMargin );
}
ESFloat CESCIScanner::GetYOffsetMargin()
{
 return CESCIAccessor::GetYOffsetMargin();
}
ESErrorCode CESCIScanner::SetYOffsetMargin( ESFloat fMargin )
{
 return CESCIAccessor::SetYOffsetMargin( fMargin );
}
ESIndexSet CESCIScanner::GetSupportedColorFormats()
{
 return CESCIAccessor::GetSupportedColorFormats();
}
ESNumber CESCIScanner::GetColorFormat()
{
 return CESCIAccessor::GetColorFormat();
}
ESErrorCode CESCIScanner::SetColorFormat( ESNumber nColorFormat )
{
 return CESCIAccessor::SetColorFormat( nColorFormat );
}
ESNumber CESCIScanner::GetBitsPerSample()
{
 return CESCIAccessor::GetBitsPerSample();
}
ESNumber CESCIScanner::GetSamplesPerPixel()
{
 return CESCIAccessor::GetSamplesPerPixel();
}
ESNumber CESCIScanner::GetBitsPerPixel()
{
 return CESCIAccessor::GetBitsPerPixel();
}
ESAny CESCIScanner::GetColorMatrix()
{
 return CESCIAccessor::GetColorMatrix();
}
ESErrorCode CESCIScanner::SetColorMatrix( ESFloatArray arColorMatrix )
{
 return CESCIAccessor::SetColorMatrix( arColorMatrix );
}
ESIndexSet CESCIScanner::GetSupportedGammaModes()
{
 return CESCIAccessor::GetSupportedGammaModes();
}
ESGammaMode CESCIScanner::GetGammaMode()
{
 return CESCIAccessor::GetGammaMode();
}
ESErrorCode CESCIScanner::SetGammaMode( ESNumber nGammaMode )
{
 return CESCIAccessor::SetGammaMode( nGammaMode );
}
ESAny CESCIScanner::GetGammaTableMono()
{
 return CESCIAccessor::GetGammaTableMono();
}
ESAny CESCIScanner::GetGammaTableRed()
{
 return CESCIAccessor::GetGammaTableRed();
}
ESAny CESCIScanner::GetGammaTableGreen()
{
 return CESCIAccessor::GetGammaTableGreen();
}
ESAny CESCIScanner::GetGammaTableBlue()
{
 return CESCIAccessor::GetGammaTableBlue();
}
ESErrorCode CESCIScanner::SetGammaTableMono( ESIndexArray arGammaTable )
{
 return CESCIAccessor::SetGammaTableMono( arGammaTable );
}
ESErrorCode CESCIScanner::SetGammaTableRed( ESIndexArray arGammaTable )
{
 return CESCIAccessor::SetGammaTableRed( arGammaTable );
}
ESErrorCode CESCIScanner::SetGammaTableGreen( ESIndexArray arGammaTable )
{
 return CESCIAccessor::SetGammaTableGreen( arGammaTable );
}
ESErrorCode CESCIScanner::SetGammaTableBlue( ESIndexArray arGammaTable )
{
 return CESCIAccessor::SetGammaTableBlue( arGammaTable );
}
ESAny CESCIScanner::GetSupportedThreshold()
{
 return CESCIAccessor::GetSupportedThreshold();
}
ESNumber CESCIScanner::GetThreshold()
{
 return CESCIAccessor::GetThreshold();
}
ESErrorCode CESCIScanner::SetThreshold( ESNumber nThreshold )
{
 return CESCIAccessor::SetThreshold( nThreshold );
}
ESIndexSet CESCIScanner::GetSupportedQuietModes()
{
 return CESCIAccessor::GetSupportedQuietModes();
}
ESQuietMode CESCIScanner::GetQuietMode()
{
 return CESCIAccessor::GetQuietMode();
}
ESErrorCode CESCIScanner::SetQuietMode( ESNumber nQuietMode )
{
 return CESCIAccessor::SetQuietMode( nQuietMode );
}
bool CESCIScanner::IsFeederSupported()
{
 return CESCIAccessor::IsFeederSupported();
}
bool CESCIScanner::IsFeederEnabled()
{
 return CESCIAccessor::IsFeederEnabled();
}
ESDuplexType CESCIScanner::GetDuplexType()
{
 return CESCIAccessor::GetDuplexType();
}
bool CESCIScanner::IsDuplexSupported()
{
 return CESCIAccessor::IsDuplexSupported();
}
bool CESCIScanner::IsDuplexEnabled()
{
 return CESCIAccessor::IsDuplexEnabled();
}
ESErrorCode CESCIScanner::SetDuplexEnabled( bool bDuplexEnabled )
{
 return CESCIAccessor::SetDuplexEnabled( bDuplexEnabled );
}
ESIndexSet CESCIScanner::GetSupportedDoubleFeedDetections()
{
 return CESCIAccessor::GetSupportedDoubleFeedDetections();
}
ESDoubleFeedDetection CESCIScanner::GetDoubleFeedDetection()
{
 return CESCIAccessor::GetDoubleFeedDetection();
}
ESErrorCode CESCIScanner::SetDoubleFeedDetection( ESNumber nDoubleFeedDetection )
{
 return CESCIAccessor::SetDoubleFeedDetection( nDoubleFeedDetection );
}
bool CESCIScanner::IsDocumentLoaded()
{
 return CESCIAccessor::IsDocumentLoaded();
}
ESNumber CESCIScanner::GetPagesToBeScanned()
{
 return CESCIAccessor::GetPagesToBeScanned();
}
ESErrorCode CESCIScanner::SetPagesToBeScanned( ESNumber nPagesToBeScanned )
{
 return CESCIAccessor::SetPagesToBeScanned( nPagesToBeScanned );
}
bool CESCIScanner::IsCleaningSupported()
{
 return CESCIAccessor::IsCleaningSupported();
}
bool CESCIScanner::IsCalibrationSupported()
{
 return CESCIAccessor::IsCleaningSupported();
}
bool CESCIScanner::IsCaptureCommandSupported()
{
 return CESCIAccessor::IsCaptureCommandSupported();
}
ESErrorCode CESCIScanner::SetCaptureCommandSupported( bool bSupported )
{
 return CESCIAccessor::SetCaptureCommandSupported( bSupported );
}
