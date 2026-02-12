error_ret(struct tok_state *tok)
{
    tok->decoding_erred = 1;
    if (tok->fp != NULL && tok->buf != NULL)
        PyMem_FREE(tok->buf);
    tok->buf = tok->cur = tok->end = tok->inp = tok->start = NULL;
    tok->done = E_DECODE;
    return NULL;
}
