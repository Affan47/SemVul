mo_operwall(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(!IsOperOperwall(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS),
			   me.name, source_p->name, "operwall");
		return 0;
	}

	sendto_wallops_flags(UMODE_OPERWALL, source_p, "OPERWALL - %s", parv[1]);
	sendto_server(client_p, NULL, CAP_TS6, NOCAPS, ":%s OPERWALL :%s",
		      use_id(source_p), parv[1]);

	return 0;
}
