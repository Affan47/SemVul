gfm_host_get_canonical_self_name(struct gfm_connection *gfm_server,
	char **canonical_hostnamep, int *portp)
{
	gfarm_error_t e;
	static char *canonical_self_name = NULL;
	static int port;
	static gfarm_error_t error_save = GFARM_ERR_NO_ERROR;

	if (canonical_self_name == NULL) {
		if (error_save != GFARM_ERR_NO_ERROR)
			return (error_save);
		e = gfm_host_get_canonical_name(gfm_server,
		    gfarm_host_get_self_name(), &canonical_self_name, &port);
		if (e != GFARM_ERR_NO_ERROR) {
			error_save = e;
			gflog_debug(GFARM_MSG_1000870,
				"gfm_host_get_canonical_name() failed: %s",
				gfarm_error_string(e));
			return (e);
		}
	}
	*canonical_hostnamep = canonical_self_name;
	*portp = port;
	return (GFARM_ERR_NO_ERROR);
}
