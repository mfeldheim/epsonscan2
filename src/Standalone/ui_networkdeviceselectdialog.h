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
//  ui_networkdeviceselectdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_NETWORKDEVICESELECTDIALOG_H
#define UI_NETWORKDEVICESELECTDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
QT_BEGIN_NAMESPACE
class Ui_NetworkDeviceSelectDialog
{
public:
    QPushButton *Connect_pushButton;
    QPushButton *Add_pushButton;
    QPushButton *Delete_pushButton;
    QLineEdit *Address_lineEdit;
    QLabel *Address_label;
    QTableWidget *IP_List_tableWidget;
    QPushButton *Cancel_pushButton;
    QLabel *Address_colon_label;
    void setupUi(QDialog *NetworkDeviceSelectDialog)
    {
        if (NetworkDeviceSelectDialog->objectName().isEmpty())
            NetworkDeviceSelectDialog->setObjectName(QStringLiteral("NetworkDeviceSelectDialog"));
        NetworkDeviceSelectDialog->resize(400, 231);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        NetworkDeviceSelectDialog->setWindowIcon(icon);
        Connect_pushButton = new QPushButton(NetworkDeviceSelectDialog);
        Connect_pushButton->setObjectName(QStringLiteral("Connect_pushButton"));
        Connect_pushButton->setEnabled(false);
        Connect_pushButton->setGeometry(QRect(197, 194, 80, 25));
        Add_pushButton = new QPushButton(NetworkDeviceSelectDialog);
        Add_pushButton->setObjectName(QStringLiteral("Add_pushButton"));
        Add_pushButton->setEnabled(false);
        Add_pushButton->setGeometry(QRect(20, 194, 80, 25));
        Delete_pushButton = new QPushButton(NetworkDeviceSelectDialog);
        Delete_pushButton->setObjectName(QStringLiteral("Delete_pushButton"));
        Delete_pushButton->setEnabled(false);
        Delete_pushButton->setGeometry(QRect(108, 194, 80, 25));
        Address_lineEdit = new QLineEdit(NetworkDeviceSelectDialog);
        Address_lineEdit->setObjectName(QStringLiteral("Address_lineEdit"));
        Address_lineEdit->setGeometry(QRect(150, 156, 221, 23));
        Address_lineEdit->setMaxLength(64);
        Address_lineEdit->setClearButtonEnabled(false);
        Address_label = new QLabel(NetworkDeviceSelectDialog);
        Address_label->setObjectName(QStringLiteral("Address_label"));
        Address_label->setGeometry(QRect(30, 156, 111, 23));
        IP_List_tableWidget = new QTableWidget(NetworkDeviceSelectDialog);
        if (IP_List_tableWidget->columnCount() < 1)
            IP_List_tableWidget->setColumnCount(1);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem->setFont(font);
        IP_List_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        IP_List_tableWidget->setObjectName(QStringLiteral("IP_List_tableWidget"));
        IP_List_tableWidget->setGeometry(QRect(32, 21, 341, 121));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(IP_List_tableWidget->sizePolicy().hasHeightForWidth());
        IP_List_tableWidget->setSizePolicy(sizePolicy);
        IP_List_tableWidget->setLayoutDirection(Qt::LeftToRight);
        IP_List_tableWidget->setAutoFillBackground(false);
        IP_List_tableWidget->setFrameShape(QFrame::WinPanel);
        IP_List_tableWidget->setFrameShadow(QFrame::Raised);
        IP_List_tableWidget->setLineWidth(1);
        IP_List_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        IP_List_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        IP_List_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        IP_List_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        IP_List_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        IP_List_tableWidget->setShowGrid(false);
        IP_List_tableWidget->setGridStyle(Qt::SolidLine);
        IP_List_tableWidget->setSortingEnabled(false);
        IP_List_tableWidget->setRowCount(0);
        IP_List_tableWidget->setColumnCount(1);
        IP_List_tableWidget->verticalHeader()->setVisible(false);
        IP_List_tableWidget->verticalHeader()->setDefaultSectionSize(16);
        IP_List_tableWidget->verticalHeader()->setHighlightSections(true);
        Cancel_pushButton = new QPushButton(NetworkDeviceSelectDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(286, 194, 98, 25));
        Address_colon_label = new QLabel(NetworkDeviceSelectDialog);
        Address_colon_label->setObjectName(QStringLiteral("Address_colon_label"));
        Address_colon_label->setEnabled(true);
        Address_colon_label->setGeometry(QRect(144, 158, 16, 20));
#ifndef QT_NO_TOOLTIP
        Address_colon_label->setToolTip(QStringLiteral(""));
#endif
        Address_colon_label->setText(QStringLiteral(":"));
        retranslateUi(NetworkDeviceSelectDialog);
        QObject::connect(Connect_pushButton, SIGNAL(clicked()), NetworkDeviceSelectDialog, SLOT(reject()));
        QObject::connect(Address_lineEdit, SIGNAL(textEdited(QString)), NetworkDeviceSelectDialog, SLOT(LineEditFinished()));
        QObject::connect(Add_pushButton, SIGNAL(pressed()), NetworkDeviceSelectDialog, SLOT(PushButtonAction()));
        QObject::connect(Delete_pushButton, SIGNAL(pressed()), NetworkDeviceSelectDialog, SLOT(PushButtonAction()));
        QObject::connect(IP_List_tableWidget, SIGNAL(itemSelectionChanged()), NetworkDeviceSelectDialog, SLOT(AvailableDeleteButton()));
        QObject::connect(Connect_pushButton, SIGNAL(clicked()), NetworkDeviceSelectDialog, SLOT(PushButtonAction()));
        QObject::connect(Cancel_pushButton, SIGNAL(clicked()), NetworkDeviceSelectDialog, SLOT(PushButtonAction()));
        QObject::connect(Cancel_pushButton, SIGNAL(clicked()), NetworkDeviceSelectDialog, SLOT(reject()));
        QMetaObject::connectSlotsByName(NetworkDeviceSelectDialog);
    }
    void retranslateUi(QDialog *NetworkDeviceSelectDialog)
    {
        NetworkDeviceSelectDialog->setWindowTitle(QApplication::translate("NetworkDeviceSelectDialog", "ADDNETSCANNER_001", 0));
        Connect_pushButton->setText(QApplication::translate("NetworkDeviceSelectDialog", "SCANNERSETTING_010", 0));
        Add_pushButton->setText(QApplication::translate("NetworkDeviceSelectDialog", "ADDNETSCANNER_013", 0));
        Delete_pushButton->setText(QApplication::translate("NetworkDeviceSelectDialog", "DELETESETTING_002", 0));
        Address_label->setText(QApplication::translate("NetworkDeviceSelectDialog", "ADDNETSCANNER_012", 0));
        QTableWidgetItem *___qtablewidgetitem = IP_List_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("NetworkDeviceSelectDialog", "ADDNETSCANNER_009", 0));
        Cancel_pushButton->setText(QApplication::translate("NetworkDeviceSelectDialog", "ADDNETSCANNER_014", 0));
    }
};
namespace Ui {
    class NetworkDeviceSelectDialog: public Ui_NetworkDeviceSelectDialog {};
}
QT_END_NAMESPACE
#endif
