detach_server_conf(struct Client *client_p)
{
	struct server_conf *server_p = client_p->localClient->att_sconf;

	if(server_p == NULL)
		return;

	client_p->localClient->att_sconf = NULL;
	server_p->servers--;
	CurrUsers(server_p->class)--;

	if(ServerConfIllegal(server_p) && !server_p->servers)
	{

		if(MaxUsers(server_p->class) < 0 && CurrUsers(server_p->class) <= 0)
			free_class(server_p->class);

		rb_dlinkDelete(&server_p->node, &server_conf_list);
		free_server_conf(server_p);
	}
}
