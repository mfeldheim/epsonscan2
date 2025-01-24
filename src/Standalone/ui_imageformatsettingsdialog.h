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
//  ui_imageformatsettingsdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_IMAGEFORMATSETTINGSDIALOG_H
#define UI_IMAGEFORMATSETTINGSDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "imageformatsettingscombobox.h"
#include "tiffcompressionmonocombobox.h"
QT_BEGIN_NAMESPACE
class Ui_ImageFormatSettingsDialog
{
public:
    QPushButton *Close_pushButton;
    QFrame *Image_Format_frame;
    QStackedWidget *Image_Format_stackedWidget;
    QWidget *PNM;
    QLabel *no_option_label;
    QWidget *JPEG;
    QLabel *Encoding_label;
    QLabel *High_label;
    QLabel *High_Quality_label;
    QLabel *Encoding_colon_label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *Image_Quality_label;
    QLabel *Image_Quality_colon_label;
    QSlider *Image_Quality_horizontalSlider;
    QSpinBox *Image_Quality_spinBox;
    QRadioButton *Progressive_radioButton;
    QRadioButton *Standard_radioButton;
    QWidget *PNG;
    QLabel *no_option_label_2;
    QWidget *TIFF;
    QGroupBox *Compression_groupBox;
    QLabel *Black_White_label;
    TiffCompressionMonoCombobox *Black_White_comboBox;
    QLabel *Black_White_colon_label;
    QWidget *PDF;
    QLabel *Page_Number_label;
    QSpinBox *Select_Page_spinBox;
    QLabel *Page_Number_colon_label;
    QLabel *High_label_2;
    QLabel *High_Quality_label_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Image_Quality_label_2;
    QLabel *Image_Quality_colon_label_2;
    QSlider *Image_Quality_horizontalSlider_2;
    QSpinBox *Image_Quality_spinBox_2;
    QRadioButton *Select_Page_radioButton;
    QRadioButton *All_Page_radioButton;
    QWidget *page;
    QLabel *no_option_label_3;
    ImageFormatSettingsCombobox *Image_Format_Settings_comboBox;
    QLabel *ImageFormatlabel;
    QLabel *ImageFormat_colon_label;
    void setupUi(QDialog *ImageFormatSettingsDialog)
    {
        if (ImageFormatSettingsDialog->objectName().isEmpty())
            ImageFormatSettingsDialog->setObjectName(QStringLiteral("ImageFormatSettingsDialog"));
        ImageFormatSettingsDialog->resize(552, 402);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ImageFormatSettingsDialog->setWindowIcon(icon);
        Close_pushButton = new QPushButton(ImageFormatSettingsDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(456, 359, 80, 25));
        Image_Format_frame = new QFrame(ImageFormatSettingsDialog);
        Image_Format_frame->setObjectName(QStringLiteral("Image_Format_frame"));
        Image_Format_frame->setGeometry(QRect(14, 80, 521, 271));
        Image_Format_frame->setFrameShape(QFrame::StyledPanel);
        Image_Format_frame->setFrameShadow(QFrame::Raised);
        Image_Format_stackedWidget = new QStackedWidget(Image_Format_frame);
        Image_Format_stackedWidget->setObjectName(QStringLiteral("Image_Format_stackedWidget"));
        Image_Format_stackedWidget->setGeometry(QRect(10, 10, 501, 251));
        PNM = new QWidget();
        PNM->setObjectName(QStringLiteral("PNM"));
        no_option_label = new QLabel(PNM);
        no_option_label->setObjectName(QStringLiteral("no_option_label"));
        no_option_label->setGeometry(QRect(10, 10, 371, 21));
        Image_Format_stackedWidget->addWidget(PNM);
        JPEG = new QWidget();
        JPEG->setObjectName(QStringLiteral("JPEG"));
        Encoding_label = new QLabel(JPEG);
        Encoding_label->setObjectName(QStringLiteral("Encoding_label"));
        Encoding_label->setGeometry(QRect(11, 19, 181, 23));
        High_label = new QLabel(JPEG);
        High_label->setObjectName(QStringLiteral("High_label"));
        High_label->setGeometry(QRect(90, 130, 201, 23));
        High_Quality_label = new QLabel(JPEG);
        High_Quality_label->setObjectName(QStringLiteral("High_Quality_label"));
        High_Quality_label->setGeometry(QRect(340, 130, 131, 23));
        Encoding_colon_label = new QLabel(JPEG);
        Encoding_colon_label->setObjectName(QStringLiteral("Encoding_colon_label"));
        Encoding_colon_label->setEnabled(true);
        Encoding_colon_label->setGeometry(QRect(200, 22, 16, 16));
#ifndef QT_NO_TOOLTIP
        Encoding_colon_label->setToolTip(QStringLiteral(""));
#endif
        Encoding_colon_label->setText(QStringLiteral(":"));
        layoutWidget = new QWidget(JPEG);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 101, 461, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Image_Quality_label = new QLabel(layoutWidget);
        Image_Quality_label->setObjectName(QStringLiteral("Image_Quality_label"));
        horizontalLayout->addWidget(Image_Quality_label);
        Image_Quality_colon_label = new QLabel(layoutWidget);
        Image_Quality_colon_label->setObjectName(QStringLiteral("Image_Quality_colon_label"));
        Image_Quality_colon_label->setEnabled(true);
#ifndef QT_NO_TOOLTIP
        Image_Quality_colon_label->setToolTip(QStringLiteral(""));
#endif
        Image_Quality_colon_label->setText(QStringLiteral(":"));
        horizontalLayout->addWidget(Image_Quality_colon_label);
        Image_Quality_horizontalSlider = new QSlider(layoutWidget);
        Image_Quality_horizontalSlider->setObjectName(QStringLiteral("Image_Quality_horizontalSlider"));
        Image_Quality_horizontalSlider->setMaximum(100);
        Image_Quality_horizontalSlider->setValue(85);
        Image_Quality_horizontalSlider->setSliderPosition(85);
        Image_Quality_horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalLayout->addWidget(Image_Quality_horizontalSlider);
        Image_Quality_spinBox = new QSpinBox(layoutWidget);
        Image_Quality_spinBox->setObjectName(QStringLiteral("Image_Quality_spinBox"));
        Image_Quality_spinBox->setWrapping(false);
        Image_Quality_spinBox->setFrame(true);
        Image_Quality_spinBox->setReadOnly(false);
        Image_Quality_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Image_Quality_spinBox->setAccelerated(false);
        Image_Quality_spinBox->setMinimum(1);
        Image_Quality_spinBox->setMaximum(100);
        Image_Quality_spinBox->setValue(85);
        horizontalLayout->addWidget(Image_Quality_spinBox);
        Progressive_radioButton = new QRadioButton(JPEG);
        Progressive_radioButton->setObjectName(QStringLiteral("Progressive_radioButton"));
        Progressive_radioButton->setGeometry(QRect(221, 50, 215, 23));
        Standard_radioButton = new QRadioButton(JPEG);
        Standard_radioButton->setObjectName(QStringLiteral("Standard_radioButton"));
        Standard_radioButton->setGeometry(QRect(221, 23, 215, 23));
        Standard_radioButton->setChecked(true);
        Image_Format_stackedWidget->addWidget(JPEG);
        PNG = new QWidget();
        PNG->setObjectName(QStringLiteral("PNG"));
        no_option_label_2 = new QLabel(PNG);
        no_option_label_2->setObjectName(QStringLiteral("no_option_label_2"));
        no_option_label_2->setGeometry(QRect(10, 10, 381, 21));
        Image_Format_stackedWidget->addWidget(PNG);
        TIFF = new QWidget();
        TIFF->setObjectName(QStringLiteral("TIFF"));
        Compression_groupBox = new QGroupBox(TIFF);
        Compression_groupBox->setObjectName(QStringLiteral("Compression_groupBox"));
        Compression_groupBox->setGeometry(QRect(10, 20, 461, 101));
        Black_White_label = new QLabel(Compression_groupBox);
        Black_White_label->setObjectName(QStringLiteral("Black_White_label"));
        Black_White_label->setGeometry(QRect(20, 53, 221, 16));
        Black_White_comboBox = new TiffCompressionMonoCombobox(Compression_groupBox);
        Black_White_comboBox->setObjectName(QStringLiteral("Black_White_comboBox"));
        Black_White_comboBox->setGeometry(QRect(260, 50, 191, 22));
        Black_White_colon_label = new QLabel(Compression_groupBox);
        Black_White_colon_label->setObjectName(QStringLiteral("Black_White_colon_label"));
        Black_White_colon_label->setEnabled(true);
        Black_White_colon_label->setGeometry(QRect(250, 49, 20, 23));
#ifndef QT_NO_TOOLTIP
        Black_White_colon_label->setToolTip(QStringLiteral(""));
#endif
        Black_White_colon_label->setText(QStringLiteral(":"));
        Image_Format_stackedWidget->addWidget(TIFF);
        PDF = new QWidget();
        PDF->setObjectName(QStringLiteral("PDF"));
        Page_Number_label = new QLabel(PDF);
        Page_Number_label->setObjectName(QStringLiteral("Page_Number_label"));
        Page_Number_label->setGeometry(QRect(-1, 30, 141, 23));
        Select_Page_spinBox = new QSpinBox(PDF);
        Select_Page_spinBox->setObjectName(QStringLiteral("Select_Page_spinBox"));
        Select_Page_spinBox->setEnabled(false);
        Select_Page_spinBox->setGeometry(QRect(410, 80, 91, 22));
        Select_Page_spinBox->setLayoutDirection(Qt::LeftToRight);
        Select_Page_spinBox->setMinimum(1);
        Select_Page_spinBox->setMaximum(999);
        Page_Number_colon_label = new QLabel(PDF);
        Page_Number_colon_label->setObjectName(QStringLiteral("Page_Number_colon_label"));
        Page_Number_colon_label->setEnabled(true);
        Page_Number_colon_label->setGeometry(QRect(142, 31, 16, 16));
#ifndef QT_NO_TOOLTIP
        Page_Number_colon_label->setToolTip(QStringLiteral(""));
#endif
        Page_Number_colon_label->setText(QStringLiteral(":"));
        High_label_2 = new QLabel(PDF);
        High_label_2->setObjectName(QStringLiteral("High_label_2"));
        High_label_2->setGeometry(QRect(99, 149, 201, 23));
        High_Quality_label_2 = new QLabel(PDF);
        High_Quality_label_2->setObjectName(QStringLiteral("High_Quality_label_2"));
        High_Quality_label_2->setGeometry(QRect(349, 149, 131, 23));
        layoutWidget_2 = new QWidget(PDF);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 120, 461, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Image_Quality_label_2 = new QLabel(layoutWidget_2);
        Image_Quality_label_2->setObjectName(QStringLiteral("Image_Quality_label_2"));
        horizontalLayout_2->addWidget(Image_Quality_label_2);
        Image_Quality_colon_label_2 = new QLabel(layoutWidget_2);
        Image_Quality_colon_label_2->setObjectName(QStringLiteral("Image_Quality_colon_label_2"));
        Image_Quality_colon_label_2->setEnabled(true);
#ifndef QT_NO_TOOLTIP
        Image_Quality_colon_label_2->setToolTip(QStringLiteral(""));
#endif
        Image_Quality_colon_label_2->setText(QStringLiteral(":"));
        horizontalLayout_2->addWidget(Image_Quality_colon_label_2);
        Image_Quality_horizontalSlider_2 = new QSlider(layoutWidget_2);
        Image_Quality_horizontalSlider_2->setObjectName(QStringLiteral("Image_Quality_horizontalSlider_2"));
        Image_Quality_horizontalSlider_2->setMaximum(100);
        Image_Quality_horizontalSlider_2->setValue(85);
        Image_Quality_horizontalSlider_2->setSliderPosition(85);
        Image_Quality_horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalLayout_2->addWidget(Image_Quality_horizontalSlider_2);
        Image_Quality_spinBox_2 = new QSpinBox(layoutWidget_2);
        Image_Quality_spinBox_2->setObjectName(QStringLiteral("Image_Quality_spinBox_2"));
        Image_Quality_spinBox_2->setWrapping(false);
        Image_Quality_spinBox_2->setFrame(true);
        Image_Quality_spinBox_2->setReadOnly(false);
        Image_Quality_spinBox_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        Image_Quality_spinBox_2->setAccelerated(false);
        Image_Quality_spinBox_2->setMinimum(1);
        Image_Quality_spinBox_2->setMaximum(100);
        Image_Quality_spinBox_2->setValue(85);
        horizontalLayout_2->addWidget(Image_Quality_spinBox_2);
        Select_Page_radioButton = new QRadioButton(PDF);
        Select_Page_radioButton->setObjectName(QStringLiteral("Select_Page_radioButton"));
        Select_Page_radioButton->setGeometry(QRect(151, 60, 218, 23));
        Select_Page_radioButton->setAutoRepeat(true);
        All_Page_radioButton = new QRadioButton(PDF);
        All_Page_radioButton->setObjectName(QStringLiteral("All_Page_radioButton"));
        All_Page_radioButton->setGeometry(QRect(151, 31, 218, 23));
        All_Page_radioButton->setChecked(true);
        Image_Format_stackedWidget->addWidget(PDF);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        no_option_label_3 = new QLabel(page);
        no_option_label_3->setObjectName(QStringLiteral("no_option_label_3"));
        no_option_label_3->setGeometry(QRect(10, 10, 371, 21));
        Image_Format_stackedWidget->addWidget(page);
        Image_Format_Settings_comboBox = new ImageFormatSettingsCombobox(ImageFormatSettingsDialog);
        Image_Format_Settings_comboBox->setObjectName(QStringLiteral("Image_Format_Settings_comboBox"));
        Image_Format_Settings_comboBox->setGeometry(QRect(240, 30, 201, 23));
        ImageFormatlabel = new QLabel(ImageFormatSettingsDialog);
        ImageFormatlabel->setObjectName(QStringLiteral("ImageFormatlabel"));
        ImageFormatlabel->setGeometry(QRect(30, 31, 191, 23));
        ImageFormat_colon_label = new QLabel(ImageFormatSettingsDialog);
        ImageFormat_colon_label->setObjectName(QStringLiteral("ImageFormat_colon_label"));
        ImageFormat_colon_label->setEnabled(true);
        ImageFormat_colon_label->setGeometry(QRect(230, 33, 16, 23));
#ifndef QT_NO_TOOLTIP
        ImageFormat_colon_label->setToolTip(QStringLiteral(""));
#endif
        ImageFormat_colon_label->setText(QStringLiteral(":"));
        retranslateUi(ImageFormatSettingsDialog);
        QObject::connect(Image_Format_Settings_comboBox, SIGNAL(activated(int)), ImageFormatSettingsDialog, SLOT(onValueChanged(int)));
        QObject::connect(Close_pushButton, SIGNAL(clicked()), ImageFormatSettingsDialog, SLOT(reject()));
        QObject::connect(Image_Quality_horizontalSlider, SIGNAL(valueChanged(int)), Image_Quality_spinBox, SLOT(setValue(int)));
        QObject::connect(Image_Quality_spinBox, SIGNAL(valueChanged(int)), Image_Quality_horizontalSlider, SLOT(setValue(int)));
        QObject::connect(Select_Page_radioButton, SIGNAL(toggled(bool)), Select_Page_spinBox, SLOT(setEnabled(bool)));
        QObject::connect(Black_White_comboBox, SIGNAL(activated(int)), ImageFormatSettingsDialog, SLOT(onValueChanged(int)));
        QObject::connect(Standard_radioButton, SIGNAL(toggled(bool)), ImageFormatSettingsDialog, SLOT(update()));
        QObject::connect(ImageFormatSettingsDialog, SIGNAL(rejected()), ImageFormatSettingsDialog, SLOT(updateUI()));
        QObject::connect(Image_Quality_spinBox_2, SIGNAL(valueChanged(int)), Image_Quality_horizontalSlider_2, SLOT(setValue(int)));
        QObject::connect(Image_Quality_horizontalSlider_2, SIGNAL(valueChanged(int)), Image_Quality_spinBox_2, SLOT(setValue(int)));
        Image_Format_stackedWidget->setCurrentIndex(5);
        QMetaObject::connectSlotsByName(ImageFormatSettingsDialog);
    }
    void retranslateUi(QDialog *ImageFormatSettingsDialog)
    {
        ImageFormatSettingsDialog->setWindowTitle(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_001", 0));
        Close_pushButton->setText(QApplication::translate("ImageFormatSettingsDialog", "TC_PREVIEW_001", 0));
        no_option_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_003", 0));
        Encoding_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_001", 0));
        High_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_005", 0));
        High_Quality_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_006", 0));
        Image_Quality_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_004", 0));
        Progressive_radioButton->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_003", 0));
        Standard_radioButton->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_002", 0));
        no_option_label_2->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_003", 0));
        Compression_groupBox->setTitle(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_TIF_010", 0));
        Black_White_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_TIF_009", 0));
        Page_Number_label->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_PDF_004", 0));
        High_label_2->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_005", 0));
        High_Quality_label_2->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_006", 0));
        Image_Quality_label_2->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_JPG_004", 0));
        Select_Page_radioButton->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_PDF_006", 0));
        All_Page_radioButton->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_PDF_005", 0));
        no_option_label_3->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_003", 0));
        ImageFormatlabel->setText(QApplication::translate("ImageFormatSettingsDialog", "IMAGEFORMATOPTION_002", 0));
    }
};
namespace Ui {
    class ImageFormatSettingsDialog: public Ui_ImageFormatSettingsDialog {};
}
QT_END_NAMESPACE
#endif
