recv_hello_verify_request(gnutls_session_t session,
				  uint8_t * data, int datalen)
{
	ssize_t len = datalen;
	size_t pos = 0;
	uint8_t cookie_len;
	unsigned int nb_verifs;

	if (!IS_DTLS(session)
	    || session->security_parameters.entity == GNUTLS_SERVER) {
		gnutls_assert();
		return GNUTLS_E_INTERNAL_ERROR;
	}

	nb_verifs = ++session->internals.dtls.hsk_hello_verify_requests;
	if (nb_verifs >= MAX_HANDSHAKE_HELLO_VERIFY_REQUESTS) {


		gnutls_assert();
		return GNUTLS_E_UNEXPECTED_PACKET;
	}


	DECR_LEN(len, 2);
	pos += 2;

	DECR_LEN(len, 1);
	cookie_len = data[pos];
	pos++;

	if (cookie_len > DTLS_MAX_COOKIE_SIZE) {
		gnutls_assert();
		return GNUTLS_E_UNEXPECTED_PACKET_LENGTH;
	}

	DECR_LEN(len, cookie_len);

	session->internals.dtls.cookie_len = cookie_len;
	memcpy(session->internals.dtls.cookie, &data[pos], cookie_len);

	if (len != 0) {
		gnutls_assert();
		return GNUTLS_E_UNEXPECTED_PACKET_LENGTH;
	}


	handshake_hash_buffer_empty(session);

	return 0;
}
