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
//  deviceselectdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "deviceselectdialog.h"
#include "ui_deviceselectdialog.h"
#include "devicefinder.h"
#include "PathUtils.h"
#include "devicelist.h"
#include <QIcon>
DeviceSelectDialog::DeviceSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceSelectDialog),
    sv(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    terminate_flag = false;
#ifdef AKBMODE
    this->setWindowTitle(DRIVER_TITLE);
#endif
#ifdef NOUSEQRC
    std::string strIconPath = EPSON_INSTALL_PATH;
    ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/update4.png");
    ui->Update_toolButton->setIcon(QIcon(strIconPath.c_str()));
#endif
#ifdef RPMBUILD
    ui->Update_toolButton->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
#endif
}
DeviceSelectDialog::~DeviceSelectDialog()
{
}
void DeviceSelectDialog::closeEvent(QCloseEvent* event){
    this->done(QDialog::Rejected);
    terminate_flag = true;
}
bool DeviceSelectDialog::Initialize(Supervisor* sv)
{
    this->sv = sv;
    if(!ui->Select_Device_comboBox->initialize()){
        return false;
    }
    this->updateUI();
    return true;
}
void DeviceSelectDialog::updateUI()
{
    ui->Select_Device_comboBox->update_device_list();
    int device_sum = DeviceList::manu_network_device_list.size() + DeviceList::device_list.size();
    if(device_sum == 0){
        ui->Connecting_pushButton->setEnabled(false);
    }else {
        ui->Connecting_pushButton->setEnabled(true);
    }
}
void DeviceSelectDialog::onValueChanged(int value)
{
    QObject* obj = sender();
    if(obj == ui->Select_Device_comboBox){
        ui->Select_Device_comboBox->item_event(value);
    }
    this->updateUI();
}
void DeviceSelectDialog::PushEventButton(void)
{
    QObject* obj = sender();
    if(obj == ui->Connecting_pushButton){
        if(ui->Select_Device_comboBox->itemData(ui->Select_Device_comboBox->currentIndex()) != OPTIONS){
            this->reject();
        }
    }else if(obj == ui->Update_toolButton){
        DeviceFinder* dev_finder = new DeviceFinder();
        if(dev_finder == NULL){
            return;
        }
        dev_finder->finder(this);
        if(!dev_finder->ManuNetfinder()){
        }
        delete dev_finder;
        dev_finder = nullptr;
        this->Initialize(this->sv);
    }
    this->updateUI();
}
