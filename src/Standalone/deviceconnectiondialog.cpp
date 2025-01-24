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
//  deviceconnectiondialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
#include "ui_deviceconnectiondialog.h"
#include "PathUtils.h"
#include "../Include/Config.h"
#include <QDebug>
#include <QProcess>
#include <pthread.h>
#define UPDATE_INTERVAL 100
DeviceConnectionDialog::DeviceConnectionDialog(Supervisor *sv, SDIDeviceInfo select_Device, bool use_lastsettings, QWidget *parent) : QDialog(parent),
                                                                                                                                      ui(new Ui::DeviceConnectionDialog)
{
    m_timer = NULL;
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->m_connect_info.sv = sv;
    this->m_connect_info.select_Device = select_Device;
    this->m_connect_info.use_lastsettings = use_lastsettings;
    this->m_connect_info.dialog = this;
    this->m_connect_info.connection_result = false;
    this->m_connect_info.terminate_connection = false;
    m_timer = new QTimer(this);
    if (m_timer == NULL)
    {
        return;
    }
    m_timer->setInterval(UPDATE_INTERVAL);
    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(CheckConnection()));
    m_timer->start();
    this->Initialize();
}
DeviceConnectionDialog::~DeviceConnectionDialog()
{
    if (m_timer)
    {
        if (m_timer->isActive())
        {
            m_timer->stop();
        }
        delete m_timer;
        m_timer = NULL;
    }
    delete ui;
}
void DeviceConnectionDialog::CheckConnection()
{
    if (this->m_connect_info.terminate_connection)
    {
        m_timer->stop();
        this->reject();
    }
}
void DeviceConnectionDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
bool DeviceConnectionDialog::GetConnectionResult(void)
{
    return this->m_connect_info.connection_result;
}
void DeviceConnectionDialog::Initialize(void)
{
    pthread_t thread;
    if (this->isHidden())
    {
        if (pthread_create(&thread, NULL, &DeviceConnectionDialog::ConnectToDevice, &this->m_connect_info) == 0)
        {
            this->exec();
            pthread_join(thread, NULL);
        }
    }
}
void DetectAlertGlassDirty(SDIScannerDriver *driver, SDIInterruptEventType event, void *userdata)
{
    UNREFERENCED_PARAMETER(driver);
    UNREFERENCED_PARAMETER(userdata);
    QDir tmpdir("/tmp");
    QStringList nameFilters;
#ifdef AKBMODE
    std::string strDst = DRIVER_NAME;
    strDst = strDst + "alert*";
    nameFilters << strDst.c_str();
#else
    nameFilters << "epsonscan2alert*";
#endif
    std::string dir_name = "epsonscan2alert";
    if (event == kSDIInterruptEventTypeCleaningRequired)
    {
        std::string strDetectAlertPath = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strDetectAlertPath, strDetectAlertPath, "detectalert");
        QString exeapp(strDetectAlertPath.c_str());
#ifdef AKBMODE
        QString arg1(DRIVER_TITLE);
#else
        QString arg1("EPSON");
#endif
        QString arg2(TranslationString::GetString().translation_str.A_UI_006);
        QString arg3(TranslationString::GetString().translation_str.VERSION_003);
        QString executable = exeapp + " " + arg1 + " " + "\"" + arg2 + "\"" + " " + arg3 + " " + "A_UI_006" + " " + std::to_string( 1).c_str();
        dir_name = dir_name + "A_UI_006";
        if (!tmpdir.exists(dir_name.c_str()))
        {
            if (!tmpdir.exists(dir_name.c_str()))
                tmpdir.mkdir(dir_name.c_str());
            if (!QProcess::startDetached(executable))
            {
                qCritical() << "Cannot start program";
            }
        }
    }
    else if (event == kSDIInterruptEventTypeGlassDirty || event == kSDIInterruptEventTypeGlassFlatbedModel)
    {
        std::string strDetectAlertPath = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strDetectAlertPath, strDetectAlertPath, "detectalert");
        QString exeapp(strDetectAlertPath.c_str());
#ifdef AKBMODE
        QString arg1(DRIVER_TITLE);
#else
        QString arg1("EPSON");
