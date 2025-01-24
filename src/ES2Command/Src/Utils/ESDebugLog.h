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
//  ESDebugLog.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#if 1
#include "CommonUtility/DbgLog.h"
#include "CommonUtility/utils/ESAnyCastUtils.h"
#define ES_TRACE_LOG(msg,...) ES_Trace_Log2( __FUNCTION__, msg, ##__VA_ARGS__ );
#define ES_INFO_LOG(msg,...) ES_Info_Log2( __FUNCTION__, msg, ##__VA_ARGS__ );
#define ES_WARM_LOG(msg,...) ES_Warning_Log2( __FUNCTION__, msg, ##__VA_ARGS__ );
#define ES_ERROR_LOG(msg,...) ES_Error_Log2( __FUNCTION__, msg, ##__VA_ARGS__ );
#define ES_LOG_MEMORY_ALLOCATE_ERROR() ES_ERROR_LOG( ES_STRING("Memory allocate error.") )
#define ES_LOG_EXCEPTION_ERROR() ES_ERROR_LOG( ES_STRING("Exception error.") )
#define ES_LOG_TIMEOUT_EXCEPTION_ERROR(e) \
 ESStringA strWhatA = e.what(); \
 if ( !strWhatA.empty() ){ \
  ESString strWhat = ES_CMN_FUNCS::STRING::ToESString(strWhatA); \
  ES_ERROR_LOG( strWhat.c_str() ) \
 } else { \
  ES_ERROR_LOG( ES_STRING("Timeout Exception error.") ) \
 }
#define ES_LOG_SOCKET_EXCEPTION_ERROR(e) \
 ESStringA strWhatA = e.what(); \
 if ( !strWhatA.empty() ){ \
  ESString strWhat = ES_CMN_FUNCS::STRING::ToESString(strWhatA); \
  ES_ERROR_LOG( strWhat.c_str() ) \
 } else { \
  ES_ERROR_LOG( ES_STRING("Socket Exception error.") ) \
 }
#define ES_LOG_CONNECTION_EXCEPTION_ERROR(e) \
 ESStringA strWhatA = e.what(); \
 if ( !strWhatA.empty() ){ \
  ESString strWhat = ES_CMN_FUNCS::STRING::ToESString(strWhatA); \
  ES_ERROR_LOG( strWhat.c_str() ) \
 } else { \
  ES_ERROR_LOG( ES_STRING("Connection Exception error.") ) \
 }
