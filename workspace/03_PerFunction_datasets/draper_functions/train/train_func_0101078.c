alloc_vs(char *ip, char *port)
{
	int size = strlen(port);
	virtual_server_t *new;

	new = (virtual_server_t *) MALLOC(sizeof(virtual_server_t));

	if (!strcmp(ip, "group")) {
		new->vsgname = (char *) MALLOC(size + 1);
		memcpy(new->vsgname, port, size);
	} else if (!strcmp(ip, "fwmark")) {
		new->vfwmark = atoi(port);
	} else {
		inet_stosockaddr(ip, port, &new->addr);
	}

	new->delay_loop = KEEPALIVED_DEFAULT_DELAY;
	strncpy(new->timeout_persistence, "0", 1);
	new->virtualhost = NULL;
	new->alpha = 0;
	new->omega = 0;
	new->quorum_up = NULL;
	new->quorum_down = NULL;
	new->quorum = 1;
	new->hysteresis = 0;
	new->quorum_state = UP;

	list_add(check_data->vs, new);
}
