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
//  configuration.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef CONFIGURATION_H
#define CONFIGURATION_H 
#include "supervisor.h"
class Configuration
{
public:
    Configuration();
    void SetConfiguration(CONFIGURATION _config);
    static Configuration& GetConfiguration();
    CONFIGURATION config_para;
};
#endif
