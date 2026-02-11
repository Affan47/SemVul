gfarm_client_process_set(struct gfs_connection *gfs_server,
	struct gfm_connection *gfm_server)
{
	gfarm_int32_t key_type;
	const char *key;
	size_t key_size;
	gfarm_pid_t pid;
	gfarm_error_t e = gfm_client_process_get(gfm_server,
	    &key_type, &key, &key_size, &pid);

	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000986,
			"gfm_client_process_get() failed: %s",
			gfarm_error_string(e));
		return (e);
	}
	return (gfs_client_process_set(gfs_server,
	    key_type, key, key_size, pid));
}
