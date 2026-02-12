int SSL_pending(const SSL *s)
{


    return (s->method->ssl_pending(s));
}
