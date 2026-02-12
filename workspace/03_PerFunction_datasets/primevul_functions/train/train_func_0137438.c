int run_sieve(const mbname_t *mbname, sieve_interp_t *interp, deliver_data_t *msgdata)
{
    struct buf attrib = BUF_INITIALIZER;
    const char *script = NULL;
    char fname[MAX_MAILBOX_PATH+1];
    sieve_execute_t *bc = NULL;
    script_data_t sdata;
    int r = 0;
    duplicate_key_t dkey = DUPLICATE_INITIALIZER;
    struct auth_state *freeauthstate = NULL;

    if (!mbname_userid(mbname)) {
        if (annotatemore_lookup(mbname_intname(mbname),
                                IMAP_ANNOT_NS "sieve", "",
                                &attrib) != 0 || !attrib.s) {

            return 1;
        }

        script = buf_cstring(&attrib);
    }

    if (sieve_find_script(mbname_localpart(mbname), mbname_domain(mbname),
                          script, fname, sizeof(fname)) != 0 ||
        sieve_script_load(fname, &bc) != SIEVE_OK) {
        buf_free(&attrib);

        return 1;
    }
    buf_free(&attrib);
    script = NULL;

    sdata.mbname = mbname;
    sdata.ns = msgdata->ns;
    sdata.edited_header = 0;

    if (mbname_userid(mbname)) {
        sdata.authstate = freeauthstate = auth_newstate(mbname_userid(mbname));
    }
    else {
        sdata.authstate = msgdata->authstate;
    }

    r = sieve_execute_bytecode(bc, interp,
                               (void *) &sdata, (void *) msgdata);

    if ((r == SIEVE_OK) && (msgdata->m->id)) {
        const char *sdb = make_sieve_db(mbname_recipient(mbname, sdata.ns));

        dkey.id = msgdata->m->id;
        dkey.to = sdb;
        dkey.date = msgdata->m->date;
        duplicate_mark(&dkey, time(NULL), 0);
    }


    if (freeauthstate) auth_freestate(freeauthstate);
    sieve_script_unload(&bc);


    return r;
}
