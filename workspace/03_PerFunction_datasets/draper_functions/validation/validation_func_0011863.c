bio_filter_in_read(BIO *bio, char *in, int inlen)
{
    apr_size_t inl = inlen;
    bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)(bio->ptr);
    apr_read_type_e block = inctx->block;

    inctx->rc = APR_SUCCESS;


    if (!in)
        return 0;


    if (inctx->filter_ctx->config->reneg_state == RENEG_ABORT) {
        inctx->rc = APR_ECONNABORTED;
        return -1;
    }


    if (bio_filter_out_flush(inctx->bio_out) < 0) {
        bio_filter_out_ctx_t *outctx = inctx->bio_out->ptr;
        inctx->rc = outctx->rc;
        return -1;
    }

    BIO_clear_retry_flags(bio);

    if (!inctx->bb) {
        inctx->rc = APR_EOF;
        return -1;
    }

    if (APR_BRIGADE_EMPTY(inctx->bb)) {

        inctx->rc = ap_get_brigade(inctx->f->next, inctx->bb,
                                   AP_MODE_READBYTES, block,
                                   inl);


        if (APR_STATUS_IS_EAGAIN(inctx->rc) || APR_STATUS_IS_EINTR(inctx->rc)
               || (inctx->rc == APR_SUCCESS && APR_BRIGADE_EMPTY(inctx->bb))) {
            BIO_set_retry_read(bio);
            return -1;
        }

        if (inctx->rc != APR_SUCCESS) {

            apr_brigade_cleanup(inctx->bb);
            inctx->bb = NULL;
            return -1;
        }
    }

    inctx->rc = brigade_consume(inctx->bb, block, in, &inl);

    if (inctx->rc == APR_SUCCESS) {
        return (int)inl;
    }

    if (APR_STATUS_IS_EAGAIN(inctx->rc)
            || APR_STATUS_IS_EINTR(inctx->rc)) {
        BIO_set_retry_read(bio);
        return (int)inl;
    }


    apr_brigade_cleanup(inctx->bb);
    inctx->bb = NULL;

    if (APR_STATUS_IS_EOF(inctx->rc) && inl) {


        return (int)inl;
    }

    return -1;
}
