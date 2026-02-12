ssl_errno (SSL *ssl, int ret)
{
	switch (SSL_get_error (ssl, ret)) {
	case SSL_ERROR_NONE:
		return 0;
	case SSL_ERROR_ZERO_RETURN:


		return EINVAL;
	case SSL_ERROR_WANT_READ:
	case SSL_ERROR_WANT_WRITE:

		return EAGAIN;
	case SSL_ERROR_SYSCALL:

		return EINTR;
	case SSL_ERROR_SSL:

		return EINTR;
	default:

		return EINTR;
	}
}
