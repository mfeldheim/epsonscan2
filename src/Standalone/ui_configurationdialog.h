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
//  ui_configurationdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_CONFIGURATIONDIALOG_H
#define UI_CONFIGURATIONDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "acpowercombobox.h"
#include "adfpaperprotectioncombobox.h"
#include "batterypowercombobox.h"
#include "behaviorwhendoublefeedcombobox.h"
#include "directpoweroncombobox.h"
#include "lastusedcheckbox.h"
#include "nonconnectpoweroffcombobox.h"
#include "openimgfolderafterscancheckbox.h"
#include "qualitypreviewcheckbox.h"
#include "sensorglassdirtsensitivitycombobox.h"
#include "sleeptimerspinbox.h"
#include "transferdataaftercompcheckbox.h"
#include "unitscombobox.h"
QT_BEGIN_NAMESPACE
class Ui_ConfigurationDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *information_tab;
    QLabel *Serialno_label;
    QLabel *Serialno_colon_label;
    QLabel *Serialno_value_label;
    QLabel *Firmware_version_value_label;
    QLabel *Firmware_version_colon_label;
    QLabel *Firmware_version_label;
    QWidget *general_tab;
    QLabel *Units_label;
    UnitsComboBox *Units_comboBox;
    LastUsedCheckBox *Last_Used_checkBox;
    OpenImgFolderAfterScanCheckBox *Open_Img_Folder_after_scan_checkBox;
    TransferDataAfterCompCheckBox *Transfer_data_after_comp_checkBox;
    QLabel *Doc_source_colon_label;
    QualityPreviewCheckbox *Quality_Preview_checkBox;
    QLabel *Preview_colon_label;
    QLabel *Preview_label;
    QWidget *counter_tab;
    QGroupBox *Scan_Counter_groupBox;
    QLabel *Scanner_Glass_label;
    QLabel *Scanner_Glass_cnt_label;
    QLabel *ADF_label;
    QLabel *ADF_cnt_label;
    QLabel *Single_Sided_label;
    QLabel *Single_Sided_cnt_label;
    QLabel *Double_Sided_label;
    QLabel *Double_Sided_cnt_label;
    QLabel *Carrier_Sheet_cnt_label;
    QLabel *Carrier_Sheet_label;
    QLabel *Card_Slot_label;
    QLabel *Card_Slot_cnt_label;
    QLabel *Paper_Jam_cnt_label;
    QLabel *Paper_Jam_label;
    QLabel *Double_Feed_cnt_label;
    QLabel *Double_Feed_label;
    QLabel *Scanner_Glass_colon_label;
    QLabel *ADF_colon_label;
    QLabel *Single_Sided_colon_label;
    QLabel *Double_Sided_colon_label;
    QLabel *Carrier_Sheet_colon_label;
    QLabel *Card_Slot_colon_label;
    QLabel *Paper_Jam_colon_label;
    QLabel *Double_Feed_colon_label;
    QLabel *Paper_Protection_cnt_colon_label;
    QLabel *Paper_Protection_cnt_label;
    QLabel *Paper_Protection_cnt_num_label;
    QStackedWidget *Counter_stackedWidget;
    QWidget *page;
    QGroupBox *Separation_Pad_groupBox;
    QPushButton *Reset_pushButton2;
    QLabel *Number_Of_Scans_cnt_label2;
    QLabel *Number_Of_Scans_label2;
    QLabel *Life_Cyde_label2;
    QLabel *Life_Cyde_cnt_label2;
    QLabel *Number_Of_Scans_colon_label_3;
    QLabel *Life_Cyde_colon_label_3;
    QGroupBox *Pickup_Pad_groupBox;
    QPushButton *Reset_pushButton;
    QLabel *Number_Of_Scans_cnt_label;
    QLabel *Number_Of_Scans_label;
    QLabel *Life_Cyde_label;
    QLabel *Life_Cyde_cnt_label;
    QLabel *Number_Of_Scans_colon_label_2;
    QLabel *Life_Cyde_colon_label_2;
    QWidget *page_2;
    QGroupBox *Roller_Assembly_Kit_groupBox;
    QPushButton *Counter_Reset_pushButton;
    QLabel *Number_Of_Scans_cnt_label3;
    QLabel *Number_Of_Scans_label3;
    QLabel *Number_Of_Scans_colon_label;
    QStackedWidget *Count_Alert_stackedWidget;
    QWidget *page_3;
    QLabel *Life_Cyde_cnt_label3;
    QLabel *Life_Cyde_label3;
    QLabel *Life_Cyde_colon_label;
    QWidget *page_4;
    QLabel *Count_Alert_Setting_num_label;
    QLabel *Count_Alert_Setting_num_colon_label;
    SleepTimerSpinBox *Count_Alert_Setting_num_spinBox;
    QWidget *power_saving_tab;
    QLabel *Sleep_Timer_label;
    SleepTimerSpinBox *Sleep_Timer_spinBox;
    QGroupBox *Power_Off_Timer_groupBox;
    QLabel *AC_Power_label;
    ACPowerComboBox *AC_Power_comboBox;
    BatteryPowerComboBox *Battery_Power_comboBox;
    QLabel *Battery_Power_label;
    QLabel *AC_Power_colon_label;
    QLabel *Battery_Power_colon_label;
    QLabel *Sleep_Timer_colon_label;
    QLabel *Direct_Power_On_label;
    NonConnectPowerOffCombobox *Power_Off_If_Disconnected_comboBox;
    QLabel *Power_Off_If_Disconnected_label;
    QLabel *Direct_Power_On_colon_label;
    QLabel *Power_Off_If_Disconnected_colon_label;
    DirectPowerOnCombobox *Direct_Power_On_comboBox;
    QWidget *maintenance_tab;
    QGroupBox *Regular_Cleaning_groupBox;
    QLabel *Number_of_Scans_label;
    QLabel *Count_Alert_Setting_label;
    QLabel *Number_of_Scans_colon_label;
    QLabel *Count_Alert_Setting_colon_label;
    QCheckBox *Regular_Cleaning_Alert_checkBox;
    SleepTimerSpinBox *Count_Alert_Setting_spinBox;
    QPushButton *Maintenance_Reset_pushButton;
    QLabel *Number_of_Scans_num_label;
    QWidget *scanner_setting_tab;
    QLabel *Detect_Glass_Dirt_label;
    QLabel *Detect_Glass_Dirt_colon_label;
    SensorGlassDirtSensitivityCombobox *Detect_Glass_Dirt_comboBox;
    QLabel *Paper_Protection_colon_label;
    QLabel *Paper_Protection_label;
    ADFPaperProtectionCombobox *Paper_Protection_comboBox;
    QLabel *Double_Feed_Stop_Timing_label;
    BehaviorWhenDoubleFeedCombobox *Double_Feed_Stop_Timing_comboBox;
    QLabel *Double_Feed_Stop_Timing_colon_label;
    QWidget *other_tab;
    QPushButton *Other_Reset_pushButton;
    QLabel *Reset_label;
    QLabel *Reset_colon_label;
    QPushButton *Close_pushButton;
    QPushButton *Unlock_pushButton;
    void setupUi(QDialog *ConfigurationDialog)
    {
        if (ConfigurationDialog->objectName().isEmpty())
            ConfigurationDialog->setObjectName(QStringLiteral("ConfigurationDialog"));
        ConfigurationDialog->setEnabled(true);
        ConfigurationDialog->resize(585, 480);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ConfigurationDialog->setWindowIcon(icon);
        tabWidget = new QTabWidget(ConfigurationDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 561, 421));
        information_tab = new QWidget();
        information_tab->setObjectName(QStringLiteral("information_tab"));
        Serialno_label = new QLabel(information_tab);
        Serialno_label->setObjectName(QStringLiteral("Serialno_label"));
        Serialno_label->setGeometry(QRect(60, 78, 211, 23));
        Serialno_colon_label = new QLabel(information_tab);
        Serialno_colon_label->setObjectName(QStringLiteral("Serialno_colon_label"));
        Serialno_colon_label->setEnabled(true);
        Serialno_colon_label->setGeometry(QRect(280, 80, 16, 20));
