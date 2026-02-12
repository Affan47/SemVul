xz_avail(xz_statep state)
{
    lzma_stream *strm = &(state->strm);

    if (state->err != LZMA_OK)
        return -1;
    if (state->eof == 0) {

        unsigned tmp = strm->avail_in;

        if (xz_load(state, state->in, state->size, &tmp) == -1) {
            strm->avail_in = tmp;
            return -1;
        }
        strm->avail_in = tmp;
        strm->next_in = state->in;
    }
    return 0;
}
