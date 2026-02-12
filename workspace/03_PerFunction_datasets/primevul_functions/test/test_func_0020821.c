EXPORTED int annotate_rename_mailbox(struct mailbox *oldmailbox,
                            struct mailbox *newmailbox)
{

    char *olduserid = mboxname_to_userid(oldmailbox->name);
    char *newuserid = mboxname_to_userid(newmailbox->name);
    annotate_db_t *d = NULL;
    int r = 0;

    init_internal();


    r = _annotate_getdb(NULL, 0, 0, &d);
    if (r == CYRUSDB_NOTFOUND) {

        r = 0;
        goto done;
    }
    if (r) goto done;

    annotate_begin(d);


    r = _annotate_rewrite(oldmailbox, 0, olduserid,
                          newmailbox, 0, newuserid,
                         1);
    if (r) goto done;

    r = annotate_commit(d);
    if (r) goto done;


 done:
    annotate_putdb(&d);
    free(olduserid);
    free(newuserid);

    return r;
}
