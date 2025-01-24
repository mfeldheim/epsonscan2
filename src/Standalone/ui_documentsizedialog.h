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
//  ui_documentsizedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DOCUMENTSIZEDIALOG_H
#define UI_DOCUMENTSIZEDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "detectpapercheckbox.h"
#include "lengthdoublespinbox.h"
#include "widthdoublespinbox.h"
QT_BEGIN_NAMESPACE
class Ui_DocumentSizeDialog
{
public:
    QLabel *Width_label;
    QLabel *Length_label;
    DetectPaperCheckBox *Det_Paper_checkBox;
    QPushButton *Close_pushButton;
    QStackedWidget *units_stackedWidget;
    QWidget *page_7;
    QLabel *w_inchi_label;
    QStackedWidget *inchi_stackedWidget;
    QWidget *page_13;
    QLabel *l_inchi_label;
    QWidget *page_14;
    QWidget *page_10;
    QLabel *w_mm_label;
    QStackedWidget *mm_stackedWidget;
    QWidget *page_11;
    QLabel *l_mm_label;
    QWidget *page_12;
    WidthDoubleSpinBox *Width_doubleSpinBox;
    QStackedWidget *Length_stackedWidget;
    QWidget *page_8;
    LengthDoubleSpinBox *Length_doubleSpinBox;
    QWidget *page_9;
    QLabel *Auto_Detect_label;
    QLabel *Width_colon_label;
    QLabel *Length_colon_label;
    void setupUi(QDialog *DocumentSizeDialog)
    {
        if (DocumentSizeDialog->objectName().isEmpty())
            DocumentSizeDialog->setObjectName(QStringLiteral("DocumentSizeDialog"));
        DocumentSizeDialog->resize(401, 256);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DocumentSizeDialog->setWindowIcon(icon);
        Width_label = new QLabel(DocumentSizeDialog);
        Width_label->setObjectName(QStringLiteral("Width_label"));
        Width_label->setGeometry(QRect(10, 40, 91, 23));
        Length_label = new QLabel(DocumentSizeDialog);
        Length_label->setObjectName(QStringLiteral("Length_label"));
        Length_label->setGeometry(QRect(10, 65, 91, 23));
        Det_Paper_checkBox = new DetectPaperCheckBox(DocumentSizeDialog);
        Det_Paper_checkBox->setObjectName(QStringLiteral("Det_Paper_checkBox"));
        Det_Paper_checkBox->setGeometry(QRect(20, 110, 351, 31));
        Close_pushButton = new QPushButton(DocumentSizeDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(250, 218, 131, 25));
        units_stackedWidget = new QStackedWidget(DocumentSizeDialog);
        units_stackedWidget->setObjectName(QStringLiteral("units_stackedWidget"));
        units_stackedWidget->setGeometry(QRect(177, 39, 221, 51));
        page_7 = new QWidget();
        page_7->setObjectName(QStringLiteral("page_7"));
        w_inchi_label = new QLabel(page_7);
        w_inchi_label->setObjectName(QStringLiteral("w_inchi_label"));
        w_inchi_label->setGeometry(QRect(12, 0, 171, 21));
        inchi_stackedWidget = new QStackedWidget(page_7);
        inchi_stackedWidget->setObjectName(QStringLiteral("inchi_stackedWidget"));
        inchi_stackedWidget->setGeometry(QRect(10, 20, 81, 31));
        page_13 = new QWidget();
        page_13->setObjectName(QStringLiteral("page_13"));
        l_inchi_label = new QLabel(page_13);
        l_inchi_label->setObjectName(QStringLiteral("l_inchi_label"));
        l_inchi_label->setGeometry(QRect(2, 10, 81, 16));
        inchi_stackedWidget->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QStringLiteral("page_14"));
        inchi_stackedWidget->addWidget(page_14);
        units_stackedWidget->addWidget(page_7);
        page_10 = new QWidget();
        page_10->setObjectName(QStringLiteral("page_10"));
        w_mm_label = new QLabel(page_10);
        w_mm_label->setObjectName(QStringLiteral("w_mm_label"));
        w_mm_label->setGeometry(QRect(10, 0, 171, 21));
        mm_stackedWidget = new QStackedWidget(page_10);
        mm_stackedWidget->setObjectName(QStringLiteral("mm_stackedWidget"));
        mm_stackedWidget->setGeometry(QRect(0, 20, 101, 31));
        page_11 = new QWidget();
        page_11->setObjectName(QStringLiteral("page_11"));
        l_mm_label = new QLabel(page_11);
        l_mm_label->setObjectName(QStringLiteral("l_mm_label"));
        l_mm_label->setGeometry(QRect(10, 10, 91, 16));
        mm_stackedWidget->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName(QStringLiteral("page_12"));
        mm_stackedWidget->addWidget(page_12);
        units_stackedWidget->addWidget(page_10);
        Width_doubleSpinBox = new WidthDoubleSpinBox(DocumentSizeDialog);
        Width_doubleSpinBox->setObjectName(QStringLiteral("Width_doubleSpinBox"));
        Width_doubleSpinBox->setGeometry(QRect(110, 39, 71, 22));
        QFont font;
        font.setKerning(true);
        Width_doubleSpinBox->setFont(font);
        Width_doubleSpinBox->setMouseTracking(false);
        Width_doubleSpinBox->setAutoFillBackground(false);
        Width_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Width_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Width_doubleSpinBox->setDecimals(2);
        Length_stackedWidget = new QStackedWidget(DocumentSizeDialog);
        Length_stackedWidget->setObjectName(QStringLiteral("Length_stackedWidget"));
        Length_stackedWidget->setGeometry(QRect(99, 65, 291, 21));
        page_8 = new QWidget();
        page_8->setObjectName(QStringLiteral("page_8"));
        Length_doubleSpinBox = new LengthDoubleSpinBox(page_8);
        Length_doubleSpinBox->setObjectName(QStringLiteral("Length_doubleSpinBox"));
        Length_doubleSpinBox->setGeometry(QRect(10, 0, 71, 22));
        Length_doubleSpinBox->setFont(font);
        Length_doubleSpinBox->setMouseTracking(false);
        Length_doubleSpinBox->setAutoFillBackground(false);
        Length_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Length_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Length_stackedWidget->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QStringLiteral("page_9"));
        Auto_Detect_label = new QLabel(page_9);
        Auto_Detect_label->setObjectName(QStringLiteral("Auto_Detect_label"));
        Auto_Detect_label->setGeometry(QRect(10, 1, 251, 21));
        Length_stackedWidget->addWidget(page_9);
        Width_colon_label = new QLabel(DocumentSizeDialog);
        Width_colon_label->setObjectName(QStringLiteral("Width_colon_label"));
        Width_colon_label->setEnabled(true);
        Width_colon_label->setGeometry(QRect(100, 42, 16, 16));
