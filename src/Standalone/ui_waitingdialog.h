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
//  ui_waitingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_WAITINGDIALOG_H
#define UI_WAITINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
QT_BEGIN_NAMESPACE
class Ui_WaitingDialog
{
public:
    QLabel *Waiting_Message_label;
    QProgressBar *progressBar;
    void setupUi(QDialog *WaitingDialog)
    {
        if (WaitingDialog->objectName().isEmpty())
            WaitingDialog->setObjectName(QStringLiteral("WaitingDialog"));
        WaitingDialog->resize(457, 71);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        WaitingDialog->setWindowIcon(icon);
        Waiting_Message_label = new QLabel(WaitingDialog);
        Waiting_Message_label->setObjectName(QStringLiteral("Waiting_Message_label"));
        Waiting_Message_label->setGeometry(QRect(20, 5, 421, 21));
        Waiting_Message_label->setText(QStringLiteral("waiting message ..."));
        progressBar = new QProgressBar(WaitingDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(59, 30, 341, 23));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);
        progressBar->setFormat(QStringLiteral("%p%"));
        retranslateUi(WaitingDialog);
        QMetaObject::connectSlotsByName(WaitingDialog);
    }
    void retranslateUi(QDialog *WaitingDialog)
    {
        WaitingDialog->setWindowTitle(QApplication::translate("WaitingDialog", "MENU_001", 0));
    }
};
namespace Ui {
    class WaitingDialog: public Ui_WaitingDialog {};
}
QT_END_NAMESPACE
#endif
