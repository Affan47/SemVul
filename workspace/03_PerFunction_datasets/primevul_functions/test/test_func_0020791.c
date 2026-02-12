HIDDEN int annotate_msg_cleanup(struct mailbox *mailbox, unsigned int uid)
{
    char key[MAX_MAILBOX_PATH+1];
    size_t keylen;
    int r = 0;
    annotate_db_t *d = NULL;

    assert(uid);

    r = _annotate_getdb(mailbox->name, uid, 0, &d);
    if (r) return r;


    annotate_begin(d);


    assert(mailbox->annot_state != NULL);
    assert(mailbox->annot_state->d == d);

    keylen = make_key(mailbox->name, uid, "", NULL, key, sizeof(key));

    r = cyrusdb_foreach(d->db, key, keylen, NULL, &cleanup_cb, d, tid(d));

    annotate_putdb(&d);
    return r;
}
