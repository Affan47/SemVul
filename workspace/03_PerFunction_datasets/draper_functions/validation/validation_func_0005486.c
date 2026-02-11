host_address_get(const char *name, int port,
	int (*match)(struct gfarm_hostspec *, const char *, struct sockaddr *),
	struct gfarm_hostspec *hostspec,
	struct sockaddr *peer_addr, char **if_hostnamep)
{
	struct addrinfo hints, *res, *res0;
	int error;
	char *n, sbuf[NI_MAXSERV];

	snprintf(sbuf, sizeof(sbuf), "%u", port);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	error = gfarm_getaddrinfo(name, sbuf, &hints, &res0);
	if (error != 0) {
		gflog_debug(GFARM_MSG_1000878,
			"Unknown host (%s): %s",
			name,
			gfarm_error_string(GFARM_ERR_UNKNOWN_HOST));
		return (GFARM_ERR_UNKNOWN_HOST);
	}

	for (res = res0; res != NULL; res = res->ai_next) {
		if ((*match)(hostspec, name, res->ai_addr)) {

			if (res0->ai_addr->sa_family != AF_INET ||
			    res0->ai_addrlen > sizeof(*peer_addr)) {
				gfarm_freeaddrinfo(res0);
				gflog_debug(GFARM_MSG_1000879,
					"Address family not supported by "
					"protocol family (%s): %s",
					name,
					gfarm_error_string(
		GFARM_ERR_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL_FAMILY));
				return (GFARM_ERR_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL_FAMILY);
			}
			if (if_hostnamep != NULL) {

				n = strdup(name);
				if (n == NULL) {
					gfarm_freeaddrinfo(res0);
					gflog_debug(GFARM_MSG_1000880,
						"allocation of hostname failed"
						": %s",
						gfarm_error_string(
							GFARM_ERR_NO_MEMORY));
					return (GFARM_ERR_NO_MEMORY);
				}
				*if_hostnamep = n;
			}
			memset(peer_addr, 0, sizeof(*peer_addr));
			memcpy(peer_addr, res0->ai_addr, sizeof(*peer_addr));
			gfarm_freeaddrinfo(res0);
			return (GFARM_ERR_NO_ERROR);
		}
	}
	gfarm_freeaddrinfo(res0);
	gflog_debug(GFARM_MSG_1000881,
		"failed to get host address (%s): %s",
		name,
		gfarm_error_string(GFARM_ERR_NO_SUCH_OBJECT));
	return (GFARM_ERR_NO_SUCH_OBJECT);
}
