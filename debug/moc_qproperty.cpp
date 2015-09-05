/****************************************************************************
** Meta object code from reading C++ file 'qproperty.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qproperty.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qproperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QProperty[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QProperty[] = {
    "QProperty\0\0signal_change(QString)\0"
    "slot_click()\0"
};

void QProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QProperty *_t = static_cast<QProperty *>(_o);
        switch (_id) {
        case 0: _t->signal_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slot_click(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QProperty::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QProperty::staticMetaObject = {
    { &FramelessWin::staticMetaObject, qt_meta_stringdata_QProperty,
      qt_meta_data_QProperty, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QProperty::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QProperty))
        return static_cast<void*>(const_cast< QProperty*>(this));
    return FramelessWin::qt_metacast(_clname);
}

int QProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FramelessWin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QProperty::signal_change(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
