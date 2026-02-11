socket_create_and_bind(const host_addr_t bind_addr,
	const uint16 port, const int type)
{
	bool socket_failed;
	socket_fd_t fd;
	int saved_errno, family;
	int protocol;

	g_assert(SOCK_DGRAM == type || SOCK_STREAM == type);

	if (1 == port) {
		errno = EINVAL;
		return INVALID_SOCKET;
	}
	if (NET_TYPE_NONE == host_addr_net(bind_addr)) {
		errno = EINVAL;
		return INVALID_SOCKET;
	}
	family = host_addr_family(bind_addr);
	if (-1 == family) {
		errno = EINVAL;
		return INVALID_SOCKET;
	}

	protocol = (SOCK_DGRAM == type) ? IPPROTO_UDP : IPPROTO_TCP;
	fd = socket(family, type, protocol);

	if (!is_valid_fd(fd)) {
		socket_failed = TRUE;
		saved_errno = errno;
	} else {
		static const int enable = 1;
		socket_addr_t addr;
		socklen_t len;


		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof enable);

#if defined(HAS_IPV6) && defined(IPV6_V6ONLY)
		if (
			host_addr_is_ipv6(bind_addr) &&
			setsockopt(fd, sol_ipv6(), IPV6_V6ONLY, &enable, sizeof enable)
		) {
			g_warning("setsockopt() failed for IPV6_V6ONLY: %m");
		}
#endif


		socket_failed = FALSE;
		len = socket_addr_set(&addr, bind_addr, port);
		if (-1 == bind(fd, socket_addr_get_const_sockaddr(&addr), len)) {
			saved_errno = errno;
			s_close(fd);
			fd = INVALID_SOCKET;
		} else {
			saved_errno = 0;
		}
	}

#if defined(HAS_SOCKER_GET)
	if (!is_valid_fd(fd) && (EACCES == saved_errno || EPERM == saved_errno)) {
		char addr_str[128];

		host_addr_to_string_buf(bind_addr, addr_str, sizeof addr_str);
		fd = socker_get(family, type, 0, addr_str, port);
		if (!is_valid_fd(fd)) {
			g_warning("socker_get() failed: %m");
		}
	}
#else
	(void) saved_errno;
#endif

	if (!is_valid_fd(fd)) {
		const char *type_str = SOCK_DGRAM == type ? "datagram" : "stream";
		const char *net_str = net_type_to_string(host_addr_net(bind_addr));

		if (socket_failed) {
			g_warning("unable to create the %s (%s) socket: %m",
				type_str, net_str);
		} else {
			char bind_addr_str[HOST_ADDR_PORT_BUFLEN];

			host_addr_port_to_string_buf(bind_addr, port,
				bind_addr_str, sizeof bind_addr_str);
			g_warning("unable to bind() the %s (%s) socket to %s: %m",
				type_str, net_str, bind_addr_str);
		}
	} else {
		fd = get_non_stdio_fd(fd);
		set_close_on_exec(fd);
		fd_set_nonblocking(fd);
	}

	return fd;
}
