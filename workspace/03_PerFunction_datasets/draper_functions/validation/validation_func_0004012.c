map_read(void)
{
	char buf[256];
	FILE *f;

	if (!map_file)
		return;

	debug("reading map from %s\n", map_file);

	if (!(f = fopen(map_file, "r"))) {
		debug("unable to read map file, ignoring\n");
		return;
	}

	while (fgets(buf, sizeof(buf), f)) {
		char *p, *ipv4, *ipv6;
		map_t *m;

		for (p = buf; *p == ' ' || *p == '\t'; p++);

		if (!*p)
			continue;

		ipv4 = p;

		for (; *p && *p != ' ' && *p != '\t'; p++);

		if (!*p)
			continue;

		*p = 0;
		p++;

		for (; *p == ' ' || *p == '\t'; p++);

		if (!*p)
			continue;

		ipv6 = p;

		for (; *p && *p != ' ' && *p != '\t' && *p != '\r' && *p != '\n'; p++);

		*p = 0;

		debug("[%s] mapped to [%s]\n", ipv4, ipv6);

		m = (map_t*) xmalloc(sizeof(map_t));
		m->ipv4 = xstrdup(ipv4);
		m->ipv6 = xstrdup(ipv6);
		m->next = map_list;
		map_list = m;
	}

	fclose(f);
}
