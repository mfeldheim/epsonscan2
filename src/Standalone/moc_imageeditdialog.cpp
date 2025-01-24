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
//  moc_imageeditdialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "imageeditdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageEditDialog_t {
    QByteArrayData data[7];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageEditDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageEditDialog_t qt_meta_stringdata_ImageEditDialog = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 15),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 21),
QT_MOC_LITERAL(4, 55, 22),
QT_MOC_LITERAL(5, 78, 23),
QT_MOC_LITERAL(6, 102, 21)
    },
    "ImageEditDialog\0onButtonPressed\0\0"
    "on_rotateLeft_clicked\0on_rotateRight_clicked\0"
    "on_removeButton_clicked\0on_saveButton_clicked"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_ImageEditDialog[] = {
       7,
       0,
       0, 0,
       5, 14,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       1, 0, 39, 2, 0x08 ,
       3, 0, 40, 2, 0x08 ,
       4, 0, 41, 2, 0x08 ,
       5, 0, 42, 2, 0x08 ,
       6, 0, 43, 2, 0x08 ,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
       0
};
void ImageEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageEditDialog *_t = static_cast<ImageEditDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onButtonPressed(); break;
        case 1: _t->on_rotateLeft_clicked(); break;
        case 2: _t->on_rotateRight_clicked(); break;
        case 3: _t->on_removeButton_clicked(); break;
        case 4: _t->on_saveButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
const QMetaObject ImageEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImageEditDialog.data,
      qt_meta_data_ImageEditDialog, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *ImageEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *ImageEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageEditDialog.stringdata0))
        return static_cast<void*>(const_cast< ImageEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}
int ImageEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
