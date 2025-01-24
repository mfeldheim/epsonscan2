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
//  ui_documentsourcesettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DOCUMENTSOURCESETTINGSDIALOG_H
#define UI_DOCUMENTSOURCESETTINGSDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "afmtimeoutcombobox.h"
QT_BEGIN_NAMESPACE
class Ui_DocumentSourceSettingsDialog
{
public:
    QPushButton *Close_pushButton;
    QLabel *Afm_Timeout_label;
    AfmTimeoutCombobox *Afm_Timeout_comboBox;
    QLabel *Afm_Timeout_colon_label;
    void setupUi(QDialog *DocumentSourceSettingsDialog)
    {
        if (DocumentSourceSettingsDialog->objectName().isEmpty())
            DocumentSourceSettingsDialog->setObjectName(QStringLiteral("DocumentSourceSettingsDialog"));
        DocumentSourceSettingsDialog->resize(448, 156);
        QIcon icon;
        icon.addFile(QStringLiteral("../../Resources/Icons/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DocumentSourceSettingsDialog->setWindowIcon(icon);
        Close_pushButton = new QPushButton(DocumentSourceSettingsDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(350, 120, 80, 25));
        Afm_Timeout_label = new QLabel(DocumentSourceSettingsDialog);
        Afm_Timeout_label->setObjectName(QStringLiteral("Afm_Timeout_label"));
        Afm_Timeout_label->setGeometry(QRect(11, 41, 271, 41));
        Afm_Timeout_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        Afm_Timeout_label->setWordWrap(true);
        Afm_Timeout_comboBox = new AfmTimeoutCombobox(DocumentSourceSettingsDialog);
        Afm_Timeout_comboBox->setObjectName(QStringLiteral("Afm_Timeout_comboBox"));
        Afm_Timeout_comboBox->setGeometry(QRect(303, 41, 131, 23));
        Afm_Timeout_colon_label = new QLabel(DocumentSourceSettingsDialog);
        Afm_Timeout_colon_label->setObjectName(QStringLiteral("Afm_Timeout_colon_label"));
        Afm_Timeout_colon_label->setGeometry(QRect(290, 41, 16, 16));
        retranslateUi(DocumentSourceSettingsDialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), DocumentSourceSettingsDialog, SLOT(reject()));
        QObject::connect(Afm_Timeout_comboBox, SIGNAL(activated(int)), DocumentSourceSettingsDialog, SLOT(onValueChanged(int)));
        QMetaObject::connectSlotsByName(DocumentSourceSettingsDialog);
    }
    void retranslateUi(QDialog *DocumentSourceSettingsDialog)
    {
        DocumentSourceSettingsDialog->setWindowTitle(QApplication::translate("DocumentSourceSettingsDialog", "MAINSETTING_046", 0));
        Close_pushButton->setText(QApplication::translate("DocumentSourceSettingsDialog", "TC_PREVIEW_001", 0));
        Afm_Timeout_label->setText(QApplication::translate("DocumentSourceSettingsDialog", "CONFIG_DOC_018", 0));
        Afm_Timeout_colon_label->setText(QApplication::translate("DocumentSourceSettingsDialog", ":", 0));
    }
};
namespace Ui {
    class DocumentSourceSettingsDialog: public Ui_DocumentSourceSettingsDialog {};
}
QT_END_NAMESPACE
#endif
