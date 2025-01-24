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
//  moc_verticaldoctoolbutton.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "verticaldoctoolbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'verticaldoctoolbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VerticalDoctoolButton_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VerticalDoctoolButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VerticalDoctoolButton_t qt_meta_stringdata_VerticalDoctoolButton = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 12),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 7)
    },
    "VerticalDoctoolButton\0button_event\0\0"
    "checked"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_VerticalDoctoolButton[] = {
       7,
       0,
       0, 0,
       1, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 1, 19, 2, 0x0a ,
    QMetaType::Void, QMetaType::Bool, 3,
       0
};
void VerticalDoctoolButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VerticalDoctoolButton *_t = static_cast<VerticalDoctoolButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->button_event((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
const QMetaObject VerticalDoctoolButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_VerticalDoctoolButton.data,
      qt_meta_data_VerticalDoctoolButton, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *VerticalDoctoolButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *VerticalDoctoolButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VerticalDoctoolButton.stringdata0))
        return static_cast<void*>(const_cast< VerticalDoctoolButton*>(this));
    return QToolButton::qt_metacast(_clname);
}
int VerticalDoctoolButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
