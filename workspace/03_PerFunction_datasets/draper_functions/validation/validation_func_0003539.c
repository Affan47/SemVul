set_source_ip(char *arg)
{
	struct sockaddr_in src;

	memset(&src, 0, sizeof(src));
	src.sin_family = AF_INET;
	if((src.sin_addr.s_addr = inet_addr(arg)) == INADDR_NONE)
		src.sin_addr.s_addr = get_ip_address(arg);
	if(bind(icmp_sock, (struct sockaddr *)&src, sizeof(src)) == -1)
		do_output(1, "Cannot bind to IP address %s", arg);
}
