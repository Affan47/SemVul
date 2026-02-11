http_open_port_if(int port, int ssl, Octstr *interface)
{
    struct server *p;

    if (ssl)
        info(0, "HTTP: Opening SSL server at port %d.", port);
    else
        info(0, "HTTP: Opening server at port %d.", port);
    p = gw_malloc(sizeof(*p));
    p->port = port;
    p->ssl = ssl;
    p->fd = make_server_socket(port, (interface ? octstr_get_cstr(interface) : NULL));
    if (p->fd == -1) {
	gw_free(p);
    	return -1;
    }

    port_add(port);
    gwlist_produce(new_server_sockets, p);
    keep_servers_open = 1;
    start_server_thread();
    gwthread_wakeup(server_thread_id);

    return 0;
}
