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
//  ui_administratorpasswordinputdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_ADMINISTRATORPASSWORDINPUTDIALOG_H
#define UI_ADMINISTRATORPASSWORDINPUTDIALOG_H 
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
class Ui_AdministratorPasswordInputDialog
{
public:
    QPushButton *OK_pushButton;
    QPushButton *Cancel_pushButton;
    QLabel *Explanation_label;
    QLabel *Password_label;
    QLineEdit *Password_Input_lineEdit;
    QLabel *Password_colon_label;
    void setupUi(QDialog *AdministratorPasswordInputDialog)
    {
        if (AdministratorPasswordInputDialog->objectName().isEmpty())
            AdministratorPasswordInputDialog->setObjectName(QStringLiteral("AdministratorPasswordInputDialog"));
        AdministratorPasswordInputDialog->resize(400, 300);
        OK_pushButton = new QPushButton(AdministratorPasswordInputDialog);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));
        OK_pushButton->setEnabled(false);
        OK_pushButton->setGeometry(QRect(160, 260, 101, 25));
        Cancel_pushButton = new QPushButton(AdministratorPasswordInputDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(270, 260, 101, 25));
        Explanation_label = new QLabel(AdministratorPasswordInputDialog);
        Explanation_label->setObjectName(QStringLiteral("Explanation_label"));
        Explanation_label->setGeometry(QRect(20, 20, 351, 101));
        Explanation_label->setScaledContents(false);
        Explanation_label->setWordWrap(true);
        Password_label = new QLabel(AdministratorPasswordInputDialog);
        Password_label->setObjectName(QStringLiteral("Password_label"));
        Password_label->setGeometry(QRect(30, 140, 111, 31));
        Password_label->setScaledContents(false);
        Password_label->setWordWrap(true);
        Password_Input_lineEdit = new QLineEdit(AdministratorPasswordInputDialog);
        Password_Input_lineEdit->setObjectName(QStringLiteral("Password_Input_lineEdit"));
        Password_Input_lineEdit->setGeometry(QRect(160, 147, 201, 23));
        Password_Input_lineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        Password_Input_lineEdit->setEchoMode(QLineEdit::Password);
        Password_Input_lineEdit->setClearButtonEnabled(false);
        Password_colon_label = new QLabel(AdministratorPasswordInputDialog);
        Password_colon_label->setObjectName(QStringLiteral("Password_colon_label"));
        Password_colon_label->setGeometry(QRect(150, 140, 16, 31));
        Password_colon_label->setScaledContents(false);
        Password_colon_label->setWordWrap(true);
        retranslateUi(AdministratorPasswordInputDialog);
        QObject::connect(OK_pushButton, SIGNAL(pressed()), AdministratorPasswordInputDialog, SLOT(PushButtonAction()));
        QObject::connect(Cancel_pushButton, SIGNAL(pressed()), AdministratorPasswordInputDialog, SLOT(PushButtonAction()));
        QObject::connect(Password_Input_lineEdit, SIGNAL(textEdited(QString)), AdministratorPasswordInputDialog, SLOT(LineEditFinished()));
        QMetaObject::connectSlotsByName(AdministratorPasswordInputDialog);
    }
    void retranslateUi(QDialog *AdministratorPasswordInputDialog)
    {
        AdministratorPasswordInputDialog->setWindowTitle(QApplication::translate("AdministratorPasswordInputDialog", "ES2U_MAIN_069", 0));
        OK_pushButton->setText(QApplication::translate("AdministratorPasswordInputDialog", "ES2U_MAIN_046", 0));
        Cancel_pushButton->setText(QApplication::translate("AdministratorPasswordInputDialog", "ES2U_MAIN_047", 0));
        Explanation_label->setText(QApplication::translate("AdministratorPasswordInputDialog", "ES2U_MAIN_070", 0));
        Password_label->setText(QApplication::translate("AdministratorPasswordInputDialog", "ACCESSCONTROL_006", 0));
        Password_colon_label->setText(QApplication::translate("AdministratorPasswordInputDialog", ":", 0));
    }
};
namespace Ui {
    class AdministratorPasswordInputDialog: public Ui_AdministratorPasswordInputDialog {};
}
QT_END_NAMESPACE
#endif
