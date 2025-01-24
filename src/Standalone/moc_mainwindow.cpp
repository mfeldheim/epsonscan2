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
//  moc_mainwindow.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[411];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 25),
QT_MOC_LITERAL(4, 61, 14),
QT_MOC_LITERAL(5, 76, 5),
QT_MOC_LITERAL(6, 82, 18),
QT_MOC_LITERAL(7, 101, 18),
QT_MOC_LITERAL(8, 120, 5),
QT_MOC_LITERAL(9, 126, 21),
QT_MOC_LITERAL(10, 148, 30),
QT_MOC_LITERAL(11, 179, 23),
QT_MOC_LITERAL(12, 203, 32),
QT_MOC_LITERAL(13, 236, 27),
QT_MOC_LITERAL(14, 264, 21),
QT_MOC_LITERAL(15, 286, 35),
QT_MOC_LITERAL(16, 322, 14),
QT_MOC_LITERAL(17, 337, 21),
QT_MOC_LITERAL(18, 359, 18),
QT_MOC_LITERAL(19, 378, 14),
QT_MOC_LITERAL(20, 393, 5),
QT_MOC_LITERAL(21, 399, 11)
    },
    "MainWindow\0on_Scan_Button_pressed\0\0"
    "on_Preview_Button_pressed\0onValueChanged\0"
    "value\0onValueChangedQstr\0onValueChangedBool\0"
    "check\0onSave_Button_pressed\0"
    "onConfiguration_Button_pressed\0"
    "onFolder_Button_pressed\0"
    "onFileNameSetting_Button_pressed\0"
    "onAbout_Epson_Scan2_pressed\0"
    "onHelp_Button_pressed\0"
    "onTextEnhanceSetting_Button_pressed\0"
    "EditFinishText\0SelectionRestrictions\0"
    "CheckLongPaperMode\0MarqueeCreated\0"
    "exist\0MarqueeSize"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_MainWindow[] = {
       7,
       0,
       0, 0,
      16, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 0, 94, 2, 0x08 ,
       3, 0, 95, 2, 0x08 ,
       4, 1, 96, 2, 0x08 ,
       6, 1, 99, 2, 0x08 ,
       7, 1, 102, 2, 0x08 ,
       9, 0, 105, 2, 0x08 ,
      10, 0, 106, 2, 0x08 ,
      11, 0, 107, 2, 0x08 ,
      12, 0, 108, 2, 0x08 ,
      13, 0, 109, 2, 0x08 ,
      14, 0, 110, 2, 0x08 ,
      15, 0, 111, 2, 0x08 ,
      16, 0, 112, 2, 0x08 ,
      17, 1, 113, 2, 0x08 ,
      18, 0, 116, 2, 0x08 ,
      19, 2, 117, 2, 0x08 ,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 5,
    QMetaType::Void, QMetaType::QString, 5,
    QMetaType::Void, QMetaType::Bool, 8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, 5,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool, QMetaType::QRect, 20, 21,
       0
};
void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Scan_Button_pressed(); break;
        case 1: _t->on_Preview_Button_pressed(); break;
        case 2: _t->onValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onValueChangedQstr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->onValueChangedBool((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onSave_Button_pressed(); break;
        case 6: _t->onConfiguration_Button_pressed(); break;
        case 7: _t->onFolder_Button_pressed(); break;
        case 8: _t->onFileNameSetting_Button_pressed(); break;
        case 9: _t->onAbout_Epson_Scan2_pressed(); break;
        case 10: _t->onHelp_Button_pressed(); break;
        case 11: _t->onTextEnhanceSetting_Button_pressed(); break;
        case 12: _t->EditFinishText(); break;
        case 13: { bool _r = _t->SelectionRestrictions((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; } break;
        case 14: { bool _r = _t->CheckLongPaperMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; } break;
        case 15: _t->MarqueeCreated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QRect(*)>(_a[2]))); break;
        default: ;
        }
    }
}
const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}
int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
