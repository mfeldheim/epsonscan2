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
//  FKDestination.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESJsonUtils.h"
#include "FKDestination.h"
CFKDestination::CFKDestination()
{
 m_pcDelegate = NULL;
 m_eFKDestinationType = kFKDestinationTypePath;
}
CFKDestination::~CFKDestination()
{
}
IFKDestination* CFKDestination::CreateAndInitInstanceWithType( FKDestinationType eType, ES_CMN_FUNCS::BUFFER::IESBuffer& cSource )
{
 CFKDestination* pcThis = (CFKDestination*) new (std::nothrow) CFKDestination();
 if(pcThis){
  pcThis->m_eFKDestinationType = eType;
  {
   pcThis->m_cSource.Attach(cSource);
  }
 }
 return pcThis;
}
void CFKDestination::SetUserDataAsJson(ES_CHAR_CPTR pszUserDataAsJson) {
 ESImageInfo info;
 if(pszUserDataAsJson){
  ES_IMAGE_INFO::MakeImageInfoFromJson(info,pszUserDataAsJson);
 }
 SetUserData(info);
}
void CFKDestination::GetUserDataAsJson(IESResultString& strUserDataAsJson) {
 const ESImageInfo& imageinfo = GetUserData();
 ESString strImageJson;
 ES_IMAGE_INFO::GetImageInfoAsJson(strImageJson,imageinfo);
 strUserDataAsJson.Set(strImageJson.c_str());
}
void CFKDestination::NotifyDidBeginReceivingForImageInfo( ES_CHAR_CPTR pszImageInfoAsJson )
{
 if(m_pcDelegate){
  m_pcDelegate->DestinationDidBeginReceiving( this, pszImageInfoAsJson );
 }
}
void CFKDestination::NotifyDidEndReceivingForImageInfo( ES_CHAR_CPTR pszImageInfoAsJson )
{
 if(m_pcDelegate){
  m_pcDelegate->DestinationDidEndReceiving( this, pszImageInfoAsJson );
 }
}
void CFKDestination::NotifyReceiveImageData( ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ES_CHAR_CPTR pszImageInfoAsJson )
{
 if(m_pcDelegate){
  m_pcDelegate->DestinationDidReceiveImageData( this, cData, pszImageInfoAsJson );
 }
}
ES_CMN_FUNCS::BUFFER::IESBuffer& CFKDestination::GetSource()
{
 return m_cSource;
}
