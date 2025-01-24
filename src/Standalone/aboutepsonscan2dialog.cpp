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
//  aboutepsonscan2dialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "aboutepsonscan2dialog.h"
#include "ui_aboutepsonscan2dialog.h"
#include "supervisor.h"
#include "../Include/Config.h"
#include <sstream>
#include "PathUtils.h"
AboutEpsonScan2Dialog::AboutEpsonScan2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutEpsonScan2Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->Model_List_tableWidget->setColumnWidth(0, ui->Model_List_tableWidget->width()*0.7);
    ui->Model_List_tableWidget->setColumnWidth(1, ui->Model_List_tableWidget->width()*0.3);
#ifdef NOUSEQRC
    std::string strIconPath = EPSON_INSTALL_PATH;
    ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/escan2_app.ico");
    ui->Help_toolButton->setIcon(QIcon(strIconPath.c_str()));
#endif
#ifdef AKBMODE
    ui->Copyright_label->setText("");
#endif
}
AboutEpsonScan2Dialog::~AboutEpsonScan2Dialog()
{
    delete ui;
}
void AboutEpsonScan2Dialog::closeEvent(QCloseEvent* event){
}
void AboutEpsonScan2Dialog::Initialize()
{
    std::string dir1(COMMON_SHARE_PATH);
    ES_CMN_FUNCS::PATH::ES_CombinePath(dir1, dir1, "doc/");
    this->ReadVersionFile(dir1.c_str());
    ui->Locale_label->setText(QLocale::system().name());
}
void AboutEpsonScan2Dialog::ReadVersionFile(const char* version_path)
{
    std::string dir_name;
    std::string package_name;
    std::string version;
    auto files = ES_CMN_FUNCS::PATH::EnumFilesInDir("", version_path);
 for(auto file : files)
    {
        std::string filename;
        ES_CMN_FUNCS::PATH::ES_GetFileName(filename, file, FALSE);
        int a = 0, b =0, c =0, d = 0, e = 0;
        int version_length;
#ifdef AKBMODE
        std::string version_check_str = DRIVER_NAME;
        version_check_str = version_check_str + "-%d.%d.%d.%d-%d";
        if(strncmp(filename.c_str(), version_check_str.c_str(), strlen(DRIVER_NAME)) == 0){
            std::string version_check_plugin_str = version_check_str + "non-free-plugin-%d.%d.%d.%d-%d";
            if(strncmp(filename.c_str(), version_check_plugin_str.c_str(), strlen(DRIVER_NAME) + strlen("non-free-plugin-")) == 0){
                sscanf(filename.c_str(), version_check_str.c_str(),&a, &b, &c, &d, &e);
            }else {
                sscanf(filename.c_str(), version_check_plugin_str.c_str(),&a, &b, &c, &d, &e);
            }
#else
        if(strncmp(filename.c_str(), "epsonscan2-", strlen("epsonscan2-")) == 0){
            if(strncmp(filename.c_str(), "epsonscan2-non-free-plugin-", strlen("epsonscan2-non-free-plugin-")) == 0){
                sscanf(filename.c_str(), "epsonscan2-non-free-plugin-%d.%d.%d.%d-%d",&a, &b, &c, &d, &e);
            }else {
                sscanf(filename.c_str(), "epsonscan2-%d.%d.%d.%d-%d",&a, &b, &c, &d, &e);
            }
#endif
            char *version_temp = NULL;
            version_temp = (char *)malloc(15);
            if(version_temp){
               memset(version_temp, 0, 15);
                sprintf(version_temp, "%d.%d.%d.%d-%d", a, b, c, d, e);
                version_length = strlen(version_temp);
            }else {
                version_length = strlen("1.0.0.0");
            }
            dir_name = filename.c_str();
            const size_t strLen = filename.length();
            version = filename.substr(strLen - version_length, version_length);
            package_name = dir_name;
            int del_count = version.size() + 1;
            while(del_count > 0){
                package_name.erase(package_name.end() - del_count);
                del_count--;
            }
            QString temp = package_name.c_str();
            ui->Model_List_tableWidget->insertRow(0);
            ui->Model_List_tableWidget->setItem( 0, 0, new QTableWidgetItem( temp ));
            ui->Model_List_tableWidget->setCurrentItem(ui->Model_List_tableWidget->item(0, 0));
            temp = version.c_str();
            ui->Model_List_tableWidget->setItem( 0, 1, new QTableWidgetItem( temp ));
            free(version_temp);
            version_temp = NULL;
        }
    }
}
