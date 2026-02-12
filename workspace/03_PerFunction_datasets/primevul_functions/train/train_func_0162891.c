int _gnutls_session_is_ecc(gnutls_session_t session)
{
	gnutls_kx_algorithm_t kx;


	kx = _gnutls_cipher_suite_get_kx_algo(session->security_parameters.
					      cipher_suite);

	return _gnutls_kx_is_ecc(kx);
}
