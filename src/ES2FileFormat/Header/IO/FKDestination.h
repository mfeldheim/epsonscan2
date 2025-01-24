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
//  FKDestination.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FileFormatKit.h"
class CFKDestination;
class CFKDestination : public IFKDestination
{
private:
 FKDestinationType m_eFKDestinationType;
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_cSource;
 ESImageInfo m_dictImageInfo;;
 IFKDestinationDelegate* m_pcDelegate;
public:
 CFKDestination();
 ~CFKDestination();
 FKDestinationType GetFKDestinationType()
 {
  return m_eFKDestinationType;
 }
 ES_CMN_FUNCS::BUFFER::IESBuffer& GetSource();
 void SetDelegate(IFKDestinationDelegate* piDelegate){
  m_pcDelegate = piDelegate ;
 }
 void SetUserData(const ESImageInfo& dictImageInfo){
  m_dictImageInfo = dictImageInfo;
 }
 ESImageInfo GetUserData(void){
  return m_dictImageInfo;
 }
 virtual void SetUserDataAsJson(ES_CHAR_CPTR pszUserDataAsJson) override;
 virtual void GetUserDataAsJson(IESResultString& pszUserDataAsJson) override;
 static IFKDestination* CreateAndInitInstanceWithType( FKDestinationType eType, ES_CMN_FUNCS::BUFFER::IESBuffer& cSource );
 void NotifyDidBeginReceivingForImageInfo( ES_CHAR_CPTR pszImageInfoAsJson );
 void NotifyDidEndReceivingForImageInfo( ES_CHAR_CPTR pszImageInfoAsJson );
 void NotifyReceiveImageData( ES_CMN_FUNCS::BUFFER::IESBuffer& cData, ES_CHAR_CPTR pszImageInfoAsJson ) override;
 void Destroy(){
  delete this;
 }
};
