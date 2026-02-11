gkrellm_net_assign_data(gchar *name, gulong rx, gulong tx)
	{
	GList	*list;
	NetData	*net;

	for (list = net_list; list; list = list->next)
		{
		net = (NetData *) list->data;
		if (!strcmp(net->name, name))
			{
			if (net->rx != rx || net->tx != tx)
				net->changed = TRUE;
			else
				net->changed = FALSE;
			break;
			}
		}
	if (!list)
		net = net_new(name);

	if (GK.second_tick && !net_use_routed)
		net->up = TRUE;
	net->rx = rx;
	net->tx = tx;
	}
