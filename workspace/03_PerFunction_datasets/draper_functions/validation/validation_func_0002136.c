insert_port(struct gr_learn_ip_node *node, u_int16_t port)
{
	u_int16_t **tmpport;
	unsigned long num;

	tmpport = node->ports;

	num = count_ports(tmpport);

	while(tmpport && *tmpport) {
		if (**tmpport == port)
			return;
		tmpport++;
	}

	if (!num) {
		node->ports = (u_int16_t **)gr_alloc(2 * sizeof(u_int16_t *));
		*(node->ports) = (u_int16_t *)gr_alloc(sizeof(u_int16_t));
		**(node->ports) = port;
	} else {
		node->ports = (u_int16_t **)gr_realloc(node->ports, (num + 2) * sizeof(u_int16_t *));
		memset(node->ports + num, 0, 2 * sizeof(u_int16_t *));
		*(node->ports + num) = (u_int16_t *)gr_alloc(sizeof(u_int16_t));
		**(node->ports + num) = port;
	}

	return;
}
