qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CoordSysDlg *_t = static_cast<CoordSysDlg *>(_o);
        switch (_id) {
        case 0: _t->slotCartesian((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotPolar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotOriginRadius((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotLinearX((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slotLogX((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slotLinearY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slotLogY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slotDegrees((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slotGradians((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->slotRadians((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->slotWhat(); break;
        default: ;
        }
    }
}
