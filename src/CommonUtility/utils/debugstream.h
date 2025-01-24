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
//  debugstream.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>
template <class CharT, class TraitsT = std::char_traits<CharT> >
class basic_debugbuf :
    public std::basic_stringbuf<CharT, TraitsT>
{
public:
    virtual ~basic_debugbuf()
    {
        sync();
    }
protected:
    int sync()
    {
        output_debug_string(str().c_str());
        str(std::basic_string<CharT>());
        return 0;
    }
    void output_debug_string(const CharT *text) {}
};
template<>
void basic_debugbuf<char>::output_debug_string(const char *text)
{
    ::OutputDebugStringA(text);
}
template<>
void basic_debugbuf<char_t>::output_debug_string(const char_t *text)
{
    ::OutputDebugStringW(text);
}
template<class CharT, class TraitsT = std::char_traits<CharT> >
class basic_dostream :
    public std::basic_ostream<CharT, TraitsT>
{
public:
    basic_dostream() : std::basic_ostream<CharT, TraitsT>
                (new basic_debugbuf<CharT, TraitsT>()) {}
    ~basic_dostream()
    {
        delete rdbuf();
    }
};
typedef basic_dostream<char> dostream;
typedef basic_dostream<wchar_t> wdostream;
