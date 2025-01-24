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
//  scanbutton.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef SCANBUTTON_H
#define SCANBUTTON_H 
#include <QPushButton>
#include "capitem.h"
#include "supervisor.h"
#include "custommessagebox.h"
class QMainWindow;
class ScanButton : public QPushButton
{
public:
    ScanButton(QWidget *parent = 0);
    void initialize(CustomMessageBox* msg_box, QMainWindow* mainWindow = nullptr);
    void Button_pressed(Supervisor* sv, bool Add_Pages);
private:
    CustomMessageBox* m_messageBox;
    QMainWindow* m_mainWindow;
};
#endif
