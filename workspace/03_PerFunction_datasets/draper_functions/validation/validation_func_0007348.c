rfc1035_init_resolv(struct rfc1035_res *res)
{
FILE	*fp=fopen("/etc/resolv.conf", "r");
char rfc1035_buf[512];
RFC1035_ADDR ns[MAXNS];
int nns=0;

	if (!fp)	return (-1);
	while (fgets(rfc1035_buf, sizeof(rfc1035_buf), fp))
	{
	char	*p;

		for (p=rfc1035_buf; *p; p++)
			*p=tolower(*p);
		for (p=rfc1035_buf; *p; p++)
			if (isspace((int)(unsigned char)*p))	break;
		if (*p)	*p++=0;

		if (strcmp(rfc1035_buf, "domain") == 0)
		{
			while (p && isspace((int)(unsigned char)*p))
				++p;
			rfc1035_init_defaultdomain(res, p);
			continue;
		}

		if (strcmp(rfc1035_buf, "nameserver"))	continue;
		while (*p && isspace((int)(unsigned char)*p))	p++;
		if (nns < MAXNS)
		{
		char	*q;

			for (q=p; *q && !isspace((int)(unsigned char)*q); q++)
				;
			*q=0;

			if (rfc1035_aton(p, &ns[nns++]) < 0)
				--nns;
		}
	}
	fclose(fp);
	rfc1035_init_ns(res, ns, nns);
	return (0);
}
