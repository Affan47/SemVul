replica_added(gfarm_int32_t net_fd,
    gfarm_int32_t flags, gfarm_int64_t mtime_sec, gfarm_int32_t mtime_nsec,
    gfarm_off_t size, const char *request)
{
	gfarm_error_t e;
	static const char diag[] = "GFM_PROTO_REPLICA_ADDED2";

	gfm_client_compound_put_fd_request(net_fd, diag);
	if ((e = gfm_client_replica_added2_request(gfm_server,
	    flags, mtime_sec, mtime_nsec, size))
	    != GFARM_ERR_NO_ERROR)
		fatal_metadb_proto(GFARM_MSG_1000514, request, diag, e);
	gfm_client_compound_put_fd_result(diag);
	if ((e = gfm_client_replica_added_result(gfm_server))
	    != GFARM_ERR_NO_ERROR) {
		if (debug_mode)
			gflog_info(GFARM_MSG_1000518,
			    "%s result on %s: %s", diag, request,
			    gfarm_error_string(e));
	} else
		gfm_client_compound_end(diag);

	return (e);
}
