static void update_cached_ttl(unsigned char *buf, int len, int new_ttl)
{
	unsigned char *c;
	uint16_t w;
	int l;


	c = buf + 12;
	len -= 12;


	l = dns_name_length(c);
	c += l;
	len -= l;
	c += 4;
	len -= 4;


	while (len > 0) {

		l = dns_name_length(c);
		c += l;
		len -= l;
		if (len < 0)
			break;

		c += 4;
		len -= 4;
		if (len < 0)
			break;


		c[0] = new_ttl >> 24 & 0xff;
		c[1] = new_ttl >> 16 & 0xff;
		c[2] = new_ttl >> 8 & 0xff;
		c[3] = new_ttl & 0xff;
		c += 4;
		len -= 4;
		if (len < 0)
			break;


		w = c[0] << 8 | c[1];
		c += w + 2;
		len -= w + 2;
	}
}
