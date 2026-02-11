create_tcp_socket(ttp_session_t *session, const char *server_name, u_int16_t server_port)
{
    struct addrinfo  hints;
    struct addrinfo *info;
    struct addrinfo *info_save;
    char             buffer[10];
    int              socket_fd;
    int              yes = 1;
    int              status;


    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = session->parameter->ipv6_yn ? AF_INET6 : AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    sprintf(buffer, "%d", server_port);
    status = getaddrinfo(server_name, buffer, &hints, &info);
    if (status)
	return warn("Error in getting address information for server");


    info_save = info;
    do {


	socket_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (socket_fd < 0) {
	    warn("Could not create socket");
	    continue;
	}


	status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (status < 0) {
	    warn("Could not make socket reusable");
	    close(socket_fd);
	    continue;
	}


	status = setsockopt(socket_fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes));
	if (status < 0) {
	    warn("Could not disable Nagle's algorithm");
	    close(socket_fd);
	    continue;
	}


	status = connect(socket_fd, info->ai_addr, info->ai_addrlen);
	if (status == 0) {


	    session->server_address = (struct sockaddr *) malloc(info->ai_addrlen);
            session->server_address_length = info->ai_addrlen;
	    if (session->server_address == NULL)
		error("Could not allocate space for server address");
	    memcpy(session->server_address, info->ai_addr, info->ai_addrlen);
	    break;
	}

    } while ((info = info->ai_next) != NULL);


    freeaddrinfo(info_save);


    if (info == NULL)
	return warn("Error in connecting to Tsunami server");


    return socket_fd;
}
