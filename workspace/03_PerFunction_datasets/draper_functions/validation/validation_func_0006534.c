ntp_got_reply(host_addr_t addr, const void *payload, size_t len)
{
	const struct ntp_msg *m;
	uint8 version;
	uint8 mode;
	tm_t received;
	tm_t sent;
	tm_t replied;
	tm_t got;
	tm_t offset;
	double clock_offset;

	tm_now_exact(&got);

	g_info("NTP detected at %s", host_addr_to_string(addr));

	if (len != NTP_MINSIZE && len != NTP_MAXSIZE) {
		g_warning("got weird reply from NTP server (%zu bytes)", len);
		return;
	}

	m = payload;
	mode = m->flags & 0x7;
	version = (m->flags >> 3) & 0x7;

	if (mode != NTP_SERVER) {
		g_warning("got reply from NTP server with weird mode (%d)", mode);
		return;
	}

	if (GNET_PROPERTY(tsync_debug))
		g_debug("NTP got %s reply from NTP-%u server, stratum %u",
			NTP_MINSIZE == len ? "regular" : "auth", version, m->stratum);


	gnet_prop_set_boolean_val(PROP_HOST_RUNS_NTP, TRUE);
	gnet_prop_set_boolean_val(PROP_NTP_DETECTED, TRUE);


	ntp_tm_deserialize(m->originate_timestamp, &sent);
	ntp_tm_deserialize(m->receive_timestamp, &received);
	ntp_tm_deserialize(m->transmit_timestamp, &replied);

	offset = received;
	tm_sub(&offset, &sent);
	tm_add(&offset, &replied);
	tm_sub(&offset, &got);

	clock_offset = tm2f(&offset) / 2;

	if (GNET_PROPERTY(tsync_debug) > 1)
		g_debug("NTP local clock offset is %g secs",
			(double) clock_offset);

	gnet_prop_set_guint32_val(PROP_CLOCK_SKEW, (uint32) clock_offset);

	g_info("detected NTP-%u, stratum %u, offset %g secs",
		version, m->stratum, (double) clock_offset);
}
