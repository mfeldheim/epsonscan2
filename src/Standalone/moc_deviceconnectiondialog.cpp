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
//  moc_deviceconnectiondialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "deviceconnectiondialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceconnectiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DeviceConnectionDialog_t {
    QByteArrayData data[3];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceConnectionDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceConnectionDialog_t qt_meta_stringdata_DeviceConnectionDialog = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 15),
QT_MOC_LITERAL(2, 39, 0)
    },
    "DeviceConnectionDialog\0CheckConnection\0"
    ""
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_DeviceConnectionDialog[] = {
       7,
       0,
       0, 0,
       1, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 0, 19, 2, 0x08 ,
    QMetaType::Void,
       0
};
void DeviceConnectionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceConnectionDialog *_t = static_cast<DeviceConnectionDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CheckConnection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
const QMetaObject DeviceConnectionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DeviceConnectionDialog.data,
      qt_meta_data_DeviceConnectionDialog, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *DeviceConnectionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *DeviceConnectionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceConnectionDialog.stringdata0))
        return static_cast<void*>(const_cast< DeviceConnectionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}
int DeviceConnectionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
