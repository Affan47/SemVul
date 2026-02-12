static void release_ip(const char *ip, void *priv)
{
	char addr[INET6_ADDRSTRLEN];
	char *p = addr;

	client_socket_addr(get_client_fd(),addr,sizeof(addr));

	if (strncmp("::ffff:", addr, 7) == 0) {
		p = addr + 7;
	}

	if ((strcmp(p, ip) == 0) || ((p != addr) && strcmp(addr, ip) == 0)) {


		DEBUG(0,("Got release IP message for our IP %s - exiting immediately\n",
			ip));


		_exit(1);
	}
}
