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
//  networkdeviceselectdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "networkdeviceselectdialog.h"
#include "ui_networkdeviceselectdialog.h"
#include "devicelist.h"
#include "mainwindow.h"
#include "PathUtils.h"
#include <QMessageBox>
#include <QDir>
#include "DbgLog.h"
#define NETSCANNER_MAXSIZE 999
NetworkDeviceSelectDialog::NetworkDeviceSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDeviceSelectDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->IP_List_tableWidget->setColumnWidth(0, ui->IP_List_tableWidget->width());
}
NetworkDeviceSelectDialog::~NetworkDeviceSelectDialog()
{
    delete ui;
}
void NetworkDeviceSelectDialog::closeEvent(QCloseEvent* event){
   DeviceList::select_manu_ip_address = -1;
}
void NetworkDeviceSelectDialog::LineEditFinished()
{
    if(ui->Address_lineEdit->text() == ""){
        ui->Add_pushButton->setEnabled(false);
    }else {
        if(DeviceList::manu_network_device_list.size() >= NETSCANNER_MAXSIZE){
            ui->Add_pushButton->setEnabled(false);
        }else {
            ui->Add_pushButton->setEnabled(true);
        }
    }
}
void NetworkDeviceSelectDialog::AvailableDeleteButton()
{
    if(ui->IP_List_tableWidget->currentRow() < 0){
       ui->Delete_pushButton->setEnabled(false);
       ui->Connect_pushButton->setEnabled(false);
    }else {
       ui->Delete_pushButton->setEnabled(true);
       ui->Connect_pushButton->setEnabled(true);
    }
}
void NetworkDeviceSelectDialog::PushButtonAction()
{
    QObject* obj = sender();
    if(obj == ui->Add_pushButton){
        if(DeviceList::manu_network_device_list.size() < NETSCANNER_MAXSIZE){
            SDIDeviceInfo devInfo;
            memset(devInfo.ipAddress, 0, MAX_IP_ADDR);
            memset(devInfo.displayName, 0, MAX_DISPLAYNAME);
            memset(devInfo.modelID, 0, MAX_MODEL_ID);
            QString ip = ui->Address_lineEdit->text();
            QList<QTableWidgetItem*> same_ip_list = ui->IP_List_tableWidget->findItems(ip, Qt::MatchFixedString);
            if(same_ip_list.size() == 0){
                if(ip != ""){
                    ui->IP_List_tableWidget->insertRow(0);
                    ui->IP_List_tableWidget->setItem( 0, 0, new QTableWidgetItem( ip ));
                    ui->IP_List_tableWidget->setCurrentItem(ui->IP_List_tableWidget->item(0, 0));
                    memcpy(devInfo.ipAddress, (ip.toLocal8Bit()).constData(), ip.size());
                    devInfo.productID = 0;
                    devInfo.version = 0;
                    DeviceList::manu_network_device_list.push_back(devInfo);
                }
            }else {
                ui->IP_List_tableWidget->setCurrentItem(same_ip_list.value(0));
            }
            ui->Address_lineEdit->clear();
            this->LineEditFinished();
            DeviceList::select_manu_ip_address = ui->IP_List_tableWidget->currentRow();
        }
    }else if(obj == ui->Delete_pushButton){
        QString target_ip = ui->IP_List_tableWidget->currentItem()->text();
        if(this->DeleteMessageBox(target_ip)){
            ui->IP_List_tableWidget->removeRow(ui->IP_List_tableWidget->currentRow());
            this->RemoveNetworkScanner(target_ip);
            this->LineEditFinished();
        }
    }else if(obj == ui->Connect_pushButton){
        DeviceList::select_manu_ip_address = ui->IP_List_tableWidget->currentRow();
    }else if(obj == ui->Cancel_pushButton){
        DeviceList::select_manu_ip_address = -1;
    }
}
void NetworkDeviceSelectDialog::InsertDevice()
{
    auto net_device = DeviceList::manu_network_device_list.begin();
    int list_size = DeviceList::manu_network_device_list.size();
    int i = 0;
    while(i < list_size){
        ui->IP_List_tableWidget->insertRow(0);
        ui->IP_List_tableWidget->setItem( 0, 0, new QTableWidgetItem( net_device->ipAddress ));
        ui->IP_List_tableWidget->setCurrentItem(ui->IP_List_tableWidget->item(0, 0));
        ++net_device;
        i++;
    }
}
void NetworkDeviceSelectDialog::RemoveNetworkScanner(QString target_ip)
{
    int list_size = DeviceList::manu_network_device_list.size();
    std::list<SDIDeviceInfo>::iterator remove_device = DeviceList::manu_network_device_list.begin();
    int i = 0;
    while(i < list_size){
        QString ip_address = remove_device->ipAddress;
        if(ip_address == target_ip){
            DeviceList::manu_network_device_list.erase(remove_device);
            break;
        }
        ++remove_device;
        i++;
    }
}
#include "common_utility.h"
bool NetworkDeviceSelectDialog::DeleteMessageBox(QString target_ip)
{
    std::string message = (TranslationString::GetString().translation_str.C_UI_002.toLocal8Bit()).constData();
    std::string warning_msg = common_utility.ReplaceString((char *)message.c_str(), "%s", (target_ip.toLocal8Bit()).constData());
    QMessageBox msgBox(this);
    msgBox.setText(warning_msg.c_str());
    msgBox.setWindowTitle(TranslationString::GetString().translation_str.MENU_001);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, TranslationString::GetString().translation_str.ES2U_MAIN_052);
    msgBox.setButtonText(QMessageBox::No, TranslationString::GetString().translation_str.ES2U_MAIN_053);
    msgBox.setIcon(QMessageBox::Warning);
    int res = msgBox.exec();
    if (res == QMessageBox::Yes){
        return true;
    } else if (res == QMessageBox::No) {
        return false;
    }
    return false;
}
int NetworkDeviceSelectDialog::Get_IP_ListTable_Size()
{
    return ui->IP_List_tableWidget->rowCount();
}
bool NetworkDeviceSelectDialog::UpdateNetworkSettingFile()
{
    ES_Trace_Log(this, "UpdateNetworkSettingFile IN");
    char ip_row[256];
    int list_size = DeviceList::manu_network_device_list.size();
    std::string netDst((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
#ifdef AKBMODE
    std::string strDst = ".";
    strDst = strDst + DRIVER_NAME;
    strDst = strDst + "/Network/";
    strDst = strDst + DRIVER_NAME;
    strDst = strDst + ".conf";
    ES_CMN_FUNCS::PATH::ES_CombinePath(netDst, netDst, strDst.c_str());
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(netDst, netDst, ".epsonscan2/Network/epsonscan2.conf");
#endif
    const bool result =ES_CMN_FUNCS::PATH::ES_IsExistFile(netDst);
    if (result) {
        pid_t c_pid;
        c_pid = getpid();
#ifdef AKBMODE
        ES_Trace_Log(this, "Exist network setting file");
#else
        ES_Trace_Log(this, "Exist file : .epsonscan2/Network/epsonscan2.conf");
#endif*/
       std::string work_path = ES_CMN_FUNCS::PATH::ES_GetWorkTempPath();
       QDir tmpdir("/tmp");
       if (!tmpdir.exists(work_path.c_str())) tmpdir.mkdir(work_path.c_str());
       std::string strDst = work_path;
       ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, "temp.conf");
       ES_Trace_Log(this, "before : %s", netDst.c_str());
       ES_Trace_Log(this, "after : %s", strDst.c_str());
        try {
            ES_Trace_Log(this, "Create temp.conf file");
            system((boost::format("mv %1% %2%") % netDst.c_str() % strDst.c_str()).str().c_str());
        }
        catch (...) {
            throw;
        }
        std::fstream temp_netSettingFile(strDst.c_str());
        std::ofstream(netDst.c_str());
        std::fstream out_netSettingFile(netDst.c_str());
        if (temp_netSettingFile.fail() || out_netSettingFile.fail())
        {
#ifdef AKBMODE
            ES_Trace_Log(this, "Failed to create network setting file");
#else
            ES_Trace_Log(this, "Failed to create epsonscan2.conf file");
#endif
            return false;
        }
        while (temp_netSettingFile.getline(ip_row, 256 - 1))
        {
            out_netSettingFile << ip_row << std::endl;
            if(strcmp(ip_row, "[Network]") == 0){
                QString ip;
                while (temp_netSettingFile.getline(ip_row, 256 - 1))
                {
                    ip = ip_row;
                    ip = ip.trimmed();
                    if(ip[0] == '#' || ip[0] == ';'){
                        out_netSettingFile << ip_row << std::endl;
                    }
                }
                auto device = DeviceList::manu_network_device_list.begin();
                int i = 0;
                out_netSettingFile << "" << std::endl;
                while(i < list_size){
                    out_netSettingFile << device->ipAddress << std::endl;
                    ++device;
                    i++;
                }
                try {
                    DeleteFile(strDst.c_str());
                }
                catch (...) {
                    throw;
                }
                ES_Trace_Log(this, "UpdateNetworkSettingFile OUT");
                return true;
            }
        }
        try {
            DeleteFile(netDst.c_str());
        }
        catch (...) {
            throw;
        }
        if(!CreateNewNetworkSettingFile(list_size)){
#ifdef AKBMODE
            ES_Trace_Log(this, "Create new network setting file");
#else
            ES_Trace_Log(this, "Create new epsonscan2.conf file");
#endif
            return false;
        }
        ES_Trace_Log(this, "TBD return point");
        return false;
    }else {
        if(!CreateNewNetworkSettingFile(list_size)){
#ifdef AKBMODE
            ES_Trace_Log(this, "Create new network setting file");
#else
            ES_Trace_Log(this, "Create new epsonscan2.conf file");
#endif
            return false;
        }
    }
    ES_Trace_Log(this, "UpdateNetworkSettingFile OUT");
    return true;
}
bool NetworkDeviceSelectDialog::CreateNewNetworkSettingFile(int device_list_size)
{
    std::string netDst((QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toLocal8Bit()).constData());
#ifdef AKBMODE
    std::string dir_name = ".";
    dir_name = dir_name + DRIVER_NAME;
    dir_name = dir_name + "/Network";
    ES_CMN_FUNCS::PATH::ES_CombinePath(netDst, netDst, dir_name.c_str());
    netDst = netDst + "/";
    netDst = netDst + DRIVER_NAME;
    std::string network_settings_file = netDst + ".conf";
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(netDst, netDst, ".epsonscan2/Network");
    std::string network_settings_file = netDst + "/epsonscan2.conf";
#endif
    if(ES_CMN_FUNCS::PATH::ES_IsExistFolder(netDst) == FALSE)
    {
        ES_CMN_FUNCS::PATH::ES_MakeFolder(netDst);
    }
    std::ofstream(network_settings_file.c_str());
    std::fstream new_netSettingFile(network_settings_file.c_str());
    if (new_netSettingFile.fail())
    {
        return false;
    }
    new_netSettingFile << "[Network]" << std::endl;
    auto device = DeviceList::manu_network_device_list.begin();
    int i = 0;
    new_netSettingFile << "" << std::endl;
    while(i < device_list_size){
        new_netSettingFile << device->ipAddress << std::endl;
        ++device;
        i++;
    }
    return true;
}
