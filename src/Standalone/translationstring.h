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
//  translationstring.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef TRANSLATIONSTRING_H
#define TRANSLATIONSTRING_H 
#include <QObject>
typedef struct {
    QString MAINSETTING_003;
    QString MAINSETTING_004;
    QString MAINSETTING_005;
    QString MAINSETTING_006;
    QString MAINSETTING_009;
    QString MAINSETTING_010;
    QString MAINSETTING_014;
    QString MAINSETTING_015;
    QString MAINSETTING_016;
    QString MAINSETTING_017;
    QString MAINSETTING_021;
    QString MAINSETTING_022;
    QString MAINSETTING_023;
    QString MAINSETTING_024;
    QString MAINSETTING_025;
    QString MAINSETTING_031;
    QString MAINSETTING_047;
    QString MAINSETTING_075;
    QString MAINSETTING_076;
    QString MAINSETTING_077;
    QString MAINSETTING_078;
    QString MAINSETTING_081;
    QString ADVANCEDSETTING_008;
    QString ADVANCEDSETTING_009;
    QString ADVANCEDSETTING_011;
    QString ADVANCEDSETTING_012;
    QString ADVANCEDSETTING_013;
    QString ADVANCEDSETTING_050;
    QString ADVANCEDSETTING_051;
    QString ADVANCEDSETTING_052;
    QString ADVANCEDSETTING_053;
    QString ADVANCEDSETTING_054;
    QString ADVANCEDSETTING_055;
    QString ADVANCEDSETTING_059;
    QString ADVANCEDSETTING_060;
    QString ADVANCEDSETTING_061;
    QString ADVANCEDSETTING_063;
    QString ADVANCEDSETTING_064;
    QString ADVANCEDSETTING_070;
    QString ADVANCEDSETTING_072;
    QString ADVANCEDSETTING_114;
    QString AUTOFEEDMODE_005;
    QString AUTOFEEDMODE_006;
    QString AUTOFEEDMODE_007;
    QString IMAGEFORMATOPTION_TIF_011;
    QString IMAGEFORMATOPTION_TIF_012;
    QString E_SCAN_001;
    QString E_SCAN_003;
    QString E_SCAN_101;
    QString E_SCAN_102;
    QString E_SCAN_103;
    QString E_SCAN_104;
    QString E_SCAN_105;
    QString E_SCAN_107;
    QString E_SCAN_109;
    QString E_SCAN_110;
    QString E_SCAN_111;
    QString E_SCAN_113;
    QString E_SCAN_114;
    QString E_SCAN_117;
    QString E_SCAN_118;
    QString ES2U_MAIN_008;
    QString ES2U_MAIN_025;
    QString ES2U_MAIN_052;
    QString ES2U_MAIN_053;
    QString ES2U_SCANNER_003;
    QString ES2U_SCANNER_004;
    QString ES2U_SCANNER_005;
    QString ES2U_SCANNER_008;
    QString ES2U_SCANNER_010;
    QString ES2U_SCANNER_011;
    QString ES2U_SCANNER_012;
    QString ES2U_SCANNER_013;
    QString ES2U_SCANNER_014;
    QString SIZELIST_NOSIZE_028;
    QString SIZELIST_NOSIZE_030;
    QString SIZELIST_NOSIZE_015;
    QString SIZELIST_NOSIZE_016;
    QString SIZELIST_NOSIZE_019;
    QString SIZELIST_NOSIZE_025;
    QString SIZELIST_NOSIZE_017;
    QString SIZELIST_NOSIZE_018;
    QString SIZELIST_NOSIZE_011;
    QString SIZELIST_NOSIZE_012;
    QString SIZELIST_NOSIZE_009;
    QString SIZELIST_NOSIZE_010;
    QString SIZELIST_NOSIZE_007;
    QString SIZELIST_NOSIZE_008;
    QString SIZELIST_NOSIZE_023;
    QString SIZELIST_NOSIZE_024;
    QString SIZELIST_NOSIZE_013;
    QString SIZELIST_NOSIZE_014;
    QString SIZELIST_NOSIZE_021;
    QString SIZELIST_NOSIZE_001;
    QString SIZELIST_NOSIZE_002;
    QString SIZELIST_NOSIZE_003;
    QString SIZELIST_NOSIZE_004;
    QString SIZELIST_NOSIZE_027;
    QString SIZELIST_NOSIZE_029;
    QString SIZELIST_NOSIZE_031;
    QString SIZELIST_NOSIZE_032;
    QString SIZELIST_NOSIZE_038;
    QString SIZELIST_NOSIZE_039;
    QString SIZELIST_NOSIZE_040;
    QString SIZELIST_NOSIZE_041;
    QString SIZELIST_NOSIZE_042;
    QString SIZELIST_NOSIZE_043;
    QString A_UI_003;
    QString A_UI_005;
    QString A_UI_006;
    QString A_SCAN_001;
    QString A_UNIT_001;
    QString A_UNIT_007;
    QString A_UNIT_008;
    QString A_UNIT_015;
    QString A_UNIT_009;
    QString C_UI_002;
    QString C_UI_004;
    QString C_UI_005;
    QString C_UI_006;
    QString C_UI_101;
    QString C_UI_102;
    QString C_UNIT_001;
    QString C_UNIT_002;
    QString C_UNIT_003;
    QString E_UI_103;
    QString E_UI_109;
    QString E_SAVE_001;
    QString E_SAVE_004;
    QString E_COMM_001;
    QString E_COMM_102;
    QString E_COMM_103;
    QString E_UNIT_008;
    QString E_UNIT_009;
    QString E_UNIT_010;
    QString E_UNIT_011;
    QString E_ENV_001;
    QString E_PARA_001;
    QString E_PARA_003;
    QString E_PARA_005;
    QString E_PARA_011;
    QString E_PARA_013;
    QString CUSTOMSIZE_008;
    QString CUSTOMSIZE_009;
    QString CUSTOMSIZE_010;
    QString CONFIG_GENERAL_003;
    QString CONFIG_GENERAL_004;
    QString CONFIG_DOC_004;
    QString CONFIG_DOC_005;
    QString CONFIG_DOC_010;
    QString CONFIG_DOC_013;
    QString CONFIG_DOC_014;
    QString CONFIG_DOC_019;
    QString CONFIG_DOC_020;
    QString CONFIG_DOC_021;
    QString CONFIG_DOC_022;
    QString CONFIG_DOC_023;
    QString CONFIG_DOC_024;
    QString CONFIG_SCAN_008;
    QString CONFIG_SCAN_009;
    QString PROGRESS_003;
    QString PROGRESS_005;
    QString PROGRESS_007;
    QString PROGRESS_008;
    QString FILESAVESETTING_003;
    QString FILESAVESETTING_004;
    QString FILESAVESETTING_005;
    QString FILESAVESETTING_006;
    QString FILESAVESETTING_007;
    QString FILESAVESETTING_009;
    QString FILESAVESETTING_016;
    QString FILESAVESETTING_012;
    QString MENU_001;
    QString SCANNERSETTING_005;
    QString SCANNERSETTING_006;
    QString VERSION_003;
    QString CONFIRMCONTINUE_002;
    QString CONFIRMCONTINUE_003;
    QString CONFIRMCONTINUE_004;
    QString CONFIRMCONTINUE_005;
    QString CONFIRMCONTINUE_008;
    QString CONFIRMCONTINUE_011;
    QString CONFIRMCONTINUE_013;
    QString CONFIRMCONTINUE_014;
    QString CONFIRMCONTINUE_015;
    QString LINUX_E_COMM_001;
    QString LINUX_C_UI_001;
    QString LINUX_C_UI_002;
    QString LINUX_DEVICESELECT_003;
    QString LINUX_SIZELIST_NOSIZE_001;
    QString LINUX_FILESAVESETTING_001;
    QString LINUX_FILESAVESETTING_002;
    QString LINUX_FILESAVESETTING_003;
    QString LINUX_FILESAVESETTING_004;
    QString LINUX_FILESAVESETTING_005;
    QString LINUX_FILESAVESETTING_006;
    QString LINUX_FILESAVESETTING_007;
    QString LINUX_FILESAVESETTING_008;
    QString LINUX_FILESAVESETTING_009;
    QString LINUX_MAINSETTING_001;
    QString PHOTO_MAIN_008;
    QString PHOTO_MAIN_009;
    QString PHOTO_MAIN_010;
    QString PHOTO_MAIN_013;
    QString PHOTO_MAIN_019;
    QString PHOTO_MAIN_020;
} TRANSLATIONSTR;
class TranslationString
{
public:
    TranslationString();
    void SetString();
    void SetFilename(std::string _filename);
    static TranslationString& GetString();
    TRANSLATIONSTR translation_str;
};
#endif
