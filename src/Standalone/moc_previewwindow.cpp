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
//  moc_previewwindow.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "previewwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PreviewWindow_t {
    QByteArrayData data[8];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PreviewWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PreviewWindow_t qt_meta_stringdata_PreviewWindow = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 23),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 7),
QT_MOC_LITERAL(4, 47, 24),
QT_MOC_LITERAL(5, 72, 31),
QT_MOC_LITERAL(6, 104, 14),
QT_MOC_LITERAL(7, 119, 5)
    },
    "PreviewWindow\0on_Close_Button_pressed\0"
    "\0Confirm\0on_Delete_Button_pressed\0"
    "on_FocusPosition_Button_pressed\0"
    "MarqueeCreated\0exist"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_PreviewWindow[] = {
       7,
       0,
       0, 0,
       5, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 1, 39, 2, 0x0a ,
       1, 0, 42, 2, 0x2a ,
       4, 0, 43, 2, 0x08 ,
       5, 0, 44, 2, 0x08 ,
       6, 1, 45, 2, 0x08 ,
    QMetaType::Bool, QMetaType::Bool, 3,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, 7,
       0
};
void PreviewWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreviewWindow *_t = static_cast<PreviewWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->on_Close_Button_pressed((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; } break;
        case 1: { bool _r = _t->on_Close_Button_pressed();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; } break;
        case 2: _t->on_Delete_Button_pressed(); break;
        case 3: _t->on_FocusPosition_Button_pressed(); break;
        case 4: _t->MarqueeCreated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
const QMetaObject PreviewWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PreviewWindow.data,
      qt_meta_data_PreviewWindow, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *PreviewWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *PreviewWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewWindow.stringdata0))
        return static_cast<void*>(const_cast< PreviewWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}
int PreviewWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
