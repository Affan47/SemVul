int SSL_renegotiate_pending(SSL *s)
{


    return (s->renegotiate != 0);
}
