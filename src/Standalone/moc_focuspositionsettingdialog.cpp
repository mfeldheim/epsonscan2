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
//  moc_focuspositionsettingdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "focuspositionsettingdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'focuspositionsettingdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FocusPositionSettingDialog_t {
    QByteArrayData data[5];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FocusPositionSettingDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FocusPositionSettingDialog_t qt_meta_stringdata_FocusPositionSettingDialog = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 14),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 5),
QT_MOC_LITERAL(4, 49, 16)
    },
    "FocusPositionSettingDialog\0onValueChanged\0"
    "\0value\0PushButtonAction"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_FocusPositionSettingDialog[] = {
       7,
       0,
       0, 0,
       2, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 1, 24, 2, 0x0a ,
       4, 0, 27, 2, 0x0a ,
    QMetaType::Void, QMetaType::Int, 3,
    QMetaType::Void,
       0
};
void FocusPositionSettingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FocusPositionSettingDialog *_t = static_cast<FocusPositionSettingDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->PushButtonAction(); break;
        default: ;
        }
    }
}
const QMetaObject FocusPositionSettingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FocusPositionSettingDialog.data,
      qt_meta_data_FocusPositionSettingDialog, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *FocusPositionSettingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *FocusPositionSettingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FocusPositionSettingDialog.stringdata0))
        return static_cast<void*>(const_cast< FocusPositionSettingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}
int FocusPositionSettingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
