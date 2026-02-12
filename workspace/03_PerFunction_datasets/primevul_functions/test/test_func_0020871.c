static int split_attribs(const char *data, int datalen,
                         struct buf *value, struct annotate_metadata *mdata)
{
    unsigned long tmp;
    const char *tmps;
    const char *end = data + datalen;


    memset(mdata, 0, sizeof(struct annotate_metadata));


    if (datalen <= 0)
            return 1;


    memcpy(&tmp, data, sizeof(unsigned long));
    data += sizeof(unsigned long);

    buf_init_ro(value, data, ntohl(tmp));


    tmps = data + ntohl(tmp) + 1;
    if (tmps < end) {
        tmps += strlen(tmps) + 1;
        tmps += sizeof(unsigned long);
    }

    if (tmps < end) {

        modseq_t modseq;
        memcpy(&modseq, tmps, sizeof(modseq));
        mdata->modseq = ntohll(modseq);
        tmps += sizeof(modseq_t);
    }

    if (tmps < end) {
        mdata->flags = *tmps;
        tmps++;
    }


    if (mdata->flags & ANNOTATE_FLAG_DELETED) {
        buf_reset(value);
    }

    return 0;
}
