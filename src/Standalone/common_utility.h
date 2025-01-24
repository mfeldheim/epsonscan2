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
//  common_utility.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H 
#endif
#include <string>
class StandAloneCommonUtility
{
public:
    char *StrShift( char *String, size_t nShift )
    {
        char *start = String;
        char *stop = String + strlen( String );
        memmove( start + nShift, start, stop-start+1 );
        return String + nShift;
    }
    std::string ReplaceString( char* String, const char *From, const char* To)
    {
           int StrLen = strlen( To ) + strlen( String );
           char destStr[StrLen + 1];
           memset(destStr, 0, StrLen + 1);
           memcpy(destStr, String, strlen( String ));
           StrReplace(destStr, From , To);
           return std::string(destStr);
    }
    void StrReplace( char* String, const char *From, const char* To )
    {
        int nToLen;
        int nFromLen;
        int nShift;
        char *start;
        char *stop;
        char *p;
        nToLen = strlen( To );
        nFromLen = strlen( From );
        nShift = nToLen - nFromLen;
        start = String;
        stop = String + strlen( String );
        while( NULL != ( p = strstr( start, From ) ) )
        {
            start = StrShift( p + nFromLen, nShift );
            stop = stop + nShift;
            memmove( p, To, nToLen );
        }
    }
    double PixelToMm(double input_num, int resolution)
    {
        int temp;
        input_num = input_num / (double)resolution * 25.4;
        temp = input_num * 10 + 5;
        return temp / 10;
    }
    double PixelToInchi(double input_num, int resolution)
    {
        return input_num / (double)resolution;
    }
    double MmToInchi(double input_num, int resolution)
    {
        int temp;
        double mpp = 25.4 / (double)resolution;
        temp = (input_num / mpp / (double)resolution * 1000 + 5) / 10;
        return temp;
    }
    double MmToPixel(double value, int res)
    {
        double mpp = 25.4 / (double)res;
        return value / mpp;
    }
    double InchiToPixel(double value, int res)
    {
        return value * (double)res;
    }
    bool search_item_list(int item, int32_t item_list[], int32_t list_size)
    {
        int i = 0;
        while(i < list_size){
            if(item_list[i] == item){
                return true;
            }
            i++;
        }
        return false;
    }
};
static StandAloneCommonUtility common_utility;
