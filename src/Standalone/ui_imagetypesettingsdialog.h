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
//  ui_imagetypesettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_IMAGETYPESETTINGSDIALOG_H
#define UI_IMAGETYPESETTINGSDIALOG_H 
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
#include "paperthicknesscombobox.h"
#include "skipblankpagesdetlvslider.h"
QT_BEGIN_NAMESPACE
class Ui_ImageTypeSettingsDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *ImageType_Adjustment_label;
    QLabel *ImageType_Adjustment_colon_label;
    SkipBlankPagesDetLvSlider *ImageType_Adjustment_horizontalSlider;
    QPushButton *Close_pushButton;
    PaperThicknessComboBox *Detection_Color_Auto_comboBox;
    QLabel *Detection_Color_Auto_colon_label;
    QLabel *Detection_Color_Auto_label;
    QLabel *More_Gray_label;
    QLabel *More_BW_label;
    void setupUi(QDialog *ImageTypeSettingsDialog)
    {
        if (ImageTypeSettingsDialog->objectName().isEmpty())
            ImageTypeSettingsDialog->setObjectName(QStringLiteral("ImageTypeSettingsDialog"));
        ImageTypeSettingsDialog->resize(524, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageTypeSettingsDialog->sizePolicy().hasHeightForWidth());
        ImageTypeSettingsDialog->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(ImageTypeSettingsDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 170, 471, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ImageType_Adjustment_label = new QLabel(layoutWidget);
        ImageType_Adjustment_label->setObjectName(QStringLiteral("ImageType_Adjustment_label"));
        horizontalLayout->addWidget(ImageType_Adjustment_label);
        ImageType_Adjustment_colon_label = new QLabel(layoutWidget);
        ImageType_Adjustment_colon_label->setObjectName(QStringLiteral("ImageType_Adjustment_colon_label"));
        ImageType_Adjustment_colon_label->setEnabled(true);
#ifndef QT_NO_TOOLTIP
        ImageType_Adjustment_colon_label->setToolTip(QStringLiteral(""));
#endif
        ImageType_Adjustment_colon_label->setText(QStringLiteral(":"));
        horizontalLayout->addWidget(ImageType_Adjustment_colon_label);
        ImageType_Adjustment_horizontalSlider = new SkipBlankPagesDetLvSlider(layoutWidget);
        ImageType_Adjustment_horizontalSlider->setObjectName(QStringLiteral("ImageType_Adjustment_horizontalSlider"));
        ImageType_Adjustment_horizontalSlider->setMinimum(0);
        ImageType_Adjustment_horizontalSlider->setMaximum(4);
        ImageType_Adjustment_horizontalSlider->setPageStep(1);
        ImageType_Adjustment_horizontalSlider->setValue(2);
        ImageType_Adjustment_horizontalSlider->setOrientation(Qt::Horizontal);
        ImageType_Adjustment_horizontalSlider->setInvertedAppearance(false);
        ImageType_Adjustment_horizontalSlider->setInvertedControls(false);
        horizontalLayout->addWidget(ImageType_Adjustment_horizontalSlider);
        Close_pushButton = new QPushButton(ImageTypeSettingsDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(379, 260, 111, 25));
        Detection_Color_Auto_comboBox = new PaperThicknessComboBox(ImageTypeSettingsDialog);
        Detection_Color_Auto_comboBox->setObjectName(QStringLiteral("Detection_Color_Auto_comboBox"));
        Detection_Color_Auto_comboBox->setGeometry(QRect(280, 69, 191, 23));
        Detection_Color_Auto_colon_label = new QLabel(ImageTypeSettingsDialog);
        Detection_Color_Auto_colon_label->setObjectName(QStringLiteral("Detection_Color_Auto_colon_label"));
        Detection_Color_Auto_colon_label->setEnabled(true);
        Detection_Color_Auto_colon_label->setGeometry(QRect(260, 72, 16, 20));
#ifndef QT_NO_TOOLTIP
        Detection_Color_Auto_colon_label->setToolTip(QStringLiteral(""));
#endif
        Detection_Color_Auto_colon_label->setText(QStringLiteral(":"));
        Detection_Color_Auto_label = new QLabel(ImageTypeSettingsDialog);
        Detection_Color_Auto_label->setObjectName(QStringLiteral("Detection_Color_Auto_label"));
        Detection_Color_Auto_label->setGeometry(QRect(33, 70, 201, 23));
        More_Gray_label = new QLabel(ImageTypeSettingsDialog);
        More_Gray_label->setObjectName(QStringLiteral("More_Gray_label"));
        More_Gray_label->setGeometry(QRect(150, 190, 151, 23));
        More_BW_label = new QLabel(ImageTypeSettingsDialog);
        More_BW_label->setObjectName(QStringLiteral("More_BW_label"));
        More_BW_label->setGeometry(QRect(400, 190, 121, 23));
        retranslateUi(ImageTypeSettingsDialog);
        QObject::connect(Close_pushButton, SIGNAL(pressed()), ImageTypeSettingsDialog, SLOT(reject()));
        QObject::connect(Detection_Color_Auto_comboBox, SIGNAL(currentIndexChanged(int)), ImageTypeSettingsDialog, SLOT(onValueChanged(int)));
        QObject::connect(ImageType_Adjustment_horizontalSlider, SIGNAL(valueChanged(int)), ImageTypeSettingsDialog, SLOT(onValueChanged(int)));
        QMetaObject::connectSlotsByName(ImageTypeSettingsDialog);
    }
    void retranslateUi(QDialog *ImageTypeSettingsDialog)
    {
        ImageTypeSettingsDialog->setWindowTitle(QApplication::translate("ImageTypeSettingsDialog", "MAINSETTING_073", 0));
        ImageType_Adjustment_label->setText(QApplication::translate("ImageTypeSettingsDialog", "MAINSETTING_082", 0));
        Close_pushButton->setText(QApplication::translate("ImageTypeSettingsDialog", "TC_PREVIEW_001", 0));
        Detection_Color_Auto_label->setText(QApplication::translate("ImageTypeSettingsDialog", "MAINSETTING_074", 0));
        More_Gray_label->setText(QApplication::translate("ImageTypeSettingsDialog", "MAINSETTING_083", 0));
        More_BW_label->setText(QApplication::translate("ImageTypeSettingsDialog", "MAINSETTING_084", 0));
    }
};
namespace Ui {
    class ImageTypeSettingsDialog: public Ui_ImageTypeSettingsDialog {};
}
QT_END_NAMESPACE
#endif
