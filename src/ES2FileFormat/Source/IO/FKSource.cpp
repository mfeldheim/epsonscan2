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
//  FKSource.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "FKSource.h"
CFKSource::CFKSource()
{
 m_eType = kFKSourceTypePath;
 m_bFull = false;
}
CFKSource::~CFKSource()
{
}
IFKSource* CFKSource::CreateAndInitInstanceWithType(FKSourceType eSourceType, ES_CMN_FUNCS::BUFFER::IESBuffer& cSource, BOOL bIsFull)
{
 CFKSource* pcThis = (CFKSource*) new (std::nothrow) CFKSource();
 if(pcThis){
  pcThis->m_cSource.Attach(cSource);
  pcThis->m_bFull = bIsFull;
  pcThis->m_eType = eSourceType;
 }
 return pcThis;
}
ES_CMN_FUNCS::BUFFER::IESBuffer& CFKSource::GetSource()
{
 return m_cSource;
}
const ES_CMN_FUNCS::BUFFER::IESBuffer& CFKSource::GetConstSource() const
{
 return m_cSource;
}