#ifndef QT_NO_TOOLTIP
        Serialno_colon_label->setToolTip(QStringLiteral(""));
#endif
        Serialno_colon_label->setText(QStringLiteral(":"));
        Serialno_value_label = new QLabel(information_tab);
        Serialno_value_label->setObjectName(QStringLiteral("Serialno_value_label"));
        Serialno_value_label->setGeometry(QRect(300, 77, 221, 23));
        Firmware_version_value_label = new QLabel(information_tab);
        Firmware_version_value_label->setObjectName(QStringLiteral("Firmware_version_value_label"));
        Firmware_version_value_label->setGeometry(QRect(300, 107, 221, 23));
        Firmware_version_colon_label = new QLabel(information_tab);
        Firmware_version_colon_label->setObjectName(QStringLiteral("Firmware_version_colon_label"));
        Firmware_version_colon_label->setEnabled(true);
        Firmware_version_colon_label->setGeometry(QRect(280, 110, 16, 20));
#ifndef QT_NO_TOOLTIP
        Firmware_version_colon_label->setToolTip(QStringLiteral(""));
#endif
        Firmware_version_colon_label->setText(QStringLiteral(":"));
        Firmware_version_label = new QLabel(information_tab);
        Firmware_version_label->setObjectName(QStringLiteral("Firmware_version_label"));
        Firmware_version_label->setGeometry(QRect(60, 108, 211, 23));
        tabWidget->addTab(information_tab, QString());
        general_tab = new QWidget();
        general_tab->setObjectName(QStringLiteral("general_tab"));
        Units_label = new QLabel(general_tab);
        Units_label->setObjectName(QStringLiteral("Units_label"));
        Units_label->setGeometry(QRect(20, 30, 141, 23));
        Units_comboBox = new UnitsComboBox(general_tab);
        Units_comboBox->setObjectName(QStringLiteral("Units_comboBox"));
        Units_comboBox->setGeometry(QRect(170, 29, 211, 23));
        Last_Used_checkBox = new LastUsedCheckBox(general_tab);
        Last_Used_checkBox->setObjectName(QStringLiteral("Last_Used_checkBox"));
        Last_Used_checkBox->setGeometry(QRect(170, 60, 381, 23));
        Open_Img_Folder_after_scan_checkBox = new OpenImgFolderAfterScanCheckBox(general_tab);
        Open_Img_Folder_after_scan_checkBox->setObjectName(QStringLiteral("Open_Img_Folder_after_scan_checkBox"));
        Open_Img_Folder_after_scan_checkBox->setGeometry(QRect(170, 90, 381, 23));
        Transfer_data_after_comp_checkBox = new TransferDataAfterCompCheckBox(general_tab);
        Transfer_data_after_comp_checkBox->setObjectName(QStringLiteral("Transfer_data_after_comp_checkBox"));
        Transfer_data_after_comp_checkBox->setGeometry(QRect(170, 120, 381, 23));
        Doc_source_colon_label = new QLabel(general_tab);
        Doc_source_colon_label->setObjectName(QStringLiteral("Doc_source_colon_label"));
        Doc_source_colon_label->setEnabled(true);
        Doc_source_colon_label->setGeometry(QRect(160, 32, 16, 20));
#ifndef QT_NO_TOOLTIP
        Doc_source_colon_label->setToolTip(QStringLiteral(""));
#endif
        Doc_source_colon_label->setText(QStringLiteral(":"));
        Quality_Preview_checkBox = new QualityPreviewCheckbox(general_tab);
        Quality_Preview_checkBox->setObjectName(QStringLiteral("Quality_Preview_checkBox"));
        Quality_Preview_checkBox->setGeometry(QRect(170, 151, 381, 23));
        Preview_colon_label = new QLabel(general_tab);
        Preview_colon_label->setObjectName(QStringLiteral("Preview_colon_label"));
        Preview_colon_label->setEnabled(true);
        Preview_colon_label->setGeometry(QRect(160, 152, 16, 20));
#ifndef QT_NO_TOOLTIP
        Preview_colon_label->setToolTip(QStringLiteral(""));
