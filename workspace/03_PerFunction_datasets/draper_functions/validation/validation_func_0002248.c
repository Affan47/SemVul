VTCP_hisname(int sock, char *abuf, unsigned alen, char *pbuf, unsigned plen)
{
	struct sockaddr_storage addr_s;
	socklen_t l;

	l = sizeof addr_s;
	if (!getpeername(sock, (void*)&addr_s, &l))
		VTCP_name(&addr_s, l, abuf, alen, pbuf, plen);
	else {
		(void)snprintf(abuf, alen, "<none>");
		(void)snprintf(pbuf, plen, "<none>");
	}
}
