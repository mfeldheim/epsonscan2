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
//  ui_addpagedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_ADDPAGEDIALOG_H
#define UI_ADDPAGEDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
QT_BEGIN_NAMESPACE
class Ui_AddPageDialog
{
public:
    QLabel *Scan_complete_label;
    QPushButton *Save_pushButton;
    QPushButton *Cancel_pushButton;
    QPushButton *Add_pushButton;
    void setupUi(QDialog *AddPageDialog)
    {
        if (AddPageDialog->objectName().isEmpty())
            AddPageDialog->setObjectName(QStringLiteral("AddPageDialog"));
        AddPageDialog->resize(758, 221);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddPageDialog->setWindowIcon(icon);
        Scan_complete_label = new QLabel(AddPageDialog);
        Scan_complete_label->setObjectName(QStringLiteral("Scan_complete_label"));
        Scan_complete_label->setGeometry(QRect(10, 10, 731, 151));
        Save_pushButton = new QPushButton(AddPageDialog);
        Save_pushButton->setObjectName(QStringLiteral("Save_pushButton"));
        Save_pushButton->setGeometry(QRect(531, 185, 94, 25));
        Cancel_pushButton = new QPushButton(AddPageDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(631, 185, 94, 25));
        Cancel_pushButton->setAutoDefault(false);
        Add_pushButton = new QPushButton(AddPageDialog);
        Add_pushButton->setObjectName(QStringLiteral("Add_pushButton"));
        Add_pushButton->setGeometry(QRect(431, 185, 94, 25));
        Add_pushButton->setAutoDefault(false);
        retranslateUi(AddPageDialog);
        QObject::connect(Save_pushButton, SIGNAL(clicked()), AddPageDialog, SLOT(reject()));
        QObject::connect(Add_pushButton, SIGNAL(clicked()), AddPageDialog, SLOT(onButtonPressed()));
        QObject::connect(Save_pushButton, SIGNAL(clicked()), AddPageDialog, SLOT(onButtonPressed()));
        QObject::connect(Cancel_pushButton, SIGNAL(clicked()), AddPageDialog, SLOT(onButtonPressed()));
        QObject::connect(Add_pushButton, SIGNAL(clicked()), AddPageDialog, SLOT(reject()));
        QMetaObject::connectSlotsByName(AddPageDialog);
    }
    void retranslateUi(QDialog *AddPageDialog)
    {
        AddPageDialog->setWindowTitle(QApplication::translate("AddPageDialog", "ADDPAGE_001", 0));
        Scan_complete_label->setText(QApplication::translate("AddPageDialog", "ADDPAGE_002", 0));
        Save_pushButton->setText(QApplication::translate("AddPageDialog", "ADDPAGE_006", 0));
        Cancel_pushButton->setText(QApplication::translate("AddPageDialog", "ADDPAGE_005", 0));
        Add_pushButton->setText(QApplication::translate("AddPageDialog", "ADDPAGE_004", 0));
    }
};
namespace Ui {
    class AddPageDialog: public Ui_AddPageDialog {};
}
QT_END_NAMESPACE
#endif
