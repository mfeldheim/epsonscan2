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
//  moc_gammaslider.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "gammaslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gammaslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GammaSlider_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GammaSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GammaSlider_t qt_meta_stringdata_GammaSlider = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 14),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 5)
    },
    "GammaSlider\0setGammaSlider\0\0value"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_GammaSlider[] = {
       7,
       0,
       0, 0,
       1, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 1, 19, 2, 0x08 ,
    QMetaType::Void, QMetaType::Double, 3,
       0
};
void GammaSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GammaSlider *_t = static_cast<GammaSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGammaSlider((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}
const QMetaObject GammaSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_GammaSlider.data,
      qt_meta_data_GammaSlider, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *GammaSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *GammaSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GammaSlider.stringdata0))
        return static_cast<void*>(const_cast< GammaSlider*>(this));
    return QSlider::qt_metacast(_clname);
}
int GammaSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
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
