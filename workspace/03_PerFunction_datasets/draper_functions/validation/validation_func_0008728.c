remote_ending_action_parser(struct nv_pair *nv, int line,
                remote_conf_t *config)
{
	if (strcasecmp(nv->value, "reconnect") == 0) {
		config->remote_ending_action = FA_RECONNECT;
		return 0;
	}
	return action_parser(nv, line, &config->remote_ending_action,
			&config->remote_ending_exe);
}