#endif
        Preview_colon_label->setText(QStringLiteral(":"));
        Preview_label = new QLabel(general_tab);
        Preview_label->setObjectName(QStringLiteral("Preview_label"));
        Preview_label->setGeometry(QRect(20, 150, 141, 23));
        tabWidget->addTab(general_tab, QString());
        counter_tab = new QWidget();
        counter_tab->setObjectName(QStringLiteral("counter_tab"));
        Scan_Counter_groupBox = new QGroupBox(counter_tab);
        Scan_Counter_groupBox->setObjectName(QStringLiteral("Scan_Counter_groupBox"));
        Scan_Counter_groupBox->setGeometry(QRect(10, 5, 531, 201));
        Scanner_Glass_label = new QLabel(Scan_Counter_groupBox);
        Scanner_Glass_label->setObjectName(QStringLiteral("Scanner_Glass_label"));
        Scanner_Glass_label->setGeometry(QRect(10, 23, 181, 23));
        Scanner_Glass_cnt_label = new QLabel(Scan_Counter_groupBox);
        Scanner_Glass_cnt_label->setObjectName(QStringLiteral("Scanner_Glass_cnt_label"));
        Scanner_Glass_cnt_label->setGeometry(QRect(230, 23, 221, 23));
        ADF_label = new QLabel(Scan_Counter_groupBox);
        ADF_label->setObjectName(QStringLiteral("ADF_label"));
        ADF_label->setGeometry(QRect(10, 42, 181, 23));
        ADF_cnt_label = new QLabel(Scan_Counter_groupBox);
        ADF_cnt_label->setObjectName(QStringLiteral("ADF_cnt_label"));
        ADF_cnt_label->setGeometry(QRect(230, 42, 221, 23));
        Single_Sided_label = new QLabel(Scan_Counter_groupBox);
        Single_Sided_label->setObjectName(QStringLiteral("Single_Sided_label"));
        Single_Sided_label->setGeometry(QRect(10, 61, 181, 23));
        Single_Sided_cnt_label = new QLabel(Scan_Counter_groupBox);
        Single_Sided_cnt_label->setObjectName(QStringLiteral("Single_Sided_cnt_label"));
        Single_Sided_cnt_label->setGeometry(QRect(230, 61, 221, 23));
        Double_Sided_label = new QLabel(Scan_Counter_groupBox);
        Double_Sided_label->setObjectName(QStringLiteral("Double_Sided_label"));
        Double_Sided_label->setGeometry(QRect(10, 81, 181, 23));
        Double_Sided_cnt_label = new QLabel(Scan_Counter_groupBox);
        Double_Sided_cnt_label->setObjectName(QStringLiteral("Double_Sided_cnt_label"));
        Double_Sided_cnt_label->setGeometry(QRect(230, 81, 221, 23));
        Carrier_Sheet_cnt_label = new QLabel(Scan_Counter_groupBox);
        Carrier_Sheet_cnt_label->setObjectName(QStringLiteral("Carrier_Sheet_cnt_label"));
        Carrier_Sheet_cnt_label->setGeometry(QRect(230, 100, 221, 23));
        Carrier_Sheet_label = new QLabel(Scan_Counter_groupBox);
        Carrier_Sheet_label->setObjectName(QStringLiteral("Carrier_Sheet_label"));
        Carrier_Sheet_label->setGeometry(QRect(10, 102, 181, 23));
        Card_Slot_label = new QLabel(Scan_Counter_groupBox);
        Card_Slot_label->setObjectName(QStringLiteral("Card_Slot_label"));
        Card_Slot_label->setGeometry(QRect(10, 119, 181, 23));
        Card_Slot_cnt_label = new QLabel(Scan_Counter_groupBox);
        Card_Slot_cnt_label->setObjectName(QStringLiteral("Card_Slot_cnt_label"));
        Card_Slot_cnt_label->setGeometry(QRect(230, 119, 221, 23));
        Paper_Jam_cnt_label = new QLabel(Scan_Counter_groupBox);
        Paper_Jam_cnt_label->setObjectName(QStringLiteral("Paper_Jam_cnt_label"));
        Paper_Jam_cnt_label->setGeometry(QRect(230, 139, 221, 23));
        Paper_Jam_label = new QLabel(Scan_Counter_groupBox);
        Paper_Jam_label->setObjectName(QStringLiteral("Paper_Jam_label"));
        Paper_Jam_label->setGeometry(QRect(10, 139, 181, 23));
        Double_Feed_cnt_label = new QLabel(Scan_Counter_groupBox);
        Double_Feed_cnt_label->setObjectName(QStringLiteral("Double_Feed_cnt_label"));
        Double_Feed_cnt_label->setGeometry(QRect(230, 159, 221, 23));
        Double_Feed_label = new QLabel(Scan_Counter_groupBox);
        Double_Feed_label->setObjectName(QStringLiteral("Double_Feed_label"));
        Double_Feed_label->setGeometry(QRect(10, 160, 181, 23));
        Scanner_Glass_colon_label = new QLabel(Scan_Counter_groupBox);
        Scanner_Glass_colon_label->setObjectName(QStringLiteral("Scanner_Glass_colon_label"));
        Scanner_Glass_colon_label->setEnabled(true);
        Scanner_Glass_colon_label->setGeometry(QRect(210, 25, 16, 20));
#ifndef QT_NO_TOOLTIP
        Scanner_Glass_colon_label->setToolTip(QStringLiteral(""));
#endif
        Scanner_Glass_colon_label->setText(QStringLiteral(":"));
        ADF_colon_label = new QLabel(Scan_Counter_groupBox);
        ADF_colon_label->setObjectName(QStringLiteral("ADF_colon_label"));
        ADF_colon_label->setEnabled(true);
        ADF_colon_label->setGeometry(QRect(210, 44, 16, 20));
#ifndef QT_NO_TOOLTIP
        ADF_colon_label->setToolTip(QStringLiteral(""));
#endif
        ADF_colon_label->setText(QStringLiteral(":"));
        Single_Sided_colon_label = new QLabel(Scan_Counter_groupBox);
        Single_Sided_colon_label->setObjectName(QStringLiteral("Single_Sided_colon_label"));
        Single_Sided_colon_label->setEnabled(true);
        Single_Sided_colon_label->setGeometry(QRect(210, 63, 16, 20));
#ifndef QT_NO_TOOLTIP
        Single_Sided_colon_label->setToolTip(QStringLiteral(""));
#endif
        Single_Sided_colon_label->setText(QStringLiteral(":"));
        Double_Sided_colon_label = new QLabel(Scan_Counter_groupBox);
        Double_Sided_colon_label->setObjectName(QStringLiteral("Double_Sided_colon_label"));
        Double_Sided_colon_label->setEnabled(true);
        Double_Sided_colon_label->setGeometry(QRect(210, 83, 16, 20));
#ifndef QT_NO_TOOLTIP
        Double_Sided_colon_label->setToolTip(QStringLiteral(""));
#endif
        Double_Sided_colon_label->setText(QStringLiteral(":"));
        Carrier_Sheet_colon_label = new QLabel(Scan_Counter_groupBox);
        Carrier_Sheet_colon_label->setObjectName(QStringLiteral("Carrier_Sheet_colon_label"));
        Carrier_Sheet_colon_label->setEnabled(true);
        Carrier_Sheet_colon_label->setGeometry(QRect(210, 102, 16, 20));
#ifndef QT_NO_TOOLTIP
        Carrier_Sheet_colon_label->setToolTip(QStringLiteral(""));
#endif
        Carrier_Sheet_colon_label->setText(QStringLiteral(":"));
        Card_Slot_colon_label = new QLabel(Scan_Counter_groupBox);
        Card_Slot_colon_label->setObjectName(QStringLiteral("Card_Slot_colon_label"));
        Card_Slot_colon_label->setEnabled(true);
        Card_Slot_colon_label->setGeometry(QRect(210, 121, 16, 20));
#ifndef QT_NO_TOOLTIP
        Card_Slot_colon_label->setToolTip(QStringLiteral(""));
#endif
        Card_Slot_colon_label->setText(QStringLiteral(":"));
        Paper_Jam_colon_label = new QLabel(Scan_Counter_groupBox);
        Paper_Jam_colon_label->setObjectName(QStringLiteral("Paper_Jam_colon_label"));
        Paper_Jam_colon_label->setEnabled(true);
        Paper_Jam_colon_label->setGeometry(QRect(210, 141, 16, 20));
#ifndef QT_NO_TOOLTIP
        Paper_Jam_colon_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Jam_colon_label->setText(QStringLiteral(":"));
        Double_Feed_colon_label = new QLabel(Scan_Counter_groupBox);
        Double_Feed_colon_label->setObjectName(QStringLiteral("Double_Feed_colon_label"));
        Double_Feed_colon_label->setEnabled(true);
        Double_Feed_colon_label->setGeometry(QRect(210, 162, 16, 20));
