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
//  waitingdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "waitingdialog.h"
#include "ui_waitingdialog.h"
#include "unistd.h"
#include "../Include/Config.h"
#define UPDATE_INTERVAL 100
WaitingDialog::WaitingDialog(const char* message, int time, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingDialog)
{
    m_timer = NULL;
    time_count = 0;
    wait_time = time * 1000;
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->Waiting_Message_label->setText(message);
    m_timer = new QTimer(this);
    if(m_timer == NULL){
        return;
    }
    m_timer->setInterval(UPDATE_INTERVAL);
    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()));
    m_timer->start();
#ifdef AKBMODE
    this->setWindowTitle(DRIVER_TITLE);
#endif
    if(this->isHidden()){
        this->exec();
    }else {
        this->activateWindow();
    }
}
WaitingDialog::~WaitingDialog()
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
void WaitingDialog::Update()
{
    ui->progressBar->update();
    time_count += UPDATE_INTERVAL;
    if(time_count >= wait_time){
        this->reject();
    }
}
void WaitingDialog::closeEvent(QCloseEvent* event){
    event->ignore();
}
