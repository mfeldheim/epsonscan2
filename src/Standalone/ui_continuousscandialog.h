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
//  ui_continuousscandialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_CONTINUOUSSCANDIALOG_H
#define UI_CONTINUOUSSCANDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
QT_BEGIN_NAMESPACE
class Ui_ContinuousScanDialog
{
public:
    QGraphicsView *graphicsView;
    QPushButton *Stop_pushButton;
    QPushButton *Save_pushButton;
    QPushButton *Continue_pushButton;
    QLabel *last_scanimage_label;
    QLabel *continuous_label;
    QToolButton *Icon_toolButton;
    QFrame *frame;
    QLabel *noimage_label;
    QLabel *ADFSpecialErrorMessageForPassport_label;
    void setupUi(QDialog *ContinuousScanDialog)
    {
        if (ContinuousScanDialog->objectName().isEmpty())
            ContinuousScanDialog->setObjectName(QStringLiteral("ContinuousScanDialog"));
        ContinuousScanDialog->resize(640, 367);
        QIcon icon;
        icon.addFile(QStringLiteral("../../Resources/Icons/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ContinuousScanDialog->setWindowIcon(icon);
        graphicsView = new QGraphicsView(ContinuousScanDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(410, 30, 16, 16));
        Stop_pushButton = new QPushButton(ContinuousScanDialog);
        Stop_pushButton->setObjectName(QStringLiteral("Stop_pushButton"));
        Stop_pushButton->setGeometry(QRect(10, 331, 141, 25));
        Save_pushButton = new QPushButton(ContinuousScanDialog);
        Save_pushButton->setObjectName(QStringLiteral("Save_pushButton"));
        Save_pushButton->setGeometry(QRect(160, 331, 201, 25));
        Continue_pushButton = new QPushButton(ContinuousScanDialog);
        Continue_pushButton->setObjectName(QStringLiteral("Continue_pushButton"));
        Continue_pushButton->setGeometry(QRect(370, 331, 141, 25));
        last_scanimage_label = new QLabel(ContinuousScanDialog);
        last_scanimage_label->setObjectName(QStringLiteral("last_scanimage_label"));
        last_scanimage_label->setGeometry(QRect(385, 6, 251, 23));
        last_scanimage_label->setAlignment(Qt::AlignCenter);
        last_scanimage_label->setWordWrap(true);
        continuous_label = new QLabel(ContinuousScanDialog);
        continuous_label->setObjectName(QStringLiteral("continuous_label"));
        continuous_label->setGeometry(QRect(50, 20, 351, 191));
        continuous_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        continuous_label->setWordWrap(true);
        Icon_toolButton = new QToolButton(ContinuousScanDialog);
        Icon_toolButton->setObjectName(QStringLiteral("Icon_toolButton"));
        Icon_toolButton->setEnabled(true);
        Icon_toolButton->setGeometry(QRect(4, 41, 51, 41));
#ifndef QT_NO_TOOLTIP
        Icon_toolButton->setToolTip(QStringLiteral(""));
#endif
        Icon_toolButton->setText(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Icon_toolButton->setIcon(icon1);
        Icon_toolButton->setIconSize(QSize(60, 60));
        Icon_toolButton->setCheckable(false);
        Icon_toolButton->setChecked(false);
        Icon_toolButton->setAutoRepeat(false);
        Icon_toolButton->setAutoExclusive(false);
        Icon_toolButton->setPopupMode(QToolButton::DelayedPopup);
        Icon_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Icon_toolButton->setAutoRaise(true);
        Icon_toolButton->setArrowType(Qt::NoArrow);
        frame = new QFrame(ContinuousScanDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(410, 30, 211, 291));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        noimage_label = new QLabel(frame);
        noimage_label->setObjectName(QStringLiteral("noimage_label"));
        noimage_label->setGeometry(QRect(10, 110, 191, 61));
        noimage_label->setAlignment(Qt::AlignCenter);
        noimage_label->setWordWrap(true);
        ADFSpecialErrorMessageForPassport_label = new QLabel(ContinuousScanDialog);
        ADFSpecialErrorMessageForPassport_label->setObjectName(QStringLiteral("ADFSpecialErrorMessageForPassport_label"));
        ADFSpecialErrorMessageForPassport_label->setGeometry(QRect(60, 240, 311, 71));
        ADFSpecialErrorMessageForPassport_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        ADFSpecialErrorMessageForPassport_label->setWordWrap(true);
        continuous_label->raise();
        Stop_pushButton->raise();
        Save_pushButton->raise();
        Continue_pushButton->raise();
        last_scanimage_label->raise();
        Icon_toolButton->raise();
        frame->raise();
        graphicsView->raise();
        ADFSpecialErrorMessageForPassport_label->raise();
        retranslateUi(ContinuousScanDialog);
        QObject::connect(Save_pushButton, SIGNAL(clicked()), ContinuousScanDialog, SLOT(onButtonPressed()));
        QObject::connect(Continue_pushButton, SIGNAL(clicked()), ContinuousScanDialog, SLOT(onButtonPressed()));
        QObject::connect(Stop_pushButton, SIGNAL(clicked()), ContinuousScanDialog, SLOT(onButtonPressed()));
        QMetaObject::connectSlotsByName(ContinuousScanDialog);
    }
    void retranslateUi(QDialog *ContinuousScanDialog)
    {
        ContinuousScanDialog->setWindowTitle(QApplication::translate("ContinuousScanDialog", "COMMON_001", 0));
        Stop_pushButton->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_005", 0));
        Save_pushButton->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_004", 0));
        Continue_pushButton->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_003", 0));
        last_scanimage_label->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_006", 0));
        continuous_label->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_008", 0));
        noimage_label->setText(QApplication::translate("ContinuousScanDialog", "CONFIRMCONTINUE_007", 0));
        ADFSpecialErrorMessageForPassport_label->setText(QString());
    }
};
namespace Ui {
    class ContinuousScanDialog: public Ui_ContinuousScanDialog {};
}
QT_END_NAMESPACE
#endif
