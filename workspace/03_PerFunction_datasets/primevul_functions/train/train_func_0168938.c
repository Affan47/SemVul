int SSL_has_matching_session_id(const SSL *ssl, const unsigned char *id,
                                unsigned int id_len)
{


    SSL_SESSION r, *p;

    if (id_len > sizeof r.session_id)
        return 0;

    r.ssl_version = ssl->version;
    r.session_id_length = id_len;
    memcpy(r.session_id, id, id_len);


    if ((r.ssl_version == SSL2_VERSION) &&
        (id_len < SSL2_SSL_SESSION_ID_LENGTH)) {
        memset(r.session_id + id_len, 0, SSL2_SSL_SESSION_ID_LENGTH - id_len);
        r.session_id_length = SSL2_SSL_SESSION_ID_LENGTH;
    }

    CRYPTO_r_lock(CRYPTO_LOCK_SSL_CTX);
    p = lh_SSL_SESSION_retrieve(ssl->ctx->sessions, &r);
    CRYPTO_r_unlock(CRYPTO_LOCK_SSL_CTX);
    return (p != NULL);
}
