virtual_server_find(const char *name)
{
	int rcode;
	virtual_server_t *server;

	rcode = virtual_server_idx(name);
	for (server = virtual_servers[rcode];
	     server != NULL;
	     server = server->next) {
		if (!name && !server->name) break;

		if ((name && server->name) &&
		    (strcmp(name, server->name) == 0)) break;
	}

	return server;
}
