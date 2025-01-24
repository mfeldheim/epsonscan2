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
//  TransferCompression.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "TransferCompression.hpp"
#include "Scanner.hpp"
#include <ES2Command/ES2CommandAPI.h>
namespace epsonscan {
void TransferCompression::SetValue(const SDIInt& intVal)
{
 current_ = intVal;
}
void TransferCompression::Reset()
{
 current_ = SupportCompressionTransfer();
}
void TransferCompression::GetValue(SDIInt& intVal)
{
 intVal = current_;
}
void TransferCompression::GetCapability(SDICapability &capability)
{
 SetDefaultListCapability(capability);
 ESIndexSet availableTransferCompression;
 capability.supportLevel = kSDISupportLevelNone;
 if (SupportCompressionTransfer() && SupportRAWTransfer())
 {
  AddList(capability, kSDITransferCompressionJPEG);
  AddAllList(capability, kSDITransferCompressionJPEG);
  AddList(capability, kSDITransferCompressionRAW);
  AddAllList(capability, kSDITransferCompressionRAW);
  capability.supportLevel = kSDISupportLevelAvailable;
 }else{
  capability.supportLevel = kSDISupportLevelNone;
 }
}
ESDictionary TransferCompression::GetEngineKeyValues()
{
 auto dict = ESDictionary();
 if (SupportCompressionTransfer() && SupportRAWTransfer() == false)
 {
  dict[kESImageFormat] = (ESNumber)kESImageFormatJPEG;
 }else if (SupportCompressionTransfer() == false && SupportRAWTransfer())
 {
  dict[kESImageFormat] = (ESNumber)kESImageFormatRaw;
 }else{
  if (current_)
  {
   dict[kESImageFormat] = (ESNumber)kESImageFormatJPEG;
  }else{
   dict[kESImageFormat] = (ESNumber)kESImageFormatRaw;
  }
 }
  ESNumber commandType = kPrvHRD_CommandType_ESCI2;
  dataProvider_->GetModelInfo()->GetValue(kPrvHRD_CommandType, commandType);
  if (commandType == kPrvHRD_CommandType_ESCI2)
  {
   ESNumber bufferSize = 0;
   dataProvider_->GetModelInfo()->GetValue(kPrvHRD_I2BSZ, bufferSize);
   if (bufferSize == 0)
   {
    dict[kESBufferSize] = (ESNumber)1048576;
   }else{
    dict[kESBufferSize] = (ESNumber)bufferSize;
   }
  }else{
   dict[kESBufferSize] = 262144;
  }
 return dict;
}
bool TransferCompression::SupportCompressionTransfer()
{
 ESIndexSet availableTransferCompression;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESImageFormat, availableTransferCompression))
 {
  if (availableTransferCompression.find(kESImageFormatJPEG) != availableTransferCompression.end())
     {
   return true;
  }
  else {
   return false;
  }
 }
 return false;
}
bool TransferCompression::SupportRAWTransfer()
{
 ESIndexSet availableTransferCompression;
 Scanner* scanner = dataProvider_->GetScanner().get();
 if(scanner && scanner->GetAvailableValueForKey(kESImageFormat, availableTransferCompression))
 {
  if (availableTransferCompression.find(kESImageFormatRaw) != availableTransferCompression.end())
     {
   return true;
  }
  else {
   return false;
  }
 }
 return false;
}
}
