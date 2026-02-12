EXPORTED int annotate_delete_mailbox(struct mailbox *mailbox)
{
    int r = 0;
    char *fname = NULL;
    annotate_db_t *d = NULL;

    init_internal();

    assert(mailbox);


    r = _annotate_getdb(NULL, 0, 0, &d);
    if (r == CYRUSDB_NOTFOUND) {

        r = 0;
        goto out;
    }
    if (r) goto out;

    annotate_begin(d);

    r = _annotate_rewrite(mailbox,
                          0, NULL,
                          NULL,
                          0, NULL,
                          0);
    if (r) goto out;


    r = annotate_dbname_mailbox(mailbox, &fname);
    if (r) goto out;


    if (unlink(fname) < 0 && errno != ENOENT) {
        syslog(LOG_ERR, "cannot unlink %s: %m", fname);
    }

    r = annotate_commit(d);

out:
    annotate_putdb(&d);
    free(fname);
    return r;
}
