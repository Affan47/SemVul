new_net(gchar *name)
	{
	NetMon		*net;

	net = g_new0(NetMon, 1);
	net->name = g_strdup(name);
	if (strcmp(name, "lo"))
		net->enabled = TRUE;
	net->chart_labels = TRUE;
	net->label = g_strdup("");
	net->launch.command = g_strdup("");
	net->launch.tooltip_comment = g_strdup("");
	net->alert_uses_rx = net->alert_uses_tx = TRUE;
	net_mon_list = g_list_insert_sorted(net_mon_list, net,
				(GCompareFunc) strcmp_net_name);

	net_stat_init(net);

	return net;
	}
