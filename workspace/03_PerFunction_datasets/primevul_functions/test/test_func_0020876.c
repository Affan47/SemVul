static int rename_cb(const char *mboxname __attribute__((unused)),
                     uint32_t uid,
                     const char *entry,
                     const char *userid, const struct buf *value,
                     const struct annotate_metadata *mdata __attribute__((unused)),
                     void *rock)
{
    struct rename_rock *rrock = (struct rename_rock *) rock;
    int r = 0;

    if (rrock->newmailbox &&

            strcmp(entry, IMAP_ANNOT_NS "snoozed") &&

            strcmp(entry, IMAP_ANNOT_NS "displayname")) {

        const char *newuserid = userid;

        if (rrock->olduserid && rrock->newuserid &&
            !strcmpsafe(rrock->olduserid, userid)) {

            newuserid = rrock->newuserid;
        }
        r = write_entry(rrock->newmailbox, rrock->newuid, entry, newuserid,
                        value, 0, 0, NULL, 1);
    }

    if (!rrock->copy && !r) {

        struct buf dattrib = BUF_INITIALIZER;
        r = write_entry(rrock->oldmailbox, uid, entry, userid, &dattrib,
                        0, 0, NULL, 1);
    }

    return r;
}
