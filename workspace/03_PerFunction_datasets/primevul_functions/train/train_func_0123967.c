process_cookie(ns_client_t *client, isc_buffer_t *buf, size_t optlen) {
	ns_altsecret_t *altsecret;
	unsigned char dbuf[COOKIE_SIZE];
	unsigned char *old;
	isc_stdtime_t now;
	uint32_t when;
	uint32_t nonce;
	isc_buffer_t db;


	if ((!client->sctx->answercookie) ||
	    (client->attributes & NS_CLIENTATTR_WANTCOOKIE) != 0)
	{
		isc_buffer_forward(buf, (unsigned int)optlen);
		return;
	}

	client->attributes |= NS_CLIENTATTR_WANTCOOKIE;

	ns_stats_increment(client->sctx->nsstats, ns_statscounter_cookiein);

	if (optlen != COOKIE_SIZE) {


		INSIST(optlen >= 8U);
		memmove(client->cookie, isc_buffer_current(buf), 8);
		isc_buffer_forward(buf, (unsigned int)optlen);

		if (optlen == 8U) {
			ns_stats_increment(client->sctx->nsstats,
					   ns_statscounter_cookienew);
		} else {
			ns_stats_increment(client->sctx->nsstats,
					   ns_statscounter_cookiebadsize);
		}
		return;
	}


	old = isc_buffer_current(buf);
	memmove(client->cookie, old, 8);
	isc_buffer_forward(buf, 8);
	nonce = isc_buffer_getuint32(buf);
	when = isc_buffer_getuint32(buf);
	isc_buffer_forward(buf, 8);


	isc_stdtime_get(&now);
	if (isc_serial_gt(when, (now + 300)) ||
	    isc_serial_lt(when, (now - 3600)))
	{
		ns_stats_increment(client->sctx->nsstats,
				   ns_statscounter_cookiebadtime);
		return;
	}

	isc_buffer_init(&db, dbuf, sizeof(dbuf));
	compute_cookie(client, when, nonce, client->sctx->secret, &db);

	if (isc_safe_memequal(old, dbuf, COOKIE_SIZE)) {
		ns_stats_increment(client->sctx->nsstats,
				   ns_statscounter_cookiematch);
		client->attributes |= NS_CLIENTATTR_HAVECOOKIE;
		return;
	}

	for (altsecret = ISC_LIST_HEAD(client->sctx->altsecrets);
	     altsecret != NULL; altsecret = ISC_LIST_NEXT(altsecret, link))
	{
		isc_buffer_init(&db, dbuf, sizeof(dbuf));
		compute_cookie(client, when, nonce, altsecret->secret, &db);
		if (isc_safe_memequal(old, dbuf, COOKIE_SIZE)) {
			ns_stats_increment(client->sctx->nsstats,
					   ns_statscounter_cookiematch);
			client->attributes |= NS_CLIENTATTR_HAVECOOKIE;
			return;
		}
	}

	ns_stats_increment(client->sctx->nsstats,
			   ns_statscounter_cookienomatch);
}
