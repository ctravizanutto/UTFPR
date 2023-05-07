/****************************************************************************
** Meta object code from reading C++ file 'my_frame.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Computer_Graphics/my_frame.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSmy_frameENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSmy_frameENDCLASS = QtMocHelpers::stringData(
    "my_frame",
    "rect_rot_r",
    "",
    "rect_rot_l",
    "rect_inc",
    "rect_dec",
    "rect_up",
    "rect_down",
    "rect_left",
    "rect_right"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSmy_frameENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[9];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[8];
    char stringdata7[10];
    char stringdata8[10];
    char stringdata9[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSmy_frameENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSmy_frameENDCLASS_t qt_meta_stringdata_CLASSmy_frameENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "my_frame"
        QT_MOC_LITERAL(9, 10),  // "rect_rot_r"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 10),  // "rect_rot_l"
        QT_MOC_LITERAL(32, 8),  // "rect_inc"
        QT_MOC_LITERAL(41, 8),  // "rect_dec"
        QT_MOC_LITERAL(50, 7),  // "rect_up"
        QT_MOC_LITERAL(58, 9),  // "rect_down"
        QT_MOC_LITERAL(68, 9),  // "rect_left"
        QT_MOC_LITERAL(78, 10)   // "rect_right"
    },
    "my_frame",
    "rect_rot_r",
    "",
    "rect_rot_l",
    "rect_inc",
    "rect_dec",
    "rect_up",
    "rect_down",
    "rect_left",
    "rect_right"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSmy_frameENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    0,   63,    2, 0x0a,    2 /* Public */,
       4,    0,   64,    2, 0x0a,    3 /* Public */,
       5,    0,   65,    2, 0x0a,    4 /* Public */,
       6,    0,   66,    2, 0x0a,    5 /* Public */,
       7,    0,   67,    2, 0x0a,    6 /* Public */,
       8,    0,   68,    2, 0x0a,    7 /* Public */,
       9,    0,   69,    2, 0x0a,    8 /* Public */,

 // slots: parameters
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

Q_CONSTINIT const QMetaObject my_frame::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_CLASSmy_frameENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSmy_frameENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSmy_frameENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<my_frame, std::true_type>,
        // method 'rect_rot_r'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_rot_l'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_inc'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_dec'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_up'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_down'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_left'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rect_right'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void my_frame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<my_frame *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rect_rot_r(); break;
        case 1: _t->rect_rot_l(); break;
        case 2: _t->rect_inc(); break;
        case 3: _t->rect_dec(); break;
        case 4: _t->rect_up(); break;
        case 5: _t->rect_down(); break;
        case 6: _t->rect_left(); break;
        case 7: _t->rect_right(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *my_frame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *my_frame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSmy_frameENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int my_frame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
