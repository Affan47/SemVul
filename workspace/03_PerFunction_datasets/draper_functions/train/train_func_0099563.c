sock_watch_cb(GIOChannel *source, GIOCondition condition,
			      gpointer data)
{
	SockInfo *sock = (SockInfo *)data;

	if ((condition & sock->condition) == 0)
		return TRUE;

	return sock->callback(sock, sock->condition, sock->data);
}
