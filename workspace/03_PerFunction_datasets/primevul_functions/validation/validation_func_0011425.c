xz_reset(xz_statep state)
{
    state->have = 0;
    state->eof = 0;
    state->how = LOOK;
    state->direct = 1;
    state->seek = 0;
    xz_error(state, LZMA_OK, NULL);
    state->pos = 0;
    state->strm.avail_in = 0;
#ifdef HAVE_ZLIB_H
    state->zstrm.avail_in = 0;
#endif
}
