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
//  translationstring.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef TRANSLATIONSTRING_H
#define TRANSLATIONSTRING_H 
#include <QObject>
typedef struct {
    QString MAINSETTING_003;
} TRANSLATIONSTR;
class TranslationString
{
public:
    TranslationString();
    void SetString();
    void SetFilename(std::string _filename);
    static TranslationString& GetString();
    TRANSLATIONSTR translation_str;
};
#endif
