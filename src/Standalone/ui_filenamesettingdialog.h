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
//  ui_filenamesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_FILENAMESETTINGDIALOG_H
#define UI_FILENAMESETTINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include "detectpapercheckbox.h"
QT_BEGIN_NAMESPACE
class Ui_FileNameSettingDialog
{
public:
    QPushButton *Close_pushButton;
    DetectPaperCheckBox *File_Counter_checkBox;
    DetectPaperCheckBox *Samename_Overwrite_checkBox;
    void setupUi(QDialog *FileNameSettingDialog)
    {
        if (FileNameSettingDialog->objectName().isEmpty())
            FileNameSettingDialog->setObjectName(QStringLiteral("FileNameSettingDialog"));
        FileNameSettingDialog->resize(422, 239);
        Close_pushButton = new QPushButton(FileNameSettingDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(320, 198, 80, 25));
        File_Counter_checkBox = new DetectPaperCheckBox(FileNameSettingDialog);
        File_Counter_checkBox->setObjectName(QStringLiteral("File_Counter_checkBox"));
        File_Counter_checkBox->setGeometry(QRect(40, 60, 351, 23));
        Samename_Overwrite_checkBox = new DetectPaperCheckBox(FileNameSettingDialog);
        Samename_Overwrite_checkBox->setObjectName(QStringLiteral("Samename_Overwrite_checkBox"));
        Samename_Overwrite_checkBox->setGeometry(QRect(40, 110, 351, 23));
        retranslateUi(FileNameSettingDialog);
        QObject::connect(File_Counter_checkBox, SIGNAL(clicked(bool)), FileNameSettingDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Samename_Overwrite_checkBox, SIGNAL(clicked(bool)), FileNameSettingDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Close_pushButton, SIGNAL(clicked()), FileNameSettingDialog, SLOT(reject()));
        QMetaObject::connectSlotsByName(FileNameSettingDialog);
    }
    void retranslateUi(QDialog *FileNameSettingDialog)
    {
        FileNameSettingDialog->setWindowTitle(QApplication::translate("FileNameSettingDialog", "FILENAMESETTING_001", 0));
        Close_pushButton->setText(QApplication::translate("FileNameSettingDialog", "TC_PREVIEW_001", 0));
        File_Counter_checkBox->setText(QApplication::translate("FileNameSettingDialog", "FILENAMESETTING_007", 0));
        Samename_Overwrite_checkBox->setText(QApplication::translate("FileNameSettingDialog", "FILENAMESETTING_016", 0));
    }
};
namespace Ui {
    class FileNameSettingDialog: public Ui_FileNameSettingDialog {};
}
QT_END_NAMESPACE
#endif
