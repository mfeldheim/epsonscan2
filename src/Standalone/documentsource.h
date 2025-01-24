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
//  documentsource.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DOCUMENTSOURCE_H
#define DOCUMENTSOURCE_H 
#include <QComboBox>
#include "supervisor.h"
#include "documentsourcesettingsdialog.h"
class Document_Source : public QComboBox
{
public:
    FunctionalUnit current_item;
    Document_Source(QWidget *parent = 0);
    void initialize(INT_SETTING_VALUE document_source_para, bool functionalunit_auto);
    void update_ui(INT_SETTING_VALUE document_source_para, SDISupportLevel AFM_supported_level);
    void item_event(int value, SCANPARA* doc_source_para);
    bool changed;
private:
    DocumentSourceSettingsDialog* m_documentsourcesettings_dialog;
    void set_enabled(bool enabled);
    void add_item(int32_t item_list[], int32_t list_size, bool AFM_supported);
    void select_item();
    void item_event_options(INT_SETTING_VALUE* afm_timeout_para);
    bool search_item_list(int item, int32_t item_list[], int32_t list_size);
};
#endif
