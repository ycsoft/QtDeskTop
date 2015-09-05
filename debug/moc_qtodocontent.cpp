/****************************************************************************
** Meta object code from reading C++ file 'qtodocontent.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../todo/qtodocontent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtodocontent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QToDoContent[] = {

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
      14,   13,   13,   13, 0x0a,
      33,   27,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QToDoContent[] = {
    "QToDoContent\0\0ok_clicked()\0index\0"
    "tree_clicked(QModelIndex)\0"
};

void QToDoContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QToDoContent *_t = static_cast<QToDoContent *>(_o);
        switch (_id) {
        case 0: _t->ok_clicked(); break;
        case 1: _t->tree_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QToDoContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QToDoContent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QToDoContent,
      qt_meta_data_QToDoContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QToDoContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QToDoContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QToDoContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QToDoContent))
        return static_cast<void*>(const_cast< QToDoContent*>(this));
    return QWidget::qt_metacast(_clname);
}

int QToDoContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
