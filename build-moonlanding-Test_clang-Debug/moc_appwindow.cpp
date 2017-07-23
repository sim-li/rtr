/****************************************************************************
** Meta object code from reading C++ file 'appwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../moonlanding/appwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppWindow_t {
    QByteArrayData data[13];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppWindow_t qt_meta_stringdata_AppWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AppWindow"
QT_MOC_LITERAL(1, 10, 6), // "showUI"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "hideUI"
QT_MOC_LITERAL(4, 25, 13), // "keyPressEvent"
QT_MOC_LITERAL(5, 39, 10), // "QKeyEvent*"
QT_MOC_LITERAL(6, 50, 5), // "event"
QT_MOC_LITERAL(7, 56, 18), // "setDefaultUIValues"
QT_MOC_LITERAL(8, 75, 21), // "displayBufferContents"
QT_MOC_LITERAL(9, 97, 2), // "id"
QT_MOC_LITERAL(10, 100, 5), // "label"
QT_MOC_LITERAL(11, 106, 3), // "img"
QT_MOC_LITERAL(12, 110, 18) // "hideBufferContents"

    },
    "AppWindow\0showUI\0\0hideUI\0keyPressEvent\0"
    "QKeyEvent*\0event\0setDefaultUIValues\0"
    "displayBufferContents\0id\0label\0img\0"
    "hideBufferContents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,
       8,    3,   50,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::QString, QMetaType::QImage,    9,   10,   11,
    QMetaType::Void,

       0        // eod
};

void AppWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppWindow *_t = static_cast<AppWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showUI(); break;
        case 1: _t->hideUI(); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->setDefaultUIValues(); break;
        case 4: _t->displayBufferContents((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< const QImage(*)>(_a[3]))); break;
        case 5: _t->hideBufferContents(); break;
        default: ;
        }
    }
}

const QMetaObject AppWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AppWindow.data,
      qt_meta_data_AppWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AppWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AppWindow.stringdata0))
        return static_cast<void*>(const_cast< AppWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int AppWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
