/****************************************************************************
** Meta object code from reading C++ file 'loginwithsafe.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../loginwithsafe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwithsafe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginWithSafe[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      35,   27,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   14,   14,   14, 0x0a,
      76,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoginWithSafe[] = {
    "LoginWithSafe\0\0LoginSafe()\0jid,pwd\0"
    "LoginWithInfo(QString,QString)\0okClick()\0"
    "readyRead()\0"
};

void LoginWithSafe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginWithSafe *_t = static_cast<LoginWithSafe *>(_o);
        switch (_id) {
        case 0: _t->LoginSafe(); break;
        case 1: _t->LoginWithInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->okClick(); break;
        case 3: _t->readyRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoginWithSafe::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginWithSafe::staticMetaObject = {
    { &FramelessWin::staticMetaObject, qt_meta_stringdata_LoginWithSafe,
      qt_meta_data_LoginWithSafe, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWithSafe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWithSafe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWithSafe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWithSafe))
        return static_cast<void*>(const_cast< LoginWithSafe*>(this));
    return FramelessWin::qt_metacast(_clname);
}

int LoginWithSafe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FramelessWin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LoginWithSafe::LoginSafe()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LoginWithSafe::LoginWithInfo(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
