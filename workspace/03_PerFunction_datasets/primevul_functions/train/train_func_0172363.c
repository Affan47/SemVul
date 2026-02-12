static void build_radius_packet(AUTH_HDR *request, CONST char *user, CONST char *password, radius_conf_t *conf)
{
	char hostname[256];
	uint32_t ipaddr;

	hostname[0] = '\0';
	gethostname(hostname, sizeof(hostname) - 1);

	request->length = htons(AUTH_HDR_LEN);

	if (password) {
		get_random_vector(request->vector);
	}

	add_attribute(request, PW_USER_NAME, (unsigned char *) user, strlen(user));


	if (password) {
		add_password(request, PW_PASSWORD, password, conf->server->secret);


	} else if (request->code != PW_ACCOUNTING_REQUEST) {
		add_password(request, PW_PASSWORD, "", conf->server->secret);
	}


	if ((conf->server->ip.s_addr == ntohl(0x7f000001)) || (!hostname[0])) {
		ipaddr = 0x7f000001;
	} else {
		struct hostent *hp;

		if ((hp = gethostbyname(hostname)) == (struct hostent *) NULL) {
			ipaddr = 0x00000000;
		} else {
			ipaddr = ntohl(*(uint32_t *) hp->h_addr);
		}
	}


	if (ipaddr) {
		add_int_attribute(request, PW_NAS_IP_ADDRESS, ipaddr);
	}


	if (conf->client_id && *conf->client_id) {
		add_attribute(request, PW_NAS_IDENTIFIER, (unsigned char *) conf->client_id, strlen(conf->client_id));
	}


	add_int_attribute(request, PW_NAS_PORT_ID, getpid());
	add_int_attribute(request, PW_NAS_PORT_TYPE, PW_NAS_PORT_TYPE_VIRTUAL);
}
