static void process_mset_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    item *it;
    int i;
    short comm = NREAD_SET;
    struct _meta_flags of = {0};
    char *errstr = "CLIENT_ERROR bad command line format";
    uint32_t hv;
    mc_resp *resp = c->resp;
    char *p = resp->wbuf;

    assert(c != NULL);
    WANT_TOKENS_MIN(ntokens, 3);


    if (tokens[KEY_TOKEN].length > KEY_MAX_LENGTH) {
        out_errstring(c, "CLIENT_ERROR bad command line format");
        return;
    }

    key = tokens[KEY_TOKEN].value;
    nkey = tokens[KEY_TOKEN].length;

    if (ntokens == 3) {
        out_errstring(c, "CLIENT_ERROR bad command line format");
        return;
    }

    if (ntokens > MFLAG_MAX_OPT_LENGTH) {
        out_errstring(c, "CLIENT_ERROR options flags too long");
        return;
    }


    p = resp->wbuf + 3;


    if (_meta_flag_preparse(tokens, ntokens, &of, &errstr) != 0) {
        goto error;
    }


    c->noreply = of.no_reply;

    bool has_error = false;
    for (i = KEY_TOKEN+1; i < ntokens-1; i++) {
        switch (tokens[i].value[0]) {

            case 'O':
                if (tokens[i].length > MFLAG_MAX_OPAQUE_LENGTH) {
                    errstr = "CLIENT_ERROR opaque token too long";
                    has_error = true;
                    break;
                }
                META_SPACE(p);
                memcpy(p, tokens[i].value, tokens[i].length);
                p += tokens[i].length;
                break;
            case 'k':
                META_CHAR(p, 'k');
                memcpy(p, key, nkey);
                p += nkey;
                break;
        }
    }


    switch (of.mode) {
        case 0:
            break;
        case 'E':
            comm = NREAD_ADD;
            break;
        case 'A':
            comm = NREAD_APPEND;
            break;
        case 'P':
            comm = NREAD_PREPEND;
            break;
        case 'R':
            comm = NREAD_REPLACE;
            break;
        case 'S':
            comm = NREAD_SET;
            break;
        default:
            errstr = "CLIENT_ERROR invalid mode for ms M token";
            goto error;
    }


    if (of.has_cas && (comm == NREAD_SET || comm == NREAD_REPLACE)) {
        comm = NREAD_CAS;
    }


    if (has_error)
        goto error;

    it = item_alloc(key, nkey, of.client_flags, of.exptime, of.value_len);

    if (it == 0) {
        enum store_item_type status;


        if (! item_size_ok(nkey, of.client_flags, of.value_len)) {
            errstr = "SERVER_ERROR object too large for cache";
            status = TOO_LARGE;
        } else {
            errstr = "SERVER_ERROR out of memory storing object";
            status = NO_MEMORY;
        }

        LOGGER_LOG(c->thread->l, LOG_MUTATIONS, LOGGER_ITEM_STORE,
                NULL, status, comm, key, nkey, 0, 0);


        it = item_get_locked(key, nkey, c, DONT_UPDATE, &hv);
        if (it) {
            do_item_unlink(it, hv);
            STORAGE_delete(c->thread->storage, it);
            do_item_remove(it);
        }
        item_unlock(hv);

        goto error;
    }
    ITEM_set_cas(it, of.req_cas_id);

    c->item = it;
#ifdef NEED_ALIGN
    if (it->it_flags & ITEM_CHUNKED) {
        c->ritem = ITEM_schunk(it);
    } else {
        c->ritem = ITEM_data(it);
    }
#else
    c->ritem = ITEM_data(it);
#endif
    c->rlbytes = it->nbytes;
    c->cmd = comm;
    if (of.set_stale && comm == NREAD_CAS) {
        c->set_stale = true;
    }
    resp->wbytes = p - resp->wbuf;
    memcpy(resp->wbuf + resp->wbytes, "\r\n", 2);
    resp->wbytes += 2;

    resp_add_iov(resp, resp->wbuf, resp->wbytes);
    c->mset_res = true;
    conn_set_state(c, conn_nread);
    return;
error:

    c->sbytes = of.value_len;


    out_errstring(c, errstr);

    conn_set_state(c, conn_swallow);
}
