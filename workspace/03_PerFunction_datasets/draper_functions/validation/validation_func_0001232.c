sprint_open_modes(mode_t flags)
{
	static char outstr[1024];
	char *p;
	char sep = 0;
	const char *str;
	const struct xlat *x;

	p = str_append(outstr, "flags ");
	str = xlookup(open_access_modes, flags & 3);
	if (str) {
		p = str_append(p, str);
		flags &= ~3;
		if (!flags)
			return outstr;
		sep = '|';
	}

	for (x = open_mode_flags; x->str; x++) {
		if ((flags & x->val) == x->val) {
			if (sep)
				*p++ = sep;
			p = str_append(p, x->str);
			flags &= ~x->val;
			if (!flags)
				return outstr;
			sep = '|';
		}
	}

	if (sep)
		*p++ = sep;
	sprintf(p, "%#x", flags);
	return outstr;
}
