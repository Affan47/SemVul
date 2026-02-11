sin_set_ip(union sockaddr_union *so, const IPADDR *ip)
{
	if (ip == NULL) {
#ifdef HAVE_IPV6
		so->sin6.sin6_family = AF_INET6;
		so->sin6.sin6_addr = in6addr_any;
#else
		so->sin.sin_family = AF_INET;
		so->sin.sin_addr.s_addr = INADDR_ANY;
#endif
		return;
	}

	so->sin.sin_family = ip->family;
#ifdef HAVE_IPV6
	if (ip->family == AF_INET6)
		memcpy(&so->sin6.sin6_addr, &ip->ip, sizeof(ip->ip));
	else
#endif
		memcpy(&so->sin.sin_addr, &ip->ip, 4);
}
