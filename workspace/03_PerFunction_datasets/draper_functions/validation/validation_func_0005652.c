config_int(struct configuration *p, unsigned long *i)
{
	char *e;
	unsigned long u;
	const char *t;

	if ((t = gettoken(p)) != t_string)
		return t;
	u = strtoul(p->tokbuf, &e, 0);
	if (*e || e == p->tokbuf)
		return e_inval;
	*i = u;
	return 0;
}
