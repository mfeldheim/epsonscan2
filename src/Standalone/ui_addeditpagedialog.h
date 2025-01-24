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
//  ui_addeditpagedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_ADDEDITPAGEDIALOG_H
#define UI_ADDEDITPAGEDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
QT_BEGIN_NAMESPACE
class Ui_addeditpageDialog
{
public:
    QLabel *Scan_complete_label;
    QLabel *Scan_complete_label_2;
    QPushButton *Add_pushButton;
    QPushButton *Edit_pushButton;
    QPushButton *Save_pushButton;
    QPushButton *Cancel_pushButton;
    void setupUi(QDialog *addeditpageDialog)
    {
        if (addeditpageDialog->objectName().isEmpty())
            addeditpageDialog->setObjectName(QStringLiteral("addeditpageDialog"));
        addeditpageDialog->resize(777, 344);
        QIcon icon;
        icon.addFile(QStringLiteral("icons/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addeditpageDialog->setWindowIcon(icon);
        Scan_complete_label = new QLabel(addeditpageDialog);
        Scan_complete_label->setObjectName(QStringLiteral("Scan_complete_label"));
        Scan_complete_label->setGeometry(QRect(20, 20, 731, 151));
        Scan_complete_label_2 = new QLabel(addeditpageDialog);
        Scan_complete_label_2->setObjectName(QStringLiteral("Scan_complete_label_2"));
        Scan_complete_label_2->setGeometry(QRect(20, 190, 731, 71));
        Add_pushButton = new QPushButton(addeditpageDialog);
        Add_pushButton->setObjectName(QStringLiteral("Add_pushButton"));
        Add_pushButton->setGeometry(QRect(422, 300, 94, 25));
        Add_pushButton->setAutoDefault(false);
        Edit_pushButton = new QPushButton(addeditpageDialog);
        Edit_pushButton->setObjectName(QStringLiteral("Edit_pushButton"));
        Edit_pushButton->setGeometry(QRect(306, 300, 94, 25));
        Edit_pushButton->setAutoDefault(false);
        Save_pushButton = new QPushButton(addeditpageDialog);
        Save_pushButton->setObjectName(QStringLiteral("Save_pushButton"));
        Save_pushButton->setGeometry(QRect(539, 300, 94, 25));
        Cancel_pushButton = new QPushButton(addeditpageDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(655, 300, 94, 25));
        Cancel_pushButton->setAutoDefault(false);
        retranslateUi(addeditpageDialog);
        QObject::connect(Save_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(reject()));
        QObject::connect(Cancel_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(onButtonPressed()));
        QObject::connect(Save_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(onButtonPressed()));
        QObject::connect(Edit_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(onButtonPressed()));
        QObject::connect(Add_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(reject()));
        QObject::connect(Add_pushButton, SIGNAL(clicked()), addeditpageDialog, SLOT(onButtonPressed()));
        QMetaObject::connectSlotsByName(addeditpageDialog);
    }
    void retranslateUi(QDialog *addeditpageDialog)
    {
        addeditpageDialog->setWindowTitle(QApplication::translate("addeditpageDialog", "ADDPAGE_001", 0));
        Scan_complete_label->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_002", 0));
        Scan_complete_label_2->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_003", 0));
        Add_pushButton->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_004", 0));
        Edit_pushButton->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_007", 0));
        Save_pushButton->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_006", 0));
        Cancel_pushButton->setText(QApplication::translate("addeditpageDialog", "ADDPAGE_005", 0));
    }
};
namespace Ui {
    class addeditpageDialog: public Ui_addeditpageDialog {};
}
QT_END_NAMESPACE
#endif
