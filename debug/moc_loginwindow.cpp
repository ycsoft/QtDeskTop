/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../loginwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Loginwindow[] = {

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
      21,   13,   12,   12, 0x0a,
      52,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Loginwindow[] = {
    "Loginwindow\0\0jid,pwd\0"
    "LoginWithInfo(QString,QString)\0"
    "slotloginclick()\0"
};

void Loginwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Loginwindow *_t = static_cast<Loginwindow *>(_o);
        switch (_id) {
        case 0: _t->LoginWithInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->slotloginclick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Loginwindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Loginwindow::staticMetaObject = {
    { &ShadowDlg::staticMetaObject, qt_meta_stringdata_Loginwindow,
      qt_meta_data_Loginwindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Loginwindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Loginwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Loginwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Loginwindow))
        return static_cast<void*>(const_cast< Loginwindow*>(this));
    return ShadowDlg::qt_metacast(_clname);
}

int Loginwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ShadowDlg::qt_metacall(_c, _id, _a);
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
