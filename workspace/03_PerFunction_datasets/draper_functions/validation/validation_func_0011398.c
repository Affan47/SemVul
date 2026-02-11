print_protocol(const char *val)
{
	int i;
	char *out;

	errno = 0;
        i = strtoul(val, NULL, 10);
	if (errno) {
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
	} else {
		struct protoent *p = getprotobynumber(i);
		if (p)
			out = strdup(p->p_name);
		else
			out = strdup("undefined protocol");
	}
	return out;
}
