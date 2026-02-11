on_login_success(struct hub_info* hub, struct hub_user* u)
{

	if (!uman_send_user_list(hub, hub->users, u))
		return;


	user_set_state(u, state_normal);
	uman_add(hub->users, u);


	if (user_is_logged_in(u))
		route_info_message(hub, u);

	plugin_log_user_login_success(hub, u);


	net_con_clear_timeout(u->connection);
}
