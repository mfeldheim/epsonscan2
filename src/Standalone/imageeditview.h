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
//  imageeditview.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef IMAGEEDITVIEW_H
#define IMAGEEDITVIEW_H 
#include <QMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <vector>
#include <QDrag>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <iostream>
#include <string>
#include <QImage>
#include <QObject>
#include "imageeditscene.h"
#include "mainwindow.h"
class ImageEditView : public QGraphicsView
{
public:
    ImageEditView(QWidget *parent = 0);
    void rotateLeft();
    void rotateRight();
    void setBackGround();
    void removeItem();
    void pdfDialog();
    bool imageIsSelected();
    void Initialize(ImageEditDialog* main);
    ImageEditScene m_scene;
    int getItemCount();
    std::list<imageEditInfo> *m_returnInfoList = NULL;
private:
    void setImageScene();
    void resizeScene();
    QPixmap imageTransparent(int imageSize);
    void detectImage(QPoint mousePosS);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void integrateMousePushFunction(QPoint mousePush);
    int selectedArea(QPoint mouse);
    QPoint setImagePosition(int imgCount);
    QPoint getImagePosition(int imgCount);
    void loadImage();
    void loadImage(QString filepath);
    void storeOriginalImages();
    void storeOriginalImages(QString filepath);
    void imageScaled();
    void makeAreas();
    void makeFrontAndBack();
    int numberOfImage();
    void sortImageOrder(int numberOfRange, int pushedRange, int releaseRange, int selectedItemNumber, int numberOfRow);
    void sortOriginalImageOrder();
    void sortImage();
    bool selectedFrontAndBack(QPoint mousePos);
    void setSmallImage(QPoint mousePos);
    void setBigImage(QPoint mousePos);
    void numberingImage();
    void showErrorMessage();
    int showRemoveMessage();
    void makeVerticalBar(QPoint mouse);
    void moveVerticalBar(QPoint mouse);
    void removeVerticalBar();
    void makeSelectedItemRectangle();
    void removeSelectedItemRectangle();
    void moveSelectedItemRectangle();
    int getImageRotation(int i);
    void rotateImage(int angle);
private slots:
    ImageEditDialog* m_MainWindow = NULL;
    QPoint m_mouseScenePos;
    QString m_fileName;
    QPixmap m_pixmap;
    int m_viewWidth = 0;
    int m_viewHeight = 0;
    int m_initialViewHeight = 0;
    QGraphicsRectItem* m_rectangle = NULL;
    QGraphicsRectItem* rectangleItem = NULL;
    QGraphicsPolygonItem* m_upperTriangle = NULL;
    QGraphicsPolygonItem* m_lowerTriangle = NULL;
    QGraphicsScene m_indicateBar;
    QGraphicsPixmapItem *m_item = NULL;
    QGraphicsPixmapItem *m_smallItem = NULL;
    QPixmap m_transparentedPixmap;
    QPixmap m_smallImage;
    QImage m_image;
    QImage m_originalImage;
    QGraphicsItem *m_myQGraphicsItem = NULL;
    const int m_scaleValue = 200;
    const int m_margin = 30;
    const int m_sideMargin = 20;
    int m_releaseSelectedRange = 0;
    int m_pushSelectedRange = 0;
    bool m_PressPointIsFront = true;
    int m_itemCount = 0;
    int m_selectedItemNumber= -1;
    QPoint m_pushedPosition;
    QPoint m_releasedPosition;
    std::vector< std::vector<int> > m_array;
    std::vector<int> m_sortOrder;
    QList<imageEditInfo> m_imageInfo;
    QList<QGraphicsItem *> m_orderItem;
    QList<QImage> m_originalImages;
    bool m_loadSuccess = false;
    int m_NumberOfRow = 0;
    std::vector< std::vector<int> > m_range;
    int m_presentSelectedRange = 0;
    int m_rangeSize = 0;
    bool m_itemIsEmpty = true;
    int y = 200;
    bool m_rectangleIsExist = false;
public:
    void getImageInfo();
    void integrateLoadFunction(std::list<imageEditInfo> list, std::list<imageEditInfo> *infoList);
};
#endif
