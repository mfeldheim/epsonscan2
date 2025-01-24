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
//  test.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include <stdio.h>
#include <iostream>
#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>
#include <utils/ESBuffer.h>
#include "Emulator.h"
class MyDelegateReciver : public IESScannerDelegate
{
 virtual void CALLBACK ScannerWillBeginContinuousScanning(IESScanner* pScanner)
  {
  }
 virtual void CALLBACK ScannerDidEndContinuousScanning(IESScanner* pScanenr)
  {
  }
 virtual void CALLBACK ScannerWillScanToScannedImage( IESScanner* pScanner, IESScannedImage* pESImage )
  {
  }
 virtual void CALLBACK ScannerDidScanToScannedImage( IESScanner* pScanner, IESScannedImage* pESImage )
  {
  }
 virtual void CALLBACK ScannerWillCancelScanning( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK ScannerDidCancelScanning( IESScanner* pScanner)
  {
  }
 virtual void CALLBACK ScannerDidCompleteScanningWithError( IESScanner* pScanner, ESErrorCode err)
  {
  }
 virtual void CALLBACK ScannerDidInterruptScanningWithError(IESScanner* pcScanner ,ESErrorCode err)
  {
  }
 virtual void CALLBACK ScannerDidEncounterDeviceCommunicationError( IESScanner* pScanner, ESErrorCode err )
  {
  }
 virtual void CALLBACK ScannerWillWarmUp( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK ScannerDidWarmUp( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK NetworkScannerDidRequestStartScanning( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK NetworkScannerDidRequestStopScanning( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK ScannerDidDisconnect( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK NetworkScannerDidReceiveServerError( IESScanner* pScanner )
  {
  }
 virtual BOOL CALLBACK NetworkScannerShouldPreventTimeout( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK NetworkScannerDidTimeout( IESScanner* pScanner )
  {
  }
 virtual void CALLBACK ScannerIsReservedByHost( IESScanner* pScanner, const ES_CHAR* pszAddress )
  {
  }
 virtual void CALLBACK ScannerDidPressButton( UInt8 un8ButtonNumber )
  {
  }
 virtual void CALLBACK ScannerDidRequestStop(IESScanner *pScanner)
  {
  }
};
int main(int argc, char const *argv[]) {
  ESString str;
  ESDictionary dict;
  ESNumber PreviousPageNum = 0;
  dict["DisplayName"] = (ESString)"DS-7000";
  dict["modelID"] = (ESNumber)0x13C;
  dict["type"] = (ESNumber)1;
  dict["Label"] = (ESString)"USB Device Label";
  ESDictionary dict2;
  dict2["ConnectionSetting"] = dict;
  ES_CMN_FUNCS::JSON::DictionaryToJSON(dict2, str);
  printf("%s", str.c_str());
  Emulator *test_emu = new Emulator();
  test_emu->SetConnection(str.c_str());
  test_emu->SetValuesWithJSON(str.c_str());
  MyDelegateReciver *rec = new MyDelegateReciver();
  test_emu->SetDelegate(rec);
  test_emu->Open();
  test_emu->SetLoadingPaperNum(1);
  test_emu->Scan();
  if(test_emu->IsOpened()){
    test_emu->Close();
    test_emu->DestroyInstance();
    test_emu = NULL;
    delete rec;
  }
  return 0;
}
