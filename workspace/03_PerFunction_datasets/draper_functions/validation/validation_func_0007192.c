fr_socket(fr_ipaddr_t *ipaddr, int port)
{
	int sockfd;
	struct sockaddr_storage salocal;
	socklen_t	salen;

	if ((port < 0) || (port > 65535)) {
		fr_strerror_printf("Port %d is out of allowed bounds", port);
		return -1;
	}

	sockfd = socket(ipaddr->af, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fr_strerror_printf("cannot open socket: %s", strerror(errno));
		return sockfd;
	}

#ifdef WITH_UDPFROMTO


	if (udpfromto_init(sockfd) != 0) {
		close(sockfd);
		fr_strerror_printf("cannot initialize udpfromto: %s", strerror(errno));
		return -1;
	}
#endif

	if (fr_nonblock(sockfd) < 0) {
		close(sockfd);
		return -1;
	}

	if (!fr_ipaddr2sockaddr(ipaddr, port, &salocal, &salen)) {
		return sockfd;
	}

#ifdef HAVE_STRUCT_SOCKADDR_IN6
	if (ipaddr->af == AF_INET6) {


#ifdef IPV6_V6ONLY

		if (IN6_IS_ADDR_UNSPECIFIED(&ipaddr->ipaddr.ip6addr)) {
			int on = 1;

			setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY,
				   (char *)&on, sizeof(on));
		}
#endif
	}
#endif

	if (ipaddr->af == AF_INET) {
		UNUSED int flag;

#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)


		flag = IP_PMTUDISC_DONT;
		setsockopt(sockfd, IPPROTO_IP, IP_MTU_DISCOVER,
			   &flag, sizeof(flag));
#endif

#if defined(IP_DONTFRAG)


		flag = 0;
		setsockopt(sockfd, IPPROTO_IP, IP_DONTFRAG,
			   &flag, sizeof(flag));
#endif
	}

	if (bind(sockfd, (struct sockaddr *) &salocal, salen) < 0) {
		close(sockfd);
		fr_strerror_printf("cannot bind socket: %s", strerror(errno));
		return -1;
	}

	return sockfd;
}
