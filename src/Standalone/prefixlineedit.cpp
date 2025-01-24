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
//  prefixlineedit.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
PrefixLineedit::PrefixLineedit(QWidget *parent) :
    QLineEdit(parent),
    changed(false),
    current_prefix("")
{
}
void PrefixLineedit::initialize(std::string default_prefix){
    changed = true;
    current_prefix = default_prefix.c_str();
    this->setEnabled(true);
    this->setText(current_prefix);
}
QString PrefixLineedit::set_prefix(QString prefix){
    QRegExp r1("^.*[/:.*?\"<>|].*");
    if(r1.exactMatch(prefix) || prefix.indexOf("\\") != -1){
        BanMessageBox();
        current_prefix = DEFAULT_PREFIX;
        this->setText(DEFAULT_PREFIX);
    }else if(prefix.isEmpty()){
        current_prefix = DEFAULT_PREFIX;
    }else {
        current_prefix = prefix;
    }
    return current_prefix;
}
void PrefixLineedit::get_prefix(std::string* prefix){
    *prefix = (std::string)current_prefix.toLocal8Bit();
}
void PrefixLineedit::BanMessageBox(void)
{
    QMessageBox msgBox(this);
    msgBox.setText(TranslationString::GetString().translation_str.E_UI_103);
    msgBox.setWindowTitle(TranslationString::GetString().translation_str.MENU_001);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, TranslationString::GetString().translation_str.VERSION_003);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}
