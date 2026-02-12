void streamReplyWithCGLag(client *c, stream *s, streamCG *cg) {
    int valid = 0;
    long long lag = 0;

    if (!s->entries_added) {

        lag = 0;
        valid = 1;
    } else if (cg->entries_read != SCG_INVALID_ENTRIES_READ && !streamRangeHasTombstones(s,&cg->last_id,NULL)) {


        lag = (long long)s->entries_added - cg->entries_read;
        valid = 1;
    } else {

        long long entries_read = streamEstimateDistanceFromFirstEverEntry(s,&cg->last_id);
        if (entries_read != SCG_INVALID_ENTRIES_READ) {

            lag = (long long)s->entries_added - entries_read;
            valid = 1;
        }
    }

    if (valid) {
        addReplyLongLong(c,lag);
    } else {
        addReplyNull(c);
    }
}
