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
//  ui_detectdoublefeedsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_DETECTDOUBLEFEEDSETTINGSDIALOG_H
#define UI_DETECTDOUBLEFEEDSETTINGSDIALOG_H 
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
#include "detectionareamaxdoublespinbox.h"
#include "detectionareamindoublespinbox.h"
#include "paperthicknesscombobox.h"
QT_BEGIN_NAMESPACE
class Ui_DetectDoubleFeedSettingsDialog
{
public:
    QPushButton *Close_pushButton;
    QLabel *Paper_Thickness_label;
    PaperThicknessComboBox *Paper_Thickness_comboBox;
    QLabel *Detection_Area_label;
    QStackedWidget *Det_Area_stackedWidget;
    QWidget *mm_page;
    QLabel *mm_label1;
    QLabel *label;
    QLabel *mm_label2;
    QWidget *inchi_page;
    QLabel *inchi_label2;
    QLabel *inchi_label1;
    QLabel *label_2;
    DetectionAreaMinDoubleSpinBox *Min_doubleSpinBox;
    DetectionAreaMaxDoubleSpinBox *Max_doubleSpinBox;
    QLabel *Paper_Thickness_colon_label;
    QLabel *Detection_Area_colon_label;
    void setupUi(QDialog *DetectDoubleFeedSettingsDialog)
    {
        if (DetectDoubleFeedSettingsDialog->objectName().isEmpty())
            DetectDoubleFeedSettingsDialog->setObjectName(QStringLiteral("DetectDoubleFeedSettingsDialog"));
        DetectDoubleFeedSettingsDialog->resize(610, 129);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DetectDoubleFeedSettingsDialog->setWindowIcon(icon);
        Close_pushButton = new QPushButton(DetectDoubleFeedSettingsDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(500, 90, 80, 25));
        Paper_Thickness_label = new QLabel(DetectDoubleFeedSettingsDialog);
        Paper_Thickness_label->setObjectName(QStringLiteral("Paper_Thickness_label"));
        Paper_Thickness_label->setGeometry(QRect(10, 20, 161, 23));
        Paper_Thickness_comboBox = new PaperThicknessComboBox(DetectDoubleFeedSettingsDialog);
        Paper_Thickness_comboBox->setObjectName(QStringLiteral("Paper_Thickness_comboBox"));
        Paper_Thickness_comboBox->setGeometry(QRect(197, 19, 191, 23));
        Detection_Area_label = new QLabel(DetectDoubleFeedSettingsDialog);
        Detection_Area_label->setObjectName(QStringLiteral("Detection_Area_label"));
        Detection_Area_label->setGeometry(QRect(10, 51, 161, 23));
        Det_Area_stackedWidget = new QStackedWidget(DetectDoubleFeedSettingsDialog);
        Det_Area_stackedWidget->setObjectName(QStringLiteral("Det_Area_stackedWidget"));
        Det_Area_stackedWidget->setGeometry(QRect(194, 48, 401, 31));
        mm_page = new QWidget();
        mm_page->setObjectName(QStringLiteral("mm_page"));
        mm_label1 = new QLabel(mm_page);
        mm_label1->setObjectName(QStringLiteral("mm_label1"));
        mm_label1->setGeometry(QRect(110, 6, 61, 23));
        label = new QLabel(mm_page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 5, 21, 23));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QStringLiteral(""));
