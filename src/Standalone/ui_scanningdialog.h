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
//  ui_scanningdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_SCANNINGDIALOG_H
#define UI_SCANNINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
QT_BEGIN_NAMESPACE
class Ui_ScanningDialog
{
public:
    QProgressBar *scan_progressBar;
    QPushButton *cancel_pushButton;
    QLabel *progress_label;
    void setupUi(QDialog *ScanningDialog)
    {
        if (ScanningDialog->objectName().isEmpty())
            ScanningDialog->setObjectName(QStringLiteral("ScanningDialog"));
        ScanningDialog->resize(392, 121);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ScanningDialog->setWindowIcon(icon);
        scan_progressBar = new QProgressBar(ScanningDialog);
        scan_progressBar->setObjectName(QStringLiteral("scan_progressBar"));
        scan_progressBar->setGeometry(QRect(35, 50, 321, 23));
        scan_progressBar->setAcceptDrops(false);
        scan_progressBar->setMaximum(0);
        scan_progressBar->setValue(-1);
        scan_progressBar->setTextVisible(false);
        scan_progressBar->setInvertedAppearance(false);
        cancel_pushButton = new QPushButton(ScanningDialog);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setGeometry(QRect(252, 86, 101, 25));
        progress_label = new QLabel(ScanningDialog);
        progress_label->setObjectName(QStringLiteral("progress_label"));
        progress_label->setGeometry(QRect(34, 20, 231, 23));
        retranslateUi(ScanningDialog);
        QObject::connect(cancel_pushButton, SIGNAL(clicked()), ScanningDialog, SLOT(Cancel()));
        QMetaObject::connectSlotsByName(ScanningDialog);
    }
    void retranslateUi(QDialog *ScanningDialog)
    {
        ScanningDialog->setWindowTitle(QApplication::translate("ScanningDialog", "PROGRESS_001", 0));
        cancel_pushButton->setText(QApplication::translate("ScanningDialog", "PROGRESS_017", 0));
        progress_label->setText(QApplication::translate("ScanningDialog", "PROGRESS_008", 0));
    }
};
namespace Ui {
    class ScanningDialog: public Ui_ScanningDialog {};
}
QT_END_NAMESPACE
#endif
