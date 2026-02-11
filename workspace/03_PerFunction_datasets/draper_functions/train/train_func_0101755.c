qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdvancedConnector *_t = static_cast<AdvancedConnector *>(_o);
        switch (_id) {
        case 0: _t->srvLookup((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->srvResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->httpSyncStarted(); break;
        case 3: _t->httpSyncFinished(); break;
        case 4: _t->dns_done(); break;
        case 5: _t->srv_done(); break;
        case 6: _t->bs_connected(); break;
        case 7: _t->bs_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->http_syncStarted(); break;
        case 9: _t->http_syncFinished(); break;
        default: ;
        }
    }
}
