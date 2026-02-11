cproxy_got_reply(const struct http_async *unused_ha,
	const struct gnutella_socket *s, const char *status, const header_t *header)
{
	(void) unused_ha;

	if (GNET_PROPERTY(push_proxy_trace) & SOCK_TRACE_IN) {
		g_debug("----Got push-proxy reply from %s:",
			host_addr_to_string(s->addr));
		if (log_printable(LOG_STDERR)) {
			fprintf(stderr, "%s\n", status);
			header_dump(stderr, header, "----");
		}
	}
}
