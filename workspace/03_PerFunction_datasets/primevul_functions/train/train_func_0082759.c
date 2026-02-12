xz_head(xz_statep state)
{
    lzma_stream *strm = &(state->strm);
    lzma_stream init = LZMA_STREAM_INIT;
    int flags;
    unsigned len;


    if (state->size == 0) {

        state->in = xmlMalloc(state->want);
        state->out = xmlMalloc(state->want << 1);
        if (state->in == NULL || state->out == NULL) {
            if (state->out != NULL)
                xmlFree(state->out);
            if (state->in != NULL)
                xmlFree(state->in);
            xz_error(state, LZMA_MEM_ERROR, "out of memory");
            return -1;
        }
        state->size = state->want;


        state->strm = init;
        state->strm.avail_in = 0;
        state->strm.next_in = NULL;
        if (lzma_auto_decoder(&state->strm, UINT64_MAX, 0) != LZMA_OK) {
            xmlFree(state->out);
            xmlFree(state->in);
            state->size = 0;
            xz_error(state, LZMA_MEM_ERROR, "out of memory");
            return -1;
        }
#ifdef HAVE_ZLIB_H

        state->zstrm.zalloc = Z_NULL;
        state->zstrm.zfree = Z_NULL;
        state->zstrm.opaque = Z_NULL;
        state->zstrm.avail_in = 0;
        state->zstrm.next_in = Z_NULL;
        if (state->init == 0) {
            if (inflateInit2(&(state->zstrm), -15) != Z_OK) {
                xmlFree(state->out);
                xmlFree(state->in);
                state->size = 0;
                xz_error(state, LZMA_MEM_ERROR, "out of memory");
                return -1;
            }
            state->init = 1;
        }
#endif
    }


    if (strm->avail_in == 0) {
        if (xz_avail(state) == -1)
            return -1;
        if (strm->avail_in == 0)
            return 0;
    }


    if (is_format_xz(state) || is_format_lzma(state)) {
        state->how = LZMA;
        state->direct = 0;
        return 0;
    }
#ifdef HAVE_ZLIB_H

    if (strm->next_in[0] == 31) {
        strm->avail_in--;
        strm->next_in++;
        if (strm->avail_in == 0 && xz_avail(state) == -1)
            return -1;
        if (strm->avail_in && strm->next_in[0] == 139) {

            strm->avail_in--;
            strm->next_in++;


            if (NEXT() != 8) {
                xz_error(state, LZMA_DATA_ERROR,
                         "unknown compression method");
                return -1;
            }
            flags = NEXT();
            if (flags & 0xe0) {
                xz_error(state, LZMA_DATA_ERROR,
                         "unknown header flags set");
                return -1;
            }
            NEXT();
            NEXT();
            NEXT();
            NEXT();
            NEXT();
            NEXT();
            if (flags & 4) {
                len = (unsigned) NEXT();
                len += (unsigned) NEXT() << 8;
                while (len--)
                    if (NEXT() < 0)
                        break;
            }
            if (flags & 8)
                while (NEXT() > 0) ;
            if (flags & 16)
                while (NEXT() > 0) ;
            if (flags & 2) {
                NEXT();
                NEXT();
            }


            inflateReset(&state->zstrm);
            state->zstrm.adler = crc32(0L, Z_NULL, 0);
            state->how = GZIP;
            state->direct = 0;
            return 0;
        } else {

            state->out[0] = 31;
            state->have = 1;
        }
    }
#endif


    state->raw = state->pos;
    state->next = state->out;
    if (strm->avail_in) {
        memcpy(state->next + state->have, strm->next_in, strm->avail_in);
        state->have += strm->avail_in;
        strm->avail_in = 0;
    }
    state->how = COPY;
    state->direct = 1;
    return 0;
}
