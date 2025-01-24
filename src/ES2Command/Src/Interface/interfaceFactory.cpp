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
//  interfaceFactory.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
#include "Include/Config.h"
#endif
#include <Include/ES2Command/ESCommandProperties.h>
#include "interfaceFactory.h"
#include "interface.h"
#include "interfaceImpl.h"
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
#include "usb/usbInterfaceImpl.h"
#include "ipc/ipcInterfaceImpl.h"
#else
#if !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
#include "usb/androidUsbInterfaceImpl.h"
#endif
#include "network/androidNetworkInterface.h"
#endif
#include "CommonUtility/utils/ESJsonUtils.h"
#include "CommonUtility/utils/ESAnyCastUtils.h"
std::string ipc_interface_path(std::string name)
{
    try{
        if (name.find('/') == std::string::npos)
        {
#if !defined(__ANDROID__) && !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
            std::string path(EPSON_INSTALL_PATH);
#else
            std::string path("");
#endif
            if (!path.empty() && path[path.length()-1] != '/'){
                path += '/';
            }
            path += "non-free-exec/" + name;
            return path;
        }
    }
    catch(...){
    }
    return "";
}
class InterfaceImplFactory
{
public:
    static std::unique_ptr<IInterfaceImpl> Create(const ESConnectionType connection_type, const ESDictionary& dicSetting) {
#if defined(__ANDROID__) || TARGET_OS_IPHONE || defined(TARGET_OS_EMBEDDED)
        switch(connection_type) {
#if !TARGET_OS_IPHONE && !defined(TARGET_OS_EMBEDDED)
            case kESConnectionLocal: {
                std::unique_ptr<AndroidUSBInterfaceImpl> impl(new AndroidUSBInterfaceImpl());
                if (impl){
                    ESString interfacePointerAsString = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_INTERFACEPOINTER, ESString, "");
                    ESString deviceName = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_DEVICENAME, ESString, "");
                    jobject interface = (jobject)std::stol(interfacePointerAsString);
                    if (impl->Init(interface, deviceName) != kESErrorNoError){
                        return nullptr;
                    }
                }
                return std::move(impl);
            }
            break;
#endif
            case kESConnectionNetworkIS: {
                std::unique_ptr<AndroidNetworkInterface> impl(new AndroidNetworkInterface());
                if (impl){
                    ESString ipAddress = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_ADDRESS, ESString, "");
                    if (impl->Init(ipAddress) != kESErrorNoError){
                        return nullptr;
                    }
                }
                return std::move(impl);
            }
                break;
            default:
                return nullptr;
        }
        return nullptr;
#else
        switch(connection_type){
                    case kESConnectionLocal:
                        {
                            std::unique_ptr<USBInterfaceImpl> impl(new USBInterfaceImpl());
                            if (impl){
                                ESNumber vid = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_VID, ESNumber, 0);
                                ESNumber pid = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_PID, ESNumber, 0);
                                ESString deviceNumber = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_SERIAL_NUMBER, ESString, "");
                                if (deviceNumber.length() == 0)
                                {
                                    if (impl->Init(static_cast<UInt16>(vid), static_cast<UInt16>(pid)) != kESErrorNoError){
                                        return nullptr;
                                    }
                                }else{
                                   if (impl->Init(static_cast<UInt16>(vid), static_cast<UInt16>(pid), deviceNumber) != kESErrorNoError){
                                        return nullptr;
                                    }
                                }
                            }
                            return std::move(impl);
                        }
                        break;
                    case kESConnectionNetworkIS:
                    case kESConnectionNetworkNT:
                        {
                            const ESString* pAddress = SAFE_KEYS_DATA_CPTR(dicSetting, ES_CNCT_KEY_ADDRESS, ESString);
                            if (!pAddress){
                                return nullptr;
                            }
        #ifdef UNICODE
                            std::string address = ES_CMN_FUNCS::STRING::UnicodeToUTF8(*pAddress);
        #else
                            std::string address(*pAddress);
        #endif
                            ESNumber nConnectionTimeout_s = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_CONNECTION_TIMEOUT, ESNumber, -1);
                            ESNumber nTimeout_s = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_COMMUNICATION_TIMEOUT, ESNumber, -1);
                            std::unique_ptr<ipc::IPCInterfaceImpl> impl(new ipc::IPCInterfaceImpl(ipc_interface_path("es2netif")));
                            if (impl){
                                if (impl->Init("//" + address, nConnectionTimeout_s, nTimeout_s)){
                                    return nullptr;
                                }
                            }
                            return std::move(impl);
                        }
                        break;
                    case kESConnectionInterpreter:
                        {
                            const ESString* pInterpreterName = SAFE_KEYS_DATA_CPTR(dicSetting, ES_CNCT_KEY_INTERPRETER_NAME, ESString);
                            if (!pInterpreterName){
                                return nullptr;
                            }
        #ifdef UNICODE
                            std::string interpreter_name = ES_CMN_FUNCS::STRING::UnicodeToUTF8(*pInterpreterName);
        #else
                            std::string interpreter_name(*pInterpreterName);
        #endif
                            ESNumber vid = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_VID, ESNumber, 0);
                            ESNumber pid = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_PID, ESNumber, 0);
                            ESString deviceSerial = SAFE_ANY_VALUE_FROM_DICT(dicSetting, ES_CNCT_KEY_SERIAL_NUMBER, ESString, "");
                            std::ostringstream ss;
                            if(deviceSerial.length() == 0)
                            {
                            ss << "usb:";
                            ss << std::hex << vid << ":" << pid;
                            }
                            else
                            {
                            ss << "usb:";
                            ss << std::hex << vid << ":" << pid << ":";
                            ss << deviceSerial;
                            }
                            std::unique_ptr<ipc::IPCInterfaceImpl> impl(new ipc::IPCInterfaceImpl(ipc_interface_path(interpreter_name)));
                            if (impl){
                                if (impl->Init(ss.str(), 0, 0)){
                                    return nullptr;
                                }
                            }
                            return std::move(impl);
                        }
                        break;
                    default:
                        return nullptr;
                }
        #endif
        }
};
ESErrorCode InterfaceFactory::Create(const ES_CHAR* json, IInterface** ppInterface)
{
    if (!ppInterface){
        return kESErrorInvalidParameter;
    }
    *ppInterface = nullptr;
 if (!json || json[0] == ES_STRING('\0')) {
  return kESErrorInvalidParameter;
 }
    try{
  ESDictionary dicRoot;
  UInt32 un32ErrCounter = ES_CMN_FUNCS::JSON::JSONtoDictionary(json, dicRoot);
  assert(un32ErrCounter == 0);
  ESDictionary* pDicSetting = SAFE_KEYS_DATA_PTR(dicRoot, ES_CNCT_KEY_ROOT, ESDictionary);
  if (!pDicSetting) {
   return kESErrorInvalidParameter;
  }
        const ESConnectionType* connection_type = (ESConnectionType*)SAFE_KEYS_DATA_CPTR(*pDicSetting, ES_CNCT_KEY_TYPE, ESNumber);
  if (!connection_type) {
            return kESErrorInvalidParameter;
  }
        Interface* interface = new Interface(*connection_type, InterfaceImplFactory::Create(*connection_type, *pDicSetting));
        *ppInterface = interface;
        return kESErrorNoError;
    } catch(const std::bad_alloc&){
  return kESErrorMemoryError;
 } catch( const std::invalid_argument& ){
  return kESErrorInvalidParameter;
    } catch(...) {
  return kESErrorFatalError;
    }
}
