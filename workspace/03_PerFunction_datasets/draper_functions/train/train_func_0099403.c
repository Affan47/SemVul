process_certificate(SSL *ssl, X509_CTX **x509_ctx)
{
    int ret = SSL_OK;
    uint8_t *buf = &ssl->bm_data[ssl->dc->bm_proc_index];
    int pkt_size = ssl->bm_index;
    int cert_size, offset = 5;
    int total_cert_size = (buf[offset]<<8) + buf[offset+1];
    int is_client = IS_SET_SSL_FLAG(SSL_IS_CLIENT);
    X509_CTX **chain = x509_ctx;
    offset += 2;

    PARANOIA_CHECK(total_cert_size, offset);

    while (offset < total_cert_size)
    {
        offset++;
        cert_size = (buf[offset]<<8) + buf[offset+1];
        offset += 2;

        if (x509_new(&buf[offset], NULL, chain))
        {
            ret = SSL_ERROR_BAD_CERTIFICATE;
            goto error;
        }

        chain = &((*chain)->next);
        offset += cert_size;
    }

    PARANOIA_CHECK(pkt_size, offset);


    if (is_client && !IS_SET_SSL_FLAG(SSL_SERVER_VERIFY_LATER))
    {
        ret = ssl_verify_cert(ssl);
    }

    ssl->next_state = is_client ? HS_SERVER_HELLO_DONE : HS_CLIENT_KEY_XCHG;
    ssl->dc->bm_proc_index += offset;
error:
    return ret;
}
