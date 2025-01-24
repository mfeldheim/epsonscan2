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
//  FKErrorUtil.h -- template and derived ESC/I ESC/I-2 protocol commands

#import "FileFormatKit.h"
static NSString* const kESImageFormatKitErrorDomain = @"ESImageFormatKit";
inline static FKErrorCode FKErrorCodeFromNSError(NSError** error,FKErrorCode defaultCode)
{
    if (error) {
        return [*error code];
    }
    return defaultCode;
}
inline static BOOL NSErrorFromFKErrorCode(FKErrorCode errorCode,NSError** outError)
{
    if(outError) {
        if (errorCode == kFKNoError) {
            *outError = nil;
        }else{
            *outError = [NSError errorWithDomain:kESImageFormatKitErrorDomain
                                            code:errorCode
                                        userInfo:nil];
        }
        return YES;
    }
    return NO;
}
