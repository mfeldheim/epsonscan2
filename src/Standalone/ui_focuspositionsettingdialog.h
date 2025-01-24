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
//  ui_focuspositionsettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_FOCUSPOSITIONSETTINGDIALOG_H
#define UI_FOCUSPOSITIONSETTINGDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "gammadoublespinbox.h"
#include "gammaslider.h"
QT_BEGIN_NAMESPACE
class Ui_FocusPositionSettingDialog
{
public:
    QPushButton *OK_pushButton;
    QPushButton *Cancel_pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *FocusPosition_label;
    QLabel *FocusPosition_colon_label;
    GammaSlider *FocusPosition_slider;
    GammaDoubleSpinBox *FocusPosition_spinBox;
    void setupUi(QDialog *FocusPositionSettingDialog)
    {
        if (FocusPositionSettingDialog->objectName().isEmpty())
            FocusPositionSettingDialog->setObjectName(QStringLiteral("FocusPositionSettingDialog"));
        FocusPositionSettingDialog->resize(452, 91);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FocusPositionSettingDialog->setWindowIcon(icon);
        OK_pushButton = new QPushButton(FocusPositionSettingDialog);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));
        OK_pushButton->setGeometry(QRect(360, 60, 80, 25));
        Cancel_pushButton = new QPushButton(FocusPositionSettingDialog);
        Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
        Cancel_pushButton->setGeometry(QRect(270, 60, 80, 25));
        layoutWidget = new QWidget(FocusPositionSettingDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 431, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        FocusPosition_label = new QLabel(layoutWidget);
        FocusPosition_label->setObjectName(QStringLiteral("FocusPosition_label"));
        horizontalLayout->addWidget(FocusPosition_label);
        FocusPosition_colon_label = new QLabel(layoutWidget);
        FocusPosition_colon_label->setObjectName(QStringLiteral("FocusPosition_colon_label"));
        horizontalLayout->addWidget(FocusPosition_colon_label);
        FocusPosition_slider = new GammaSlider(layoutWidget);
        FocusPosition_slider->setObjectName(QStringLiteral("FocusPosition_slider"));
        FocusPosition_slider->setMinimum(-20);
        FocusPosition_slider->setMaximum(60);
        FocusPosition_slider->setOrientation(Qt::Horizontal);
        horizontalLayout->addWidget(FocusPosition_slider);
        FocusPosition_spinBox = new GammaDoubleSpinBox(layoutWidget);
        FocusPosition_spinBox->setObjectName(QStringLiteral("FocusPosition_spinBox"));
        FocusPosition_spinBox->setDecimals(1);
        FocusPosition_spinBox->setMinimum(-2);
        FocusPosition_spinBox->setMaximum(6);
        FocusPosition_spinBox->setSingleStep(0.1);
        horizontalLayout->addWidget(FocusPosition_spinBox);
        retranslateUi(FocusPositionSettingDialog);
        QObject::connect(OK_pushButton, SIGNAL(pressed()), FocusPositionSettingDialog, SLOT(PushButtonAction()));
        QObject::connect(Cancel_pushButton, SIGNAL(pressed()), FocusPositionSettingDialog, SLOT(PushButtonAction()));
        QObject::connect(FocusPosition_slider, SIGNAL(valueChanged(int)), FocusPosition_spinBox, SLOT(setGamma(int)));
        QObject::connect(FocusPosition_spinBox, SIGNAL(valueChanged(double)), FocusPosition_slider, SLOT(setGammaSlider(double)));
        QMetaObject::connectSlotsByName(FocusPositionSettingDialog);
    }
    void retranslateUi(QDialog *FocusPositionSettingDialog)
    {
        FocusPositionSettingDialog->setWindowTitle(QApplication::translate("FocusPositionSettingDialog", "MANUAL_FOCUSPOSITION_002", 0));
        OK_pushButton->setText(QApplication::translate("FocusPositionSettingDialog", "ES2U_MAIN_046", 0));
        Cancel_pushButton->setText(QApplication::translate("FocusPositionSettingDialog", "ES2U_MAIN_047", 0));
        FocusPosition_label->setText(QApplication::translate("FocusPositionSettingDialog", "MANUAL_FOCUSPOSITION_002", 0));
        FocusPosition_colon_label->setText(QApplication::translate("FocusPositionSettingDialog", ":", 0));
    }
};
namespace Ui {
    class FocusPositionSettingDialog: public Ui_FocusPositionSettingDialog {};
}
QT_END_NAMESPACE
#endif
