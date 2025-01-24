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
//  continuousscandialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef CONTINUOUSSCANDIALOG_H
#define CONTINUOUSSCANDIALOG_H 
#include <QDialog>
#include <QGraphicsScene>
#include <QCloseEvent>
#include "supervisor.h"
namespace Ui {
class ContinuousScanDialog;
}
class ContinuousScanDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContinuousScanDialog(Supervisor* sv, QWidget *parent = 0);
    ~ContinuousScanDialog();
    void Initialize(QString message, DoubleFeedMode dialog_type=IMMEDIATE);
    ScanningStatus GetScanningStatus();
protected:
    void closeEvent(QCloseEvent* event);
private slots:
    void onButtonPressed();
private:
    Ui::ContinuousScanDialog *ui;
    QGraphicsScene Scene_;
    QImage m_image;
    ScanningStatus m_scanning_status;
    DoubleFeedMode m_dialog_type;
    Supervisor* m_sv;
    void LoadScanImage();
    void ChangeStrings(DoubleFeedMode dialog_type, QString message);
    void AddADFSpecialErrorMessageForPassportStrings(QString message);
};
#endif
