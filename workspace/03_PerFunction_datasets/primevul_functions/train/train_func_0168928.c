void ssl_free_wbio_buffer(SSL *s)
{
    if (s->bbio == NULL)
        return;

    if (s->bbio == s->wbio) {

        s->wbio = BIO_pop(s->wbio);
#ifdef REF_CHECK

        assert(s->wbio != NULL);
#endif
    }
    BIO_free(s->bbio);
    s->bbio = NULL;
}
