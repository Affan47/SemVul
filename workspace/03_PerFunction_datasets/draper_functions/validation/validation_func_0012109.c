tcp_dd_send_alarm_query_request(struct network_client *client, int type, int index)
{
	int ret;
	struct tcp_dd_package pkg;

	pkg.type = type;
	pkg.alarm_query.index = index;

	ret = sizeof(pkg.alarm_query) + MOFS(struct tcp_dd_package, alarm_query);
	ret = client->send(client, (char *) &pkg, ret);
	if (ret < 0)
	{
		pr_red_info("inet_send");
		return ret;
	}

	return tcp_dd_recv_response(client);
}
