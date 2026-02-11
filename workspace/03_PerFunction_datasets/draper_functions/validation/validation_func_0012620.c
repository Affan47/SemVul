qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConversionDlg *_t = static_cast<ConversionDlg *>(_o);
        switch (_id) {
        case 0: _t->nextPressed(); break;
        case 1: _t->prevPressed(); break;
        case 2: _t->doubleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->floatChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->integerChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->valueChanged(); break;
        case 7: _t->asciiChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
