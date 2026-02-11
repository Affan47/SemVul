m_users(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(hunt_server(client_p, source_p, ":%s USERS :%s", 1, parc, parv) == HUNTED_ISME)
	{
		sendto_one_numeric(source_p, RPL_LOCALUSERS,
				   form_str(RPL_LOCALUSERS),
				   (int)rb_dlink_list_length(&lclient_list),
				   Count.max_loc,
				   (int)rb_dlink_list_length(&lclient_list),
				   Count.max_loc);

		sendto_one_numeric(source_p, RPL_GLOBALUSERS,
				   form_str(RPL_GLOBALUSERS),
				   Count.total, Count.max_tot,
				   Count.total, Count.max_tot);
	}

	return 0;
}
