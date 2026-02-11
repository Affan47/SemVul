linenoiseEditInsert(struct linenoiseState *l, char c) {
    if (l->len < l->buflen) {
        if (l->len == l->pos) {
            l->buf[l->pos] = c;
            l->pos++;
            l->len++;
            l->buf[l->len] = '\0';
            if ((!mlmode && l->plen+l->len < l->cols) ) {


                if (write(l->ofd,&c,1) == -1) return -1;
            } else {
                refreshLine(l);
            }
        } else {
            memmove(l->buf+l->pos+1,l->buf+l->pos,l->len-l->pos);
            l->buf[l->pos] = c;
            l->len++;
            l->pos++;
            l->buf[l->len] = '\0';
            refreshLine(l);
        }
    }
    return 0;
}
