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
//  continuousscandialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "continuousscandialog.h"
#include "ui_continuousscandialog.h"
#include "translationstring.h"
#include "saveimagepathlist.h"
#include <QStyle>
ContinuousScanDialog::ContinuousScanDialog(Supervisor* sv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContinuousScanDialog),
    m_dialog_type(IMMEDIATE),
    m_scanning_status(CONTINUE)
{
    m_sv = sv;
    ui->setupUi(this);
    this->setFixedSize(this->size());
}
ContinuousScanDialog::~ContinuousScanDialog()
{
    delete ui;
}
void ContinuousScanDialog::Initialize(QString message, DoubleFeedMode dialog_type)
{
    this->m_dialog_type = dialog_type;
    ui->graphicsView->hide();
    ui->Icon_toolButton->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxWarning));
    ui->frame->setObjectName("frame");
    ui->frame->setStyleSheet("#frame {background-color:dimgray;}");
    QPalette pal = ui->noimage_label->palette();
    pal.setColor(QPalette::Foreground, QColor("#FFFFFF"));
    ui->noimage_label->setPalette(pal);
    this->ChangeStrings(dialog_type, message);
    if(m_sv->device_data.ADFSpecialErrorMessageForPassport.select){
        this->AddADFSpecialErrorMessageForPassportStrings(TranslationString::GetString().translation_str.CONFIRMCONTINUE_015);
    }
    this->LoadScanImage();
}
void ContinuousScanDialog::closeEvent(QCloseEvent* event){
    event->ignore();
}
void ContinuousScanDialog::LoadScanImage()
{
    if(SaveImagePathList::save_image_path_list.size() > 0)
    {
        auto save_path = SaveImagePathList::save_image_path_list.end();
        save_path--;
        imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
        std::string temp_str = temp_edit_info.file_path;
        if(m_image.load((const char*)temp_str.c_str())){
            ui->graphicsView->resize(ui->frame->width(), ui->frame->height());
            ui->graphicsView->show();
            ui->graphicsView->setScene(&Scene_);
            Scene_.clear();
            QPixmap pixmap=QPixmap::fromImage(m_image);
            Scene_.addPixmap(pixmap.scaled(ui->graphicsView->width()-5, ui->graphicsView->height()-5, Qt::KeepAspectRatio,Qt::FastTransformation));
        }
    }
}
void ContinuousScanDialog::onButtonPressed()
{
    QObject* obj = sender();
    if(obj == ui->Continue_pushButton){
        this->m_scanning_status = CONTINUE;
    }else if(obj == ui->Stop_pushButton){
        this->m_scanning_status = CANCEL;
    }else if(obj == ui->Save_pushButton){
        if(this->m_dialog_type == IMMEDIATE){
            this->m_scanning_status = SAVE;
        }else {
            this->m_scanning_status = DISCARD;
        }
    }
    this->reject();
}
ScanningStatus ContinuousScanDialog::GetScanningStatus()
{
    return this->m_scanning_status;
}
void ContinuousScanDialog::ChangeStrings(DoubleFeedMode dialog_type, QString message)
{
    ui->continuous_label->setText(message);
    if(dialog_type == AFTER_EJECT){
        ui->Save_pushButton->setText(TranslationString::GetString().translation_str.CONFIRMCONTINUE_014);
    }else if(dialog_type == IMMEDIATE){
        ui->Save_pushButton->setText(TranslationString::GetString().translation_str.CONFIRMCONTINUE_004);
    }
}
void ContinuousScanDialog::AddADFSpecialErrorMessageForPassportStrings(QString message)
{
    ui->ADFSpecialErrorMessageForPassport_label->setText(message);
}
