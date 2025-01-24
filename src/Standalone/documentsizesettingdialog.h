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
//  documentsizesettingdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DOCUMENTSIZESETTINGDIALOG_H
#define DOCUMENTSIZESETTINGDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class DocumentSizeSettingDialog;
}
class DocumentSizeSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DocumentSizeSettingDialog(INT_SETTING_VALUE* inscribed_para, QWidget *parent = 0);
    ~DocumentSizeSettingDialog();
    void Initialize(INT_SETTING_VALUE* document_size_setting);
public slots:
    void onValueChangedBool(bool value);
private:
    Ui::DocumentSizeSettingDialog *ui;
    void updateUI(void);
    void ChangeDetPaperCheck(bool checked);
    INT_SETTING_VALUE* m_inscribed_para;
};
#endif
