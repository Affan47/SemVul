tls_handshake_recv(REQUEST *request, tls_session_t *ssn)
{
	int err;

	BIO_write(ssn->into_ssl, ssn->dirty_in.data, ssn->dirty_in.used);

	err = SSL_read(ssn->ssl, ssn->clean_out.data + ssn->clean_out.used,
		       sizeof(ssn->clean_out.data) - ssn->clean_out.used);
	if (err > 0) {
		ssn->clean_out.used += err;
		record_init(&ssn->dirty_in);
		return 1;
	}

	if (!int_ssl_check(request, ssn->ssl, err, "SSL_read")) {
		return 0;
	}


	if (SSL_is_init_finished(ssn->ssl)) {
		DEBUG2("SSL Connection Established\n");
	}
   	if (SSL_in_init(ssn->ssl)) {
		DEBUG2("In SSL Handshake Phase\n");
	}
   	if (SSL_in_before(ssn->ssl)) {
		DEBUG2("Before SSL Handshake Phase\n");
	}
   	if (SSL_in_accept_init(ssn->ssl)) {
		DEBUG2("In SSL Accept mode \n");
	}
   	if (SSL_in_connect_init(ssn->ssl)) {
		DEBUG2("In SSL Connect mode \n");
	}

	err = BIO_ctrl_pending(ssn->from_ssl);
	if (err > 0) {
		err = BIO_read(ssn->from_ssl, ssn->dirty_out.data,
			       sizeof(ssn->dirty_out.data));
		if (err > 0) {
			ssn->dirty_out.used = err;

		} else if (BIO_should_retry(ssn->from_ssl)) {
			record_init(&ssn->dirty_in);
			DEBUG2("  tls: Asking for more data in tunnel");
			return 1;

		} else {
			int_ssl_check(request, ssn->ssl, err, "BIO_read");
			record_init(&ssn->dirty_in);
			return 0;
		}
	} else {
		DEBUG2("SSL Application Data");

		record_init(&ssn->clean_out);
	}


	record_init(&ssn->dirty_in);
	return 1;
}
