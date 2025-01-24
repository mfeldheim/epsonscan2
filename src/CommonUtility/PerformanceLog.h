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
//  PerformanceLog.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#if 0
 namespace
 {
  #include <sstream>
  class stopwatch
  {
  public:
   explicit stopwatch(const std::string& message):message_(message)
   {
    std::stringstream ss;
    ss << "@,>>,[" << message_.c_str() << "],";
    OutputDebugStringA(ss.str().c_str());
    QueryPerformanceFrequency(&freq_);
    QueryPerformanceCounter(&begin_);
   }
   explicit stopwatch(const std::string& message, const std::string& key):message_(message)
   {
    std::stringstream ss;
    ss << "@,>>,[" << message_.c_str() << ":" << key.c_str() <<"],";
    OutputDebugStringA(ss.str().c_str());
    QueryPerformanceFrequency(&freq_);
    QueryPerformanceCounter(&begin_);
   }
   ~stopwatch()
   {
    QueryPerformanceCounter(&end_);
    std::stringstream ss;
    ss << "@,<<,[" << message_.c_str() << "],";
    ss << int(double(end_.QuadPart - begin_.QuadPart) * 1000.0 / double(freq_.QuadPart));
    OutputDebugStringA(ss.str().c_str());
   }
  private:
   LARGE_INTEGER freq_;
   LARGE_INTEGER begin_;
   LARGE_INTEGER end_;
   std::string message_;
  };
  #define INTERVALTIME_LOG ::stopwatch stopwatch_(__FUNCTION__);
 };
#else
  #define INTERVALTIME_LOG ;
#endif
