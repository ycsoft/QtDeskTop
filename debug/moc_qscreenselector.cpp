/****************************************************************************
** Meta object code from reading C++ file 'qscreenselector.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../screenOper/qscreenselector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscreenselector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QScreenSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      42,   16,   16,   16, 0x0a,
      64,   16,   16,   16, 0x0a,
      87,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QScreenSelector[] = {
    "QScreenSelector\0\0slot_selectDesk(QString)\0"
    "slot_showall(QString)\0slot_showtodo(QString)\0"
    "slot_showdone(QString)\0"
};

void QScreenSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QScreenSelector *_t = static_cast<QScreenSelector *>(_o);
        switch (_id) {
        case 0: _t->slot_selectDesk((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slot_showall((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slot_showtodo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slot_showdone((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QScreenSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QScreenSelector::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QScreenSelector,
      qt_meta_data_QScreenSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QScreenSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QScreenSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QScreenSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QScreenSelector))
        return static_cast<void*>(const_cast< QScreenSelector*>(this));
    return QWidget::qt_metacast(_clname);
}

int QScreenSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
