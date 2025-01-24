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
//  imageeditdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGEEDITDIALOG_H
#define IMAGEEDITDIALOG_H 
#include <QDialog>
#include "supervisor.h"
#include "imageeditview.h"
namespace Ui {
class ImageEditDialog;
}
class ImageEditDialog : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent* event);
public:
    explicit ImageEditDialog(std::list<imageEditInfo> imgpath_list, ScanningStatus* scanning_status, QWidget *parent = 0);
    ~ImageEditDialog();
    void grayOut(bool existImage);
    void saveButtonGrayOut(bool existOneImage);
    std::list<imageEditInfo> m_returnInfoList;
    void getInfoList(std::list<imageEditInfo> *List);
    enum ImageEditStatusFlag{
        ImageEditStatusIsNotGot = 0x0,
        ImageEditStatusIsSave = 0x1,
        ImageEditStatusIsReturn = 0x2
    };
    ImageEditStatusFlag m_returnStatus = ImageEditStatusIsNotGot;
private slots:
    void onButtonPressed();
    void on_rotateLeft_clicked();
    void on_rotateRight_clicked();
    void on_removeButton_clicked();
    void on_saveButton_clicked();
private:
    Ui::ImageEditDialog *ui;
    void reject();
    int showRemoveMessage();
    bool CancelDialog(void);
    ScanningStatus* scanning_status;
};
#endif
