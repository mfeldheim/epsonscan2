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
//  ui_deviceselectdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DEVICESELECTDIALOG_H
#define UI_DEVICESELECTDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "initdeviceselectcombobox.h"
QT_BEGIN_NAMESPACE
class Ui_DeviceSelectDialog
{
public:
    QLabel *Select_label;
    InitDeviceSelectCombobox *Select_Device_comboBox;
    QPushButton *Connecting_pushButton;
    QToolButton *Update_toolButton;
    void setupUi(QDialog *DeviceSelectDialog)
    {
        if (DeviceSelectDialog->objectName().isEmpty())
            DeviceSelectDialog->setObjectName(QStringLiteral("DeviceSelectDialog"));
        DeviceSelectDialog->setWindowModality(Qt::NonModal);
        DeviceSelectDialog->setEnabled(true);
        DeviceSelectDialog->resize(376, 113);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DeviceSelectDialog->sizePolicy().hasHeightForWidth());
        DeviceSelectDialog->setSizePolicy(sizePolicy);
        DeviceSelectDialog->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DeviceSelectDialog->setWindowIcon(icon);
        DeviceSelectDialog->setSizeGripEnabled(false);
        DeviceSelectDialog->setModal(false);
        Select_label = new QLabel(DeviceSelectDialog);
        Select_label->setObjectName(QStringLiteral("Select_label"));
        Select_label->setGeometry(QRect(40, 20, 281, 16));
        Select_Device_comboBox = new InitDeviceSelectCombobox(DeviceSelectDialog);
        Select_Device_comboBox->setObjectName(QStringLiteral("Select_Device_comboBox"));
        Select_Device_comboBox->setGeometry(QRect(40, 40, 281, 22));
        Connecting_pushButton = new QPushButton(DeviceSelectDialog);
        Connecting_pushButton->setObjectName(QStringLiteral("Connecting_pushButton"));
        Connecting_pushButton->setGeometry(QRect(270, 76, 91, 25));
        Update_toolButton = new QToolButton(DeviceSelectDialog);
        Update_toolButton->setObjectName(QStringLiteral("Update_toolButton"));
        Update_toolButton->setEnabled(true);
        Update_toolButton->setGeometry(QRect(331, 35, 31, 31));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/update4.png"), QSize(), QIcon::Normal, QIcon::Off);
        Update_toolButton->setIcon(icon1);
        Update_toolButton->setIconSize(QSize(25, 25));
        Update_toolButton->setCheckable(false);
        Update_toolButton->setAutoRepeat(false);
        Update_toolButton->setAutoExclusive(false);
        Update_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Update_toolButton->setAutoRaise(true);
        retranslateUi(DeviceSelectDialog);
        QObject::connect(Select_Device_comboBox, SIGNAL(activated(int)), DeviceSelectDialog, SLOT(onValueChanged(int)));
        QObject::connect(Connecting_pushButton, SIGNAL(clicked()), DeviceSelectDialog, SLOT(PushEventButton()));
        QObject::connect(Update_toolButton, SIGNAL(clicked()), DeviceSelectDialog, SLOT(PushEventButton()));
        QMetaObject::connectSlotsByName(DeviceSelectDialog);
    }
    void retranslateUi(QDialog *DeviceSelectDialog)
    {
        DeviceSelectDialog->setWindowTitle(QApplication::translate("DeviceSelectDialog", "MENU_001", 0));
        Select_label->setText(QApplication::translate("DeviceSelectDialog", "LINUX_DEVICESELECT_001", 0));
        Connecting_pushButton->setText(QApplication::translate("DeviceSelectDialog", "LINUX_DEVICESELECT_002", 0));
        Update_toolButton->setText(QString());
    }
};
namespace Ui {
    class DeviceSelectDialog: public Ui_DeviceSelectDialog {};
}
QT_END_NAMESPACE
#endif
