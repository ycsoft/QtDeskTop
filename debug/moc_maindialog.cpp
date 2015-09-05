/****************************************************************************
** Meta object code from reading C++ file 'maindialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../maindialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   11,   11,   11, 0x0a,
      54,   11,   11,   11, 0x0a,
      68,   11,   11,   11, 0x0a,
      87,   11,   11,   11, 0x0a,
     104,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     145,  138,   11,   11, 0x0a,
     200,  195,   11,   11, 0x0a,
     230,  226,   11,   11, 0x0a,
     245,   11,   11,   11, 0x0a,
     257,   11,   11,   11, 0x0a,
     269,   11,   11,   11, 0x0a,
     285,  281,   11,   11, 0x0a,
     306,   11,   11,   11, 0x0a,
     320,   11,   11,   11, 0x0a,
     334,   11,   11,   11, 0x0a,
     344,   11,   11,   11, 0x0a,
     356,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainDialog[] = {
    "MainDialog\0\0sigShowMsg(QString)\0"
    "dbclick_icon(QString)\0showDesktop()\0"
    "click_mycomputer()\0action_add_app()\0"
    "action_add_notify()\0action_prop()\0"
    "reason\0trayIconActive(QSystemTrayIcon::ActivationReason)\0"
    "spic\0slot_change_desk(QString)\0txt\0"
    "click(QString)\0addNotify()\0connected()\0"
    "readyRead()\0msg\0showMessage(QString)\0"
    "popupMsgWin()\0showScreens()\0viewURL()\0"
    "showStart()\0showToDoManager()\0"
};

void MainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainDialog *_t = static_cast<MainDialog *>(_o);
        switch (_id) {
        case 0: _t->sigShowMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->dbclick_icon((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->showDesktop(); break;
        case 3: _t->click_mycomputer(); break;
        case 4: _t->action_add_app(); break;
        case 5: _t->action_add_notify(); break;
        case 6: _t->action_prop(); break;
        case 7: _t->trayIconActive((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 8: _t->slot_change_desk((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->click((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->addNotify(); break;
        case 11: _t->connected(); break;
        case 12: _t->readyRead(); break;
        case 13: _t->showMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->popupMsgWin(); break;
        case 15: _t->showScreens(); break;
        case 16: _t->viewURL(); break;
        case 17: _t->showStart(); break;
        case 18: _t->showToDoManager(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MainDialog,
      qt_meta_data_MainDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialog))
        return static_cast<void*>(const_cast< MainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainDialog::sigShowMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
