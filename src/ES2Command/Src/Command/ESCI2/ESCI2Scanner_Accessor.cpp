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
//  ESCI2Scanner_Accessor.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESCI2Scanner.h"
ESErrorCode CESCI2Scanner::GetValueForKey( ES_CHAR_CPTR pszKey, ESAny& anyValue )
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
ESErrorCode CESCI2Scanner::SetValueForKey( ES_CHAR_CPTR pszKey, ESAny anyValue )
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
ESString CESCI2Scanner::GetWorkFolder()
{
 return CESCI2Accessor::GetWorkFolder();
}
ESErrorCode CESCI2Scanner::SetWorkFolder( ESString strWorkFolder )
{
 return CESCI2Accessor::SetWorkFolder(strWorkFolder);
}
ESErrorCode CESCI2Scanner::GetErrorStatus()
{
 return CESCI2Accessor::GetErrorStatus();
}
ESNumber CESCI2Scanner::GetBufferSize()
{
 return CESCI2Accessor::GetBufferSize();
}
ESErrorCode CESCI2Scanner::SetBufferSize( ESNumber nBufferSize )
{
 return CESCI2Accessor::SetBufferSize( nBufferSize );
}
bool CESCI2Scanner::IsAuthenticationSupported()
{
 return CESCI2Accessor::IsAuthenticationSupported();
}
ENUM_ES_HASH_TYPE CESCI2Scanner::GetMaintenanceHashType()
{
 return CESCI2Accessor::GetMaintenanceHashType();
}
bool CESCI2Scanner::IsAuthenticationEnabled()
{
 return CESCI2Accessor::IsAuthenticationEnabled();
}
ESErrorCode CESCI2Scanner::SetAuthenticationEnabled( bool bEnabled )
{
 return CESCI2Accessor::SetAuthenticationEnabled( bEnabled );
}
ESString CESCI2Scanner::GetAuthUserName()
{
 return CESCI2Accessor::GetAuthUserName();
}
ESErrorCode CESCI2Scanner::SetAuthUserName( ESString strAuthUserName )
{
 return CESCI2Accessor::SetAuthUserName( strAuthUserName );
}
ESString CESCI2Scanner::GetAuthPassword()
{
 return CESCI2Accessor::GetAuthPassword();
}
ESErrorCode CESCI2Scanner::SetAuthPassword( ESString strAuthPassword )
{
 return CESCI2Accessor::SetAuthPassword( strAuthPassword );
}
ESString CESCI2Scanner::GetProductName()
{
 return CESCI2Accessor::GetProductName();
}
ESIndexSet CESCI2Scanner::GetSupportedFunctionalUnitTypes()
{
 return CESCI2Accessor::GetSupportedFunctionalUnitTypes();
}
ESFunctionalUnitType CESCI2Scanner::GetFunctionalUnitType()
{
 return CESCI2Accessor::GetFunctionalUnitType();
}
ESErrorCode CESCI2Scanner::SetFunctionalUnitType( ESNumber nFunctionalUnitType )
{
 return CESCI2Accessor::SetFunctionalUnitType( nFunctionalUnitType );
}
ESAny CESCI2Scanner::GetSupportedXResolutions()
{
 return CESCI2Accessor::GetSupportedXResolutions();
}
ESAny CESCI2Scanner::GetSupportedYResolutions()
{
 return CESCI2Accessor::GetSupportedYResolutions();
}
ESNumber CESCI2Scanner::GetXResolution()
{
 return CESCI2Accessor::GetXResolution();
}
ESNumber CESCI2Scanner::GetYResolution()
{
 return CESCI2Accessor::GetYResolution();
}
ESErrorCode CESCI2Scanner::SetXResolution( ESNumber xResolution )
{
 return CESCI2Accessor::SetXResolution( xResolution );
}
ESErrorCode CESCI2Scanner::SetYResolution( ESNumber yResolution )
{
 return CESCI2Accessor::SetYResolution( yResolution );
}
ESNumber CESCI2Scanner::GetOpticalResolution()
{
 return CESCI2Accessor::GetOpticalResolution();
}
ST_ES_SIZE_F CESCI2Scanner::GetMaxScanSize()
{
 return CESCI2Accessor::GetMaxScanSize();
}
ST_ES_RECT_F CESCI2Scanner::GetScanArea()
{
 return CESCI2Accessor::GetScanArea();
}
ESErrorCode CESCI2Scanner::SetScanArea(ST_ES_RECT_F rcScanArea)
{
 return CESCI2Accessor::SetScanArea( rcScanArea );
}
ST_ES_RECT_UN32 CESCI2Scanner::GetScanAreaInPixel()
{
 return CESCI2Accessor::GetScanAreaInPixel();
}
ESErrorCode CESCI2Scanner::SetScanAreaInPixel( ST_ES_RECT_UN32 rcUn32ScanAreaInPixel)
{
 return CESCI2Accessor::SetScanAreaInPixel( rcUn32ScanAreaInPixel );
}
ST_ES_SIZE_F CESCI2Scanner::GetScanSize()
{
 return CESCI2Accessor::GetScanSize();
}
ESErrorCode CESCI2Scanner::SetScanSize( ST_ES_SIZE_F sizeScan )
{
 return CESCI2Accessor::SetScanSize( sizeScan );
}
ST_ES_SIZE_UN32 CESCI2Scanner::GetScanSizeInPixel()
{
 return CESCI2Accessor::GetScanSizeInPixel();
}
ESErrorCode CESCI2Scanner::SetScanSizeInPixel( ST_ES_SIZE_UN32 sizeScan )
{
 return CESCI2Accessor::SetScanSizeInPixel( sizeScan );
}
ESFloat CESCI2Scanner::GetXOffsetMargin()
{
 return CESCI2Accessor::GetXOffsetMargin();
}
ESErrorCode CESCI2Scanner::SetXOffsetMargin( ESFloat fMargin )
{
 return CESCI2Accessor::SetXOffsetMargin( fMargin );
}
ESFloat CESCI2Scanner::GetYOffsetMargin()
{
 return CESCI2Accessor::GetYOffsetMargin();
}
ESErrorCode CESCI2Scanner::SetYOffsetMargin( ESFloat fMargin )
{
 return CESCI2Accessor::SetYOffsetMargin( fMargin );
}
ESIndexSet CESCI2Scanner::GetSupportedColorFormats()
{
 return CESCI2Accessor::GetSupportedColorFormats();
}
ESNumber CESCI2Scanner::GetColorFormat()
{
 return CESCI2Accessor::GetColorFormat();
}
ESErrorCode CESCI2Scanner::SetColorFormat( ESNumber nColorFormat )
{
 return CESCI2Accessor::SetColorFormat( nColorFormat );
}
ESNumber CESCI2Scanner::GetBitsPerSample()
{
 return CESCI2Accessor::GetBitsPerSample();
}
ESNumber CESCI2Scanner::GetSamplesPerPixel()
{
 return CESCI2Accessor::GetSamplesPerPixel();
}
ESNumber CESCI2Scanner::GetBitsPerPixel()
{
 return CESCI2Accessor::GetBitsPerPixel();
}
ESAny CESCI2Scanner::GetColorMatrix()
{
 return CESCI2Accessor::GetColorMatrix();
}
ESErrorCode CESCI2Scanner::SetColorMatrix( ESFloatArray arColorMatrix )
{
 return CESCI2Accessor::SetColorMatrix( arColorMatrix );
}
ESIndexSet CESCI2Scanner::GetSupportedGammaModes()
{
 return CESCI2Accessor::GetSupportedGammaModes();
}
ESGammaMode CESCI2Scanner::GetGammaMode()
{
 return CESCI2Accessor::GetGammaMode();
}
ESErrorCode CESCI2Scanner::SetGammaMode( ESNumber nGammaMode )
{
 return CESCI2Accessor::SetGammaMode( nGammaMode );
}
ESAny CESCI2Scanner::GetGammaTableMono()
{
 return CESCI2Accessor::GetGammaTableMono();
}
ESAny CESCI2Scanner::GetGammaTableRed()
{
 return CESCI2Accessor::GetGammaTableRed();
}
ESAny CESCI2Scanner::GetGammaTableGreen()
{
 return CESCI2Accessor::GetGammaTableGreen();
}
ESAny CESCI2Scanner::GetGammaTableBlue()
{
 return CESCI2Accessor::GetGammaTableBlue();
}
ESErrorCode CESCI2Scanner::SetGammaTableMono( ESIndexArray arGammaTable )
{
 return CESCI2Accessor::SetGammaTableMono( arGammaTable );
}
ESErrorCode CESCI2Scanner::SetGammaTableRed( ESIndexArray arGammaTable )
{
 return CESCI2Accessor::SetGammaTableRed( arGammaTable );
}
ESErrorCode CESCI2Scanner::SetGammaTableGreen( ESIndexArray arGammaTable )
{
 return CESCI2Accessor::SetGammaTableGreen( arGammaTable );
}
ESErrorCode CESCI2Scanner::SetGammaTableBlue( ESIndexArray arGammaTable )
{
 return CESCI2Accessor::SetGammaTableBlue( arGammaTable );
}
ESAny CESCI2Scanner::GetSupportedThreshold()
{
 return CESCI2Accessor::GetSupportedThreshold();
}
ESNumber CESCI2Scanner::GetThreshold()
{
 return CESCI2Accessor::GetThreshold();
}
ESErrorCode CESCI2Scanner::SetThreshold( ESNumber nThreshold )
{
 return CESCI2Accessor::SetThreshold( nThreshold );
}
ESIndexSet CESCI2Scanner::GetSupportedQuietModes()
{
 return CESCI2Accessor::GetSupportedQuietModes();
}
ESQuietMode CESCI2Scanner::GetQuietMode()
{
 return CESCI2Accessor::GetQuietMode();
}
ESErrorCode CESCI2Scanner::SetQuietMode( ESNumber nQuietMode )
{
 return CESCI2Accessor::SetQuietMode( nQuietMode );
}
bool CESCI2Scanner::IsFeederSupported()
{
 return CESCI2Accessor::IsFeederSupported();
}
bool CESCI2Scanner::IsFeederEnabled()
{
 return CESCI2Accessor::IsFeederEnabled();
}
ESDuplexType CESCI2Scanner::GetDuplexType()
{
 return CESCI2Accessor::GetDuplexType();
}
bool CESCI2Scanner::IsDuplexSupported()
{
 return CESCI2Accessor::IsDuplexSupported();
}
bool CESCI2Scanner::IsDuplexEnabled()
{
 return CESCI2Accessor::IsDuplexEnabled();
}
ESErrorCode CESCI2Scanner::SetDuplexEnabled( bool bDuplexEnabled )
{
 return CESCI2Accessor::SetDuplexEnabled( bDuplexEnabled );
}
ESIndexSet CESCI2Scanner::GetSupportedDoubleFeedDetections()
{
 return CESCI2Accessor::GetSupportedDoubleFeedDetections();
}
ESDoubleFeedDetection CESCI2Scanner::GetDoubleFeedDetection()
{
 return CESCI2Accessor::GetDoubleFeedDetection();
}
ESErrorCode CESCI2Scanner::SetDoubleFeedDetection( ESNumber nDoubleFeedDetection )
{
 return CESCI2Accessor::SetDoubleFeedDetection( nDoubleFeedDetection );
}
bool CESCI2Scanner::IsDocumentLoaded()
{
 return CESCI2Accessor::IsDocumentLoaded();
}
ESNumber CESCI2Scanner::GetPagesToBeScanned()
{
 return CESCI2Accessor::GetPagesToBeScanned();
}
ESErrorCode CESCI2Scanner::SetPagesToBeScanned( ESNumber nPagesToBeScanned )
{
 return CESCI2Accessor::SetPagesToBeScanned( nPagesToBeScanned );
}
bool CESCI2Scanner::IsCleaningSupported()
{
 return CESCI2Accessor::IsCleaningSupported();
}
bool CESCI2Scanner::IsCalibrationSupported()
{
 return CESCI2Accessor::IsCleaningSupported();
}
bool CESCI2Scanner::IsCaptureCommandSupported()
{
 return CESCI2Accessor::IsCaptureCommandSupported();
}
ESErrorCode CESCI2Scanner::SetCaptureCommandSupported( bool bSupported )
{
 return CESCI2Accessor::SetCaptureCommandSupported( bSupported );
}
