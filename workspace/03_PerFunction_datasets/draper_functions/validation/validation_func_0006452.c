_sx_nad_write(sx_t s, nad_t nad, int elem) {
    char *out;
    int len;


    if(s->state >= state_CLOSING) {
        log_debug(ZONE, "stream closed, dropping outgoing packet");
        nad_free(nad);
        return 1;
    }


    if(_sx_chain_nad_write(s, nad, elem) == 0)
        return 1;


    nad_print(nad, elem, &out, &len);

    _sx_debug(ZONE, "queueing for write: %.*s", len, out);


    jqueue_push(s->wbufq, _sx_buffer_new(out, len, NULL, NULL), 0);

    nad_free(nad);


    s->want_write = 1;

    return 0;
}
