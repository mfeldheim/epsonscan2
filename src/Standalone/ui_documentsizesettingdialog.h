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
//  ui_documentsizesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DOCUMENTSIZESETTINGDIALOG_H
#define UI_DOCUMENTSIZESETTINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include "autocroppinginscribedcheckbox.h"
QT_BEGIN_NAMESPACE
class Ui_DocumentSizeSettingDialog
{
public:
    AutoCroppingInscribedCheckBox *Black_edge_inscribed_checkBox;
    QPushButton *Close_pushButton;
    void setupUi(QDialog *DocumentSizeSettingDialog)
    {
        if (DocumentSizeSettingDialog->objectName().isEmpty())
            DocumentSizeSettingDialog->setObjectName(QStringLiteral("DocumentSizeSettingDialog"));
        DocumentSizeSettingDialog->resize(461, 80);
        Black_edge_inscribed_checkBox = new AutoCroppingInscribedCheckBox(DocumentSizeSettingDialog);
        Black_edge_inscribed_checkBox->setObjectName(QStringLiteral("Black_edge_inscribed_checkBox"));
        Black_edge_inscribed_checkBox->setGeometry(QRect(10, 20, 441, 18));
        Close_pushButton = new QPushButton(DocumentSizeSettingDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(320, 50, 131, 25));
        retranslateUi(DocumentSizeSettingDialog);
        QObject::connect(Black_edge_inscribed_checkBox, SIGNAL(clicked(bool)), DocumentSizeSettingDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Close_pushButton, SIGNAL(clicked(bool)), DocumentSizeSettingDialog, SLOT(reject()));
        QMetaObject::connectSlotsByName(DocumentSizeSettingDialog);
    }
    void retranslateUi(QDialog *DocumentSizeSettingDialog)
    {
        DocumentSizeSettingDialog->setWindowTitle(QApplication::translate("DocumentSizeSettingDialog", "MAINSETTING_045", 0));
        Black_edge_inscribed_checkBox->setText(QApplication::translate("DocumentSizeSettingDialog", "MAINSETTING_86", 0));
        Close_pushButton->setText(QApplication::translate("DocumentSizeSettingDialog", "TC_PREVIEW_001", 0));
    }
};
namespace Ui {
    class DocumentSizeSettingDialog: public Ui_DocumentSizeSettingDialog {};
}
QT_END_NAMESPACE
#endif
