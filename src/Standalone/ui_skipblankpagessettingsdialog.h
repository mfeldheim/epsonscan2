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
//  ui_skipblankpagessettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_SKIPBLANKPAGESSETTINGSDIALOG_H
#define UI_SKIPBLANKPAGESSETTINGSDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "skipblankpagesdetlvslider.h"
QT_BEGIN_NAMESPACE
class Ui_SkipBlankPagesSettingsDialog
{
public:
    QPushButton *CLose_pushButton;
    QTextBrowser *Description_textBrowser;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *Det_Lv_label;
    QLabel *Det_Lv_colon_label;
    SkipBlankPagesDetLvSlider *Det_Lv_horizontalSlider;
    QSpinBox *Det_Lv_spinBox;
    void setupUi(QDialog *SkipBlankPagesSettingsDialog)
    {
        if (SkipBlankPagesSettingsDialog->objectName().isEmpty())
            SkipBlankPagesSettingsDialog->setObjectName(QStringLiteral("SkipBlankPagesSettingsDialog"));
        SkipBlankPagesSettingsDialog->resize(452, 180);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SkipBlankPagesSettingsDialog->setWindowIcon(icon);
        CLose_pushButton = new QPushButton(SkipBlankPagesSettingsDialog);
        CLose_pushButton->setObjectName(QStringLiteral("CLose_pushButton"));
        CLose_pushButton->setGeometry(QRect(350, 150, 80, 25));
        Description_textBrowser = new QTextBrowser(SkipBlankPagesSettingsDialog);
        Description_textBrowser->setObjectName(QStringLiteral("Description_textBrowser"));
        Description_textBrowser->setGeometry(QRect(20, 60, 411, 81));
        Description_textBrowser->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ADVANCEDSETTING_061</p></body></html>"));
        Description_textBrowser->setPlaceholderText(QStringLiteral(""));
        layoutWidget = new QWidget(SkipBlankPagesSettingsDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 30, 411, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Det_Lv_label = new QLabel(layoutWidget);
        Det_Lv_label->setObjectName(QStringLiteral("Det_Lv_label"));
        horizontalLayout->addWidget(Det_Lv_label);
        Det_Lv_colon_label = new QLabel(layoutWidget);
        Det_Lv_colon_label->setObjectName(QStringLiteral("Det_Lv_colon_label"));
        Det_Lv_colon_label->setEnabled(true);
#ifndef QT_NO_TOOLTIP
        Det_Lv_colon_label->setToolTip(QStringLiteral(""));
#endif
        Det_Lv_colon_label->setText(QStringLiteral(":"));
        horizontalLayout->addWidget(Det_Lv_colon_label);
        Det_Lv_horizontalSlider = new SkipBlankPagesDetLvSlider(layoutWidget);
        Det_Lv_horizontalSlider->setObjectName(QStringLiteral("Det_Lv_horizontalSlider"));
        Det_Lv_horizontalSlider->setMinimum(1);
        Det_Lv_horizontalSlider->setMaximum(30);
        Det_Lv_horizontalSlider->setValue(10);
        Det_Lv_horizontalSlider->setOrientation(Qt::Horizontal);
        Det_Lv_horizontalSlider->setInvertedAppearance(false);
        Det_Lv_horizontalSlider->setInvertedControls(false);
        horizontalLayout->addWidget(Det_Lv_horizontalSlider);
        Det_Lv_spinBox = new QSpinBox(layoutWidget);
        Det_Lv_spinBox->setObjectName(QStringLiteral("Det_Lv_spinBox"));
        Det_Lv_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Det_Lv_spinBox->setMinimum(1);
        Det_Lv_spinBox->setMaximum(30);
        Det_Lv_spinBox->setValue(10);
        horizontalLayout->addWidget(Det_Lv_spinBox);
        retranslateUi(SkipBlankPagesSettingsDialog);
        QObject::connect(CLose_pushButton, SIGNAL(clicked()), SkipBlankPagesSettingsDialog, SLOT(reject()));
        QObject::connect(Det_Lv_horizontalSlider, SIGNAL(valueChanged(int)), Det_Lv_spinBox, SLOT(setValue(int)));
        QObject::connect(Det_Lv_spinBox, SIGNAL(valueChanged(int)), Det_Lv_horizontalSlider, SLOT(setValue(int)));
        QObject::connect(Det_Lv_horizontalSlider, SIGNAL(valueChanged(int)), SkipBlankPagesSettingsDialog, SLOT(onValueChanged(int)));
        QMetaObject::connectSlotsByName(SkipBlankPagesSettingsDialog);
    }
    void retranslateUi(QDialog *SkipBlankPagesSettingsDialog)
    {
        SkipBlankPagesSettingsDialog->setWindowTitle(QApplication::translate("SkipBlankPagesSettingsDialog", "ADVANCEDSETTING_056", 0));
        CLose_pushButton->setText(QApplication::translate("SkipBlankPagesSettingsDialog", "TC_PREVIEW_001", 0));
        Det_Lv_label->setText(QApplication::translate("SkipBlankPagesSettingsDialog", "ADVANCEDSETTING_058", 0));
    }
};
namespace Ui {
    class SkipBlankPagesSettingsDialog: public Ui_SkipBlankPagesSettingsDialog {};
}
QT_END_NAMESPACE
#endif
