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
//  detectionareamindoublespinbox.h -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef DETECTIONAREAMINDOUBLESPINBOX_H
#define DETECTIONAREAMINDOUBLESPINBOX_H 
#include <QDoubleSpinBox>
#include "supervisor.h"
class DetectionAreaMinDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    DetectionAreaMinDoubleSpinBox(QWidget *parent = 0);
    double current_value_inchi;
    double current_value_mm;
    double base_value;
    void initialize(SDIInt default_value);
    void Finalize(void);
    void CreateBaseToValue(void);
    double CreateDisplayValue(double value);
    bool isUnit_inchi(void);
public slots:
    void setMaxValue(double value);
private:
    void SetSpinBoxParam(void);
    void CreateValueToBase(void);
    void set_enabled(bool enabled);
};
#endif