#define ES_LOG_INVALID_JSON_FORMAT(json) ES_ERROR_LOG( ES_STRING("Invalid JSON format.\n%s"), json )
#define ES_LOG_INVALID_MSG(name) ES_ERROR_LOG( ES_STRING("Invalid %s."), name )
#define ES_LOG_INVALID_INPUT_PARAM() ES_LOG_INVALID_MSG( ES_STRING("input parameter") )
#define ES_LOG_INVALID_COMMAND_TYPE_PARAM() ES_LOG_INVALID_MSG( ES_STRING("command type parameter") )
#define ES_LOG_INVALID_SETTING_PARAM() ES_LOG_INVALID_MSG( ES_STRING("setting parameter") )
#define ES_LOG_INVALID_SEQUENCE() ES_LOG_INVALID_MSG( ES_STRING("sequence") )
#define ES_LOG_INVALID_RESPONSE() ES_LOG_INVALID_MSG( ES_STRING("response") )
#define ES_LOG_INVALID_STATUS() ES_LOG_INVALID_MSG( ES_STRING("status") )
#define ES_LOG_AUTH_FAILURE() ES_ERROR_LOG( ES_STRING("Auth Failure") )
#define ES_LOG_FAILED_MSG(task,name) ES_ERROR_LOG( ES_STRING("Failed %s %s."), task, name )
#define ES_LOG_FAILED_CREATE_DEVICE() ES_LOG_FAILED_MSG( ES_STRING("create"), ES_STRING("device instance") )
#define ES_LOG_FAILED_CREATE_IMAGE() ES_LOG_FAILED_MSG( ES_STRING("create"), ES_STRING("image instance") )
#define ES_LOG_FAILED_INITIALIZE_IMAGE() ES_LOG_FAILED_MSG( ES_STRING("initialize"), ES_STRING("image instance") )
#define ES_LOG_FAILED_OPEN_DEVICE() ES_LOG_FAILED_MSG( ES_STRING("open"), ES_STRING("device") )
#define ES_LOG_FAILED_WRITE_DATA() ES_LOG_FAILED_MSG( ES_STRING("write"), ES_STRING("data") )
#define ES_LOG_FAILED_READ_DATA() ES_LOG_FAILED_MSG( ES_STRING("read"), ES_STRING("data") )
#define ES_LOG_FAILED_READ_ACK() ES_LOG_FAILED_MSG( ES_STRING("read"), ES_STRING("ack") )
#define ES_LOG_FAILED_SEND_COMMAND() ES_LOG_FAILED_MSG( ES_STRING("send"), ES_STRING("command") )
#define ES_LOG_FAILED_PASE_DATA() ES_LOG_FAILED_MSG( ES_STRING("pase"), ES_STRING(" data") )
#define ES_LOG_FAILED_CONVERT_DATA() ES_LOG_FAILED_MSG( ES_STRING("convert"), ES_STRING(" data") )
#define ES_LOG_USERAUTH_ENABLED() ES_WARM_LOG( ES_STRING("User authentication function is enabled."))
#define ES_LOG_NOT_READY() ES_WARM_LOG( ES_STRING("Not ready.") )
#define ES_LOG_BUSY() ES_WARM_LOG( ES_STRING("Busy.") )
#define ES_LOG_NOT_REGISTERD_MSG(name) ES_WARM_LOG( ES_STRING("%s is not registered."), name )
#define ES_LOG_DELEGATE_NOT_REGISTERD() ES_LOG_NOT_REGISTERD_MSG( ES_STRING("Delegate") )
#define ES_LOG_DEVICE_STREAM_NOT_REGISTERD() ES_LOG_NOT_REGISTERD_MSG( ES_STRING("Device stream") )
#ifdef WIN32
#define ES_LOG_TRACE_FUNC() ES_TRACE_LOG( ES_STRING("ENTER : %s"), __FUNCTIONW__ )
#else
#define ES_LOG_TRACE_FUNC() ES_TRACE_LOG( ES_STRING("ENTER : %s"), __FUNCTION__ )
#endif
#else
#define ES_INFO_LOG(msg,...) __noop
#define ES_WARM_LOG(msg,...) __noop
#define ES_ERROR_LOG(msg,...) __noop
#define ES_LOG_MEMORY_ALLOCATE_ERROR() __noop
#define ES_LOG_EXCEPTION_ERROR() __noop
#define ES_LOG_TIMEOUT_EXCEPTION_ERROR(e) __noop
#define ES_LOG_SOCKET_EXCEPTION_ERROR(e) __noop
#define ES_LOG_CONNECTION_EXCEPTION_ERROR(e) __noop
#define ES_LOG_INVALID_JSON_FORMAT(json) __noop
#define ES_LOG_INVALID_MSG(name) __noop
#define ES_LOG_INVALID_INPUT_PARAM() __noop
#define ES_LOG_INVALID_COMMAND_TYPE_PARAM() __noop
#define ES_LOG_INVALID_SETTING_PARAM() __noop
#define ES_LOG_INVALID_SEQUENCE() __noop
#define ES_LOG_INVALID_RESPONSE() __noop
#define ES_LOG_INVALID_STATUS() __noop
#define ES_LOG_AUTH_FAILURE() __noop
#define ES_LOG_FAILED_MSG(task,name) __noop
#define ES_LOG_FAILED_CREATE_DEVICE() __noop
#define ES_LOG_FAILED_CREATE_IMAGE() __noop
#define ES_LOG_FAILED_INITIALIZE_IMAGE() __noop
#define ES_LOG_FAILED_OPEN_DEVICE() __noop
#define ES_LOG_FAILED_WRITE_DATA() __noop
#define ES_LOG_FAILED_READ_DATA() __noop
#define ES_LOG_FAILED_READ_ACK() __noop
#define ES_LOG_FAILED_SEND_COMMAND() __noop
#define ES_LOG_FAILED_PASE_DATA() __noop
#define ES_LOG_FAILED_CONVERT_DATA() __noop
#define ES_LOG_NOT_READY() __noop
#define ES_LOG_BUSY() __noop
#define ES_LOG_NOT_REGISTERD_MSG(name) __noop
#define ES_LOG_DELEGATE_NOT_REGISTERD() __noop
#define ES_LOG_DEVICE_STREAM_NOT_REGISTERD() __noop
#define ES_LOG_TRACE_FUNC() __noop
#endif
