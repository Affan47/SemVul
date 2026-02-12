int SSL_get_error(const SSL *s, int i)
{
    int reason;
    unsigned long l;
    BIO *bio;

    if (i > 0)
        return (SSL_ERROR_NONE);


    if ((l = ERR_peek_error()) != 0) {
        if (ERR_GET_LIB(l) == ERR_LIB_SYS)
            return (SSL_ERROR_SYSCALL);
        else
            return (SSL_ERROR_SSL);
    }

    if ((i < 0) && SSL_want_read(s)) {
        bio = SSL_get_rbio(s);
        if (BIO_should_read(bio))
            return (SSL_ERROR_WANT_READ);
        else if (BIO_should_write(bio))


            return (SSL_ERROR_WANT_WRITE);
        else if (BIO_should_io_special(bio)) {
            reason = BIO_get_retry_reason(bio);
            if (reason == BIO_RR_CONNECT)
                return (SSL_ERROR_WANT_CONNECT);
            else if (reason == BIO_RR_ACCEPT)
                return (SSL_ERROR_WANT_ACCEPT);
            else
                return (SSL_ERROR_SYSCALL);
        }
    }

    if ((i < 0) && SSL_want_write(s)) {
        bio = SSL_get_wbio(s);
        if (BIO_should_write(bio))
            return (SSL_ERROR_WANT_WRITE);
        else if (BIO_should_read(bio))


            return (SSL_ERROR_WANT_READ);
        else if (BIO_should_io_special(bio)) {
            reason = BIO_get_retry_reason(bio);
            if (reason == BIO_RR_CONNECT)
                return (SSL_ERROR_WANT_CONNECT);
            else if (reason == BIO_RR_ACCEPT)
                return (SSL_ERROR_WANT_ACCEPT);
            else
                return (SSL_ERROR_SYSCALL);
        }
    }
    if ((i < 0) && SSL_want_x509_lookup(s)) {
        return (SSL_ERROR_WANT_X509_LOOKUP);
    }

    if (i == 0) {
        if (s->version == SSL2_VERSION) {

            return (SSL_ERROR_ZERO_RETURN);
        } else {
            if ((s->shutdown & SSL_RECEIVED_SHUTDOWN) &&
                (s->s3->warn_alert == SSL_AD_CLOSE_NOTIFY))
                return (SSL_ERROR_ZERO_RETURN);
        }
    }
    return (SSL_ERROR_SYSCALL);
}
