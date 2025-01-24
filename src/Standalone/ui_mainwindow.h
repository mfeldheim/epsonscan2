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
//  ui_mainwindow.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "addpagescheckbox.h"
#include "automaticfeedingmodecombobox.h"
#include "backgroundcolorcombobox.h"
#include "brightnessslider.h"
#include "contrastslider.h"
#include "deskewcheckbox.h"
#include "detectdoublefeedcomb.h"
#include "devicenamestackedwidget.h"
#include "deviceselectorcombobox.h"
#include "documentsize.h"
#include "documentsource.h"
#include "documenttype.h"
#include "dropoutcombobox.h"
#include "edgecorrection.h"
#include "foldercomb.h"
#include "gammadoublespinbox.h"
#include "gammaslider.h"
#include "horizondoctoolbutton.h"
#include "imageformatcomb.h"
#include "imagetype.h"
#include "noneradiobutton.h"
#include "prefixlineedit.h"
#include "previewbutton.h"
#include "removebackcombobox.h"
#include "removebackradiobutton.h"
#include "removepunchholes.h"
#include "resolution.h"
#include "rotate.h"
#include "scanbutton.h"
#include "scanningside.h"
#include "skipblankpagescomb.h"
#include "textenhancecombobox.h"
#include "thresholdslider.h"
#include "verticaldoctoolbutton.h"
QT_BEGIN_NAMESPACE
class Ui_MainWindow
{
public:
    QAction *actionAboutEpsonScan2;
    QAction *action_Exit;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    Document_Source *Document_source_comb;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    Document_Size *Document_size_comb;
    QWidget *page_4;
    Document_Size *Document_size_comb_2;
    HorizonDoctoolButton *Horizontal_doc_toolButton;
    VerticalDoctoolButton *Vertical_doc_toolButton;
    QLabel *Scanning_side_label;
    QLabel *Document_source_label;
    Scanning_Side *Scanning_side_comb;
    QLabel *Document_size_label;
    QLabel *Dpi_label;
    QLabel *Resolution_label;
    QLabel *Rotate_label;
    QLabel *Image_type_label;
    Image_Type *Image_type_comb;
    Resolution *Resolution_comb;
    DeskewCheckbox *Deskew_checkbox;
    RotateComb *Rotate_comb;
    QFrame *line;
    QLabel *Detect_double_page_label;
    QLabel *Skip_blank_pages_label;
    DetectDoubleFeedComb *Detect_double_feed_comb;
    AddpagesCheckbox *Ad_pages_checkbox;
    SkipblankpagesComb *Skip_blank_pages_comb;
    QFrame *line_2;
    QLabel *Doc_source_colon_label;
    QLabel *Scanning_side_colon_label;
    QLabel *Document_size_colon_label;
    QLabel *Image_type_colon_label;
    QLabel *Resolution_colon_label;
    QLabel *Rotate_colon_label;
    QLabel *Skip_blank_pages_colon_label;
    QLabel *Detect_double_page_colon_label;
    BackgroundColorCombobox *Background_color_comb;
    QLabel *Background_color_label;
    QLabel *Background_color_colon_label;
    AutomaticFeedingModeCombobox *Automatic_feeding_mode_comb;
    QLabel *Automatic_feeding_mode_colon_label;
    QLabel *Automatic_feeding_mode_label;
    QLabel *Document_type_colon_label;
    QLabel *Document_type_label;
    Document_Type *Document_type_comb;
    QWidget *tab_2;
    QLabel *Image_option_label;
    RemoveBackComboBox *RemoveBack_comboBox;
    DropoutCombobox *Dropout_comboBox;
    QStackedWidget *image_type_stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Threshold_label;
    QLabel *Document_size_colon_label_2;
    ThresholdSlider *Threshold_hSlider;
    QSpinBox *Threshold_spinBox;
    QWidget *page_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *Brightness_label;
    QLabel *Brightness_colon_label;
    BrightnessSlider *Brightness_hSlider;
    QSpinBox *Brightness_spinBox;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Contrast_label;
    QLabel *Contrast_colon_label;
    ContrastSlider *Contrast_hSlider;
    QSpinBox *Contrast_spinBox;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *Gamma_label;
    QLabel *Gamma_colon_label;
    GammaSlider *Gamma_hSlider;
    GammaDoubleSpinBox *Gamma_doubleSpinBox;
    QLabel *Image_option_colon_label;
    NoneRadioButton *None_radioButton;
    QRadioButton *Dropout_radioButton;
    RemoveBackRadioButton *RemoveBack_radioButton;
    QRadioButton *TextEnhance_radioButton;
    QStackedWidget *TextEnhance_stackedWidget;
    QWidget *ColorGray_page;
    TextEnhanceCombobox *TextEnhance_comboBox;
    QWidget *Mono_page;
    QPushButton *TextEnhance_Setting_pushButton;
    QLabel *remove_punch_holes_label;
    QLabel *remove_punch_holes_colon_label;
    RemovePunchHoles *remove_punch_holes_comb;
    QLabel *edge_correction_colon_label;
    EdgeCorrection *edge_correction_comb;
    QLabel *edge_correction_label;
    ImageFormatComb *Image_format_comb;
    FolderComb *Folder_comb;
    QLabel *Image_format_label;
    QLabel *File_name_label;
    QLabel *Folder_label;
    QLabel *File_extension_label;
    QToolButton *Configuration_toolButton;
    PrefixLineedit *Prefix_lineEdit;
    DeviceNameStackedWidget *Device_name_stackedWidget;
    QWidget *Dev_select_page;
    DeviceSelectorCombobox *Device_selector_comb;
    QLabel *device_name_label;
    QLabel *device_name_colon_label;
    QWidget *Dev_progress_page;
    QLabel *Connecting_label;
    QToolButton *Folder_toolButton;
    QStackedWidget *Scan_Button_stackedWidget;
    QWidget *page_scan;
    ScanButton *Scan_Button;
    PreviewButton *Preview_Button;
    QWidget *page_save;
    QPushButton *Save_pushButton;
    QLabel *Image_format_colon_label;
    QLabel *File_name_colon_label;
    QLabel *Folder_colon_label;
    QToolButton *Help_toolButton;
    QToolButton *FileNameSetting_toolButton;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QStatusBar *statusBar;
    QButtonGroup *ImageOption_buttonGroup;
    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(488, 690);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(488, 690));
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAboutEpsonScan2 = new QAction(MainWindow);
        actionAboutEpsonScan2->setObjectName(QStringLiteral("actionAboutEpsonScan2"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(false);
        tabWidget->setGeometry(QRect(16, 31, 451, 418));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setAcceptDrops(false);
        tabWidget->setAutoFillBackground(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        Document_source_comb = new Document_Source(tab);
        Document_source_comb->setObjectName(QStringLiteral("Document_source_comb"));
        Document_source_comb->setEnabled(false);
        Document_source_comb->setGeometry(QRect(230, 6, 201, 23));
        stackedWidget = new QStackedWidget(tab);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(230, 111, 211, 31));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        Document_size_comb = new Document_Size(page_3);
        Document_size_comb->setObjectName(QStringLiteral("Document_size_comb"));
        Document_size_comb->setEnabled(false);
        Document_size_comb->setGeometry(QRect(0, 4, 201, 23));
        Document_size_comb->setLayoutDirection(Qt::LeftToRight);
        Document_size_comb->setMaxVisibleItems(50);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        Document_size_comb_2 = new Document_Size(page_4);
        Document_size_comb_2->setObjectName(QStringLiteral("Document_size_comb_2"));
        Document_size_comb_2->setEnabled(false);
        Document_size_comb_2->setGeometry(QRect(0, 4, 131, 23));
        Document_size_comb_2->setMaxVisibleItems(50);
        Horizontal_doc_toolButton = new HorizonDoctoolButton(page_4);
        Horizontal_doc_toolButton->setObjectName(QStringLiteral("Horizontal_doc_toolButton"));
        Horizontal_doc_toolButton->setEnabled(false);
        Horizontal_doc_toolButton->setGeometry(QRect(140, 0, 31, 31));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(184, 242, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(219, 248, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(92, 121, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(123, 161, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Horizontal_doc_toolButton->setPalette(palette);
#ifndef QT_NO_TOOLTIP
        Horizontal_doc_toolButton->setToolTip(QStringLiteral(""));
#endif
        Horizontal_doc_toolButton->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/yokot.png"), QSize(), QIcon::Normal, QIcon::Off);
        Horizontal_doc_toolButton->setIcon(icon1);
        Horizontal_doc_toolButton->setIconSize(QSize(25, 25));
        Horizontal_doc_toolButton->setCheckable(true);
        Horizontal_doc_toolButton->setChecked(false);
        Horizontal_doc_toolButton->setAutoRepeat(false);
        Horizontal_doc_toolButton->setAutoExclusive(false);
        Horizontal_doc_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Horizontal_doc_toolButton->setAutoRaise(true);
        Horizontal_doc_toolButton->setArrowType(Qt::NoArrow);
        Vertical_doc_toolButton = new VerticalDoctoolButton(page_4);
        Vertical_doc_toolButton->setObjectName(QStringLiteral("Vertical_doc_toolButton"));
        Vertical_doc_toolButton->setEnabled(false);
        Vertical_doc_toolButton->setGeometry(QRect(170, 0, 31, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Vertical_doc_toolButton->setPalette(palette1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/tatet.png"), QSize(), QIcon::Normal, QIcon::Off);
        Vertical_doc_toolButton->setIcon(icon2);
        Vertical_doc_toolButton->setIconSize(QSize(25, 25));
        Vertical_doc_toolButton->setCheckable(true);
        Vertical_doc_toolButton->setChecked(false);
        Vertical_doc_toolButton->setAutoRepeat(false);
        Vertical_doc_toolButton->setAutoExclusive(false);
        Vertical_doc_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Vertical_doc_toolButton->setAutoRaise(true);
        stackedWidget->addWidget(page_4);
        Scanning_side_label = new QLabel(tab);
        Scanning_side_label->setObjectName(QStringLiteral("Scanning_side_label"));
        Scanning_side_label->setEnabled(false);
        Scanning_side_label->setGeometry(QRect(21, 88, 191, 23));
        Document_source_label = new QLabel(tab);
        Document_source_label->setObjectName(QStringLiteral("Document_source_label"));
        Document_source_label->setEnabled(false);
        Document_source_label->setGeometry(QRect(20, 9, 191, 23));
        Scanning_side_comb = new Scanning_Side(tab);
        Scanning_side_comb->setObjectName(QStringLiteral("Scanning_side_comb"));
        Scanning_side_comb->setEnabled(false);
        Scanning_side_comb->setGeometry(QRect(230, 87, 201, 23));
        Document_size_label = new QLabel(tab);
        Document_size_label->setObjectName(QStringLiteral("Document_size_label"));
        Document_size_label->setEnabled(false);
        Document_size_label->setGeometry(QRect(20, 116, 191, 23));
        Dpi_label = new QLabel(tab);
        Dpi_label->setObjectName(QStringLiteral("Dpi_label"));
        Dpi_label->setEnabled(false);
        Dpi_label->setGeometry(QRect(340, 186, 91, 23));
        Resolution_label = new QLabel(tab);
        Resolution_label->setObjectName(QStringLiteral("Resolution_label"));
        Resolution_label->setEnabled(false);
        Resolution_label->setGeometry(QRect(20, 184, 191, 23));
        Rotate_label = new QLabel(tab);
        Rotate_label->setObjectName(QStringLiteral("Rotate_label"));
        Rotate_label->setEnabled(false);
        Rotate_label->setGeometry(QRect(20, 212, 191, 23));
        Image_type_label = new QLabel(tab);
        Image_type_label->setObjectName(QStringLiteral("Image_type_label"));
        Image_type_label->setEnabled(false);
        Image_type_label->setGeometry(QRect(20, 154, 191, 23));
        Image_type_comb = new Image_Type(tab);
        Image_type_comb->setObjectName(QStringLiteral("Image_type_comb"));
        Image_type_comb->setEnabled(false);
        Image_type_comb->setGeometry(QRect(230, 154, 201, 23));
        Resolution_comb = new Resolution(tab);
        Resolution_comb->setObjectName(QStringLiteral("Resolution_comb"));
        Resolution_comb->setEnabled(false);
        Resolution_comb->setGeometry(QRect(230, 183, 101, 23));
        Resolution_comb->setEditable(true);
        Resolution_comb->setMaxCount(12800);
        Resolution_comb->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
        Deskew_checkbox = new DeskewCheckbox(tab);
        Deskew_checkbox->setObjectName(QStringLiteral("Deskew_checkbox"));
        Deskew_checkbox->setEnabled(false);
        Deskew_checkbox->setGeometry(QRect(20, 239, 411, 23));
        Rotate_comb = new RotateComb(tab);
        Rotate_comb->setObjectName(QStringLiteral("Rotate_comb"));
        Rotate_comb->setEnabled(false);
        Rotate_comb->setGeometry(QRect(230, 211, 201, 23));
        line = new QFrame(tab);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 136, 401, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        Detect_double_page_label = new QLabel(tab);
        Detect_double_page_label->setObjectName(QStringLiteral("Detect_double_page_label"));
        Detect_double_page_label->setEnabled(false);
        Detect_double_page_label->setGeometry(QRect(20, 297, 231, 23));
        Skip_blank_pages_label = new QLabel(tab);
        Skip_blank_pages_label->setObjectName(QStringLiteral("Skip_blank_pages_label"));
        Skip_blank_pages_label->setEnabled(false);
        Skip_blank_pages_label->setGeometry(QRect(20, 326, 231, 23));
        Detect_double_feed_comb = new DetectDoubleFeedComb(tab);
        Detect_double_feed_comb->setObjectName(QStringLiteral("Detect_double_feed_comb"));
        Detect_double_feed_comb->setEnabled(false);
        Detect_double_feed_comb->setGeometry(QRect(270, 296, 161, 23));
        Ad_pages_checkbox = new AddpagesCheckbox(tab);
        Ad_pages_checkbox->setObjectName(QStringLiteral("Ad_pages_checkbox"));
        Ad_pages_checkbox->setEnabled(false);
        Ad_pages_checkbox->setGeometry(QRect(20, 272, 411, 23));
        Skip_blank_pages_comb = new SkipblankpagesComb(tab);
        Skip_blank_pages_comb->setObjectName(QStringLiteral("Skip_blank_pages_comb"));
        Skip_blank_pages_comb->setEnabled(false);
        Skip_blank_pages_comb->setGeometry(QRect(270, 325, 161, 23));
        line_2 = new QFrame(tab);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 257, 401, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        Doc_source_colon_label = new QLabel(tab);
        Doc_source_colon_label->setObjectName(QStringLiteral("Doc_source_colon_label"));
        Doc_source_colon_label->setEnabled(false);
        Doc_source_colon_label->setGeometry(QRect(220, 9, 16, 20));
#ifndef QT_NO_TOOLTIP
        Doc_source_colon_label->setToolTip(QStringLiteral(""));
#endif
        Doc_source_colon_label->setText(QStringLiteral(":"));
        Scanning_side_colon_label = new QLabel(tab);
        Scanning_side_colon_label->setObjectName(QStringLiteral("Scanning_side_colon_label"));
        Scanning_side_colon_label->setEnabled(false);
        Scanning_side_colon_label->setGeometry(QRect(220, 89, 16, 20));
        Scanning_side_colon_label->setText(QStringLiteral(":"));
        Document_size_colon_label = new QLabel(tab);
        Document_size_colon_label->setObjectName(QStringLiteral("Document_size_colon_label"));
        Document_size_colon_label->setEnabled(false);
        Document_size_colon_label->setGeometry(QRect(220, 118, 16, 20));
        Document_size_colon_label->setText(QStringLiteral(":"));
        Image_type_colon_label = new QLabel(tab);
        Image_type_colon_label->setObjectName(QStringLiteral("Image_type_colon_label"));
        Image_type_colon_label->setEnabled(false);
        Image_type_colon_label->setGeometry(QRect(220, 157, 16, 20));
        Image_type_colon_label->setText(QStringLiteral(":"));
        Resolution_colon_label = new QLabel(tab);
        Resolution_colon_label->setObjectName(QStringLiteral("Resolution_colon_label"));
        Resolution_colon_label->setEnabled(false);
        Resolution_colon_label->setGeometry(QRect(220, 186, 16, 20));
        Resolution_colon_label->setText(QStringLiteral(":"));
        Rotate_colon_label = new QLabel(tab);
        Rotate_colon_label->setObjectName(QStringLiteral("Rotate_colon_label"));
        Rotate_colon_label->setEnabled(false);
        Rotate_colon_label->setGeometry(QRect(220, 214, 16, 20));
        Rotate_colon_label->setText(QStringLiteral(":"));
        Skip_blank_pages_colon_label = new QLabel(tab);
        Skip_blank_pages_colon_label->setObjectName(QStringLiteral("Skip_blank_pages_colon_label"));
        Skip_blank_pages_colon_label->setEnabled(false);
        Skip_blank_pages_colon_label->setGeometry(QRect(260, 328, 16, 20));
        Skip_blank_pages_colon_label->setText(QStringLiteral(":"));
        Detect_double_page_colon_label = new QLabel(tab);
        Detect_double_page_colon_label->setObjectName(QStringLiteral("Detect_double_page_colon_label"));
        Detect_double_page_colon_label->setEnabled(false);
        Detect_double_page_colon_label->setGeometry(QRect(260, 299, 16, 20));
        Detect_double_page_colon_label->setText(QStringLiteral(":"));
        Background_color_comb = new BackgroundColorCombobox(tab);
        Background_color_comb->setObjectName(QStringLiteral("Background_color_comb"));
        Background_color_comb->setEnabled(false);
        Background_color_comb->setGeometry(QRect(270, 354, 161, 23));
        Background_color_label = new QLabel(tab);
        Background_color_label->setObjectName(QStringLiteral("Background_color_label"));
        Background_color_label->setEnabled(false);
        Background_color_label->setGeometry(QRect(20, 355, 231, 23));
        Background_color_colon_label = new QLabel(tab);
        Background_color_colon_label->setObjectName(QStringLiteral("Background_color_colon_label"));
        Background_color_colon_label->setEnabled(false);
        Background_color_colon_label->setGeometry(QRect(260, 356, 16, 20));
        Background_color_colon_label->setText(QStringLiteral(":"));
        Automatic_feeding_mode_comb = new AutomaticFeedingModeCombobox(tab);
        Automatic_feeding_mode_comb->setObjectName(QStringLiteral("Automatic_feeding_mode_comb"));
        Automatic_feeding_mode_comb->setEnabled(false);
        Automatic_feeding_mode_comb->setGeometry(QRect(230, 60, 201, 23));
        Automatic_feeding_mode_colon_label = new QLabel(tab);
        Automatic_feeding_mode_colon_label->setObjectName(QStringLiteral("Automatic_feeding_mode_colon_label"));
        Automatic_feeding_mode_colon_label->setEnabled(false);
        Automatic_feeding_mode_colon_label->setGeometry(QRect(220, 63, 16, 20));
#ifndef QT_NO_TOOLTIP
        Automatic_feeding_mode_colon_label->setToolTip(QStringLiteral(""));
#endif
        Automatic_feeding_mode_colon_label->setText(QStringLiteral(":"));
        Automatic_feeding_mode_label = new QLabel(tab);
        Automatic_feeding_mode_label->setObjectName(QStringLiteral("Automatic_feeding_mode_label"));
        Automatic_feeding_mode_label->setEnabled(false);
        Automatic_feeding_mode_label->setGeometry(QRect(20, 57, 201, 31));
        Automatic_feeding_mode_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Automatic_feeding_mode_label->setWordWrap(true);
        Document_type_colon_label = new QLabel(tab);
        Document_type_colon_label->setObjectName(QStringLiteral("Document_type_colon_label"));
        Document_type_colon_label->setEnabled(false);
        Document_type_colon_label->setGeometry(QRect(220, 36, 16, 20));
#ifndef QT_NO_TOOLTIP
        Document_type_colon_label->setToolTip(QStringLiteral(""));
#endif
        Document_type_colon_label->setText(QStringLiteral(":"));
        Document_type_label = new QLabel(tab);
        Document_type_label->setObjectName(QStringLiteral("Document_type_label"));
        Document_type_label->setEnabled(false);
        Document_type_label->setGeometry(QRect(20, 36, 191, 23));
        Document_type_comb = new Document_Type(tab);
        Document_type_comb->setObjectName(QStringLiteral("Document_type_comb"));
        Document_type_comb->setEnabled(false);
        Document_type_comb->setGeometry(QRect(230, 33, 201, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        Image_option_label = new QLabel(tab_2);
        Image_option_label->setObjectName(QStringLiteral("Image_option_label"));
        Image_option_label->setGeometry(QRect(4, 30, 151, 23));
        RemoveBack_comboBox = new RemoveBackComboBox(tab_2);
        RemoveBack_comboBox->setObjectName(QStringLiteral("RemoveBack_comboBox"));
        RemoveBack_comboBox->setEnabled(false);
        RemoveBack_comboBox->setGeometry(QRect(188, 100, 91, 23));
        Dropout_comboBox = new DropoutCombobox(tab_2);
        Dropout_comboBox->setObjectName(QStringLiteral("Dropout_comboBox"));
        Dropout_comboBox->setEnabled(false);
        Dropout_comboBox->setGeometry(QRect(351, 54, 91, 23));
        image_type_stackedWidget = new QStackedWidget(tab_2);
        image_type_stackedWidget->setObjectName(QStringLiteral("image_type_stackedWidget"));
        image_type_stackedWidget->setGeometry(QRect(10, 190, 421, 101));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(13, 10, 391, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Threshold_label = new QLabel(layoutWidget);
        Threshold_label->setObjectName(QStringLiteral("Threshold_label"));
        horizontalLayout_3->addWidget(Threshold_label);
        Document_size_colon_label_2 = new QLabel(layoutWidget);
        Document_size_colon_label_2->setObjectName(QStringLiteral("Document_size_colon_label_2"));
        Document_size_colon_label_2->setEnabled(false);
        Document_size_colon_label_2->setText(QStringLiteral(":"));
        horizontalLayout_3->addWidget(Document_size_colon_label_2);
        Threshold_hSlider = new ThresholdSlider(layoutWidget);
        Threshold_hSlider->setObjectName(QStringLiteral("Threshold_hSlider"));
        Threshold_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        Threshold_hSlider->setMaximum(255);
        Threshold_hSlider->setValue(110);
        Threshold_hSlider->setOrientation(Qt::Horizontal);
        horizontalLayout_3->addWidget(Threshold_hSlider);
        Threshold_spinBox = new QSpinBox(layoutWidget);
        Threshold_spinBox->setObjectName(QStringLiteral("Threshold_spinBox"));
        Threshold_spinBox->setMinimum(0);
        Threshold_spinBox->setMaximum(255);
        Threshold_spinBox->setValue(110);
        Threshold_spinBox->setDisplayIntegerBase(10);
        horizontalLayout_3->addWidget(Threshold_spinBox);
        image_type_stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        layoutWidget1 = new QWidget(page_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 9, 401, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Brightness_label = new QLabel(layoutWidget1);
        Brightness_label->setObjectName(QStringLiteral("Brightness_label"));
        horizontalLayout->addWidget(Brightness_label);
        Brightness_colon_label = new QLabel(layoutWidget1);
        Brightness_colon_label->setObjectName(QStringLiteral("Brightness_colon_label"));
        Brightness_colon_label->setEnabled(false);
        Brightness_colon_label->setText(QStringLiteral(":"));
        horizontalLayout->addWidget(Brightness_colon_label);
        Brightness_hSlider = new BrightnessSlider(layoutWidget1);
        Brightness_hSlider->setObjectName(QStringLiteral("Brightness_hSlider"));
        Brightness_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        Brightness_hSlider->setMinimum(-100);
        Brightness_hSlider->setMaximum(100);
        Brightness_hSlider->setOrientation(Qt::Horizontal);
        horizontalLayout->addWidget(Brightness_hSlider);
        Brightness_spinBox = new QSpinBox(layoutWidget1);
        Brightness_spinBox->setObjectName(QStringLiteral("Brightness_spinBox"));
        Brightness_spinBox->setMinimum(-100);
        Brightness_spinBox->setMaximum(100);
        Brightness_spinBox->setSingleStep(1);
        Brightness_spinBox->setValue(0);
        Brightness_spinBox->setDisplayIntegerBase(10);
        horizontalLayout->addWidget(Brightness_spinBox);
        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 40, 401, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Contrast_label = new QLabel(layoutWidget2);
        Contrast_label->setObjectName(QStringLiteral("Contrast_label"));
        horizontalLayout_2->addWidget(Contrast_label);
        Contrast_colon_label = new QLabel(layoutWidget2);
        Contrast_colon_label->setObjectName(QStringLiteral("Contrast_colon_label"));
        Contrast_colon_label->setEnabled(false);
        Contrast_colon_label->setText(QStringLiteral(":"));
        horizontalLayout_2->addWidget(Contrast_colon_label);
        Contrast_hSlider = new ContrastSlider(layoutWidget2);
        Contrast_hSlider->setObjectName(QStringLiteral("Contrast_hSlider"));
        Contrast_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        Contrast_hSlider->setAutoFillBackground(true);
        Contrast_hSlider->setMinimum(-100);
        Contrast_hSlider->setMaximum(100);
        Contrast_hSlider->setOrientation(Qt::Horizontal);
        Contrast_hSlider->setInvertedAppearance(false);
        Contrast_hSlider->setInvertedControls(false);
        horizontalLayout_2->addWidget(Contrast_hSlider);
        Contrast_spinBox = new QSpinBox(layoutWidget2);
        Contrast_spinBox->setObjectName(QStringLiteral("Contrast_spinBox"));
        Contrast_spinBox->setMinimum(-100);
        Contrast_spinBox->setMaximum(100);
        Contrast_spinBox->setDisplayIntegerBase(10);
        horizontalLayout_2->addWidget(Contrast_spinBox);
        layoutWidget3 = new QWidget(page_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 70, 401, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        Gamma_label = new QLabel(layoutWidget3);
        Gamma_label->setObjectName(QStringLiteral("Gamma_label"));
        horizontalLayout_4->addWidget(Gamma_label);
        Gamma_colon_label = new QLabel(layoutWidget3);
        Gamma_colon_label->setObjectName(QStringLiteral("Gamma_colon_label"));
        Gamma_colon_label->setEnabled(false);
        Gamma_colon_label->setText(QStringLiteral(":"));
        horizontalLayout_4->addWidget(Gamma_colon_label);
        Gamma_hSlider = new GammaSlider(layoutWidget3);
        Gamma_hSlider->setObjectName(QStringLiteral("Gamma_hSlider"));
        Gamma_hSlider->setCursor(QCursor(Qt::ArrowCursor));
        Gamma_hSlider->setMouseTracking(false);
        Gamma_hSlider->setAutoFillBackground(true);
        Gamma_hSlider->setMinimum(5);
        Gamma_hSlider->setMaximum(30);
        Gamma_hSlider->setSingleStep(1);
        Gamma_hSlider->setPageStep(10);
        Gamma_hSlider->setValue(22);
        Gamma_hSlider->setTracking(true);
        Gamma_hSlider->setOrientation(Qt::Horizontal);
        Gamma_hSlider->setInvertedAppearance(false);
        Gamma_hSlider->setInvertedControls(false);
        Gamma_hSlider->setTickPosition(QSlider::NoTicks);
        horizontalLayout_4->addWidget(Gamma_hSlider);
        Gamma_doubleSpinBox = new GammaDoubleSpinBox(layoutWidget3);
        Gamma_doubleSpinBox->setObjectName(QStringLiteral("Gamma_doubleSpinBox"));
        Gamma_doubleSpinBox->setDecimals(1);
        Gamma_doubleSpinBox->setMinimum(0.5);
        Gamma_doubleSpinBox->setMaximum(3);
        Gamma_doubleSpinBox->setSingleStep(0.1);
        Gamma_doubleSpinBox->setValue(2.2);
        horizontalLayout_4->addWidget(Gamma_doubleSpinBox);
        image_type_stackedWidget->addWidget(page_2);
        Image_option_colon_label = new QLabel(tab_2);
        Image_option_colon_label->setObjectName(QStringLiteral("Image_option_colon_label"));
        Image_option_colon_label->setEnabled(false);
        Image_option_colon_label->setGeometry(QRect(160, 32, 16, 20));
#ifndef QT_NO_TOOLTIP
        Image_option_colon_label->setToolTip(QStringLiteral(""));
#endif
        Image_option_colon_label->setText(QStringLiteral(":"));
        None_radioButton = new NoneRadioButton(tab_2);
        ImageOption_buttonGroup = new QButtonGroup(MainWindow);
        ImageOption_buttonGroup->setObjectName(QStringLiteral("ImageOption_buttonGroup"));
        ImageOption_buttonGroup->setExclusive(true);
        ImageOption_buttonGroup->addButton(None_radioButton);
        None_radioButton->setObjectName(QStringLiteral("None_radioButton"));
        None_radioButton->setGeometry(QRect(168, 32, 181, 23));
        None_radioButton->setCheckable(true);
        None_radioButton->setChecked(true);
        Dropout_radioButton = new QRadioButton(tab_2);
        ImageOption_buttonGroup->addButton(Dropout_radioButton);
        Dropout_radioButton->setObjectName(QStringLiteral("Dropout_radioButton"));
        Dropout_radioButton->setGeometry(QRect(168, 56, 181, 23));
        RemoveBack_radioButton = new RemoveBackRadioButton(tab_2);
        ImageOption_buttonGroup->addButton(RemoveBack_radioButton);
        RemoveBack_radioButton->setObjectName(QStringLiteral("RemoveBack_radioButton"));
        RemoveBack_radioButton->setGeometry(QRect(168, 80, 271, 23));
        RemoveBack_radioButton->setChecked(false);
        TextEnhance_radioButton = new QRadioButton(tab_2);
        ImageOption_buttonGroup->addButton(TextEnhance_radioButton);
        TextEnhance_radioButton->setObjectName(QStringLiteral("TextEnhance_radioButton"));
        TextEnhance_radioButton->setGeometry(QRect(168, 130, 271, 23));
        TextEnhance_stackedWidget = new QStackedWidget(tab_2);
        TextEnhance_stackedWidget->setObjectName(QStringLiteral("TextEnhance_stackedWidget"));
        TextEnhance_stackedWidget->setGeometry(QRect(170, 150, 211, 31));
        ColorGray_page = new QWidget();
        ColorGray_page->setObjectName(QStringLiteral("ColorGray_page"));
        TextEnhance_comboBox = new TextEnhanceCombobox(ColorGray_page);
        TextEnhance_comboBox->setObjectName(QStringLiteral("TextEnhance_comboBox"));
        TextEnhance_comboBox->setGeometry(QRect(20, 1, 91, 23));
        TextEnhance_stackedWidget->addWidget(ColorGray_page);
        Mono_page = new QWidget();
        Mono_page->setObjectName(QStringLiteral("Mono_page"));
        TextEnhance_Setting_pushButton = new QPushButton(Mono_page);
        TextEnhance_Setting_pushButton->setObjectName(QStringLiteral("TextEnhance_Setting_pushButton"));
        TextEnhance_Setting_pushButton->setGeometry(QRect(20, 1, 111, 23));
        TextEnhance_stackedWidget->addWidget(Mono_page);
        remove_punch_holes_label = new QLabel(tab_2);
        remove_punch_holes_label->setObjectName(QStringLiteral("remove_punch_holes_label"));
        remove_punch_holes_label->setEnabled(false);
        remove_punch_holes_label->setGeometry(QRect(10, 310, 191, 23));
        remove_punch_holes_colon_label = new QLabel(tab_2);
        remove_punch_holes_colon_label->setObjectName(QStringLiteral("remove_punch_holes_colon_label"));
        remove_punch_holes_colon_label->setEnabled(false);
        remove_punch_holes_colon_label->setGeometry(QRect(210, 313, 16, 20));
        remove_punch_holes_colon_label->setText(QStringLiteral(":"));
        remove_punch_holes_comb = new RemovePunchHoles(tab_2);
        remove_punch_holes_comb->setObjectName(QStringLiteral("remove_punch_holes_comb"));
        remove_punch_holes_comb->setEnabled(false);
        remove_punch_holes_comb->setGeometry(QRect(220, 310, 201, 23));
        edge_correction_colon_label = new QLabel(tab_2);
        edge_correction_colon_label->setObjectName(QStringLiteral("edge_correction_colon_label"));
        edge_correction_colon_label->setEnabled(false);
        edge_correction_colon_label->setGeometry(QRect(210, 340, 16, 20));
        edge_correction_colon_label->setText(QStringLiteral(":"));
        edge_correction_comb = new EdgeCorrection(tab_2);
        edge_correction_comb->setObjectName(QStringLiteral("edge_correction_comb"));
        edge_correction_comb->setEnabled(false);
        edge_correction_comb->setGeometry(QRect(220, 340, 201, 23));
        edge_correction_label = new QLabel(tab_2);
        edge_correction_label->setObjectName(QStringLiteral("edge_correction_label"));
        edge_correction_label->setEnabled(false);
        edge_correction_label->setGeometry(QRect(10, 340, 191, 23));
        tabWidget->addTab(tab_2, QString());
        Image_format_comb = new ImageFormatComb(centralWidget);
        Image_format_comb->setObjectName(QStringLiteral("Image_format_comb"));
        Image_format_comb->setEnabled(false);
        Image_format_comb->setGeometry(QRect(200, 461, 221, 23));
        Folder_comb = new FolderComb(centralWidget);
        Folder_comb->setObjectName(QStringLiteral("Folder_comb"));
        Folder_comb->setEnabled(false);
        Folder_comb->setGeometry(QRect(200, 521, 191, 23));
        Folder_comb->setInsertPolicy(QComboBox::InsertAtBottom);
        Folder_comb->setModelColumn(0);
        Image_format_label = new QLabel(centralWidget);
        Image_format_label->setObjectName(QStringLiteral("Image_format_label"));
        Image_format_label->setEnabled(false);
        Image_format_label->setGeometry(QRect(30, 462, 161, 23));
        File_name_label = new QLabel(centralWidget);
        File_name_label->setObjectName(QStringLiteral("File_name_label"));
        File_name_label->setEnabled(false);
        File_name_label->setGeometry(QRect(30, 492, 161, 23));
        Folder_label = new QLabel(centralWidget);
        Folder_label->setObjectName(QStringLiteral("Folder_label"));
        Folder_label->setEnabled(false);
        Folder_label->setGeometry(QRect(30, 522, 161, 23));
        File_extension_label = new QLabel(centralWidget);
        File_extension_label->setObjectName(QStringLiteral("File_extension_label"));
        File_extension_label->setEnabled(false);
        File_extension_label->setGeometry(QRect(393, 494, 41, 23));
        Configuration_toolButton = new QToolButton(centralWidget);
        Configuration_toolButton->setObjectName(QStringLiteral("Configuration_toolButton"));
        Configuration_toolButton->setEnabled(false);
        Configuration_toolButton->setGeometry(QRect(60, 557, 31, 31));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/btn_config@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        Configuration_toolButton->setIcon(icon3);
        Configuration_toolButton->setIconSize(QSize(25, 25));
        Configuration_toolButton->setCheckable(false);
        Configuration_toolButton->setAutoRepeat(false);
        Configuration_toolButton->setAutoExclusive(false);
        Configuration_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Configuration_toolButton->setAutoRaise(true);
        Prefix_lineEdit = new PrefixLineedit(centralWidget);
        Prefix_lineEdit->setObjectName(QStringLiteral("Prefix_lineEdit"));
        Prefix_lineEdit->setEnabled(false);
        Prefix_lineEdit->setGeometry(QRect(200, 490, 191, 23));
        Prefix_lineEdit->setInputMethodHints(Qt::ImhNone);
        Prefix_lineEdit->setText(QStringLiteral("img"));
        Prefix_lineEdit->setMaxLength(64);
        Prefix_lineEdit->setFrame(true);
        Prefix_lineEdit->setEchoMode(QLineEdit::Normal);
        Prefix_lineEdit->setCursorPosition(3);
        Prefix_lineEdit->setDragEnabled(false);
        Prefix_lineEdit->setPlaceholderText(QStringLiteral("img"));
        Prefix_lineEdit->setClearButtonEnabled(true);
        Device_name_stackedWidget = new DeviceNameStackedWidget(centralWidget);
        Device_name_stackedWidget->setObjectName(QStringLiteral("Device_name_stackedWidget"));
        Device_name_stackedWidget->setGeometry(QRect(20, -6, 391, 41));
        Dev_select_page = new QWidget();
        Dev_select_page->setObjectName(QStringLiteral("Dev_select_page"));
        Device_selector_comb = new DeviceSelectorCombobox(Dev_select_page);
        Device_selector_comb->setObjectName(QStringLiteral("Device_selector_comb"));
        Device_selector_comb->setGeometry(QRect(130, 10, 221, 23));
        Device_selector_comb->setEditable(false);
        Device_selector_comb->setMaxVisibleItems(50);
        device_name_label = new QLabel(Dev_select_page);
        device_name_label->setObjectName(QStringLiteral("device_name_label"));
        device_name_label->setGeometry(QRect(10, 11, 101, 23));
        device_name_colon_label = new QLabel(Dev_select_page);
        device_name_colon_label->setObjectName(QStringLiteral("device_name_colon_label"));
        device_name_colon_label->setEnabled(false);
        device_name_colon_label->setGeometry(QRect(120, 13, 16, 20));
#ifndef QT_NO_TOOLTIP
        device_name_colon_label->setToolTip(QStringLiteral(""));
#endif
        device_name_colon_label->setText(QStringLiteral(":"));
        Device_name_stackedWidget->addWidget(Dev_select_page);
        Dev_progress_page = new QWidget();
        Dev_progress_page->setObjectName(QStringLiteral("Dev_progress_page"));
        Connecting_label = new QLabel(Dev_progress_page);
        Connecting_label->setObjectName(QStringLiteral("Connecting_label"));
        Connecting_label->setGeometry(QRect(109, 5, 231, 31));
        QFont font;
        font.setFamily(QStringLiteral("Century Schoolbook L"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        Connecting_label->setFont(font);
        Connecting_label->setText(QStringLiteral("Connecting the scanner"));
        Device_name_stackedWidget->addWidget(Dev_progress_page);
        Folder_toolButton = new QToolButton(centralWidget);
        Folder_toolButton->setObjectName(QStringLiteral("Folder_toolButton"));
        Folder_toolButton->setEnabled(false);
        Folder_toolButton->setGeometry(QRect(394, 517, 31, 31));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/savefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        Folder_toolButton->setIcon(icon4);
        Folder_toolButton->setIconSize(QSize(25, 25));
        Folder_toolButton->setCheckable(false);
        Folder_toolButton->setAutoRepeat(false);
        Folder_toolButton->setAutoExclusive(false);
        Folder_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Folder_toolButton->setAutoRaise(true);
        Scan_Button_stackedWidget = new QStackedWidget(centralWidget);
        Scan_Button_stackedWidget->setObjectName(QStringLiteral("Scan_Button_stackedWidget"));
        Scan_Button_stackedWidget->setEnabled(true);
        Scan_Button_stackedWidget->setGeometry(QRect(150, 546, 311, 51));
        page_scan = new QWidget();
        page_scan->setObjectName(QStringLiteral("page_scan"));
        Scan_Button = new ScanButton(page_scan);
        Scan_Button->setObjectName(QStringLiteral("Scan_Button"));
        Scan_Button->setEnabled(false);
        Scan_Button->setGeometry(QRect(170, 10, 101, 31));
        Preview_Button = new PreviewButton(page_scan);
        Preview_Button->setObjectName(QStringLiteral("Preview_Button"));
        Preview_Button->setEnabled(false);
        Preview_Button->setGeometry(QRect(60, 10, 101, 31));
        Scan_Button_stackedWidget->addWidget(page_scan);
        page_save = new QWidget();
        page_save->setObjectName(QStringLiteral("page_save"));
        Save_pushButton = new QPushButton(page_save);
        Save_pushButton->setObjectName(QStringLiteral("Save_pushButton"));
        Save_pushButton->setEnabled(false);
        Save_pushButton->setGeometry(QRect(30, 10, 101, 31));
        Scan_Button_stackedWidget->addWidget(page_save);
        Image_format_colon_label = new QLabel(centralWidget);
        Image_format_colon_label->setObjectName(QStringLiteral("Image_format_colon_label"));
        Image_format_colon_label->setEnabled(false);
        Image_format_colon_label->setGeometry(QRect(192, 464, 16, 20));
        Image_format_colon_label->setText(QStringLiteral(":"));
        File_name_colon_label = new QLabel(centralWidget);
        File_name_colon_label->setObjectName(QStringLiteral("File_name_colon_label"));
        File_name_colon_label->setEnabled(false);
        File_name_colon_label->setGeometry(QRect(192, 494, 16, 20));
        File_name_colon_label->setText(QStringLiteral(":"));
        Folder_colon_label = new QLabel(centralWidget);
        Folder_colon_label->setObjectName(QStringLiteral("Folder_colon_label"));
        Folder_colon_label->setEnabled(false);
        Folder_colon_label->setGeometry(QRect(192, 524, 16, 20));
        Folder_colon_label->setText(QStringLiteral(":"));
        Help_toolButton = new QToolButton(centralWidget);
        Help_toolButton->setObjectName(QStringLiteral("Help_toolButton"));
        Help_toolButton->setEnabled(false);
        Help_toolButton->setGeometry(QRect(24, 557, 31, 31));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/btn_help.png"), QSize(), QIcon::Normal, QIcon::Off);
        Help_toolButton->setIcon(icon5);
        Help_toolButton->setIconSize(QSize(25, 25));
        Help_toolButton->setCheckable(false);
        Help_toolButton->setAutoRepeat(false);
        Help_toolButton->setAutoExclusive(false);
        Help_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Help_toolButton->setAutoRaise(true);
        FileNameSetting_toolButton = new QToolButton(centralWidget);
        FileNameSetting_toolButton->setObjectName(QStringLiteral("FileNameSetting_toolButton"));
        FileNameSetting_toolButton->setEnabled(true);
        FileNameSetting_toolButton->setGeometry(QRect(433, 492, 21, 21));
        FileNameSetting_toolButton->setIcon(icon4);
        FileNameSetting_toolButton->setIconSize(QSize(25, 25));
        FileNameSetting_toolButton->setCheckable(false);
        FileNameSetting_toolButton->setAutoRepeat(false);
        FileNameSetting_toolButton->setAutoExclusive(false);
        FileNameSetting_toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        FileNameSetting_toolButton->setAutoRaise(true);
        MainWindow->setCentralWidget(centralWidget);
        Device_name_stackedWidget->raise();
        tabWidget->raise();
        Image_format_comb->raise();
        Folder_comb->raise();
        Image_format_label->raise();
        File_name_label->raise();
        Folder_label->raise();
        File_extension_label->raise();
        Configuration_toolButton->raise();
        Prefix_lineEdit->raise();
        Folder_toolButton->raise();
        Scan_Button_stackedWidget->raise();
        Image_format_colon_label->raise();
        File_name_colon_label->raise();
        Folder_colon_label->raise();
        Help_toolButton->raise();
        FileNameSetting_toolButton->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 488, 17));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QStringLiteral("menu_file"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar->addAction(menu_file->menuAction());
        menu_file->addAction(actionAboutEpsonScan2);
        menu_file->addAction(action_Exit);
        retranslateUi(MainWindow);
        QObject::connect(Brightness_spinBox, SIGNAL(valueChanged(int)), Brightness_hSlider, SLOT(setValue(int)));
        QObject::connect(Contrast_spinBox, SIGNAL(valueChanged(int)), Contrast_hSlider, SLOT(setValue(int)));
        QObject::connect(Folder_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Image_format_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Image_type_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Resolution_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Rotate_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Deskew_checkbox, SIGNAL(clicked(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(Ad_pages_checkbox, SIGNAL(clicked(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(Skip_blank_pages_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Detect_double_feed_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Prefix_lineEdit, SIGNAL(editingFinished()), MainWindow, SLOT(EditFinishText()));
        QObject::connect(Contrast_hSlider, SIGNAL(valueChanged(int)), Contrast_spinBox, SLOT(setValue(int)));
        QObject::connect(Brightness_hSlider, SIGNAL(valueChanged(int)), Brightness_spinBox, SLOT(setValue(int)));
        QObject::connect(RemoveBack_comboBox, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Dropout_comboBox, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Brightness_hSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Contrast_hSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Gamma_hSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Gamma_hSlider, SIGNAL(valueChanged(int)), Gamma_doubleSpinBox, SLOT(setGamma(int)));
        QObject::connect(Gamma_doubleSpinBox, SIGNAL(valueChanged(double)), Gamma_hSlider, SLOT(setGammaSlider(double)));
        QObject::connect(Threshold_hSlider, SIGNAL(valueChanged(int)), Threshold_spinBox, SLOT(setValue(int)));
        QObject::connect(Threshold_spinBox, SIGNAL(valueChanged(int)), Threshold_hSlider, SLOT(setValue(int)));
        QObject::connect(Threshold_hSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Configuration_toolButton, SIGNAL(clicked()), MainWindow, SLOT(onConfiguration_Button_pressed()));
        QObject::connect(Device_selector_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(RemoveBack_radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(Dropout_radioButton, SIGNAL(toggled(bool)), Dropout_comboBox, SLOT(setEnabled(bool)));
        QObject::connect(Folder_toolButton, SIGNAL(clicked()), MainWindow, SLOT(onFolder_Button_pressed()));
        QObject::connect(action_Exit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(None_radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(Dropout_radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(Document_source_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Vertical_doc_toolButton, SIGNAL(clicked(bool)), Vertical_doc_toolButton, SLOT(button_event(bool)));
        QObject::connect(Scanning_side_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Vertical_doc_toolButton, SIGNAL(clicked(bool)), Horizontal_doc_toolButton, SLOT(button_event(bool)));
        QObject::connect(Horizontal_doc_toolButton, SIGNAL(clicked(bool)), Vertical_doc_toolButton, SLOT(button_event(bool)));
        QObject::connect(Document_size_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Horizontal_doc_toolButton, SIGNAL(clicked(bool)), Horizontal_doc_toolButton, SLOT(button_event(bool)));
        QObject::connect(Save_pushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(Save_pushButton, SIGNAL(clicked()), MainWindow, SLOT(onSave_Button_pressed()));
        QObject::connect(actionAboutEpsonScan2, SIGNAL(triggered()), MainWindow, SLOT(onAbout_Epson_Scan2_pressed()));
        QObject::connect(Help_toolButton, SIGNAL(clicked()), MainWindow, SLOT(onHelp_Button_pressed()));
        QObject::connect(Automatic_feeding_mode_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Background_color_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(FileNameSetting_toolButton, SIGNAL(clicked()), MainWindow, SLOT(onFileNameSetting_Button_pressed()));
        QObject::connect(TextEnhance_radioButton, SIGNAL(toggled(bool)), MainWindow, SLOT(onValueChangedBool(bool)));
        QObject::connect(TextEnhance_Setting_pushButton, SIGNAL(pressed()), MainWindow, SLOT(onTextEnhanceSetting_Button_pressed()));
        QObject::connect(TextEnhance_comboBox, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(remove_punch_holes_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(Document_type_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        QObject::connect(edge_correction_comb, SIGNAL(activated(int)), MainWindow, SLOT(onValueChanged(int)));
        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);
        Resolution_comb->setCurrentIndex(-1);
        image_type_stackedWidget->setCurrentIndex(0);
        Device_name_stackedWidget->setCurrentIndex(0);
        Scan_Button_stackedWidget->setCurrentIndex(0);
        QMetaObject::connectSlotsByName(MainWindow);
    }
    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "COMMON_001", 0));
        actionAboutEpsonScan2->setText(QApplication::translate("MainWindow", "VERSION_001", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "MENU_007", 0));
        Horizontal_doc_toolButton->setText(QString());
        Vertical_doc_toolButton->setText(QString());
        Scanning_side_label->setText(QApplication::translate("MainWindow", "MAINSETTING_008", 0));
        Document_source_label->setText(QApplication::translate("MainWindow", "MAINSETTING_002", 0));
        Document_size_label->setText(QApplication::translate("MainWindow", "MAINSETTING_012", 0));
        Dpi_label->setText(QApplication::translate("MainWindow", "MAINSETTING_019", 0));
        Resolution_label->setText(QApplication::translate("MainWindow", "MAINSETTING_018", 0));
        Rotate_label->setText(QApplication::translate("MainWindow", "MAINSETTING_020", 0));
        Image_type_label->setText(QApplication::translate("MainWindow", "MAINSETTING_013", 0));
        Resolution_comb->setCurrentText(QString());
#ifndef QT_NO_TOOLTIP
        Deskew_checkbox->setToolTip(QApplication::translate("MainWindow", "MAINSETTING_050", 0));
#endif
        Deskew_checkbox->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_045", 0));
        Detect_double_page_label->setText(QApplication::translate("MainWindow", "CONFIG_DOC_003", 0));
        Skip_blank_pages_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_034", 0));
#ifndef QT_NO_TOOLTIP
        Detect_double_feed_comb->setToolTip(QApplication::translate("MainWindow", "MAINSETTING_053", 0));
#endif
#ifndef QT_NO_TOOLTIP
        Ad_pages_checkbox->setToolTip(QApplication::translate("MainWindow", "LINUX_MAINSETTING_002", 0));
#endif
        Ad_pages_checkbox->setText(QApplication::translate("MainWindow", "MAINSETTING_047", 0));
#ifndef QT_NO_TOOLTIP
        Skip_blank_pages_comb->setToolTip(QApplication::translate("MainWindow", "MAINSETTING_052", 0));
#endif
#ifndef QT_NO_TOOLTIP
        Background_color_comb->setToolTip(QApplication::translate("MainWindow", "MAINSETTING_069", 0));
#endif
        Background_color_label->setText(QApplication::translate("MainWindow", "MAINSETTING_068", 0));
#ifndef QT_NO_TOOLTIP
        Automatic_feeding_mode_comb->setToolTip(QApplication::translate("MainWindow", "MAINSETTING_048", 0));
#endif
        Automatic_feeding_mode_label->setText(QApplication::translate("MainWindow", "MAINSETTING_007", 0));
        Document_type_label->setText(QApplication::translate("MainWindow", "PHOTO_MAIN_007", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "MAINSETTING_001", 0));
        Image_option_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_004", 0));
#ifndef QT_NO_TOOLTIP
        RemoveBack_comboBox->setToolTip(QString());
#endif
        Threshold_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_033", 0));
#ifndef QT_NO_TOOLTIP
        Threshold_hSlider->setToolTip(QApplication::translate("MainWindow", "ADVANCEDSETTING_077", 0));
#endif
        Brightness_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_030", 0));
#ifndef QT_NO_TOOLTIP
        Brightness_hSlider->setToolTip(QApplication::translate("MainWindow", "PHOTO_ADVANCED_045", 0));
#endif
        Contrast_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_031", 0));
#ifndef QT_NO_TOOLTIP
        Contrast_hSlider->setToolTip(QApplication::translate("MainWindow", "PHOTO_ADVANCED_046", 0));
#endif
        Gamma_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_032", 0));
#ifndef QT_NO_TOOLTIP
        Gamma_hSlider->setToolTip(QApplication::translate("MainWindow", "ADVANCEDSETTING_076", 0));
#endif
        None_radioButton->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_005", 0));
#ifndef QT_NO_TOOLTIP
        Dropout_radioButton->setToolTip(QApplication::translate("MainWindow", "ADVANCEDSETTING_068", 0));
#endif
        Dropout_radioButton->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_010", 0));
#ifndef QT_NO_TOOLTIP
        RemoveBack_radioButton->setToolTip(QApplication::translate("MainWindow", "ADVANCEDSETTING_065", 0));
#endif
        RemoveBack_radioButton->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_062", 0));
#ifndef QT_NO_TOOLTIP
        TextEnhance_radioButton->setToolTip(QApplication::translate("MainWindow", "ADVANCEDSETTING_066", 0));
#endif
        TextEnhance_radioButton->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_006", 0));
        TextEnhance_Setting_pushButton->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_083", 0));
        remove_punch_holes_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_050", 0));
        edge_correction_label->setText(QApplication::translate("MainWindow", "ADVANCEDSETTING_114", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "ADVANCEDSETTING_001", 0));
        Image_format_comb->setCurrentText(QString());
        Image_format_label->setText(QApplication::translate("MainWindow", "FILESAVESETTING_001", 0));
        File_name_label->setText(QApplication::translate("MainWindow", "FILESAVESETTING_010", 0));
        Folder_label->setText(QApplication::translate("MainWindow", "FILESAVESETTING_012", 0));
        File_extension_label->setText(QApplication::translate("MainWindow", "LINUX_FILESAVESETTING_006", 0));
#ifndef QT_NO_TOOLTIP
        Configuration_toolButton->setToolTip(QApplication::translate("MainWindow", "CONFIG_001", 0));
#endif
        Configuration_toolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        Prefix_lineEdit->setToolTip(QApplication::translate("MainWindow", "FILENAMESETTING_004", 0));
#endif
        Prefix_lineEdit->setInputMask(QString());
        Device_selector_comb->setCurrentText(QString());
        device_name_label->setText(QApplication::translate("MainWindow", "COMMON_002", 0));
        Folder_toolButton->setText(QString());
        Scan_Button->setText(QApplication::translate("MainWindow", "FILESAVESETTING_018", 0));
        Preview_Button->setText(QApplication::translate("MainWindow", "FILESAVESETTING_017", 0));
        Save_pushButton->setText(QApplication::translate("MainWindow", "SAVESETTING_003", 0));
#ifndef QT_NO_TOOLTIP
        Help_toolButton->setToolTip(QApplication::translate("MainWindow", "FILESAVESETTING_021", 0));
#endif
        Help_toolButton->setText(QString());
        FileNameSetting_toolButton->setText(QString());
        menu_file->setTitle(QApplication::translate("MainWindow", "ES2U_MAIN_004", 0));
    }
};
namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}
QT_END_NAMESPACE
#endif