#ifndef QT_NO_TOOLTIP
        Double_Feed_colon_label->setToolTip(QStringLiteral(""));
#endif
        Double_Feed_colon_label->setText(QStringLiteral(":"));
        Paper_Protection_cnt_colon_label = new QLabel(Scan_Counter_groupBox);
        Paper_Protection_cnt_colon_label->setObjectName(QStringLiteral("Paper_Protection_cnt_colon_label"));
        Paper_Protection_cnt_colon_label->setEnabled(true);
        Paper_Protection_cnt_colon_label->setGeometry(QRect(210, 181, 16, 20));
#ifndef QT_NO_TOOLTIP
        Paper_Protection_cnt_colon_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Protection_cnt_colon_label->setText(QStringLiteral(":"));
        Paper_Protection_cnt_label = new QLabel(Scan_Counter_groupBox);
        Paper_Protection_cnt_label->setObjectName(QStringLiteral("Paper_Protection_cnt_label"));
        Paper_Protection_cnt_label->setGeometry(QRect(10, 179, 181, 23));
        Paper_Protection_cnt_num_label = new QLabel(Scan_Counter_groupBox);
        Paper_Protection_cnt_num_label->setObjectName(QStringLiteral("Paper_Protection_cnt_num_label"));
        Paper_Protection_cnt_num_label->setGeometry(QRect(230, 178, 221, 23));
        Counter_stackedWidget = new QStackedWidget(counter_tab);
        Counter_stackedWidget->setObjectName(QStringLiteral("Counter_stackedWidget"));
        Counter_stackedWidget->setGeometry(QRect(0, 212, 551, 181));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        Separation_Pad_groupBox = new QGroupBox(page);
        Separation_Pad_groupBox->setObjectName(QStringLiteral("Separation_Pad_groupBox"));
        Separation_Pad_groupBox->setGeometry(QRect(10, 85, 511, 81));
        Reset_pushButton2 = new QPushButton(Separation_Pad_groupBox);
        Reset_pushButton2->setObjectName(QStringLiteral("Reset_pushButton2"));
        Reset_pushButton2->setGeometry(QRect(390, 25, 101, 25));
        Number_Of_Scans_cnt_label2 = new QLabel(Separation_Pad_groupBox);
        Number_Of_Scans_cnt_label2->setObjectName(QStringLiteral("Number_Of_Scans_cnt_label2"));
        Number_Of_Scans_cnt_label2->setGeometry(QRect(210, 29, 181, 23));
        Number_Of_Scans_label2 = new QLabel(Separation_Pad_groupBox);
        Number_Of_Scans_label2->setObjectName(QStringLiteral("Number_Of_Scans_label2"));
        Number_Of_Scans_label2->setGeometry(QRect(10, 26, 181, 23));
        Number_Of_Scans_label2->setWordWrap(true);
        Life_Cyde_label2 = new QLabel(Separation_Pad_groupBox);
        Life_Cyde_label2->setObjectName(QStringLiteral("Life_Cyde_label2"));
        Life_Cyde_label2->setGeometry(QRect(10, 50, 181, 23));
        Life_Cyde_cnt_label2 = new QLabel(Separation_Pad_groupBox);
        Life_Cyde_cnt_label2->setObjectName(QStringLiteral("Life_Cyde_cnt_label2"));
        Life_Cyde_cnt_label2->setGeometry(QRect(210, 52, 181, 23));
        Number_Of_Scans_colon_label_3 = new QLabel(Separation_Pad_groupBox);
        Number_Of_Scans_colon_label_3->setObjectName(QStringLiteral("Number_Of_Scans_colon_label_3"));
        Number_Of_Scans_colon_label_3->setEnabled(true);
        Number_Of_Scans_colon_label_3->setGeometry(QRect(190, 29, 16, 20));
#ifndef QT_NO_TOOLTIP
        Number_Of_Scans_colon_label_3->setToolTip(QStringLiteral(""));
#endif
        Number_Of_Scans_colon_label_3->setText(QStringLiteral(":"));
        Life_Cyde_colon_label_3 = new QLabel(Separation_Pad_groupBox);
        Life_Cyde_colon_label_3->setObjectName(QStringLiteral("Life_Cyde_colon_label_3"));
        Life_Cyde_colon_label_3->setEnabled(true);
        Life_Cyde_colon_label_3->setGeometry(QRect(190, 52, 16, 16));
#ifndef QT_NO_TOOLTIP
        Life_Cyde_colon_label_3->setToolTip(QStringLiteral(""));
#endif
        Life_Cyde_colon_label_3->setText(QStringLiteral(":"));
        Pickup_Pad_groupBox = new QGroupBox(page);
        Pickup_Pad_groupBox->setObjectName(QStringLiteral("Pickup_Pad_groupBox"));
        Pickup_Pad_groupBox->setGeometry(QRect(10, 1, 511, 81));
        Reset_pushButton = new QPushButton(Pickup_Pad_groupBox);
        Reset_pushButton->setObjectName(QStringLiteral("Reset_pushButton"));
        Reset_pushButton->setGeometry(QRect(390, 26, 101, 25));
        Number_Of_Scans_cnt_label = new QLabel(Pickup_Pad_groupBox);
        Number_Of_Scans_cnt_label->setObjectName(QStringLiteral("Number_Of_Scans_cnt_label"));
        Number_Of_Scans_cnt_label->setGeometry(QRect(210, 30, 181, 23));
        Number_Of_Scans_label = new QLabel(Pickup_Pad_groupBox);
        Number_Of_Scans_label->setObjectName(QStringLiteral("Number_Of_Scans_label"));
        Number_Of_Scans_label->setGeometry(QRect(10, 27, 181, 23));
        Number_Of_Scans_label->setWordWrap(true);
        Life_Cyde_label = new QLabel(Pickup_Pad_groupBox);
        Life_Cyde_label->setObjectName(QStringLiteral("Life_Cyde_label"));
        Life_Cyde_label->setGeometry(QRect(10, 50, 181, 23));
        Life_Cyde_cnt_label = new QLabel(Pickup_Pad_groupBox);
        Life_Cyde_cnt_label->setObjectName(QStringLiteral("Life_Cyde_cnt_label"));
        Life_Cyde_cnt_label->setGeometry(QRect(210, 53, 181, 23));
        Number_Of_Scans_colon_label_2 = new QLabel(Pickup_Pad_groupBox);
        Number_Of_Scans_colon_label_2->setObjectName(QStringLiteral("Number_Of_Scans_colon_label_2"));
        Number_Of_Scans_colon_label_2->setEnabled(true);
        Number_Of_Scans_colon_label_2->setGeometry(QRect(190, 29, 16, 20));
#ifndef QT_NO_TOOLTIP
        Number_Of_Scans_colon_label_2->setToolTip(QStringLiteral(""));
#endif
        Number_Of_Scans_colon_label_2->setText(QStringLiteral(":"));
        Life_Cyde_colon_label_2 = new QLabel(Pickup_Pad_groupBox);
        Life_Cyde_colon_label_2->setObjectName(QStringLiteral("Life_Cyde_colon_label_2"));
        Life_Cyde_colon_label_2->setEnabled(true);
        Life_Cyde_colon_label_2->setGeometry(QRect(190, 52, 16, 20));
