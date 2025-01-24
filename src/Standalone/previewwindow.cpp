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
//  previewwindow.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "previewwindow.h"
#include "PathUtils.h"
#include "saveimagepathlist.h"
#include "focuspositionsettingdialog.h"
#include "mainwindow.h"
#define ADJUSTMENT_VALUE 50
PreviewWindow::PreviewWindow(Supervisor* sv, QWidget *parent) : QMainWindow(parent),
    m_DrawFrame(nullptr),
    m_CloseFrame(nullptr),
    m_SizeFrame(nullptr),
    m_WidthIconImageLabel(nullptr),
    m_HeightIconImageLabel(nullptr),
    m_CloseButton(nullptr),
    m_DeleteButton(nullptr),
    m_FocusPositionButton(nullptr),
    m_graphicsView(nullptr),
    m_main_window(nullptr),
    m_Scene_(nullptr)
{
    m_sv = sv;
}
void PreviewWindow::initialize(MainWindow* window)
{
    m_main_window = window;
    if(m_main_window->m_viewPreviewWindow == false){
        m_main_window->setFixedWidth(m_main_window->width()*2);
        m_DrawFrame = new QFrame(m_main_window);
        m_DrawFrame->setObjectName("frame");
        m_DrawFrame->setStyleSheet("#frame {background-color:gray;}");
        m_DrawFrame->setGeometry(INIT_MAINWINDOW_WIDTH+(ADJUSTMENT_VALUE/2), ADJUSTMENT_VALUE/2+5, INIT_MAINWINDOW_WIDTH-ADJUSTMENT_VALUE, INIT_MAINWINDOW_HEIGHT-(ADJUSTMENT_VALUE*1.5));
        m_DrawFrame->show();
        m_CloseFrame = new QFrame(m_main_window);
        m_CloseFrame->setObjectName("frame");
        m_CloseFrame->setStyleSheet("#frame {background-color:dimgray;}");
        m_CloseFrame->setGeometry(INIT_MAINWINDOW_WIDTH+(ADJUSTMENT_VALUE/2), ADJUSTMENT_VALUE/2+5, INIT_MAINWINDOW_WIDTH-ADJUSTMENT_VALUE, ADJUSTMENT_VALUE-10);
        m_CloseFrame->show();
        m_SizeFrame = new QFrame(m_main_window);
        m_SizeFrame->setObjectName("frame");
        m_SizeFrame->setStyleSheet("#frame {background-color:dimgray;}");
        m_SizeFrame->setGeometry(INIT_MAINWINDOW_WIDTH+(ADJUSTMENT_VALUE/2), INIT_MAINWINDOW_HEIGHT - (ADJUSTMENT_VALUE*1.5)+5, INIT_MAINWINDOW_WIDTH-ADJUSTMENT_VALUE, ADJUSTMENT_VALUE-10);
        m_SizeFrame->show();
        std::string strIconPath = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/btn_preview_mark_width.png");
        QImage WidthIconImage;
        WidthIconImage.load( strIconPath.c_str() );
        m_WidthIconImageLabel = new QLabel(m_SizeFrame);
        m_WidthIconImageLabel->setGeometry(m_SizeFrame->width()/2.2 + m_SizeFrame->width()/20-15, 10, WidthIconImage.width(), WidthIconImage.height());
        QPixmap pWMap = QPixmap::fromImage( WidthIconImage );
        pWMap = pWMap.scaled( m_WidthIconImageLabel->size() );
        m_WidthIconImageLabel->setPixmap( pWMap );
        m_WidthIconImageLabel->show();
        m_WidthSizeLabel = new QLabel(m_SizeFrame);
        m_WidthSizeLabel->setGeometry(m_SizeFrame->width()/2.2 + m_SizeFrame->width()/20 + m_WidthIconImageLabel->width()-10, 10, 80, WidthIconImage.height());
        QPalette pal = m_WidthSizeLabel->palette();
        pal.setColor(QPalette::Foreground, QColor("#ffffff"));
        m_WidthSizeLabel->setPalette(pal);
        m_WidthSizeLabel->show();
        strIconPath = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/btn_preview_mark_height.png");
        QImage HeightIconImage;
        HeightIconImage.load( strIconPath.c_str() );
        m_HeightIconImageLabel = new QLabel(m_SizeFrame);
        m_HeightIconImageLabel->setGeometry(m_SizeFrame->width()/2.2 + m_SizeFrame->width()/4, 10, HeightIconImage.width(), HeightIconImage.height());
        QPixmap pHMap = QPixmap::fromImage( HeightIconImage );
        pHMap = pHMap.scaled( m_HeightIconImageLabel->size() );
        m_HeightIconImageLabel->setPixmap( pHMap );
        m_HeightIconImageLabel->show();
        m_HeightSizeLabel = new QLabel(m_SizeFrame);
        m_HeightSizeLabel->setGeometry(m_SizeFrame->width()/2.2 + m_SizeFrame->width()/4 + HeightIconImage.width() + 5, 10, 100, HeightIconImage.height());
        m_HeightSizeLabel->setPalette(pal);
        m_HeightSizeLabel->show();
        strIconPath = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/btn_preview_close.png");
        QImage CloseIconImage;
        CloseIconImage.load( strIconPath.c_str() );
        m_CloseButton = new QPushButton(m_CloseFrame);
        m_CloseButton->setFlat(true);
        m_CloseButton->setGeometry(m_SizeFrame->width() - CloseIconImage.width() - 10, 8, CloseIconImage.width(), CloseIconImage.height());
        m_CloseButton->setIconSize(CloseIconImage.size());
        QPixmap pCMap = QPixmap::fromImage( CloseIconImage );
        pCMap = pCMap.scaled( m_CloseButton->size() );
        m_CloseButton->setIcon( pCMap );
        m_CloseButton->show();
        connect(m_CloseButton, SIGNAL(clicked()), this, SLOT(on_Close_Button_pressed()));
        strIconPath = EPSON_INSTALL_PATH;
        std::string strIconPath_disabled = EPSON_INSTALL_PATH;
        ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/btn_marquee_delete@2x.png");
        ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath_disabled, strIconPath_disabled, "Resources/Icons/btn_marquee_delete_disabled@2x.png");
        QImage DeleteIconImage;
        DeleteIconImage.load( strIconPath.c_str() );
        m_DeleteButton = new QPushButton(m_DrawFrame);
        m_DeleteButton->setFlat(true);
        m_DeleteButton->setGeometry(3, 50, DeleteIconImage.width(), DeleteIconImage.height());
        m_DeleteButton->setIconSize(DeleteIconImage.size());
        QIcon ico;
        ico.addPixmap(QPixmap(strIconPath.c_str()), QIcon::Normal);
        ico.addPixmap(QPixmap(strIconPath_disabled.c_str()), QIcon::Disabled);
        m_DeleteButton->setIcon( ico );
        m_DeleteButton->show();
        connect(m_DeleteButton, SIGNAL(clicked()), this, SLOT(on_Delete_Button_pressed()));
        m_DeleteButton->setEnabled(false);
        if(m_sv->device_data.focusPosition.capability.supportLevel == kSDISupportLevelAvailable)
        {
            strIconPath = EPSON_INSTALL_PATH;
            ES_CMN_FUNCS::PATH::ES_CombinePath(strIconPath, strIconPath, "Resources/Icons/indicator_focus_adjusted@2x.png");
            QImage FocusPositionIconImage;
            FocusPositionIconImage.load( strIconPath.c_str() );
            m_FocusPositionButton = new QPushButton(m_DrawFrame);
            m_FocusPositionButton->setFlat(true);
            m_FocusPositionButton->setGeometry(3, 100, FocusPositionIconImage.width() * 1.5, FocusPositionIconImage.height() * 1.5);
            QSize focusIconSize;
            focusIconSize.setWidth(FocusPositionIconImage.width() * 1.5);
            focusIconSize.setHeight(FocusPositionIconImage.height() * 1.5);
            m_FocusPositionButton->setIconSize(focusIconSize);
            QIcon ico_1;
            ico_1.addPixmap(QPixmap(strIconPath.c_str()), QIcon::Normal);
            m_FocusPositionButton->setIcon( ico_1 );
            m_FocusPositionButton->setIconSize(focusIconSize);
            m_FocusPositionButton->show();
            connect(m_FocusPositionButton, SIGNAL(clicked()), this, SLOT(on_FocusPosition_Button_pressed()));
            m_FocusPositionButton->setEnabled(true);
        }
    }
}
DrawingArea* PreviewWindow::getDrawingArea(void)
{
    return m_graphicsView;
}
void PreviewWindow::DeleteMarquee()
{
    getDrawingArea()->DeleteMarquee();
    this->m_DeleteButton->setEnabled(false);
}
bool PreviewWindow::DrawImage()
{
    if(!m_main_window->m_viewPreviewWindow){
        m_graphicsView = new DrawingArea(m_DrawFrame);
        m_graphicsView->SetMarqueeSizeLabel(m_WidthSizeLabel, m_HeightSizeLabel);
        m_graphicsView->SetMarqueeCreatedForDelButtonCallBack(std::bind(
                                                                  &PreviewWindow::MarqueeCreated,
                                                                  this,
                                                                  std::placeholders::_1));
    }
    auto save_path = SaveImagePathList::save_image_path_list.begin();
    imageEditInfo temp_edit_info = (imageEditInfo)*save_path;
    std::string temp_str = temp_edit_info.file_path;
    if(m_preview_image.load((const char*)temp_str.c_str())){
        this->PreviewImageAdjustment();
        double adjustment_width = m_graphicsView->MagnificationConversion(m_preview_image.width(), false);
        double adjustment_height = m_graphicsView->MagnificationConversion(m_preview_image.height(), false);
        m_graphicsView->setFrameStyle(QFrame::NoFrame);
        m_graphicsView->setGeometry(this->PreviewImagePositionAdjustment(adjustment_width, adjustment_height).x(), this->PreviewImagePositionAdjustment(adjustment_width, adjustment_height).y(), adjustment_width, adjustment_height);
        if(m_Scene_ == nullptr){
            m_Scene_ = new QGraphicsScene();
        }
        m_graphicsView->setScene(m_Scene_);
        m_Scene_->clear();
        QPixmap pixmap = QPixmap::fromImage(m_preview_image);
        m_Scene_->addPixmap(pixmap.scaled(m_graphicsView->width()-(m_graphicsView->frameWidth()*2), m_graphicsView->height()-(m_graphicsView->frameWidth()*2), Qt::KeepAspectRatio,Qt::FastTransformation));
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->show();
    }else {
        std::cout << "image load error!" << std::endl;
        return false;
    }
    SaveImagePathList::save_image_path_list.clear();
    m_graphicsView->UpdateMarqueeSizeLabel(m_graphicsView->MagnificationConversion(m_preview_image.width(), false), m_graphicsView->MagnificationConversion(m_preview_image.height(), false));
    return true;
}
void PreviewWindow::PreviewImageAdjustment(void)
{
    bool over_width = false;
    bool over_height = false;
    if(REFERENCE_WIDTH < m_preview_image.width()){
        over_width = true;
    }
    if(REFERENCE_HEIGHT < m_preview_image.height()){
        over_height = true;
    }
    if(over_width && !over_height){
        m_graphicsView->m_adjustment_value = (double)REFERENCE_WIDTH / (double)m_preview_image.width();
    }else if(!over_width && over_height){
        m_graphicsView->m_adjustment_value = (double)REFERENCE_HEIGHT / (double)m_preview_image.height();
    }else if(over_width && over_height){
        double x_diff = (double)REFERENCE_WIDTH / (double)m_preview_image.width();
        double y_diff = (double)REFERENCE_HEIGHT / (double)m_preview_image.height();
        if(x_diff < y_diff){
            m_graphicsView->m_adjustment_value = x_diff;
        }else {
            m_graphicsView->m_adjustment_value = y_diff;
        }
    }else {
        m_graphicsView->m_adjustment_value = 1;
    }
}
QPoint PreviewWindow::PreviewImagePositionAdjustment(double preview_img_width, double preview_img_height)
{
    QPoint start_pos;
    bool under_width = false;
    bool under_height = false;
    if(REFERENCE_WIDTH > preview_img_width){
        under_width = true;
    }
    if(REFERENCE_HEIGHT > preview_img_height){
        under_height = true;
    }
    if(under_width && !under_height){
        start_pos.setX((REFERENCE_WIDTH - preview_img_width) / 2 + REFERENCE_POSX);
        start_pos.setY(REFERENCE_POSY);
    }else if(!under_width && under_height){
        start_pos.setX(REFERENCE_POSX);
        start_pos.setY((REFERENCE_HEIGHT - preview_img_height) / 2 + REFERENCE_POSY);
    }else if(under_width && under_height){
        start_pos.setX((REFERENCE_WIDTH - preview_img_width) / 2 + REFERENCE_POSX);
        start_pos.setY((REFERENCE_HEIGHT - preview_img_height) / 2 + REFERENCE_POSY);
    }else {
        start_pos.setX(REFERENCE_POSX);
        start_pos.setY(REFERENCE_POSY);
    }
    return start_pos;
}
bool PreviewWindow::on_Close_Button_pressed(bool Confirm)
{
    bool close = false;
    if(Confirm == true){
        close = this->ResetMessageBox();
    }else {
        close = true;
    }
    if(close){
        if(m_graphicsView){
            delete m_graphicsView;
            m_graphicsView = nullptr;
        }
        if(m_Scene_){
            delete m_Scene_;
            m_Scene_ = nullptr;
        }
        if(m_DeleteButton){
            delete m_DeleteButton;
            m_DeleteButton = nullptr;
        }
        if(m_CloseButton){
            delete m_CloseButton;
            m_CloseButton = nullptr;
        }
        if(m_HeightIconImageLabel){
            delete m_HeightIconImageLabel;
            m_HeightIconImageLabel = nullptr;
        }
        if(m_WidthIconImageLabel){
            delete m_WidthIconImageLabel;
            m_WidthIconImageLabel = nullptr;
        }
        if(m_SizeFrame){
            delete m_SizeFrame;
            m_SizeFrame = nullptr;
        }
        if(m_DrawFrame){
            delete m_DrawFrame;
            m_DrawFrame = nullptr;
        }
        if(m_CloseFrame){
            delete m_CloseFrame;
            m_CloseFrame = nullptr;
        }
        m_main_window->setFixedWidth(m_main_window->width()/2);
        m_main_window->m_viewPreviewWindow = false;
        return true;
    }
    return false;
}
bool PreviewWindow::ResetMessageBox(void)
{
    QMessageBox msgBox(this);
    msgBox.setText(TranslationString::GetString().translation_str.C_UI_004);
    msgBox.setWindowTitle(TranslationString::GetString().translation_str.MENU_001);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, TranslationString::GetString().translation_str.ES2U_MAIN_052);
    msgBox.setButtonText(QMessageBox::No, TranslationString::GetString().translation_str.ES2U_MAIN_053);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setGeometry(m_main_window->x()+(m_main_window->width()/2), m_main_window->y()+(m_main_window->height()/2), msgBox.width(), msgBox.height());
    int res = msgBox.exec();
    if (res == QMessageBox::Yes){
        return true;
    } else if (res == QMessageBox::No) {
        return false;
    }
    return false;
}
QRect PreviewWindow::UpdateMarqueeSizeLabel()
{
    QRect marquee_size = m_graphicsView->GetMarqueeSize();
    if(marquee_size.width() != 0 && marquee_size.height() != 0){
        m_graphicsView->UpdateMarqueeSizeLabel(marquee_size.width(), marquee_size.height());
    }else {
        m_graphicsView->UpdateMarqueeSizeLabel(m_graphicsView->MagnificationConversion(m_preview_image.width(), false), m_graphicsView->MagnificationConversion(m_preview_image.height(), false));
    }
    return marquee_size;
}
QImage PreviewWindow::getPreviewImage(void)
{
    return m_preview_image;
}
void PreviewWindow::on_Delete_Button_pressed()
{
    if(m_graphicsView->isExistedMarquee()){
        m_graphicsView->setMarqueeExist(false);
        m_graphicsView->UpdateMarqueeSizeLabel(m_graphicsView->width(), m_graphicsView->height());
        m_graphicsView->DeleteMarquee();
    }
}
void PreviewWindow::on_FocusPosition_Button_pressed()
{
    FocusPositionSettingDialog* focuspositionSettingDialog = new FocusPositionSettingDialog(&m_sv->device_data);
    if(focuspositionSettingDialog == NULL){
        return;
    }
    if(focuspositionSettingDialog->isHidden()){
        focuspositionSettingDialog->exec();
    }else {
        focuspositionSettingDialog->activateWindow();
    }
    focuspositionSettingDialog->SetValue();
    focuspositionSettingDialog->GetValue(&m_sv->device_data);
    delete focuspositionSettingDialog;
    focuspositionSettingDialog = NULL;
    return;
}
void PreviewWindow::MarqueeCreated(bool exist)
{
    if(exist){
        this->m_DeleteButton->setEnabled(true);
    }else {
        this->m_DeleteButton->setEnabled(false);
    }
}
