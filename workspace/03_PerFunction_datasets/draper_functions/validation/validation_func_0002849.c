qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        widgetDate *_t = static_cast<widgetDate *>(_o);
        switch (_id) {
        case 0: _t->dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->calenderPopupPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->dateEditDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->setDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->setReadOnly((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setLimitMinValueSetupTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setLimitMaxValueSetupTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setLimitAllowChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setLimitValuesExecutionDayWeek((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 9: _t->setLimitValuesExecutionDayMonth((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}