#endif
        label->setText(QStringLiteral("-"));
        mm_label2 = new QLabel(mm_page);
        mm_label2->setObjectName(QStringLiteral("mm_label2"));
        mm_label2->setGeometry(QRect(300, 6, 71, 23));
        Det_Area_stackedWidget->addWidget(mm_page);
        inchi_page = new QWidget();
        inchi_page->setObjectName(QStringLiteral("inchi_page"));
        inchi_label2 = new QLabel(inchi_page);
        inchi_label2->setObjectName(QStringLiteral("inchi_label2"));
        inchi_label2->setGeometry(QRect(300, 6, 71, 23));
        inchi_label1 = new QLabel(inchi_page);
        inchi_label1->setObjectName(QStringLiteral("inchi_label1"));
        inchi_label1->setGeometry(QRect(110, 6, 61, 23));
        label_2 = new QLabel(inchi_page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 5, 21, 23));
        label_2->setText(QStringLiteral("-"));
        Det_Area_stackedWidget->addWidget(inchi_page);
        Min_doubleSpinBox = new DetectionAreaMinDoubleSpinBox(DetectDoubleFeedSettingsDialog);
        Min_doubleSpinBox->setObjectName(QStringLiteral("Min_doubleSpinBox"));
        Min_doubleSpinBox->setGeometry(QRect(197, 50, 101, 23));
        QFont font;
        font.setKerning(true);
        Min_doubleSpinBox->setFont(font);
        Min_doubleSpinBox->setMouseTracking(false);
        Min_doubleSpinBox->setAutoFillBackground(false);
        Min_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        Min_doubleSpinBox->setDecimals(2);
        Max_doubleSpinBox = new DetectionAreaMaxDoubleSpinBox(DetectDoubleFeedSettingsDialog);
        Max_doubleSpinBox->setObjectName(QStringLiteral("Max_doubleSpinBox"));
        Max_doubleSpinBox->setGeometry(QRect(386, 50, 101, 23));
        Max_doubleSpinBox->setFont(font);
        Max_doubleSpinBox->setMouseTracking(false);
        Max_doubleSpinBox->setAutoFillBackground(false);
        Max_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        Paper_Thickness_colon_label = new QLabel(DetectDoubleFeedSettingsDialog);
        Paper_Thickness_colon_label->setObjectName(QStringLiteral("Paper_Thickness_colon_label"));
        Paper_Thickness_colon_label->setEnabled(true);
        Paper_Thickness_colon_label->setGeometry(QRect(180, 22, 16, 20));
#ifndef QT_NO_TOOLTIP
        Paper_Thickness_colon_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Thickness_colon_label->setText(QStringLiteral(":"));
        Detection_Area_colon_label = new QLabel(DetectDoubleFeedSettingsDialog);
        Detection_Area_colon_label->setObjectName(QStringLiteral("Detection_Area_colon_label"));
        Detection_Area_colon_label->setEnabled(true);
        Detection_Area_colon_label->setGeometry(QRect(180, 53, 16, 20));
#ifndef QT_NO_TOOLTIP
        Detection_Area_colon_label->setToolTip(QStringLiteral(""));
#endif
        Detection_Area_colon_label->setText(QStringLiteral(":"));
        retranslateUi(DetectDoubleFeedSettingsDialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), DetectDoubleFeedSettingsDialog, SLOT(reject()));
        QObject::connect(Paper_Thickness_comboBox, SIGNAL(activated(int)), DetectDoubleFeedSettingsDialog, SLOT(onValueChanged(int)));
        QObject::connect(Max_doubleSpinBox, SIGNAL(valueChanged(double)), Min_doubleSpinBox, SLOT(setMaxValue(double)));
        QObject::connect(Min_doubleSpinBox, SIGNAL(valueChanged(double)), Max_doubleSpinBox, SLOT(setMinValue(double)));
        Det_Area_stackedWidget->setCurrentIndex(1);
        QMetaObject::connectSlotsByName(DetectDoubleFeedSettingsDialog);
    }
    void retranslateUi(QDialog *DetectDoubleFeedSettingsDialog)
    {
        DetectDoubleFeedSettingsDialog->setWindowTitle(QApplication::translate("DetectDoubleFeedSettingsDialog", "MAINSETTING_044", 0));
        Close_pushButton->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "TC_PREVIEW_001", 0));
        Paper_Thickness_label->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "CONFIG_DOC_012", 0));
        Detection_Area_label->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "CONFIG_DOC_016", 0));
        mm_label1->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "EDGEFILLLEVEL_007", 0));
        mm_label2->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "EDGEFILLLEVEL_007", 0));
        inchi_label2->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "EDGEFILLLEVEL_008", 0));
        inchi_label1->setText(QApplication::translate("DetectDoubleFeedSettingsDialog", "EDGEFILLLEVEL_008", 0));
    }
};
namespace Ui {
    class DetectDoubleFeedSettingsDialog: public Ui_DetectDoubleFeedSettingsDialog {};
}
QT_END_NAMESPACE
#endif
