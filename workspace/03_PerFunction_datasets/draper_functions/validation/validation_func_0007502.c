sig_disconnected(IRC_SERVER_REC *server)
{
	g_return_if_fail(server != NULL);

	if (!IS_IRC_SERVER(server))
		return;

	g_slist_free(server->ctcpqueue);
        server->ctcpqueue = NULL;
}
