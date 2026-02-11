qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DirStat *_t = static_cast<DirStat *>(_o);
        switch (_id) {
        case 0: _t->populateHeader(); break;
        case 1: _t->populateTerminated(); break;
        case 2: _t->populateScheduled(); break;
        case 3: _t->populateRunning(); break;
        case 4: _t->populateAll(); break;
        case 5: _t->timerTriggered(); break;
        case 6: _t->consoleCancelJob(); break;
        case 7: _t->consoleDisableJob(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
