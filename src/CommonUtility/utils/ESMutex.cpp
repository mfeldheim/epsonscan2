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
//  ESMutex.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "stdafx.h"
#include "ESMutex.h"
#include "DbgLog.h"
CESMutex::CESMutex(void)
{
 m_hMutex = NULL;
}
CESMutex::~CESMutex(void)
{
 if(m_hMutex){
#ifdef WIN32
  ::CloseHandle(m_hMutex);
#else
  CloseHandle(m_hMutex);
#endif
 }
}
BOOL CESMutex::InitMutex(LPCTSTR strMutexName,BOOL* pbAlreadyExist){
 if(m_hMutex == NULL){
#ifdef WIN32
  SECURITY_DESCRIPTOR sd = {0};
  SECURITY_ATTRIBUTES secAttribute = {0};
  if(InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION)){
   if(SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE)){
    secAttribute.nLength = sizeof (secAttribute);
    secAttribute.lpSecurityDescriptor = &sd;
    secAttribute.bInheritHandle = TRUE;
   }
  }
  m_hMutex = ::CreateMutex(&secAttribute, FALSE, strMutexName);
#else
  pthread_mutexattr_t mat;
   pthread_mutexattr_init(&mat);
   if (pthread_mutexattr_setpshared(&mat, PTHREAD_PROCESS_SHARED) != 0) {
     return FALSE;
   }
  pthread_mutex_init((pthread_mutex_t *)m_hMutex, &mat);
#endif
#ifdef WIN32
  if(m_hMutex && pbAlreadyExist ){
   if(GetLastError() == ERROR_ALREADY_EXISTS){
    *pbAlreadyExist = TRUE;
   }else{
    *pbAlreadyExist = FALSE;
   }
  }
#endif
  if(m_hMutex == NULL)
  {
   ES_Error_Log(this,ES_STRING("CreateMutexFail[%s]"),strMutexName);
  }else{
   ES_Info_Log(this,ES_STRING("CreateMutexSuccess[%08X][%s]"),m_hMutex,strMutexName);
  }
 }
 return m_hMutex != NULL;
}
BOOL CESMutex::IsExistMutex(LPCTSTR strMutexName){
 BOOL bExist = FALSE;
#ifdef WIN32
 HANDLE hmutex = OpenMutex(MUTEX_ALL_ACCESS , FALSE , strMutexName);
 if(hmutex){
  bExist = TRUE;
  CloseHandle(hmutex);
 }
#else
 assert(FALSE);
#endif
 return bExist;
}
BOOL CESMutex::EnterMutex(){
 if(m_hMutex != NULL){
#ifdef WIN32
  ::ES2WaitForSingleObject(m_hMutex,INFINITE);
#else
  ES2WaitForSingleObject(m_hMutex,INFINITE);
#endif
  return TRUE;
 }
 return FALSE;
}
void CESMutex::Release(){
 if(m_hMutex){
#ifdef WIN32
  ReleaseMutex(m_hMutex);
#else
  pthread_mutex_destroy((pthread_mutex_t *)m_hMutex);
#endif
 }
}
void CESMutex::CloseMutex(){
 if(m_hMutex){
#ifdef WIN32
  ::CloseHandle(m_hMutex);
#else
  CloseHandle(m_hMutex);
#endif
  m_hMutex = NULL;
 }
}
