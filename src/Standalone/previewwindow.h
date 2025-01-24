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
//  previewwindow.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H 
       
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include "supervisor.h"
#include "drawingarea.h"
#define REFERENCE_WIDTH 290
#define REFERENCE_HEIGHT 460
#define REFERENCE_POSX 80
#define REFERENCE_POSY 50
class MainWindow;
class PreviewWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PreviewWindow(Supervisor* sv, QWidget *parent = 0);
    void initialize(MainWindow* window);
    DrawingArea* getDrawingArea(void);
    bool DrawImage(void);
    bool ResetMessageBox(void);
    QRect UpdateMarqueeSizeLabel(void);
    QPushButton *m_CloseButton;
    QImage getPreviewImage(void);
    void DeleteMarquee();
private:
    MainWindow* m_main_window;
    QFrame *m_DrawFrame;
    QFrame *m_CloseFrame;
    QFrame *m_SizeFrame;
    QLabel *m_WidthIconImageLabel;
    QLabel *m_WidthSizeLabel;
    QLabel *m_HeightIconImageLabel;
    QLabel *m_HeightSizeLabel;
    QPushButton *m_DeleteButton;
    QPushButton *m_FocusPositionButton;
    DrawingArea* m_graphicsView;
    QGraphicsScene* m_Scene_;
    Supervisor *m_sv;
    QImage m_preview_image;
    void PreviewImageAdjustment(void);
    QPoint PreviewImagePositionAdjustment(double preview_img_width, double preview_img_height);
public slots:
    bool on_Close_Button_pressed(bool Confirm=true);
private slots:
    void on_Delete_Button_pressed();
    void on_FocusPosition_Button_pressed();
    void MarqueeCreated(bool exist);
};
#endif
