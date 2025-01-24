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
//  Platform.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "Platform.h"
#include "CommonUtility/utils/PathUtils.h"
#include <fstream>
#ifndef WIN32
errno_t fopen_s(
    FILE** pFile,
    const char *filename,
    const char *mode
)
{
 errno_t err = 0;
 if ( (NULL == pFile)
  || (NULL == filename)
  || (NULL == mode)
  )
 {
  return EINVAL;
 }
 *pFile = NULL;
 *pFile = fopen(filename, mode);
 if (NULL == *pFile) {
  err = errno;
 }
 return err;
}
errno_t _wfopen_s(
     FILE** pFile,
     const wchar_t *filename,
     const wchar_t *mode)
{
 return 0;
}
int _wtoi( const wchar_t* str) {
 return 0;
}
float _wtof( const wchar_t* str) {
 return 0.0;
}
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
DWORD ES2WaitForSingleObject(
        HANDLE hHandle,
        DWORD dwMilliseconds
        )
{
 int rc = 0;
 if( (NULL == hHandle)
    || (INFINITE != dwMilliseconds)
    )
 {
  return WAIT_FAILED;
 }
 LPGLOBAL_HANDLE hGlobal = (LPGLOBAL_HANDLE) ((char*)hHandle - sizeof(GLOBAL_HANDLE));
 if (NULL == hGlobal) {
  return WAIT_FAILED;
 }
 switch(hGlobal->handle_ID)
 {
  case EVENT_HANDLE_ID:
  {
   LPEVENT_HANDLE hEventHandle = (LPEVENT_HANDLE) hHandle;
   rc = pthread_mutex_lock(&hEventHandle->mutex);
   if (0 != rc)
   {
    return WAIT_FAILED;
   }
   if (FALSE == hEventHandle->condstatus)
   {
    if (0 != pthread_cond_wait(&hEventHandle->cond, &hEventHandle->mutex))
    {
     pthread_mutex_unlock(&hEventHandle->mutex);
     return WAIT_FAILED;
    }
   }
   if (FALSE == hEventHandle->is_manual_reset) {
    hEventHandle->condstatus = FALSE;
   }
   rc = pthread_mutex_unlock(&hEventHandle->mutex);
   if (0 != rc)
   {
    return WAIT_FAILED;
   }
  }
   break;
  case THREAD_HANDLE_ID:
  {
   LPTHREAD_HANDLE hThreadHandle = (LPTHREAD_HANDLE) hHandle;
   if( (int)NULL == hThreadHandle->threadID ) {
    return WAIT_OBJECT_0;
   }
   int thread_status = 0;
   do
   {
    void* pStatus = 0;
    thread_status = pthread_tryjoin_np(hThreadHandle->threadID, (void**)&pStatus);
    if( EBUSY == thread_status ) {
     hThreadHandle->dwThreadStatus = STILL_ACTIVE;
     Sleep(100);
    }
    else
    {
     intptr_t lRet = (intptr_t)pStatus;
     hThreadHandle->dwThreadStatus = (DWORD)lRet;
     hThreadHandle->threadID = (int)NULL;
    }
   }
   while (EBUSY == thread_status);
  }
   break;
  default:
   break;
 }
 return WAIT_OBJECT_0;
}
#endif
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
DWORD ES2WaitForMultipleObjects(
        DWORD nCount,
        const HANDLE *lpHandles,
        BOOL fWaitAll,
        DWORD dwMilliseconds
        )
{
 DWORD dwRet = WAIT_OBJECT_0;
 if( (NULL == lpHandles)
    || (INFINITE != dwMilliseconds)
    || (FALSE == fWaitAll)
    )
 {
  return WAIT_FAILED;
 }
 for (DWORD i = 0; i < nCount; i++)
 {
  if ( WAIT_FAILED == ES2WaitForSingleObject((HANDLE)lpHandles[i], dwMilliseconds))
  {
   dwRet = WAIT_FAILED;
  }
 }
 return dwRet;
}
#endif
BOOL CloseHandle(HANDLE hObject)
{
 BOOL bReturn = TRUE;
 if( (NULL == hObject)
    || (INVALID_HANDLE_VALUE == hObject)
    )
 {
  return FALSE;
 }
 LPGLOBAL_HANDLE hGlobal = (LPGLOBAL_HANDLE) ((char*)hObject - sizeof(GLOBAL_HANDLE));
 if (NULL == hGlobal) {
  return FALSE;
 }
 try {
  switch (hGlobal->handle_ID) {
   case THREAD_HANDLE_ID:
   {
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
    ES2WaitForSingleObject(hObject, INFINITE);
    LPTHREAD_HANDLE pThreadHandle = (LPTHREAD_HANDLE)hObject;
    pThreadHandle->dwThreadStatus = 0;
    pThreadHandle->threadID = (int)NULL;
#endif
   }
    break;
   case EVENT_HANDLE_ID:
   {
    LPEVENT_HANDLE pEventHandle = (LPEVENT_HANDLE)hObject;
    pthread_mutex_destroy(&pEventHandle->mutex);
    pthread_cond_destroy(&pEventHandle->cond);
   }
    break;
   case FILE_HANDLE_ID:
   {
    LPFILE_HANDLE pFile = (LPFILE_HANDLE)hObject;
    close(pFile->fileDescriptor);
    pFile->fileDescriptor = 0;
   }
    break;
   default:
    break;
  }
 } catch (BOOL bRet) {
  bReturn = bRet;
 }
 free(hObject);
    return bReturn;
}
BOOL GetExitCodeThread( HANDLE hThread, DWORD *dwExitCode )
{
 if(NULL == hThread)
 {
  return FALSE;
 }
 LPTHREAD_HANDLE hThreadHandle = (LPTHREAD_HANDLE) hThread;
 if( (pthread_t)NULL == hThreadHandle->threadID ) {
  return FALSE;
 }
 int thread_status = pthread_kill( hThreadHandle->threadID, 0 );
 if( 0 == thread_status ) {
  hThreadHandle->dwThreadStatus = STILL_ACTIVE;
  *dwExitCode = hThreadHandle->dwThreadStatus;
  return TRUE;
 }
 else {
  *dwExitCode = 0;
  return FALSE;
 }
}
BOOL FreeLibrary(
     HMODULE hModule
)
{
 if (NULL == hModule)
 {
  return FALSE;
 }
 if(dlclose(hModule) == 0){
  return TRUE;
 }else {
  return FALSE;
 }
}
HMODULE LoadLibraryEx(
           LPCTSTR lpFileName,
           HANDLE hFile,
           DWORD dwFlags
                      )
{
 UNREFERENCED_PARAMETER(hFile);
 HMODULE hModule = NULL;
 if (NULL == lpFileName) {
  return NULL;
 }
 if (LOAD_WITH_ALTERED_SEARCH_PATH != dwFlags) {
  return NULL;
 }
 hModule = dlopen(lpFileName, RTLD_LAZY);
  return hModule;
}
HMODULE LoadLibrary(
                     LPCTSTR lpFileName
                     )
{
  HMODULE hModule = NULL;
 if (NULL == lpFileName) {
  return NULL;
 }
 hModule = dlopen(lpFileName, RTLD_LAZY);
 if (!hModule)
 {
    printf("%s", dlerror());
 }
  return hModule;
}
DWORD GetModuleFileName(LPTSTR lpFilename, DWORD buf_size)
{
 DWORD dwRet = 0;
    memset(lpFilename, 0, buf_size);
 readlink( "/proc/self/exe", lpFilename, buf_size - 1 );
 dwRet = (DWORD)strlen(lpFilename);
 return dwRet;
}
BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists){
  try {
  if(bFailIfExists){
   if (ES_CMN_FUNCS::PATH::ES_IsExistFile(lpNewFileName))
   {
    return FALSE;
   }
   std::ifstream src(lpExistingFileName, std::ios::binary);
   std::ofstream dst(lpNewFileName, std::ios::binary);
   dst << src.rdbuf();
   if ( src.fail() ) { return FALSE; }
   if ( dst.fail() ) { return FALSE; }
  }else
  {
   if (ES_CMN_FUNCS::PATH::ES_IsExistFile(lpNewFileName))
   {
    DeleteFile(lpNewFileName);
   }
   return CopyFile(lpExistingFileName, lpNewFileName, TRUE);
  }
  }
  catch (...) {
   return FALSE;
  }
  return TRUE;
}
BOOL
DeleteFile(LPCSTR lpFileName )
{
  if( remove( lpFileName ) != 0 ){
  return FALSE;
  }
  return TRUE;
}
errno_t strcat_s(
     char *strDestination,
     size_t numberOfElements,
     const char *strSource
)
{
 if (NULL == strDestination)
 {
  return EINVAL;
 }
 if (NULL == strSource)
 {
  strDestination[0] = (char)NULL;
  return EINVAL;
 }
 if ( (0 == numberOfElements)
  || (numberOfElements <= (strlen(strDestination) + strlen(strSource)))
  )
 {
  strDestination[0] = (char)NULL;
  return ERANGE;
 }
 strcat(strDestination, strSource);
 return 0;
}
errno_t _tcscat_s(
      TCHAR *strDestination,
      size_t numberOfElements,
      const TCHAR *strSource
      )
{
 return strcat_s(strDestination, numberOfElements, strSource);
}
errno_t memcpy_s(
     void *dest,
     size_t numberOfElements,
     const void *src,
     size_t count
      )
{
 if ((NULL == dest) || (0 == numberOfElements))
 {
  return EINVAL;
 }
 if (NULL == src)
 {
  dest = NULL;
  return EINVAL;
 }
 if (numberOfElements < count)
 {
  dest = NULL;
  return ERANGE;
 }
 memcpy(dest, src, count);
 return 0;
}
void Sleep(DWORD dwMillseconds)
{
 usleep(dwMillseconds * 1000);
}
#endif
