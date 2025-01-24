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
//  NetFinder.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "NetFinder.hpp"
#include "ModelInfo.hpp"
#include <iostream>
#include <vector>
#include <string.h>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "Utility.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <vector>
#include <algorithm>
namespace epsonscan {
 static const int32_t kBufSize = 1024;
 NetFinder::NetFinder() : cancelled_(false)
 {
 }
 void NetFinder::Reset() {
  SetCancelled(false);
 }
 void NetFinder::Start(NetFinderCallBack &didFindDeviceCallBack)
    {
  FILE *fp = nullptr;
  char buf[kBufSize];
  {
   if(system("which avahi-browse > /dev/null"))
   {
    SDI_TRACE_LOG("avahi browse not found");
    return;
   }
  }
  const char *cmdline = "avahi-browse -r -p -t _scanner._tcp 2>/dev/null";
  if ( (fp=popen(cmdline,"r")) == nullptr) {
   return;
  }
  try {
  while(fgets(buf, kBufSize, fp) != nullptr && cancelled_ == false) {
     std::vector<std::string> elements;
   const std::string line(buf);
    boost::split(elements, line, boost::is_any_of(std::string(";")));
            if (elements.size() > 9) {
    std::string netType = elements.at(2);
    if(netType == "IPv4" ){
     std::string resolved = elements.at(0);
     std::string note = elements.at(9);
     std::string ipAddr = elements.at(7);
     if (resolved == "=") {
      std::regex mdlRegex("mdl=([^\"]*)");
      std::smatch results;
      std::regex_search(note, results, mdlRegex);
      if (results.size() > 1) {
       std::string hostName = results.str(1) ;
       SDIDeviceInfo devInfo = {0};
       strncpy(devInfo.displayName, hostName.c_str(), MAX_DISPLAYNAME - 1);
       strncpy(devInfo.ipAddress, ipAddr.c_str(), MAX_IP_ADDR - 1);
       std::string modelID;
       if(ModelInfo::GetModelIDFromProductName(hostName.c_str(), modelID)){
        strncpy(const_cast<char*>(devInfo.modelID), modelID.c_str(), MAX_MODEL_ID - 1);
        didFindDeviceCallBack(devInfo);
       }
      }
     }
    }
   }
  }
  }catch(std::regex_error& error)
  {
   SDI_TRACE_LOG("regex_error = %s", error.what());
  }catch(...)
  {
  }
  pclose(fp);
 }
 void NetFinder::Stop()
 {
  SetCancelled(true);
 }
 void NetFinder::SetCancelled(bool cancelled)
 {
     mutex_.lock();
  cancelled_ = cancelled;
     mutex_.unlock();
 }
}
