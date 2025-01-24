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
//  ui_automaticfeedingmodedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_AUTOMATICFEEDINGMODEDIALOG_H
#define UI_AUTOMATICFEEDINGMODEDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
QT_BEGIN_NAMESPACE
class Ui_AutomaticFeedingModeDialog
{
public:
    QPushButton *Finish_pushButton;
    QLabel *AutoFeedMode_label;
    QToolButton *Icon_toolButton;
    QLabel *progress_label;
    QPushButton *cancel_pushButton;
    QProgressBar *scan_progressBar;
    void setupUi(QDialog *AutomaticFeedingModeDialog)
    {
        if (AutomaticFeedingModeDialog->objectName().isEmpty())
            AutomaticFeedingModeDialog->setObjectName(QStringLiteral("AutomaticFeedingModeDialog"));
        AutomaticFeedingModeDialog->resize(517, 308);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AutomaticFeedingModeDialog->setWindowIcon(icon);
        Finish_pushButton = new QPushButton(AutomaticFeedingModeDialog);
        Finish_pushButton->setObjectName(QStringLiteral("Finish_pushButton"));
        Finish_pushButton->setGeometry(QRect(410, 270, 91, 25));
        AutoFeedMode_label = new QLabel(AutomaticFeedingModeDialog);
        AutoFeedMode_label->setObjectName(QStringLiteral("AutoFeedMode_label"));
        AutoFeedMode_label->setGeometry(QRect(90, 20, 411, 151));
        AutoFeedMode_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        AutoFeedMode_label->setWordWrap(true);
        Icon_toolButton = new QToolButton(AutomaticFeedingModeDialog);
        Icon_toolButton->setObjectName(QStringLiteral("Icon_toolButton"));
        Icon_toolButton->setEnabled(true);
        Icon_toolButton->setGeometry(QRect(0, 0, 81, 81));
#ifndef QT_NO_TOOLTIP
        Icon_toolButton->setToolTip(QStringLiteral(""));
#endif
        Icon_toolButton->setText(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/bmp_mss_image@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        Icon_toolButton->setIcon(icon1);
        Icon_toolButton->setIconSize(QSize(90, 90));
        Icon_toolButton->setCheckable(false);
        Icon_toolButton->setChecked(false);
        Icon_toolButton->setAutoRepeat(false);
        Icon_toolButton->setAutoExclusive(false);
        Icon_toolButton->setPopupMode(QToolButton::DelayedPopup);
        Icon_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Icon_toolButton->setAutoRaise(true);
        Icon_toolButton->setArrowType(Qt::NoArrow);
        progress_label = new QLabel(AutomaticFeedingModeDialog);
        progress_label->setObjectName(QStringLiteral("progress_label"));
        progress_label->setGeometry(QRect(89, 200, 231, 23));
        cancel_pushButton = new QPushButton(AutomaticFeedingModeDialog);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setEnabled(false);
        cancel_pushButton->setGeometry(QRect(310, 270, 91, 25));
        scan_progressBar = new QProgressBar(AutomaticFeedingModeDialog);
        scan_progressBar->setObjectName(QStringLiteral("scan_progressBar"));
        scan_progressBar->setGeometry(QRect(90, 230, 321, 23));
        scan_progressBar->setAcceptDrops(false);
        scan_progressBar->setMaximum(100);
        scan_progressBar->setValue(-1);
        scan_progressBar->setTextVisible(false);
        scan_progressBar->setInvertedAppearance(false);
        retranslateUi(AutomaticFeedingModeDialog);
        QObject::connect(Finish_pushButton, SIGNAL(clicked()), AutomaticFeedingModeDialog, SLOT(reject()));
        QObject::connect(cancel_pushButton, SIGNAL(clicked()), AutomaticFeedingModeDialog, SLOT(Cancel()));
        QMetaObject::connectSlotsByName(AutomaticFeedingModeDialog);
    }
    void retranslateUi(QDialog *AutomaticFeedingModeDialog)
    {
        AutomaticFeedingModeDialog->setWindowTitle(QApplication::translate("AutomaticFeedingModeDialog", "MAINSETTING_007", 0));
        Finish_pushButton->setText(QApplication::translate("AutomaticFeedingModeDialog", "AUTOFEEDMODE_003", 0));
        AutoFeedMode_label->setText(QApplication::translate("AutomaticFeedingModeDialog", "AUTOFEEDMODE_002", 0));
        progress_label->setText(QApplication::translate("AutomaticFeedingModeDialog", "PROGRESS_008", 0));
        cancel_pushButton->setText(QApplication::translate("AutomaticFeedingModeDialog", "PROGRESS_017", 0));
    }
};
namespace Ui {
    class AutomaticFeedingModeDialog: public Ui_AutomaticFeedingModeDialog {};
}
QT_END_NAMESPACE
#endif
