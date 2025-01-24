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
//  custommessagebox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H 
#include <supervisor.h>
#include "QMessageBox"
typedef enum {Question=0, Information, Warning, Critical}IconType;
class CustomMessageBox
{
public:
    CustomMessageBox(QWidget* parent);
    bool CreateMessageBox(QString message, QString button_message, IconType type, bool use_doNotShow=false);
    bool CreateSelectableMessageBox(QString message, IconType type);
    void ErrorMessageBox(Supervisor* sv, bool Preview=false);
private:
    QWidget* parent_dialog;
    void PaperJamDialog(Supervisor* sv, QString message, DoubleFeedMode dialog_type=IMMEDIATE);
};
#endif
