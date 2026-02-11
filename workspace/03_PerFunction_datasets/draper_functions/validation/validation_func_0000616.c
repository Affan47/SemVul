parq_upload_abusing(
	struct upload *u, struct parq_ul_queued *puq,
	time_t now, time_t org_retry)
{
	gnet_stats_inc_general(GNR_PARQ_RETRY_AFTER_VIOLATION);

	if (
		delta_time(puq->ban_timeout, now) > 0 &&
		GNET_PROPERTY(parq_ban_bad_maxcountwait) != 0
	)
		puq->ban_countwait++;

	if (GNET_PROPERTY(parq_debug)) g_warning("[PARQ UL] "
		"host %s (%s) re-requested \"%s\" too soon (%s early, warn #%u)",
		host_addr_port_to_string(u->socket->addr, u->socket->port),
		upload_vendor_str(u),
		u->name, short_time(delta_time(org_retry, now)),
		puq->ban_countwait);

	if (
		delta_time(puq->ban_timeout, now) > 0 &&
		puq->ban_countwait >= GNET_PROPERTY(parq_ban_bad_maxcountwait)
	) {


		gnet_stats_inc_general(GNR_PARQ_RETRY_AFTER_KICK_OUT);

		if (GNET_PROPERTY(parq_debug)) g_warning(
			"[PARQ UL] "
			"punishing %s (%s) for re-requesting \"%s\" %s early [%s]",
			host_addr_port_to_string(u->socket->addr, u->socket->port),
			upload_vendor_str(u),
			u->name, short_time(delta_time(org_retry, now)),
			guid_hex_str(&puq->id));

		parq_add_banned_source(u->addr, delta_time(puq->retry, now));
		parq_upload_force_remove(u);
		return TRUE;
	}

	puq->ban_timeout = time_advance(now, parq_upload_ban_window);

	return FALSE;
}