#endif
        QString arg2;
        QString arg3;
        QString executable;
        if (event == kSDIInterruptEventTypeGlassFlatbedModel)
        {
            arg2 = (TranslationString::GetString().translation_str.A_UNIT_015);
            arg3 = (TranslationString::GetString().translation_str.VERSION_003);
            executable = exeapp + " " + arg1 + " " + "\"" + arg2 + "\"" + " " + arg3 + " " + "A_UNIT_015" + " " + std::to_string( 2).c_str();
            dir_name = dir_name + "A_UNIT_015";
        }
        else
        {
            arg2 = (TranslationString::GetString().translation_str.A_UNIT_008);
            arg3 = (TranslationString::GetString().translation_str.VERSION_003);
            executable = exeapp + " " + arg1 + " " + "\"" + arg2 + "\"" + " " + arg3 + " " + "A_UNIT_008" + " " + std::to_string( 2).c_str();
            dir_name = dir_name + "A_UNIT_008";
        }
        if (!tmpdir.exists(dir_name.c_str()))
        {
            if (!tmpdir.exists(dir_name.c_str()))
                tmpdir.mkdir(dir_name.c_str());
            if (!QProcess::startDetached(executable))
            {
                qCritical() << "Cannot start program";
            }
        }
    }
}
void *DeviceConnectionDialog::ConnectToDevice(void *vpContext)
{
    CONNECTINFO *connect_info = (CONNECTINFO *)vpContext;
    DeviceConnectionDialog *dialog = (DeviceConnectionDialog *)connect_info->dialog;
#ifdef AKBMODE
    dialog->setWindowTitle(DRIVER_TITLE);
#endif
    Supervisor *sv = connect_info->sv;
    SDIDeviceInfo select_Device = connect_info->select_Device;
    bool use_lastsettings = connect_info->use_lastsettings;
    sleep(1);
    sv->m_LastError = sv->Connecting_Scanner(select_Device, DetectAlertGlassDirty);
    if (sv->m_LastError == kSDIErrorNone)
    {
        Configuration &config = Configuration::GetConfiguration();
        if (config.config_para.last_used_settings)
        {
            if (!use_lastsettings)
            {
                if (config.config_para.used_default_settings == false)
                {
                    dialog->ResetOnlyStandaloneVal(sv);
                }
            }
        }
        else
        {
            if (config.config_para.used_default_settings == false)
            {
                dialog->ResetOnlyStandaloneVal(sv);
            }
        }
        connect_info->connection_result = true;
    }
    else
    {
        connect_info->connection_result = false;
    }
    connect_info->terminate_connection = true;
    return NULL;
}
void DeviceConnectionDialog::ResetOnlyStandaloneVal(Supervisor *sv)
{
    sv->device_data.ScanArea.FixedSize = Auto_Detect;
    sv->device_data.Add_Pages = false;
    sv->device_data.Prefix = DEFAULT_PREFIX;
    sv->device_data.ScanArea.UserDefine_Width = 0;
    sv->device_data.ScanArea.UserDefine_Length = 0;
    sv->device_data.ImageFormatSettings.PDFImgFormatOption.AllPage = true;
    sv->device_data.ImageFormatSettings.PDFImgFormatOption.page = 1;
    sv->device_data.UserDefinePath = "";
    sv->device_data.Folder = 0;
    sv->device_data.ImageOption = ImageOptionNone;
    sv->device_data.ScanArea.PaperEndDetectionMemory = false;
    sv->device_data.AFMTimeout.select = Timeout_180;
    sv->device_data.DNShow_PlasticCard_dialog = false;
    sv->device_data.DNShow_LongPaperWarning_dialog = false;
    sv->device_data.OverDurationAlert = false;
    sv->device_data.NearDurationAlert = false;
    sv->device_data.ImageFormatSettings.JpegQuality_forJPEG = 85;
    if (sv->device_data.ScannerKind.select == kSDIKindMFLargeFormat)
    {
        sv->device_data.ImageFormatSettings.DefaultJpegQuality_forPDF = 85;
    }
    else
    {
        sv->device_data.ImageFormatSettings.DefaultJpegQuality_forPDF = 37;
    }
    sv->device_data.ImageFormatSettings.JpegQuality_forPDF = sv->device_data.ImageFormatSettings.DefaultJpegQuality_forPDF;
    sv->device_data.use_continuousAutoFeedingMode = false;
    sv->device_data.FileName_OverWrite = 0;
    sv->device_data.FileName_Counter = 0;
}
