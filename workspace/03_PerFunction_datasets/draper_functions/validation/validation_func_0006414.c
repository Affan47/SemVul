qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PointSetDlg *_t = static_cast<PointSetDlg *>(_o);
        switch (_id) {
        case 0: _t->slotPointShape((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->slotPointSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->slotPointLineSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotPointLineColor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotPointInColor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slotLineSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->slotLineColor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->slotLineConnectAs((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->slotWhat(); break;
        default: ;
        }
    }
}
