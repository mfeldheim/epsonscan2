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
//  ESCI2Command.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "CommonUtility/utils/ESBuffer.h"
#include "Command/Base/CommandBase.h"
#include "ESCI2Defs.h"
#include "ESCI2DataConstructor.h"
#include "ESCI2DataEnumerator.h"
class CESCI2Command : public CCommandBase
{
public:
 CESCI2Command();
 virtual ~CESCI2Command();
 virtual ESErrorCode Initialize();
public:
 static ESStringA FCCSTR( const UInt32 un32CmdId );
 static UInt32 FourCharCode( const ESStringA strCode );
protected:
 virtual bool IsAuthenticationSupported() = 0;
 virtual ESString GetAuthUserName() = 0;
 virtual bool IsAuthenticationEnabled() = 0;
 virtual ESString GetAuthPassword() = 0;
 virtual ESString GetProductName() = 0;
 virtual ESFunctionalUnitType GetFunctionalUnitType() = 0;
 virtual ESNumber GetDeviceMaxBufferSize() = 0;
 virtual ST_ES_RECT_UN32 GetScanAreaInPixel() = 0;
 virtual bool IsDuplexEnabled() = 0;
 virtual bool IsAdminLockSupported() = 0;
 virtual ENUM_ES_HASH_TYPE GetMaintenanceHashType() = 0;
 virtual bool IsAdminLockEnabled() = 0;
 virtual bool IsAdminLockEnabledWithUnlockTest(bool bUnlockTest) = 0;
 virtual ESString GetAdminLockPassword() = 0;
 virtual bool RequestingUnlockAdminLock() = 0;
 virtual ESErrorCode SetAdminLockPassword(ESString strPassword) = 0;
 bool IsRetry();
 bool IsShouldSyncFunctionalUnit();
 bool IsShouldKeepControlMode();
 bool IsShouldZeroClearEdgeFillForFB();
 bool IsShouldIgnoreDateAndTime();
 bool IsShouldSendStatAfterADFScan();
 ESErrorCode SyncFunctionalUnit();
    virtual bool IsFeedTypeADF() = 0;
    virtual bool IsAdfLoadSupported() = 0 ;
    virtual bool IsAutoCroppingEnabled() = 0;
 virtual bool IsAutoCroppingInscribedEnabled() = 0;
    virtual bool IsSkewCorrectionEnabled() =0;
    virtual ESNumber GetBackGroundRemoval() = 0;
private:
 ESErrorCode SendRequest ( __in ESCI2RequestCode eRequestCode, __in_opt ESByteData* pParamData );
 ESErrorCode ReceiveReply( __inout ESCI2RequestCode& eRequestCode, __out_opt ESDictionaryA* pDicOutHeaderInfo, __out_opt ES_CMN_FUNCS::BUFFER::CESHeapBuffer* pOutDataBuffer );
 ESErrorCode RunSequence ( __in ESCI2RequestCode eRequestCode, __in_opt ESByteData* pParamBlock, __out_opt ESDictionaryA* pDicOutHeaderInfo, __out_opt ES_CMN_FUNCS::BUFFER::CESHeapBuffer* pOutDataBuffer );
protected:
 ESErrorCode RequestScannerControl();
 ESErrorCode RequestScannerInquiry();
 ESErrorCode RequestScannerMaintenance();
 ESErrorCode RequestFinalize();
 ESErrorCode RequestMechanicalControlWithParameter( ESByteData& parameter );
 enum {
  kModeNone = 0,
  kModeControl = (1 << 0),
  kModeInquiry = (1 << 1),
  kModeMaintenance = (1 << 2),
 };
 typedef UInt8 ESCI2Mode;
 ESCI2Mode GetMode();
 ESErrorCode SetMode( ESCI2Mode eMode );
 ESByteData ParameterDataWithDict( ESDictionaryA& dicParameters, UInt32 un32MaxSize, ESStringArrayA& arOutProcessedKeys );
 ESByteData MaintenanceParameterDataWithDict( ESDictionaryA& dicParameters, UInt32 un32MaxSize, ESStringArrayA& arOutProcessedKeys );
 ESErrorCode RequestRunSequence( ESCI2RequestCode eRequestCode, ESCI2Mode eMode, ESByteData* pParamBlock, const ESDictionaryA& dicRules, ESDictionaryA& dicOutResult );
 ESErrorCode WaitUntilDone();
protected:
 ESErrorCode StartScanning();
 ESErrorCode RequestImage( ESDictionaryA& dicHeaderInfo, ES_CMN_FUNCS::BUFFER::CESHeapBuffer& cOutBuffer );
 ESErrorCode RequestCancel();
    ESErrorCode RequestAdministratorLock(bool bModeOn, const ESString &password);
 ESErrorCode RequestAfmMode( bool bModeOn );
 ESErrorCode RequestPanelToPushScanReady( bool bPushScanReady );
 ESErrorCode RequestJobMode( UInt32 un32JobMode );
 ESErrorCode GetInfo( __out ESDictionaryA& dicOutInfo );
 ESErrorCode GetMaintenanceInfo( __out ESDictionaryA& dicOutMaintenanceInfo );
 ESErrorCode GetMaintenanceStatus( __out ESDictionaryA& dicOutStatus );
 ESErrorCode GetExtInfo( __out ESDictionaryA& dicOutExtInfo );
 ESErrorCode GetCapabilities( __out ESDictionaryA& dicOutCapability );
 ESErrorCode GetMaintenanceCapabilities( __out ESDictionaryA& dicOutMaintenanceCapability );
 ESErrorCode GetStatus( __out ESDictionaryA& dicOutStatus );
 ESErrorCode GetResults( __out ESDictionaryA& dicOutResults, __in_opt ESStringArrayA* pStrarKeys );
 ESErrorCode GetMaintenanceResults( __out ESDictionaryA& dicOutResults, __in_opt ESStringArrayA* pStrarKeys );
 ESErrorCode SendParameters( __in ESDictionaryA dicParameters );
 ESErrorCode SendMaintenanceParameters( __in ESDictionaryA dicParameters );
    const ESDictionaryA& HeaderPaseRule();
    const ESDictionaryA& CapabilitiesPaseRule();
    const ESDictionaryA& GetMaintenanceCapabilitiesPaseRule();
    const ESDictionaryA& GetInfoPaseRule();
    const ESDictionaryA& GetMaintenanceInfoPaseRule();
    const ESDictionaryA& GetStatusPaseRule();
    const ESDictionaryA& GetResultsPaseRule();
    const ESDictionaryA& GetMaintenanceResultsPaseRule();
protected:
 class CESCI2DataEnumeratorDataSource : public IESCI2DataEnumeratorDataSource
 {
 public:
  CESCI2DataEnumeratorDataSource();
  ~CESCI2DataEnumeratorDataSource();
  void Init(CESCI2Command* pParent );
  virtual UInt32 ReadFromEnumerator( CESCI2DataEnumerator* pSender, PESByte pBuffer, UInt32 un32Length );
 protected:
  CESCI2Command* m_pParent;
 };
protected:
 bool m_bIsRetry;
 ESCI2Mode m_eESCI2Mode;
 CESCI2DataEnumeratorDataSource m_cEnumeratorDataSource;
 ESDictionaryA m_dicMaintenanceResults;
 bool m_bIsAllowAuthError;
 bool m_bIsTransferring;
    ESDictionaryA m_dicHeaderPaseRule;
    ESDictionaryA m_dicCapabilitiesPaseRule;
    ESDictionaryA m_dicMaintenanceCapabilitiesPaseRule;
    ESDictionaryA m_dicInfoPaseRule;
    ESDictionaryA m_dicMaintenanceInfoPaseRule;
    ESDictionaryA m_dicStatusPaseRule;
    ESDictionaryA m_dicResultsPaseRule;
    ESDictionaryA m_dicMaintenanceResultsPaseRule;
};
