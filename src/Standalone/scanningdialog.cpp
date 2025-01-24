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
//  scanningdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "scanningdialog.h"
#include "ui_scanningdialog.h"
#include "unistd.h"
#include "mainwindow.h"
#include "common_utility.h"
ScanningDialog::ScanningDialog(Supervisor* sv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanningDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setWindowFlags(Qt::WindowTitleHint | Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint) ;
    this->sv = sv;
    do_cancel = false;
    m_timer = NULL;
}
ScanningDialog::~ScanningDialog()
{
    if(m_timer){
        if(m_timer->isActive()){
            m_timer->stop();
        }
        delete m_timer;
        m_timer = NULL;
    }
    delete ui;
}
void ScanningDialog::closeEvent(QCloseEvent* event){
    event->ignore();
}
void ScanningDialog::ScanInitialize(QString progress_message){
    page_count = 0;
    if(sv->Scan_Start(kSDIOperationTypeNew)){
        m_timer = new QTimer(this);
        if(m_timer == NULL){
            return;
        }
        m_timer->setInterval(100);
        m_timer->setSingleShot(false);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()));
        m_timer->start();
        ui->progress_label->setText(progress_message);
    }
}
void ScanningDialog::Update()
{
    if(do_cancel || sv->scanning_status == CANCEL){
        sv->Cancel_Scanning();
        sv->outEventType = kSDITransferEventTypeCancel;
        m_timer->stop();
        this->reject();
    }else {
        if(page_count != 0){
            std::string message = (TranslationString::GetString().translation_str.PROGRESS_008.toLocal8Bit()).constData();
            std::string progress_message = common_utility.ReplaceString((char *)message.c_str(), "%d", std::to_string(page_count).c_str());
            ui->progress_label->setText(progress_message.c_str());
        }
        if(sv->CheckNextTransferEvent(false)){
            if(sv->Scanning()){
                if(sv->outEventType == kSDITrasnferEventTypeImage){
                    sv->Get_Image();
                    sv->Save_Path();
                    page_count++;
                }
            }else {
                m_timer->stop();
                sv->Get_Image();
                this->reject();
            }
            sv->Dispose_Ptr();
        }else if(sv->outEventType == kSDITransferEventTypeComplete){
            m_timer->stop();
            this->reject();
        }
    }
}
void ScanningDialog::Cancel()
{
    do_cancel = true;
}
