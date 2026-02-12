void SSL_CTX_free(SSL_CTX *a)
{
    int i;

    if (a == NULL)
        return;

    i = CRYPTO_add(&a->references, -1, CRYPTO_LOCK_SSL_CTX);
#ifdef REF_PRINT
    REF_PRINT("SSL_CTX", a);
#endif
    if (i > 0)
        return;
#ifdef REF_CHECK
    if (i < 0) {
        fprintf(stderr, "SSL_CTX_free, bad reference count\n");
        abort();
    }
#endif

    if (a->param)
        X509_VERIFY_PARAM_free(a->param);


    if (a->sessions != NULL)
        SSL_CTX_flush_sessions(a, 0);

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_SSL_CTX, a, &a->ex_data);

    if (a->sessions != NULL)
        lh_SSL_SESSION_free(a->sessions);

    if (a->cert_store != NULL)
        X509_STORE_free(a->cert_store);
    if (a->cipher_list != NULL)
        sk_SSL_CIPHER_free(a->cipher_list);
    if (a->cipher_list_by_id != NULL)
        sk_SSL_CIPHER_free(a->cipher_list_by_id);
    if (a->cert != NULL)
        ssl_cert_free(a->cert);
    if (a->client_CA != NULL)
        sk_X509_NAME_pop_free(a->client_CA, X509_NAME_free);
    if (a->extra_certs != NULL)
        sk_X509_pop_free(a->extra_certs, X509_free);
#if 0

    if (a->comp_methods != NULL)
        sk_SSL_COMP_pop_free(a->comp_methods, SSL_COMP_free);
#else
    a->comp_methods = NULL;
#endif

#ifndef OPENSSL_NO_SRTP
    if (a->srtp_profiles)
        sk_SRTP_PROTECTION_PROFILE_free(a->srtp_profiles);
#endif

#ifndef OPENSSL_NO_PSK
    if (a->psk_identity_hint)
        OPENSSL_free(a->psk_identity_hint);
#endif
#ifndef OPENSSL_NO_SRP
    SSL_CTX_SRP_CTX_free(a);
#endif
#ifndef OPENSSL_NO_ENGINE
    if (a->client_cert_engine)
        ENGINE_finish(a->client_cert_engine);
#endif

#ifndef OPENSSL_NO_BUF_FREELISTS
    if (a->wbuf_freelist)
        ssl_buf_freelist_free(a->wbuf_freelist);
    if (a->rbuf_freelist)
        ssl_buf_freelist_free(a->rbuf_freelist);
#endif

    OPENSSL_free(a);
}
