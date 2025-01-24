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
//  ui_aboutepsonscan2dialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_ABOUTEPSONSCAN2DIALOG_H
#define UI_ABOUTEPSONSCAN2DIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
QT_BEGIN_NAMESPACE
class Ui_AboutEpsonScan2Dialog
{
public:
    QTableWidget *Model_List_tableWidget;
    QPushButton *Close_pushButton;
    QLabel *Copyright_label;
    QLabel *Locale_label;
    QToolButton *Help_toolButton;
    void setupUi(QDialog *AboutEpsonScan2Dialog)
    {
        if (AboutEpsonScan2Dialog->objectName().isEmpty())
            AboutEpsonScan2Dialog->setObjectName(QStringLiteral("AboutEpsonScan2Dialog"));
        AboutEpsonScan2Dialog->resize(364, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AboutEpsonScan2Dialog->setWindowIcon(icon);
        Model_List_tableWidget = new QTableWidget(AboutEpsonScan2Dialog);
        if (Model_List_tableWidget->columnCount() < 2)
            Model_List_tableWidget->setColumnCount(2);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        Model_List_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        Model_List_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        Model_List_tableWidget->setObjectName(QStringLiteral("Model_List_tableWidget"));
        Model_List_tableWidget->setGeometry(QRect(10, 90, 341, 121));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Model_List_tableWidget->sizePolicy().hasHeightForWidth());
        Model_List_tableWidget->setSizePolicy(sizePolicy);
        Model_List_tableWidget->setLayoutDirection(Qt::LeftToRight);
        Model_List_tableWidget->setAutoFillBackground(false);
        Model_List_tableWidget->setFrameShape(QFrame::WinPanel);
        Model_List_tableWidget->setFrameShadow(QFrame::Raised);
        Model_List_tableWidget->setLineWidth(1);
        Model_List_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Model_List_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Model_List_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Model_List_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        Model_List_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        Model_List_tableWidget->setShowGrid(false);
        Model_List_tableWidget->setGridStyle(Qt::SolidLine);
        Model_List_tableWidget->setSortingEnabled(false);
        Model_List_tableWidget->setRowCount(0);
        Model_List_tableWidget->setColumnCount(2);
        Model_List_tableWidget->verticalHeader()->setVisible(false);
        Model_List_tableWidget->verticalHeader()->setDefaultSectionSize(16);
        Model_List_tableWidget->verticalHeader()->setHighlightSections(true);
        Close_pushButton = new QPushButton(AboutEpsonScan2Dialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(270, 260, 80, 25));
        Copyright_label = new QLabel(AboutEpsonScan2Dialog);
        Copyright_label->setObjectName(QStringLiteral("Copyright_label"));
        Copyright_label->setGeometry(QRect(10, 210, 351, 51));
        QFont font1;
        font1.setPointSize(8);
        Copyright_label->setFont(font1);
        Copyright_label->setText(QLatin1String("Copyright (C) Seiko Epson Corporation 2018. \n"
"All rights reserved."));
        Locale_label = new QLabel(AboutEpsonScan2Dialog);
        Locale_label->setObjectName(QStringLiteral("Locale_label"));
        Locale_label->setGeometry(QRect(160, 60, 55, 23));
        Locale_label->setText(QStringLiteral("EN-US"));
        Help_toolButton = new QToolButton(AboutEpsonScan2Dialog);
        Help_toolButton->setObjectName(QStringLiteral("Help_toolButton"));
        Help_toolButton->setEnabled(true);
        Help_toolButton->setGeometry(QRect(150, 16, 51, 41));
#ifndef QT_NO_TOOLTIP
        Help_toolButton->setToolTip(QStringLiteral(""));
#endif
        Help_toolButton->setText(QStringLiteral(""));
        Help_toolButton->setIcon(icon);
        Help_toolButton->setIconSize(QSize(60, 60));
        Help_toolButton->setCheckable(false);
        Help_toolButton->setChecked(false);
        Help_toolButton->setAutoRepeat(false);
        Help_toolButton->setAutoExclusive(false);
        Help_toolButton->setPopupMode(QToolButton::DelayedPopup);
        Help_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Help_toolButton->setAutoRaise(true);
        Help_toolButton->setArrowType(Qt::NoArrow);
        retranslateUi(AboutEpsonScan2Dialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), AboutEpsonScan2Dialog, SLOT(reject()));
        QMetaObject::connectSlotsByName(AboutEpsonScan2Dialog);
    }
    void retranslateUi(QDialog *AboutEpsonScan2Dialog)
    {
        AboutEpsonScan2Dialog->setWindowTitle(QApplication::translate("AboutEpsonScan2Dialog", "VERSION_001", 0));
        QTableWidgetItem *___qtablewidgetitem = Model_List_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("AboutEpsonScan2Dialog", "LINUX_VERSION_001", 0));
        QTableWidgetItem *___qtablewidgetitem1 = Model_List_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("AboutEpsonScan2Dialog", "VERSION_002", 0));
        Close_pushButton->setText(QApplication::translate("AboutEpsonScan2Dialog", "TC_PREVIEW_001", 0));
    }
};
namespace Ui {
    class AboutEpsonScan2Dialog: public Ui_AboutEpsonScan2Dialog {};
}
QT_END_NAMESPACE
#endif
