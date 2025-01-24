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
//  gammaslider.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef GAMMASLIDER_H
#define GAMMASLIDER_H 
#include <QSlider>
#include "supervisor.h"
class GammaSlider : public QSlider
{
    Q_OBJECT
public:
    GammaSlider(QWidget *parent = 0);
    double current_item;
    void initialize(double default_item);
    void update_ui();
    void item_event(double value, INT_SETTING_VALUE* gamma_para);
private slots:
    void setGammaSlider(double value);
private:
    bool changed;
    void set_enabled(bool enabled);
};
#endif