#ifndef QT_NO_TOOLTIP
        Life_Cyde_colon_label_2->setToolTip(QStringLiteral(""));
#endif
        Life_Cyde_colon_label_2->setText(QStringLiteral(":"));
        Counter_stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        Roller_Assembly_Kit_groupBox = new QGroupBox(page_2);
        Roller_Assembly_Kit_groupBox->setObjectName(QStringLiteral("Roller_Assembly_Kit_groupBox"));
        Roller_Assembly_Kit_groupBox->setGeometry(QRect(10, 1, 511, 81));
        Counter_Reset_pushButton = new QPushButton(Roller_Assembly_Kit_groupBox);
        Counter_Reset_pushButton->setObjectName(QStringLiteral("Counter_Reset_pushButton"));
        Counter_Reset_pushButton->setGeometry(QRect(390, 25, 101, 25));
        Number_Of_Scans_cnt_label3 = new QLabel(Roller_Assembly_Kit_groupBox);
        Number_Of_Scans_cnt_label3->setObjectName(QStringLiteral("Number_Of_Scans_cnt_label3"));
        Number_Of_Scans_cnt_label3->setGeometry(QRect(210, 27, 181, 23));
        Number_Of_Scans_label3 = new QLabel(Roller_Assembly_Kit_groupBox);
        Number_Of_Scans_label3->setObjectName(QStringLiteral("Number_Of_Scans_label3"));
        Number_Of_Scans_label3->setGeometry(QRect(10, 27, 181, 23));
        Number_Of_Scans_colon_label = new QLabel(Roller_Assembly_Kit_groupBox);
        Number_Of_Scans_colon_label->setObjectName(QStringLiteral("Number_Of_Scans_colon_label"));
        Number_Of_Scans_colon_label->setEnabled(true);
        Number_Of_Scans_colon_label->setGeometry(QRect(190, 29, 16, 20));
#ifndef QT_NO_TOOLTIP
        Number_Of_Scans_colon_label->setToolTip(QStringLiteral(""));
#endif
        Number_Of_Scans_colon_label->setText(QStringLiteral(":"));
        Count_Alert_stackedWidget = new QStackedWidget(Roller_Assembly_Kit_groupBox);
        Count_Alert_stackedWidget->setObjectName(QStringLiteral("Count_Alert_stackedWidget"));
        Count_Alert_stackedWidget->setGeometry(QRect(0, 50, 491, 21));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        Life_Cyde_cnt_label3 = new QLabel(page_3);
        Life_Cyde_cnt_label3->setObjectName(QStringLiteral("Life_Cyde_cnt_label3"));
        Life_Cyde_cnt_label3->setGeometry(QRect(210, 0, 181, 23));
        Life_Cyde_label3 = new QLabel(page_3);
        Life_Cyde_label3->setObjectName(QStringLiteral("Life_Cyde_label3"));
        Life_Cyde_label3->setGeometry(QRect(10, 0, 181, 23));
        Life_Cyde_colon_label = new QLabel(page_3);
        Life_Cyde_colon_label->setObjectName(QStringLiteral("Life_Cyde_colon_label"));
        Life_Cyde_colon_label->setEnabled(true);
        Life_Cyde_colon_label->setGeometry(QRect(190, 2, 16, 20));
#ifndef QT_NO_TOOLTIP
        Life_Cyde_colon_label->setToolTip(QStringLiteral(""));
#endif
        Life_Cyde_colon_label->setText(QStringLiteral(":"));
        Count_Alert_stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        Count_Alert_Setting_num_label = new QLabel(page_4);
        Count_Alert_Setting_num_label->setObjectName(QStringLiteral("Count_Alert_Setting_num_label"));
        Count_Alert_Setting_num_label->setGeometry(QRect(10, 0, 181, 23));
        Count_Alert_Setting_num_colon_label = new QLabel(page_4);
        Count_Alert_Setting_num_colon_label->setObjectName(QStringLiteral("Count_Alert_Setting_num_colon_label"));
        Count_Alert_Setting_num_colon_label->setEnabled(true);
        Count_Alert_Setting_num_colon_label->setGeometry(QRect(190, 2, 16, 20));
#ifndef QT_NO_TOOLTIP
        Count_Alert_Setting_num_colon_label->setToolTip(QStringLiteral(""));
#endif
        Count_Alert_Setting_num_colon_label->setText(QStringLiteral(":"));
        Count_Alert_Setting_num_spinBox = new SleepTimerSpinBox(page_4);
        Count_Alert_Setting_num_spinBox->setObjectName(QStringLiteral("Count_Alert_Setting_num_spinBox"));
        Count_Alert_Setting_num_spinBox->setGeometry(QRect(210, 0, 121, 23));
        Count_Alert_Setting_num_spinBox->setFocusPolicy(Qt::NoFocus);
        Count_Alert_Setting_num_spinBox->setReadOnly(false);
        Count_Alert_Setting_num_spinBox->setMaximum(200000);
        Count_Alert_Setting_num_spinBox->setSingleStep(1000);
        Count_Alert_stackedWidget->addWidget(page_4);
        Counter_stackedWidget->addWidget(page_2);
        tabWidget->addTab(counter_tab, QString());
        power_saving_tab = new QWidget();
        power_saving_tab->setObjectName(QStringLiteral("power_saving_tab"));
        Sleep_Timer_label = new QLabel(power_saving_tab);
        Sleep_Timer_label->setObjectName(QStringLiteral("Sleep_Timer_label"));
        Sleep_Timer_label->setGeometry(QRect(100, 34, 221, 23));
        Sleep_Timer_spinBox = new SleepTimerSpinBox(power_saving_tab);
        Sleep_Timer_spinBox->setObjectName(QStringLiteral("Sleep_Timer_spinBox"));
        Sleep_Timer_spinBox->setGeometry(QRect(340, 33, 121, 23));
        Power_Off_Timer_groupBox = new QGroupBox(power_saving_tab);
        Power_Off_Timer_groupBox->setObjectName(QStringLiteral("Power_Off_Timer_groupBox"));
        Power_Off_Timer_groupBox->setGeometry(QRect(46, 70, 461, 91));
        AC_Power_label = new QLabel(Power_Off_Timer_groupBox);
        AC_Power_label->setObjectName(QStringLiteral("AC_Power_label"));
        AC_Power_label->setGeometry(QRect(18, 30, 241, 23));
        AC_Power_comboBox = new ACPowerComboBox(Power_Off_Timer_groupBox);
        AC_Power_comboBox->setObjectName(QStringLiteral("AC_Power_comboBox"));
        AC_Power_comboBox->setGeometry(QRect(290, 28, 131, 23));
        Battery_Power_comboBox = new BatteryPowerComboBox(Power_Off_Timer_groupBox);
        Battery_Power_comboBox->setObjectName(QStringLiteral("Battery_Power_comboBox"));
        Battery_Power_comboBox->setGeometry(QRect(290, 60, 131, 23));
        Battery_Power_label = new QLabel(Power_Off_Timer_groupBox);
        Battery_Power_label->setObjectName(QStringLiteral("Battery_Power_label"));
        Battery_Power_label->setGeometry(QRect(18, 60, 241, 23));
        AC_Power_colon_label = new QLabel(Power_Off_Timer_groupBox);
        AC_Power_colon_label->setObjectName(QStringLiteral("AC_Power_colon_label"));
        AC_Power_colon_label->setEnabled(true);
        AC_Power_colon_label->setGeometry(QRect(270, 31, 16, 20));
