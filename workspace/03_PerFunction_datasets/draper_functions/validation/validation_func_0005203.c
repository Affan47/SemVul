qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SideBarTree *_t = static_cast<SideBarTree *>(_o);
        switch (_id) {
        case 0: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->plsShowRestState(); break;
        case 2: _t->plsShowNowPlaying(); break;
        case 3: _t->expandIndexUnderMouse(); break;
        case 4: _t->onActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->onContainerPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onAppEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        default: ;
        }
    }
}
