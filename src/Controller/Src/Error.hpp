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
//  Error.hpp -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
namespace epsonscan {
  class Error
  {
  };
  class RuntimeError : public Error, public boost::exception, public std::runtime_error
  {
   public:
    RuntimeError(const char* message) : std::runtime_error(message)
    {
    }
    RuntimeError(const char* message, SDIError error) : std::runtime_error(message), error_(error)
    {
    }
    SDIError GetCode()
    {
     return error_;
    }
   private:
    SDIError error_ = kSDIErrorUnknownError;
  };
  #define ES_REQUIRE(expression, string) { if (!(expression)) { BOOST_THROW_EXCEPTION(RuntimeError(string)); } }
}
