get_u64_parm (int optional, const char flag_c, int *flag_p, __u64 *value_p,
		unsigned int min_value, __u64 limit, const char *eprefix, const char *emsg)
{
	int got_value = 0;
	__u64 value = *value_p;
	char *endp = NULL;

	if (!*argp && argc && (isdigit(**argv) || (flag_p && flag_c == **argv)))
		argp = *argv++, --argc;

	if (flag_p) {
		*flag_p = 0;
		if (*argp == flag_c) {
			*flag_p = 1;
			argp++;
		}
	}

	errno = 0;
	value = strtoll(argp, &endp, 0);
	if (errno != 0 || (endp != argp && ((__s64)value < (__s64)min_value || value > limit))) {
		fprintf(stderr, "  %s: %s\n", eprefix, emsg);
		exit(EINVAL);
	}
	if (endp != argp) {
		got_value = 1;
		*value_p = value;
		argp = endp;
	}
	if (!optional && !got_value) {
		fprintf(stderr, "  %s: %s\n", eprefix, emsg);
		exit(EINVAL);
	}
	return got_value;
}
