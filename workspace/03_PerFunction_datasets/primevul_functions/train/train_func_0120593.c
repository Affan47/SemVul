static ssize_t stream_ssl_error(RedStream *s, int return_code)
{
    SPICE_GNUC_UNUSED int ssl_error;

    ssl_error = SSL_get_error(s->priv->ssl, return_code);


#ifdef _WIN32
    if (ssl_error == SSL_ERROR_WANT_READ || ssl_error == SSL_ERROR_WANT_WRITE) {
        errno = EAGAIN;
    } else {
        errno = EPIPE;
    }
#endif


    return -1;
}
