EXPORTED int annotatemore_write(const char *mboxname, const char *entry,
                                const char *userid, const struct buf *value)
{
    struct mailbox *mailbox = NULL;
    int r = 0;
    annotate_db_t *d = NULL;

    init_internal();

    r = _annotate_getdb(mboxname, 0, CYRUSDB_CREATE, &d);
    if (r) goto done;

    if (mboxname) {
        r = mailbox_open_iwl(mboxname, &mailbox);
        if (r) goto done;
    }

    r = write_entry(mailbox, 0, entry, userid, value,
                    1, 0, NULL, 1);
    if (r) goto done;

    r = annotate_commit(d);

done:
    annotate_putdb(&d);
    mailbox_close(&mailbox);

    return r;
}
