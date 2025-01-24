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
//  ui_deviceconnectiondialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DEVICECONNECTIONDIALOG_H
#define UI_DEVICECONNECTIONDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
QT_BEGIN_NAMESPACE
class Ui_DeviceConnectionDialog
{
public:
    QLabel *Select_label;
    QProgressBar *scan_progressBar;
    void setupUi(QDialog *DeviceConnectionDialog)
    {
        if (DeviceConnectionDialog->objectName().isEmpty())
            DeviceConnectionDialog->setObjectName(QStringLiteral("DeviceConnectionDialog"));
        DeviceConnectionDialog->resize(412, 98);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DeviceConnectionDialog->setWindowIcon(icon);
#ifndef QT_NO_TOOLTIP
        DeviceConnectionDialog->setToolTip(QStringLiteral(""));
#endif
        Select_label = new QLabel(DeviceConnectionDialog);
        Select_label->setObjectName(QStringLiteral("Select_label"));
        Select_label->setGeometry(QRect(40, 20, 331, 23));
        scan_progressBar = new QProgressBar(DeviceConnectionDialog);
        scan_progressBar->setObjectName(QStringLiteral("scan_progressBar"));
        scan_progressBar->setGeometry(QRect(40, 43, 331, 23));
        scan_progressBar->setAcceptDrops(false);
        scan_progressBar->setMaximum(0);
        scan_progressBar->setValue(-1);
        scan_progressBar->setTextVisible(false);
        scan_progressBar->setInvertedAppearance(false);
        retranslateUi(DeviceConnectionDialog);
        QMetaObject::connectSlotsByName(DeviceConnectionDialog);
    }
    void retranslateUi(QDialog *DeviceConnectionDialog)
    {
        DeviceConnectionDialog->setWindowTitle(QApplication::translate("DeviceConnectionDialog", "COMMON_001", 0));
        Select_label->setText(QApplication::translate("DeviceConnectionDialog", "SCANNERSETTING_013", 0));
    }
};
namespace Ui {
    class DeviceConnectionDialog: public Ui_DeviceConnectionDialog {};
}
QT_END_NAMESPACE
#endif
