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
//  CommandBase.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include <sys/syscall.h>
#include "CommandBase.h"
#include "Include/ES2Command/ES2CommandAPI.h"
#include "Interface/IInterface.h"
#include "CommonUtility/utils/PathUtils.h"
#if defined(__ANDROID__) || TARGET_OS_IPHONE || defined(TARGET_OS_EMBEDDED)
#include "sha1.h"
#else
#include "../../../thirdparty/sha1/sha1.h"
#endif
CCommandBase::CCommandBase()
{
 m_pDevInterface = nullptr;
 m_pDelegate = nullptr;
 m_pScanner = nullptr;
 m_bCancelled = false;
 m_bScanning = false;
 m_bIsInterrupted = false;
 ES_CMN_FUNCS::PATH::ES_GetSystemTempDir( m_strWorkFolder );
}
CCommandBase::~CCommandBase()
{
 SYNCHRONIZED_START
 {
  if ( IsDeviceOpened() ){
   CloseDevice();
  }
  if (m_pDevInterface){
   m_pDevInterface->DestroyInstance();
   m_pDevInterface = nullptr;
  }
 }
 SYNCHRONIZED_END
}
void CCommandBase::SetDelegate( IESScannerDelegate* pDelegate, IESScanner* pScanner )
{
 {
  CBlockCriticalSection cBlockCriticalSection(m_cDelegateCriticalSection);
  m_pDelegate = pDelegate;
  m_pScanner = pScanner;
 }
}
IESScannerDelegate* CCommandBase::GetDelegate()
{
 {
  CBlockCriticalSection cBlockCriticalSection(m_cDelegateCriticalSection);
  return m_pDelegate;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerWillBeginContinuousScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerWillBeginContinuousScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidEndContinuousScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidEndContinuousScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerWillScanToScannedImage( IESScannedImage* pESImage )
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerWillScanToScannedImage( m_pScanner, pESImage );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidScanToScannedImage( IESScannedImage* pESImage )
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidScanToScannedImage( m_pScanner, pESImage );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerWillCancelScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerWillCancelScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidCancelScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidCancelScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidCompleteScanningWithError( ESErrorCode err)
{
 ES_LOG_TRACE_FUNC();
 ES_INFO_LOG( ES_STRING("ScannerDidCompleteScanningWithError( %d )"), err );
 {
  if ( (err == kESErrorDataSendFailure) || (err == kESErrorDataReceiveFailure) ){
   DeviceDisconnected();
   CloseDevice();
  }
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidCompleteScanningWithError( m_pScanner, err );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidInterruptScanningWithError( ESErrorCode err )
{
 ES_LOG_TRACE_FUNC();
 {
  if ( (err == kESErrorDataSendFailure) || (err == kESErrorDataReceiveFailure) ){
   DeviceDisconnected();
   CloseDevice();
  }
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidInterruptScanningWithError( m_pScanner, err );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidEncounterDeviceCommunicationError( ESErrorCode err )
{
 ES_LOG_TRACE_FUNC();
 {
  {
   DeviceDisconnected();
   CloseDevice();
  }
  if(!IsScanning()){
   IESScannerDelegate* pDelegate = GetDelegate();
   if ( pDelegate == NULL ){
    ES_LOG_DELEGATE_NOT_REGISTERD();
    return kESErrorFatalError;
   }
   pDelegate->ScannerDidEncounterDeviceCommunicationError( m_pScanner, err );
  }
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerWillWarmUp()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerWillWarmUp( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidWarmUp()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidWarmUp( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateNetworkScannerDidRequestStartScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->NetworkScannerDidRequestStartScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateNetworkScannerDidRequestStopScanning()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->NetworkScannerDidRequestStopScanning( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidDisconnect()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidDisconnect( m_pScanner );
  ES_TRACE_LOG(ES_STRING("Leave CallDelegateScannerDidDisconnect"));
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateNetworkScannerDidReceiveServerError()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->NetworkScannerDidReceiveServerError( m_pScanner );
  return kESErrorNoError;
 }
}
BOOL CCommandBase::CallDelegateNetworkScannerShouldPreventTimeout()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return FALSE;
  }
  return pDelegate->NetworkScannerShouldPreventTimeout( m_pScanner );
 }
}
ESErrorCode CCommandBase::CallDelegateNetworkScannerScannerDidTimeout()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->NetworkScannerDidTimeout( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerIsReservedByHost( const ES_CHAR* pszAddress )
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerIsReservedByHost( m_pScanner, pszAddress );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidPressButton( UInt8 un8ButtonNumber )
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidPressButton( un8ButtonNumber );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidRequestStop()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidRequestStop( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidRequestPushScanConnection()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidRequestPushScanConnection( m_pScanner );
  return kESErrorNoError;
 }
}
ESErrorCode CCommandBase::CallDelegateScannerDidNotifyStatusChange()
{
 ES_LOG_TRACE_FUNC();
 {
  IESScannerDelegate* pDelegate = GetDelegate();
  if ( pDelegate == NULL ){
   ES_LOG_DELEGATE_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  pDelegate->ScannerDidNotifyStatusChange( m_pScanner );
  return kESErrorNoError;
 }
}
void CALLBACK CCommandBase::DidPressButton( UInt8 un8ButtonNumber )
{
 CallDelegateScannerDidPressButton( un8ButtonNumber );
}
void CALLBACK CCommandBase::DidRequestStartScanning()
{
 CallDelegateNetworkScannerDidRequestStartScanning();
}
void CALLBACK CCommandBase::DidRequestStopScanning()
{
 CallDelegateNetworkScannerDidRequestStopScanning();
}
void CALLBACK CCommandBase::DidRequestStartOrStop()
{
 if ( !IsScanning() ){
  CallDelegateNetworkScannerDidRequestStartScanning();
 } else {
  CallDelegateNetworkScannerDidRequestStopScanning();
 }
}
void CALLBACK CCommandBase::DidReceiveServerError()
{
 CallDelegateNetworkScannerDidReceiveServerError();
}
void CALLBACK CCommandBase::DidRequestStop()
{
 CallDelegateScannerDidRequestStop();
}
void CALLBACK CCommandBase::DidDisconnect()
{
 DeviceDisconnected();
 CallDelegateScannerDidDisconnect();
}
void CALLBACK CCommandBase::DidRequestPushScanConnection()
{
 CallDelegateScannerDidRequestPushScanConnection();
}
BOOL CALLBACK CCommandBase::ShouldPreventTimeout()
{
 return CallDelegateNetworkScannerShouldPreventTimeout();
}
void CALLBACK CCommandBase::DidTimeout()
{
 DeviceDisconnected();
 CallDelegateNetworkScannerScannerDidTimeout();
}
void CALLBACK CCommandBase::IsReservedByHost(IInterface* pDeviceInterface, const ES_CHAR* pszAddress )
{
 CallDelegateScannerIsReservedByHost( pszAddress );
}
void CALLBACK CCommandBase::DeviceCommunicationError( ESErrorCode err )
{
 CallDelegateScannerDidEncounterDeviceCommunicationError( err );
}
BOOL CALLBACK CCommandBase::ShouldStopScanning( IInterface* pDeviceInterface )
{
 return IsCancelled();
}
void CALLBACK CCommandBase::DidRequestGetImageData()
{
 ES_LOG_TRACE_FUNC();
}
void CALLBACK CCommandBase::DidNotifyStatusChange()
{
 CallDelegateScannerDidNotifyStatusChange();
}
ESErrorCode CCommandBase::SetDeviceInterface(IInterface* pDeviceInterface )
{
 SYNCHRONIZED_START
 {
  if (m_pDevInterface && m_pDevInterface != pDeviceInterface ){
   m_pDevInterface->SetDelegate(nullptr);
   m_pDevInterface->DestroyInstance();
   m_pDevInterface = nullptr;
  }
  if (pDeviceInterface){
   pDeviceInterface->SetDelegate( this );
  }
  m_pDevInterface = pDeviceInterface;
 }
 SYNCHRONIZED_END
 return kESErrorNoError;
}
ESErrorCode CCommandBase::OpenDevice()
{
 SYNCHRONIZED_START
 {
  if (!m_pDevInterface){
   ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  ESErrorCode err = m_pDevInterface->Open();
  if ( IS_ERR_CODE( err ) ){
   ES_LOG_FAILED_OPEN_DEVICE();
  }
  return err;
 }
 SYNCHRONIZED_END
}
ESErrorCode CCommandBase::CloseDevice()
{
 SYNCHRONIZED_START
 {
  if (!m_pDevInterface){
   ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
   return kESErrorFatalError;
  }
  m_pDevInterface->Close();
  return kESErrorNoError;
 }
 SYNCHRONIZED_END
}
IInterface* CCommandBase::GetDeviceInterface()
{
 SYNCHRONIZED_START
 {
  return m_pDevInterface;
 }
 SYNCHRONIZED_END
}
bool CCommandBase::IsDeviceOpened() const
{
 SYNCHRONIZED_START
 {
  if (!m_pDevInterface){
   ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
   return false;
  }
  return m_pDevInterface->IsOpened();
 }
 SYNCHRONIZED_END
}
void CCommandBase::DeviceDisconnected()
{
}
void CCommandBase::SetScanning( bool bScanning )
{
 m_bScanning = bScanning;
}
bool CCommandBase::IsScanning() const
{
 return m_bScanning;
}
void CCommandBase::SetCancelled( bool bCanncelled )
{
 m_bCancelled = bCanncelled;
}
bool CCommandBase::IsCancelled()
{
 return m_bCancelled;
}
void CCommandBase::SetInterrupted( bool bInterrupted )
{
 m_bIsInterrupted = bInterrupted;
}
bool CCommandBase::IsInterrupted() const
{
 return m_bIsInterrupted;
}
#if 0
ESErrorCode CCommandBase::Write( __in PESByte pBuf, __in UInt32 un32BufferLen )
{
 if ( pBuf == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorFatalError;
 }
 if ( m_pDevStream == NULL ){
  ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
  return kESErrorFatalError;
 }
 ESErrorCode err = m_pDevStream->Write( pBuf, un32BufferLen );
 if ( IS_ERR_CODE( err ) ){
  err = kESErrorDataSendFailure;
  ES_LOG_FAILED_WRITE_DATA();
  CallDelegateDidEncounterDeviceCommunicationError( err );
 }
 return err;
}
#endif
ESErrorCode CCommandBase::Write( __in PESByte pBuf, __in UInt32 un32BufferLen, __in UInt32 un32ComittedReadLength )
{
 if ( pBuf == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorFatalError;
 }
 if (!m_pDevInterface){
  ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
  return kESErrorFatalError;
 }
 ESErrorCode err = m_pDevInterface->Write( pBuf, un32BufferLen, un32ComittedReadLength );
 if ( IS_ERR_CODE( err ) ){
  err = kESErrorDataSendFailure;
  ES_LOG_FAILED_WRITE_DATA();
  if ( !IsScanning() ){
   CallDelegateScannerDidEncounterDeviceCommunicationError( err );
  }
 }
 return err;
}
ESErrorCode CCommandBase::Read( __out PESByte pOutBuf, __in UInt32 un32BufferLen )
{
 if ( pOutBuf == NULL ){
  ES_LOG_INVALID_INPUT_PARAM();
  return kESErrorFatalError;
 }
 if (!m_pDevInterface){
  ES_LOG_DEVICE_STREAM_NOT_REGISTERD();
  return kESErrorFatalError;
 }
 memset( pOutBuf, 0, un32BufferLen );
 ESErrorCode err = m_pDevInterface->Read( pOutBuf, un32BufferLen );
 if ( IS_ERR_CODE( err ) ){
  err = kESErrorDataReceiveFailure;
  ES_LOG_FAILED_READ_DATA();
  if ( !IsScanning() ){
   CallDelegateScannerDidEncounterDeviceCommunicationError( err );
  }
 }
 return err;
}
ESErrorCode CCommandBase::SendAck()
{
 ES_LOG_TRACE_FUNC();
 UInt8 rep = ACK;
 return Write( &rep, sizeof(rep), 0 );
}
ESErrorCode CCommandBase::ReceiveAck( __out ESByte& outAck )
{
 outAck = ACK;
 ESErrorCode err = Read( &outAck, sizeof(ESByte) );
 if ( IS_ERR_CODE( err ) ){
  ES_LOG_FAILED_READ_ACK();
  return err;
 }
 ES_INFO_LOG( ES_STRING("ack : %02xh"), outAck );
 return err;
}
ESErrorCode CCommandBase::CreateSha1HashedPasswordData( __in const ESStringA strAuthUserNameA, __in const ESStringA strPasswordDataA, __out ESByteData& bdPasswordData )
{
 if ( strAuthUserNameA.empty() || strAuthUserNameA.size() > MAX_USERNAME_LENGTH || strPasswordDataA.size() > HASH_DATA_SIZE ){
  ES_LOG_INVALID_SETTING_PARAM();
  return kESErrorInvalidParameter;
 }
 char szUser[ MAX_USERNAME_LENGTH + 1 ] = {0};
 char szHash[ HASH_DATA_SIZE + 1 ] = {0};
 ::memcpy_s( szUser, sizeof(szUser), strAuthUserNameA.c_str(), strAuthUserNameA.size() );
 ::memcpy_s( szHash, sizeof(szHash), strPasswordDataA.c_str(), strPasswordDataA.size() );
 SHA1Context sha = {0};
 BYTE byHash[ SHA1HashSize ] = {0};
 bdPasswordData.clear();
 bdPasswordData.resize( (MAX_USERNAME_LENGTH + SHA1HashSize), 0 );
 if ( SHA1Reset( &sha ) != shaSuccess ){
  ES_LOG_FAILED_MSG( ES_STRING("password encode"), ES_STRING("reset") );
  return kESErrorFatalError;
 }
 if ( SHA1Input( &sha, (const uint8_t *)szUser, (unsigned int)strlen(szUser)) != shaSuccess ) {
  ES_LOG_FAILED_MSG( ES_STRING("password encode"), ES_STRING("input user name") );
  return kESErrorFatalError;
 }
 if ( SHA1Input( &sha, (const uint8_t *)szHash, (unsigned int)strlen(szHash)) != shaSuccess ) {
  ES_LOG_FAILED_MSG( ES_STRING("password encode"), ES_STRING("input pass data") );
  return kESErrorFatalError;
 }
 if ( SHA1Result( &sha, byHash ) != shaSuccess ) {
  ES_LOG_FAILED_MSG( ES_STRING("password encode"), ES_STRING("result") );
  return kESErrorFatalError;
 }
 ::memcpy( &bdPasswordData[0], szUser, MAX_USERNAME_LENGTH );
 ::memcpy( &bdPasswordData[MAX_USERNAME_LENGTH], byHash, SHA1HashSize );
 return kESErrorNoError;
}
ESErrorCode CCommandBase::CreateSha1HashedData(__in const ESStringA strDataA, __out ESByteData& bdSha1HashData)
{
 if (strDataA.size() > HASH_DATA_SIZE){
  ES_LOG_INVALID_SETTING_PARAM();
  return kESErrorInvalidParameter;
 }
 char szHash[HASH_DATA_SIZE + 1] = { 0 };
 ::memcpy_s(szHash, sizeof(szHash), strDataA.c_str(), strDataA.size());
 SHA1Context sha = { 0 };
 BYTE byHash[SHA1HashSize] = { 0 };
 bdSha1HashData.clear();
 bdSha1HashData.resize(SHA1HashSize, 0);
 if (SHA1Reset(&sha) != shaSuccess){
  ES_LOG_FAILED_MSG(L"password encode", L"reset");
  return kESErrorFatalError;
 }
 if (SHA1Input(&sha, (const uint8_t *)szHash, strlen(szHash)) != shaSuccess) {
  ES_LOG_FAILED_MSG(L"password encode", L"input pass data");
  return kESErrorFatalError;
 }
 if (SHA1Result(&sha, byHash) != shaSuccess) {
  ES_LOG_FAILED_MSG(L"password encode", L"result");
  return kESErrorFatalError;
 }
 ::memcpy(&bdSha1HashData[0], byHash, SHA1HashSize);
 return kESErrorNoError;
}
ESErrorCode CCommandBase::CreateSha256HashedData(__in const ESStringA strPasswordDataA, __out ESByteData& bdPasswordData)
{
    char commandBuf[1024];
 uint8_t hashBuf[HASH_DATA_SIZE_32];
    uint8_t salt[HASH_SOLT_LENGTH];
    std::string hashOrigin = strPasswordDataA;
    std::string saltHex;
 {
#ifdef __x86_64
  syscall(318, (void*)salt, HASH_SOLT_LENGTH, 0);
#elif __i686
  syscall(355, (void*)salt, HASH_SOLT_LENGTH, 0);
#else
  syscall(SYS_getrandom, (void*)salt, HASH_SOLT_LENGTH, 0);
#endif
  for (uint8_t i = 0; i < HASH_SOLT_LENGTH; i++)
  {
   char buf[3];
   snprintf(buf, sizeof(buf), "%02x", salt[i]);
   saltHex += buf;
  }
 }
    {
  snprintf(commandBuf,
    sizeof(commandBuf),
             "/bin/bash -c \'echo -e \"%s\\c\" | openssl dgst -sha256 -binary -mac hmac -macopt hexkey:%s\'",
    hashOrigin.c_str(),
    saltHex.c_str());
  FILE* fp = popen(commandBuf, "r");
  if (fp)
  {
      fread((char*)hashBuf, 1, HASH_DATA_SIZE_32, fp);
   pclose(fp);
  }
 }
 {
  bdPasswordData.clear();
  bdPasswordData.resize((HASH_DATA_SIZE_32 + HASH_SOLT_LENGTH), 0);
  ::memcpy(&bdPasswordData[0], hashBuf, HASH_DATA_SIZE_32);
  ::memcpy(&bdPasswordData[HASH_DATA_SIZE_32], salt, HASH_SOLT_LENGTH);
 }
 return kESErrorNoError;
}
ESString CCommandBase::GetWorkFolder()
{
 return m_strWorkFolder;
}
ESErrorCode CCommandBase::SetWorkFolder( ESString strWorkFolder )
{
 if ( ES_CMN_FUNCS::PATH::ES_IsExistFolder( strWorkFolder ) ){
  m_strWorkFolder = strWorkFolder;
  return kESErrorNoError;
 } else {
  return kESErrorInvalidParameter;
 }
}
