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
//  ui_selectabledetectdoublefeedsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_SELECTABLEDETECTDOUBLEFEEDSETTINGSDIALOG_H
#define UI_SELECTABLEDETECTDOUBLEFEEDSETTINGSDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "detectionareamaxdoublespinbox.h"
#include "detectionareamindoublespinbox.h"
#include "paperthicknesscombobox.h"
QT_BEGIN_NAMESPACE
class Ui_SelectableDetectDoubleFeedSettingsDialog
{
public:
    DetectionAreaMaxDoubleSpinBox *Max_doubleSpinBox;
    QPushButton *Close_pushButton;
    DetectionAreaMinDoubleSpinBox *Min_doubleSpinBox;
    QStackedWidget *Det_Area_stackedWidget;
    QWidget *mm_page;
    QLabel *mm_label1;
    QLabel *label;
    QLabel *mm_label2;
    QWidget *inchi_page;
    QLabel *inchi_label2;
    QLabel *inchi_label1;
    QLabel *label_2;
    PaperThicknessComboBox *Paper_Thickness_comboBox;
    QLabel *Detection_Area_label;
    QLabel *Paper_Thickness_label;
    QCheckBox *Ultrasonic_sensor_checkBox;
    QCheckBox *Scanned_image_checkBox;
    QCheckBox *Paper_Protection_checkBox;
    QFrame *line;
    QTextBrowser *Description_textBrowser;
    QLabel *Paper_Thickness_colon_label;
    QLabel *Detection_Area_colon_label;
    void setupUi(QDialog *SelectableDetectDoubleFeedSettingsDialog)
    {
        if (SelectableDetectDoubleFeedSettingsDialog->objectName().isEmpty())
            SelectableDetectDoubleFeedSettingsDialog->setObjectName(QStringLiteral("SelectableDetectDoubleFeedSettingsDialog"));
        SelectableDetectDoubleFeedSettingsDialog->resize(461, 339);
        SelectableDetectDoubleFeedSettingsDialog->setWindowTitle(QStringLiteral("Dialog"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SelectableDetectDoubleFeedSettingsDialog->setWindowIcon(icon);
        Max_doubleSpinBox = new DetectionAreaMaxDoubleSpinBox(SelectableDetectDoubleFeedSettingsDialog);
        Max_doubleSpinBox->setObjectName(QStringLiteral("Max_doubleSpinBox"));
        Max_doubleSpinBox->setEnabled(false);
        Max_doubleSpinBox->setGeometry(QRect(260, 77, 61, 23));
        QFont font;
        font.setKerning(true);
        Max_doubleSpinBox->setFont(font);
        Max_doubleSpinBox->setMouseTracking(false);
        Max_doubleSpinBox->setAutoFillBackground(false);
        Max_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        Close_pushButton = new QPushButton(SelectableDetectDoubleFeedSettingsDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(370, 297, 80, 25));
#ifndef QT_NO_TOOLTIP
        Close_pushButton->setToolTip(QStringLiteral(""));
#endif
        Close_pushButton->setText(QStringLiteral("Close"));
        Min_doubleSpinBox = new DetectionAreaMinDoubleSpinBox(SelectableDetectDoubleFeedSettingsDialog);
        Min_doubleSpinBox->setObjectName(QStringLiteral("Min_doubleSpinBox"));
        Min_doubleSpinBox->setEnabled(false);
        Min_doubleSpinBox->setGeometry(QRect(147, 77, 61, 23));
        Min_doubleSpinBox->setFont(font);
        Min_doubleSpinBox->setMouseTracking(false);
        Min_doubleSpinBox->setAutoFillBackground(false);
        Min_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        Min_doubleSpinBox->setDecimals(2);
        Det_Area_stackedWidget = new QStackedWidget(SelectableDetectDoubleFeedSettingsDialog);
        Det_Area_stackedWidget->setObjectName(QStringLiteral("Det_Area_stackedWidget"));
        Det_Area_stackedWidget->setEnabled(false);
        Det_Area_stackedWidget->setGeometry(QRect(144, 77, 221, 31));
        mm_page = new QWidget();
        mm_page->setObjectName(QStringLiteral("mm_page"));
        mm_label1 = new QLabel(mm_page);
        mm_label1->setObjectName(QStringLiteral("mm_label1"));
        mm_label1->setGeometry(QRect(67, 6, 21, 16));
#ifndef QT_NO_TOOLTIP
        mm_label1->setToolTip(QStringLiteral(""));
#endif
        mm_label1->setText(QStringLiteral("mm"));
        label = new QLabel(mm_page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(102, 5, 21, 16));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QStringLiteral(""));
#endif
        label->setText(QStringLiteral("-"));
        mm_label2 = new QLabel(mm_page);
        mm_label2->setObjectName(QStringLiteral("mm_label2"));
        mm_label2->setGeometry(QRect(180, 6, 21, 16));
#ifndef QT_NO_TOOLTIP
        mm_label2->setToolTip(QStringLiteral(""));
#endif
        mm_label2->setText(QStringLiteral("mm"));
        Det_Area_stackedWidget->addWidget(mm_page);
        inchi_page = new QWidget();
        inchi_page->setObjectName(QStringLiteral("inchi_page"));
#ifndef QT_NO_TOOLTIP
        inchi_page->setToolTip(QStringLiteral(""));
#endif
        inchi_label2 = new QLabel(inchi_page);
        inchi_label2->setObjectName(QStringLiteral("inchi_label2"));
        inchi_label2->setGeometry(QRect(180, 6, 21, 23));
#ifndef QT_NO_TOOLTIP
        inchi_label2->setToolTip(QStringLiteral(""));
#endif
        inchi_label2->setText(QStringLiteral("in."));
        inchi_label1 = new QLabel(inchi_page);
        inchi_label1->setObjectName(QStringLiteral("inchi_label1"));
        inchi_label1->setGeometry(QRect(67, 6, 21, 23));
#ifndef QT_NO_TOOLTIP
        inchi_label1->setToolTip(QStringLiteral(""));
#endif
        inchi_label1->setText(QStringLiteral("in."));
        label_2 = new QLabel(inchi_page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(102, 5, 21, 16));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QStringLiteral(""));
#endif
        label_2->setText(QStringLiteral("-"));
        Det_Area_stackedWidget->addWidget(inchi_page);
        Paper_Thickness_comboBox = new PaperThicknessComboBox(SelectableDetectDoubleFeedSettingsDialog);
        Paper_Thickness_comboBox->setObjectName(QStringLiteral("Paper_Thickness_comboBox"));
        Paper_Thickness_comboBox->setEnabled(false);
        Paper_Thickness_comboBox->setGeometry(QRect(147, 46, 191, 23));
#ifndef QT_NO_TOOLTIP
        Paper_Thickness_comboBox->setToolTip(QStringLiteral(""));
#endif
        Detection_Area_label = new QLabel(SelectableDetectDoubleFeedSettingsDialog);
        Detection_Area_label->setObjectName(QStringLiteral("Detection_Area_label"));
        Detection_Area_label->setEnabled(false);
        Detection_Area_label->setGeometry(QRect(40, 80, 111, 23));
#ifndef QT_NO_TOOLTIP
        Detection_Area_label->setToolTip(QStringLiteral(""));
#endif
        Detection_Area_label->setText(QStringLiteral("CONFIG_DOC_016"));
        Paper_Thickness_label = new QLabel(SelectableDetectDoubleFeedSettingsDialog);
        Paper_Thickness_label->setObjectName(QStringLiteral("Paper_Thickness_label"));
        Paper_Thickness_label->setEnabled(false);
        Paper_Thickness_label->setGeometry(QRect(40, 49, 101, 23));
#ifndef QT_NO_TOOLTIP
        Paper_Thickness_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Thickness_label->setText(QStringLiteral("CONFIG_DOC_012"));
        Ultrasonic_sensor_checkBox = new QCheckBox(SelectableDetectDoubleFeedSettingsDialog);
        Ultrasonic_sensor_checkBox->setObjectName(QStringLiteral("Ultrasonic_sensor_checkBox"));
        Ultrasonic_sensor_checkBox->setGeometry(QRect(20, 17, 131, 23));
#ifndef QT_NO_TOOLTIP
        Ultrasonic_sensor_checkBox->setToolTip(QStringLiteral(""));
#endif
        Ultrasonic_sensor_checkBox->setText(QStringLiteral("CONFIG_DOC_007"));
        Scanned_image_checkBox = new QCheckBox(SelectableDetectDoubleFeedSettingsDialog);
        Scanned_image_checkBox->setObjectName(QStringLiteral("Scanned_image_checkBox"));
        Scanned_image_checkBox->setGeometry(QRect(20, 107, 121, 23));
#ifndef QT_NO_TOOLTIP
        Scanned_image_checkBox->setToolTip(QStringLiteral(""));
#endif
        Scanned_image_checkBox->setText(QStringLiteral("Scanned image"));
        Paper_Protection_checkBox = new QCheckBox(SelectableDetectDoubleFeedSettingsDialog);
        Paper_Protection_checkBox->setObjectName(QStringLiteral("Paper_Protection_checkBox"));
        Paper_Protection_checkBox->setGeometry(QRect(20, 164, 131, 23));
#ifndef QT_NO_TOOLTIP
        Paper_Protection_checkBox->setToolTip(QStringLiteral(""));
#endif
        Paper_Protection_checkBox->setText(QStringLiteral("Paper Protection"));
        line = new QFrame(SelectableDetectDoubleFeedSettingsDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 137, 421, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        Description_textBrowser = new QTextBrowser(SelectableDetectDoubleFeedSettingsDialog);
        Description_textBrowser->setObjectName(QStringLiteral("Description_textBrowser"));
        Description_textBrowser->setGeometry(QRect(20, 197, 411, 81));
#ifndef QT_NO_TOOLTIP
        Description_textBrowser->setToolTip(QStringLiteral(""));
#endif
        Description_textBrowser->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        Description_textBrowser->setPlaceholderText(QStringLiteral(""));
        Paper_Thickness_colon_label = new QLabel(SelectableDetectDoubleFeedSettingsDialog);
        Paper_Thickness_colon_label->setObjectName(QStringLiteral("Paper_Thickness_colon_label"));
        Paper_Thickness_colon_label->setEnabled(false);
        Paper_Thickness_colon_label->setGeometry(QRect(131, 49, 16, 16));
#ifndef QT_NO_TOOLTIP
        Paper_Thickness_colon_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Thickness_colon_label->setText(QStringLiteral(":"));
        Detection_Area_colon_label = new QLabel(SelectableDetectDoubleFeedSettingsDialog);
        Detection_Area_colon_label->setObjectName(QStringLiteral("Detection_Area_colon_label"));
        Detection_Area_colon_label->setEnabled(false);
        Detection_Area_colon_label->setGeometry(QRect(131, 80, 16, 16));
#ifndef QT_NO_TOOLTIP
        Detection_Area_colon_label->setToolTip(QStringLiteral(""));
#endif
        Detection_Area_colon_label->setText(QStringLiteral(":"));
        Close_pushButton->raise();
        Det_Area_stackedWidget->raise();
        Paper_Thickness_comboBox->raise();
        Detection_Area_label->raise();
        Paper_Thickness_label->raise();
        Ultrasonic_sensor_checkBox->raise();
        Scanned_image_checkBox->raise();
        Paper_Protection_checkBox->raise();
        line->raise();
        Description_textBrowser->raise();
        Min_doubleSpinBox->raise();
        Max_doubleSpinBox->raise();
        Paper_Thickness_colon_label->raise();
        Detection_Area_colon_label->raise();
        retranslateUi(SelectableDetectDoubleFeedSettingsDialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), SelectableDetectDoubleFeedSettingsDialog, SLOT(reject()));
        QObject::connect(Max_doubleSpinBox, SIGNAL(valueChanged(double)), Min_doubleSpinBox, SLOT(setMaxValue(double)));
        QObject::connect(Min_doubleSpinBox, SIGNAL(valueChanged(double)), Max_doubleSpinBox, SLOT(setMinValue(double)));
        QObject::connect(Paper_Thickness_comboBox, SIGNAL(activated(int)), SelectableDetectDoubleFeedSettingsDialog, SLOT(onValueChanged(int)));
        QObject::connect(Ultrasonic_sensor_checkBox, SIGNAL(toggled(bool)), SelectableDetectDoubleFeedSettingsDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Scanned_image_checkBox, SIGNAL(toggled(bool)), SelectableDetectDoubleFeedSettingsDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Paper_Protection_checkBox, SIGNAL(toggled(bool)), SelectableDetectDoubleFeedSettingsDialog, SLOT(onValueChangedBool(bool)));
        Det_Area_stackedWidget->setCurrentIndex(1);
        QMetaObject::connectSlotsByName(SelectableDetectDoubleFeedSettingsDialog);
    }
    void retranslateUi(QDialog *SelectableDetectDoubleFeedSettingsDialog)
    {
        Q_UNUSED(SelectableDetectDoubleFeedSettingsDialog);
    }
};
namespace Ui {
    class SelectableDetectDoubleFeedSettingsDialog: public Ui_SelectableDetectDoubleFeedSettingsDialog {};
}
QT_END_NAMESPACE
#endif
