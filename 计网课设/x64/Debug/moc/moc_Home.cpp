/****************************************************************************
** Meta object code from reading C++ file 'Home.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Home.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Home.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Home_t {
    QByteArrayData data[18];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Home_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Home_t qt_meta_stringdata_Home = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Home"
QT_MOC_LITERAL(1, 5, 11), // "file_import"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "file_export"
QT_MOC_LITERAL(4, 30, 11), // "view_filter"
QT_MOC_LITERAL(5, 42, 13), // "capture_start"
QT_MOC_LITERAL(6, 56, 11), // "capture_end"
QT_MOC_LITERAL(7, 68, 15), // "capture_restart"
QT_MOC_LITERAL(8, 84, 16), // "statistics_chart"
QT_MOC_LITERAL(9, 101, 15), // "statistics_IPv4"
QT_MOC_LITERAL(10, 117, 15), // "statistics_IPv6"
QT_MOC_LITERAL(11, 133, 14), // "statistics_UDP"
QT_MOC_LITERAL(12, 148, 14), // "statistics_TCP"
QT_MOC_LITERAL(13, 163, 14), // "statistics_ARP"
QT_MOC_LITERAL(14, 178, 15), // "statistics_HTTP"
QT_MOC_LITERAL(15, 194, 15), // "statistics_DHCP"
QT_MOC_LITERAL(16, 210, 14), // "statistics_DNS"
QT_MOC_LITERAL(17, 225, 5) // "about"

    },
    "Home\0file_import\0\0file_export\0view_filter\0"
    "capture_start\0capture_end\0capture_restart\0"
    "statistics_chart\0statistics_IPv4\0"
    "statistics_IPv6\0statistics_UDP\0"
    "statistics_TCP\0statistics_ARP\0"
    "statistics_HTTP\0statistics_DHCP\0"
    "statistics_DNS\0about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Home[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Home::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Home *_t = static_cast<Home *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->file_import(); break;
        case 1: _t->file_export(); break;
        case 2: _t->view_filter(); break;
        case 3: _t->capture_start(); break;
        case 4: _t->capture_end(); break;
        case 5: _t->capture_restart(); break;
        case 6: _t->statistics_chart(); break;
        case 7: _t->statistics_IPv4(); break;
        case 8: _t->statistics_IPv6(); break;
        case 9: _t->statistics_UDP(); break;
        case 10: _t->statistics_TCP(); break;
        case 11: _t->statistics_ARP(); break;
        case 12: _t->statistics_HTTP(); break;
        case 13: _t->statistics_DHCP(); break;
        case 14: _t->statistics_DNS(); break;
        case 15: _t->about(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Home::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Home.data,
      qt_meta_data_Home,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Home::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Home::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Home.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Home::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