#ifndef QT_NO_TOOLTIP
        AC_Power_colon_label->setToolTip(QStringLiteral(""));
#endif
        AC_Power_colon_label->setText(QStringLiteral(":"));
        Battery_Power_colon_label = new QLabel(Power_Off_Timer_groupBox);
        Battery_Power_colon_label->setObjectName(QStringLiteral("Battery_Power_colon_label"));
        Battery_Power_colon_label->setEnabled(true);
        Battery_Power_colon_label->setGeometry(QRect(270, 63, 16, 20));
#ifndef QT_NO_TOOLTIP
        Battery_Power_colon_label->setToolTip(QStringLiteral(""));
#endif
        Battery_Power_colon_label->setText(QStringLiteral(":"));
        Sleep_Timer_colon_label = new QLabel(power_saving_tab);
        Sleep_Timer_colon_label->setObjectName(QStringLiteral("Sleep_Timer_colon_label"));
        Sleep_Timer_colon_label->setEnabled(true);
        Sleep_Timer_colon_label->setGeometry(QRect(330, 36, 16, 20));
#ifndef QT_NO_TOOLTIP
        Sleep_Timer_colon_label->setToolTip(QStringLiteral(""));
#endif
        Sleep_Timer_colon_label->setText(QStringLiteral(":"));
        Direct_Power_On_label = new QLabel(power_saving_tab);
        Direct_Power_On_label->setObjectName(QStringLiteral("Direct_Power_On_label"));
        Direct_Power_On_label->setGeometry(QRect(64, 220, 241, 23));
        Power_Off_If_Disconnected_comboBox = new NonConnectPowerOffCombobox(power_saving_tab);
        Power_Off_If_Disconnected_comboBox->setObjectName(QStringLiteral("Power_Off_If_Disconnected_comboBox"));
        Power_Off_If_Disconnected_comboBox->setGeometry(QRect(336, 188, 131, 23));
        Power_Off_If_Disconnected_label = new QLabel(power_saving_tab);
        Power_Off_If_Disconnected_label->setObjectName(QStringLiteral("Power_Off_If_Disconnected_label"));
        Power_Off_If_Disconnected_label->setGeometry(QRect(64, 190, 241, 23));
        Direct_Power_On_colon_label = new QLabel(power_saving_tab);
        Direct_Power_On_colon_label->setObjectName(QStringLiteral("Direct_Power_On_colon_label"));
        Direct_Power_On_colon_label->setEnabled(true);
        Direct_Power_On_colon_label->setGeometry(QRect(316, 223, 16, 20));
#ifndef QT_NO_TOOLTIP
        Direct_Power_On_colon_label->setToolTip(QStringLiteral(""));
#endif
        Direct_Power_On_colon_label->setText(QStringLiteral(":"));
        Power_Off_If_Disconnected_colon_label = new QLabel(power_saving_tab);
        Power_Off_If_Disconnected_colon_label->setObjectName(QStringLiteral("Power_Off_If_Disconnected_colon_label"));
        Power_Off_If_Disconnected_colon_label->setEnabled(true);
        Power_Off_If_Disconnected_colon_label->setGeometry(QRect(316, 191, 16, 20));
#ifndef QT_NO_TOOLTIP
        Power_Off_If_Disconnected_colon_label->setToolTip(QStringLiteral(""));
#endif
        Power_Off_If_Disconnected_colon_label->setText(QStringLiteral(":"));
        Direct_Power_On_comboBox = new DirectPowerOnCombobox(power_saving_tab);
        Direct_Power_On_comboBox->setObjectName(QStringLiteral("Direct_Power_On_comboBox"));
        Direct_Power_On_comboBox->setGeometry(QRect(336, 220, 131, 25));
        tabWidget->addTab(power_saving_tab, QString());
        maintenance_tab = new QWidget();
        maintenance_tab->setObjectName(QStringLiteral("maintenance_tab"));
        Regular_Cleaning_groupBox = new QGroupBox(maintenance_tab);
        Regular_Cleaning_groupBox->setObjectName(QStringLiteral("Regular_Cleaning_groupBox"));
        Regular_Cleaning_groupBox->setGeometry(QRect(50, 20, 461, 121));
        Number_of_Scans_label = new QLabel(Regular_Cleaning_groupBox);
        Number_of_Scans_label->setObjectName(QStringLiteral("Number_of_Scans_label"));
        Number_of_Scans_label->setEnabled(false);
        Number_of_Scans_label->setGeometry(QRect(18, 62, 211, 23));
        Count_Alert_Setting_label = new QLabel(Regular_Cleaning_groupBox);
        Count_Alert_Setting_label->setObjectName(QStringLiteral("Count_Alert_Setting_label"));
        Count_Alert_Setting_label->setEnabled(false);
        Count_Alert_Setting_label->setGeometry(QRect(18, 92, 211, 23));
        Number_of_Scans_colon_label = new QLabel(Regular_Cleaning_groupBox);
        Number_of_Scans_colon_label->setObjectName(QStringLiteral("Number_of_Scans_colon_label"));
        Number_of_Scans_colon_label->setEnabled(false);
        Number_of_Scans_colon_label->setGeometry(QRect(230, 63, 16, 20));
#ifndef QT_NO_TOOLTIP
        Number_of_Scans_colon_label->setToolTip(QStringLiteral(""));
#endif
        Number_of_Scans_colon_label->setText(QStringLiteral(":"));
        Count_Alert_Setting_colon_label = new QLabel(Regular_Cleaning_groupBox);
        Count_Alert_Setting_colon_label->setObjectName(QStringLiteral("Count_Alert_Setting_colon_label"));
        Count_Alert_Setting_colon_label->setEnabled(false);
        Count_Alert_Setting_colon_label->setGeometry(QRect(230, 95, 16, 20));
#ifndef QT_NO_TOOLTIP
        Count_Alert_Setting_colon_label->setToolTip(QStringLiteral(""));
