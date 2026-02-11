gfm_server_replica_added(struct peer *peer, int from_client, int skip)
{
	gfarm_error_t e;
	gfarm_int32_t flags, mtime_nsec;
	gfarm_int64_t mtime_sec;
	static const char diag[] = "GFM_PROTO_REPLICA_ADDED";

	e = gfm_server_get_request(peer, diag, "ili",
	    &flags, &mtime_sec, &mtime_nsec);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001967, "%s request failed: %s",
			diag, gfarm_error_string(e));
		return (e);
	}
	if (skip)
		return (GFARM_ERR_NO_ERROR);
	giant_lock();

	e = gfm_server_replica_added_common(diag, peer, from_client,
		flags, mtime_sec, mtime_nsec, -1);

	giant_unlock();
	return (gfm_server_put_reply(peer, diag, e, ""));
}
