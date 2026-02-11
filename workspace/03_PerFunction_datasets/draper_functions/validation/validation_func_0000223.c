spam_prune_old(void *key, void *value, size_t u_len, void *u_data)
{
	const gnet_host_t *h = key;
	const struct spamdata *sd = value;
	time_delta_t d;
	double p = 0.0;
	bool expired;

	(void) u_len;
	(void) u_data;


	d = delta_time(tm_time(), sd->last_time);
	if (sd->create_time == sd->last_time) {
		expired = d > SPAM_STABLE_LIFETIME;
	} else {
		p = stable_still_alive_probability(sd->create_time, sd->last_time);
		expired = p < SPAM_STABLE_PROBA;
	}

	if (GNET_PROPERTY(spam_debug) > 5) {
		g_debug("SPAM cached %s life=%s last_seen=%s, p=%.2f%%%s",
			host_addr_to_string(gnet_host_get_addr(h)),
			compact_time(delta_time(sd->last_time, sd->create_time)),
			compact_time2(d), p * 100.0,
			expired ? " [EXPIRED]" : "");
	}

	return expired;
}
