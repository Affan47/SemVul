realtime_user(const char *username, struct sockaddr_in *sin)
{
	struct ast_variable *var;
	struct ast_variable *tmp;
	struct iax2_user *user=NULL;

	var = ast_load_realtime("iaxusers", "name", username, "host", "dynamic", SENTINEL);
	if (!var)
		var = ast_load_realtime("iaxusers", "name", username, "host", ast_inet_ntoa(sin->sin_addr), SENTINEL);
	if (!var && sin) {
		char porta[6];
		snprintf(porta, sizeof(porta), "%d", ntohs(sin->sin_port));
		var = ast_load_realtime("iaxusers", "name", username, "ipaddr", ast_inet_ntoa(sin->sin_addr), "port", porta, SENTINEL);
		if (!var)
			var = ast_load_realtime("iaxusers", "ipaddr", ast_inet_ntoa(sin->sin_addr), "port", porta, SENTINEL);
	}
	if (!var) {
		var = ast_load_realtime("iaxusers", "name", username, SENTINEL);


		if (var) {
			for (tmp = var; tmp; tmp = tmp->next) {
				if (!strcasecmp(tmp->name, "host")) {
					struct ast_hostent ahp;
					struct hostent *hp;
					if (!(hp = ast_gethostbyname(tmp->value, &ahp)) || memcmp(hp->h_addr, &sin->sin_addr, hp->h_length)) {

						ast_variables_destroy(var);
						var = NULL;
					}
					break;
				}
			}
		}
	}
	if (!var)
		return NULL;

	tmp = var;
	while(tmp) {

		if (!strcasecmp(tmp->name, "type")) {
			if (strcasecmp(tmp->value, "friend") &&
			    strcasecmp(tmp->value, "user")) {
				return NULL;
			}
		}
		tmp = tmp->next;
	}

	user = build_user(username, var, NULL, !ast_test_flag64((&globalflags), IAX_RTCACHEFRIENDS));

	ast_variables_destroy(var);

	if (!user)
		return NULL;

	if (ast_test_flag64((&globalflags), IAX_RTCACHEFRIENDS)) {
		ast_set_flag64(user, IAX_RTCACHEFRIENDS);
		ao2_link(users, user);
	} else {
		ast_set_flag64(user, IAX_TEMPONLY);
	}

	return user;
}