#ifndef QT_NO_TOOLTIP
        Width_colon_label->setToolTip(QStringLiteral(""));
#endif
        Width_colon_label->setText(QStringLiteral(":"));
        Length_colon_label = new QLabel(DocumentSizeDialog);
        Length_colon_label->setObjectName(QStringLiteral("Length_colon_label"));
        Length_colon_label->setEnabled(true);
        Length_colon_label->setGeometry(QRect(100, 68, 16, 16));
#ifndef QT_NO_TOOLTIP
        Length_colon_label->setToolTip(QStringLiteral(""));
#endif
        Length_colon_label->setText(QStringLiteral(":"));
        retranslateUi(DocumentSizeDialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), DocumentSizeDialog, SLOT(reject()));
        QObject::connect(Det_Paper_checkBox, SIGNAL(toggled(bool)), DocumentSizeDialog, SLOT(onValueChangedBool(bool)));
        units_stackedWidget->setCurrentIndex(1);
        inchi_stackedWidget->setCurrentIndex(1);
        mm_stackedWidget->setCurrentIndex(0);
        Length_stackedWidget->setCurrentIndex(0);
        QMetaObject::connectSlotsByName(DocumentSizeDialog);
    }
    void retranslateUi(QDialog *DocumentSizeDialog)
    {
        DocumentSizeDialog->setWindowTitle(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_001", 0));
        Width_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_006", 0));
        Length_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_007", 0));
        Det_Paper_checkBox->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_013", 0));
        Close_pushButton->setText(QApplication::translate("DocumentSizeDialog", "TC_PREVIEW_001", 0));
        w_inchi_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_009", 0));
        l_inchi_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_009", 0));
        w_mm_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_008", 0));
        l_mm_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_008", 0));
        Auto_Detect_label->setText(QApplication::translate("DocumentSizeDialog", "CUSTOMSIZE_010", 0));
    }
};
namespace Ui {
    class DocumentSizeDialog: public Ui_DocumentSizeDialog {};
}
QT_END_NAMESPACE
#endif
