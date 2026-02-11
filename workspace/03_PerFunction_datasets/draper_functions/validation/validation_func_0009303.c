qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActionCollection *_t = static_cast<ActionCollection *>(_o);
        switch (_id) {
        case 0: _t->inserted((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->actionHovered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->actionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->connectNotify((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 4: _t->slotActionTriggered(); break;
        case 5: _t->slotActionHovered(); break;
        case 6: _t->actionDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->associatedWidgetDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
