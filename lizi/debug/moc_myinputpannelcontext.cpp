/****************************************************************************
** Meta object code from reading C++ file 'myinputpannelcontext.h'
**
** Created: Mon Jun 4 14:19:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../myinputpannelcontext.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myinputpannelcontext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyInputPannelContext[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x0a,
      52,   48,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyInputPannelContext[] = {
    "MyInputPannelContext\0\0character\0"
    "charSlot(QChar)\0key\0intSlot(int)\0"
};

void MyInputPannelContext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyInputPannelContext *_t = static_cast<MyInputPannelContext *>(_o);
        switch (_id) {
        case 0: _t->charSlot((*reinterpret_cast< QChar(*)>(_a[1]))); break;
        case 1: _t->intSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyInputPannelContext::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyInputPannelContext::staticMetaObject = {
    { &QInputContext::staticMetaObject, qt_meta_stringdata_MyInputPannelContext,
      qt_meta_data_MyInputPannelContext, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyInputPannelContext::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyInputPannelContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyInputPannelContext::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyInputPannelContext))
        return static_cast<void*>(const_cast< MyInputPannelContext*>(this));
    return QInputContext::qt_metacast(_clname);
}

int MyInputPannelContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
