send_query(GResolv *resolv, const unsigned char *buf, int len)
{
	GList *list;
	int nr_ns;

	if (resolv->nameserver_list == NULL)
		return -ENOENT;

	for (list = g_list_first(resolv->nameserver_list), nr_ns = 0;
				list; list = g_list_next(list), nr_ns++) {
		struct resolv_nameserver *nameserver = list->data;
		int sk, sent;

		if (nameserver->udp_channel == NULL)
			continue;

		sk = g_io_channel_unix_get_fd(nameserver->udp_channel);

		sent = send(sk, buf, len, 0);
		if (sent < 0)
			continue;
	}

	return nr_ns;
}
