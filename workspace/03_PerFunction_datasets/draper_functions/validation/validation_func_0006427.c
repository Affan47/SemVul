init_term()
{
	int i;
	const char *term = getenv("TERM");
	for (i = 0; terms[i].name; i++) {
		if (!strcmp(terms[i].name, term)) {
			keys = terms[i].keys;
			funcs = terms[i].funcs;
			return 0;
		}
	}
	return EUNSUPPORTED_TERM;
}
