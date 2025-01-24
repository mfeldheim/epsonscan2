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
//  JsonCommon.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <cstdio>
#include "../ESJsonUtils.h"
using namespace rapidjson;
typedef GenericDocument< UTF16<> > Document16;
typedef GenericValue< UTF16<> > Value16;
typedef GenericStringStream< UTF16<> > StringStream16;
typedef EncodedInputStream< UTF16<>, FileReadStream > EncodedInputStream16;
typedef EncodedOutputStream< UTF16LE<>, FileWriteStream > EncodedOutputStream16LE;
typedef GenericStringBuffer< UTF16<> > StringBuffer16;
typedef PrettyWriter< StringBuffer16, UTF16<>, UTF16<> > BufferWriter16;
typedef EncodedOutputStream16LE EncodeStream16;
typedef PrettyWriter< EncodeStream16, UTF16LE<>, UTF16<> > FileWriter16;
typedef GenericDocument< UTF8<> > Document8;
typedef GenericValue< UTF8<> > Value8;
typedef GenericStringStream< UTF8<> > StringStream8;
typedef EncodedInputStream< UTF8<>, FileReadStream > EncodedInputStream8;
typedef EncodedOutputStream< UTF8<>, FileWriteStream > EncodedOutputStream8;
typedef GenericStringBuffer< UTF8<> > StringBuffer8;
typedef PrettyWriter< StringBuffer8, UTF8<>, UTF8<> > BufferWriter8;
typedef EncodedOutputStream8 EncodeStream8;
typedef PrettyWriter< EncodeStream8, UTF8<> > FileWriter8;
