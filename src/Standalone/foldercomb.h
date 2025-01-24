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
//  foldercomb.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef FOLDERCOMB_H
#define FOLDERCOMB_H 
#include <QComboBox>
#include <QStandardPaths>
#include "supervisor.h"
#include "custommessagebox.h"
class FolderComb : public QComboBox
{
public:
    FolderComb(QWidget *parent = 0);
    Folder current_item;
    void initialize(SCANPARA dev_data, CustomMessageBox* msg_box);
    void focusOutEvent(QFocusEvent* event);
    void update_ui();
    void item_event(int value, SCANPARA* path_data);
    void select_current_path(SCANPARA* path_data);
    QString user_define_path;
private:
    CustomMessageBox* m_messageBox;
    bool changed;
    QVariant old_select;
    void set_enabled(bool enabled);
    void add_item();
    void add_option(int list_size);
    void add_userdefine();
    void select_item();
    void item_event_options(void);
};
#endif
