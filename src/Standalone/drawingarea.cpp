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
//  drawingarea.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "drawingarea.h"
#define MARQUEE_WIDTH 2
#define MARQUEE_WIDTH_PLUS 3
#define MINIMUM_MARQUEE_SIZE 10
DrawingArea::DrawingArea(QWidget *parent) :
    QGraphicsView(parent),
    m_rubberBand_(nullptr),
    m_MousePressed(false),
    m_MouseEdgePressed(false),
    m_MousePos(0, 0),
    m_marqueeEdge(TopEdge),
    m_MarqueeEnebled(true)
{
}
DrawingArea::~DrawingArea(){
    if (m_mqrqueeCreatedCallBack)
    {
        m_mqrqueeCreatedCallBack(false, QRect(0,0,0,0));
    }
    this->SetMarqueeCreatedCallBack(nullptr);
    this->SetMarqueeCreatedForDelButtonCallBack(nullptr);
    if(m_rubberBand_){
        delete m_rubberBand_;
        m_rubberBand_ = nullptr;
    }
}
void DrawingArea::setMarqueeEnebled(bool Enabled)
{
    m_MarqueeEnebled = Enabled;
}
void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if(!m_MarqueeEnebled){
        return;
    }
    this->viewport()->setMouseTracking(true);
    m_MousePressed = true;
    if (!m_rubberBand_) {
        m_rubberBand_ = new MyRubberBand(MyRubberBand::Rectangle, this);
    }
    if(m_rubberBand_->m_existMarquee == true){
        if(CheckMouseOnEdge(event->pos())){
            m_MouseEdgePressed = true;
            m_rubberBand_->m_onMouse = true;
        }else {
            if(this->CheckMouseOnMarquee(event->pos())){
                m_MousePos = CalculateDiff(event->pos(), m_rubberBand_->m_startPos_, false);
                QApplication::setOverrideCursor(Qt::ClosedHandCursor);
                m_Before_Pos = event->pos();
                m_rubberBand_->m_onMouse = true;
            }else {
                m_rubberBand_->m_existMarquee = false;
                m_rubberBand_->m_onMouse = false;
            }
        }
    }
    m_rubberBand_->m_timer->stop();
    if(m_rubberBand_->m_existMarquee == false){
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        m_rubberBand_->repaint();
        m_rubberBand_->m_startPos_ = event->pos();
        m_rubberBand_->setGeometry(QRect(m_rubberBand_->m_startPos_, QSize()));
        m_rubberBand_->show();
    }
}
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_MarqueeEnebled || !m_rubberBand_){
        return;
    }
    if(m_MouseEdgePressed){
        m_rubberBand_->m_existMarquee = false;
        QPoint curPos = MarqueeRangeLimit(event->pos());
        if(m_marqueeEdge == TopEdge){
            curPos.setX(m_rubberBand_->m_endPos_.x());
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setY(m_rubberBand_->m_endPos_.y() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.y() != this->height()-this->frameWidth()){
                    m_marqueeEdge = DownEdge;
                }
            }else {
                if(curPos.y() <= 0){
                    m_rubberBand_->m_startPos_.setY(0);
                }else {
                    m_rubberBand_->m_startPos_.setY(curPos.y());
                }
            }
        }else if(m_marqueeEdge == DownEdge){
            curPos.setX(m_rubberBand_->m_endPos_.x());
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setY(m_rubberBand_->m_startPos_.y() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.y() != 0){
                    m_marqueeEdge = TopEdge;
                }
            }else {
                if(curPos.y() >= this->height()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setY(this->height()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setY(curPos.y());
                }
            }
        }else if(m_marqueeEdge == LeftEdge){
            curPos.setY(m_rubberBand_->m_endPos_.y());
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setX(m_rubberBand_->m_endPos_.x() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.x() != this->width()-this->frameWidth()){
                    m_marqueeEdge = RightEdge;
                }
            }else {
                if(curPos.x() <= 0){
                    m_rubberBand_->m_startPos_.setX(0);
                }else {
                    m_rubberBand_->m_startPos_.setX(curPos.x());
                }
            }
        }else if(m_marqueeEdge == RightEdge){
            curPos.setY(m_rubberBand_->m_endPos_.y());
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setX(m_rubberBand_->m_startPos_.x() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.x() != 0){
                    m_marqueeEdge = LeftEdge;
                }
            }else {
                if(curPos.x() >= this->width()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setX(this->width()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setX(curPos.x());
                }
            }
        }else if(m_marqueeEdge == TopLeftPos){
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setX(m_rubberBand_->m_endPos_.x() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.x() != this->width()-this->frameWidth()){
                    m_marqueeEdge = TopRightPos;
                }
            }else {
                if(curPos.x() <= 0){
                    m_rubberBand_->m_startPos_.setX(0);
                }else {
                    m_rubberBand_->m_startPos_.setX(curPos.x());
                }
            }
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setY(m_rubberBand_->m_endPos_.y() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.y() != this->height()-this->frameWidth()){
                    m_marqueeEdge = DownLeftPos;
                }
            }else {
                if(curPos.y() <= 0){
                    m_rubberBand_->m_startPos_.setY(0);
                }else {
                    m_rubberBand_->m_startPos_.setY(curPos.y());
                }
            }
        }else if(m_marqueeEdge == TopRightPos){
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setX(m_rubberBand_->m_startPos_.x() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.x() != 0){
                    m_marqueeEdge = TopLeftPos;
                }
            }else {
                if(curPos.x() >= this->width()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setX(this->width()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setX(curPos.x());
                }
            }
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setY(m_rubberBand_->m_endPos_.y() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.y() != this->height()-this->frameWidth()){
                    m_marqueeEdge = DownRightPos;
                }
            }else {
                if(curPos.y() <= 0){
                    m_rubberBand_->m_startPos_.setY(0);
                }else {
                    m_rubberBand_->m_startPos_.setY(curPos.y());
                }
            }
        }else if(m_marqueeEdge == DownLeftPos){
            if(this->CalculateDiff(curPos, m_rubberBand_->m_endPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_startPos_.setX(m_rubberBand_->m_endPos_.x() - MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_endPos_.x() != this->width()-this->frameWidth()){
                    m_marqueeEdge = DownRightPos;
                }
            }else {
                if(curPos.x() <= 0){
                    m_rubberBand_->m_startPos_.setX(0);
                }else {
                    m_rubberBand_->m_startPos_.setX(curPos.x());
                }
            }
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setY(m_rubberBand_->m_startPos_.y() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.y() != 0){
                    m_marqueeEdge = TopLeftPos;
                }
            }else {
                if(curPos.y() >= this->height()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setY(this->height()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setY(curPos.y());
                }
            }
        }else if(m_marqueeEdge == DownRightPos){
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).x() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setX(m_rubberBand_->m_startPos_.x() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.x() != 0){
                    m_marqueeEdge = DownLeftPos;
                }
            }else {
                if(curPos.x() >= this->width()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setX(this->width()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setX(curPos.x());
                }
            }
            if(this->CalculateDiff(curPos, m_rubberBand_->m_startPos_, true).y() < MINIMUM_MARQUEE_SIZE){
                m_rubberBand_->m_endPos_.setY(m_rubberBand_->m_startPos_.y() + MINIMUM_MARQUEE_SIZE);
                if(m_rubberBand_->m_startPos_.y() != 0){
                    m_marqueeEdge = TopRightPos;
                }
            }else {
                if(curPos.y() >= this->height()-this->frameWidth()){
                    m_rubberBand_->m_endPos_.setY(this->height()-this->frameWidth());
                }else {
                    m_rubberBand_->m_endPos_.setY(curPos.y());
                }
            }
        }
        m_rubberBand_->setGeometry(QRect(m_rubberBand_->m_startPos_, m_rubberBand_->m_endPos_).normalized());
    }else if(m_MousePressed){
        if(m_rubberBand_->m_onMouse == true){
            m_rubberBand_->m_existMarquee = false;
            m_Diff_Pos = CalculateDiff(event->pos(), m_Before_Pos, false);
            if(m_rubberBand_->m_startPos_.x() == 0){
                if(event->pos().x() <= m_MousePos.x()){
                    m_Diff_Pos.setX(0);
                }
            }
            if(m_rubberBand_->m_startPos_.y() == 0){
                if(event->pos().y() <= m_MousePos.y()){
                    m_Diff_Pos.setY(0);
                }
            }
            m_Before_Pos = event->pos();
            int smove_x = m_rubberBand_->m_startPos_.x() + m_Diff_Pos.x();
            int smove_y = m_rubberBand_->m_startPos_.y() + m_Diff_Pos.y();
            if(smove_x < 0){
                smove_x = 0;
                m_Diff_Pos.setX(0-m_rubberBand_->m_startPos_.x());
            }
            if(smove_y < 0){
                smove_y = 0;
                m_Diff_Pos.setY(0-m_rubberBand_->m_startPos_.y());
            }
            if(m_rubberBand_->m_endPos_.x() == this->width()-this->frameWidth()){
                if(event->pos().x() >= smove_x + m_MousePos.x()){
                    m_Diff_Pos.setX(0);
                }
            }
            if(m_rubberBand_->m_endPos_.y() == this->height()-this->frameWidth()){
                if(event->pos().y() >= smove_y + m_MousePos.y()){
                    m_Diff_Pos.setY(0);
                }
            }
            int emove_x = m_rubberBand_->m_endPos_.x() + m_Diff_Pos.x();
            int emove_y = m_rubberBand_->m_endPos_.y() + m_Diff_Pos.y();
            if(emove_x >= this->width()-this->frameWidth()){
                smove_x = (this->width()-this->frameWidth()) - (m_rubberBand_->m_endPos_.x() - m_rubberBand_->m_startPos_.x());
                emove_x = this->width()-this->frameWidth();
            }
            if(emove_y >= this->height()-this->frameWidth()){
                smove_y = (this->height()-this->frameWidth()) - (m_rubberBand_->m_endPos_.y() - m_rubberBand_->m_startPos_.y());
                emove_y = this->height()-this->frameWidth();
            }
            m_rubberBand_->m_startPos_.setX(smove_x);
            m_rubberBand_->m_startPos_.setY(smove_y);
            m_rubberBand_->m_endPos_.setX(emove_x);
            m_rubberBand_->m_endPos_.setY(emove_y);
            m_rubberBand_->setGeometry(QRect(m_rubberBand_->m_startPos_, m_rubberBand_->m_endPos_).normalized());
        }else {
            QPoint endPos = event->pos();
            m_rubberBand_->m_endPos_ = MarqueeRangeLimit(endPos);
            m_rubberBand_->setGeometry(QRect(m_rubberBand_->m_startPos_, m_rubberBand_->m_endPos_).normalized());
        }
    }else {
        if(!CheckMouseOnEdge(event->pos())){
            if(this->CheckMouseOnMarquee(event->pos())){
                QApplication::setOverrideCursor(Qt::OpenHandCursor);
            }else {
                QApplication::setOverrideCursor(Qt::ArrowCursor);
            }
        }
    }
}
void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(!m_MarqueeEnebled){
        return;
    }
    m_MousePos.setX(0);
    m_MousePos.setY(0);
    if(m_rubberBand_->m_startPos_ == event->pos() &&
            (m_marqueeEdge != TopLeftPos
             || (m_marqueeEdge == TopLeftPos && m_rubberBand_->m_onMouse == false))){
        m_rubberBand_->m_endPos_ = event->pos();
    }
    if(this->CalculateDiff(m_rubberBand_->m_startPos_, m_rubberBand_->m_endPos_, true).x() < MINIMUM_MARQUEE_SIZE ||
            this->CalculateDiff(m_rubberBand_->m_startPos_, m_rubberBand_->m_endPos_, true).y() < MINIMUM_MARQUEE_SIZE){
        m_rubberBand_->m_existMarquee = false;
        m_rubberBand_->m_onMouse = false;
        m_rubberBand_->hide();
        m_rubberBand_->m_startPos_.setX(0);
        m_rubberBand_->m_startPos_.setY(0);
        m_rubberBand_->m_endPos_.setX(0);
        m_rubberBand_->m_endPos_.setY(0);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        this->UpdateMarqueeSizeLabel(this->width(), this->height());
    }else {
        if(m_rubberBand_->m_onMouse == true){
            QApplication::setOverrideCursor(Qt::OpenHandCursor);
        }else {
            this->CheckMarqueeArea(event->pos());
        }
        this->OptimizeArea();
        m_rubberBand_->m_existMarquee = true;
        m_rubberBand_->m_timer->start();
        m_rubberBand_->repaint();
        if(m_rubberBand_->width() == 0 && m_rubberBand_->height() == 0){
            qDebug() << "end event->pos()" << event->pos();
        }
        this->UpdateMarqueeSizeLabel(m_rubberBand_->width(), m_rubberBand_->height());
    }
    this->m_MousePressed = false;
    this->m_MouseEdgePressed = false;
}
void DrawingArea::OptimizeArea()
{
    int start_x = m_rubberBand_->m_startPos_.x();
    int start_y = m_rubberBand_->m_startPos_.y();
    int end_x = m_rubberBand_->m_endPos_.x();
    int end_y = m_rubberBand_->m_endPos_.y();
    m_rubberBand_->m_startPos_.setX(end_x > start_x ? start_x : end_x);
    m_rubberBand_->m_startPos_.setY(end_y > start_y ? start_y : end_y);
    m_rubberBand_->m_endPos_.setX(end_x > start_x ? end_x : start_x);
    m_rubberBand_->m_endPos_.setY(end_y > start_y ? end_y : start_y);
}
QPoint DrawingArea::MarqueeRangeLimit(QPoint current_pos)
{
    QPoint ResultAreaSize;
    if(current_pos.x() >= this->width()-this->frameWidth()){
        ResultAreaSize.setX(this->width()-this->frameWidth());
    }else if(current_pos.x() <= 0){
        ResultAreaSize.setX(0);
    }else {
        ResultAreaSize.setX(current_pos.x());
    }
    if(current_pos.y() >= this->height()-this->frameWidth()){
        ResultAreaSize.setY(this->height()-this->frameWidth());
    }else if(current_pos.y() <= 0){
        ResultAreaSize.setY(0);
    }else {
        ResultAreaSize.setY(current_pos.y());
    }
    return ResultAreaSize;
}
QPoint DrawingArea::CalculateDiff(QPoint A_pos, QPoint B_pos, bool mode)
{
    QPoint MarqueeAreaSize;
    if(mode){
        if(A_pos.x() > B_pos.x()){
            MarqueeAreaSize.setX(A_pos.x() - B_pos.x());
        }else if(A_pos.x() < B_pos.x()){
            MarqueeAreaSize.setX(B_pos.x() - A_pos.x());
        }else {
            MarqueeAreaSize.setX(0);
        }
        if(A_pos.y() > B_pos.y()){
            MarqueeAreaSize.setY(A_pos.y() - B_pos.y());
        }else if(A_pos.y() < B_pos.y()){
            MarqueeAreaSize.setY(B_pos.y() - A_pos.y());
        }else {
            MarqueeAreaSize.setY(0);
        }
    }else {
        MarqueeAreaSize.setX(A_pos.x() - B_pos.x());
        MarqueeAreaSize.setY(A_pos.y() - B_pos.y());
    }
    return MarqueeAreaSize;
}
void DrawingArea::CheckMarqueeArea(QPoint current_pos)
{
    if(current_pos.x() >= m_rubberBand_->m_startPos_.x() && current_pos.y() >= m_rubberBand_->m_startPos_.y()){
        m_marqueeArea = DownRight;
    }else if(current_pos.x() > m_rubberBand_->m_startPos_.x() && current_pos.y() < m_rubberBand_->m_startPos_.y()){
        m_marqueeArea = TopRight;
    }else if(current_pos.x() < m_rubberBand_->m_startPos_.x() && current_pos.y() > m_rubberBand_->m_startPos_.y()){
        m_marqueeArea = DownLeft;
    }else if(current_pos.x() < m_rubberBand_->m_startPos_.x() && current_pos.y() < m_rubberBand_->m_startPos_.y()){
        m_marqueeArea = TopLeft;
    }
}
bool DrawingArea::CheckMouseOnMarquee(QPoint current_pos)
{
    bool In_x = false;
    bool In_y = false;
    if(current_pos.x() >= m_rubberBand_->m_startPos_.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x()){
        In_x = true;
    }else if(current_pos.x() <= m_rubberBand_->m_startPos_.x() && current_pos.x() >= m_rubberBand_->m_endPos_.x()){
        In_x = true;
    }
    if(current_pos.y() >= m_rubberBand_->m_startPos_.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y()){
        In_y = true;
    }else if(current_pos.y() <= m_rubberBand_->m_startPos_.y() && current_pos.y() >= m_rubberBand_->m_endPos_.y()){
        In_y = true;
    }
    if(In_x && In_y){
        return true;
    }else {
        return false;
    }
}
bool DrawingArea::CheckMouseOnEdge(QPoint current_pos)
{
    if(m_rubberBand_->m_existMarquee){
        if(m_rubberBand_->m_endPos_.x() == this->width()-this->frameWidth() || m_rubberBand_->m_endPos_.y() == this->height()-this->frameWidth()){
            if(m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH_PLUS -3 <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH_PLUS -3){
                if(m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH_PLUS < current_pos.y() && current_pos.y() < m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH_PLUS){
                    QApplication::setOverrideCursor(Qt::SizeHorCursor);
                    m_marqueeEdge = RightEdge;
                    return true;
                }
            }
            if((m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH_PLUS -3 <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH_PLUS -3)
                     && (m_rubberBand_->m_startPos_.y() - MARQUEE_WIDTH_PLUS -3 <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH_PLUS -3)){
                QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
                m_marqueeEdge = TopRightPos;
                return true;
            }
            if((m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH_PLUS -3 <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH_PLUS -3)
                     && (m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH_PLUS -3 <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH_PLUS -3)){
                QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
                m_marqueeEdge = DownRightPos;
                return true;
            }
            if(m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH_PLUS -3 <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH_PLUS -3){
                if(m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH_PLUS < current_pos.x() && current_pos.x() < m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH_PLUS){
                    QApplication::setOverrideCursor(Qt::SizeVerCursor);
                    m_marqueeEdge = DownEdge;
                    return true;
                }
            }
            if((m_rubberBand_->m_startPos_.x() - MARQUEE_WIDTH_PLUS -3 <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH_PLUS -3)
                     && (m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH_PLUS -3 <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH_PLUS -3)){
                QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
                m_marqueeEdge = DownLeftPos;
                return true;
            }
        }
        if(m_rubberBand_->m_startPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH){
            if(m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH < current_pos.y() && current_pos.y() < m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH){
                QApplication::setOverrideCursor(Qt::SizeHorCursor);
                m_marqueeEdge = LeftEdge;
                return true;
            }
        }else if(m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH){
            if(m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH < current_pos.y() && current_pos.y() < m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH){
                QApplication::setOverrideCursor(Qt::SizeHorCursor);
                m_marqueeEdge = RightEdge;
                return true;
            }
        }else if(m_rubberBand_->m_startPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH){
            if(m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH < current_pos.x() && current_pos.x() < m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH){
                QApplication::setOverrideCursor(Qt::SizeVerCursor);
                m_marqueeEdge = TopEdge;
                return true;
            }
        }else if(m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH){
            if(m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH < current_pos.x() && current_pos.x() < m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH){
                QApplication::setOverrideCursor(Qt::SizeVerCursor);
                m_marqueeEdge = DownEdge;
                return true;
            }
        }
        if((m_rubberBand_->m_startPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH)
                && (m_rubberBand_->m_startPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH)){
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            m_marqueeEdge = TopLeftPos;
            return true;
        }else if((m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH)
                 && (m_rubberBand_->m_startPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_startPos_.y() + MARQUEE_WIDTH)){
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            m_marqueeEdge = TopRightPos;
            return true;
        }else if((m_rubberBand_->m_startPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_startPos_.x() + MARQUEE_WIDTH)
                 && (m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH)){
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            m_marqueeEdge = DownLeftPos;
            return true;
        }else if((m_rubberBand_->m_endPos_.x() - MARQUEE_WIDTH <= current_pos.x() && current_pos.x() <= m_rubberBand_->m_endPos_.x() + MARQUEE_WIDTH)
                 && (m_rubberBand_->m_endPos_.y() - MARQUEE_WIDTH <= current_pos.y() && current_pos.y() <= m_rubberBand_->m_endPos_.y() + MARQUEE_WIDTH)){
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            m_marqueeEdge = DownRightPos;
            return true;
        }
    }
    return false;
}
void DrawingArea::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(!m_MarqueeEnebled){
        return;
    }
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
void DrawingArea::SetMarqueeSizeLabel(QLabel *width_label, QLabel *height_label)
{
    m_Width_label = width_label;
    m_Height_label = height_label;
}
#include "configuration.h"
#include "translationstring.h"
#include "common_utility.h"
void DrawingArea::UpdateMarqueeSizeLabel(int width_size, int height_size)
{
    Configuration& config = Configuration::GetConfiguration();
    Units units = config.config_para.units;
    QString units_str;
    if(units == unit_mm){
        units_str = TranslationString::GetString().translation_str.CUSTOMSIZE_008;
        QString size = QString::number(common_utility.PixelToMm(this->MagnificationConversion(width_size, true), config.config_para.preview_immediately_resolution)) + " " + units_str;
        m_Width_label->setText(size);
        size = QString::number(common_utility.PixelToMm(this->MagnificationConversion(height_size, true), config.config_para.preview_immediately_resolution)) + " " + units_str;
        m_Height_label->setText(size);
    }else if(units == unit_inchi){
        units_str = TranslationString::GetString().translation_str.CUSTOMSIZE_009;
        double temp_size = common_utility.PixelToMm(this->MagnificationConversion(width_size, true), config.config_para.preview_immediately_resolution);
        temp_size = common_utility.MmToInchi(temp_size, config.config_para.preview_immediately_resolution);
        QString size = QString::number(temp_size / 100) + " " + units_str;
        m_Width_label->setText(size);
        temp_size = common_utility.PixelToMm(this->MagnificationConversion(height_size, true), config.config_para.preview_immediately_resolution);
        temp_size = common_utility.MmToInchi(temp_size, config.config_para.preview_immediately_resolution);
        size = QString::number(temp_size / 100) + " " + units_str;
        m_Height_label->setText(size);
    }
    if(m_rubberBand_){
        if (m_mqrqueeCreatedCallBack)
        {
            m_mqrqueeCreatedCallBack(m_rubberBand_->m_existMarquee, QRect(this->MagnificationConversion(m_rubberBand_->geometry().x(), true),
                                                                          this->MagnificationConversion(m_rubberBand_->geometry().y(), true),
                                                                          this->MagnificationConversion(m_rubberBand_->geometry().width(), true),
                                                                          this->MagnificationConversion(m_rubberBand_->geometry().height(), true)));
        }
        if (m_mqrqueeCreatedForDelButtonCallBack)
        {
            m_mqrqueeCreatedForDelButtonCallBack(m_rubberBand_->m_existMarquee);
        }
    }
}
double DrawingArea::MagnificationConversion(double input_num, bool toOriginal)
{
    int temp;
    if(toOriginal){
        input_num = input_num / m_adjustment_value;
    }else {
        input_num = input_num * m_adjustment_value;
    }
    temp = input_num * 10 + 5;
    return temp / 10;
}
QRect DrawingArea::GetMarqueeSize()
{
    if(m_rubberBand_ && m_rubberBand_->m_existMarquee){
        return m_rubberBand_->geometry();
    }else {
        return QRect(0, 0, 0, 0);
    }
}
bool DrawingArea::isExistedMarquee(void)
{
    if(!m_rubberBand_){
        return false;
    }
    return m_rubberBand_->m_existMarquee;
}
void DrawingArea::DeleteMarquee(void)
{
    if(m_rubberBand_){
        delete m_rubberBand_;
        m_rubberBand_ = nullptr;
    }
}
void DrawingArea::setMarqueeExist(bool existed)
{
    m_rubberBand_->m_existMarquee = existed;
}
