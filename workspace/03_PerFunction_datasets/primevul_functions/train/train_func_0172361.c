static int host2server(radius_server_t *server)
{
	char *p;

	if ((p = strchr(server->hostname, ':')) != NULL) {
		*(p++) = '\0';
	}

	if ((server->ip.s_addr = get_ipaddr(server->hostname)) == ((uint32_t)0)) {
		DPRINT(LOG_DEBUG, "DEBUG: get_ipaddr(%s) returned 0.\n", server->hostname);
		return PAM_AUTHINFO_UNAVAIL;
	}


	if (!server->port) {
		if (p && isdigit(*p)) {
			unsigned int i = atoi(p) & 0xffff;

			if (!server->accounting) {
				server->port = htons((uint16_t) i);
			} else {
				server->port = htons((uint16_t) (i + 1));
			}
		} else {
			struct servent *svp;

			if (p) {
				svp = getservbyname (p, "udp");

				DPRINT(LOG_DEBUG, "DEBUG: getservbyname('%s', udp) returned %p.\n", p, svp);
				*(--p) = ':';
			} else {
				if (!server->accounting) {
					svp = getservbyname ("radius", "udp");
					DPRINT(LOG_DEBUG, "DEBUG: getservbyname(radius, udp) returned %p.\n", svp);
				} else {
					svp = getservbyname ("radacct", "udp");
					DPRINT(LOG_DEBUG, "DEBUG: getservbyname(radacct, udp) returned %p.\n", svp);
				}
			}

			if (svp == (struct servent *) 0) {

				return PAM_AUTHINFO_UNAVAIL;
			}

			server->port = svp->s_port;
		}
	}

	return PAM_SUCCESS;
}
