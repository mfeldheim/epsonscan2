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
//  main.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "detectalert.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DetectAlert alert;
    if(argc != 6){
        return -1;
    }
    alert.CustomMessageBox(argv[1], argv[2], argv[3], argv[4], argv[5]);
    return 1;
}
