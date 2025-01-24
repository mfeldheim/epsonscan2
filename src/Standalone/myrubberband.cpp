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
//  myrubberband.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "myrubberband.h"
#include <QPainter>
#include <QStyleOptionFocusRect>
#define UPDATE_INTERVAL 150
MyRubberBand::MyRubberBand(QRubberBand::Shape s, QWidget *p) :
    QRubberBand(s,p),
    m_timer(NULL),
    m_existMarquee(false),
    m_animation_flag(0),
    m_onMouse(false)
{
    m_timer = new QTimer(this);
    if(m_timer == NULL){
        return;
    }
    m_timer->setInterval(UPDATE_INTERVAL);
    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()));
}
MyRubberBand::~MyRubberBand(){
    if(m_timer){
        if(m_timer->isActive()){
            m_timer->stop();
        }
        delete m_timer;
        m_timer = NULL;
    }
}
void MyRubberBand::paintEvent(QPaintEvent *event)
{
    if(m_existMarquee == false){
        QRubberBand::paintEvent(event);
    }
    QPainter p(this);
    p.setBrush(QBrush(Qt::NoBrush));
    QPen pen = p.pen();
    if(m_animation_flag == 0){
        pen.setStyle(Qt::DashLine );
    }else if(m_animation_flag == 1){
        pen.setStyle(Qt::DashDotLine );
    }else if(m_animation_flag == 2){
        pen.setStyle(Qt::DashDotDotLine );
    }
    pen.setBrush(Qt::blue);
    pen.setWidth(2);
    p.setPen(pen);
    int width, height;
    width = this->width();
    height = this->height();
    p.drawLine(QPoint(0, 0), QPoint(width, 0));
    p.drawLine(QPoint(0, 0), QPoint(0, height));
    p.drawLine(QPoint(width, 0), QPoint(width, height));
    p.drawLine(QPoint(0, height), QPoint(width, height));
}
void MyRubberBand::Update()
{
    m_animation_flag++;
    if(m_animation_flag == 3){
        m_animation_flag = 0;
    }
    this->repaint();
}
