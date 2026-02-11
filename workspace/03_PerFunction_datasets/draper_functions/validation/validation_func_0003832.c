open_vrrp_socket(sa_family_t family, int proto, int idx, int unicast)
{
	interface_t *ifp;
	int fd = -1;


	ifp = if_get_by_ifindex(idx);


	fd = socket(family, SOCK_RAW, proto);
	if (fd < 0) {
		int err = errno;
		log_message(LOG_INFO, "cant open raw socket. errno=%d", err);
		return -1;
	}


	if (!unicast)
		if_join_vrrp_group(family, &fd, ifp, proto);
	if (fd < 0)
		return -1;

	if (family == AF_INET) {

		if_setsockopt_bindtodevice(&fd, ifp);
	}

	return fd;
}
