__libxml2_xzread(xzFile file, void *buf, unsigned len)
{
    unsigned got, n;
    xz_statep state;
    lzma_stream *strm;


    if (file == NULL)
        return -1;
    state = (xz_statep) file;
    strm = &(state->strm);


    if (state->err != LZMA_OK)
        return -1;


    if ((int) len < 0) {
        xz_error(state, LZMA_BUF_ERROR,
                 "requested length does not fit in int");
        return -1;
    }


    if (len == 0)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (xz_skip(state, state->skip) == -1)
            return -1;
    }


    got = 0;
    do {

        if (state->have) {
            n = state->have > len ? len : state->have;
            memcpy(buf, state->next, n);
            state->next += n;
            state->have -= n;
        }


        else if (state->eof && strm->avail_in == 0)
            break;


        else if (state->how == LOOK || len < (state->size << 1)) {

            if (xz_make(state) == -1)
                return -1;
            continue;


        }


        else if (state->how == COPY) {
            if (xz_load(state, buf, len, &n) == -1)
                return -1;
        }


        else {
            strm->avail_out = len;
            strm->next_out = buf;
            if (xz_decomp(state) == -1)
                return -1;
            n = state->have;
            state->have = 0;
        }


        len -= n;
        buf = (char *) buf + n;
        got += n;
        state->pos += n;
    } while (len);


    return (int) got;
}
