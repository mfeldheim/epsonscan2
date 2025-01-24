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
//  prefixlineedit.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef PREFIXLINEEDIT_H
#define PREFIXLINEEDIT_H 
#include <QLineEdit>
#define DEFAULT_PREFIX "img"
class PrefixLineedit : public QLineEdit
{
public:
    PrefixLineedit(QWidget *parent = 0);
    QString current_prefix;
    void initialize(std::string default_prefix);
    QString set_prefix(QString prefix);
    void get_prefix(std::string* prefix);
private:
    bool changed;
    void BanMessageBox(void);
};
#endif
