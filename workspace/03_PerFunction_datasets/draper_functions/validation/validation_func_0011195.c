gfarm_sockopt_config_add_internal(struct gfarm_param_config ***lastp,
	char *config, struct gfarm_hostspec *hsp)
{
	gfarm_error_t e;
	int param_type_index;
	long value;

	e = gfarm_sockopt_initialize();
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000899,
			"Initialization of socket option failed: %s",
			gfarm_error_string(e));
		return (e);
	}
	e = gfarm_param_config_parse_long(NSOCKOPTS, gfarm_sockopt_type_table,
	    config, &param_type_index, &value);
	if (e == GFARM_ERR_NO_SUCH_OBJECT) {
		gflog_debug(GFARM_MSG_1000900,
			"Unknown socket option (%s)",
			config);
		return (GFARM_ERRMSG_UNKNOWN_SOCKET_OPTION);
	}
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1000901,
			"gfarm_param_config_parse_long(%s) failed: %s",
			config,
			gfarm_error_string(e));
		return (e);
	}
	return (gfarm_param_config_add_long(lastp,
	    param_type_index, value, hsp));
}
