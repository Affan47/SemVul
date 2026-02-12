static int reply_query_type(unsigned char *msg, int len)
{
	unsigned char *c;
	int l;
	int type;


	c = msg + sizeof(struct domain_hdr);
	len -= sizeof(struct domain_hdr);

	if (len < 0)
		return 0;


	l = dns_name_length(c);
	c += l;
	type = c[0] << 8 | c[1];

	return type;
}
