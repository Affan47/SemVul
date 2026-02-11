_ios_read(ios_t *s, char *dest, size_t n, int all)
{
    size_t tot = 0;
    size_t got, avail;


    while (n > 0) {
        avail = s->size - s->bpos;

        if (avail > 0) {
            size_t ncopy = (avail >= n) ? n : avail;
            memcpy(dest, s->buf + s->bpos, ncopy);
            s->bpos += ncopy;
            if (ncopy >= n) {
                s->state = bst_rd;
                return tot+ncopy;
            }
        }
        if (s->bm == bm_mem || s->fd == -1) {

            s->state = bst_rd;
            if (avail == 0)
                s->_eof = 1;
            return avail;
        }

        dest += avail;
        n -= avail;
        tot += avail;

        ios_flush(s);
        s->bpos = s->size = 0;
        s->state = bst_rd;

        s->fpos = -1;
        if (n > MOST_OF(s->maxsize)) {

            if (all) {

                _os_read_all(s->fd, dest, n, &got);
            } else {

                _os_read(s->fd, dest, n, &got);
            }
            tot += got;
            if (got == 0)
                s->_eof = 1;
            return tot;
        }
        else {

            if (_os_read(s->fd, s->buf, s->maxsize, &got)) {
                s->_eof = 1;
                return tot;
            }
            if (got == 0) {
                s->_eof = 1;
                return tot;
            }
            s->size = got;
        }
    }

    return tot;
}
