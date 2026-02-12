int tls_collect_extensions(SSL *s, PACKET *packet, unsigned int context,
                           RAW_EXTENSION **res, size_t *len, int init)
{
    PACKET extensions = *packet;
    size_t i = 0;
    size_t num_exts;
    custom_ext_methods *exts = &s->cert->custext;
    RAW_EXTENSION *raw_extensions = NULL;
    const EXTENSION_DEFINITION *thisexd;

    *res = NULL;


    if ((context & SSL_EXT_CLIENT_HELLO) != 0)
        custom_ext_init(&s->cert->custext);

    num_exts = OSSL_NELEM(ext_defs) + (exts != NULL ? exts->meths_count : 0);
    raw_extensions = OPENSSL_zalloc(num_exts * sizeof(*raw_extensions));
    if (raw_extensions == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_COLLECT_EXTENSIONS,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    i = 0;
    while (PACKET_remaining(&extensions) > 0) {
        unsigned int type, idx;
        PACKET extension;
        RAW_EXTENSION *thisex;

        if (!PACKET_get_net_2(&extensions, &type) ||
            !PACKET_get_length_prefixed_2(&extensions, &extension)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_COLLECT_EXTENSIONS,
                     SSL_R_BAD_EXTENSION);
            goto err;
        }


        if (!verify_extension(s, context, type, exts, raw_extensions, &thisex)
                || (thisex != NULL && thisex->present == 1)
                || (type == TLSEXT_TYPE_psk
                    && (context & SSL_EXT_CLIENT_HELLO) != 0
                    && PACKET_remaining(&extensions) != 0)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_COLLECT_EXTENSIONS,
                     SSL_R_BAD_EXTENSION);
            goto err;
        }
        idx = thisex - raw_extensions;


        if (idx < OSSL_NELEM(ext_defs)
                && (context & (SSL_EXT_CLIENT_HELLO
                               | SSL_EXT_TLS1_3_CERTIFICATE_REQUEST
                               | SSL_EXT_TLS1_3_NEW_SESSION_TICKET)) == 0
                && type != TLSEXT_TYPE_cookie
                && type != TLSEXT_TYPE_renegotiate
                && type != TLSEXT_TYPE_signed_certificate_timestamp
                && (s->ext.extflags[idx] & SSL_EXT_FLAG_SENT) == 0
#ifndef OPENSSL_NO_GOST
                && !((context & SSL_EXT_TLS1_2_SERVER_HELLO) != 0
                     && type == TLSEXT_TYPE_cryptopro_bug)
#endif
								) {
            SSLfatal(s, SSL_AD_UNSUPPORTED_EXTENSION,
                     SSL_F_TLS_COLLECT_EXTENSIONS, SSL_R_UNSOLICITED_EXTENSION);
            goto err;
        }
        if (thisex != NULL) {
            thisex->data = extension;
            thisex->present = 1;
            thisex->type = type;
            thisex->received_order = i++;
            if (s->ext.debug_cb)
                s->ext.debug_cb(s, !s->server, thisex->type,
                                PACKET_data(&thisex->data),
                                PACKET_remaining(&thisex->data),
                                s->ext.debug_arg);
        }
    }

    if (init) {


        for (thisexd = ext_defs, i = 0; i < OSSL_NELEM(ext_defs);
             i++, thisexd++) {
            if (thisexd->init != NULL && (thisexd->context & context) != 0
                && extension_is_relevant(s, thisexd->context, context)
                && !thisexd->init(s, context)) {

                goto err;
            }
        }
    }

    *res = raw_extensions;
    if (len != NULL)
        *len = num_exts;
    return 1;

 err:
    OPENSSL_free(raw_extensions);
    return 0;
}
