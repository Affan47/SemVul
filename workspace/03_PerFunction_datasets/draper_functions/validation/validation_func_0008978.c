qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AboutForm *_t = static_cast<AboutForm *>(_o);
        switch (_id) {
        case 0: _t->HandleHeimdallStdout(); break;
        case 1: _t->HandleHeimdallReturned((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: _t->HandleHeimdallError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    }
}