#endif
        Count_Alert_Setting_colon_label->setText(QStringLiteral(":"));
        Regular_Cleaning_Alert_checkBox = new QCheckBox(Regular_Cleaning_groupBox);
        Regular_Cleaning_Alert_checkBox->setObjectName(QStringLiteral("Regular_Cleaning_Alert_checkBox"));
        Regular_Cleaning_Alert_checkBox->setGeometry(QRect(20, 30, 381, 23));
        Count_Alert_Setting_spinBox = new SleepTimerSpinBox(Regular_Cleaning_groupBox);
        Count_Alert_Setting_spinBox->setObjectName(QStringLiteral("Count_Alert_Setting_spinBox"));
        Count_Alert_Setting_spinBox->setEnabled(false);
        Count_Alert_Setting_spinBox->setGeometry(QRect(250, 90, 201, 23));
        Count_Alert_Setting_spinBox->setFocusPolicy(Qt::NoFocus);
        Count_Alert_Setting_spinBox->setMaximum(200000);
        Count_Alert_Setting_spinBox->setSingleStep(1000);
        Maintenance_Reset_pushButton = new QPushButton(Regular_Cleaning_groupBox);
        Maintenance_Reset_pushButton->setObjectName(QStringLiteral("Maintenance_Reset_pushButton"));
        Maintenance_Reset_pushButton->setEnabled(false);
        Maintenance_Reset_pushButton->setGeometry(QRect(370, 58, 81, 25));
        Number_of_Scans_num_label = new QLabel(Regular_Cleaning_groupBox);
        Number_of_Scans_num_label->setObjectName(QStringLiteral("Number_of_Scans_num_label"));
        Number_of_Scans_num_label->setEnabled(false);
        Number_of_Scans_num_label->setGeometry(QRect(250, 60, 111, 23));
        tabWidget->addTab(maintenance_tab, QString());
        scanner_setting_tab = new QWidget();
        scanner_setting_tab->setObjectName(QStringLiteral("scanner_setting_tab"));
        Detect_Glass_Dirt_label = new QLabel(scanner_setting_tab);
        Detect_Glass_Dirt_label->setObjectName(QStringLiteral("Detect_Glass_Dirt_label"));
        Detect_Glass_Dirt_label->setGeometry(QRect(110, 40, 241, 23));
        Detect_Glass_Dirt_colon_label = new QLabel(scanner_setting_tab);
        Detect_Glass_Dirt_colon_label->setObjectName(QStringLiteral("Detect_Glass_Dirt_colon_label"));
        Detect_Glass_Dirt_colon_label->setEnabled(true);
        Detect_Glass_Dirt_colon_label->setGeometry(QRect(362, 41, 16, 20));
#ifndef QT_NO_TOOLTIP
        Detect_Glass_Dirt_colon_label->setToolTip(QStringLiteral(""));
#endif
        Detect_Glass_Dirt_colon_label->setText(QStringLiteral(":"));
        Detect_Glass_Dirt_comboBox = new SensorGlassDirtSensitivityCombobox(scanner_setting_tab);
        Detect_Glass_Dirt_comboBox->setObjectName(QStringLiteral("Detect_Glass_Dirt_comboBox"));
        Detect_Glass_Dirt_comboBox->setGeometry(QRect(382, 38, 131, 23));
        Paper_Protection_colon_label = new QLabel(scanner_setting_tab);
        Paper_Protection_colon_label->setObjectName(QStringLiteral("Paper_Protection_colon_label"));
        Paper_Protection_colon_label->setEnabled(true);
        Paper_Protection_colon_label->setGeometry(QRect(362, 82, 16, 20));
#ifndef QT_NO_TOOLTIP
        Paper_Protection_colon_label->setToolTip(QStringLiteral(""));
#endif
        Paper_Protection_colon_label->setText(QStringLiteral(":"));
        Paper_Protection_label = new QLabel(scanner_setting_tab);
        Paper_Protection_label->setObjectName(QStringLiteral("Paper_Protection_label"));
        Paper_Protection_label->setGeometry(QRect(110, 81, 241, 23));
        Paper_Protection_comboBox = new ADFPaperProtectionCombobox(scanner_setting_tab);
        Paper_Protection_comboBox->setObjectName(QStringLiteral("Paper_Protection_comboBox"));
        Paper_Protection_comboBox->setGeometry(QRect(382, 79, 131, 23));
        Double_Feed_Stop_Timing_label = new QLabel(scanner_setting_tab);
        Double_Feed_Stop_Timing_label->setObjectName(QStringLiteral("Double_Feed_Stop_Timing_label"));
        Double_Feed_Stop_Timing_label->setGeometry(QRect(110, 121, 241, 23));
        Double_Feed_Stop_Timing_comboBox = new BehaviorWhenDoubleFeedCombobox(scanner_setting_tab);
        Double_Feed_Stop_Timing_comboBox->setObjectName(QStringLiteral("Double_Feed_Stop_Timing_comboBox"));
        Double_Feed_Stop_Timing_comboBox->setGeometry(QRect(382, 119, 131, 23));
        Double_Feed_Stop_Timing_colon_label = new QLabel(scanner_setting_tab);
        Double_Feed_Stop_Timing_colon_label->setObjectName(QStringLiteral("Double_Feed_Stop_Timing_colon_label"));
        Double_Feed_Stop_Timing_colon_label->setEnabled(true);
        Double_Feed_Stop_Timing_colon_label->setGeometry(QRect(362, 122, 16, 20));
#ifndef QT_NO_TOOLTIP
        Double_Feed_Stop_Timing_colon_label->setToolTip(QStringLiteral(""));
#endif
        Double_Feed_Stop_Timing_colon_label->setText(QStringLiteral(":"));
        tabWidget->addTab(scanner_setting_tab, QString());
        other_tab = new QWidget();
        other_tab->setObjectName(QStringLiteral("other_tab"));
        Other_Reset_pushButton = new QPushButton(other_tab);
        Other_Reset_pushButton->setObjectName(QStringLiteral("Other_Reset_pushButton"));
        Other_Reset_pushButton->setGeometry(QRect(400, 51, 111, 25));
        Reset_label = new QLabel(other_tab);
        Reset_label->setObjectName(QStringLiteral("Reset_label"));
        Reset_label->setGeometry(QRect(50, 52, 321, 23));
        Reset_colon_label = new QLabel(other_tab);
        Reset_colon_label->setObjectName(QStringLiteral("Reset_colon_label"));
        Reset_colon_label->setEnabled(true);
        Reset_colon_label->setGeometry(QRect(380, 54, 16, 20));
#ifndef QT_NO_TOOLTIP
        Reset_colon_label->setToolTip(QStringLiteral(""));
