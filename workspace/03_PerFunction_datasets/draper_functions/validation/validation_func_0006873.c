cproxy_build_request(const struct http_async *ha,
	char *buf, size_t len, const char *verb, const char *path)
{
	char addr_v4_buf[128];
	char addr_v6_buf[128];
	host_addr_t addr;
	bool has_ipv4 = FALSE;

	g_assert(len <= INT_MAX);

	addr = listen_addr();
	addr_v4_buf[0] = '\0';
	if (is_host_addr(addr)) {
		has_ipv4 = TRUE;
		concat_strings(addr_v4_buf, sizeof addr_v4_buf,
			"X-Node: ",
			host_addr_port_to_string(addr, GNET_PROPERTY(listen_port)),
			"\r\n",
			(void *) 0);
	}

	addr = listen_addr6();
	addr_v6_buf[0] = '\0';
	if (is_host_addr(addr)) {


		concat_strings(addr_v6_buf, sizeof addr_v6_buf,
			has_ipv4 ? "X-Node-IPv6: " : "X-Node: ",
			host_addr_port_to_string(addr, GNET_PROPERTY(listen_port)),
			"\r\n",
			(void *) 0);
	}

	return str_bprintf(buf, len,
		"%s %s HTTP/1.1\r\n"
		"User-Agent: %s\r\n"
		"Connection: close\r\n"
		"Host: %s\r\n"
		"X-Token: %s\r\n"
		"%s"
		"%s"
		"\r\n",
		verb, path, version_string,
		http_async_remote_host_port(ha),
		tok_version(),
		addr_v4_buf,
		addr_v6_buf);
}
