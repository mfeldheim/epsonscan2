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
//  scanbutton.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include <stdio.h>
#include <iostream>
#include <boost/format.hpp>
#include <QDesktopServices>
#include "scanbutton.h"
#include "mainwindow.h"
#include "scanningdialog.h"
#include "addpagedialog.h"
#include "addeditpagedialog.h"
#include "saveimagepathlist.h"
#include "PathUtils.h"
#include "savedestfolder.h"
#include "automaticfeedingmodedialog.h"
#include "rotateimage.h"
#include "supervisor.h"
#include <QtWidgets/QProgressDialog>
ScanButton::ScanButton(QWidget *parent) :
    QPushButton(parent)
{
    m_messageBox = NULL;
    m_mainWindow = NULL;
}
void ScanButton::initialize(CustomMessageBox* msg_box, QMainWindow* mainWindow)
{
    this->setEnabled(true);
    m_messageBox = msg_box;
    m_mainWindow = mainWindow;
}
 void MyProgessCallBack(int, int)
 {
    QCoreApplication::processEvents();
 }
void ScanButton::Button_pressed(Supervisor* sv, bool Add_Pages)
{
    ScanningDialog* scanning_dialog = NULL;
    sv->scanning_status = SAVE;
    bool first_image_save = false;
    bool edit_mode = false;
    QProgressDialog* saveProgressDialog = nullptr;
    do{
        if(sv->device_data.AutomaticFeedingMode.select){
            AutomaticFeedingModeDialog* afm_dialog = new AutomaticFeedingModeDialog(sv, m_messageBox);
            if(afm_dialog == NULL){
                sv->scanning_status = ERROR;
                sv->m_LastError = kSDIErrorUnknownError;
                m_messageBox->ErrorMessageBox(sv);
                break;
            }
            afm_dialog->setAttribute(Qt::WA_DeleteOnClose);
            if(sv->m_LastError != kSDIErrorNone){
                m_messageBox->ErrorMessageBox(sv);
                break;
            }else {
                if(afm_dialog->isHidden()){
                    afm_dialog->exec();
                }else {
                    afm_dialog->activateWindow();
                }
            }
        }else {
            scanning_dialog = new ScanningDialog(sv);
            scanning_dialog->ScanInitialize(TranslationString::GetString().translation_str.PROGRESS_007);
            if(scanning_dialog == NULL){
                sv->scanning_status = ERROR;
                sv->m_LastError = kSDIErrorUnknownError;
                m_messageBox->ErrorMessageBox(sv);
                break;
            }
            scanning_dialog->setAttribute(Qt::WA_DeleteOnClose);
            if(sv->m_LastError != kSDIErrorNone){
                m_messageBox->ErrorMessageBox(sv);
                break;
            }else {
                if(scanning_dialog->isHidden()){
                    scanning_dialog->exec();
                }else {
                    scanning_dialog->activateWindow();
                }
            }
        }
        if(!sv->device_data.AutomaticFeedingMode.select){
            if(sv->outEventType == kSDITransferEventTypeCancel){
                m_messageBox->ErrorMessageBox(sv);
                sv->scanning_status = CANCEL;
            }else
            if(sv->m_LastError != kSDIErrorNone){
                m_messageBox->ErrorMessageBox(sv);
                if(sv->m_LastError == kSDIErrorPaperEmpty){
                    if(sv->scanning_status == CONTINUE){
                        sv->scanning_status = SAVE;
                    }else {
                        sv->scanning_status = CANCEL;
                    }
                }else if(sv->m_LastError == kSDIErrorCoverOpen){
                    sv->scanning_status = CANCEL;
                }else
                if(sv->m_LastError == kSDIErrorNone){
                    ;
                }else
                if(!(sv->m_LastError == kSDIErrorPaperJam ||
                     sv->m_LastError == kSDIErrorPaperDoubleFeed ||
                     sv->m_LastError == kSDIErrorPaperDoubleFeed2 ||
                     sv->m_LastError == kSDIErrorPaperProtect ||
                     sv->m_LastError == kSDIErrorDeviceFormChangedInterruptedly ||
                     sv->m_LastError == kSDIErrorPaperRemoveError ||
                     sv->m_LastError == kSDIErrorSkewDetectError ||
                     sv->m_LastError == kSDIErrorSepLeverChangedInterruptedly)){
                    sv->scanning_status = ERROR;
                }
            }else {
                sv->scanning_status = SAVE;
            }
            if(sv->scanning_status == SAVE || (sv->scanning_status == CANCEL && first_image_save)){
                if(Add_Pages){
                    do{
                        if(sv->device_data.ImageFormatSettings.ImageFormat.select == ImageFormatTIFF){
                            AddPageDialog* add_page_dialog = new AddPageDialog(&sv->scanning_status);
                            if(add_page_dialog == NULL){
                                sv->scanning_status = ERROR;
                                sv->m_LastError = kSDIErrorUnknownError;
                                m_messageBox->ErrorMessageBox(sv);
                                break;
                            }
                            if(!edit_mode){
                                if(add_page_dialog->isHidden()){
                                    add_page_dialog->exec();
                                }else {
                                    add_page_dialog->activateWindow();
                                }
                            }
                            delete(add_page_dialog);
                            add_page_dialog = NULL;
                        }else {
                            addeditpageDialog* add_page_dialog = new addeditpageDialog(&sv->scanning_status);
                            if(add_page_dialog == NULL){
                                sv->scanning_status = ERROR;
                                sv->m_LastError = kSDIErrorUnknownError;
                                m_messageBox->ErrorMessageBox(sv);
                                break;
                            }
                            if(!edit_mode){
                                if(add_page_dialog->isHidden()){
                                    add_page_dialog->exec();
                                }else {
                                    add_page_dialog->activateWindow();
                                }
                            }else {
                                sv->scanning_status = EDIT;
                            }
                            if(sv->scanning_status == EDIT){
                                edit_mode = add_page_dialog->EditDialog(&SaveImagePathList::save_image_path_list);
                            }
                            delete(add_page_dialog);
                            add_page_dialog = NULL;
                        }
                        if(sv->device_data.FunctionalUnit.select == kSDIFunctionalUnitDocumentFeeder &&
                                sv->scanning_status == CONTINUE){
                            if(!sv->GetPaperLoadedStatus()){
                                sv->m_LastError = kSDIErrorPaperEmpty;
                                m_messageBox->ErrorMessageBox(sv);
                            }else {
                                sv->m_LastError = kSDIErrorNone;
                                first_image_save = true;
                            }
                        }else {
                            sv->m_LastError = kSDIErrorNone;
                            first_image_save = true;
                        }
                    }while(sv->m_LastError == kSDIErrorPaperEmpty);
                }
            }
        }
        if(sv->scanning_status == SAVE){
            RotateImage* rotateImage = new RotateImage((ColorType)sv->device_data.ColorType.select);
            auto save_path = SaveImagePathList::save_image_path_list.begin();
            for(int i = 0; i < (int)SaveImagePathList::save_image_path_list.size(); i++)
            {
                imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
                int angle = temp_edit_info.angle % 360;
                if(angle != 0){
                    rotateImage->Rotate(temp_edit_info.file_path, angle, (ImageFormat)sv->device_data.ImageFormatSettings.ImageFormat.select, sv->device_data.ImageFormatSettings.MultiTiffEnabled.select, sv->device_data.ImageFormatSettings.OFDEnabled.select);
                }
                ++save_path;
            }
            ProgessCallBack progressCallBack = nullptr;
            if (sv->device_data.ImageFormatSettings.ImageFormat.select == kSDIImageFormatPNM &&
                sv->device_data.ImageFormatSettings.OFDEnabled.select)
            {
                std::string message = (TranslationString::GetString().translation_str.PROGRESS_003.toLocal8Bit()).constData();
                saveProgressDialog = new QProgressDialog(message.c_str(),NULL, 0, 0, m_mainWindow);
                saveProgressDialog->setWindowModality(Qt::WindowModal);
                saveProgressDialog->setWindowFlags(Qt::WindowTitleHint | Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint) ;
                saveProgressDialog->setCancelButton(NULL);
                saveProgressDialog->setModal(true);
                saveProgressDialog->open();
                progressCallBack = MyProgessCallBack;
                QCoreApplication::processEvents();
                sleep(1);
                QCoreApplication::processEvents();
            }
            if(sv->Save_Image2(progressCallBack)){
                Configuration& config = Configuration::GetConfiguration();
                if(config.config_para.open_img_folder){
                    SaveDestFolder* folder = new SaveDestFolder();
                    if(folder){
                        if(!folder->open_folder(sv)){
                            m_messageBox->CreateMessageBox(TranslationString::GetString().translation_str.E_SAVE_001, TranslationString::GetString().translation_str.VERSION_003, Critical);
                        }
                        delete folder;
                        folder = NULL;
                    }
                }else {
                    const bool result = ES_CMN_FUNCS::PATH::ES_IsExistFile(sv->device_data.SelectPath);
                    if (!result) {
                        m_messageBox->CreateMessageBox(TranslationString::GetString().translation_str.E_SAVE_001, TranslationString::GetString().translation_str.VERSION_003, Critical);
                    }
                }
            }else {
                if(sv->m_LastError == kSDIErrorWriteFile){
                    m_messageBox->CreateMessageBox(TranslationString::GetString().translation_str.E_SAVE_001, TranslationString::GetString().translation_str.VERSION_003, Critical);
                }else {
                    if(sv->m_DoneBlanckPage && !sv->m_ExistsPage){
                        m_messageBox->CreateMessageBox(TranslationString::GetString().translation_str.A_SCAN_001, TranslationString::GetString().translation_str.VERSION_003, Warning);
                    }
                }
            }
            delete rotateImage;
            rotateImage = NULL;
        }
        if(sv->scanning_status == CANCEL){
            while(sv->outEventType != kSDITransferEventTypeComplete){
                if(sv->CheckNextTransferEvent(false))
                {
                    sv->Scanning();
                    sv->Dispose_Ptr();
                }else{
                    sv->outEventType = kSDITransferEventTypeComplete;
                }
            }
            SaveImagePathList::save_image_path_list.clear();
        }
        if(sv->scanning_status == DISCARD){
            if (sv->device_data.DuplexType.select == 1)
            {
                auto save_path = SaveImagePathList::save_image_path_list.end();
                for(int i = 0; i < 2; ++i)
                {
                    save_path--;
                    imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
                     std::string temp_str = temp_edit_info.file_path;
                    if(temp_str.c_str()){
                    SaveImagePathList::save_image_path_list.erase(save_path);
                    }
                }
            }
            else
            {
                auto save_path = SaveImagePathList::save_image_path_list.end();
                save_path--;
                imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
                std::string temp_str = temp_edit_info.file_path;
                if(temp_str.c_str()){
                 SaveImagePathList::save_image_path_list.erase(save_path);
                }
            }
            sv->scanning_status = CONTINUE;
        }
    }while(sv->scanning_status == CONTINUE);
    if (saveProgressDialog)
    {
        delete saveProgressDialog;
        saveProgressDialog = nullptr;
    }
}
