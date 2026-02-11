parse_range(const char *str)
{
	unsigned int f1,f2,f3,f4,m,n, mask, start, end, len;
	struct dhcpv4_iprange *r;

	n = sscanf(str, "%u.%u.%u.%u/%u", &f1, &f2, &f3, &f4, &m);

	if (n != 5)
		goto parse_err;
	if (f1 > 255)
		goto parse_err;
	if (f2 > 255)
		goto parse_err;
	if (f3 > 255)
		goto parse_err;
	if (f4 > 255)
		goto parse_err;
	if (m == 0 || m > 30)
		goto parse_err;

	start = (f1 << 24) | (f2 << 16) | (f3 << 8) | f4;
	mask = ~((1 << (32 - m)) - 1);
	start = start & mask;
	end = start | ~mask;

	len = (end - start - 1) / (8 * sizeof(long)) + 1;

	r = _malloc(sizeof(*r) + len * sizeof(long));
	memset(r, 0, sizeof(*r));
	memset(r->free, 0xff, len * sizeof(long));
	r->routerip = start + 1;
	r->startip = start;
	r->mask = m;
	r->len = len;
	pthread_mutex_init(&r->lock, NULL);

	end -= start;
	r->free[(end - 1) / ( 8 * sizeof(long))] &= (1 << ((end - 1) % (8 * sizeof(long)) + 1)) - 1;
	r->free[0] &= ~3;

	return r;

parse_err:
	log_emerg("dhcpv4: failed to parse range=%s\n", str);
	return NULL;
}
