int64_t streamTrim(stream *s, streamAddTrimArgs *args) {
    size_t maxlen = args->maxlen;
    streamID *id = &args->minid;
    int approx = args->approx_trim;
    int64_t limit = args->limit;
    int trim_strategy = args->trim_strategy;

    if (trim_strategy == TRIM_STRATEGY_NONE)
        return 0;

    raxIterator ri;
    raxStart(&ri,s->rax);
    raxSeek(&ri,"^",NULL,0);

    int64_t deleted = 0;
    while (raxNext(&ri)) {
        if (trim_strategy == TRIM_STRATEGY_MAXLEN && s->length <= maxlen)
            break;

        unsigned char *lp = ri.data, *p = lpFirst(lp);
        int64_t entries = lpGetInteger(p);


        if (limit && (deleted + entries) > limit)
            break;


        int remove_node;
        streamID master_id = {0};
        if (trim_strategy == TRIM_STRATEGY_MAXLEN) {
            remove_node = s->length - entries >= maxlen;
        } else {

            streamDecodeID(ri.key, &master_id);


            streamID last_id;
            lpGetEdgeStreamID(lp, 0, &master_id, &last_id);


            remove_node = streamCompareID(&last_id, id) < 0;
        }

        if (remove_node) {
            lpFree(lp);
            raxRemove(s->rax,ri.key,ri.key_len,NULL);
            raxSeek(&ri,">=",ri.key,ri.key_len);
            s->length -= entries;
            deleted += entries;
            continue;
        }


        if (approx) break;


        int64_t deleted_from_lp = 0;

        p = lpNext(lp, p);
        p = lpNext(lp, p);


        int64_t master_fields_count = lpGetInteger(p);
        p = lpNext(lp,p);
        for (int64_t j = 0; j < master_fields_count; j++)
            p = lpNext(lp,p);
        p = lpNext(lp,p);


        while (p) {


            unsigned char *pcopy = p;

            int64_t flags = lpGetInteger(p);
            p = lpNext(lp, p);
            int64_t to_skip;

            int64_t ms_delta = lpGetInteger(p);
            p = lpNext(lp, p);
            int64_t seq_delta = lpGetInteger(p);
            p = lpNext(lp, p);

            streamID currid = {0};
            if (trim_strategy == TRIM_STRATEGY_MINID) {
                currid.ms = master_id.ms + ms_delta;
                currid.seq = master_id.seq + seq_delta;
            }

            int stop;
            if (trim_strategy == TRIM_STRATEGY_MAXLEN) {
                stop = s->length <= maxlen;
            } else {


                stop = streamCompareID(&currid, id) >= 0;
            }
            if (stop)
                break;

            if (flags & STREAM_ITEM_FLAG_SAMEFIELDS) {
                to_skip = master_fields_count;
            } else {
                to_skip = lpGetInteger(p);
                p = lpNext(lp,p);
                to_skip *= 2;
            }

            while(to_skip--) p = lpNext(lp,p);
            p = lpNext(lp,p);


            if (!(flags & STREAM_ITEM_FLAG_DELETED)) {
                intptr_t delta = p - lp;
                flags |= STREAM_ITEM_FLAG_DELETED;
                lp = lpReplaceInteger(lp, &pcopy, flags);
                deleted_from_lp++;
                s->length--;
                p = lp + delta;
            }
        }
        deleted += deleted_from_lp;


        p = lpFirst(lp);
        lp = lpReplaceInteger(lp,&p,entries-deleted_from_lp);
        p = lpNext(lp,p);
        int64_t marked_deleted = lpGetInteger(p);
        lp = lpReplaceInteger(lp,&p,marked_deleted+deleted_from_lp);
        p = lpNext(lp,p);


        entries -= deleted_from_lp;
        marked_deleted += deleted_from_lp;
        if (entries + marked_deleted > 10 && marked_deleted > entries/2) {

        }


        raxInsert(s->rax,ri.key,ri.key_len,lp,NULL);

        break;

    }
    raxStop(&ri);


    if (s->length == 0) {
        s->first_id.ms = 0;
        s->first_id.seq = 0;
    } else if (deleted) {
        streamGetEdgeID(s,1,1,&s->first_id);
    }

    return deleted;
}
