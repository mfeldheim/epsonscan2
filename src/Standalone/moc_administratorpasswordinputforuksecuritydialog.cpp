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
//  moc_administratorpasswordinputforuksecuritydialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "administratorpasswordinputforuksecuritydialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'administratorpasswordinputforuksecuritydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog_t {
    QByteArrayData data[4];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog_t qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog = {
    {
QT_MOC_LITERAL(0, 0, 45),
QT_MOC_LITERAL(1, 46, 16),
QT_MOC_LITERAL(2, 63, 0),
QT_MOC_LITERAL(3, 64, 16)
    },
    "AdministratorPasswordInputForUKSecurityDialog\0"
    "PushButtonAction\0\0LineEditFinished"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_AdministratorPasswordInputForUKSecurityDialog[] = {
       7,
       0,
       0, 0,
       2, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 0, 24, 2, 0x0a ,
       3, 0, 25, 2, 0x0a ,
    QMetaType::Void,
    QMetaType::Void,
       0
};
void AdministratorPasswordInputForUKSecurityDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AdministratorPasswordInputForUKSecurityDialog *_t = static_cast<AdministratorPasswordInputForUKSecurityDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PushButtonAction(); break;
        case 1: _t->LineEditFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
const QMetaObject AdministratorPasswordInputForUKSecurityDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog.data,
      qt_meta_data_AdministratorPasswordInputForUKSecurityDialog, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *AdministratorPasswordInputForUKSecurityDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *AdministratorPasswordInputForUKSecurityDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AdministratorPasswordInputForUKSecurityDialog.stringdata0))
        return static_cast<void*>(const_cast< AdministratorPasswordInputForUKSecurityDialog*>(this));
    return QDialog::qt_metacast(_clname);
}
int AdministratorPasswordInputForUKSecurityDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
