int should_add_extension(SSL *s, unsigned int extctx, unsigned int thisctx,
                         int max_version)
{

    if ((extctx & thisctx) == 0)
        return 0;


    if (!extension_is_relevant(s, extctx, thisctx)
            || ((extctx & SSL_EXT_TLS1_3_ONLY) != 0
                && (thisctx & SSL_EXT_CLIENT_HELLO) != 0
                && (SSL_IS_DTLS(s) || max_version < TLS1_3_VERSION)))
        return 0;

    return 1;
}
