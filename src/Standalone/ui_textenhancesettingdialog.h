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
//  ui_textenhancesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_TEXTENHANCESETTINGDIALOG_H
#define UI_TEXTENHANCESETTINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "thresholdslider.h"
QT_BEGIN_NAMESPACE
class Ui_TextEnhanceSettingDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *textEnhanceSensitivity_horizontalLayout;
    QLabel *textEnhanceSensitivity_label;
    QLabel *textEnhanceSensitivity_colon_label;
    ThresholdSlider *textEnhanceSensitivity_hSlider;
    QSpinBox *textEnhanceSensitivity_spinBox;
    QWidget *layoutWidget_2;
    QHBoxLayout *thresholdAdjustment_horizontalLayout;
    QLabel *thresholdAdjustment_label;
    QLabel *thresholdAdjustment_colon_label;
    ThresholdSlider *thresholdAdjustment_hSlider;
    QSpinBox *thresholdAdjustment_spinBox;
    QWidget *layoutWidget_3;
    QHBoxLayout *textEnhanceNoiseReductionLevel_horizontalLayout;
    QLabel *textEnhanceNoiseReductionLevel_label;
    QLabel *textEnhanceNoiseReductionLevel_colon_label;
    ThresholdSlider *textEnhanceNoiseReductionLevel_hSlider;
    QSpinBox *textEnhanceNoiseReductionLevel_spinBox;
    QCheckBox *textEnhancePaperCreaseReduction_checkBox;
    QPushButton *Close_pushButton;
    void setupUi(QDialog *TextEnhanceSettingDialog)
    {
        if (TextEnhanceSettingDialog->objectName().isEmpty())
            TextEnhanceSettingDialog->setObjectName(QStringLiteral("TextEnhanceSettingDialog"));
        TextEnhanceSettingDialog->resize(457, 300);
        layoutWidget = new QWidget(TextEnhanceSettingDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 50, 391, 25));
        textEnhanceSensitivity_horizontalLayout = new QHBoxLayout(layoutWidget);
        textEnhanceSensitivity_horizontalLayout->setObjectName(QStringLiteral("textEnhanceSensitivity_horizontalLayout"));
        textEnhanceSensitivity_horizontalLayout->setContentsMargins(0, 0, 0, 0);
        textEnhanceSensitivity_label = new QLabel(layoutWidget);
        textEnhanceSensitivity_label->setObjectName(QStringLiteral("textEnhanceSensitivity_label"));
        textEnhanceSensitivity_horizontalLayout->addWidget(textEnhanceSensitivity_label);
        textEnhanceSensitivity_colon_label = new QLabel(layoutWidget);
        textEnhanceSensitivity_colon_label->setObjectName(QStringLiteral("textEnhanceSensitivity_colon_label"));
        textEnhanceSensitivity_colon_label->setEnabled(true);
        textEnhanceSensitivity_colon_label->setText(QStringLiteral(":"));
        textEnhanceSensitivity_horizontalLayout->addWidget(textEnhanceSensitivity_colon_label);
        textEnhanceSensitivity_hSlider = new ThresholdSlider(layoutWidget);
        textEnhanceSensitivity_hSlider->setObjectName(QStringLiteral("textEnhanceSensitivity_hSlider"));
        textEnhanceSensitivity_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        textEnhanceSensitivity_hSlider->setMinimum(-50);
        textEnhanceSensitivity_hSlider->setMaximum(50);
        textEnhanceSensitivity_hSlider->setPageStep(1);
        textEnhanceSensitivity_hSlider->setValue(0);
        textEnhanceSensitivity_hSlider->setOrientation(Qt::Horizontal);
        textEnhanceSensitivity_horizontalLayout->addWidget(textEnhanceSensitivity_hSlider);
        textEnhanceSensitivity_spinBox = new QSpinBox(layoutWidget);
        textEnhanceSensitivity_spinBox->setObjectName(QStringLiteral("textEnhanceSensitivity_spinBox"));
        textEnhanceSensitivity_spinBox->setMinimum(-50);
        textEnhanceSensitivity_spinBox->setMaximum(50);
        textEnhanceSensitivity_spinBox->setValue(0);
        textEnhanceSensitivity_spinBox->setDisplayIntegerBase(10);
        textEnhanceSensitivity_horizontalLayout->addWidget(textEnhanceSensitivity_spinBox);
        layoutWidget_2 = new QWidget(TextEnhanceSettingDialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 90, 391, 25));
        thresholdAdjustment_horizontalLayout = new QHBoxLayout(layoutWidget_2);
        thresholdAdjustment_horizontalLayout->setObjectName(QStringLiteral("thresholdAdjustment_horizontalLayout"));
        thresholdAdjustment_horizontalLayout->setContentsMargins(0, 0, 0, 0);
        thresholdAdjustment_label = new QLabel(layoutWidget_2);
        thresholdAdjustment_label->setObjectName(QStringLiteral("thresholdAdjustment_label"));
        thresholdAdjustment_horizontalLayout->addWidget(thresholdAdjustment_label);
        thresholdAdjustment_colon_label = new QLabel(layoutWidget_2);
        thresholdAdjustment_colon_label->setObjectName(QStringLiteral("thresholdAdjustment_colon_label"));
        thresholdAdjustment_colon_label->setEnabled(true);
        thresholdAdjustment_colon_label->setText(QStringLiteral(":"));
        thresholdAdjustment_horizontalLayout->addWidget(thresholdAdjustment_colon_label);
        thresholdAdjustment_hSlider = new ThresholdSlider(layoutWidget_2);
        thresholdAdjustment_hSlider->setObjectName(QStringLiteral("thresholdAdjustment_hSlider"));
        thresholdAdjustment_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        thresholdAdjustment_hSlider->setMinimum(-50);
        thresholdAdjustment_hSlider->setMaximum(50);
        thresholdAdjustment_hSlider->setPageStep(1);
        thresholdAdjustment_hSlider->setValue(0);
        thresholdAdjustment_hSlider->setOrientation(Qt::Horizontal);
        thresholdAdjustment_horizontalLayout->addWidget(thresholdAdjustment_hSlider);
        thresholdAdjustment_spinBox = new QSpinBox(layoutWidget_2);
        thresholdAdjustment_spinBox->setObjectName(QStringLiteral("thresholdAdjustment_spinBox"));
        thresholdAdjustment_spinBox->setMinimum(-50);
        thresholdAdjustment_spinBox->setMaximum(50);
        thresholdAdjustment_spinBox->setValue(0);
        thresholdAdjustment_spinBox->setDisplayIntegerBase(10);
        thresholdAdjustment_horizontalLayout->addWidget(thresholdAdjustment_spinBox);
        layoutWidget_3 = new QWidget(TextEnhanceSettingDialog);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(30, 130, 391, 25));
        textEnhanceNoiseReductionLevel_horizontalLayout = new QHBoxLayout(layoutWidget_3);
        textEnhanceNoiseReductionLevel_horizontalLayout->setObjectName(QStringLiteral("textEnhanceNoiseReductionLevel_horizontalLayout"));
        textEnhanceNoiseReductionLevel_horizontalLayout->setContentsMargins(0, 0, 0, 0);
        textEnhanceNoiseReductionLevel_label = new QLabel(layoutWidget_3);
        textEnhanceNoiseReductionLevel_label->setObjectName(QStringLiteral("textEnhanceNoiseReductionLevel_label"));
        textEnhanceNoiseReductionLevel_horizontalLayout->addWidget(textEnhanceNoiseReductionLevel_label);
        textEnhanceNoiseReductionLevel_colon_label = new QLabel(layoutWidget_3);
        textEnhanceNoiseReductionLevel_colon_label->setObjectName(QStringLiteral("textEnhanceNoiseReductionLevel_colon_label"));
        textEnhanceNoiseReductionLevel_colon_label->setEnabled(true);
        textEnhanceNoiseReductionLevel_colon_label->setText(QStringLiteral(":"));
        textEnhanceNoiseReductionLevel_horizontalLayout->addWidget(textEnhanceNoiseReductionLevel_colon_label);
        textEnhanceNoiseReductionLevel_hSlider = new ThresholdSlider(layoutWidget_3);
        textEnhanceNoiseReductionLevel_hSlider->setObjectName(QStringLiteral("textEnhanceNoiseReductionLevel_hSlider"));
        textEnhanceNoiseReductionLevel_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        textEnhanceNoiseReductionLevel_hSlider->setMinimum(1);
        textEnhanceNoiseReductionLevel_hSlider->setMaximum(5);
        textEnhanceNoiseReductionLevel_hSlider->setPageStep(1);
        textEnhanceNoiseReductionLevel_hSlider->setValue(1);
        textEnhanceNoiseReductionLevel_hSlider->setOrientation(Qt::Horizontal);
        textEnhanceNoiseReductionLevel_horizontalLayout->addWidget(textEnhanceNoiseReductionLevel_hSlider);
        textEnhanceNoiseReductionLevel_spinBox = new QSpinBox(layoutWidget_3);
        textEnhanceNoiseReductionLevel_spinBox->setObjectName(QStringLiteral("textEnhanceNoiseReductionLevel_spinBox"));
        textEnhanceNoiseReductionLevel_spinBox->setMinimum(1);
        textEnhanceNoiseReductionLevel_spinBox->setMaximum(5);
        textEnhanceNoiseReductionLevel_spinBox->setValue(1);
        textEnhanceNoiseReductionLevel_spinBox->setDisplayIntegerBase(10);
        textEnhanceNoiseReductionLevel_horizontalLayout->addWidget(textEnhanceNoiseReductionLevel_spinBox);
        textEnhancePaperCreaseReduction_checkBox = new QCheckBox(TextEnhanceSettingDialog);
        textEnhancePaperCreaseReduction_checkBox->setObjectName(QStringLiteral("textEnhancePaperCreaseReduction_checkBox"));
        textEnhancePaperCreaseReduction_checkBox->setGeometry(QRect(120, 190, 301, 23));
        Close_pushButton = new QPushButton(TextEnhanceSettingDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(299, 270, 121, 25));
        retranslateUi(TextEnhanceSettingDialog);
        QObject::connect(textEnhanceSensitivity_spinBox, SIGNAL(valueChanged(int)), textEnhanceSensitivity_hSlider, SLOT(setValue(int)));
        QObject::connect(textEnhanceSensitivity_hSlider, SIGNAL(valueChanged(int)), textEnhanceSensitivity_spinBox, SLOT(setValue(int)));
        QObject::connect(textEnhanceSensitivity_hSlider, SIGNAL(valueChanged(int)), TextEnhanceSettingDialog, SLOT(onValueChanged(int)));
        QObject::connect(Close_pushButton, SIGNAL(clicked()), TextEnhanceSettingDialog, SLOT(reject()));
        QObject::connect(thresholdAdjustment_spinBox, SIGNAL(valueChanged(int)), thresholdAdjustment_hSlider, SLOT(setValue(int)));
        QObject::connect(thresholdAdjustment_hSlider, SIGNAL(valueChanged(int)), thresholdAdjustment_spinBox, SLOT(setValue(int)));
        QObject::connect(thresholdAdjustment_hSlider, SIGNAL(valueChanged(int)), TextEnhanceSettingDialog, SLOT(onValueChanged(int)));
        QObject::connect(textEnhanceNoiseReductionLevel_spinBox, SIGNAL(valueChanged(int)), textEnhanceNoiseReductionLevel_hSlider, SLOT(setValue(int)));
        QObject::connect(textEnhanceNoiseReductionLevel_hSlider, SIGNAL(valueChanged(int)), textEnhanceNoiseReductionLevel_spinBox, SLOT(setValue(int)));
        QObject::connect(textEnhanceNoiseReductionLevel_hSlider, SIGNAL(valueChanged(int)), TextEnhanceSettingDialog, SLOT(onValueChanged(int)));
        QMetaObject::connectSlotsByName(TextEnhanceSettingDialog);
    }
    void retranslateUi(QDialog *TextEnhanceSettingDialog)
    {
        TextEnhanceSettingDialog->setWindowTitle(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_084", 0));
        textEnhanceSensitivity_label->setText(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_089", 0));
#ifndef QT_NO_TOOLTIP
        textEnhanceSensitivity_hSlider->setToolTip(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_077", 0));
#endif
        thresholdAdjustment_label->setText(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_086", 0));
#ifndef QT_NO_TOOLTIP
        thresholdAdjustment_hSlider->setToolTip(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_077", 0));
#endif
        textEnhanceNoiseReductionLevel_label->setText(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_087", 0));
#ifndef QT_NO_TOOLTIP
        textEnhanceNoiseReductionLevel_hSlider->setToolTip(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_077", 0));
#endif
        textEnhancePaperCreaseReduction_checkBox->setText(QApplication::translate("TextEnhanceSettingDialog", "ADVANCEDSETTING_088", 0));
        Close_pushButton->setText(QApplication::translate("TextEnhanceSettingDialog", "TC_PREVIEW_001", 0));
    }
};
namespace Ui {
    class TextEnhanceSettingDialog: public Ui_TextEnhanceSettingDialog {};
}
QT_END_NAMESPACE
#endif
