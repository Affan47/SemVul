socket_connect_by_name_helper(const host_addr_t *addrs, size_t n,
	void *user_data)
{
	struct gnutella_socket *s = user_data;
	host_addr_t addr;
	bool can_tls;

	socket_check(s);
	g_assert(addrs);

	if (n < 1 || s->type == SOCK_TYPE_DESTROYING) {
		s->adns |= SOCK_ADNS_FAILED | SOCK_ADNS_BADNAME;
		s->adns_msg = "Could not resolve address";
		goto finish;
	}

	addr = addrs[random_value(n - 1)];
	can_tls = 0 != (SOCK_F_TLS & s->flags) || tls_cache_lookup(addr, s->port);

	if (can_tls && socket_tls_banned(addr, s->port))
		can_tls = FALSE;

	if (
		s->net != host_addr_net(addr) ||
		(can_tls && 0 == (SOCK_F_TLS & s->flags))
	) {
		s->net = host_addr_net(addr);

		if (is_valid_fd(s->file_desc)) {
			s_close(s->file_desc);
			s->file_desc = INVALID_SOCKET;
		}
		if (can_tls) {
			s->flags |= SOCK_F_TLS;
		}
		if (socket_connect_prepare(s, addr, s->port, s->type, s->flags)) {
			s->adns |= SOCK_ADNS_FAILED;
			s->adns_msg = "Could not resolve address";
			goto finish;
		}
	}


	if (socket_connect_finalize(s, addr, FALSE)) {
		s->adns |= SOCK_ADNS_FAILED;
		s->adns_msg = "Connection failed";
		goto finish;
	}

finish:
	s->adns &= ~SOCK_ADNS_PENDING;
	if ((s->adns & SOCK_ADNS_ASYNC) && (s->adns & SOCK_ADNS_FAILED)) {
		socket_destroy(s, s->adns_msg);
	}
}
