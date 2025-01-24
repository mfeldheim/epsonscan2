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
//  ui_imageeditdialog.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef UI_IMAGEEDITDIALOG_H
#define UI_IMAGEEDITDIALOG_H 
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include "imageeditview.h"
QT_BEGIN_NAMESPACE
class Ui_ImageEditDialog
{
public:
    QPushButton *rotateLeft;
    QPushButton *rotateRight;
    QPushButton *removeButton;
    QPushButton *saveButton;
    QPushButton *addButton;
    ImageEditView *graphicsView;
    QPushButton *cancelButton;
    void setupUi(QDialog *ImageEditDialog)
    {
        if (ImageEditDialog->objectName().isEmpty())
            ImageEditDialog->setObjectName(QStringLiteral("ImageEditDialog"));
        ImageEditDialog->resize(1214, 673);
        QIcon icon;
        icon.addFile(QStringLiteral(":/escan2_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ImageEditDialog->setWindowIcon(icon);
        rotateLeft = new QPushButton(ImageEditDialog);
        rotateLeft->setObjectName(QStringLiteral("rotateLeft"));
        rotateLeft->setGeometry(QRect(20, 10, 45, 38));
        rotateLeft->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/btn_multipage_rotate_left90@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        rotateLeft->setIcon(icon1);
        rotateLeft->setIconSize(QSize(32, 32));
        rotateRight = new QPushButton(ImageEditDialog);
        rotateRight->setObjectName(QStringLiteral("rotateRight"));
        rotateRight->setGeometry(QRect(70, 10, 45, 38));
        rotateRight->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/btn_multipage_rotate_right90@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        rotateRight->setIcon(icon2);
        rotateRight->setIconSize(QSize(32, 32));
        removeButton = new QPushButton(ImageEditDialog);
        removeButton->setObjectName(QStringLiteral("removeButton"));
        removeButton->setGeometry(QRect(120, 10, 45, 38));
        removeButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/btn_multipage_delete@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon3);
        removeButton->setIconSize(QSize(32, 32));
        saveButton = new QPushButton(ImageEditDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(980, 620, 89, 25));
        saveButton->setFocusPolicy(Qt::NoFocus);
        addButton = new QPushButton(ImageEditDialog);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(880, 620, 89, 25));
        addButton->setFocusPolicy(Qt::NoFocus);
        graphicsView = new ImageEditView(ImageEditDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 70, 1181, 531));
        graphicsView->setMinimumSize(QSize(1181, 531));
        graphicsView->setMaximumSize(QSize(1181, 531));
        QBrush brush(QColor(0, 0, 0, 100));
        brush.setStyle(Qt::SolidPattern);
        graphicsView->setBackgroundBrush(brush);
        cancelButton = new QPushButton(ImageEditDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(1080, 620, 89, 25));
        cancelButton->setFocusPolicy(Qt::NoFocus);
        retranslateUi(ImageEditDialog);
        QObject::connect(addButton, SIGNAL(clicked()), ImageEditDialog, SLOT(onButtonPressed()));
        QObject::connect(saveButton, SIGNAL(clicked()), ImageEditDialog, SLOT(onButtonPressed()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ImageEditDialog, SLOT(onButtonPressed()));
        QObject::connect(addButton, SIGNAL(clicked()), ImageEditDialog, SLOT(reject()));
        QObject::connect(saveButton, SIGNAL(clicked()), ImageEditDialog, SLOT(reject()));
        QObject::connect(saveButton, SIGNAL(clicked()), ImageEditDialog, SLOT(on_saveButton_clicked()));
        QMetaObject::connectSlotsByName(ImageEditDialog);
    }
    void retranslateUi(QDialog *ImageEditDialog)
    {
        ImageEditDialog->setWindowTitle(QApplication::translate("ImageEditDialog", "EDITPAGE_001", 0));
        rotateLeft->setText(QString());
        rotateRight->setText(QString());
        removeButton->setText(QString());
        saveButton->setText(QApplication::translate("ImageEditDialog", "ADDPAGE_006", 0));
        addButton->setText(QApplication::translate("ImageEditDialog", "EDITPAGE_008", 0));
        cancelButton->setText(QApplication::translate("ImageEditDialog", "ADDPAGE_005", 0));
    }
};
namespace Ui {
    class ImageEditDialog: public Ui_ImageEditDialog {};
}
QT_END_NAMESPACE
#endif
