ip6_to_str_buf(const ws_in6_addr *addr, gchar *buf, int buf_size)
{
	gchar addr_buf[WS_INET6_ADDRSTRLEN];
	int len;


	len = (int)g_strlcpy(buf, ws_inet_ntop6(addr, addr_buf, sizeof(addr_buf)), buf_size);

	if (len > buf_size - 1) {
		len = (int)g_strlcpy(buf, BUF_TOO_SMALL_ERR, buf_size);
	}
	return len;
}
