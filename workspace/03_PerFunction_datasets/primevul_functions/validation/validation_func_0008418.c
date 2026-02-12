static int create_tls_random(uint8_t * dst)
{
	uint32_t tim;
	int ret;


	tim = gnutls_time(NULL);

	_gnutls_write_uint32(tim, dst);

	ret =
	    _gnutls_rnd(GNUTLS_RND_NONCE, &dst[3], GNUTLS_RANDOM_SIZE - 3);
	if (ret < 0) {
		gnutls_assert();
		return ret;
	}

	return 0;
}
