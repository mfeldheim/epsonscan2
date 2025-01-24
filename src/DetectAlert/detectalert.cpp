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
//  detectalert.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "detectalert.h"
#include "translationstring.h"
#include <QDesktopWidget>
#include <QGridLayout>
#include <QSpacerItem>
#include <QDir>
#include <QDirIterator>
#include "../Include/Config.h"
DetectAlert::DetectAlert(QWidget *parent)
    : QMainWindow(parent)
{
}
DetectAlert::~DetectAlert()
{
}
static const int kMessageBoxWidth = 500;
static const int kMessageBoxHeight = 100;
void DetectAlert::CustomMessageBox(QString dialog_title, QString message, QString button_message, std::string identifier, std::string dir_num)
{
#ifdef AKBMODE
    std::string dir_name = "epsonscan2alert";
#else
    std::string dir_name = "epsonscan2alert";
#endif
    dir_name = dir_name + identifier;
    int num = std::atoi(dir_num.c_str());
    QDir tmpdir("/tmp");
        QMessageBox msgBox(this);
        QDesktopWidget desktop_info;
        msgBox.setIconPixmap(QPixmap(":/escan2_app.icon"));
        msgBox.setText(message);
        msgBox.setWindowTitle(dialog_title);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, button_message);
        if(num == 1){
            msgBox.setGeometry(desktop_info.width() - kMessageBoxWidth - 20, desktop_info.height() - kMessageBoxHeight, 0, 0);
        }else if(num == 2){
            msgBox.setGeometry(desktop_info.width() - kMessageBoxWidth - 20, desktop_info.height() - kMessageBoxHeight - (kMessageBoxHeight * 1 + (1 * 50)), 0, 0);
        }
        QSpacerItem* horizontalSpacer = new QSpacerItem(kMessageBoxWidth , kMessageBoxHeight, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = (QGridLayout*)msgBox.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1,layout->columnCount());
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        tmpdir.rmdir(dir_name.c_str());
}
int DetectAlert::CheckExistDir()
{
    QDir tmpdir("/tmp");
    QStringList nameFilters;
#ifdef AKBMODE
    std::string strDst = DRIVER_NAME;
    strDst = strDst + "alert*";
    nameFilters << strDst.c_str();
#else
    nameFilters << "epsonscan2alert*";
#endif
    QStringList dirlist = tmpdir.entryList(nameFilters, QDir::Dirs);
    return dirlist.count();
}
