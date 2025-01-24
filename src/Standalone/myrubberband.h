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
//  myrubberband.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef MYRUBBERBAND_H
#define MYRUBBERBAND_H 
#include <QRubberBand>
#include <QPaintEvent>
#include <QTimer>
#include <QObject>
#include <QApplication>
#include <QDebug>
class MyRubberBand : public QRubberBand
{
    Q_OBJECT
public:
    explicit MyRubberBand(Shape s, QWidget * p = 0);
    ~MyRubberBand();
    QPoint m_startPos_;
    QPoint m_endPos_;
    bool m_existMarquee;
    QTimer* m_timer;
    int m_animation_flag;
    bool m_onMouse;
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void Update();
};
#endif
