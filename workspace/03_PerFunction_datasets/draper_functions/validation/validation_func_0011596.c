sin_set_port(union sockaddr_union *so, int port)
{
#ifdef HAVE_IPV6
	if (so->sin.sin_family == AF_INET6)
                so->sin6.sin6_port = htons((unsigned short)port);
	else
#endif
		so->sin.sin_port = htons((unsigned short)port);
}
