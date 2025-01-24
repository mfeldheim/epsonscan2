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
//  moc_aboutepsonscan2dialog.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#include "aboutepsonscan2dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aboutepsonscan2dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif
QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AboutEpsonScan2Dialog_t {
    QByteArrayData data[1];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx,ofs,len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AboutEpsonScan2Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AboutEpsonScan2Dialog_t qt_meta_stringdata_AboutEpsonScan2Dialog = {
    {
QT_MOC_LITERAL(0, 0, 21)
    },
    "AboutEpsonScan2Dialog"
};
#undef QT_MOC_LITERAL
static const uint qt_meta_data_AboutEpsonScan2Dialog[] = {
       7,
       0,
       0, 0,
       0, 0,
       0, 0,
       0, 0,
       0, 0,
       0,
       0,
       0
};
void AboutEpsonScan2Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}
const QMetaObject AboutEpsonScan2Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AboutEpsonScan2Dialog.data,
      qt_meta_data_AboutEpsonScan2Dialog, qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};
const QMetaObject *AboutEpsonScan2Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}
void *AboutEpsonScan2Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AboutEpsonScan2Dialog.stringdata0))
        return static_cast<void*>(const_cast< AboutEpsonScan2Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}
int AboutEpsonScan2Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
