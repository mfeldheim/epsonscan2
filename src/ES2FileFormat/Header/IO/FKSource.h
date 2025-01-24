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
//  FKSource.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "FileFormatKit.h"
typedef std::vector< ESDictionary > FKDictArray;
class CFKSource : public IFKSource
{
private:
 ES_CMN_FUNCS::BUFFER::CESHeapBuffer m_cSource;
 FKSourceType m_eType;
 BOOL m_bFull;
public:
 CFKSource();
 virtual ~CFKSource();
 FKSourceType GetFKSourceType() const override
 {
  return m_eType;
 }
 BOOL IsFull() const override
 {
  return m_bFull;
 }
 ES_CMN_FUNCS::BUFFER::IESBuffer& GetSource( );
 static IFKSource* CreateAndInitInstanceWithType(FKSourceType eSourceType, ES_CMN_FUNCS::BUFFER::IESBuffer& vpSource, BOOL bIsFull);
 void Destroy() override{
  delete this;
 }
 const ES_CMN_FUNCS::BUFFER::IESBuffer& GetConstSource( ) const override;
};