#endif
        Reset_colon_label->setText(QStringLiteral(":"));
        tabWidget->addTab(other_tab, QString());
        Close_pushButton = new QPushButton(ConfigurationDialog);
        Close_pushButton->setObjectName(QStringLiteral("Close_pushButton"));
        Close_pushButton->setGeometry(QRect(459, 439, 111, 25));
        Unlock_pushButton = new QPushButton(ConfigurationDialog);
        Unlock_pushButton->setObjectName(QStringLiteral("Unlock_pushButton"));
        Unlock_pushButton->setEnabled(true);
        Unlock_pushButton->setGeometry(QRect(20, 439, 151, 25));
        retranslateUi(ConfigurationDialog);
        QObject::connect(Close_pushButton, SIGNAL(clicked()), ConfigurationDialog, SLOT(reject()));
        QObject::connect(Units_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Last_Used_checkBox, SIGNAL(clicked(bool)), ConfigurationDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Sleep_Timer_spinBox, SIGNAL(valueChanged(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(AC_Power_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Battery_Power_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Other_Reset_pushButton, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        QObject::connect(Open_Img_Folder_after_scan_checkBox, SIGNAL(clicked(bool)), ConfigurationDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Transfer_data_after_comp_checkBox, SIGNAL(clicked(bool)), ConfigurationDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Counter_Reset_pushButton, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        QObject::connect(Quality_Preview_checkBox, SIGNAL(clicked(bool)), ConfigurationDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Detect_Glass_Dirt_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Paper_Protection_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Double_Feed_Stop_Timing_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Power_Off_If_Disconnected_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Direct_Power_On_comboBox, SIGNAL(activated(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Count_Alert_Setting_num_spinBox, SIGNAL(valueChanged(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Count_Alert_Setting_spinBox, SIGNAL(valueChanged(int)), ConfigurationDialog, SLOT(onValueChanged(int)));
        QObject::connect(Regular_Cleaning_Alert_checkBox, SIGNAL(clicked(bool)), ConfigurationDialog, SLOT(onValueChangedBool(bool)));
        QObject::connect(Maintenance_Reset_pushButton, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        QObject::connect(Reset_pushButton, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        QObject::connect(Reset_pushButton2, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        QObject::connect(Unlock_pushButton, SIGNAL(pressed()), ConfigurationDialog, SLOT(PushButtonAction()));
        tabWidget->setCurrentIndex(0);
        Counter_stackedWidget->setCurrentIndex(0);
        Count_Alert_stackedWidget->setCurrentIndex(0);
        QMetaObject::connectSlotsByName(ConfigurationDialog);
    }
    void retranslateUi(QDialog *ConfigurationDialog)
    {
        ConfigurationDialog->setWindowTitle(QApplication::translate("ConfigurationDialog", "CONFIG_001", 0));
        Serialno_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_005", 0));
        Serialno_value_label->setText(QApplication::translate("ConfigurationDialog", "xxxxx", 0));
        Firmware_version_value_label->setText(QApplication::translate("ConfigurationDialog", "xxxxx", 0));
        Firmware_version_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_006", 0));
        tabWidget->setTabText(tabWidget->indexOf(information_tab), QApplication::translate("ConfigurationDialog", "ES2U_MAIN_004", 0));
        Units_label->setText(QApplication::translate("ConfigurationDialog", "CONFIG_GENERAL_002", 0));
        Last_Used_checkBox->setText(QApplication::translate("ConfigurationDialog", "CONFIG_GENERAL_005", 0));
        Open_Img_Folder_after_scan_checkBox->setText(QApplication::translate("ConfigurationDialog", "CONFIG_SAVEFILE_002", 0));
        Transfer_data_after_comp_checkBox->setText(QApplication::translate("ConfigurationDialog", "CONFIG_SCAN_004", 0));
        Quality_Preview_checkBox->setText(QApplication::translate("ConfigurationDialog", "CONFIG_PREVIEW_002", 0));
        Preview_label->setText(QApplication::translate("ConfigurationDialog", "CONFIG_PREVIEW_001", 0));
        tabWidget->setTabText(tabWidget->indexOf(general_tab), QApplication::translate("ConfigurationDialog", "CONFIG_GENERAL_001", 0));
        Scan_Counter_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_010", 0));
        Scanner_Glass_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_011", 0));
        Scanner_Glass_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
#ifndef QT_NO_TOOLTIP
        ADF_label->setToolTip(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_012", 0));
#endif
        ADF_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_012", 0));
        ADF_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Single_Sided_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_013", 0));
        Single_Sided_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Double_Sided_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_014", 0));
        Double_Sided_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Carrier_Sheet_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Carrier_Sheet_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_054", 0));
        Card_Slot_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_051", 0));
        Card_Slot_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Paper_Jam_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Paper_Jam_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_015", 0));
        Double_Feed_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Double_Feed_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_016", 0));
        Paper_Protection_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_058", 0));
        Paper_Protection_cnt_num_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Separation_Pad_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_060", 0));
        Reset_pushButton2->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_020", 0));
        Number_Of_Scans_cnt_label2->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Number_Of_Scans_label2->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_018", 0));
        Life_Cyde_label2->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_019", 0));
        Life_Cyde_cnt_label2->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Pickup_Pad_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_049", 0));
        Reset_pushButton->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_020", 0));
        Number_Of_Scans_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Number_Of_Scans_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_018", 0));
        Life_Cyde_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_019", 0));
        Life_Cyde_cnt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Roller_Assembly_Kit_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_017", 0));
        Counter_Reset_pushButton->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_020", 0));
        Number_Of_Scans_cnt_label3->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Number_Of_Scans_label3->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_018", 0));
        Life_Cyde_cnt_label3->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_008", 0));
        Life_Cyde_label3->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_019", 0));
        Count_Alert_Setting_num_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_065", 0));
        tabWidget->setTabText(tabWidget->indexOf(counter_tab), QApplication::translate("ConfigurationDialog", "ES2U_MAIN_009", 0));
        Sleep_Timer_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_022", 0));
        Power_Off_Timer_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_024", 0));
        AC_Power_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_056", 0));
        Battery_Power_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_057", 0));
        Direct_Power_On_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_SCANNER_012", 0));
        Power_Off_If_Disconnected_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_061", 0));
        tabWidget->setTabText(tabWidget->indexOf(power_saving_tab), QApplication::translate("ConfigurationDialog", "ES2U_MAIN_021", 0));
        Regular_Cleaning_groupBox->setTitle(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_062", 0));
        Number_of_Scans_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_064", 0));
        Count_Alert_Setting_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_065", 0));
        Regular_Cleaning_Alert_checkBox->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_063", 0));
        Maintenance_Reset_pushButton->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_020", 0));
        Number_of_Scans_num_label->setText(QApplication::translate("ConfigurationDialog", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(maintenance_tab), QApplication::translate("ConfigurationDialog", "ES2U_MAIN_027", 0));
        Detect_Glass_Dirt_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_SCANNER_002", 0));
        Paper_Protection_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_SCANNER_007", 0));
        Double_Feed_Stop_Timing_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_SCANNER_009", 0));
        tabWidget->setTabText(tabWidget->indexOf(scanner_setting_tab), QApplication::translate("ConfigurationDialog", "ES2U_SCANNER_001", 0));
        Other_Reset_pushButton->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_045", 0));
        Reset_label->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_044", 0));
        tabWidget->setTabText(tabWidget->indexOf(other_tab), QApplication::translate("ConfigurationDialog", "ES2U_MAIN_043", 0));
        Close_pushButton->setText(QApplication::translate("ConfigurationDialog", "TC_PREVIEW_001", 0));
#ifndef QT_NO_TOOLTIP
        Unlock_pushButton->setToolTip(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_068", 0));
#endif
        Unlock_pushButton->setText(QApplication::translate("ConfigurationDialog", "ES2U_MAIN_067", 0));
    }
};
namespace Ui {
    class ConfigurationDialog: public Ui_ConfigurationDialog {};
}
QT_END_NAMESPACE
#endif
