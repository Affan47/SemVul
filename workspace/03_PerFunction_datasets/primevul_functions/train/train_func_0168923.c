int SSL_shutdown(SSL *s)
{


    if (s->handshake_func == 0) {
        SSLerr(SSL_F_SSL_SHUTDOWN, SSL_R_UNINITIALIZED);
        return -1;
    }

    if ((s != NULL) && !SSL_in_init(s))
        return (s->method->ssl_shutdown(s));
    else
        return (1);
}
