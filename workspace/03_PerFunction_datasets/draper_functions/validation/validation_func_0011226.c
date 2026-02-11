iw_open(Store *store, volatile Analyzer *analyzer,
                     const Config *config)
{
    IndexWriter *iw = ALLOC_AND_ZERO(IndexWriter);
    mutex_init(&iw->mutex, NULL);
    iw->store = store;
    if (!config) {
        config = &default_config;
    }
    iw->config = *config;

    TRY
        iw->write_lock = open_lock(store, WRITE_LOCK_NAME);
        if (!iw->write_lock->obtain(iw->write_lock)) {
            RAISE(LOCK_ERROR,
                  "Couldn't obtain write lock when opening IndexWriter");
        }

        iw->sis = sis_read(store);
        iw->fis = iw->sis->fis;
        REF(iw->fis);
    XCATCHALL
        if (iw->write_lock) {
            iw->write_lock->release(iw->write_lock);
            close_lock(iw->write_lock);
            iw->write_lock = NULL;
        }
        if (iw->sis) sis_destroy(iw->sis);
        if (analyzer) a_deref((Analyzer *)analyzer);
        free(iw);
    XENDTRY

    iw->similarity = sim_create_default();
    iw->analyzer = analyzer ? (Analyzer *)analyzer
                            : mb_standard_analyzer_new(true);

    iw->deleter = deleter_new(iw->sis, store);
    deleter_delete_deletable_files(iw->deleter);

    REF(store);
    return iw;
}
