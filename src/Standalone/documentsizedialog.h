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
//  documentsizedialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DOCUMENTSIZEDIALOG_H
#define DOCUMENTSIZEDIALOG_H 
#include <QDialog>
#include "supervisor.h"
namespace Ui {
class DocumentSizeDialog;
}
class DocumentSizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DocumentSizeDialog(QWidget *parent = 0);
    ~DocumentSizeDialog();
    void Initialize(SCAN_AREA_VALUE document_size_para, ScannerKind kind);
    void Finalize();
    void SetSize(void);
    void GetSize(double *user_width, double *user_length, bool *user_det_paper_len);
    void select_units(void);
public slots:
    void onValueChangedBool(bool value);
private:
    Ui::DocumentSizeDialog *d_size_ui;
    double width;
    double length;
    bool det_paper_length;
    void updateUI(void);
    void ChangeDetPaperCheck(bool checked);
};
#endif
