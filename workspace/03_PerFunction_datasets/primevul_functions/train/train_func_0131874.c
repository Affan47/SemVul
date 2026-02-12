static void process_mget_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    item *it;
    unsigned int i = 0;
    struct _meta_flags of = {0};
    uint32_t hv;
    bool failed = false;
    bool item_created = false;
    bool won_token = false;
    bool ttl_set = false;
    char *errstr = "CLIENT_ERROR bad command line format";
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
    } else if (ntokens > MFLAG_MAX_OPT_LENGTH) {

        out_errstring(c, "CLIENT_ERROR options flags are too long");
        return;
    }


    if (_meta_flag_preparse(tokens, ntokens, &of, &errstr) != 0) {
        out_errstring(c, errstr);
        return;
    }
    c->noreply = of.no_reply;


    bool overflow = false;
    if (!of.locked) {
        it = limited_get(key, nkey, c, 0, false, !of.no_update, &overflow);
    } else {

        it = limited_get_locked(key, nkey, c, DONT_UPDATE, &hv, &overflow);
    }


    if (overflow) {
        assert(it == NULL);
        out_errstring(c, "SERVER_ERROR refcount overflow during fetch");
        return;
    }

    if (it == NULL && of.vivify) {

        it = item_alloc(key, nkey, 0, realtime(0), 2);


        if (it != NULL) {

            memcpy(ITEM_data(it), "\r\n", 2);

            do_item_link(it, hv);
            item_created = true;
        }
    }


    if (it) {
        if (of.value) {
            memcpy(p, "VA ", 3);
            p = itoa_u32(it->nbytes-2, p+3);
        } else {
            memcpy(p, "OK", 2);
            p += 2;
        }

        for (i = KEY_TOKEN+1; i < ntokens-1; i++) {
            switch (tokens[i].value[0]) {
                case 'T':
                    ttl_set = true;
                    it->exptime = of.exptime;
                    break;
                case 'N':
                    if (item_created) {
                        it->exptime = of.autoviv_exptime;
                        won_token = true;
                    }
                    break;
                case 'R':


                    if ((it->it_flags & ITEM_TOKEN_SENT) == 0
                            && !item_created
                            && it->exptime != 0
                            && it->exptime < of.recache_time) {
                        won_token = true;
                    }
                    break;
                case 's':
                    META_CHAR(p, 's');
                    p = itoa_u32(it->nbytes-2, p);
                    break;
                case 't':


                    META_CHAR(p, 't');
                    if (it->exptime == 0) {
                        *p = '-';
                        *(p+1) = '1';
                        p += 2;
                    } else {
                        p = itoa_u32(it->exptime - current_time, p);
                    }
                    break;
                case 'c':
                    META_CHAR(p, 'c');
                    p = itoa_u64(ITEM_get_cas(it), p);
                    break;
                case 'f':
                    META_CHAR(p, 'f');
                    if (FLAGS_SIZE(it) == 0) {
                        *p = '0';
                        p++;
                    } else {
                        p = itoa_u32(*((uint32_t *) ITEM_suffix(it)), p);
                    }
                    break;
                case 'l':
                    META_CHAR(p, 'l');
                    p = itoa_u32(current_time - it->time, p);
                    break;
                case 'h':
                    META_CHAR(p, 'h');
                    if (it->it_flags & ITEM_FETCHED) {
                        *p = '1';
                    } else {
                        *p = '0';
                    }
                    p++;
                    break;
                case 'O':
                    if (tokens[i].length > MFLAG_MAX_OPAQUE_LENGTH) {
                        errstr = "CLIENT_ERROR opaque token too long";
                        goto error;
                    }
                    META_SPACE(p);
                    memcpy(p, tokens[i].value, tokens[i].length);
                    p += tokens[i].length;
                    break;
                case 'k':
                    META_CHAR(p, 'k');
                    memcpy(p, ITEM_key(it), it->nkey);
                    p += it->nkey;
                    break;
            }
        }


        if (it->it_flags & ITEM_TOKEN_SENT) {
            META_CHAR(p, 'Z');
        }
        if (it->it_flags & ITEM_STALE) {
            META_CHAR(p, 'X');

            if ((it->it_flags & ITEM_TOKEN_SENT) == 0) {

                won_token = true;
            }
        }

        if (won_token) {

            META_CHAR(p, 'W');
            it->it_flags |= ITEM_TOKEN_SENT;
        }

        *p = '\r';
        *(p+1) = '\n';
        *(p+2) = '\0';
        p += 2;

        resp_add_iov(resp, resp->wbuf, p - resp->wbuf);

        if (of.value) {
#ifdef EXTSTORE
            if (it->it_flags & ITEM_HDR) {
                if (_get_extstore(c, it, resp) != 0) {
                    pthread_mutex_lock(&c->thread->stats.mutex);
                    c->thread->stats.get_oom_extstore++;
                    pthread_mutex_unlock(&c->thread->stats.mutex);

                    failed = true;
                }
            } else if ((it->it_flags & ITEM_CHUNKED) == 0) {
                resp_add_iov(resp, ITEM_data(it), it->nbytes);
            } else {
                resp_add_chunked_iov(resp, it, it->nbytes);
            }
#else
            if ((it->it_flags & ITEM_CHUNKED) == 0) {
                resp_add_iov(resp, ITEM_data(it), it->nbytes);
            } else {
                resp_add_chunked_iov(resp, it, it->nbytes);
            }
#endif
        }


#ifdef EXTSTORE
        if (!failed) {
            if ((it->it_flags & ITEM_HDR) != 0 && of.value) {

                resp->item = NULL;
            } else {
                resp->item = it;
            }
        } else {

            if (of.locked) {
                do_item_remove(it);
            } else {
                item_remove(it);
            }
        }
#else
        resp->item = it;
#endif
    } else {
        failed = true;
    }

    if (of.locked) {

        if (!of.no_update && it != NULL) {
            do_item_bump(c, it, hv);
        }
        item_unlock(hv);
    }


    if (!failed) {
        pthread_mutex_lock(&c->thread->stats.mutex);
        if (ttl_set) {
            c->thread->stats.touch_cmds++;
            c->thread->stats.slab_stats[ITEM_clsid(it)].touch_hits++;
        } else {
            c->thread->stats.lru_hits[it->slabs_clsid]++;
            c->thread->stats.get_cmds++;
        }
        pthread_mutex_unlock(&c->thread->stats.mutex);

        conn_set_state(c, conn_new_cmd);
    } else {
        pthread_mutex_lock(&c->thread->stats.mutex);
        if (ttl_set) {
            c->thread->stats.touch_cmds++;
            c->thread->stats.touch_misses++;
        } else {
            c->thread->stats.get_misses++;
            c->thread->stats.get_cmds++;
        }
        MEMCACHED_COMMAND_GET(c->sfd, key, nkey, -1, 0);
        pthread_mutex_unlock(&c->thread->stats.mutex);


        out_string(c, "EN");
    }
    return;
error:
    if (it) {
        do_item_remove(it);
        if (of.locked) {
            item_unlock(hv);
        }
    }
    out_errstring(c, errstr);
}
