static int _annotate_getdb(const char *mboxname,
                           unsigned int uid,
                           int dbflags,
                           annotate_db_t **dbp)
{
    annotate_db_t *d, *prev = NULL;
    char *fname = NULL;
    struct db *db;
    int r;

    *dbp = NULL;


    if (!strcmpsafe(mboxname, NULL)  ||
        !uid )
        mboxname = NULL;


    for (d = all_dbs_head ; d ; prev = d, d = d->next) {
        if (!strcmpsafe(mboxname, d->mboxname)) {

            d->refcount++;
            *dbp = d;


            detach_db(prev, d);
            append_db(d);
            return 0;
        }
    }


    r = annotate_dbname(mboxname, &fname);
    if (r)
        goto error;
#if DEBUG
    syslog(LOG_ERR, "Opening annotations db %s\n", fname);
#endif

    r = cyrusdb_open(DB, fname, dbflags | CYRUSDB_CONVERT, &db);
    if (r != 0) {
        if (!(dbflags & CYRUSDB_CREATE) && r == CYRUSDB_NOTFOUND)
            goto error;
        syslog(LOG_ERR, "DBERROR: opening %s: %s",
                        fname, cyrusdb_strerror(r));
        goto error;
    }


    d = xzmalloc(sizeof(*d));
    d->refcount = 1;
    d->mboxname = xstrdupnull(mboxname);
    d->filename = fname;
    d->db = db;

    append_db(d);

    *dbp = d;
    return 0;

error:
    free(fname);
    *dbp = NULL;
    return r;
}
