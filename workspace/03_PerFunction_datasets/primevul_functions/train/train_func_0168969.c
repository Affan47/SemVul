int SSL_accept(SSL *s)
{
    if (s->handshake_func == 0)

        SSL_set_accept_state(s);

    return (s->method->ssl_accept(s));
}
