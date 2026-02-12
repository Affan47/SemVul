static int autorespond(void *ac,
                       void *ic __attribute__((unused)),
                       void *sc,
                       void *mc __attribute__((unused)),
                       const char **errmsg __attribute__((unused)))
{
    sieve_autorespond_context_t *arc = (sieve_autorespond_context_t *) ac;
    script_data_t *sd = (script_data_t *) sc;
    time_t t, now;
    int ret;
    int i;
    duplicate_key_t dkey = DUPLICATE_INITIALIZER;
    char *id;

    prometheus_increment(CYRUS_LMTP_SIEVE_AUTORESPOND_TOTAL);
    snmp_increment(SIEVE_VACATION_TOTAL, 1);

    now = time(NULL);


    id = xmalloc(SIEVE_HASHLEN*2 + 1);
    for (i = 0; i < SIEVE_HASHLEN; i++) {
        id[i*2+0] = hex[arc->hash[i] / 16];
        id[i*2+1] = hex[arc->hash[i] % 16];
    }
    id[SIEVE_HASHLEN*2] = '\0';
    dkey.id = id;
    dkey.to = mbname_userid(sd->mbname);
    dkey.date = "";
    t = duplicate_check(&dkey);
    if (t) {
        if (now >= t) {

            ret = SIEVE_OK;
        } else {
            ret = SIEVE_DONE;
        }
    } else {

        ret = SIEVE_OK;
    }

    if (ret == SIEVE_OK) {
        duplicate_mark(&dkey, now + arc->seconds, 0);
    }

    free(id);

    return ret;
}
