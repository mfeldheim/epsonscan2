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
//  custommessagebox.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "custommessagebox.h"
#include "continuousscandialog.h"
#include "translationstring.h"
#include "../Include/Config.h"
#include <QCheckBox>
CustomMessageBox::CustomMessageBox(QWidget* parent)
{
    parent_dialog = parent;
}
bool CustomMessageBox::CreateMessageBox(QString message, QString button_message, IconType type, bool use_doNotShow)
{
    QMessageBox msgBox(parent_dialog);
    msgBox.setText(message + "\n");
#ifdef AKBMODE
    msgBox.setWindowTitle(DRIVER_TITLE);
#else
    msgBox.setWindowTitle(TranslationString::GetString().translation_str.MENU_001);
#endif
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, button_message);
    switch (type){
        case Question:
            msgBox.setIcon(QMessageBox::Question);
            break;
        case Information:
            msgBox.setIcon(QMessageBox::Information);
            break;
        case Warning:
            msgBox.setIcon(QMessageBox::Warning);
            break;
        case Critical:
            msgBox.setIcon(QMessageBox::Critical);
            break;
    }
    if(use_doNotShow){
        QCheckBox *doNotShowCheckBox = new QCheckBox(TranslationString::GetString().translation_str.LINUX_C_UI_002, parent_dialog);
        doNotShowCheckBox->setGeometry(10, 30, 0, 300);
        msgBox.setCheckBox(doNotShowCheckBox);
        msgBox.exec();
        if(doNotShowCheckBox->checkState() == Qt::Checked ){
            return true;
        }
    }else {
        msgBox.exec();
    }
    return false;
}
bool CustomMessageBox::CreateSelectableMessageBox(QString message, IconType type)
{
    QMessageBox msgBox(parent_dialog);
    msgBox.setText(message + "\n");
#ifdef AKBMODE
    msgBox.setWindowTitle(DRIVER_TITLE);
#else
    msgBox.setWindowTitle(TranslationString::GetString().translation_str.MENU_001);
#endif
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, TranslationString::GetString().translation_str.ES2U_MAIN_052);
    msgBox.setButtonText(QMessageBox::No, TranslationString::GetString().translation_str.ES2U_MAIN_053);
    switch (type){
        case Question:
            msgBox.setIcon(QMessageBox::Question);
            break;
        case Information:
            msgBox.setIcon(QMessageBox::Information);
            break;
        case Warning:
            msgBox.setIcon(QMessageBox::Warning);
            break;
        case Critical:
            msgBox.setIcon(QMessageBox::Critical);
            break;
    }
    int res = msgBox.exec();
    if (res == QMessageBox::Yes){
        return true;
    } else if (res == QMessageBox::No) {
        return false;
    }
    return false;
}
void CustomMessageBox::ErrorMessageBox(Supervisor* sv, bool Preview)
{
    QString error_message;
    IconType type = Warning;
    if(sv->m_LastError != kSDIErrorNone){
        if(sv->m_LastError == kSDIErrorPaperEmpty){
            error_message = TranslationString::GetString().translation_str.E_SCAN_101;
        }else if(sv->m_LastError == kSDIErrorPaperJam){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_103;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.CONFIRMCONTINUE_008);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorPaperDoubleFeed){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_104;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.CONFIRMCONTINUE_002);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorPaperDoubleFeed2){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_104;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.CONFIRMCONTINUE_013, AFTER_EJECT);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorPaperProtect){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_103;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.CONFIRMCONTINUE_011);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorDeviceInBusy){
            error_message = TranslationString::GetString().translation_str.E_COMM_001;
        }else if(sv->m_LastError == kSDIErrorCoverOpen){
            error_message = TranslationString::GetString().translation_str.E_SCAN_102;
        }else if(sv->m_LastError == kSDIErrorTrayClose){
            error_message = TranslationString::GetString().translation_str.E_SCAN_105;
        }else if(sv->m_LastError == kSDIErrorInvalidResponse){
            error_message = TranslationString::GetString().translation_str.E_SCAN_003;
        }else if(sv->m_LastError == kSDIErrorNoMemory){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_ENV_001;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDITransferEventTypeCancel){
            return;
        }else if(sv->m_LastError == kSDIErrorDataSend){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_COMM_103;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorDataReceive){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_COMM_102;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorDeviceInUse){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_COMM_001;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorWriteFile){
            error_message = TranslationString::GetString().translation_str.E_SAVE_001;
        }else if(sv->m_LastError == kSDIErrorUnknownError){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_SCAN_001;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorDeviceFormChangedInterruptedly){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_110;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.E_SCAN_111);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorDeviceFormUnstable){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_SCAN_109;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorSepLeverChangedInterruptedly){
            if(Preview){
                error_message = TranslationString::GetString().translation_str.E_SCAN_113;
                sv->scanning_status = CANCEL;
            }else {
                this->PaperJamDialog(sv, TranslationString::GetString().translation_str.E_SCAN_114);
                return;
            }
        }else if(sv->m_LastError == kSDIErrorUnscannableDeviceConfig1){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_SCAN_107;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorETSensorError || sv->m_LastError == kSDIErrorPESensorError){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.A_UNIT_007;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorUserAuthEnabled){
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_UNIT_008;
            sv->scanning_status = ERROR;
        }else if(sv->m_LastError == kSDIErrorPaperRemoveError){
            error_message = TranslationString::GetString().translation_str.E_SCAN_117;
            sv->scanning_status = CANCEL;
        }else if(sv->m_LastError == kSDIErrorSkewDetectError){
            error_message = TranslationString::GetString().translation_str.E_SCAN_118;
            sv->scanning_status = CANCEL;
        }else if(sv->m_LastError == kSDIErrorDeviceFatalError){
            error_message = TranslationString::GetString().translation_str.E_SCAN_003 + "\n(E425-" + QString::number(sv->CheckDeviceErrorStatus()) + ")";
        }else {
            type = Critical;
            error_message = TranslationString::GetString().translation_str.E_SCAN_001;
            sv->scanning_status = ERROR;
        }
    }else {
        return;
    }
    CreateMessageBox(error_message, TranslationString::GetString().translation_str.VERSION_003, Warning);
}
void CustomMessageBox::PaperJamDialog(Supervisor* sv, QString message, DoubleFeedMode dialog_type)
{
    ContinuousScanDialog* continuous_dialog = new ContinuousScanDialog(sv);
    if(continuous_dialog == NULL){
        return;
    }
    do{
        continuous_dialog->Initialize(message, dialog_type);
        if(continuous_dialog->isHidden()){
            continuous_dialog->exec();
        }else {
            continuous_dialog->activateWindow();
        }
        sv->scanning_status = continuous_dialog->GetScanningStatus();
        if(dialog_type == AFTER_EJECT && !sv->device_data.AutomaticFeedingMode.select){
            if(sv->scanning_status == DISCARD || sv->scanning_status == CONTINUE){
                if(sv->device_data.FunctionalUnit.select == kSDIFunctionalUnitDocumentFeeder){
                    if(!sv->GetPaperLoadedStatus()){
                        sv->m_LastError = kSDIErrorPaperEmpty;
                        if(sv->scanning_status == DISCARD){
                            this->ErrorMessageBox(sv);
                        }
                    }else {
                        sv->m_LastError = sv->CheckDeviceErrorStatus();
                    }
                }else {
                    sv->m_LastError = sv->CheckDeviceErrorStatus();
                }
            }
        }
        if(sv->device_data.AutomaticFeedingMode.select){
           break;
        }
    }while(sv->m_LastError == kSDIErrorPaperEmpty && sv->scanning_status == DISCARD);
    if(sv->m_LastError == kSDIErrorCoverOpen){
        if(sv->scanning_status == CONTINUE || sv->scanning_status == DISCARD){
            this->ErrorMessageBox(sv);
        }
    }
}
