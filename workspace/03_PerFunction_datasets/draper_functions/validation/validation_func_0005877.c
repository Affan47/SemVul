client_net_timer_line_from_server(gchar *line)
	{
	gchar		name[32];

	if (!net_timer)
		return;
	sscanf(line, "%s %d", name, &net_timer->up_time);
	}
