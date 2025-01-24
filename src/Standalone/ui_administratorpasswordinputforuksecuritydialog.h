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
//  ui_administratorpasswordinputforuksecuritydialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_ADMINISTRATORPASSWORDINPUTFORUKSECURITYDIALOG_H
#define UI_ADMINISTRATORPASSWORDINPUTFORUKSECURITYDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
QT_BEGIN_NAMESPACE
class Ui_AdministratorPasswordInputForUKSecurityDialog
{
public:
    QPushButton *OK_pushButton;
    QPushButton *Cancel_pushButton;
    QLabel *Password_label;
    QLabel *Password_colon_label;
    QLineEdit *Password_Input_lineEdit;
    QLabel *Explanation_label;
    QLabel *UKSecurity_label;
    QLabel *HyperLink_label;
    void setupUi(QDialog *AdministratorPasswordInputForUKSecurityDialog)
    {
        if (AdministratorPasswordInputForUKSecurityDialog->objectName().isEmpty())
            AdministratorPasswordInputForUKSecurityDialog->setObjectName(QStringLiteral("AdministratorPasswordInputForUKSecurityDialog"));
        AdministratorPasswordInputForUKSecurityDialog->resize(400, 470);
        OK_pushButton = new QPushButton(AdministratorPasswordInputForUKSecurityDialog);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));
        OK_pushButton->setEnabled(false);
        OK_pushButton->setGeometry(QRect(160, 260, 101, 25));
        Cancel_pushButton = new QPushButton(AdministratorPasswordInputForUKSecurityDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(270, 260, 101, 25));
        Password_label = new QLabel(AdministratorPasswordInputForUKSecurityDialog);
        Password_label->setObjectName(QStringLiteral("Password_label"));
        Password_label->setGeometry(QRect(30, 140, 111, 31));
        Password_label->setScaledContents(false);
        Password_label->setWordWrap(true);
        Password_colon_label = new QLabel(AdministratorPasswordInputForUKSecurityDialog);
        Password_colon_label->setObjectName(QStringLiteral("Password_colon_label"));
        Password_colon_label->setGeometry(QRect(150, 140, 16, 31));
        Password_colon_label->setScaledContents(false);
        Password_colon_label->setWordWrap(true);
        Password_Input_lineEdit = new QLineEdit(AdministratorPasswordInputForUKSecurityDialog);
        Password_Input_lineEdit->setObjectName(QStringLiteral("Password_Input_lineEdit"));
        Password_Input_lineEdit->setGeometry(QRect(160, 147, 201, 25));
        Password_Input_lineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        Password_Input_lineEdit->setEchoMode(QLineEdit::Password);
        Password_Input_lineEdit->setClearButtonEnabled(false);
        Explanation_label = new QLabel(AdministratorPasswordInputForUKSecurityDialog);
        Explanation_label->setObjectName(QStringLiteral("Explanation_label"));
        Explanation_label->setGeometry(QRect(20, 20, 351, 101));
        Explanation_label->setScaledContents(false);
        Explanation_label->setWordWrap(true);
        UKSecurity_label = new QLabel(AdministratorPasswordInputForUKSecurityDialog);
        UKSecurity_label->setObjectName(QStringLiteral("UKSecurity_label"));
        UKSecurity_label->setGeometry(QRect(20, 290, 341, 131));
        UKSecurity_label->setScaledContents(false);
        UKSecurity_label->setWordWrap(true);
        HyperLink_label = new QLabel(AdministratorPasswordInputForUKSecurityDialog);
        HyperLink_label->setObjectName(QStringLiteral("HyperLink_label"));
        HyperLink_label->setGeometry(QRect(20, 420, 370, 40));
        HyperLink_label->setScaledContents(false);
        HyperLink_label->setWordWrap(true);
        retranslateUi(AdministratorPasswordInputForUKSecurityDialog);
        QObject::connect(OK_pushButton, SIGNAL(pressed()), AdministratorPasswordInputForUKSecurityDialog, SLOT(PushButtonAction()));
        QObject::connect(Cancel_pushButton, SIGNAL(pressed()), AdministratorPasswordInputForUKSecurityDialog, SLOT(PushButtonAction()));
        QObject::connect(Password_Input_lineEdit, SIGNAL(textEdited(QString)), AdministratorPasswordInputForUKSecurityDialog, SLOT(LineEditFinished()));
        QMetaObject::connectSlotsByName(AdministratorPasswordInputForUKSecurityDialog);
    }
    void retranslateUi(QDialog *AdministratorPasswordInputForUKSecurityDialog)
    {
        AdministratorPasswordInputForUKSecurityDialog->setWindowTitle(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ES2U_MAIN_069", 0));
        OK_pushButton->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ES2U_MAIN_046", 0));
        Cancel_pushButton->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ES2U_MAIN_047", 0));
        Password_label->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ACCESSCONTROL_006", 0));
        Password_colon_label->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", ":", 0));
        Explanation_label->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ES2U_MAIN_070", 0));
        UKSecurity_label->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "ES2U_MAIN_071", 0));
        HyperLink_label->setText(QApplication::translate("AdministratorPasswordInputForUKSecurityDialog", "https://support.epson.net/manu/adminpw/index.html", 0));
    }
};
namespace Ui {
    class AdministratorPasswordInputForUKSecurityDialog: public Ui_AdministratorPasswordInputForUKSecurityDialog {};
}
QT_END_NAMESPACE
#endif
