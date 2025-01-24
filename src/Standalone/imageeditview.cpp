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
//  imageeditview.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "imageeditview.h"
#include "imageeditdialog.h"
#include <QImageReader>
#include <QImageIOPlugin>
#include <QTimer>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
ImageEditView::ImageEditView(QWidget *parent) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
}
void ImageEditView::Initialize(ImageEditDialog* main)
{
    m_MainWindow = main;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
void ImageEditView::setBackGround()
{
    m_viewWidth = this->frameSize().width();
    m_viewHeight = this->frameSize().height();
    m_initialViewHeight = m_viewHeight;
    QPixmap pixmap;
    setScene(&m_scene);
    m_scene.setSceneRect(0,0,m_viewWidth,m_viewHeight);
    m_scene.clear();
    m_scene.addPixmap(pixmap);
}
void ImageEditView::makeVerticalBar(QPoint mouse)
{
    QPolygonF upperTriangle, lowerTriangle;
    QRectF rectangle;
    int thicknessOfBar = 2;
    for(int i=0; i < (int)m_range.size(); i++){
        if(i == 0 && mouse.x() > m_range[i][0] && mouse.x() < m_range[i][1]
                && mouse.y() > m_range[i][2] && mouse.y() < m_range[i][3])
        {
            rectangle = QRectF(0, m_range[i][2], thicknessOfBar, m_scaleValue);
            upperTriangle << QPointF(0 + thicknessOfBar / 2, m_range[i][2] + thicknessOfBar)
                          << QPointF(0 - thicknessOfBar, m_range[i][2])
                          << QPointF(0 + thicknessOfBar * 2, m_range[i][2]);
            lowerTriangle << QPointF(0 + thicknessOfBar / 2,m_range[i][3] - thicknessOfBar)
                          << QPointF(0 - thicknessOfBar, m_range[i][3])
                          << QPointF(0 + thicknessOfBar * 2, m_range[i][3]);
        }
        else if(m_range[i].size() > 4 && i % m_NumberOfRow == 0 && mouse.x() > m_range[i][4] && mouse.x() < m_range[i][5]
                                       && mouse.y() > m_range[i][6] && mouse.y() < m_range[i][7])
        {
            rectangle = QRectF(0, m_range[i][6], thicknessOfBar, m_scaleValue);
            upperTriangle << QPointF(0 + thicknessOfBar / 2, m_range[i][6] + thicknessOfBar)
                          << QPointF(0 - thicknessOfBar, m_range[i][6])
                          << QPointF(0 + thicknessOfBar * 2, m_range[i][6]);
            lowerTriangle << QPointF(0 + thicknessOfBar / 2, m_range[i][7] - thicknessOfBar)
                          << QPointF(0 - thicknessOfBar, m_range[i][7])
                          << QPointF(0 + thicknessOfBar * 2, m_range[i][7]);
        }
        else if(mouse.x()>m_range[i][0] && mouse.x()<m_range[i][1]
                && mouse.y()>m_range[i][2] && mouse.y()<m_range[i][3])
        {
            rectangle = QRectF((m_range[i][0]+m_range[i][1])/2,m_range[i][2],thicknessOfBar,m_scaleValue);
            upperTriangle << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar/2,m_range[i][2]+thicknessOfBar)
                          << QPointF((m_range[i][0]+m_range[i][1])/2-thicknessOfBar,m_range[i][2])
                          << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar*2,m_range[i][2]);
            lowerTriangle << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar/2,m_range[i][3]-thicknessOfBar)
                          << QPointF((m_range[i][0]+m_range[i][1])/2-thicknessOfBar,m_range[i][3])
                          << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar*2,m_range[i][3]);
        }
    }
    m_rectangle = m_scene.addRect(rectangle, QPen(Qt::white), QBrush(Qt::white));
    m_upperTriangle = m_scene.addPolygon(upperTriangle, QPen(Qt::white), QBrush(Qt::white));
    m_lowerTriangle = m_scene.addPolygon(lowerTriangle, QPen(Qt::white), QBrush(Qt::white));
}
void ImageEditView::moveVerticalBar(QPoint mouse)
{
    int thicknessOfBar = 2;
    QPolygonF upperTriangle, lowerTriangle;
    QRectF rectangle;
    for(int i=0; i< (int)m_range.size(); i++){
            if(i==0 && mouse.x()>m_range[i][0] && mouse.x()<m_range[i][1]
                    && mouse.y()>m_range[i][2] && mouse.y()<m_range[i][3])
            {
                rectangle = QRectF(0,m_range[i][2],thicknessOfBar,m_scaleValue);
                 upperTriangle << QPointF(0+thicknessOfBar/2,m_range[i][2]+thicknessOfBar)
                               << QPointF(0-thicknessOfBar,m_range[i][2])
                               << QPointF(0+thicknessOfBar*2,m_range[i][2]);
                 lowerTriangle << QPointF(0+thicknessOfBar/2,m_range[i][3]-thicknessOfBar)
                               << QPointF(0-thicknessOfBar,m_range[i][3])
                               << QPointF(0+thicknessOfBar*2,m_range[i][3]);
            }
            else if(m_range[i].size() > 4 && i % m_NumberOfRow == 0 && mouse.x()>m_range[i][4] && mouse.x()<m_range[i][5]
                                           && mouse.y()>m_range[i][6] && mouse.y()<m_range[i][7])
            {
                rectangle = QRectF(0,m_range[i][6],thicknessOfBar,m_scaleValue);
                upperTriangle << QPointF(0+thicknessOfBar/2,m_range[i][6]+thicknessOfBar)
                              << QPointF(0-thicknessOfBar,m_range[i][6])
                              << QPointF(0+thicknessOfBar*2,m_range[i][6]);
                lowerTriangle << QPointF(0+thicknessOfBar/2,m_range[i][7]-thicknessOfBar)
                              << QPointF(0-thicknessOfBar,m_range[i][7])
                              << QPointF(0+thicknessOfBar*2,m_range[i][7]);
            }
            else if(mouse.x()>m_range[i][0] && mouse.x()<m_range[i][1]
                    && mouse.y()>m_range[i][2] && mouse.y()<m_range[i][3])
            {
                rectangle = QRectF((m_range[i][0]+m_range[i][1])/2,m_range[i][2],thicknessOfBar,m_scaleValue);
                upperTriangle << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar/2,m_range[i][2]+thicknessOfBar)
                              << QPointF((m_range[i][0]+m_range[i][1])/2-thicknessOfBar,m_range[i][2])
                              << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar*2,m_range[i][2]);
                lowerTriangle << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar/2,m_range[i][3]-thicknessOfBar)
                              << QPointF((m_range[i][0]+m_range[i][1])/2-thicknessOfBar,m_range[i][3])
                              << QPointF((m_range[i][0]+m_range[i][1])/2+thicknessOfBar*2,m_range[i][3]);
            }
    }
    if(mouse.x() >= 0 && mouse.y() >= 0 && mapFromScene(mouse).x() < this->width() && mapFromScene(mouse).y() < this->height()){
        m_rectangle->setRect(rectangle);
        m_rectangle->setSelected(false);
        m_upperTriangle->setPolygon(upperTriangle);
        m_lowerTriangle->setPolygon(lowerTriangle);
        m_rectangle->show();
        m_upperTriangle->show();
        m_lowerTriangle->show();
    }
    else {
        m_rectangle->hide();
        m_upperTriangle->hide();
        m_lowerTriangle->hide();
    }
}
void ImageEditView::removeVerticalBar()
{
    if(m_rectangle->scene() != NULL){
        m_scene.removeItem(m_rectangle);
    }
    if(m_upperTriangle->scene() != NULL){
        m_scene.removeItem(m_upperTriangle);
    }
    if(m_lowerTriangle->scene() != NULL){
        m_scene.removeItem(m_lowerTriangle);
    }
}
void ImageEditView::makeSelectedItemRectangle()
{
    if(m_rectangleIsExist == false && m_scene.selectedItems().isEmpty() == false)
    {
        QRectF rectangle;
        rectangle = QRectF(0, 0, m_scaleValue, m_scaleValue);
        QColor brushColor;
        brushColor.setRgb(0,0,255,90);
        QColor penColor;
        penColor.setRgb(255,255,255);
        rectangleItem = m_scene.addRect(rectangle,penColor,brushColor);
        rectangleItem->setPos(((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().x() - (m_scaleValue - ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().width())/2,
                ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().y() - (m_scaleValue - ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().height())/2
                );
        rectangleItem->setSelected(false);
        m_rectangleIsExist = true;
    }
}
void ImageEditView::moveSelectedItemRectangle()
{
    rectangleItem->setPos(setImagePosition(m_selectedItemNumber));
}
void ImageEditView::removeSelectedItemRectangle()
{
    if(m_rectangleIsExist == true)
    {
        m_scene.removeItem(rectangleItem);
        m_rectangleIsExist = false;
    }
}
void ImageEditView::integrateLoadFunction(std::list<imageEditInfo> list, std::list<imageEditInfo> *returnInfoList)
{
    auto save_path = list.begin();
    for(int i = 0; i < (int)list.size(); i++)
    {
        imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
        std::string temp_str = temp_edit_info.file_path;
        loadImage(QString::fromStdString(string(temp_str)));
        if(m_loadSuccess == true)
        {
            imageScaled();
            setImageScene();
            makeAreas();
            makeFrontAndBack();
            numberingImage();
            rotateImage(temp_edit_info.angle);
        }
        ++save_path;
    }
    m_returnInfoList = returnInfoList;
}
void ImageEditView::loadImage(QString filepath)
{
    try
    {
        m_fileName = filepath;
        m_image.load(m_fileName);
        if(m_image.isNull() == true){
            m_loadSuccess = false;
            throw 1;
        }
        m_originalImage = m_image;
        storeOriginalImages(filepath);
        m_loadSuccess = true;
    } catch (int i)
    {
        if(i == 1){
            m_loadSuccess = false;
        }
    }
}
void ImageEditView::storeOriginalImages()
{
    m_originalImages.append(m_originalImage);
}
void ImageEditView::storeOriginalImages(QString filepath)
{
    m_originalImages.append(m_originalImage);
    imageEditInfo info;
    info.file_path = filepath.toStdString();
    info.angle = 0;
    m_imageInfo.append(info);
}
void ImageEditView::imageScaled()
{
    m_image = m_image.scaledToWidth(m_scaleValue);
    if(m_image.height() > 200)
    {
        m_image = m_image.scaledToHeight(m_scaleValue);
    }
}
void ImageEditView::setImageScene()
{
    m_pixmap=QPixmap::fromImage(m_image);
    try {
        m_item = m_scene.addPixmap(m_pixmap);
        m_item->setOffset(setImagePosition(getItemCount() - 1));
        m_item->setFlags(QGraphicsItem::ItemIsSelectable);
        resizeScene();
        if(m_item == nullptr){
            throw 1;
        }
    } catch (int i) {
    }
}
void ImageEditView::resizeScene()
{
    int numberOfLines = ((getItemCount() - 1) / m_NumberOfRow) + 1;
    if(numberOfLines <= 2)
    {
        m_viewHeight = m_initialViewHeight;
    }else {
        m_viewHeight = m_initialViewHeight + ((numberOfLines-2) * (m_scaleValue + m_margin)) - m_margin;
    }
    m_scene.setSceneRect(0,0,m_viewWidth, m_viewHeight);
}
QPoint ImageEditView::setImagePosition(int imgCount)
{
    int i = 0;
    while (1)
    {
        if(((m_scaleValue + m_margin) * i) + (m_scaleValue - m_item->pixmap().width()) / 2 + m_scaleValue > m_viewWidth)
        {
            m_NumberOfRow = i;
            break;
        }
        i++;
    }
    QPoint ImagePos;
    if(m_NumberOfRow != 0)
    {
        ImagePos.setX(((m_scaleValue+m_margin)*(imgCount % m_NumberOfRow))+(m_scaleValue - m_item->pixmap().width())/2);
        ImagePos.setY(((m_scaleValue+m_margin)*(imgCount / m_NumberOfRow))+(m_scaleValue - m_item->pixmap().height())/2);
    }
    return ImagePos;
}
QPoint ImageEditView::getImagePosition(int imgCount)
{
    QPoint ImagePos;
    ImagePos = setImagePosition(imgCount);
    ImagePos.setX(mapFromScene(ImagePos).x());
    ImagePos.setY(mapFromScene(ImagePos).y());
    return ImagePos;
}
void ImageEditView::makeAreas()
{
    m_range.resize(getItemCount() + 1);
    for(int i =0; i < (getItemCount() + 1); i++)
    {
        m_range[i].resize(4);
        if(i == 0)
        {
            m_range[i][0] = 0;
            m_range[i][1] = m_scaleValue / 2;
            m_range[i][2] = 0;
            m_range[i][3] = m_scaleValue;
        }
        if(i % m_NumberOfRow == 0 && i / m_NumberOfRow > 0)
        {
            m_range[i].resize(8);
            m_range[i][0] = m_range[(i-1) % (m_NumberOfRow + 1)][1];
            m_range[i][1] = m_range[i % (m_NumberOfRow + 1)][0] + m_scaleValue + m_margin;
            m_range[i][2] = (m_scaleValue + m_margin)* ((i) / (m_NumberOfRow + 1));
            m_range[i][3] = m_range[i][2] + m_scaleValue;
            m_range[i][4] = 0;
            m_range[i][5] = m_scaleValue / 2;
            m_range[i][6] = (m_scaleValue + m_margin)* ((i) / (m_NumberOfRow));
            m_range[i][7] = m_range[i][6] + m_scaleValue;
        }
        if(i % m_NumberOfRow == 1 && i / m_NumberOfRow > 0)
        {
            m_range[i][0] = m_range[i-1][5];
            m_range[i][1] = m_range[i][0] + m_scaleValue + m_margin;
            m_range[i][2] = m_range[i-1][6];
            m_range[i][3] = m_range[i][2] + m_scaleValue;
        }
        else if(i > 0)
        {
            m_range[i][0] = m_range[i-1][1];
            m_range[i][1] = m_range[i][0] + m_scaleValue + m_margin;
            m_range[i][2] = m_range[i-1][2];
            m_range[i][3] = m_range[i][2] + m_scaleValue;
        }
    }
}
void ImageEditView::makeFrontAndBack()
{
    m_array.resize((getItemCount() + 1) * 2);
    for( int i = 0; i < (getItemCount() + 1) * 2; i++)
    {
        m_array[i].resize(2);
    }
    for (int i = 0; i < (getItemCount() + 1) * 2; i++)
    {
        if(i == 0)
        {
            m_array[i][0] = 0;
            m_array[i][1] = m_scaleValue / 2;
        }
        else if(i > 0)
        {
            m_array[i][0] = m_array[i-1][1];
            m_array[i][1] = m_array[i][0] + (m_scaleValue + m_margin) / 2;
        }
    }
}
bool ImageEditView::selectedFrontAndBack(QPoint mousePos)
{
    bool PressPointIsFront = false;
    try {
        if(m_scene.selectedItems().isEmpty() == true)
        {
            throw 1;
        }
        for(int i=0;i < getItemCount() * 2;i++)
        {
            if(mousePos.x() > m_array[i][0] && mousePos.x() < m_array[i][1] && i % 2 == 0)
            {
                PressPointIsFront = true;
            }
            else if(mousePos.x() < m_array[i][1] && mousePos.x() > m_array[i+1][0] && i % 2 == 1)
            {
                PressPointIsFront = false;
            }
        }
    } catch (int i) {
    }
    return PressPointIsFront;
}
void ImageEditView::setSmallImage(QPoint mousePos)
{
    imageTransparent(80);
    m_smallItem = m_scene.addPixmap(m_smallImage);
    m_smallItem->setOffset(mousePos);
}
void ImageEditView::setBigImage(QPoint mousePos)
{
    imageTransparent(150);
    m_smallItem = m_scene.addPixmap(m_smallImage);
    m_smallItem->setOffset(mousePos);
}
int ImageEditView::selectedArea(QPoint mouse){
    int SelectedRange = -1;
    for(int i =0; i< (int)m_range.size(); i++){
        if(mouse.x() > m_range[i][0] && mouse.x() <= m_range[i][1]
                && mouse.y() > m_range[i][2] && mouse.y() <= m_range[i][3])
        {
            SelectedRange = i;
        }
        if(i % m_NumberOfRow == 0 && i / m_NumberOfRow > 0
            && mouse.x() > m_range[i][4] && mouse.x() <= m_range[i][5]
            && mouse.y() > m_range[i][6] && mouse.y() <= m_range[i][7])
        {
            SelectedRange = i;
        }
    }
    return SelectedRange;
}
void ImageEditView::detectImage(QPoint mousePos)
{
    for(int i=0;i<getItemCount();i++)
    {
        m_scene.items()[i]->setSelected(false);
    }
    if(this->items(mapFromScene(mousePos).x(), mapFromScene(mousePos).y(),1,1).count() > 0)
    {
        ((QGraphicsPixmapItem*)this->items(mapFromScene(mousePos).x(), mapFromScene(mousePos).y(),1,1)[0])->setSelected(true);
        m_item = ((QGraphicsPixmapItem*)this->items(mapFromScene(mousePos).x(), mapFromScene(mousePos).y(),1,1)[0]);
        for(int i=0;i<getItemCount();i++){
            if((int)(m_item->offset().x()) ==
                    ((int)((QGraphicsPixmapItem*)this->items(getImagePosition(i).x()+100,getImagePosition(i).y()+100,1,1)[0])->offset().x()) &&
                    (int)(m_item->offset().y()) ==
                    ((int)((QGraphicsPixmapItem*)this->items(getImagePosition(i).x()+100,getImagePosition(i).y()+100,1,1)[0])->offset().y())
                    )
            {
                m_selectedItemNumber = i;
            }
        }
    }
}
void ImageEditView::numberingImage()
{
    m_orderItem.clear();
    for(int i=0;i<getItemCount();i++)
    {
        if(this->items(getImagePosition(i).x()+(m_scaleValue/2),getImagePosition(i).y()+(m_scaleValue/2),1,1).isEmpty() == false)
        {
            m_orderItem.append(this->items(getImagePosition(i).x()+(m_scaleValue/2),getImagePosition(i).y()+(m_scaleValue/2),1,1)[0]);
        }
    }
}
void ImageEditView::sortImageOrder(int NumberOfItems, int pushedRange, int releaseRange, int selectedItemNumber, int numberOfRow)
{
    bool once = true;
    int sortOrder[NumberOfItems];
    for(int i=0; i< NumberOfItems; i++)
    {
        sortOrder[i] = i;
    }
    for(int i=0; i< NumberOfItems; i++)
    {
        if(releaseRange > pushedRange)
        {
            for(i=0;i<selectedItemNumber;i++)
            {
                sortOrder[i] = i;
            }
            for(i=selectedItemNumber;i<releaseRange-1;i++)
            {
                sortOrder[i] = i+1;
            }
            if(i==releaseRange-1)
            {
                sortOrder[i] = selectedItemNumber;
            }
            for(i=releaseRange;i<NumberOfItems;i++)
            {
                sortOrder[i] = i;
            }
        }
        else if(releaseRange < pushedRange)
        {
            for(i=0;i<releaseRange;i++)
            {
                sortOrder[i] = i;
            }
            if(i==releaseRange)
            {
                sortOrder[i] = selectedItemNumber;
            }
            for(i=releaseRange+1;i<selectedItemNumber+1;i++)
            {
                sortOrder[i] = i-1;
            }
            for(i=selectedItemNumber+1;i<NumberOfItems;i++)
            {
                sortOrder[i] = i;
            }
        }
    }
    m_sortOrder.clear();
    m_sortOrder.resize(NumberOfItems);
    for(int i=0; i<NumberOfItems; i++)
    {
        m_sortOrder[i] = sortOrder[i];
        if(m_selectedItemNumber == sortOrder[i] && once == true)
        {
            m_selectedItemNumber = i;
            once = false;
        }
    }
    sortOriginalImageOrder();
    sortImage();
}
void ImageEditView::sortOriginalImageOrder()
{
    QList<QImage> copy_originalImages;
    copy_originalImages = m_originalImages;
    for(int i=0; i<m_originalImages.size();i++)
    {
        m_originalImages[i] = copy_originalImages[m_sortOrder[i]];
    }
    QList<imageEditInfo> copy_imageInfo;
    copy_imageInfo = m_imageInfo;
    for(int i=0; i<m_imageInfo.size();i++)
    {
        m_imageInfo[i] = copy_imageInfo[m_sortOrder[i]];
    }
}
void ImageEditView::sortImage()
{
    numberingImage();
    for(int i = 0; i < getItemCount(); i++)
    {
        m_item = ((QGraphicsPixmapItem*) m_orderItem[m_sortOrder[i]]);
        ((QGraphicsPixmapItem*) m_orderItem[m_sortOrder[i]])->setOffset(setImagePosition(i));
        ((QGraphicsPixmapItem*) m_orderItem[m_sortOrder[i]])->setTransformOriginPoint(setImagePosition(i).x()
                                         + ((QGraphicsPixmapItem*)m_orderItem[m_sortOrder[i]])->pixmap().width()/2
                ,setImagePosition(i).y() + ((QGraphicsPixmapItem*)m_orderItem[m_sortOrder[i]])->pixmap().height()/2);
    }
}
void ImageEditView::removeItem()
{
    int sortOrder[getItemCount()];
    removeSelectedItemRectangle();
    numberingImage();
    try
    {
        if(m_scene.selectedItems().isEmpty() == true)
        {
            throw 1;
        }
        m_scene.removeItem(m_orderItem[m_selectedItemNumber]);
        m_scene.clearSelection();
        for(int i = 0; i < getItemCount() +1; i++)
        {
            if(i < m_selectedItemNumber)
            {
                sortOrder[i] = i;
            }
            else if(i >= m_selectedItemNumber)
            {
                m_item = (QGraphicsPixmapItem*)m_orderItem[i];
                m_item->setOffset(setImagePosition(i - 1));
                m_item->setTransformOriginPoint(m_item->offset().x() + m_item->pixmap().width() / 2,
                                                m_item->offset().y() + m_item->pixmap().height() / 2);
            }
        }
        m_sortOrder.clear();
        m_sortOrder.resize(getItemCount());
        for(int i = 0; i < getItemCount(); i++)
        {
            m_sortOrder[i] = sortOrder[i];
        }
        m_range.resize(m_range.size() - 1);
        m_originalImages.removeAt(m_selectedItemNumber);
        m_imageInfo.removeAt(m_selectedItemNumber);
        resizeScene();
    } catch (int i) {
    }
}
QPixmap ImageEditView::imageTransparent(int imageSize)
{
    QGraphicsPixmapItem* originalPixmapItem = (QGraphicsPixmapItem*)m_scene.selectedItems()[0];
    QPixmap originalPixmap = originalPixmapItem->pixmap();
    QImage originalImage = originalPixmap.toImage();
    int viewWidth = originalImage.width();
    int viewHeight = originalImage.height();
    QImage image(viewWidth, viewHeight,QImage::Format_ARGB32);
    for(int ix=0;ix<viewWidth;ix++)
    {
        for(int iy=0; iy<viewHeight; iy++)
        {
            int red = qRed(originalImage.pixel(ix,iy));
            int green = qGreen(originalImage.pixel(ix,iy));
            int blue = qBlue(originalImage.pixel(ix,iy));
            int alpha = 40;
            QColor color;
            color.setRgb(red,green,blue,alpha);
            image.setPixel(ix, iy, qRgba(red, green, blue, alpha));
            image.pixel(ix,iy);
        }
    }
    m_transparentedPixmap=QPixmap::fromImage(image);
    m_smallImage = m_transparentedPixmap.scaledToHeight(imageSize);
    return m_smallImage;
}
void ImageEditView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        removeSelectedItemRectangle();
    }
    if(event->button() == Qt::LeftButton)
    {
        m_mouseScenePos = mapToScene(event->pos()).toPoint();
        try {
            m_pushedPosition = m_mouseScenePos;
            m_pushSelectedRange = selectedArea(m_mouseScenePos);
            detectImage(m_mouseScenePos);
            if(m_scene.selectedItems().isEmpty() == true || getItemCount() == 0)
            {
                bool i = m_scene.selectedItems().isEmpty();
                throw 1;
            }
            setSmallImage(m_mouseScenePos);
            makeVerticalBar(m_pushedPosition);
        } catch (int i) {
        }
    }
    makeSelectedItemRectangle();
}
void ImageEditView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::NoButton){
    }
    if(event->buttons() == Qt::LeftButton){
        m_mouseScenePos = mapToScene(event->pos()).toPoint();
        m_presentSelectedRange = selectedArea(m_mouseScenePos);
        try {
            if(m_scene.selectedItems().isEmpty() == true || getItemCount() == 0)
            {
                throw 1;
            }
            m_smallItem->setOffset(m_mouseScenePos.x(), m_mouseScenePos.y());
            moveVerticalBar(m_mouseScenePos);
        } catch (int i) {
        }
    }
}
void ImageEditView::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouseScenePos = mapToScene(event->pos()).toPoint();
    removeSelectedItemRectangle();
    try {
        if(m_scene.selectedItems().isEmpty() == true || getItemCount() == 0 ||
                mapFromScene(m_mouseScenePos).x() > this->width() || mapFromScene(m_mouseScenePos).y() > this->height() ||
                mapFromScene(m_mouseScenePos).x() < 0 || mapFromScene(m_mouseScenePos).y() < 0)
        {
            if(m_mouseScenePos.x() > this->width() || m_mouseScenePos.y() > this->height() ||
                    m_mouseScenePos.x() < 0 || m_mouseScenePos.y() < 0){
                m_scene.removeItem(m_smallItem);
                removeVerticalBar();
            }
            throw 1;
        }
        m_releasedPosition = m_mouseScenePos;
        if(m_smallItem->scene() != NULL){
            m_scene.removeItem(m_smallItem);
        }
        removeVerticalBar();
        m_releaseSelectedRange = selectedArea(m_releasedPosition);
        if(m_releaseSelectedRange == -1){
            m_releaseSelectedRange = m_pushSelectedRange;
        }
        sortImageOrder(getItemCount(), m_pushSelectedRange, m_releaseSelectedRange, m_selectedItemNumber, m_NumberOfRow);
    } catch (int i) {
    }
    makeSelectedItemRectangle();
    if(m_scene.selectedItems().isEmpty() == false){
        m_MainWindow->grayOut(true);
    }
    else{
        m_MainWindow->grayOut(false);
    }
    if(getItemCount() == 0){
        m_MainWindow->saveButtonGrayOut(false);
    }
    else {
        m_MainWindow->saveButtonGrayOut(true);
    }
}
void ImageEditView::mouseDoubleClickEvent(QMouseEvent *event)
{
}
bool ImageEditView::imageIsSelected()
{
    if(m_scene.selectedItems().isEmpty() == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void ImageEditView::rotateImage(int angle)
{
    if(angle != 0){
        m_myQGraphicsItem = this->items()[0];
        m_myQGraphicsItem->setTransformOriginPoint(((QGraphicsPixmapItem*)m_myQGraphicsItem)->offset().x() +
                ((QGraphicsPixmapItem*)m_myQGraphicsItem)->pixmap().width()/2
                , ((QGraphicsPixmapItem*)m_myQGraphicsItem)->offset().y() +
                ((QGraphicsPixmapItem*)m_myQGraphicsItem)->pixmap().height()/2);
        m_myQGraphicsItem->setRotation(angle);
    }
}
void ImageEditView::rotateLeft()
{
    if(m_scene.selectedItems().isEmpty() == false){
        m_myQGraphicsItem = m_scene.selectedItems()[0];
        m_myQGraphicsItem->setTransformOriginPoint(((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().x() +
                ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().width()/2
                , ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().y() +
                ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().height()/2);
        m_myQGraphicsItem->setRotation(m_myQGraphicsItem->rotation() - 90);
    }
}
void ImageEditView::rotateRight()
{
    if(m_scene.selectedItems().isEmpty() == false){
        m_myQGraphicsItem = m_scene.selectedItems()[0];
        m_myQGraphicsItem->setTransformOriginPoint(((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().x() +
                ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().width()/2
                , ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->offset().y() +
                ((QGraphicsPixmapItem*)m_scene.selectedItems()[0])->pixmap().height()/2);
        m_myQGraphicsItem->setRotation(m_myQGraphicsItem->rotation() + 90);
    }
}
void ImageEditView::showErrorMessage(){
    QMessageBox msgBox(this);
    msgBox.setText(tr("画像ファイルを読み込めませんでした"));
    msgBox.setWindowTitle(tr("Couldn't open the image"));
    msgBox.exec();
}
int ImageEditView::getItemCount()
{
    int itemCount = 0;
    if(m_rectangleIsExist == true)
    {
        itemCount = m_scene.items().count() - 2;
    }
    else {
        itemCount = m_scene.items().count() - 1;
    }
    return itemCount;
}
void ImageEditView::getImageInfo()
{
    m_returnInfoList->clear();
    for (int i=0;i<getItemCount();i++)
    {
        m_returnInfoList->push_back(m_imageInfo.at(i));
    }
}
int ImageEditView::getImageRotation(int i){
    if((int)itemAt(getImagePosition(i).x() +100,getImagePosition(i).y()+100)->flags() != QGraphicsItem::ItemIsSelectable){
        return items( getImagePosition(i).x() +100, getImagePosition(i).y()+100)[1]->rotation();
    } else {
        return items( getImagePosition(i).x() +100, getImagePosition(i).y()+100)[0]->rotation();
    }
}
void ImageEditView::pdfDialog()
{
    QList<imageEditInfo> copy_imageInfo;
    copy_imageInfo = m_imageInfo;
    m_imageInfo.clear();
    for(int i=0; i < getItemCount(); i++)
    {
        imageEditInfo info;
        info.file_path = copy_imageInfo.at(i).file_path;
        info.angle = getImageRotation(i);
        m_imageInfo.append(info);
    }
    getImageInfo();
    for (int i=0;i<getItemCount();i++)
    {
    }
}
