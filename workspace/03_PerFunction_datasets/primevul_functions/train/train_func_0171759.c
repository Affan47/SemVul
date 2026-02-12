int ssl3_check_finished(SSL *s)
	{
	int ok;
	long n;


	n=s->method->ssl_get_message(s,
		SSL3_ST_CR_CERT_A,
		SSL3_ST_CR_CERT_B,
		-1,
		s->max_cert_list,
		&ok);
	if (!ok) return((int)n);
	s->s3->tmp.reuse_message = 1;

	if (s->s3->tmp.message_type == SSL3_MT_SUPPLEMENTAL_DATA)
		return 3;

	if (!s->session->tlsext_tick)
		return 1;
	if ((s->s3->tmp.message_type == SSL3_MT_FINISHED)
		|| (s->s3->tmp.message_type == SSL3_MT_NEWSESSION_TICKET))
		return 2;

	return 1;
	}
