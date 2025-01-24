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
//  translationstring.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "translationstring.h"
static TranslationString translation;
TranslationString::TranslationString()
{
}
TranslationString& TranslationString::GetString()
{
    return translation;
}
void TranslationString::SetString()
{
    TRANSLATIONSTR temp_translation;
    temp_translation.MAINSETTING_003 = QObject::tr("MAINSETTING_003");
    this->translation_str = temp_translation;
}
